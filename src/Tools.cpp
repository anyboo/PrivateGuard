#include "stdafx.h"
#include "Tools.h"


void GetAppRunDir(std::string& strPath)
{
	char buf[MAX_PATH] = {0};
	::GetModuleFileNameA(NULL, buf, MAX_PATH);

	strPath = buf;
	strPath = strPath.substr(0, strPath.rfind('\\'));
}

void GetAppRunDir(std::wstring& wsPath)
{
	wchar_t buf[MAX_PATH] = {0};
	::GetModuleFileNameW(NULL, buf, MAX_PATH);

	wsPath = buf;
	wsPath = wsPath.substr(0, wsPath.rfind('\\'));
}

std::wstring GetItemTextW(HWND hWnd)
{
	ATLASSERT(::IsWindow(hWnd));

	int size = ::GetWindowTextLength(hWnd);
	if (size == 0)	return L"";

	wchar_t *pBuffer = new wchar_t[size+1];
	::GetWindowTextW(hWnd, pBuffer, size+1);
	std::wstring wsText(pBuffer);
	delete [] pBuffer;

	return wsText;
}