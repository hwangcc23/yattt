#include <windows.h>
#include "resource.h"

char cGameRecord[3][3];
HWND hDlg=0;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE PreInstance,PSTR szCmdLine,int iCmdShow)
{
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	char * szAppName="TicTacToc";

	wndclass.cbSize=sizeof(wndclass);
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.style=CS_HREDRAW | CS_VREDRAW;
	wndclass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_RINOA));
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hIconSm=wndclass.hIcon;
	wndclass.lpszClassName=szAppName;
	wndclass.lpszMenuName=NULL;
	wndclass.hInstance=hInstance;
	wndclass.lpfnWndProc=WndProc;
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);

	RegisterClassEx(&wndclass);

	hwnd=CreateWindow(szAppName,NULL,WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,CW_USEDEFAULT,
						CW_USEDEFAULT,CW_USEDEFAULT,
						0,0,hInstance,NULL);

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0)) {
		if(hDlg==0 || !IsDialogMessage(hDlg,&msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

