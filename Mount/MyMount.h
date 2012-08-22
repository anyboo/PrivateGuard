#pragma once

#include <Tcdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

	BOOL Mount (HWND hwndDlg, int nDosDriveNo, char *szFileName);
	BOOL Dismount (HWND hwndDlg, int nDosDriveNo);
	BOOL DismountAll (HWND hwndDlg, BOOL forceUnmount, BOOL interact, int dismountMaxRetries, int dismountAutoRetryDelay);

#ifdef __cplusplus
}
#endif
