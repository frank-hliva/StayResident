#include "pch.h"
#include "Path.h"

namespace IO
{
	wstring Path::join(wstring path1, wstring path2)
	{
		wchar_t result[MAX_PATH] = L"";
		wchar_t* _result;
		_result = result;
		PathCombineW(_result, path1.c_str(), path2.c_str());
		return wstring(_result);
	}

	wstring Path::onlyDirectoryName(wstring path)
	{
		wchar_t* _path = (wchar_t*)path.c_str();
		PathRemoveFileSpecW(_path);
		return wstring(_path);
	}
}