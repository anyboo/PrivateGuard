// bkwintpl.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "PrivacyGuard.h"
#include "Setting.h"
#include "LogonDlg.h"
#include "MainFrame.h"

CAppModule _Module;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
	// If you are running on NT 4.0 or higher you can use the following call instead to 
	// make the EXE free threaded. This means that calls come in on a random RPC thread.
	//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	int nRet = 0;
	
	{
		BkFontPool::SetDefaultFont(_T("宋体"), -12);
		BkSkin::LoadSkins(IDR_BK_SKIN_APP);
		BkStyle::LoadStyles(IDR_BK_STYLE_APP);
		BkString::Load(IDR_BK_STRING_APP);

		CSETTING;

		{
			CLogonDlg logonDlg;
			if (logonDlg.DoModal() == IDCANCEL)
				goto CANCEL;
		}

		CMainFrame dlg;
		dlg.DoModal();
	}	

CANCEL:

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
