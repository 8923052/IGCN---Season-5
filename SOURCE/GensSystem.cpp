#include "StdAfx.h"
#include "..\common\winutil.h"
#include "GensSystem.h"
#include "logproc.h"
#include "user.h"

CPvPGens PvPGens;

CPvPGens::CPvPGens(void)
{
	this->Tick = GetTickCount();
}


CPvPGens::~CPvPGens(void)
{
}

char GensName[3][10] = { "Empty", "Duprian", "Vanert" };

void CPvPGens::Run()
{
	GetLocalTime(&this->Time);
	if(this->Time.wHour == 2 || this->Time.wHour == 8 || this->Time.wHour == 12 || this->Time.wHour == 18 || this->Time.wHour == 22 || this->Time.wHour == 0)
	{
		if(this->Time.wMinute == 0)
		{
			if(this->UpdateStatus == 0)
			{
				this->UpdateStatus = 1;
			}
		}
		else if(this->UpdateStatus == 2)
		{
			this->UpdateStatus = 0;
		}
	}
	if(this->UpdateStatus == 1)
	{
		LogAddTD("[Gens][RankUpdate] STATE: START");
		for(int i=OBJ_STARTUSERINDEX;i<OBJMAX;++i)
		{
			if(gObj[i].GensNumber != 0)
			{
				GDReqGensRank(i);
				LogAddTD("[Gens][RankUpdate] UPDATE RANK: (%s)(%s) (%s)", gObj[i].AccountID, gObj[i].Name, GensName[gObj[i].GensNumber]);
			}
		}
		LogAddTD("[Gens][RankUpdate] STATE: END");
		this->UpdateStatus = 2;
	}

	if(GetTickCount() - this->Tick > 300000)
	{
		for(int i=OBJ_STARTUSERINDEX;i<OBJMAX;++i)
		{
			if(gObj[i].GensNumber != 0)
			{
				GDReqGensSave(i);
			}
		}
		this->Tick = GetTickCount();
	}
}

void CPvPGens::CGReqJoinGens(PMSG_REQ_GENS_JOIN *lpMsg, LPOBJ lpObj)
{
	if(!OBJMAX_RANGE(lpObj->m_Index))
		return;

	if(lpObj->Type != OBJ_USER)
		return;

	if(lpObj->m_IfState.use == 1 && lpObj->m_IfState.type != 12)
		return;

	if(lpObj->PartyNumber != -1)
	{
		PMSG_GENS_JOIN pMsg;
		PHeadSubSetBE((LPBYTE)&pMsg, 0xF8, 0x02, sizeof(pMsg));
		pMsg.result = 6;
		pMsg.unk = 0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	}

	GDReqGensJoin(lpObj->m_Index, lpMsg->GensID);
	LogAddTD("[Gens] (%s)(%s) Request to Join to Gens: %s", lpObj->AccountID, lpObj->Name, GensName[lpMsg->GensID]);
}

void CPvPGens::GCAnsJoinGens(LPOBJ lpObj, int Result, int GensID, int GensExp, int GensNextExp, int GensPos)
{
	if(!OBJMAX_RANGE(lpObj->m_Index))
		return;

	if(lpObj->Type != OBJ_USER)
		return;

	if(lpObj->m_IfState.use == 1 && lpObj->m_IfState.type != 12)
		return;

	PMSG_GENS_JOIN pMsg;
	PHeadSubSetBE((LPBYTE)&pMsg, 0xF8, 0x02, sizeof(pMsg));

	pMsg.unk = GensExp;
	pMsg.result = Result;

	if(Result == 0)
	{
		lpObj->GensNumber = GensID;
		lpObj->GensExp = GensExp;
		lpObj->GensNextExp = GensNextExp;
		lpObj->GensPosition = GensPos;
		lpObj->GensRank = 0;

		LogAddTD("[Gens] (%s)(%s) Join to Gens: Success (%s)", lpObj->AccountID, lpObj->Name, GensName[GensID]);

		this->SendInfo(lpObj);
	}
	else
	{
		LogAddTD("[Gens] (%s)(%s) Join to Gens: Failed (%s)", lpObj->AccountID, lpObj->Name, GensName[GensID]);
	}

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	GDReqGensInfo(lpObj->m_Index);
}

void CPvPGens::CGReqGensInfo(LPOBJ lpObj)
{
	if(!OBJMAX_RANGE(lpObj->m_Index))
		return;

	if(lpObj->Type != OBJ_USER)
		return;

	GDReqGensInfo(lpObj->m_Index);
}

void CPvPGens::GCAnsGensInfo(GSP_ANS_GENS_INFO * aRecv)
{
	LPOBJ lpObj = &gObj[aRecv->aIndex];

	lpObj->GensNumber = aRecv->GensID;
	lpObj->GensPosition = aRecv->GensPos;
	lpObj->GensExp = aRecv->GensExp;
	lpObj->GensNextExp = aRecv->GensNextExp;
	lpObj->GensRank = aRecv->GensRank;
	lpObj->GensReward = aRecv->GensReward;

	PMSG_GENS_INFO pMsg;

	pMsg.GensID = aRecv->GensID;
	pMsg.GensLevel = aRecv->GensRank;
	pMsg.Contribution = aRecv->GensExp;
	pMsg.Position = aRecv->GensPos;
	pMsg.NextPosition = aRecv->GensNextExp;

	if(lpObj->GensExp > 10000 || lpObj->GensNextExp == 0)
	{
		lpObj->GensPosition = this->CalcPositionByRank(lpObj);
		pMsg.Position = lpObj->GensPosition;
	}

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x07, sizeof(pMsg));
	
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	LogAddTD("[Gens] (%s)(%s) Recv Info: %s, Contribution: %d, NextRank: %d, Rank: %d", lpObj->AccountID, lpObj->Name, GensName[lpObj->GensNumber], lpObj->GensExp, lpObj->GensNextExp, lpObj->GensPosition);
}

void CPvPGens::CGReqQuitGens(LPOBJ lpObj)
{
	if(!OBJMAX_RANGE(lpObj->m_Index))
		return;

	if(lpObj->Type != OBJ_USER)
		return;

	if(lpObj->m_IfState.use == 1 && lpObj->m_IfState.type != 12)
		return;

	PMSG_GENS_LEAVE pMsg;
	PHeadSubSetBE((LPBYTE)&pMsg, 0xF8, 0x04, sizeof(pMsg));

	if(lpObj->GensNumber == 0)
	{
		pMsg.result = 1;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if((lpObj->GensNumber == 1 && lpObj->TargetShopNumber != 543) || (lpObj->GensNumber == 2 && lpObj->TargetShopNumber != 544))
	{
		pMsg.result = 3;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if(lpObj->GuildStatus == 0x128) // GuildMaster
	{
		pMsg.result = 2;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	GDReqGensQuit(lpObj->m_Index);
	LogAddTD("[Gens] (%s)(%s) Request to leave from Gens: %s", lpObj->AccountID, lpObj->Name, GensName[lpObj->GensNumber]);
}

void CPvPGens::GCAnsGensQuit(LPOBJ lpObj, int Result)
{
	if(Result == 0)
	{
		lpObj->GensNumber = 0;
		lpObj->GensExp = 0;
		lpObj->GensNextExp = 0;
		lpObj->GensPosition = 0;
		lpObj->GensRank = 0;
		lpObj->GensReward = false;

		this->SendInfo(lpObj);

		PMSG_GENS_LEAVE pMsg;
		PHeadSubSetBE((LPBYTE)&pMsg, 0xF8, 0x04, sizeof(pMsg));

		pMsg.result = Result;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	}
}

void CPvPGens::CGReqGensReward(PMSG_REQ_GENS_REWARD *aRecv, LPOBJ lpObj)
{
	PMSG_ANS_GENS_REWARD pMsg;
	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x0A, sizeof(pMsg));

	if(lpObj->GensNumber == 0)
	{
		pMsg.result = 6;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if((lpObj->GensNumber == 1 && lpObj->TargetShopNumber == 544) || (lpObj->GensNumber == 2 && lpObj->TargetShopNumber == 543))
	{
		pMsg.result = 5;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if(this->Time.wDay != 1)
	{
		pMsg.result = 1;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if(lpObj->GensRank > 300)
	{
		pMsg.result = 2;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if(lpObj->GensReward == false)
	{
		pMsg.result = 4;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	int Count = 0;
	int PrizeID = 0;

	switch ( lpObj->GensPosition )
	{
		case 8:
			Count = 3;
			PrizeID = ITEMGET(14,144);
			break;
		case 7:
			Count = 5;
			PrizeID = ITEMGET(14,144);
			break;
		case 6:
			Count = 5;
			PrizeID = ITEMGET(14,143);
			break;
		case 5:
			Count = 10;
			PrizeID = ITEMGET(14,143);
			break;
		case 4:
			Count = 10;
			PrizeID = ITEMGET(14,142);
			break;
		case 3:
			Count = 20;
			PrizeID = ITEMGET(14,142);
			break;
		case 2:
			Count = 20;
			PrizeID = ITEMGET(14,141);
			break;
		case 1:
			Count = 30;
			PrizeID = ITEMGET(14,141);
			break;
	}

	if(PrizeID == 0 || Count == 0)
	{
		return;
	}

	for(int i=0;i<Count;++i)
	{
		if(!CheckInventoryEmptySpace(lpObj, 1, 1))
		{
			pMsg.result = 3;
			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			return;
		}
	}

	lpObj->GensReward = false;
	pMsg.result = 0;
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	for(int i=0;i<Count;++i)
	{
		ItemSerialCreateSend(lpObj->m_Index, 235, 0, 0, PrizeID, 0, 0, 0, 0, 0, lpObj->m_Index, 0, 0);
	}

	LogAddTD("[Gens] (%s)(%s) Got a monthly reward (%d)(%d)(%d)", lpObj->AccountID, lpObj->Name, lpObj->GensRank, PrizeID, Count);
}

void CPvPGens::SendInfo(LPOBJ lpObj)
{
	PMSG_GENS_INFO pMsg;

	pMsg.GensID = lpObj->GensNumber;
	pMsg.GensLevel = lpObj->GensRank;
	pMsg.Contribution = lpObj->GensExp;
	pMsg.Position = lpObj->GensPosition;
	pMsg.NextPosition = lpObj->GensNextExp - lpObj->GensExp;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x07, sizeof(pMsg));
	
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	gObjViewportListProtocolCreate(lpObj);
}
		
int CPvPGens::CalcPoint(LPOBJ lpObj, LPOBJ lpTargetObj, bool DeadMode)
{
	short LevelDiff = lpObj->Level - lpTargetObj->Level;
	if(!DeadMode)
	{
		if(LevelDiff < -51)
		{
			return 1;
		}
		if(LevelDiff <= -31 && LevelDiff >= -51)
		{
			return 2;
		}
		if(LevelDiff <= -11 && LevelDiff >= -30)
		{
			return 3;
		}
		if(LevelDiff >= -10 && LevelDiff <= 10)
		{
			return 5;
		}
		if(LevelDiff >= 11 && LevelDiff <= 50)
		{
			return 6;
		}
		if(LevelDiff >= 51)
		{
			return 7;
		}
	}
	else
	{
		if(LevelDiff <= 30)
		{
			return 3;
		}
		if(LevelDiff >= 31 && LevelDiff <= 50)
		{
			return 2;
		}
		if(LevelDiff >= 51)
		{
			return 1;
		}
	}
	return 0;
}

int CPvPGens::CalcNextPosition(LPOBJ lpObj)
{
	if(lpObj->GensPosition == 14)
		return 500;
	if(lpObj->GensPosition == 13)
		return 1500;
	if(lpObj->GensPosition == 12)
		return 3000;
	if(lpObj->GensPosition == 11)
		return 6000;
	if(lpObj->GensPosition == 10)
		return 10000;
	
	return 0;
}

int CPvPGens::CalcPositionByRank(LPOBJ lpObj)
{
	if(lpObj->GensRank > 200 && lpObj->GensRank <= 300)
		return 8;
	if(lpObj->GensRank >= 101 && lpObj->GensRank <= 200)
		return 7;
	if(lpObj->GensRank >= 51 && lpObj->GensRank <= 100)
		return 6;
	if(lpObj->GensRank >= 31 && lpObj->GensRank <= 50)
		return 5;
	if(lpObj->GensRank >= 11 && lpObj->GensRank <= 30)
		return 4;
	if(lpObj->GensRank >= 6 && lpObj->GensRank <= 10)
		return 3;
	if(lpObj->GensRank >= 2 && lpObj->GensRank <= 5)
		return 2;
	if(lpObj->GensRank == 1)
		return 1;

	return lpObj->GensRank;
}

bool CPvPGens::GensCheck(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(lpObj->MapNumber != lpTargetObj->MapNumber)
		return false;

	if(!this->IsBattleZone(lpObj->MapNumber))
		return false;

	if(lpObj->GensNumber == 0 || lpTargetObj->GensNumber == 0)
		return false;

	if(lpObj->GensNumber == lpTargetObj->GensNumber)
		return false;

	return true;
}

void CPvPGens::KillUserProc(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	lpTargetObj->GensExp += this->CalcPoint(lpObj, lpTargetObj, false);
	lpObj->GensExp -= this->CalcPoint(lpObj, lpTargetObj, true);
	if(lpObj->GensExp < 0) lpObj->GensExp = 0;

	if(lpTargetObj->GensExp >= lpTargetObj->GensNextExp && lpTargetObj->GensNextExp != 0)
	{
		lpTargetObj->GensPosition--;
		lpTargetObj->GensNextExp = this->CalcNextPosition(lpTargetObj);
		LogAddTD("[Gens] (%s)(%s) Position Up: %d", lpTargetObj->AccountID, lpTargetObj->Name, lpTargetObj->GensPosition);
	}

	this->SendInfo(lpObj);
	this->SendInfo(lpTargetObj);
}

void CPvPGens::RefreshPlayerRank(LPOBJ lpObj, int Rank)
{
	lpObj->GensRank = Rank;
	if(lpObj->GensExp > 10000 || lpObj->GensNextExp != 0)
	{
		lpObj->GensPosition = this->CalcPositionByRank(lpObj);
	}

	PMSG_GENS_INFO pMsg;

	pMsg.GensID = lpObj->GensNumber;
	pMsg.GensLevel = Rank;
	pMsg.Contribution = lpObj->GensExp;
	pMsg.Position = lpObj->GensPosition;
	pMsg.NextPosition = lpObj->GensNextExp;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x07, sizeof(pMsg));
	
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

}