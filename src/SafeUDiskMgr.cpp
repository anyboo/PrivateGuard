#include "StdAfx.h"
#include "SafeUDiskMgr.h"


CUDiskMgr::CUDiskMgr()
: m_hThreadRunning(NULL)
, m_bRunning(FALSE)
, m_dwResult(-1)
, m_observer(NULL)
, m_bOpenUDisk(true)
, m_bIsUDiskOpened(false)
{
}

CUDiskMgr::~CUDiskMgr()
{
}

bool CUDiskMgr::Start(bool bOpenUDisk)
{
	m_bOpenUDisk = bOpenUDisk;
	if (m_bRunning)
		return true;

	if (m_hThreadRunning)
	{
		CloseHandle(m_hThreadRunning);
		m_hThreadRunning = NULL;
	}

	m_hThreadRunning = (HANDLE) _beginthreadex(NULL, 0, UDiskProc, this, 0, NULL);
	if (m_hThreadRunning)
		m_bRunning = TRUE;
	else
		return false;

	return true;
}

unsigned int WINAPI CUDiskMgr::UDiskProc(LPVOID lpParam)
{
	SetThreadPriority(::GetCurrentThread (), THREAD_PRIORITY_HIGHEST );

	CUDiskMgr *pMgr = (CUDiskMgr*) lpParam;

	pMgr->NotifyObserver(UDISK_BEGIN);

	if (pMgr->m_bOpenUDisk)
	{
		pMgr->NotifyObserver(UDISK_BEGIN_OPEN_SAFE_UDISK);
		pMgr->m_dwResult = OpenSafeUDisk();
		pMgr->m_bIsUDiskOpened = (pMgr->m_dwResult == 1 ? true : false);

	}
	else
	{
		pMgr->NotifyObserver(UDISK_BEGIN_CLOSE_SAFE_UDISK);
		pMgr->m_dwResult = CloseSafeUDisk();
		pMgr->m_bIsUDiskOpened = (pMgr->m_dwResult == 1 ? false : true);
	}

	pMgr->m_bRunning = FALSE;

	pMgr->NotifyObserver(UDISK_END);
	return 0;
}

void CUDiskMgr::NotifyObserver(DWORD dwStatus)
{
	if (m_observer)
		m_observer->OnUDiskStatus(this, dwStatus);
}

bool CUDiskMgr::OpenSafeUDisk()
{
	for (int i=0;i<=10;i++)
	{
		Sleep(200);
	}
	return true;
}

bool CUDiskMgr::CloseSafeUDisk()
{
	for (int i=0;i<=10;i++)
	{
		Sleep(200);
	}
	return true;
}