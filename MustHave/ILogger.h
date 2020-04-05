#pragma once

#include <iostream>
#include <string>

namespace Logging {

	using namespace std;

	struct LogItem {
		wstring subject;
		wstring value;
	};

	class ILogger
	{
	protected:
		wostream* outputStream;
		virtual void write(wostream* outputStream, LogItem item) = 0;
	public:
		ILogger(wostream* outputStream);
		void log(LogItem item);
		void log(wstring subject, wstring value);
		void log(wstring value);
	};

}