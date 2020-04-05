#pragma once

#include <map>
#include <string>
#include "Starter.h"
#include "ILogger.h"

typedef map<wstring, shared_ptr<Starter>> StartupItems;

class StartupManager {
private:
    unique_ptr<StartupItems> _items;
    shared_ptr<Logging::ILogger> logger;
public:
    StartupManager(shared_ptr<Logging::ILogger> logger = nullptr);
    const StartupItems& items;
    void add(StarterProps props);
    void add(const wstring path, const bool repeatStart = true);
    void startAll();
};