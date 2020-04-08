#include "ApplicationConfig.h"
#include "Path.h"
#include "ApplicationInfo.h"
#include "boost/algorithm/string/replace.hpp"

ApplicationConfig::ApplicationConfig(wstring appConfigPath) : configTable(
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