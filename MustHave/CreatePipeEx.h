#pragma once
#include <Windows.h>
#include <string>

using namespace std;

namespace IO
{
    namespace Pipes
    {
        bool __stdcall CreatePipeW(
            OUT LPHANDLE readPipe,
            OUT LPHANDLE writePipe,
            IN LPSECURITY_ATTRIBUTES securityAttributes,
            IN unsigned long size,
            unsigned long readMode,
            unsigned long writeMode,
            wstring pipeName
        );
    }
}