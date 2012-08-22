#include "StdAfx.h"
#include "MainFrame.h"
#include "Format/Tcformat.h"
#include "Mount/MyMount.h"
#include "charset.h"
#include "DlgMsgbox.h"
#include "TinyXML/tinyxml.h"
#include "Tools.h"
#include "Setting.h"

#define MBSIZE 1024*1024


CMainFrame::CMainFrame()
: CBkDialogImpl<CMainFrame>(IDR_BK_MAIN_DIALOG)
{
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::LoadDriveLetters()
{
	wchar_t *szDriveLetters[]=
	{L"A:", L"B:", L"C:", L"D:",
	L"E:", L"F:", L"G:", L"H:", L"I:", L"J:", L"K:",
	L"L:", L"M:", L"N:", L"O:", L"P:", L"Q:", L"R:",
	L"S:", L"T:", L"U:", L"V:", L"W:", L"X:", L"Y:",
	L"Z:"};
	DWORD LastKnownLogicalDrives = GetLogicalDrives ();

	m_combo_driveList.ResetContent();
	for (int i=2; i<26; ++i)
	{
		if (!((LastKnownLogicalDrives >> i) & 1))
		{
			int index = m_combo_driveList.AddString(szDriveLetters[i]);
			m_combo_driveList.SetItemData(index, i);
		}
	}
	m_combo_driveList.SetCurSel(0);
}

void CMainFrame::LoadSafeBox()
{
	std::string strPath;
	GetAppRunDir(strPath);
	strPath += "\\vol.xml";

	TiXmlDocument *myDocument = new TiXmlDocument(strPath.c_str());
	if (!myDocument) return;

	myDocument->LoadFile();

	TiXmlElement *RootElement = myDocument->RootElement();
	if (!RootElement) 
	{ 
		delete myDocument; 
		return; 
	}

	SafeBoxItem box;
	TiXmlElement *elem = RootElement->FirstChildElement();
	while (elem)
	{
		box.drive = /*atoi(elem->Attribute("Drive"))*/ -1;
		box.name = elem->Attribute("Name");
		box.location = elem->Attribute("Location");
		box.size = atoi(elem->Attribute("Size"));
		InsertNewSafebox(box);

		elem = elem->NextSiblingElement();
	}

	delete myDocument;
}

void CMainFrame::SaveSafeBox()
{
	std::string strPath;
	GetAppRunDir(strPath);
	strPath += "\\vol.xml";
	TiXmlDocument *myDocument = new TiXmlDocument(strPath.c_str());
	if (!myDocument) return;

	TiXmlElement *pRootElement = new TiXmlElement("SafeboxList");
	myDocument->LinkEndChild(pRootElement);

	int nCount = m_listview.GetItemCount();
	SafeBoxItem box;
	CString strText;
	char buf[8] = {0};
	for (int i=0; i<nCount; i++)
	{
		box.drive = (int)m_listview.GetItemData(i);
		m_listview.GetItemText(i, 1, strText);
		Charset::UnicodeToAnsi(std::wstring(strText.GetBuffer()), box.name);
		strText.ReleaseBuffer();

		m_listview.GetItemText(i, 2, strText);
		Charset::UnicodeToAnsi(std::wstring(strText.GetBuffer()), box.location);
		strText.ReleaseBuffer();

		m_listview.GetItemText(i, 3, strText);
		box.size = _ttoi(strText.GetBuffer());
		strText.ReleaseBuffer();

		TiXmlElement *pSafeboxElement = new TiXmlElement("Safebox");
		pRootElement->LinkEndChild(pSafeboxElement);
		pSafeboxElement->SetAttribute("Drive", _itoa(box.drive, buf, 10));
		pSafeboxElement->SetAttribute("Name", box.name.c_str());
		pSafeboxElement->SetAttribute("Location", box.location.c_str());
		pSafeboxElement->SetAttribute("Size", _itoa(box.size, buf, 10));
	}

	myDocument->SaveFile();

	delete myDocument;
}

LRESULT CMainFrame::OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/)
{
	m_uDiskMgr.SetObserver(this);

	CreateChildCtrl();

	m_MenuSafebox.LoadMenu(IDR_MENU_SAFEBOX);

	LoadSafeBox();

	OnSafeBoxCancel();

	return TRUE;
}

void CMainFrame::CreateChildCtrl()
{
	m_edit_safeboxName.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL, WS_EX_CLIENTEDGE);
	m_edit_safeboxName.SetDlgCtrlID(1103);
	m_edit_safeboxSize.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_NUMBER, WS_EX_CLIENTEDGE);
	m_edit_safeboxSize.SetDlgCtrlID(1105);
	m_edit_safeboxLocation.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL, WS_EX_CLIENTEDGE);
	m_edit_safeboxLocation.SetDlgCtrlID(1109);
	m_combo_driveList.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST, WS_EX_CLIENTEDGE);
	m_combo_driveList.SetDlgCtrlID(1107);

	m_edit_safeboxDir.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL, WS_EX_CLIENTEDGE);
	m_edit_safeboxDir.SetDlgCtrlID(1203);

	m_listview.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL, WS_EX_CLIENTEDGE);
	m_listview.SetDlgCtrlID(1303);
	DWORD dwStyle = m_listview.GetExtendedListViewStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_listview.SetExtendedListViewStyle(dwStyle); 
	m_listview.InsertColumn( 1, L"盘符", LVCFMT_CENTER, 50 );
	m_listview.InsertColumn( 2, L"保险箱名称", LVCFMT_CENTER, 100 );
	m_listview.InsertColumn( 3, L"实际位置", LVCFMT_LEFT, 326 );
	m_listview.InsertColumn( 4, L"大小(MB)", LVCFMT_CENTER, 80 );

	m_edit_oldPw.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
	m_edit_oldPw.SetDlgCtrlID(4103);
	m_edit_newPw.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
	m_edit_newPw.SetDlgCtrlID(4105);
	m_edit_repeatNewPw.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_PASSWORD, WS_EX_CLIENTEDGE);
	m_edit_repeatNewPw.SetDlgCtrlID(4107);
	m_edit_about.Create(GetViewHWND(), CRect(0,0,0,0), NULL, WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_LEFT|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY, WS_EX_CLIENTEDGE);
	m_edit_about.SetDlgCtrlID(4203);
	m_edit_about.SetWindowText(L"重要声明:\r\n版权归属………………………………………………………………………………………………………………………………………………end");
}

void CMainFrame::OpenSafeUDisk()
{
	if (m_uDiskMgr.m_bRunning)
	{
		return;
	}

	BOOL bRet = m_uDiskMgr.Start(true);
	ATLASSERT(bRet);

	if (!bRet)
		return;		

	SetUDiskStatus(1);
}

void CMainFrame::CloseSafeUDisk()
{
	if (m_uDiskMgr.m_bRunning)
	{
		return;
	}

	BOOL bRet = m_uDiskMgr.Start(false);
	ATLASSERT(bRet);

	if (!bRet)
		return;		

	SetUDiskStatus(1);
}

void CMainFrame::OnUDiskStatus(CUDiskMgr *pperf, DWORD dwStatus)
{
	PostMessage(UMSG_UDISK_STATUS, dwStatus, 0);
}

LRESULT CMainFrame::OnUDiskStatus(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case UDISK_BEGIN:
		SetUDiskStatus(1);
		break;
	case UDISK_BEGIN_OPEN_SAFE_UDISK:
		{
			SetItemText(2201, _T("正在开启安全U盘……"));
		}
		break;
	case UDISK_BEGIN_CLOSE_SAFE_UDISK:
		{
			SetItemText(2201, _T("正在关闭安全U盘……"));
		}
		break;
	case UDISK_END:
		{
			SetUDiskStatus(2);
		}
		break;
	default:
		ATLASSERT(FALSE);
	}

	return 0;
}

void CMainFrame::OnTabModifyPw()
{
	SetItemVisible(4101, TRUE);
	SetItemVisible(4201, FALSE);
	EnableItem(4001, false);
	EnableItem(4002, true);
}

void CMainFrame::OnTabAbout()
{	
	SetItemVisible(4101, FALSE);
	SetItemVisible(4201, TRUE);
	EnableItem(4001, true);
	EnableItem(4002, false);
}

void CMainFrame::OnBnSetPasswOK()
{
	std::wstring oldpassw = GetItemTextW(m_edit_oldPw.m_hWnd);
	if (oldpassw != CSETTING.m_password)
	{
		CDlgMsgBox::Show(L"原密码不正确，请输入正确的原密码", L"修改密码");
		return;
	}

	std::wstring newpassw = GetItemTextW(m_edit_newPw.m_hWnd);
	std::wstring repeatpassw = GetItemTextW(m_edit_repeatNewPw.m_hWnd);
	if (newpassw.length() < 6)
	{
		CDlgMsgBox::Show(L"新密码不能小于6位，请重新输入。", L"修改密码");
		return;
	}
	else if (newpassw != repeatpassw)
	{
		CDlgMsgBox::Show(L"新密码不匹配，请重新输入。", L"修改密码");
		m_edit_newPw.SetWindowTextW(L"");
		m_edit_repeatNewPw.SetWindowTextW(L"");
		return;
	}

	CSETTING.m_password = newpassw;
	CSETTING.Save();
	CDlgMsgBox::Show(L"修改新密码成功，请牢记您的新密码。", L"修改密码");
	OnBnSetPasswCancel();
}

void CMainFrame::OnBnSetPasswCancel()
{
	m_edit_oldPw.SetWindowTextW(L"");
	m_edit_newPw.SetWindowTextW(L"");
	m_edit_repeatNewPw.SetWindowTextW(L"");
}

void CMainFrame::OnSysCommand(UINT nID, CPoint point)
{
	SetMsgHandled(FALSE);

	switch (nID & 0xFFF0)
	{
	case SC_CLOSE:
		SetMsgHandled(TRUE);
		EndDialog(IDCANCEL);
		break;
	}
}

BOOL CMainFrame::OnTabSelChange( int nTabItemIDOld, int nTabItemIDNew )
{
	if (nTabItemIDNew==2)
	{
	}
	else if (nTabItemIDNew==3)
	{
	}
	return TRUE;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==TIMER_ID_UPDATEUDISKSTATUS)
	{
		++ m_dwIconIndex;
		m_dwIconIndex %= 8;
		SetItemIntAttribute(2202, "sub", m_dwIconIndex);
	}
}

void CMainFrame::OnBkBtnClose()
{
	SaveSafeBox();
	UnMountAll();
	EndDialog(IDCANCEL);
}

void CMainFrame::OnBkBtnMax()
{
	if (WS_MAXIMIZE == (GetStyle() & WS_MAXIMIZE))
		SendMessage(WM_SYSCOMMAND, SC_RESTORE | HTCAPTION, 0);
	else
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE | HTCAPTION, 0);
}

void CMainFrame::OnBkBtnMin()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE | HTCAPTION, 0);
}

void CMainFrame::OnTabCreateSafeBox()
{
	SetItemVisible(1101, TRUE);
	SetItemVisible(1201, FALSE);
	SetRichText(1000, L"<c color='0061ac'>创建保险箱</c>");
	CStringA strAttr = "skin";
	CStringA strValue = "btn_manual";
	EnableItem(1001, false);
	EnableItem(1002, true);

	LoadDriveLetters();
}

void CMainFrame::OnTabImportSafeBox()
{
	SetItemVisible(1101, FALSE);
	SetItemVisible(1201, TRUE);	
	SetRichText(1000, L"<c color='0061ac'>加载保险箱</c>");
	EnableItem(1001, true);
	EnableItem(1002, false);
}

void CMainFrame::OnSafeBoxLocation()
{
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.cfg)|*.cfg|All Files (*.*)|*.*||"), NULL);
	if (dlgFile.DoModal() == IDOK)
	{
		m_edit_safeboxLocation.SetWindowText(dlgFile.m_szFileName);
	}
}

void CMainFrame::OnSafeBoxNext()
{
	BOOL bRet = -1;
	if (IsItemVisible(1101))
	{
		// 创建新保险箱
		bRet = CreateNewSafeBox();
	}
	else if (IsItemVisible(1201))
	{
		// 加载保险箱
		bRet = ImportSafeBox();
	}

	if (bRet == TRUE)
	{
		SetItemVisible(10001, FALSE);
		SetItemVisible(10002, TRUE);
	}
}

void CMainFrame::OnSafeBoxCancel()
{
	SetItemVisible(10001, FALSE);
	SetItemVisible(10002, TRUE);	
}

void CMainFrame::OnGoCreateSafeBox()
{
	SetItemVisible(10001, TRUE);
	SetItemVisible(10002, FALSE);
	OnTabCreateSafeBox();
}

void CMainFrame::OnGoImportSafeBox()
{
	SetItemVisible(10001, TRUE);
	SetItemVisible(10002, FALSE);
	OnTabImportSafeBox();
}

void CMainFrame::OnSafeBoxSelectFile()
{
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.cfg)|*.cfg|All Files (*.*)|*.*||"), NULL);
	if (dlgFile.DoModal() == IDOK)
	{
		m_edit_safeboxDir.SetWindowText(dlgFile.m_szFileName);
	}
}

BOOL CMainFrame::CreateNewSafeBox()
{
	CString strName(_T(""));
	m_edit_safeboxName.GetWindowText(strName);
	if (strName.IsEmpty())
	{
		CDlgMsgBox::Show(L"保险箱名称不能为空，请输入保险箱名称。", L"创建保险箱");
		return FALSE;
	}

	CString strSize;
	m_edit_safeboxSize.GetWindowText(strSize);
	if (strSize.IsEmpty())
	{
		CDlgMsgBox::Show(L"保险箱容量不能为空，请输入保险箱容量。", L"创建保险箱");
		return FALSE;
	}
	int size = _ttoi(strSize);

	CString strLocation;
	m_edit_safeboxLocation.GetWindowText(strLocation);
	if (strLocation.IsEmpty())
	{
		CDlgMsgBox::Show(L"保险箱位置不能为空，请选择保险箱位置。", L"创建保险箱");
		return FALSE;
	}

	if (CDlgMsgBox::Show(L"软件将格式化您的目录\r\n"+strLocation+L"\r\n请按确定以继续", L"") != IDOK) return FALSE;

	string sLocation;
	wstring wsLocation(strLocation.GetBuffer());
	strLocation.ReleaseBuffer();
	Charset::UnicodeToAnsi(wsLocation, sLocation);
	if (myVolTransform(sLocation.c_str(), MBSIZE*size, NULL))
	{
		int drive = (int)m_combo_driveList.GetItemData(m_combo_driveList.GetCurSel());
		BOOL status = Mount(NULL, drive, (LPSTR)sLocation.c_str());
		switch (status)
		{
		case ERR_SUCCESS:
			{
				CString strDrive;
				strDrive.Format(L"%c:", 'A'+drive);
				int nRow = m_listview.InsertItem(0, strDrive);
				m_listview.SetItemText(nRow, 1, strName);
				m_listview.SetItemText(nRow, 2, strLocation);
				m_listview.SetItemText(nRow, 3, strSize);
				m_listview.SetItemData(nRow, drive);
			}
			break;
		case ERR_VOL_ALREADY_MOUNTED:
			{
				CDlgMsgBox::Show(L"此文件已经挂载。", L"挂载保险箱");
				return FALSE;
			}
		default:
			CDlgMsgBox::Show(L"挂载保险箱失败，请检查文件路径是否正确，再重试。", L"挂载保险箱");
			return FALSE;
		}
	}
	else
	{
		CDlgMsgBox::Show(L"创建保险箱失败，请检查文件路径是否正确，再重试。", L"创建保险箱");
		return FALSE;
	}

	return TRUE;
}

BOOL CMainFrame::ImportSafeBox()
{
	CString strDir;
	m_edit_safeboxDir.GetWindowText(strDir);
	if (strDir.IsEmpty())
	{
		CDlgMsgBox::Show(L"保险箱路径不能为空，请选择保险箱位置。", L"加载保险箱");
		return FALSE;
	}
	LoadDriveLetters();
	int drive = (int)m_combo_driveList.GetItemData(m_combo_driveList.GetCurSel());
	string sLocation;
	wstring wsLocation(strDir.GetBuffer());
	strDir.ReleaseBuffer();
	Charset::UnicodeToAnsi(wsLocation, sLocation);
	BOOL status = Mount(NULL, drive, (LPSTR)sLocation.c_str());
	switch (status)
	{
	case ERR_SUCCESS:
		{
			CString strDrive;
			strDrive.Format(L"%c:", 'A'+drive);
			int nRow = m_listview.InsertItem(0, strDrive);
			//m_listview.SetItemText(nRow, 1, L"");
			m_listview.SetItemText(nRow, 2, strDir);
			//m_listview.SetItemText(nRow, 3, strSize);
			m_listview.SetItemData(nRow, drive);
		}
		break;
	case ERR_VOL_ALREADY_MOUNTED:
		{
			CDlgMsgBox::Show(L"此文件已经挂载。", L"挂载保险箱");
			return FALSE;
		}
	default:
		CDlgMsgBox::Show(L"挂载保险箱失败，请检查文件路径是否正确，再重试。", L"挂载保险箱");
		return FALSE;
	}

	return TRUE;
}

void CMainFrame::SetUDiskStatus( INT nStatus ) 
{
	switch(nStatus)
	{
	case 0: // begin 
		{
			SetItemVisible(2100, TRUE);	// begin 
			SetItemVisible(2200, FALSE);	// running 
			SetItemVisible(2300, FALSE);
			KillTimer(TIMER_ID_UPDATEUDISKSTATUS);
		}
		break;
	case 1: // running 
		{
			SetItemVisible(2100, FALSE);
			SetItemVisible(2200, TRUE);
			SetItemVisible(2300, FALSE);
			SetTimer(TIMER_ID_UPDATEUDISKSTATUS, 500);
			m_dwIconIndex = 0;
		}
		break;
	case 2:	// result 
		{
			bool bSuccess = m_uDiskMgr.GetResult();
			bool bIsOpened = m_uDiskMgr.IsUDiskOpened();

			if (bSuccess && bIsOpened)  //成功打开
			{
				SetItemVisible(2100, FALSE);
				SetItemVisible(2200, FALSE);
				SetItemVisible(2300, TRUE);	
				SetRichText(2301, _T("为了您的数据安全，使用完后，请及时关闭安全U盘"));
				SetItemText(2302, _T("关闭安全U盘"));
			}
			else if (bSuccess && !bIsOpened) //成功关闭
			{
				SetItemVisible(2100, TRUE);
				SetItemVisible(2200, FALSE);
				SetItemVisible(2300, FALSE);	
				SetRichText(2101, _T("为了您的数据安全，请开启安全U盘！"));
				SetItemText(2102, _T("开启安全U盘"));
			}
			else if (!bSuccess && bIsOpened) //关闭失败
			{
				SetItemVisible(2100, FALSE);
				SetItemVisible(2200, FALSE);
				SetItemVisible(2300, TRUE);	
				SetRichText(2301, _T("关闭安全U盘失败！"));
				SetItemText(2302, _T("重试"));
			}
			else if (!bSuccess && !bIsOpened) // 打开失败
			{
				SetItemVisible(2100, TRUE);
				SetItemVisible(2200, FALSE);
				SetItemVisible(2300, FALSE);	
				SetRichText(2101, _T("打开安全U盘失败！"));
				SetItemText(2102, _T("重试"));
			}
			else
			{
				ATLASSERT(true);
			}
			KillTimer(TIMER_ID_UPDATEUDISKSTATUS);
		}
		break;
	}
}

LRESULT CMainFrame::OnNMRclickList(LPNMHDR pnmh)
{
	HMENU hsubmenu = m_MenuSafebox.GetSubMenu(0).m_hMenu;
	CPoint l_Point;
	::GetCursorPos(&l_Point);
	::TrackPopupMenu(hsubmenu, TPM_LEFTALIGN , l_Point.x, l_Point.y, 0, GetViewHWND(), NULL);

	return 0;
}

void CMainFrame::OnSafeBoxOpen()
{
	int nRow = m_listview.GetSelectionMark();

	CString strPath;
	m_listview.GetItemText(nRow, 2, strPath);
	if (strPath.IsEmpty())
	{
		// open failed
		return;
	}
	LoadDriveLetters();
	int drive = (int)m_combo_driveList.GetItemData(m_combo_driveList.GetCurSel());
	CString strDrive;
	strDrive.Format(L"%c:", 'A'+drive);
	string sLocation;
	wstring wsLocation(strPath.GetBuffer());
	strPath.ReleaseBuffer();
	Charset::UnicodeToAnsi(wsLocation, sLocation);
	BOOL status = Mount(NULL, drive, (LPSTR)sLocation.c_str());
	switch (status)
	{
	case ERR_SUCCESS:
		{
			CString strDrive;
			strDrive.Format(L"%c:", 'A'+drive);
			m_listview.SetItemText(nRow, 0, strDrive);
			m_listview.SetItemData(nRow, drive);
		}
		break;
	case ERR_VOL_ALREADY_MOUNTED:
		{
			CDlgMsgBox::Show(L"此文件已经挂载。", L"挂载保险箱");
			return;
		}
	default:
		CDlgMsgBox::Show(L"挂载保险箱失败，请检查文件路径是否正确，再重试。", L"挂载保险箱");
		return;
	}
	strPath.ReleaseBuffer();
}

void CMainFrame::OnSafeBoxClose()
{
	int nRow = m_listview.GetSelectionMark();
	if (nRow == -1) return;

	int drive = (int)m_listview.GetItemData(nRow);
	if (drive == -1) return;
	if (Dismount(NULL, drive))
	{
		m_listview.SetItemText(nRow, 0, L"未开启");
		m_listview.SetItemData(nRow, -1);
	}
}

void CMainFrame::OnSafeBoxDelete()
{
	int nRow = m_listview.GetSelectionMark();
	if (nRow == -1) return;

	int drive = (int)m_listview.GetItemData(nRow);
	if (drive==-1 || Dismount(NULL, drive))
	{
		CString strPath;
		m_listview.GetItemText(nRow, 2, strPath);
		DeleteFile(strPath);
		m_listview.DeleteItem(nRow);
	}
	else
	{
		CDlgMsgBox::Show(L"删除保险箱失败，请重试。", L"删除保险箱");
	}
}

void CMainFrame::OnCommandRangeHandlerEX(UINT uNotifyCode, int nID, HWND wndCtl)
{
	switch (nID)
	{
	case ID_SAFEOBXMENU_OPEN:
		OnSafeBoxOpen();
		break;
	case ID_SAFEOBXMENU_CLOSE:
		OnSafeBoxClose();
		break;
	case ID_SAFEOBXMENU_DELETE:
		OnSafeBoxDelete();
		break;
	}
}


bool CMainFrame::InsertNewSafebox(const SafeBoxItem& box)
{
	CString strText;
	if (box.drive == -1)
	{
		strText = L"未开启";
	}
	else
	{
		strText.Format(L"%c", 'A'+box.drive);
	}
	int nRow = m_listview.InsertItem(0, strText);
	m_listview.SetItemText(nRow, 1, Charset::s2ws(box.name).c_str());
	m_listview.SetItemText(nRow, 2, Charset::s2ws(box.location).c_str());
	strText.Format(L"%d", box.size);
	m_listview.SetItemText(nRow, 3, strText);
	m_listview.SetItemData(nRow, box.drive);
	return true;
}

void CMainFrame::UnMountAll()
{
	int nCount = m_listview.GetItemCount();
	CString strText;
	for (int i=0; i<nCount; i++)
	{
		int drive = (int)m_listview.GetItemData(i);
		if (drive != -1)
		{
			Dismount(NULL, drive);
		}
	}
}
