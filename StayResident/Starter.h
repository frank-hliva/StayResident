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
    string output = "";
    unsigned long exitCode = 0;
};

class Starter {
private:
    HANDLE childProcessStdOutWrite = nullptr;
    HANDLE childProcessStdOutRead = nullptr;
    void createPipes(SECURITY_ATTRIBUTES& securityAttributes);
    void closePipes();
    string readFromChildProcessOutput();
    void maybeLog(wstring name, wstring value);
protected:
    const int maxBufferSize = 4096;
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