#include "Starter.h"
#include <windows.h> 
#include <iostream>
#include <sstream>
#include <Path.h>
#include "CreatePipeEx.h"
#include "ExecutionFailed.h"

Starter::Starter(StarterProps props, shared_ptr<Logging::ILogger> logger) :
    props(props),
    _path(props.path),
    path(_path),
    repeatStart(props.repeatStart),
    wasStarted(_wasStarted),
    logger(logger)
{
}

ExecutionResult Starter::execute(wstring path)
{
    SECURITY_ATTRIBUTES securityAttributes;
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = true;
    securityAttributes.lpSecurityDescriptor = nullptr;

    createPipes(securityAttributes);

    PROCESS_INFORMATION processInfo;
    ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));

    STARTUPINFO startupInfo;
    ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
    startupInfo.cb = sizeof(STARTUPINFO);
    startupInfo.hStdError = childProcessStdOutWrite;
    startupInfo.hStdOutput = childProcessStdOutWrite;
    startupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startupInfo.dwFlags |= STARTF_USESTDHANDLES;

    CreateProcessW(
        nullptr,
        const_cast<wchar_t*>(path.c_str()),
        nullptr,
        nullptr,
        true,
        0,
        nullptr,
        IO::Path::onlyDirectoryName(path).c_str(),
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

    result.output = readFromChildProcessOutput();

    closePipes();

    return result;
}

string Starter::readFromChildProcessOutput()
{
    unsigned long bytesCount;
    char* charBuffer = new char[1L + maxBufferSize];
    bool isSuccess = ReadFile(childProcessStdOutRead, charBuffer, maxBufferSize, &bytesCount, nullptr);
    charBuffer[bytesCount] = '\0';
    string outputString(charBuffer);
    delete[] charBuffer;
    return outputString;
}

enum PipeCreationState Starter::createPipes(SECURITY_ATTRIBUTES& securityAttributes)
{
    childProcessStdOutWrite = nullptr;
    childProcessStdOutRead = nullptr;
    if (IO::Pipes::CreatePipeW(
        &childProcessStdOutRead,
        &childProcessStdOutWrite,
        &securityAttributes,
        0,
        0,
        0,
        L"\\\\.\\pipe\\stdOutPipe"
    ))
    {
        if (SetHandleInformation(childProcessStdOutRead, HANDLE_FLAG_INHERIT, 0))
        {
            return PipeCreationState::success;
        }
        else
        {
            throw Errors::ExecutionFailed(GetLastError());
        }
    }
    else
    {
        unsigned int errorCode = GetLastError();
        if (errorCode == ERROR_PIPE_BUSY)
        {
            return pipeIsBusy;
        }
        else
        {
            throw Errors::ExecutionFailed("A output pipe isn't created.", errorCode);
        }
    }
}

void Starter::closePipes()
{
    CloseHandle(childProcessStdOutWrite);
    CloseHandle(childProcessStdOutRead);
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