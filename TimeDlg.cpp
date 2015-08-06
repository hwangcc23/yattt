#include <windows.h>
#include "resource.h"

#define ID_TIMER 1

BOOL WINAPI DlgProc(HWND hDlg,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	char szTimer[100];

	switch(iMsg) {
		case WM_INITDIALOG:
			SetTimer(hDlg,ID_TIMER,1000,NULL);
			return FALSE;

		case WM_TIMER:
			GetTimeFormat(LOCALE_SYSTEM_DEFAULT,0,NULL,NULL,szTimer,sizeof(szTimer));
			SetDlgItemText(hDlg,IDC_TIME,szTimer);
			return TRUE;
		case WM_DESTROY:
			KillTimer(hDlg,ID_TIMER);
	}
	return FALSE;
}

