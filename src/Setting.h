#pragma once
#include <string>

#define SE_XORPAD_SIZE 16

#define MAX_LEN 33


#define CONFIG_PATH _T("\\conf.ini")
class CSetting
{
public: 
	CSetting();
	~CSetting();

public:
	void Save();
	void Load();

	static CSetting& getInstance() { static CSetting sSetting; return sSetting; }

private:
	std::wstring Encrypt(const std::wstring& wsSrc);
	std::wstring Decrypt(const std::wstring& wsSrc);

public:
	std::wstring m_username;
	std::wstring m_password;
	std::wstring m_retrievepassw;
};

#define CSETTING CSetting::getInstance()