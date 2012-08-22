#pragma once
#include "resource.h"
#include "wtlhelper\whwindow.h"
#include "SafeUDiskMgr.h"
#include <atlutil.h>
#include <string>

enum 
{
	UMSG_UDISK_STATUS = WM_USER + 1,
};

enum 
{
	TIMER_ID_UPDATEUDISKSTATUS = 1, 
};

struct SafeBoxItem
{
	int id;				// 保险箱id
	int drive;			// 磁盘盘符
	std::string name;	// 保险箱名称
	std::string location;	// 保险箱位置
	int size;			//保险箱大小(MB)
};


class CMainFrame
	: public CBkDialogImpl<CMainFrame>
	, public CWHRoundRectFrameHelper<CMainFrame>
	, public IUDiskObserver
{
	typedef CBkDialogImpl<CMainFrame> __base_class ;

public:
	CMainFrame();
	~CMainFrame();

public:
	LRESULT OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/);

	void OnBkBtnClose();

	void OnBkBtnMax();

	void OnBkBtnMin();
	
	void OpenSafeUDisk();

	void CloseSafeUDisk();

	void SetUDiskStatus( INT nStatus );

	void OnTabModifyPw();

	void OnTabAbout();

	void OnBnSetPasswOK();
	
	void OnBnSetPasswCancel();

	virtual void OnUDiskStatus(CUDiskMgr *pperf, DWORD dwStatus);

	LRESULT OnUDiskStatus(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void OnSysCommand(UINT nID, CPoint point);

	BOOL OnTabSelChange( int nTabItemIDOld, int nTabItemIDNew );

	void OnTimer(UINT_PTR nIDEvent);

	void OnTabCreateSafeBox();

	void OnTabImportSafeBox();

	void OnSafeBoxLocation();

	void OnSafeBoxNext();

	void OnSafeBoxCancel();

	void OnGoCreateSafeBox();

	void OnGoImportSafeBox();

	void OnSafeBoxSelectFile();

	LRESULT OnNMRclickList(LPNMHDR pnmh);

	void OnSafeBoxOpen();
	void OnSafeBoxClose();
	void OnSafeBoxDelete();

	void OnCommandRangeHandlerEX(UINT uNotifyCode, int nID, HWND wndCtl);

protected:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_CLOSE, CMainFrame::OnBkBtnClose)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_MAX, CMainFrame::OnBkBtnMax)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_MIN, CMainFrame::OnBkBtnMin)
		// tab SafeBox
		BK_NOTIFY_ID_COMMAND(1001, CMainFrame::OnTabCreateSafeBox)
		BK_NOTIFY_ID_COMMAND(1002, CMainFrame::OnTabImportSafeBox)
		BK_NOTIFY_ID_COMMAND(1110, CMainFrame::OnSafeBoxLocation)
		BK_NOTIFY_ID_COMMAND(1003, CMainFrame::OnSafeBoxNext)
		BK_NOTIFY_ID_COMMAND(1004, CMainFrame::OnSafeBoxCancel)
		BK_NOTIFY_ID_COMMAND(1301, CMainFrame::OnGoCreateSafeBox)
		BK_NOTIFY_ID_COMMAND(1302, CMainFrame::OnGoImportSafeBox)
		BK_NOTIFY_ID_COMMAND(1204, CMainFrame::OnSafeBoxSelectFile)
		// tab SafeUDisk
		BK_NOTIFY_ID_COMMAND(2102, CMainFrame::OpenSafeUDisk)
		BK_NOTIFY_ID_COMMAND(2302, CMainFrame::CloseSafeUDisk)
		// tab Cleaner
		// tab Setting
		BK_NOTIFY_ID_COMMAND(4001, CMainFrame::OnTabModifyPw)
		BK_NOTIFY_ID_COMMAND(4002, CMainFrame::OnTabAbout)
		BK_NOTIFY_ID_COMMAND(4003, CMainFrame::OnBnSetPasswOK)
		BK_NOTIFY_ID_COMMAND(4004, CMainFrame::OnBnSetPasswCancel)
		BK_NOTIFY_TAB_SELCHANGE(10000, CMainFrame::OnTabSelChange)
		BK_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CMainFrame)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP( __base_class )
		CHAIN_MSG_MAP( CWHRoundRectFrameHelper<CMainFrame> )
		MSG_WM_INITDIALOG(CMainFrame::OnInitDialog)
		MSG_WM_TIMER(CMainFrame::OnTimer)
		MSG_WM_SYSCOMMAND(CMainFrame::OnSysCommand)
		MESSAGE_HANDLER_EX(UMSG_UDISK_STATUS, CMainFrame::OnUDiskStatus)
		NOTIFY_HANDLER_EX(1303, NM_RCLICK, CMainFrame::OnNMRclickList)
		COMMAND_RANGE_HANDLER_EX(ID_SAFEOBXMENU_OPEN, ID_SAFEOBXMENU_OPEN+2, CMainFrame::OnCommandRangeHandlerEX)
		END_MSG_MAP()

protected:
	CUDiskMgr				m_uDiskMgr;
	DWORD					m_dwIconIndex;

public:
	enum Trash{
		Trash_All = 0,
		Trash_Internet,
		Trash_Document,
		Trash_Office,
		Trash_Video,
		Trash_Applation,
		Trash_Others,
	};

	int ScanTrash(Trash trash);

	bool ClearTrash(Trash trash);

	void LoadDriveLetters();

public:
	void CreateChildCtrl();

	BOOL CreateNewSafeBox();
	BOOL ImportSafeBox();

	void LoadSafeBox();
	void SaveSafeBox();

	bool InsertNewSafebox(const SafeBoxItem& box);

	void UnMountAll();

public:
	// UI Control
	// 创建保险箱 begin
	CEdit m_edit_safeboxName;
	CEdit m_edit_safeboxSize;
	CEdit m_edit_safeboxLocation;
	CComboBox m_combo_driveList;
	// 创建保险箱 end

	// 加载保险箱 begin
	CEdit m_edit_safeboxDir;
	// 加载保险箱 end

	// 保险箱首页 begin
	CListViewCtrl m_listview;
	CMenu m_MenuSafebox;
	// 保险箱首页 end

	// 设置
	CEdit m_edit_oldPw;
	CEdit m_edit_newPw;
	CEdit m_edit_repeatNewPw;
	CEdit m_edit_about;
};