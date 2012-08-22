#pragma once

enum
{
	UDISK_BEGIN,
	UDISK_BEGIN_OPEN_SAFE_UDISK,
	UDISK_BEGIN_CLOSE_SAFE_UDISK,
	UDISK_END,
};

class CUDiskMgr;
class IUDiskObserver
{
public:
	virtual void OnUDiskStatus(CUDiskMgr *pperf, DWORD dwStatus) = 0;
};

class UDiskBase 
{
public:
	BOOL PerfOpenSafeUDisk()
	{
		for (int i=0;i<=10;i++)
		{
			Sleep(200);
		}
		return TRUE;
	}

	BOOL PerfCloseSafeUDisk()
	{
		for (int i=0;i<=10;i++)
		{
			Sleep(200);
		}
		return TRUE;
	}
};

class UDiskEx
{
public:

	BOOL PerfOpenSafeUDisk()
	{
		for (int i=0;i<=10;i++)
		{
			Sleep(200);
		}
		return TRUE;
	}

	BOOL PerfCloseSafeUDisk()
	{
		for (int i=0;i<=10;i++)
		{
			Sleep(200);
		}
		return TRUE;
	}
};


class CUDiskMgr
{
public:
	CUDiskMgr(void);
	~CUDiskMgr(void);

	static bool OpenSafeUDisk();

	static bool CloseSafeUDisk();

	bool Start(bool bOpenUDisk);
	
	static unsigned int WINAPI UDiskProc(LPVOID lpParam);
	
	void NotifyObserver(DWORD dwStatus);
	
public:
	DWORD GetResult() { return m_dwResult; }

	void SetObserver(IUDiskObserver *pobserver) { m_observer = pobserver; }

	bool IsUDiskOpened() { return m_bIsUDiskOpened; } 


protected:
	HANDLE		m_hThreadRunning;
	IUDiskObserver	*m_observer;

public:
	BOOL		m_bRunning;
	DWORD		m_dwResult;
	bool		m_bOpenUDisk;
	bool		m_bIsUDiskOpened;
};
