#include "pch.h"
#include "ILogger.h"

namespace Logging {

	ILogger::ILogger(wostream* outputStream)
		: outputStream(outputStream)
	{
	}

	void ILogger::log(LogItem item)
	{
		write(outputStream, item);
		outputStream->flush();
	}

	void ILogger::log(wstring subject, wstring value)
	{
		log(LogItem{ subject, value });
	}

	void ILogger::log(wstring value)
	{
		log(L"", value);
	}

}