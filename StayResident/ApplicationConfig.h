#pragma once

#include <iostream>
#include "cpptoml.h"

using namespace std;

class ApplicationConfig
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
    ApplicationConfig(wstring appConfigPath);
    const wstring& logFilePath = _logFilePath;
    const bool& loggingToStandardOutput = _loggingToStandardOutput;
    const bool& loggingToFile = _loggingToFile;
    const vector<string>& executablesPaths = _executablesPaths;
};