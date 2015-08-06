#include <stdlib.h>
extern char cGameRecord[][3];

typedef struct
{
	char first;
	char second;
	char third;
} WinLine;

WinLine WinTable[8];

void TableInit()	//Initailize WinTable
{
	//1st col
	WinTable[0].first=cGameRecord[0][0];
	WinTable[0].second=cGameRecord[0][1];
	WinTable[0].third=cGameRecord[0][2];
	//2nd col
	WinTable[1].first=cGameRecord[1][0];
	WinTable[1].second=cGameRecord[1][1];
	WinTable[1].third=cGameRecord[1][2];
	//3rd col
	WinTable[2].first=cGameRecord[2][0];
	WinTable[2].second=cGameRecord[2][1];
	WinTable[2].third=cGameRecord[2][2];
	//1st row
	WinTable[3].first=cGameRecord[0][0];
	WinTable[3].second=cGameRecord[1][0];
	WinTable[3].third=cGameRecord[2][0];
	//2nd row
	WinTable[4].first=cGameRecord[0][1];
	WinTable[4].second=cGameRecord[1][1];
	WinTable[4].third=cGameRecord[2][1];
	//3rd cow
	WinTable[5].first=cGameRecord[0][2];
	WinTable[5].second=cGameRecord[1][2];
	WinTable[5].third=cGameRecord[2][2];
	//top-left to bottom-right
	WinTable[6].first=cGameRecord[0][0];
	WinTable[6].second=cGameRecord[1][1];
	WinTable[6].third=cGameRecord[2][2];
	//top-right to bottom-left
	WinTable[7].first=cGameRecord[2][0];
	WinTable[7].second=cGameRecord[1][1];
	WinTable[7].third=cGameRecord[0][2];
}

int IsWin(WinLine wlArg)
{
	if((wlArg.first==wlArg.second)&&(wlArg.second==wlArg.third)) {
		if(wlArg.first==1)
			return 1;
		else
		if(wlArg.first==2)
			return 2;
		else return 0;
	}
	return 0;
}

int Status()
{
	//return 1 if User win
	//return 2 if Computer win
	//return 3 if draw
	//return 0.....continue
	static bool fInit=false;
	int i,j=0;

	TableInit();
	for(i=0;i<8;i++) {
		j=IsWin(WinTable[i]);
		if(j!=0)
			return j;
		else
			continue;
	}
	for(i=0;i<3;i++) {
		for(j=0;j<3;j++)
			if(cGameRecord[i][j]==0)
				return 0;	//Game continue....
	}
	return 3;			//Draw....
}

bool CompMove()	
{	
	int iRandom;
	int i;

	TableInit();
	for(i=0;i<8;i++) {
		if((WinTable[i].first+WinTable[i].second==2) && (WinTable[i].third==0)) {	
			WinTable[i].third=2;	
			//Write it into cGameRecord[][]...
			if(i<3)
				cGameRecord[i][2]=2;
			else
			if(i<6)
				cGameRecord[2][i-3]=2;
			else
			if(i==6)
				cGameRecord[2][2]=2;
			else
				cGameRecord[0][2]=2;
			return true;
		}
		else
		if((WinTable[i].second+WinTable[i].third==2) && (WinTable[i].first==0)) {
			WinTable[i].first=2;
			//Write to cGameRecord[][]...
			if(i<3)
				cGameRecord[i][0]=2;
			else
			if(i<6)
				cGameRecord[0][i-3]=2;
			else
			if(i==6)
				cGameRecord[0][0]=2;
			else
				cGameRecord[2][0]=2;
			return true;
		}
		if((WinTable[i].first+WinTable[i].third==2) && (WinTable[i].second==0)) {
			WinTable[i].second=2;
			//Write to cGameRecord[][]...
				if(i<3)
					cGameRecord[i][1]=2;
				else
				if(i<6)
					cGameRecord[1][i-3]=2;
				else
				if(i==6)
					cGameRecord[1][1]=2;
				else
					cGameRecord[1][1]=2;
				return true;
		}
	}

	while(1) {
		iRandom=rand()%9;
		if(cGameRecord[iRandom/3][iRandom%3]==0)
			break;
	}
	cGameRecord[iRandom/3][iRandom%3]=2;
	return true;			
}