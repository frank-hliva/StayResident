#include "pch.h"
#include "ApplicationInfo.h"
#include "Windows.h"
#include <Shlwapi.h>

wstring ApplicationInfo::path()
{

	wchar_t filePath[MAX_PATH] = { 0 };
	GetModuleFileNameW(nullptr, filePath, MAX_PATH);
	return wstring(filePath);
}

wstring ApplicationInfo::directory()
{

	wchar_t path[MAX_PATH] = { 0 };
	GetModuleFileNameW(nullptr, path, MAX_PATH);
	PathRemoveFileSpecW(path);
	return wstring(path);
}