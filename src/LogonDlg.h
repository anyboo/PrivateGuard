#pragma once
#include "resource.h"
#include "wtlhelper\whwindow.h"
#include <atlutil.h>
#include "Tools.h"
#include "Setting.h"
#include "DlgMsgbox.h"

class CLogonDlg;

template<class T>
class CBaseSubWnd
{
public:
	CBaseSubWnd(int dlgCtrlID, T* pParent=NULL) : m_dlgCtrlID(dlgCtrlID), m_pParentWnd(pParent) {}

	void Show(BOOL bShow = TRUE) { if (m_pParentWnd) m_pParentWnd->SetItemVisible(m_dlgCtrlID, bShow); }

	bool IsVisible() { return m_pParentWnd ? m_pParentWnd->IsItemVisible(m_dlgCtrlID) : false; }

protected:
	CFont m_font;

private:
	T *m_pParentWnd;
	int m_dlgCtrlID;
};

class CLogonHomeWnd : public CBaseSubWnd<CLogonDlg>
{
public:
	CLogonHomeWnd(int dlgCtrlID, CLogonDlg* pParent=NULL) :  CBaseSubWnd(dlgCtrlID, pParent){}
	CEdit m_edit_username;
	CEdit m_edit_password;

	void Create(HWND hParent)
	{
		m_font.CreatePointFont(90,_T("微软雅黑"));

		m_edit_username.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL, WS_EX_CLIENTEDGE);
		m_edit_username.SetDlgCtrlID(31010);
		m_edit_username.SetFont(m_font.m_hFont);

		m_edit_password.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
		m_edit_password.SetDlgCtrlID(31011);
	};

	void ClearCtrlData()
	{
		m_edit_username.SetWindowText(_T(""));
		m_edit_password.SetWindowText(_T(""));
	}

	std::wstring GetUsername() { return GetItemTextW(m_edit_username.m_hWnd); }
	std::wstring GetPassword() { return GetItemTextW(m_edit_password.m_hWnd); }

	void SetUsername(std::wstring& text) { m_edit_username.SetWindowTextW(text.c_str()); }
	void SetPassword(std::wstring& text) { m_edit_password.SetWindowTextW(text.c_str()); }
};

class CRegister1Wnd : public CBaseSubWnd<CLogonDlg>
{
public:
	CRegister1Wnd(int dlgCtrlID, CLogonDlg* pParent=NULL) :  CBaseSubWnd(dlgCtrlID, pParent){}

	CEdit m_edit_username;
	CEdit m_edit_password;
	CEdit m_edit_confirmpassw;

	void Create(HWND hParent)
	{
		m_font.CreatePointFont(90,_T("微软雅黑"));

		m_edit_username.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL, WS_EX_CLIENTEDGE);
		m_edit_username.SetDlgCtrlID(11010);
		m_edit_username.SetFont(m_font.m_hFont);

		m_edit_password.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
		m_edit_password.SetDlgCtrlID(11011);

		m_edit_confirmpassw.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
		m_edit_confirmpassw.SetDlgCtrlID(11012);
	};	
	
	void ClearCtrlData()
	{
		m_edit_username.SetWindowText(_T(""));
		m_edit_password.SetWindowText(_T(""));
		m_edit_confirmpassw.SetWindowText(_T(""));
	}

	std::wstring GetUsername() { return GetItemTextW(m_edit_username.m_hWnd); }
	std::wstring GetPassword() { return GetItemTextW(m_edit_password.m_hWnd); }

	BOOL ValidateData()
	{
		std::wstring username = GetUsername();
		std::wstring password = GetPassword();
		std::wstring confirmpassw = GetItemTextW(m_edit_confirmpassw.m_hWnd);

		if (username.length() < 4)
		{
			CDlgMsgBox::Show(L"用户名不能小于4位，请重新输入。");
			return FALSE;
		}
		if (password.length() < 6)
		{
			CDlgMsgBox::Show(L"密码不能小于6位，请重新输入。");
			return FALSE;
		}
		else if (password != confirmpassw)
		{
			CDlgMsgBox::Show(L"密码不匹配，请重新输入。");
			m_edit_password.SetWindowTextW(L"");
			m_edit_confirmpassw.SetWindowTextW(L"");
			return FALSE;
		}

		return TRUE;
	}
};

class CRegister2Wnd : public CBaseSubWnd<CLogonDlg>
{
public:
	CRegister2Wnd(int dlgCtrlID, CLogonDlg* pParent=NULL) :  CBaseSubWnd(dlgCtrlID, pParent){}

	CEdit m_edit_sparepassw;
	CEdit m_edit_confirmpassw;

	void Create(HWND hParent)
	{
		m_edit_sparepassw.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
		m_edit_sparepassw.SetDlgCtrlID(12010);

		m_edit_confirmpassw.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
		m_edit_confirmpassw.SetDlgCtrlID(12011);
	};

	void ClearCtrlData()
	{
		m_edit_sparepassw.SetWindowText(_T(""));
		m_edit_confirmpassw.SetWindowText(_T(""));
	}

	std::wstring GetSparePassword() { return GetItemTextW(m_edit_sparepassw.m_hWnd); }

	BOOL ValidateData()
	{
		std::wstring sparepassw = GetSparePassword();
		std::wstring confirmpassw = GetItemTextW(m_edit_confirmpassw.m_hWnd);

		if (sparepassw.length() < 6)
		{
			CDlgMsgBox::Show(L"密码不能小于6位，请重新输入。");
			return FALSE;
		}
		else if (sparepassw != confirmpassw)
		{
			CDlgMsgBox::Show(L"密码不匹配，请重新输入。");
			m_edit_sparepassw.SetWindowTextW(L"");
			m_edit_confirmpassw.SetWindowTextW(L"");
			return FALSE;
		}

		CDlgMsgBox::Show(L"恭喜您，注册完成。您现在可以登录了。");

		return TRUE;
	}
};

class CForgetPassw1Wnd : public CBaseSubWnd<CLogonDlg>
{
public:
	CForgetPassw1Wnd(int dlgCtrlID, CLogonDlg* pParent=NULL) :  CBaseSubWnd(dlgCtrlID, pParent){}

	CEdit m_edit_username;

	void Create(HWND hParent)
	{
		m_font.CreatePointFont(90,_T("微软雅黑"));

		m_edit_username.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL, WS_EX_CLIENTEDGE);
		m_edit_username.SetDlgCtrlID(21010);
		m_edit_username.SetFont(m_font.m_hFont);
	};

	void ClearCtrlData()
	{
		m_edit_username.SetWindowText(_T(""));
	}
	
	BOOL ValidateData()
	{
		std::wstring username = GetItemTextW(m_edit_username.m_hWnd);

		if (username != CSETTING.m_username)
		{
			CDlgMsgBox::Show(L"用户名不正确，请重新输入。");
			return FALSE;
		}

		return TRUE;
	}
};

class CForgetPassw2Wnd : public CBaseSubWnd<CLogonDlg>
{
public:
	CForgetPassw2Wnd(int dlgCtrlID, CLogonDlg* pParent=NULL) :  CBaseSubWnd(dlgCtrlID, pParent){}

	CEdit m_edit_sparepassw;
	void Create(HWND hParent)
	{
		m_edit_sparepassw.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
		m_edit_sparepassw.SetDlgCtrlID(22010);
	};

	void ClearCtrlData()
	{
		m_edit_sparepassw.SetWindowText(_T(""));
	}

	BOOL ValidateData()
	{
		std::wstring sparepassw = GetItemTextW(m_edit_sparepassw.m_hWnd);

		if (sparepassw != CSETTING.m_retrievepassw)
		{
			CDlgMsgBox::Show(L"紧急号码不正确，请重新输入。");
			return FALSE;
		}

		return TRUE;
	}
};

class CForgetPassw3Wnd : public CBaseSubWnd<CLogonDlg>
{
public:
	CForgetPassw3Wnd(int dlgCtrlID, CLogonDlg* pParent=NULL) :  CBaseSubWnd(dlgCtrlID, pParent){}

	CEdit m_edit_newpassw;
	CEdit m_edit_confirmpassw;

	void Create(HWND hParent)
	{
		m_edit_newpassw.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
		m_edit_newpassw.SetDlgCtrlID(23010);
		m_edit_confirmpassw.Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
		m_edit_confirmpassw.SetDlgCtrlID(23011);
	};
	
	void ClearCtrlData()
	{
		m_edit_newpassw.SetWindowText(_T(""));
		m_edit_confirmpassw.SetWindowText(_T(""));
	}

	std::wstring GetNewPassword() { return GetItemTextW(m_edit_newpassw.m_hWnd); }
		
	BOOL ValidateData()
	{
		std::wstring newpassw = GetNewPassword();
		std::wstring confirmpassw = GetItemTextW(m_edit_confirmpassw.m_hWnd);

		if (newpassw.length() < 6)
		{
			CDlgMsgBox::Show(L"密码不能小于6位，请重新输入。");
			return FALSE;
		}
		else if (newpassw != confirmpassw)
		{
			CDlgMsgBox::Show(L"密码不匹配，请重新输入。");
			m_edit_newpassw.SetWindowTextW(L"");
			m_edit_confirmpassw.SetWindowTextW(L"");
			return FALSE;
		}

		CDlgMsgBox::Show(L"修改密码成功，您现在可以登录了。");
		return TRUE;
	}
};

class CLogonDlg
	: public CBkDialogImpl<CLogonDlg>
	, public CWHRoundRectFrameHelper<CLogonDlg>
{
	typedef CBkDialogImpl<CLogonDlg> __base_class ;

public:
	CLogonDlg();
	~CLogonDlg();

public:
	LRESULT OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/);

	void OnBkBtnClose();

	void OnBkBtnMin();
	
	void OnBtnLogon();

	void OnClickForgetPassw();

	void OnClickRegister();

	void OnRegBtnNext();

	void OnRegBtnCancel();

	void OnForgetPwNext();

	void OnForgetPwCancel();

protected:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_CLOSE, CLogonDlg::OnBkBtnClose)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_MIN, CLogonDlg::OnBkBtnMin)
		BK_NOTIFY_ID_COMMAND(1006, CLogonDlg::OnBtnLogon)
		BK_NOTIFY_ID_COMMAND(1005, CLogonDlg::OnClickForgetPassw)
		BK_NOTIFY_ID_COMMAND(1007, CLogonDlg::OnClickRegister)
		BK_NOTIFY_ID_COMMAND(1001, CLogonDlg::OnRegBtnNext)
		BK_NOTIFY_ID_COMMAND(1002, CLogonDlg::OnRegBtnCancel)
		BK_NOTIFY_ID_COMMAND(1003, CLogonDlg::OnForgetPwNext)
		BK_NOTIFY_ID_COMMAND(1004, CLogonDlg::OnForgetPwCancel)
		BK_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CLogonDlg)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP( __base_class )
		CHAIN_MSG_MAP( CWHRoundRectFrameHelper<CLogonDlg> )
		MSG_WM_INITDIALOG(CLogonDlg::OnInitDialog)
		END_MSG_MAP()

private:
	void CreateChildCtrl();

public:
	// UI Control
	CLogonHomeWnd m_homeWnd;
	CBaseSubWnd<CLogonDlg> m_regRootWnd;
	CRegister1Wnd m_reg1Wnd;
	CRegister2Wnd m_reg2Wnd;
	CBaseSubWnd<CLogonDlg> m_forgetRootWnd;
	CForgetPassw1Wnd m_forget1Wnd;
	CForgetPassw2Wnd m_forget2Wnd;
	CForgetPassw3Wnd m_forget3Wnd;
};
