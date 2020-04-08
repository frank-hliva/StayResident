#include <iostream>
#include "Path.h"
#include "ApplicationInfo.h"
#include "ApplicationConfig.h"
#include "Logger.h"
#include "StartupManager.h"
#include "Starter.h"

using namespace std;
using namespace Logging;

shared_ptr<vector<shared_ptr<wostream>>> logFileStreams(shared_ptr<ApplicationConfig> appConfig)
{
    shared_ptr<vector<shared_ptr<wostream>>> outStreams(new vector<shared_ptr<wostream>>);
    if (appConfig->loggingToStandardOutput)
    {
        outStreams->push_back(shared_ptr<wostream>(&wcout));
    }
    if (appConfig->loggingToFile)
    {
        shared_ptr<wofstream> logFile(new wofstream(appConfig->logFilePath));
        outStreams->push_back(logFile);
    }
    return outStreams;
}

int main()
{
    auto appDirectory = ApplicationInfo::directory();
    auto appConfigPath = IO::Path::join(appDirectory, L"App.toml");
    shared_ptr<ApplicationConfig> appConfig(new ApplicationConfig(appConfigPath));
    shared_ptr<Logger> logger(new Logger(logFileStreams(appConfig)));
    unique_ptr<StartupManager> startupManager(new StartupManager(logger));
    auto executablesPaths = appConfig->executablesPaths;
    for (auto path : executablesPaths)
    {
        startupManager->add(wstring(path.begin(), path.end()));
    }
    startupManager->startAll();
}