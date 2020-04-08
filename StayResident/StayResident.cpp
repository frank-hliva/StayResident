#include <iostream>
#include "Logger.h"
#include "StartupManager.h"
#include "Path.h"
#include "ApplicationInfo.h"
#include "cpptoml.h"
#include "Starter.h"
#include "boost/algorithm/string/replace.hpp"

using namespace std;
using namespace Logging;

class AppConfig
{
private:
    vector<string> _executablesPaths;
    wstring _logFilePath;
    bool _loggingToStandardOutput;
    bool _loggingToFile;
protected:
    shared_ptr<cpptoml::table> configTable;
    shared_ptr<cpptoml::table> startupTable;
    shared_ptr<cpptoml::table> loggingTable;
    shared_ptr<cpptoml::table> loggingTargetsTable;
public:
    AppConfig(wstring appConfigPath) : configTable(
        cpptoml::parse_file(
            string(appConfigPath.begin(), appConfigPath.end())
        )
    )
    {
        startupTable = configTable->get_table("Startup");
        loggingTable = configTable->get_table("Logging");
        auto logFilePath = loggingTable->get_as<string>("log_file_path");
        _logFilePath = boost::algorithm::replace_all_copy(
            wstring(logFilePath->begin(), logFilePath->end()),
            "$APP_DIR",
            ApplicationInfo::directory()
        );
        loggingTargetsTable = loggingTable->get_table("Targets");
        _loggingToStandardOutput = loggingTargetsTable->get_as<bool>("standard_output").value_or(false);
        _loggingToFile = loggingTargetsTable->get_as<bool>("file").value_or(true);
        _executablesPaths = startupTable->get_array_of<string>("executables_paths").value_or(vector<string>());
    }
    const wstring& logFilePath = _logFilePath;
    const bool& loggingToStandardOutput = _loggingToStandardOutput;
    const bool& loggingToFile = _loggingToFile;
    const vector<string>& executablesPaths = _executablesPaths;
};

shared_ptr<vector<shared_ptr<wostream>>> logFileStreams(shared_ptr<AppConfig> appConfig)
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
    shared_ptr<AppConfig> appConfig(new AppConfig(appConfigPath));
    shared_ptr<Logger> logger(new Logger(logFileStreams(appConfig)));
    unique_ptr<StartupManager> startupManager(new StartupManager(logger));
    auto executablesPaths = appConfig->executablesPaths;
    for (auto path : executablesPaths)
    {
        startupManager->add(wstring(path.begin(), path.end()));
    }
    startupManager->startAll();
}