#include "StdAfx.h"
#include "RaklionEvent.h"
#include "user.h"
#include "logproc.h"
#include "GameMain.h"
CRaklionEvent g_Raklion;
DWORD tick;
CRaklionEvent::CRaklionEvent()
{
	this->m_iBattleState = 0;
	this->m_iMinutesLeft = 60;
	this->m_iEntrantCount = 0;
	this->BlockBossEntry = 1;
	tick = GetTickCount();
	this->m_iLiveEggCount = 0;
	this->m_iLiveSerupinCount = 0;
	this->m_iLiveSpiderCount = 0;
	
}

CRaklionEvent::~CRaklionEvent()
{
	
}

bool CRaklionEvent::isRunning()
{
	return this->m_iBattleState;
}

void CRaklionEvent::EnterEvent(int aIndex)
{
	if(this->m_iBattleState != RAKLION_NOTIFY)
	{
		LogAddC(2,"[ERROR] User try to enter raklion without event being active");
		return;
	}
	if(this->m_iEntrantCount > 9)
	{
		LogAddC(2,"[ERROR] Hatchery is Full");
		return;
	}

	if(gObj[aIndex].Money < 1000000)
	{
		GCServerMsgStringSend("You need 1M Zen to enter",aIndex,1);
		return;
	}
	gObj[aIndex].Money -= 1000000;
	GCMoneySend(aIndex,gObj[aIndex].Money);
	this->indexEntrants[this->m_iEntrantCount] = aIndex;
	this->m_iEntrantCount++;
	LogAddC(5,"[%d][%s][%s] Enter Raklion Hatchery !",
		aIndex,gObj[aIndex].AccountID,gObj[aIndex].Name);
	return;
}

void CRaklionEvent::StartEvent()
{

	if(this->m_iEntrantCount < 1)
	{
			LogAddC(5, "[ RAKLION ][ BattleOfSerupin ] Event Start Fail [No Users]");
			this->SetState_END();
			return;
	}
	this->SetState_PHAZE1();
	//139-147


}


void CRaklionEvent::Run()
{
	if(!g_isRaklionEvent)
	{
		return;
	}

	this->CheckTime();

	if(this->m_iBattleState == RAKLION_PHAZE1)
	{
		if(this->m_iLiveSpiderCount == 0)
			this->SetState_PHAZE2();
	}
	if(this->m_iBattleState == RAKLION_PHAZE2)
	{
		if(this->m_iLiveEggCount == 0)
			this->SetState_PHAZE3();
	}
	if(this->m_iBattleState == RAKLION_PHAZE3)
	{
		if(this->m_iLiveSerupinCount == 0)
			this->SetState_END();
	}
	if(this->m_iBattleState == RAKLION_END)
	{
		this->SetState(RAKLION_NONE);
		this->m_iMinutesLeft = 60;
		this->m_iEntrantCount = 0;
		this->BlockBossEntry = 1;
		tick = GetTickCount();
		this->m_iLiveEggCount = 0;
		this->m_iLiveSerupinCount = 0;
		this->m_iLiveSpiderCount = 0;
		for(int i=0;i<10;i++)
			this->indexEntrants[i] = -1;

	}
	if(this->m_iBattleState >= RAKLION_PHAZE1)
	{
		for(int i=0;i<this->m_iEntrantCount;i++)
		{
			if(gObj[this->indexEntrants[i]].MapNumber != MAP_INDEX_RAKLIONBOSS)
			{
				this->m_iEntrantCount--;
				LogAddC(0,"[%s][%s] Leave raklion map -> disqualified from event",
					gObj[indexEntrants[i]].AccountID,gObj[indexEntrants[i]].Name);
			}
		}
		if(this->m_iEntrantCount == 0)
		{
			this->SetState_END();
			LogAddC(5,"[ RAKLION ] [ BattleOfSerupin ] End -> NO USERS LEFT");
		}
	}

}

void CRaklionEvent::SetState(int iBattleState)
{
	switch ( iBattleState )
	{
		case RAKLION_NONE:
			this->SetState_NONE();
			break;
		case RAKLION_START:
			this->SetState_START();
			break;
		case RAKLION_NOTIFY:
			this->SetState_NOTIFY();
			break;
		case RAKLION_END:
			this->SetState_END();
			break;
		case RAKLION_PHAZE1:
			this->SetState_PHAZE1();
			break;
		case RAKLION_PHAZE2:
			this->SetState_PHAZE2();
			break;
		case RAKLION_PHAZE3:
			this->SetState_PHAZE3();
			break;
		default:
			LogAddC(2,"[ RAKLION ] Bad State (%d)",iBattleState);
			break;
	}
}

void CRaklionEvent::SetState_NONE()
{
	LogAddC(5, "[ RAKLION ][ BattleOfSerupin ] State(%d) -> NONE",
		this->m_iBattleState);

	this->SetBattleState(RAKLION_NONE);
}



void CRaklionEvent::SetState_START()
{
	LogAddC(5, "[ RAKLION ][ BattleOfSerupin ] State(%d) -> START",
		this->m_iBattleState);
	this->BlockBossEntry = true;

	this->SetBattleState(RAKLION_START);
	this->StartEvent();
}


void CRaklionEvent::SetState_NOTIFY()
{
	LogAddC(5, "[ RAKLION ][ BattleOfSerupin ] State(%d) -> NOTIFY",
		this->m_iBattleState);
	this->BlockBossEntry = false;
	this->SetBattleState(RAKLION_NOTIFY);
}


void CRaklionEvent::SetState_END()
{
	LogAddC(5, "[ RAKLION ][ BattleOfSerupin ] State(%d) -> END",
		this->m_iBattleState);
	tick = GetTickCount();
	this->SetBattleState(RAKLION_END);
}

void CRaklionEvent::SetState_PHAZE1()
{
	LogAddC(5, "[ RAKLION ][ BattleOfSerupin ] State(%d) -> PHAZE1",
		this->m_iBattleState);
	tick = GetTickCount();
	this->SetBattleState(RAKLION_PHAZE1);
	this->GenerateMonster(RAKLION_PHAZE1);
	for(int i=-1;i<=this->m_iEntrantCount;i++)
	{
		GCServerMsgStringSend("PHAZE 1: KILL ALL SPIDERS!",i,0);
	}

}

void CRaklionEvent::SetState_PHAZE2()
{
	LogAddC(5, "[ RAKLION ][ BattleOfSerupin ] State(%d) -> PHAZE2",
		this->m_iBattleState);
	tick = GetTickCount();
	this->SetBattleState(RAKLION_PHAZE2);
	this->GenerateMonster(RAKLION_PHAZE2);
	for(int i=0;i<=this->m_iEntrantCount;i++)
	{
		GCServerMsgStringSend("PHAZE 2: KILL ALL EGGS!",i,0);
	}
}

void CRaklionEvent::SetState_PHAZE3()
{
	LogAddC(5, "[ RAKLION ][ BattleOfSerupin ] State(%d) -> PHAZE3",
		this->m_iBattleState);
	tick = GetTickCount();
	this->SetBattleState(RAKLION_PHAZE3);
	this->GenerateMonster(RAKLION_PHAZE3);
	for(int i=0;i<=this->m_iEntrantCount;i++)
	{
		GCServerMsgStringSend("PHAZE 3: KILL ALL SERUPIN TO FINISH!",i,0);
	}
}

void CRaklionEvent::CheckTime()
{
	if(this->m_iBattleState >= RAKLION_PHAZE1)
	{
		return;
	}
	DWORD TickNow = GetTickCount();
	DWORD calcTime = TickNow-tick;
	if(calcTime >= 1000*60*60) // notify when time to enter has passed
	{
		AllSendServerMsg("Raklion Hatchery Entry Closed");
		this->SetState_START();
	}
	if(calcTime >= 1000*60*45 && this->m_iBattleState == RAKLION_NONE) // notify 15 min before start
	{
		AllSendServerMsg("Raklion Hatchery Opens in 15 Minutes!");
		this->SetState_NOTIFY();
	}

	return;
}

void CRaklionEvent::Init()
{
	this->SetState(RAKLION_NONE);
}

void CRaklionEvent::MonsterManager(int aIndex)
{
	switch(gObj[aIndex].Class)
	{
	case 457:
		{
			this->delMonster(aIndex);
			this->m_iLiveSpiderCount--;
		}
		break;
	case 462:
		{
			this->delMonster(aIndex);
			this->m_iLiveEggCount--;
		}
		break;
	case 459:
		{
			this->delMonster(aIndex);
			this->m_iLiveSerupinCount--;
		}
		break;
	default:
		LogAddC(2,"[ERROR] Wrong monster type in Raklion boss map");
		break;

	}
}

void CRaklionEvent::GenerateMonster(int Phaze)
{
	int id;
	switch(Phaze)
	{
	case RAKLION_PHAZE1:
		{
			for(int i=0;i<20;i++)
				{
					//srand(time(NULL));
					id = gObjAddMonster(MAP_INDEX_RAKLIONBOSS);
					gObjSetMonster(id,457);
					gObj[id].X = 150+rand()%10;
					gObj[id].Y = 25+rand()%5;
					gObj[id].MapNumber = MAP_INDEX_RAKLIONBOSS;
					gObj[id].m_MoveRange = 30;
					this->m_iLiveSpiderCount++;
				}
		}
		break;
	case RAKLION_PHAZE2:
		{
			for(int i=0;i<15;i++)
				{
					//srand(time(NULL));
					id = gObjAddMonster(MAP_INDEX_RAKLIONBOSS);
					gObjSetMonster(id,462);
					gObj[id].X = 150+rand()%10;
					gObj[id].Y = 25+rand()%5;
					gObj[id].MapNumber = MAP_INDEX_RAKLIONBOSS;
					gObj[id].m_MoveRange = 30;
					this->m_iLiveEggCount++;

				}
		}
		break;
	case RAKLION_PHAZE3:
		{
			for(int i=0;i<3;i++)
			{
				//srand(time(NULL));
				id = gObjAddMonster(MAP_INDEX_RAKLIONBOSS);
				gObjSetMonster(id,459);
				gObj[id].X = 150+rand()%10;
				gObj[id].Y = 25+rand()%5;
				gObj[id].MapNumber = MAP_INDEX_RAKLIONBOSS;
				gObj[id].m_MoveRange = 30;
				this->m_iLiveSerupinCount++;
			}
		}
		break;
	}
}

void CRaklionEvent::delMonster(int Index)
{
	gObjDel(Index);
}