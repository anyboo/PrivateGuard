#include "stdafx.h"
#include "LogonDlg.h"
#include "charset.h"


CLogonDlg::CLogonDlg()
: CBkDialogImpl<CLogonDlg>(IDR_BK_LOGO_DIALOG)
, m_homeWnd(30000, this)
, m_regRootWnd(10000, this)
, m_reg1Wnd(11000, this)
, m_reg2Wnd(12000, this)
, m_forgetRootWnd(20000, this)
, m_forget1Wnd(21000, this)
, m_forget2Wnd(22000, this)
, m_forget3Wnd(23000, this)
{
}

CLogonDlg::~CLogonDlg()
{
}

LRESULT CLogonDlg::OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/)
{
	CreateChildCtrl();

	return TRUE;
}

void CLogonDlg::CreateChildCtrl()
{
	m_homeWnd.Create(GetViewHWND());
	if (CSETTING.m_username.empty())
	{
		SetItemVisible(1007, TRUE);
	}
	else
	{
		m_homeWnd.SetUsername(CSETTING.m_username);
		SetItemVisible(1007, FALSE);
	}

	m_reg1Wnd.Create(GetViewHWND());
	m_reg2Wnd.Create(GetViewHWND());

	m_forget1Wnd.Create(GetViewHWND());
	m_forget2Wnd.Create(GetViewHWND());
	m_forget3Wnd.Create(GetViewHWND());
}

void CLogonDlg::OnBkBtnClose()
{
	EndDialog(IDCANCEL);
}

void CLogonDlg::OnBkBtnMin()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE | HTCAPTION, 0);
}

void CLogonDlg::OnBtnLogon()
{
	if (CSETTING.m_username.empty())
	{
		CDlgMsgBox::Show(L"请先注册账号，再登陆。注册功能在右下角，请按步骤完成注册。");
		return;
	}
	std::wstring wsUsername = m_homeWnd.GetUsername();
	std::wstring wsPassword = m_homeWnd.GetPassword();
	if (wsUsername.empty())
	{
		CDlgMsgBox::Show(L"请输入用户名。");
		return;
	}
	else if (CSETTING.m_username != wsUsername)
	{
		CDlgMsgBox::Show(L"请输入注册过的用户名。");
		return;
	}

	if (wsPassword.empty())
	{
		CDlgMsgBox::Show(L"密码不能为空，请输入密码。");
		return;
	}
	else if (CSETTING.m_password != wsPassword)
	{
		CDlgMsgBox::Show(L"密码错误，请输入正确的密码。");
		return;
	}

	EndDialog(IDOK);
}

void CLogonDlg::OnClickForgetPassw()
{
	m_homeWnd.Show(FALSE);

	m_forget1Wnd.ClearCtrlData();
	m_forget2Wnd.ClearCtrlData();
	m_forget3Wnd.ClearCtrlData();
	
	m_forget1Wnd.Show();
	m_forget2Wnd.Show(FALSE);
	m_forget3Wnd.Show(FALSE);
	m_forgetRootWnd.Show();
}

void CLogonDlg::OnClickRegister()
{
	m_homeWnd.Show(FALSE);

	m_reg1Wnd.ClearCtrlData();
	m_reg2Wnd.ClearCtrlData();

	m_reg1Wnd.Show();
	m_reg2Wnd.Show(FALSE);
	m_regRootWnd.Show();
}

void CLogonDlg::OnRegBtnNext()
{
	if (m_reg1Wnd.IsVisible() && m_reg1Wnd.ValidateData()==TRUE)
	{		
		m_reg1Wnd.Show(FALSE);
		m_reg2Wnd.Show();
	}
	else if (m_reg2Wnd.IsVisible() && m_reg2Wnd.ValidateData()==TRUE)
	{
		CSETTING.m_username = m_reg1Wnd.GetUsername();
		CSETTING.m_password = m_reg1Wnd.GetPassword();
		CSETTING.m_retrievepassw = m_reg2Wnd.GetSparePassword();
		CSETTING.Save();

		m_reg2Wnd.Show(FALSE);
		m_homeWnd.SetUsername(CSETTING.m_username);
		m_homeWnd.Show();
		SetItemVisible(1007, FALSE);
	}
}

void CLogonDlg::OnRegBtnCancel()
{
	m_homeWnd.Show();
	m_regRootWnd.Show(FALSE);
}

void CLogonDlg::OnForgetPwNext()
{
	if (m_forget1Wnd.IsVisible() && m_forget1Wnd.ValidateData()==TRUE)
	{
		m_forget1Wnd.Show(FALSE);
		m_forget2Wnd.Show();
	}
	else if (m_forget2Wnd.IsVisible() && m_forget2Wnd.ValidateData()==TRUE)
	{
		m_forget2Wnd.Show(FALSE);
		m_forget3Wnd.Show();
	}
	else if (m_forget3Wnd.IsVisible()  && m_forget3Wnd.ValidateData()==TRUE)
	{
		CSETTING.m_password = m_forget3Wnd.GetNewPassword();
		CSETTING.Save();

		m_forget3Wnd.Show(FALSE);
		m_homeWnd.SetUsername(CSETTING.m_username);
		m_homeWnd.SetPassword(std::wstring(L""));
		m_homeWnd.Show();
	}
}

void CLogonDlg::OnForgetPwCancel()
{
	m_homeWnd.Show();
	m_forgetRootWnd.Show(FALSE);
}
