#include "ExecutionFailed.h"

namespace Errors
{
    ExecutionFailed::ExecutionFailed(string message)
        : Exception(message)
    {
    }

    const char* ExecutionFailed::type() const throw ()
    {
        return "ExecutionFailed";
    }
}
