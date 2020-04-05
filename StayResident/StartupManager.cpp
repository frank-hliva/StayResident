#include "StartupManager.h"
#include <thread>
#include <vector>
#include <algorithm>

StartupManager::StartupManager(shared_ptr<Logging::ILogger> logger)
	: logger(logger), _items(new StartupItems()), items(*_items)
{
}

void StartupManager::add(StarterProps props)
{
	shared_ptr<Starter> starter(new Starter(props, logger));
	_items->insert(pair<wstring, shared_ptr<Starter>>(props.path, starter));
}

void StartupManager::add(const wstring path, const bool repeatStart)
{
	add(StarterProps{ path, repeatStart });
}

void StartupManager::startAll()
{
	vector<thread> workers;
	for (auto item : *_items)
	{
		workers.push_back(std::thread([item]()
		{
			item.second->start();
		}));
	}

	for (auto &t : workers)
	{
		t.join();
	}
}