/*
-- XMAS Event WEBZEN Season 4 (JPN)
-- Coded by drakelv (c) 2009
*/

#include "stdafx.h"
#include "XmasEvent.h"
#include "user.h"
#include "GameMain.h"
#include "LogProc.h"
#include "..\include\readscript.h"


XMasEvent gCXMasEvent;

static int g_XMasEventMap[3] = { MAP_INDEX_RORENCIA,MAP_INDEX_DEVIAS,MAP_INDEX_NORIA};



XMasEvent::XMasEvent()
{
	this->EventStartTime = 0;
	this->STATE = 0;
	this->m_iMaxMonsterCount = 0;
}

XMasEvent::~XMasEvent()
{
	return;
}


void XMasEvent::XMasEventRun()
{
if(gXMasEventRun == 0)
{return;}
	if(this->EventStartTime == 0)
	{
		tm * today;
		time_t ltime;

		time(&ltime);
		today = localtime(&ltime);

		DWORD Time = GetTickCount();
		this->EventStartTime = Time;
		LogAddTD("[XMas Event] State - CLOSED. Start After [%d] Minutes.",gXMasEventMinute-1);
	}
	else
	{
		if(this->STATE == 1) // alredy running
		return;

		DWORD Time = GetTickCount();
		if(( Time - this->EventStartTime ) > gXMasEventMinute * 60000)
		{
			LogAddC(2,"[XMAS Event] Evil Santa Attacks MuTizens");
			this->XMasEventInvade();
			this->EventStartTime = Time;
			this->STATE = 1;
		}
	}
	
//
}

void XMasEvent::XMasEventSantaBagLoad(unsigned char * filename)
{
	// to do: full code here
}

void XMasEvent::XMasEventSantaRewardDrop(LPOBJ lpObj)
{
	// to do: full code here

}

void XMasEvent::LoadData(LPSTR lpszFileName)
{
	if ( !lpszFileName || !strcmp(lpszFileName , "") )
	{
		MsgBox("[ SANTA EVENT ][ MonsterSetBase ] - File load error : File Name Error");
		return;
	}

	try
	{
		
		SMDFile = fopen(lpszFileName, "r");

		if ( SMDFile == NULL )
		{
			DWORD dwError = GetLastError();
			MsgBox("[ SANTA EVENT ][ MonsterSetBase ] - Can't Open %s ", lpszFileName);
			return;
		}

		for ( int iCount=0;iCount<50;iCount++)
		{
			memset(&this->m_SetBaseInfo[iCount], -1, sizeof(this->m_SetBaseInfo[iCount]));
		}

		this->m_iMaxMonsterCount = 0;
	
		enum SMDToken Token;
		int iType = -1;
		BYTE btGroup = 0;
		WORD wType = 0;
		BYTE btMapNumber = 0;
		BYTE btDistance = 0;
		BYTE btX = 0;
		BYTE btY = 0;
		BYTE btDir = 0;

		while ( true )
		{
			Token = GetToken();
			
			if ( Token == END )
			{
				break;
			}

			iType = TokenNumber;

			while ( true )
			{
				if ( iType == 0 )
				{
					wType = 0;
					btMapNumber = 0;
					btDistance = 0;
					btX = 0;
					btY = 0;
					btDir = 0;

					Token = GetToken();

					if ( !strcmp("end", TokenString))
					{
						break;
					}

					wType = TokenNumber;

					Token = GetToken();
					btMapNumber = TokenNumber;

					Token = GetToken();
					btDistance = TokenNumber;

					Token = GetToken();
					btX = TokenNumber;

					Token = GetToken();
					btY = TokenNumber;

					Token = GetToken();
					btDir = TokenNumber;

					if ( this->m_iMaxMonsterCount < 0 ||
						 this->m_iMaxMonsterCount >= 51 )
					{
						MsgBox("[ SANTA EVENT ][ MonsterSetBase ] - Exceed Max Info Count (%d)",
							this->m_iMaxMonsterCount);

						break;
					}

					this->SetMonsterSetBaseInfo(this->m_iMaxMonsterCount, wType,
						btMapNumber, btDistance, btX, btY, btDir);
					this->m_iMaxMonsterCount++;
				}
				else
				{
					Token = GetToken();

					if ( !strcmp("end", TokenString))
					{
						break;
					}
				}
			}
		}	

		fclose(SMDFile);
		LogAddC(2, "[ SANTA EVENT ][ MonsterSetBase ] - %s file is Loaded",
			lpszFileName);

	}
	catch ( DWORD)
	{
		MsgBox("[ SANTA EVENT ][ MonsterSetBase ] Loading Exception Error (%s) File. ", lpszFileName);
	}

	return;

}

void XMasEvent::SetMonsterSetBaseInfo(int iIndex, WORD wType, BYTE btMapNumber, BYTE btDistance, BYTE btX, BYTE btY, BYTE btDir)
{
	this->m_SetBaseInfo[iIndex].wType = wType;
	this->m_SetBaseInfo[iIndex].btMapNumber = btMapNumber;
	this->m_SetBaseInfo[iIndex].btDistance = btDistance;
	this->m_SetBaseInfo[iIndex].btX = btX;
	this->m_SetBaseInfo[iIndex].btY = btY;
	this->m_SetBaseInfo[iIndex].btDir = btDir;
}

void XMasEvent::XMasEventInvade()
{
	int iMapNumber = 0;
	WORD wType = 0;
	LPOBJ lpObj;
	int iResult;
	int iRegenCount = 0;

	for (int iCount=0;iCount<this->m_iMaxMonsterCount;iCount++)
	{
		if ( this->m_SetBaseInfo[iCount].wType != 0)
		{
			iResult = gObjAddMonster(this->m_SetBaseInfo[iCount].btMapNumber);

			if ( iResult < 0 )
				{
					LogAddTD("[ SANTA EVENT ][ Set Invasion Monster ] Fail - Type:%d Map[%d]-[%d][%d]",
						this->m_SetBaseInfo[iCount].wType,
						this->m_SetBaseInfo[iCount].btMapNumber,
						this->m_SetBaseInfo[iCount].btX,
						this->m_SetBaseInfo[iCount].btY);
				}
			else
				{
					lpObj = &gObj[iResult];

					lpObj->m_PosNum = -1;
					lpObj->X = this->m_SetBaseInfo[iCount].btX;
					lpObj->Y = this->m_SetBaseInfo[iCount].btY;
					lpObj->MapNumber = this->m_SetBaseInfo[iCount].btMapNumber;

/*				if ( this->GetPosition(iCount, lpObj->MapNumber, lpObj->X, lpObj->Y) == FALSE )
				{
					gObjDel(iResult);
					continue;
				}*/

					lpObj->TX = lpObj->X;
					lpObj->TY = lpObj->Y;
					lpObj->m_OldX = lpObj->X;
					lpObj->m_OldY = lpObj->Y;
					lpObj->StartX = lpObj->X;
					lpObj->StartY = lpObj->Y;
					lpObj->m_MoveRange = this->m_SetBaseInfo[iCount].btDistance;
					lpObj->DieRegen = FALSE;

				if ( this->m_SetBaseInfo[iCount].btDir == 0xFF )
				{
						lpObj->Dir = rand()%8;
				}
				else
				{
						lpObj->Dir = this->m_SetBaseInfo[iCount].btDir;
				}

				if ( gObjSetMonster(iResult, this->m_SetBaseInfo[iCount].wType) == FALSE )
				{
						gObjDel(iResult);
						continue;
				}

				if ( gObj[iResult].Type == OBJ_MONSTER )
				{
					this->m_XMasMonster.AddObj(iResult);
					this->m_iAliveMonsterCount++;

					LogAddTD("[ SANTA EVENT ][ SetInvadeMonster ][ACTIVE]");
				}

				iRegenCount++;
			}
		}
	}
	LogAddTD("[XMAS EVENT] START !!!");
	AllSendServerMsg("[XMAS EVENT] Start in Devias HAPPY HUNTING");
	return;
}

void XMasEvent::XMasEventEnd()
{
	for ( int iCount=0;iCount<this->m_XMasMonster.GetCount();iCount++)
	{
		if ( this->m_XMasMonster.m_iObjIndex[iCount] != -1 )
		{
			gObjDel(this->m_XMasMonster.m_iObjIndex[iCount]);
		}
	}

	this->m_XMasMonster.Reset();
	this->m_iMaxMonsterCount = 0;
	this->STATE = 0;
}

void XMasEvent::MonsterDie(int iIndex)
{
	LPOBJ lpObj = &gObj[iIndex];
	if(this->STATE == 1)
	{
	for ( int iCount=0;iCount<this->m_XMasMonster.GetCount();iCount++)
	{
		if ( this->m_XMasMonster.m_iObjIndex[iCount] == iIndex )
		{
			this->m_iAliveMonsterCount--;
				if(this->m_iAliveMonsterCount <= 0){
					LogAddTD("[XMAS Event] All Monster dead");
					AllSendServerMsg("[XMAS Event] All monster dead, go Santa Town!!!");
					this->XMasEventEnd(); }
			return;
		}
	}


	}
}