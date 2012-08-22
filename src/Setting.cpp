#include "stdafx.h"
#include "Setting.h"
#include "Tools.h"

static wchar_t wszXorPad[SE_XORPAD_SIZE] = L"you are so bad.";

CSetting::CSetting()
: m_username(L"")
, m_password(L"")
, m_retrievepassw(L"")
{
	Load();
}

CSetting::~CSetting()
{
}

void CSetting::Save()
{
	std::wstring wsAppPath;
	GetAppRunDir(wsAppPath);
	std::wstring wsConfPath = wsAppPath + CONFIG_PATH;

	WritePrivateProfileString(L"Setting", L"username", m_username.c_str(), wsConfPath.c_str());

	std::wstring cryptpassw = Encrypt(m_password);
	WritePrivateProfileString(L"Setting", L"passw", cryptpassw.c_str(), wsConfPath.c_str());

	cryptpassw = Encrypt(m_retrievepassw);
	WritePrivateProfileString(L"Setting", L"retrievepassw", cryptpassw.c_str(), wsConfPath.c_str());
}

void CSetting::Load()
{
	std::wstring wsAppPath;
	GetAppRunDir(wsAppPath);
	std::wstring wsConfPath = wsAppPath + CONFIG_PATH;

	wchar_t buffer[MAX_LEN*3] = {0};
	::GetPrivateProfileString(L"Setting", L"username",L"", buffer, _countof(buffer)*sizeof(wchar_t), wsConfPath.c_str());
	m_username = buffer;

	memset(buffer, 0, _countof(buffer)*sizeof(wchar_t));
	::GetPrivateProfileString(L"Setting", L"passw",L"", buffer, _countof(buffer)*sizeof(wchar_t), wsConfPath.c_str());
	m_password = Decrypt(buffer);

	memset(buffer, 0, _countof(buffer)*sizeof(wchar_t));
	::GetPrivateProfileString(L"Setting", L"retrievepassw",L"", buffer, _countof(buffer)*sizeof(wchar_t), wsConfPath.c_str());
	m_retrievepassw = Decrypt(buffer);
}

std::wstring CSetting::Encrypt(const std::wstring& wsSrc)
{
	std::wstring strDest(L"");
	for(int i = 0; i < wsSrc.length(); i++)
	{
		wchar_t wc = (wchar_t)(wsSrc[i]^wszXorPad[i % SE_XORPAD_SIZE]);
		wchar_t buffer[8] = {0};
		wsprintf(buffer, L"%03d", wc);
		strDest.append(buffer);
	}

	return strDest;
}


std::wstring CSetting::Decrypt(const std::wstring& wsSrc)
{
	std::wstring strDest(L"");
	for(int i = 0,j=0; i < wsSrc.length(); i=i+3)
	{
		std::wstring strInt = wsSrc.substr(i, 3);
		wchar_t wc = (wchar_t)_wtoi(strInt.c_str());

		wc ^= wszXorPad[(j++) % SE_XORPAD_SIZE];
		
		strDest += wc;
	}

	return strDest;
}