#include "stdafx.h"
#include "BossInv.h"
#include "user.h"
#include "GameMain.h"
#include "logproc.h"

BossInv cBossInv;

BossInv::BossInv()
{
	return;
}

BossInv::~BossInv()
{
	return;
}

void BossInv::Run()
{
	if(gBossInvasionRun == 1)
	{
		if(this->EventStartTime == 0)
		{
			tm * today;
			time_t ltime;

			time(&ltime);
			today = localtime(&ltime);

			DWORD Time = GetTickCount();
			this->EventStartTime = Time;
			LogAddTD("[Boss Invasion] State - Pending. Start After [%d] Minutes.",gBossInvasionStartMinute-1);
		}
	}
	else
	{
		if(this->STATE == 1) // alredy running
		return;

		DWORD Time = GetTickCount();
		if(( Time - this->EventStartTime ) > gXMasEventMinute * 60000)
		{
			LogAddC(2,"[Boss Invasion] Boss Invasion attacks MuTizens");
			this->MonsterInvade();
			this->EventStartTime = Time;
			this->STATE = 1;
		}
	}
		return;
}

void BossInv::MonsterInvade()
{

}

void BossInv::UserReward(LPOBJ lpObj)
{

}

void BossInv::End()
{

}