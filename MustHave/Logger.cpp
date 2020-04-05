#include "pch.h"
#include "Logger.h"
#include <chrono>
#include <iomanip>
#include <time.h>

namespace Logging {

	void Logger::write(wostream* outputStream, LogItem item)
	{
		std::time_t time = std::time(0);
		std::tm* now = std::localtime(&time);
		(*outputStream) << L"[" << std::put_time(now, L"%F %T") << L"] ";
		if (item.subject != L"")
		{
			(*outputStream) << item.subject << ": ";
		}
		(*outputStream) << item.value << endl;
	}

	Logger::Logger(wostream* outputStream)
		: ILogger(outputStream)
	{
	}

}