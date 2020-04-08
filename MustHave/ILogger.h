#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace Logging {

	using namespace std;

	struct LogItem {
		wstring subject;
		wstring value;
	};

	class ILogger
	{
	protected:
		shared_ptr<vector<shared_ptr<wostream>>> outputStreams;
		virtual void write(shared_ptr<wostream> outputStream, LogItem item) = 0;
		virtual void writeToAllStreams(LogItem item);
	public:
		ILogger(shared_ptr<wostream> outputStream);
		ILogger(shared_ptr<vector<shared_ptr<wostream>>> outputStreams);
		void log(LogItem item);
		void log(wstring subject, wstring value);
		void log(wstring value);
	};

}