#pragma once

#include <iostream>
#include <string>
#include "Windows.h"
#include <Shlwapi.h>

using namespace std;

namespace IO
{
	class Path
	{
	public:
		static wstring join(wstring path1, wstring path2);
	};
}