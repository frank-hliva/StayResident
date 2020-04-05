#include "pch.h"
#include "Exception.h";

namespace Errors {

	Exception::Exception(const std::string& message) : message(message) {}

	Exception::~Exception() throw () {}

	const char* Exception::what() const throw ()
	{
		return message.c_str();
	}

	const unsigned int Exception::code() const throw ()
	{
		return 0;
	}

	const char* Exception::type() const throw ()
	{
		return "Exception";
	}

	std::ostream& operator << (std::ostream& stream, const Exception& error)
	{
		auto code = error.code();
		std::string codeString = code > 0 ? (std::to_string(code) + " ") : "";
		return stream << codeString << "[" << error.type() << "]: " << error.message;
	}

}