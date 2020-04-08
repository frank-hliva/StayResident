#include "pch.h"
#include "Logger.h"
#include <chrono>
#include <iomanip>
#include <time.h>
#include <vector>
#include <sstream>

namespace Logging {

	void Logger::write(shared_ptr<wostream> outputStream, LogItem item)
	{
		std::time_t time = std::time(0);
		std::tm* now = std::localtime(&time);
		wstringstream out;
		out << L"[" << std::put_time(now, L"%F %T") << L"] ";
		if (item.subject != L"")
		{
			out << item.subject << ": ";
		}
		out << item.value << endl;
		(*outputStream) << out.rdbuf();
	}

	Logger::Logger(shared_ptr<vector<shared_ptr<wostream>>> outputStreams)
		: ILogger(outputStreams)
	{
	}

	Logger::Logger(shared_ptr<wostream> outputStream)
		: ILogger(outputStream)
	{
	}

}