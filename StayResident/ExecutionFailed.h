#pragma once

#include <string>
#include "Exception.h"

using namespace std;

namespace Errors
{
    class ExecutionFailed : public Exception
    {
    public:
        ExecutionFailed(string message = "");
        const char* type() const throw ();
    };
}

