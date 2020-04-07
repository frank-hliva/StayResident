#include "Starter.h"
#include <cstdio>
#include <windows.h> 
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "ExecutionFailed.h"

string Starter::readChildProcessOutput(const int maxBufferSize)
{
    unsigned long bytesCount, dwWritten;
    char* charBuffer = new char[(long int)maxBufferSize + (long int)1];
    bool isSuccess = false; 
    isSuccess = ReadFile(childStdOutReadPipe, charBuffer, maxBufferSize, &bytesCount, nullptr);
    charBuffer[bytesCount] = '\0';
    string outputString(charBuffer);
    delete[] charBuffer;
    return outputString;
}

ExecutionResult Starter::execute(wstring path)
{
    childStdOutReadPipe = nullptr;
    childProcessStdOut = nullptr;
    SECURITY_ATTRIBUTES securityAttributes;
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = true;
    securityAttributes.lpSecurityDescriptor = nullptr;

    if (!CreatePipe(&childStdOutReadPipe, &childProcessStdOut, &securityAttributes, 0)) {
        throw Errors::ExecutionFailed("A pipe isn't created");
    }

    if (!SetHandleInformation(childStdOutReadPipe, HANDLE_FLAG_INHERIT, 0)) {
        throw Errors::ExecutionFailed();
    }

    PROCESS_INFORMATION processInfo;
    STARTUPINFO startupInfo;

    ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
    startupInfo.cb = sizeof(STARTUPINFO);
    startupInfo.hStdError = childProcessStdOut;
    startupInfo.hStdOutput = childProcessStdOut;
    startupInfo.dwFlags |= STARTF_USESTDHANDLES;

    CreateProcessW(
        nullptr,
        const_cast<wchar_t*>(path.c_str()),
        nullptr,
        nullptr,
        true,
        0,
        nullptr,
        nullptr,
        &startupInfo,
        &processInfo
    );

    WaitForSingleObject(processInfo.hProcess, INFINITE);
    unsigned long exitCode;
    GetExitCodeProcess(processInfo.hProcess, &exitCode);
    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);
 
    ExecutionResult result;
    result.exitCode = exitCode;

    result.output = ""; //readChildProcessOutput(4096);
    CloseHandle(childProcessStdOut);
    CloseHandle(childStdOutReadPipe);
    return result;
}

Starter::Starter(StarterProps props, shared_ptr<Logging::ILogger> logger)
    :
        props(props),
        _path(props.path),
        path(_path),
        repeatStart(props.repeatStart),
        wasStarted(_wasStarted),
        logger(logger)
{
}

void Starter::maybeLog(wstring subject, wstring value)
{
    if (logger)
    {
        wstringstream subjects;
        subjects << _path;
        if (subject != L"")
        {
            subjects << L" -> " << subject << L" ";
        } 
        logger->log(subjects.str(), value);
    }
}

void Starter::startOnce()
{
    maybeLog(L"Starting", L"OK");
    _wasStarted = true;

    ExecutionResult result = execute(_path);
    _wasStarted = false;
    wstringstream out;
    out << "RESULT(" << result.exitCode << ") " << wstring(result.output.begin(), result.output.end());
    maybeLog(result.exitCode == 0 ? L"Stop" : L"Crash", out.str());
}

void Starter::start()
{
    do
    {
        this->startOnce();
    } while (repeatStart);
}