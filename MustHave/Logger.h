#pragma once

#include <iostream>
#include <string>
#include "ILogger.h"

namespace Logging {

	class Logger : public ILogger
	{
	protected:
		virtual void write(wostream* outputStream, LogItem item) override;
	public:
		Logger(wostream* outputStream);
	};

}