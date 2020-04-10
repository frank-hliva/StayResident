#include "ExecutionFailed.h"

namespace Errors
{
    ExecutionFailed::ExecutionFailed(string message, unsigned int errorCode) :
        Exception(message),
        errorCode()
    {
    }

    const char* ExecutionFailed::type() const throw ()
    {
        return "ExecutionFailed";
    }

    const unsigned int Exception::code() const throw ()
    {
        return 0;
    }
}
