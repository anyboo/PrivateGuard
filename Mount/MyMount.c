#include <windowsx.h>

#include "Dlgcode.h"
#include "../Common/Common.h"
#include "MyMount.h"


BOOL Mount (HWND hwndDlg, int nDosDriveNo, char *szFileName)
{
	BOOL status = ERR_VOL_MOUNT_FAILED;
	int mounted = 0;
	MountOptions mountOptions;
	Password VolumePassword;

	memset(&mountOptions, 0, sizeof(MountOptions));
	mountOptions.PreserveTimestamp = 1;

	memset(&VolumePassword, 0, sizeof(Password));
	VolumePassword.Length = 10;
	memcpy(VolumePassword.Text, "1234567890", 10);

	status = DriverAttach ();
	if (status != 0)
	{
		if (status == ERR_OS_ERROR)
			handleWin32Error (NULL);
		else
			handleError (NULL, status);

		AbortProcess ("NODRIVER");
	}

	if (nDosDriveNo == 0)
	{
		status = ERR_VOL_MOUNT_FAILED;
		goto ret;
	}

	if (szFileName == NULL)
	{
		status = ERR_VOL_MOUNT_FAILED;
		goto ret;
	}

	if (strlen(szFileName) == 0)
	{
		status = ERR_VOL_MOUNT_FAILED;
		goto ret;
	}

	if (IsMountedVolume (szFileName))
	{
		//Warning ("VOL_ALREADY_MOUNTED");
		status = ERR_VOL_ALREADY_MOUNTED;
		goto ret;
	}

	if (!VolumePathExists (szFileName))
	{
		status = ERR_VOL_MOUNT_FAILED;
		goto ret;
	}

	mounted = MountVolume (hwndDlg, nDosDriveNo, szFileName, &VolumePassword, 0, 0, &mountOptions, TRUE, TRUE);

	if (mounted > 0)
	{
		status = ERR_SUCCESS;
	}

ret:
	if (!MultipleMountOperationInProgress)
		burn (&VolumePassword, sizeof (VolumePassword));

	burn (&mountOptions.ProtectedHidVolPassword, sizeof (mountOptions.ProtectedHidVolPassword));

	RestoreDefaultKeyFilesParam ();

	return status;
}


BOOL Dismount (HWND hwndDlg, int nDosDriveNo)
{
	BOOL status = FALSE;

	if (nDosDriveNo == 0)
		return FALSE;

	if (UnmountVolume (hwndDlg, nDosDriveNo, 0))
	{
		status = TRUE;
	}

	return status;
}

BOOL DismountAll (HWND hwndDlg, BOOL forceUnmount, BOOL interact, int dismountMaxRetries, int dismountAutoRetryDelay)
{
//	BOOL status = TRUE;
//	MOUNT_LIST_STRUCT mountList;
//	DWORD dwResult;
//	UNMOUNT_STRUCT unmount;
//	BOOL bResult;
//	unsigned __int32 prevMountedDrives = 0;
//	int i;
//
//retry:
//	WaitCursor();
//
//	DeviceIoControl (hDriver, TC_IOCTL_GET_MOUNTED_VOLUMES, &mountList, sizeof (mountList), &mountList, sizeof (mountList), &dwResult, NULL);
//
//	if (mountList.ulMountedDrives == 0)
//	{
//		NormalCursor();
//		return TRUE;
//	}
//
//	BroadcastDeviceChange (DBT_DEVICEREMOVEPENDING, 0, mountList.ulMountedDrives);
//
//	prevMountedDrives = mountList.ulMountedDrives;
//
//	for (i = 0; i < 26; i++)
//	{
//		if (mountList.ulMountedDrives & (1 << i))
//		{
//			if (bCloseDismountedWindows)
//				CloseVolumeExplorerWindows (hwndDlg, i);
//		}
//	}
//
//	unmount.nDosDriveNo = 0;
//	unmount.ignoreOpenFiles = forceUnmount;
//
//	do
//	{
//		bResult = DeviceIoControl (hDriver, TC_IOCTL_DISMOUNT_ALL_VOLUMES, &unmount,
//			sizeof (unmount), &unmount, sizeof (unmount), &dwResult, NULL);
//
//		if (bResult == FALSE)
//		{
//			NormalCursor();
//			handleWin32Error (hwndDlg);
//			return FALSE;
//		}
//
//		if (unmount.nReturnCode == ERR_SUCCESS
//			&& unmount.HiddenVolumeProtectionTriggered
//			&& !VolumeNotificationsList.bHidVolDamagePrevReported [unmount.nDosDriveNo])
//		{
//			wchar_t msg[4096];
//
//			VolumeNotificationsList.bHidVolDamagePrevReported [unmount.nDosDriveNo] = TRUE;
//			swprintf (msg, GetString ("DAMAGE_TO_HIDDEN_VOLUME_PREVENTED"), unmount.nDosDriveNo + 'A');
//			SetForegroundWindow (hwndDlg);
//			MessageBoxW (hwndDlg, msg, lpszTitle, MB_ICONWARNING | MB_SETFOREGROUND | MB_TOPMOST);
//
//			unmount.HiddenVolumeProtectionTriggered = FALSE;
//			continue;
//		}
//
//		if (unmount.nReturnCode == ERR_FILES_OPEN)
//			Sleep (dismountAutoRetryDelay);
//		else
//			break;
//
//	} while (--dismountMaxRetries > 0);
//
//	memset (&mountList, 0, sizeof (mountList));
//	DeviceIoControl (hDriver, TC_IOCTL_GET_MOUNTED_VOLUMES, &mountList, sizeof (mountList), &mountList, sizeof (mountList), &dwResult, NULL);
//	BroadcastDeviceChange (DBT_DEVICEREMOVECOMPLETE, 0, prevMountedDrives & ~mountList.ulMountedDrives);
//
//	RefreshMainDlg (hwndDlg);
//
//	if (nCurrentOS == WIN_2000 && RemoteSession && !IsAdmin ())
//		LoadDriveLetters (GetDlgItem (hwndDlg, IDC_DRIVELIST), 0);
//
//	NormalCursor();
//
//	if (unmount.nReturnCode != 0)
//	{
//		if (forceUnmount)
//			status = FALSE;
//
//		if (unmount.nReturnCode == ERR_FILES_OPEN)
//		{
//			if (interact && IDYES == AskWarnYesNoTopmost ("UNMOUNTALL_LOCK_FAILED"))
//			{
//				forceUnmount = TRUE;
//				goto retry;
//			}
//
//			if (IsOSAtLeast (WIN_7))
//			{
//				// Undo SHCNE_DRIVEREMOVED
//				DeviceIoControl (hDriver, TC_IOCTL_GET_MOUNTED_VOLUMES, NULL, 0, &mountList, sizeof (mountList), &dwResult, NULL);
//
//				for (i = 0; i < 26; i++)
//				{
//					if (mountList.ulMountedDrives & (1 << i))
//					{
//						char root[] = { (char) i + 'A', ':', '\\', 0 };
//						SHChangeNotify (SHCNE_DRIVEADD, SHCNF_PATH, root, NULL);
//					}
//				}
//			}
//
//			return FALSE;
//		}
//		
//		if (interact)
//			MessageBoxW (hwndDlg, GetString ("UNMOUNT_FAILED"), lpszTitle, MB_ICONERROR);
//	}
//	else
//	{
//		if (bBeep)
//			MessageBeep (0xFFFFFFFF);
//	}
//
//	return status;
return FALSE;
}
