#include "stdafx.h"
#include "DlgMsgbox.h"

UINT_PTR CDlgMsgBox::Show(
    LPCWSTR lpszText, 
    LPCWSTR lpszCaption     /*= NULL*/, 
    UINT uType              /*= MB_OK*/, 
    BOOL *pbNoNotifyLater   /*= NULL*/, 
    HWND hWndParent         /*= ::GetActiveWindow()*/
	)
{
    CDlgMsgBox msgbox;
    return msgbox.ShowMsg(lpszText, lpszCaption, uType, pbNoNotifyLater, hWndParent);
}

void CDlgMsgBox::AddButton(LPCWSTR lpszText, UINT uCmdID, UINT uWidth /*= 0*/)
{
    if (0 == uWidth)
    {
        CString strText = lpszText;
        CWindowDC dc(::GetDesktopWindow());
        CRect rcText(0, 0, 1000, 1000);

        const BkStyle& btnStyle = BkStyle::GetStyle("smallbtn");

        HFONT hftOld = dc.SelectFont(btnStyle.m_ftText);

        dc.DrawText(strText, strText.GetLength(), rcText, btnStyle.m_nTextAlign | DT_CALCRECT);

        rcText.InflateRect(btnStyle.m_nMarginX, btnStyle.m_nMarginY);

        dc.SelectFont(hftOld);

        uWidth = max(80, rcText.Width());
    }

    m_lstButton.AddTail(__BKMBButton(lpszText, uCmdID, uWidth));
}

UINT_PTR CDlgMsgBox::ShowMsg(
									 LPCWSTR lpszText, 
									 LPCWSTR lpszCaption     /*= NULL*/, 
									 UINT uType              /*= MB_OK*/, 
									 BOOL *pbNoNotifyLater   /*= NULL*/, 
									 HWND hWndParent         /*= ::GetActiveWindow()*/
									 )
{
	CString strMsg = lpszText, strXml(L""), strXmlPanel(L"");
	CAtlArray<CString> arrMsgLine;
	if ( 0 == ParseMsgLine(strMsg, arrMsgLine))
		return -1;

	const INT LINE_HEIGHT = 25;

	int nWidth = 0, 
		nLineCount = arrMsgLine.GetCount(), 
		nHeight =  nLineCount* LINE_HEIGHT,
		nTop = 0;
	CRect rcText;

	for (int i = 0; i < nLineCount; i++)
	{
		if (1 == nLineCount)
			nTop = 10;
		else
			nTop = i*LINE_HEIGHT;
		strXml.Format(L"<text pos=\"0,%d\">%s</text>", nTop, arrMsgLine[i]);
		strXmlPanel += strXml;
		rcText = GetTextRect(arrMsgLine[i]);
		if (nWidth < rcText.Width())
			nWidth = rcText.Width();
	}
	CRect rc(0, 0, nWidth+10, nHeight);

	return ShowPanelMsg(strXmlPanel, &rc, lpszCaption, uType, pbNoNotifyLater, hWndParent);
}

UINT_PTR CDlgMsgBox::ShowPanelMsg( 
	LPCWSTR lpszXml, 
	LPCRECT lpRect, 
	LPCWSTR lpszCaption /*= NULL*/, 
	UINT uType /*= MB_OK*/, 
	BOOL *pbNoNotifyLater /*= NULL*/, 
	HWND hWndParent /*= NULL */ 
	)
{
	ATLASSERT(lpRect);
	if (!lpRect || !Load(IDR_BK_MESSAGEBOX))
		return -1;
	
	m_isTextXml = TRUE;
	m_rcXml = *lpRect;
	m_uType = uType;
	SetItemVisible(60016, TRUE);
	SetItemVisible(IDC_LBL_MSGBOX_TEXT, FALSE);
	SetPanelXml(60016, CT2CA(lpszXml, CP_UTF8));
	_InitTitle(lpszCaption);
	_InitLayout(pbNoNotifyLater);

	UINT_PTR nRet = DoModal(hWndParent);
	if (pbNoNotifyLater)
		*pbNoNotifyLater = m_bNoNotifyLater;

	return nRet;
}

void CDlgMsgBox::_InitTitle( LPCWSTR lpszCaption )
{
	if (lpszCaption)
	{
		m_strCaption    = lpszCaption;
		SetItemText(IDC_LBL_MSGBOX_TITLE2, m_strCaption);
	}
}

void CDlgMsgBox::_InitLayout( BOOL * pbNoNotifyLater )
{
	CString strButtonXmlFormat, strButtons, strButtonDiv;

	_MakeButtons();

	strButtonXmlFormat = BkString::Get(28);

#   define BUTTON_SPACING 20
	UINT uWidth = 0, uLeft = 0;
	POSITION pos = m_lstButton.GetHeadPosition();


	while (pos)
	{
		const __BKMBButton &btn = m_lstButton.GetNext(pos);

		uWidth += btn.uWidth;
		if (pos)
			uWidth += BUTTON_SPACING;
	}

	pos = m_lstButton.GetHeadPosition();

	while (pos)
	{
		const __BKMBButton &btn = m_lstButton.GetNext(pos);

		strButtons.AppendFormat(strButtonXmlFormat, btn.uCmdID, uLeft, uLeft + btn.uWidth, btn.strText);

		uLeft += btn.uWidth + BUTTON_SPACING;
	}

	strButtonDiv.Format(BkString::Get(29), uWidth / 2, uWidth / 2, strButtons);
	SetPanelXml(IDC_DIV_MSGBOX_BUTTONS, CT2A(strButtonDiv, CP_UTF8));

	DWORD dwIconID = 0;

	if (0 != (MB_ICONMASK & m_uType))
	{
		switch (MB_ICONMASK & m_uType)
		{
		case MB_ICONHAND:
			// dwIconID = (DWORD)(DWORD_PTR)IDI_HAND;
			dwIconID = 0;
			break;
		case MB_ICONQUESTION:
			// dwIconID = (DWORD)(DWORD_PTR)IDI_QUESTION;
			dwIconID = 1;
			break;
		case MB_ICONEXCLAMATION:
			// dwIconID = (DWORD)(DWORD_PTR)IDI_EXCLAMATION;
			dwIconID = 2;
			break;
		case MB_ICONASTERISK:
			// dwIconID = (DWORD)(DWORD_PTR)IDI_ASTERISK;
			dwIconID = 3;
			break;
		default:
            SetItemDWordAttribute(IDC_ICON_MSGBOX_ICON, "src", dwIconID);
            SetItemDWordAttribute(IDC_ICON_MSGBOX_ICON, "oem", 0);
		}		
	}

	SetItemDWordAttribute(IDC_ICON_MSGBOX_ICON, "sub", dwIconID);
	
	if (NULL == pbNoNotifyLater)
		SetItemVisible(IDC_CHK_MSGBOX_NONOTIFYLATER, FALSE);
	else
	{
		m_bShowNoNotifyLater = TRUE;
	}
}

void CDlgMsgBox::_MakeButtons()
{
    if ((MB_BK_CUSTOM_BUTTON & m_uType) == MB_BK_CUSTOM_BUTTON)
        return;

    m_lstButton.RemoveAll();

    switch (MB_TYPEMASK & m_uType)
    {
    case MB_OK:
        AddButton(BkString::Get(30), IDOK);
        break;
    case MB_OKCANCEL:
        AddButton(BkString::Get(30), IDOK);
        AddButton(BkString::Get(31), IDCANCEL);
        break;
    case MB_ABORTRETRYIGNORE:
        AddButton(BkString::Get(32), IDABORT);
        AddButton(BkString::Get(33), IDRETRY);
        AddButton(BkString::Get(34), IDIGNORE);
        break;
    case MB_YESNOCANCEL:
        AddButton(BkString::Get(35), IDYES);
        AddButton(BkString::Get(36), IDNO);
        AddButton(BkString::Get(31), IDCANCEL);
        break;
    case MB_YESNO:
        AddButton(BkString::Get(35), IDYES);
        AddButton(BkString::Get(36), IDNO);
        break;
    case MB_RETRYCANCEL:
        AddButton(BkString::Get(33), IDRETRY);
        AddButton(BkString::Get(31), IDCANCEL);
        break;
#   if(WINVER >= 0x0500)
    case MB_CANCELTRYCONTINUE:
        AddButton(BkString::Get(31), IDCANCEL);
        AddButton(BkString::Get(33), IDRETRY);
        AddButton(BkString::Get(37), IDCONTINUE);
        break;
#   endif /* WINVER >= 0x0500 */
    }
}

void CDlgMsgBox::OnBkCommand(UINT uItemID, LPCSTR szItemClass)
{
    if (strcmp(CBkButton::GetClassName(), szItemClass) != 0 && strcmp(CBkImageBtnWnd::GetClassName(), szItemClass) != 0)
    {
        if (uItemID == IDC_CHK_MSGBOX_NONOTIFYLATER)
            m_bNoNotifyLater = GetItemCheck(IDC_CHK_MSGBOX_NONOTIFYLATER);
        return;
    }

    EndDialog(uItemID);
}

LRESULT CDlgMsgBox::OnInitDialog(HWND hWnd, LPARAM lParam)
{
    CWindowDC dc(m_hWnd);
    CRect rcClient, rcCaption, rcText;
	
    HMONITOR hMonitor = ::MonitorFromWindow(GetParent(), MONITOR_DEFAULTTONULL/* MONITOR_DEFAULTTONEAREST*/);

    if (hMonitor)
    {
        MONITORINFO mi = {sizeof(MONITORINFO)};
        ::GetMonitorInfo(hMonitor, &mi);

        rcClient = mi.rcWork;
    }
    else
        GetClientRect(rcClient);


	const BkStyle& titleStyle = BkStyle::GetStyle("dlgtitle");
	HFONT hftOld = dc.SelectFont(titleStyle.m_ftText);

	rcCaption = rcClient;
	rcCaption.MoveToXY(0, 0);
	dc.DrawText(m_strCaption, m_strCaption.GetLength(), rcCaption, DT_CALCRECT);
	rcCaption.right += 100;
	
	if(m_isTextXml)
	{
		rcText = m_rcXml;
	}
	else
	{
		rcText = rcClient;
		rcText.MoveToXY(0, 0);

		const BkStyle& textStyle = BkStyle::GetStyle("msgtext");

		dc.SelectFont(textStyle.m_ftText);

		dc.DrawText(m_strText, m_strText.GetLength(), rcText, textStyle.m_nTextAlign | DT_CALCRECT);
	}
	rcText.right += 45;
	rcText.bottom += 150;

    if (m_bShowNoNotifyLater)
        rcText.bottom += 20;

    dc.SelectFont(hftOld);

	rcClient.right = rcClient.left + max(max(rcCaption.right, rcText.right), 380);
    rcClient.bottom = rcClient.top + max(rcText.bottom, 215);

    MoveWindow(rcClient, FALSE);

    return TRUE;
}

LRESULT CDlgMsgBox::OnDestory()
{
	SetMsgHandled(FALSE);
	return TRUE;
}

int CDlgMsgBox::ParseMsgLine(CString strMsg, CAtlArray<CString>& arrMsg)
{
	int nRet = -1;
	if (TRUE == strMsg.IsEmpty())
		return nRet;
	arrMsg.RemoveAll();

	int nIndex = -1;
	strMsg += L"\n";
	CString strTmp(L""), msg = strMsg;;
	nIndex = msg.Find(L"\n");

	while (-1 != nIndex)
	{
		strTmp = msg.Left(nIndex);
		if (strTmp.GetLength())
			arrMsg.Add(strTmp);
		msg = msg.Mid(nIndex+1);

		nIndex = msg.Find(L"\n");
	} 

	return arrMsg.GetCount();
}

CRect CDlgMsgBox::GetTextRect(CString strTxt)
{
	//CRect rc(0,0,0,0);
	CWindowDC dc(::GetDesktopWindow());
	CRect rcText(0, 0, 1000, 1000);

	const BkStyle& textStyle = BkStyle::GetStyle("msgtext");

	dc.SelectFont(textStyle.m_ftText);

	dc.DrawText(strTxt, strTxt.GetLength(), rcText, textStyle.m_nTextAlign | DT_CALCRECT);

	return rcText;
}
