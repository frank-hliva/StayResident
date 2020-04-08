#include "pch.h"
#include "ILogger.h"

namespace Logging {

	ILogger::ILogger(shared_ptr<vector<shared_ptr<wostream>>> outputStreams)
		: outputStreams(outputStreams)
	{
	}

	ILogger::ILogger(shared_ptr<wostream> outputStream)
		: outputStreams(new vector<shared_ptr<wostream>> { outputStream })
	{
	}

	void ILogger::writeToAllStreams(LogItem item)
	{
		for (auto outputStream : *outputStreams)
		{
			write(outputStream, item);
			outputStream->flush();
		}
	}

	void ILogger::log(LogItem item)
	{
		writeToAllStreams(item);
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