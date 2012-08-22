#pragma once
#include <atlcoll.h>
#include <wtlhelper/whwindow.h>

#define MB_BK_CUSTOM_BUTTON         0x80000000
#define IDC_LBL_MSGBOX_TITLE2                60020
#define IDC_LBL_MSGBOX_PANEL_MORELINK        60023
#define IDC_LBL_MSGBOX_MORELINK              60021

class CDlgMsgBox
	: public CBkDialogImpl<CDlgMsgBox>
	// , public CWHRoundRectFrameHelper<CDlgMsgBox>
{
public:
	CDlgMsgBox()
		: m_bShowNoNotifyLater(FALSE)
		, m_bNoNotifyLater(FALSE)
		, m_uType(MB_OK)
		, m_isTextXml(FALSE)
	{
	}

	static UINT_PTR Show(
		LPCWSTR lpszText, 
		LPCWSTR lpszCaption     = NULL, 
		UINT uType              = MB_OK, 
		BOOL *pbNoNotifyLater   = NULL, 
		HWND hWndParent         = NULL
		);

	void AddButton(LPCWSTR lpszText, UINT uCmdID, UINT uWidth = 0);

	UINT_PTR ShowMsg(
		LPCWSTR lpszText, 
		LPCWSTR lpszCaption     = NULL, 
		UINT uType              = MB_OK, 
		BOOL *pbNoNotifyLater   = NULL, 
		HWND hWndParent         = NULL
		);

	UINT_PTR ShowPanelMsg(
		LPCWSTR lpszXml, 
		LPCRECT lpRect,				// Required Xml msg RECT 
		LPCWSTR lpszCaption     = NULL, 
		UINT uType              = MB_OK, 
		BOOL *pbNoNotifyLater   = NULL, 
		HWND hWndParent         = NULL
		);

protected:

	BOOL m_isTextXml;	// true:use m_rcXml or use TEXT_CALC(m_strText) 
	RECT m_rcXml;
	CString m_strText;
	CString m_strCaption;

	UINT m_uType;
	BOOL m_bShowNoNotifyLater;
	BOOL m_bNoNotifyLater;

	class __BKMBButton
	{
	public:
		__BKMBButton(LPCWSTR lpszText, UINT uid, UINT width)
			: uCmdID(uid)
			, strText(lpszText)
			, uWidth(width)
		{

		}
		CString strText;
		UINT    uCmdID;
		UINT    uWidth;
	};

	CAtlList<__BKMBButton> m_lstButton;

	void _InitTitle( LPCWSTR lpszCaption );
	void _InitLayout( BOOL * pbNoNotifyLater );
	void _MakeButtons();
	int ParseMsgLine(CString strMsg, CAtlArray<CString>& arrMsg);
	CRect GetTextRect(CString strTxt);
	void OnBkCommand(UINT uItemID, LPCSTR szItemClass);
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
	LRESULT OnDestory();

	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_COMMAND(OnBkCommand)
	BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CDlgMsgBox)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CBkDialogImpl<CDlgMsgBox>)
		// CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CDlgMsgBox>)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DESTROY(OnDestory)
	END_MSG_MAP()
};
