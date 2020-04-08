#pragma once

#include <iostream>
#include <string>
#include "ILogger.h"

namespace Logging {

	class Logger : public ILogger
	{
	protected:
		virtual void write(shared_ptr<wostream> outputStream, LogItem item) override;
	public:
		Logger(shared_ptr<wostream> outputStream);
		Logger(shared_ptr<vector<shared_ptr<wostream>>> outputStreams);
	};

}