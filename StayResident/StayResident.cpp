#include <iostream>
#include "Logger.h"
#include "StartupManager.h"
#include "Path.h"
#include "ApplicationInfo.h"
#include "cpptoml.h"
#include "Starter.h"

using namespace std;
using namespace Logging;

int main()
{
    auto logFilePath = IO::Path::join(ApplicationInfo::directory(), L"Startup.log");
    auto appConfigPath = IO::Path::join(ApplicationInfo::directory(), L"App.toml");
    auto appConfig = cpptoml::parse_file(string(appConfigPath.begin(), appConfigPath.end()));
    wofstream logFile(logFilePath);
    shared_ptr<Logger> logger(new Logger(&logFile));
    unique_ptr<StartupManager> startupManager(new StartupManager(logger));
    auto paths = appConfig->get_table("Startup")->get_array_of<string>("paths");
    for (auto path : *paths)
    {
        startupManager->add(wstring(path.begin(), path.end()));
    }
    startupManager->startAll();
}