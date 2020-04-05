#include "pch.h"
#include "Path.h"

namespace IO
{
	wstring Path::join(wstring path1, wstring path2)
	{
		wchar_t result[MAX_PATH] = L"";
		wchar_t* presult;
		presult = result;
		PathCombineW(presult, path1.c_str(), path2.c_str());
		return wstring(presult);
	}
}