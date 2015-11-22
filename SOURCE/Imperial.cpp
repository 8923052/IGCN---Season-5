#include "stdafx.h"
#include "Imperial.h"
#include "user.h"
#include "protocol.h"
#include "BloodCastle.h"
#include "..\common\winutil.h"
#include "logproc.h"
#include "ImperialBattleUserMng.h"
#include "MasterLevelSystem.h"
#include "GameMain.h"
CImperial g_Imperial;


CImperial::CImperial()
{
	this->m_ImperialData.Reset();
}

CImperial::~CImperial()
{
}

void CImperial::Init()
{
	this->m_ImperialData.Reset();

	this->SetState(IMPERIAL_STATE_OPEN);
}

void CImperial::SetState(int iState)
{
	switch ( iState )
	{
		case IMPERIAL_STATE_NONE:
			return;
		case IMPERIAL_STATE_OPEN:
			this->SetState_OPEN();
			break;
		case IMPERIAL_STATE_DESTLER:
			this->SetState_DESTLER();
			break;
		case IMPERIAL_STATE_VERMONT:
			this->SetState_VERMONT();
			break;
		case IMPERIAL_STATE_KATO:
			this->SetState_KATO();
			break;
		case IMPERIAL_STATE_GALIA:
			this->SetState_GALIA();
			break;
		case IMPERIAL_STATE_ERKANNE:
			this->SetState_ERKANNE();
			break;
		case IMPERIAL_STATE_RAYMOND:
			this->SetState_RAYMOND();
			break;
		case IMPERIAL_STATE_GAION:
			this->SetState_GAION();
			break;
		case IMPERIAL_STATE_ENDED:
			this->SetState_ENDED();
			break;
	}
}

void CImperial::SetState_OPEN()
{
	LogAddC(4, "[ IMPERIAL FORT ] State(%d) -> OPEN", this->m_ImperialData.iState);
	for(int i=OBJ_STARTUSERINDEX;i<OBJMAX;++i)
	{
		if(IMPERIAL_MAP_RANGE(gObj[i].MapNumber) && gObj[i].Connected == PLAYER_PLAYING)
		{
			gObjMoveGate(i, 267);
		}
	}
	for(int i=0;i<OBJ_MAXMONSTER;++i)
	{
		if(gObjIsConnected(i) && IMPERIAL_MAP_RANGE(gObj[i].MapNumber) && gObj[i].Class != 523)
			gObjDel(i);
	}

	if(this->m_BattleOfDestler.GetEventState() != 3)
	{
		this->m_BattleOfDestler.SetState(0);
	}

	if(this->m_BattleOfVermont.GetEventState() != 3)
	{
		this->m_BattleOfVermont.SetState(0);
	}

	if(this->m_BattleOfKato.GetEventState() != 3)
	{
		this->m_BattleOfKato.SetState(0);
	}

	if(this->m_BattleOfGalia.GetEventState() != 3)
	{
		this->m_BattleOfGalia.SetState(0);
	}

	if(this->m_BattleOfErkanne.GetEventState() != 3)
	{
		this->m_BattleOfErkanne.SetState(0);
	}

	if(this->m_BattleOfRaymond.GetEventState() != 3)
	{
		this->m_BattleOfRaymond.SetState(0);
	}

	if(this->m_BattleOfGaion.GetEventState() != 3)
	{
		this->m_BattleOfGaion.SetState(0);
	}

	this->m_ImperialData.Reset();
	g_ImperialBattleUserMng.ResetAllData();
	this->m_ImperialData.iState = IMPERIAL_STATE_OPEN;
}

void CImperial::SetState_DESTLER()
{
	LogAddC(4, "[ IMPERIAL FORT ] State(%d) -> BATTLE_OF_DESTLER", this->m_ImperialData.iState);
	this->m_BattleOfDestler.SetState(1);
	this->m_ImperialData.iState = IMPERIAL_STATE_DESTLER;
}

void CImperial::SetState_VERMONT()
{
	LogAddC(4, "[ IMPERIAL FORT ] State(%d) -> BATTLE_OF_VERMONT", this->m_ImperialData.iState);
	this->m_BattleOfVermont.SetState(1);
	this->m_ImperialData.iState = IMPERIAL_STATE_VERMONT;
}

void CImperial::SetState_KATO()
{
	LogAddC(4, "[ IMPERIAL FORT ] State(%d) -> BATTLE_OF_KATO", this->m_ImperialData.iState);
	this->m_BattleOfKato.SetState(1);
	this->m_ImperialData.iState = IMPERIAL_STATE_KATO;
}

void CImperial::SetState_GALIA()
{
	LogAddC(4, "[ IMPERIAL FORT ] State(%d) -> BATTLE_OF_GALIA", this->m_ImperialData.iState);
	this->m_BattleOfGalia.SetState(1);
	this->m_ImperialData.iState = IMPERIAL_STATE_GALIA;
}

void CImperial::SetState_ERKANNE()
{
	LogAddC(4, "[ IMPERIAL FORT ] State(%d) -> BATTLE_OF_ERKANNE", this->m_ImperialData.iState);
	this->m_BattleOfErkanne.SetState(1);
	this->m_ImperialData.iState = IMPERIAL_STATE_ERKANNE;
}

void CImperial::SetState_RAYMOND()
{
	LogAddC(4, "[ IMPERIAL FORT ] State(%d) -> BATTLE_OF_RAYMOND", this->m_ImperialData.iState);
	this->m_BattleOfRaymond.SetState(1);
	this->m_ImperialData.iState = IMPERIAL_STATE_RAYMOND;
}

void CImperial::SetState_GAION()
{
	LogAddC(4, "[ IMPERIAL FORT ] State(%d) -> BATTLE_OF_GAION", this->m_ImperialData.iState);
	this->m_BattleOfGaion.SetState(1);
	this->m_ImperialData.iState = IMPERIAL_STATE_GAION;
}


void CImperial::SetState_ENDED()
{
	LogAddC(4, "[ IMPERIAL FORT ] State(%d) -> ENDED", this->m_ImperialData.iState);
	this->m_ImperialData.iState = IMPERIAL_STATE_ENDED;
	g_ImperialBattleUserMng.ResetAllData();
	this->m_ImperialData.Time = 60000;
	this->m_ImperialData.Tick = GetTickCount();
}


void CImperial::Run()
{
	g_ImperialBattleUserMng.CheckUserState();
	switch ( this->m_ImperialData.iState )
	{
		case IMPERIAL_STATE_NONE:
			return;
		case IMPERIAL_STATE_OPEN:
			this->ProcState_OPEN();
			break;
		case IMPERIAL_STATE_DESTLER:
			this->ProcState_DESTLER();
			break;
		case IMPERIAL_STATE_VERMONT:
			this->ProcState_VERMONT();
			break;
		case IMPERIAL_STATE_KATO:
			this->ProcState_KATO();
			break;
		case IMPERIAL_STATE_GALIA:
			this->ProcState_GALIA();
			break;
		case IMPERIAL_STATE_ERKANNE:
			this->ProcState_ERKANNE();
			break;
		case IMPERIAL_STATE_RAYMOND:
			this->ProcState_RAYMOND();
			break;
		case IMPERIAL_STATE_GAION:
			this->ProcState_GAION();
			break;
		case IMPERIAL_STATE_ENDED:
			this->ProcState_ENDED();
			break;
	}
}

void CImperial::ProcState_OPEN()
{
	if ( g_ImperialBattleUserMng.GetUserCount() > 0 )
	{
		int Day = this->GetCurrentDay();

		switch ( Day )
		{
			case 1:
				this->SetState(IMPERIAL_STATE_DESTLER);
				break;
			case 2:
				this->SetState(IMPERIAL_STATE_VERMONT);
				break;
			case 3:
				this->SetState(IMPERIAL_STATE_KATO);
				break;
			case 4:
				this->SetState(IMPERIAL_STATE_GALIA);
				break;
			case 5:
				this->SetState(IMPERIAL_STATE_ERKANNE);
				break;
			case 6:
				this->SetState(IMPERIAL_STATE_RAYMOND);
				break;
			case 7:
				this->SetState(IMPERIAL_STATE_GAION);
				break;
		}
	}
}

void CImperial::ProcState_DESTLER()
{
	if ( g_ImperialBattleUserMng.GetUserCount() <= 0 )
	{
		this->m_BattleOfDestler.SetState(7);
		return;
		//wywalanie graczy i reset
	}	
	if ( this->m_BattleOfDestler.GetEventState() == 0 )
	{
		if(this->m_BattleOfDestler.GetSuccessValue() == true)
		{
			for(int i=0;i<g_ImperialBattleUserMng.GetUserCount();++i)
			{
				this->GiveRewardExp(g_ImperialBattleUserMng.m_BattleUser[i].GetIndex(), g_ExpTable[this->m_ImperialData.Day].Experience);
			}
		}
		this->m_BattleOfDestler.SetState(0);
		this->SetState(IMPERIAL_STATE_ENDED);
		return;
	}
	this->m_ImperialData.Time = this->m_BattleOfDestler.m_BattleData.Time;
	this->m_BattleOfDestler.Run();
}

void CImperial::ProcState_VERMONT()
{
	if ( g_ImperialBattleUserMng.GetUserCount() <= 0 )
	{
		this->m_BattleOfVermont.SetState(7);
		return;
		//wywalanie graczy i reset
	}	
	if ( this->m_BattleOfVermont.GetEventState() == 0 )
	{
		if(this->m_BattleOfVermont.GetSuccessValue() == true)
		{
			for(int i=0;i<g_ImperialBattleUserMng.GetUserCount();++i)
			{
				this->GiveRewardExp(g_ImperialBattleUserMng.m_BattleUser[i].GetIndex(), g_ExpTable[this->m_ImperialData.Day].Experience);
			}
		}
		this->m_BattleOfVermont.SetState(0);
		this->SetState(IMPERIAL_STATE_ENDED);
		return;
	}
	this->m_ImperialData.Time = this->m_BattleOfVermont.m_BattleData.Time;
	this->m_BattleOfVermont.Run();
}

void CImperial::ProcState_KATO()
{
	if ( g_ImperialBattleUserMng.GetUserCount() <= 0 )
	{
		this->m_BattleOfKato.SetState(7);
		return;
		//wywalanie graczy i reset
	}	
	if ( this->m_BattleOfKato.GetEventState() == 0 )
	{
		if(this->m_BattleOfKato.GetSuccessValue() == true)
		{
			for(int i=0;i<g_ImperialBattleUserMng.GetUserCount();++i)
			{
				this->GiveRewardExp(g_ImperialBattleUserMng.m_BattleUser[i].GetIndex(), g_ExpTable[this->m_ImperialData.Day].Experience);
			}
		}
		this->m_BattleOfKato.SetState(0);
		this->SetState(IMPERIAL_STATE_ENDED);
		return;
	}
	this->m_ImperialData.Time = this->m_BattleOfKato.m_BattleData.Time;
	this->m_BattleOfKato.Run();
}

void CImperial::ProcState_GALIA()
{
	if ( g_ImperialBattleUserMng.GetUserCount() <= 0 )
	{
		this->m_BattleOfGalia.SetState(7);
		return;
		//wywalanie graczy i reset
	}	
	if ( this->m_BattleOfGalia.GetEventState() == 0 )
	{
		if(this->m_BattleOfGalia.GetSuccessValue() == true)
		{
			for(int i=0;i<g_ImperialBattleUserMng.GetUserCount();++i)
			{
				this->GiveRewardExp(g_ImperialBattleUserMng.m_BattleUser[i].GetIndex(), g_ExpTable[this->m_ImperialData.Day].Experience);
			}
		}
		this->m_BattleOfGalia.SetState(0);
		this->SetState(IMPERIAL_STATE_ENDED);
		return;
	}
	this->m_ImperialData.Time = this->m_BattleOfGalia.m_BattleData.Time;
	this->m_BattleOfGalia.Run();
}

void CImperial::ProcState_ERKANNE()
{
	if ( g_ImperialBattleUserMng.GetUserCount() <= 0 )
	{
		LogAddTD("[ IMPERIAL FORT ] Quest Failed - No User");
		this->m_BattleOfErkanne.SetState(7);
		//wywalanie graczy i reset
	}	
	if ( this->m_BattleOfErkanne.GetEventState() == 0 )
	{
		if(this->m_BattleOfErkanne.GetSuccessValue() == true)
		{
			for(int i=0;i<g_ImperialBattleUserMng.GetUserCount();++i)
			{
				this->GiveRewardExp(g_ImperialBattleUserMng.m_BattleUser[i].GetIndex(), g_ExpTable[this->m_ImperialData.Day].Experience);
			}
		}
		this->m_BattleOfErkanne.SetState(0);
		this->SetState(IMPERIAL_STATE_ENDED);
		return;
	}
	this->m_ImperialData.Time = this->m_BattleOfErkanne.m_BattleData.Time;
	this->m_BattleOfErkanne.Run();
}

void CImperial::ProcState_RAYMOND()
{
	if ( g_ImperialBattleUserMng.GetUserCount() <= 0 )
	{
		LogAddTD("[ IMPERIAL FORT ] Quest Failed - No User");
		this->m_BattleOfRaymond.SetState(7);
		//wywalanie graczy i reset
	}	
	if ( this->m_BattleOfRaymond.GetEventState() == 0 )
	{
		if(this->m_BattleOfRaymond.GetSuccessValue() == true)
		{
			for(int i=0;i<g_ImperialBattleUserMng.GetUserCount();++i)
			{
				this->GiveRewardExp(g_ImperialBattleUserMng.m_BattleUser[i].GetIndex(), g_ExpTable[this->m_ImperialData.Day].Experience);
			}
		}
		this->m_BattleOfRaymond.SetState(0);
		this->SetState(IMPERIAL_STATE_ENDED);
		return;
	}
	this->m_ImperialData.Time = this->m_BattleOfRaymond.m_BattleData.Time;
	this->m_BattleOfRaymond.Run();
}

void CImperial::ProcState_GAION()
{
	if ( g_ImperialBattleUserMng.GetUserCount() <= 0 )
	{
		LogAddTD("[ IMPERIAL FORT ] Quest Failed - No User");
		this->m_BattleOfGaion.SetState(9);
		//wywalanie graczy i reset
	}	
	if ( this->m_BattleOfGaion.GetEventState() == 0 )
	{
		if(this->m_BattleOfGaion.GetSuccessValue() == true)
		{
			for(int i=0;i<g_ImperialBattleUserMng.GetUserCount();++i)
			{
				this->GiveRewardExp(g_ImperialBattleUserMng.m_BattleUser[i].GetIndex(), g_ExpTable[this->m_ImperialData.Day].Experience);
			}
		}
		this->SetState(IMPERIAL_STATE_ENDED);
		return;
	}
	this->m_ImperialData.Time = this->m_BattleOfGaion.m_BattleData.Time;
	this->m_BattleOfGaion.Run();
}

void CImperial::ProcState_ENDED()
{
	int Tick = GetTickCount() - this->m_ImperialData.Tick;
	if(Tick >= 1000)
	{
		this->m_ImperialData.Time -= Tick;
		this->m_ImperialData.Tick = GetTickCount();

		if(this->m_ImperialData.Time <= 0)
		{
			this->SetState(IMPERIAL_STATE_OPEN);
		}
	}
}



bool CImperial::EnterEvent(short aIndex)
{
	PMSG_FORT_ENTER_RESULT pMsg;
	PHeadSubSetB((LPBYTE)&pMsg, 0xF7, 0x02, sizeof(pMsg));

	int Day = this->GetCurrentDay();
	int invitationpos = -1;
	pMsg.Index = aIndex;
	pMsg.Day = Day;
	pMsg.State = 1;
	pMsg.Unk = rand()%4; // weather
	if(!gObjIsConnectedGP(aIndex))
	{
		return false;
	}

	if(gObj[aIndex].PartyNumber == -1)
	{
		pMsg.Result = 6;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		return false;
	}

	if(Day == 7)
	{
		for(short i = 12 ; i < 76; ++i)
		{
			if(gObj[aIndex].pInventory[i].m_Type > 0 && gObj[aIndex].pInventory[i].m_Type == ITEMGET(14,109))
			{
				invitationpos = i;
				break;
			}
		}
		if(invitationpos == -1)
		{
			pMsg.Result = 2;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			return false;
		}
	}
	else
	{
		for(short i = 12 ; i < 76; ++i)
		{
			if(gObj[aIndex].pInventory[i].m_Type > 0 && gObj[aIndex].pInventory[i].m_Type == ITEMGET(14,102))
			{
				invitationpos = i;
				break;
			}
		}
		if(invitationpos == -1)
		{
			pMsg.Result = 2;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			return false;
		}
	}

	if(this->m_ImperialData.iState != IMPERIAL_STATE_OPEN)
	{
		if(gObj[aIndex].PartyNumber != this->m_ImperialData.PartyID)
		{
			int CurrState = this->GetSpecificState();
			if(CurrState != 1) // STANDBY1
			{
				pMsg.Result = 1;
				pMsg.EntryTime = ((this->m_ImperialData.Time / 60) / 1000);
				DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
				return false;
			}
		}
	}

	if(g_ImperialBattleUserMng.AddUserData(aIndex) == true)
	{
		gObjInventoryDeleteItem(aIndex, invitationpos);
		GCInventoryItemDeleteSend(aIndex, invitationpos, 1);
		gObj[aIndex].TargetShopNumber = 0;

		pMsg.Result = 0;

		this->m_ImperialData.PartyID = gObj[aIndex].PartyNumber;
		this->m_ImperialData.Day = Day;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		gObjMoveGate(aIndex, g_ImperialGate[Day-1].Gate);
		LogAddTD("[Imperial] (%s)(%s) Entered to Imperial Fort Event | Day: %d | PartyID: %d", gObj[aIndex].AccountID, gObj[aIndex].Name, Day, gObj[aIndex].PartyNumber);
	}
}

int CImperial::GetCurrentDay()
{
	SYSTEMTIME Time;
	GetSystemTime(&Time);
	if(Time.wDayOfWeek == 0)
		return 7;
	else return Time.wDayOfWeek;
}

void CImperial::SetTrapIndex(short aIndex, int MapNumber)
{
	switch ( MapNumber )
	{
		case 69:
			{
				this->m_BattleOfDestler.m_BattleData.TrapIndex = aIndex;
				this->m_BattleOfGalia.m_BattleData.TrapIndex = aIndex;
			}
			break;
		case 70:
			{
				this->m_BattleOfVermont.m_BattleData.TrapIndex = aIndex;
				this->m_BattleOfErkanne.m_BattleData.TrapIndex = aIndex;
			}
			break;
		case 71:
			{
				this->m_BattleOfKato.m_BattleData.TrapIndex = aIndex;
				this->m_BattleOfRaymond.m_BattleData.TrapIndex = aIndex;
			}
			break;
		case 72:
			{
				this->m_BattleOfGaion.m_BattleData.TrapIndex = aIndex;
			}
			break;
	}
}

bool CImperial::UsePortalGate(LPOBJ lpObj, int gt)
{
	switch ( gt )
	{
		case 308:
		case 309:
		case 310:
		case 311:
			{
				if(this->GetCurrentDay() == 1)
				{
					return this->m_BattleOfDestler.EnterPortal(lpObj);		
				}
				else if(this->GetCurrentDay() == 4)
				{
					return this->m_BattleOfGalia.EnterPortal(lpObj);
				}
			}
			break;
		case 313:
		case 314:
		case 315:
		case 316:
			{
				if(this->GetCurrentDay() == 2)
				{
					return this->m_BattleOfVermont.EnterPortal(lpObj);
				}
				else if(this->GetCurrentDay() == 5)
				{
					return this->m_BattleOfErkanne.EnterPortal(lpObj);
				}
			}
			break;
		case 318:
		case 319:
		case 320:
		case 321:
			{
				if(this->GetCurrentDay() == 3)
				{
					return this->m_BattleOfKato.EnterPortal(lpObj);
				}
				else if(this->GetCurrentDay() == 6)
				{
					return this->m_BattleOfRaymond.EnterPortal(lpObj);
				}
			}
			break;
		case 323:
		case 324:
		case 325:
		case 326:
		case 327:
		case 328:
			{
				if(this->GetCurrentDay() == 7)
				{
					return this->m_BattleOfGaion.EnterPortal(lpObj);
				}
			}
			break;
	}
}

int CImperial::GetSpecificState()
{
	switch ( this->m_ImperialData.Day )
	{
		case 1:
			return this->m_BattleOfDestler.m_BattleData.CurrentState;
		case 2:
			return this->m_BattleOfVermont.m_BattleData.CurrentState;
		case 3:
			return this->m_BattleOfKato.m_BattleData.CurrentState;
		case 4:
			return this->m_BattleOfGalia.m_BattleData.CurrentState;
		case 5:
			return this->m_BattleOfErkanne.m_BattleData.CurrentState;
		case 6:
			return this->m_BattleOfRaymond.m_BattleData.CurrentState;
		case 7:
			return this->m_BattleOfGaion.m_BattleData.CurrentState;
	}
}

int CImperial::GiveRewardExp(int aIndex, int Exp)
{
	if ( !gObjIsConnected(aIndex))
		return 0;

	if ( Exp <= -1 )
		return 0;

	int iRET_EXP = 0;
	int iCAL_EXP = Exp;
	int iMAX_LEVCOUNT = 0;

	if ( !gObjIsConnected(aIndex))
		return 0;

	iRET_EXP = iCAL_EXP;

	if ( gObj[aIndex].Type == OBJ_USER )
	{
		while ( iCAL_EXP > 0 )
		{
			if ( iCAL_EXP > 0 )
			{
				iCAL_EXP = this->LevelUp(aIndex, iCAL_EXP);
			}

			iMAX_LEVCOUNT++;

			if ( iMAX_LEVCOUNT > 5 )
			{
				LogAddTD("[ IMPERIAL FORT ][GiveRewardExp] LevelUp Error [%s][%s]",
					gObj[aIndex].AccountID, gObj[aIndex].Name);

				break;
			}
		}

		PMSG_KILLPLAYER_EXT pMsg;

		PHeadSetBE((LPBYTE)&pMsg, 0x9C, sizeof(pMsg));
		pMsg.NumberH = -1;
		pMsg.NumberL = -1;
		pMsg.ExpH = SET_NUMBERHW(Exp);
		pMsg.ExpL = SET_NUMBERLW(Exp);
		pMsg.DamageH = 0;
		pMsg.DamageL = 0;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

		PMSG_FORT_END_MESSAGE pExp = {0};
		PHeadSubSetB((LPBYTE)&pExp, 0xF7, 0x06, sizeof(pExp));
		pExp.Type = 2;
		pExp.Experience = Exp;
		DataSend(aIndex, (LPBYTE)&pExp, pExp.h.size);
	}
	return 1;
}

int CImperial::LevelUp(int iUserIndex, int iAddExp)
{
	if ( !OBJMAX_RANGE(iUserIndex ) )
		return 0;

	int iLEFT_EXP = 0;

	LogAddTD("[ IMPERIAL FORT ][ ExpPrize ] : [%s][%s](%d) %u %d",
		gObj[iUserIndex].AccountID, gObj[iUserIndex].Name,
		gObj[iUserIndex].Level, gObj[iUserIndex].Experience,
		iAddExp);

	if ( MasterLevelSystem.CanGainMasterExp(&gObj[iUserIndex]))
	{
		return MasterLevelSystem.LevelUp(&gObj[iUserIndex], iAddExp, 0, 5);
	}

	LogAddTD("Experience : Map[%d]-(%d,%d) [%s][%s](%d) %u %d MonsterIndex : %d, EventType : %d",
		gObj[iUserIndex].MapNumber, gObj[iUserIndex].X, gObj[iUserIndex].Y,
		gObj[iUserIndex].AccountID, gObj[iUserIndex].Name,
		gObj[iUserIndex].Level, gObj[iUserIndex].Experience, iAddExp, 0, EVENT_TYPE_CRYWOLF);

	gObjSetExpPetItem(iUserIndex, iAddExp);

	if ( gObj[iUserIndex].Level >= MAX_CHAR_LEVEL )
	{
		GCServerMsgStringSend("You have reached max level", gObj[iUserIndex].m_Index, 1);
		return 0;
	}

	if ( (gObj[iUserIndex].Experience + iAddExp) < gObj[iUserIndex].NextExp )
	{
		gObj[iUserIndex].Experience += iAddExp;
	}
	else
	{
		iLEFT_EXP = gObj[iUserIndex].Experience + iAddExp - gObj[iUserIndex].NextExp;
		gObj[iUserIndex].Experience = gObj[iUserIndex].NextExp;
		gObj[iUserIndex].Level++;

		if ( gObj[iUserIndex].Class == CLASS_DARKLORD || gObj[iUserIndex].Class == CLASS_MAGUMSA )
		{
			gObj[iUserIndex].LevelUpPoint += 7;
		}
		else
		{
			gObj[iUserIndex].LevelUpPoint += 5;
		}

		if ( gObj[iUserIndex].PlusStatQuestClear != false )
		{
			gObj[iUserIndex].LevelUpPoint++;

			LogAddTD("[ IMPERIAL FORT ][ ExpPrize ] [%s][%s] LevelUp PlusStatQuest Clear AddStat %d",
				gObj[iUserIndex].AccountID, gObj[iUserIndex].Name,
				gObj[iUserIndex].LevelUpPoint);
		}

		gObj[iUserIndex].MaxLife += DCInfo.DefClass[gObj[iUserIndex].Class].LevelLife;
		gObj[iUserIndex].MaxMana += DCInfo.DefClass[gObj[iUserIndex].Class].LevelMana;
		gObj[iUserIndex].Life = gObj[iUserIndex].MaxLife;
		gObj[iUserIndex].Mana = gObj[iUserIndex].MaxMana;
		gObjNextExpCal(&gObj[iUserIndex]);
		gObjSetBP(gObj[iUserIndex].m_Index);
		GCLevelUpMsgSend(gObj[iUserIndex].m_Index, 1);
		gObjCalcMaxLifePower(gObj[iUserIndex].m_Index);
	}

	return iLEFT_EXP;
}

void CImperial::SendFailMessage(int aIndex)
{
	PMSG_FORT_END_MESSAGE pMsg = {0};
	pMsg.Type = 0;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}