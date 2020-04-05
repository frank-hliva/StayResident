#pragma once

#include <iostream>
#include <string>

namespace Errors {

	class Exception : virtual public std::exception
	{
	private:
		std::string message;
		friend std::ostream& operator << (std::ostream& stream, const Exception& error);
	public:
		explicit Exception(const std::string& message);

		virtual ~Exception() throw ();

		virtual const char* what() const throw ();

		virtual const unsigned int code() const throw ();

		virtual const char* type() const throw ();
	};

	std::ostream& operator << (std::ostream& stream, const Exception& error);

}