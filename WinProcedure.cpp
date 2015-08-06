#include <windows.h>
#include <math.h>
#include "resource.h"

#define MoveTo(hdc,x,y) MoveToEx(hdc,x,y,NULL)

extern char cGameRecord[][3];
extern HWND hDlg;

BOOL WINAPI DlgProc(HWND,UINT,WPARAM,LPARAM);
int Status();
bool CompMove();

bool TestWin(HWND hwnd)		//check if someone win...
{
	int i,j;

	i=Status();
	if(i==1) {	//User win!!
		MessageBox(hwnd,"你好棒兒!!","OOXX",MB_OK);
		//Clean...
		for(i=0;i<3;i++) {
			for(j=0;j<3;j++)
				cGameRecord[i][j]=0;	
		}
		InvalidateRect(hwnd,NULL,TRUE);
		return true;
	}
	else
	if(i==2) { 	//Computer Win!!
		MessageBox(hwnd,"你好遜兒!!","OOXX",MB_OK);
		//Clean...
		for(i=0;i<3;i++) {
			for(j=0;j<3;j++)
				cGameRecord[i][j]=0;	
		}
		InvalidateRect(hwnd,NULL,TRUE);
		return true;
	}
	else
	if(i==3) {	//Draw!!
		MessageBox(hwnd,"平手!!","OOXX",MB_OK);
		//Clean...
		for(i=0;i<3;i++) {
			for(j=0;j<3;j++)
				cGameRecord[i][j]=0;	
		}
		InvalidateRect(hwnd,NULL,TRUE);
		return true;
	}
	return false;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	static int cxClient,cyClient,cxBlock,cyBlock,cxPos,cyPos,iOver;
	int i,j;
	HDC hdc;
	PAINTSTRUCT ps;

	switch(iMsg) {
		case WM_CREATE:
			hDlg=CreateDialog(((LPCREATESTRUCT)lParam)->hInstance,MAKEINTRESOURCE(IDD_TIME),
						hwnd,DlgProc);
			//Initailize GameRecord Array
			for(i=0;i<3;i++) {
				for(j=0;j<3;j++)
					cGameRecord[i][j]=0;
			}
			return 0;

		case WM_SIZE:
			cxClient=LOWORD(lParam);
			cyClient=HIWORD(lParam);
			cxBlock=cxClient/3;
			cyBlock=cyClient/3;
			return 0;

		case WM_PAINT:
			hdc=BeginPaint(hwnd,&ps);
			
			//Draw 4 Lines
			MoveTo(hdc,cxClient/3,0); LineTo(hdc,cxClient/3,cyClient);
			MoveTo(hdc,2*cxClient/3,0); LineTo(hdc,2*cxClient/3,cyClient);
			MoveTo(hdc,0,cyClient/3); LineTo(hdc,cxClient,cyClient/3);
			MoveTo(hdc,0,2*cyClient/3); LineTo(hdc,cxClient,2*cyClient/3);
			for(i=0;i<3;i++) {
				for(j=0;j<3;j++)
					if(cGameRecord[i][j]!=0) {
						if(cGameRecord[i][j]==1) 	
							//Draw "O"
							Ellipse(hdc,i*cxBlock+cxBlock/3,j*cyBlock+cyBlock/3,
									i*cxBlock+2*cxBlock/3,j*cyBlock+2*cyBlock/3);
						else	
						{	//Draw "X"
							MoveTo(hdc,i*cxBlock+cxBlock/3,j*cyBlock+cyBlock/3);
							LineTo(hdc,i*cxBlock+2*cxBlock/3,j*cyBlock+2*cyBlock/3);
							MoveTo(hdc,i*cxBlock+2*cxBlock/3,j*cyBlock+cyBlock/3);
							LineTo(hdc,i*cxBlock+cxBlock/3,j*cyBlock+2*cyBlock/3);
						}				
					}
			}
			EndPaint(hwnd,&ps);
			return 0;

		case WM_LBUTTONDOWN:
			InvalidateRect(hwnd,NULL,FALSE);
			cxPos=LOWORD(lParam)/cxBlock;
			cyPos=HIWORD(lParam)/cyBlock;		
			if(cGameRecord[cxPos][cyPos]!=0)
				return 0;
			cGameRecord[cxPos][cyPos]=1;		//"O"
			InvalidateRect(hwnd,NULL,FALSE);
			//Test Status......
			if(TestWin(hwnd))
				return 0;
			if(!CompMove()) {
				MessageBox(hwnd,"Error!!",NULL,MB_OK);
				DestroyWindow(hwnd);
			}
			if(TestWin(hwnd))
				return 0;
			InvalidateRect(hwnd,NULL,TRUE);
			return 0;

		case WM_DESTROY:
			DestroyWindow(hDlg);
			PostQuitMessage(0);
			return 0;

		default:
			break;
	}
	return DefWindowProc(hwnd,iMsg,wParam,lParam);
}
