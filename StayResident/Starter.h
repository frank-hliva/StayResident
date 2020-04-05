#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Windows.h"
#include <exception>
#include "ILogger.h"

using namespace std;

struct StarterProps {
    wstring path = nullptr;
    bool repeatStart = true;
};

struct ExecutionResult {
    string output;
    unsigned long exitCode;
};

class Starter {
private:
    HANDLE childStdOutReadPipe = nullptr;
    HANDLE childProcessStdOut = nullptr;
    string readChildProcessOutput(const int maxBufferSize);
    void maybeLog(wstring name, wstring value);
protected:
    wstring _path;
    bool _wasStarted = false;
    shared_ptr<Logging::ILogger> logger;
    ExecutionResult execute(wstring path);
    void startOnce();
public:
    Starter(StarterProps props, shared_ptr<Logging::ILogger> logger = nullptr);
    void start();
    const wstring& path;
    const StarterProps& props;
    const bool repeatStart;
    const bool& wasStarted;
};