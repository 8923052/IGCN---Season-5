#include "stdafx.h"
#include "user.h"
#include "BossAttackEvent.h"
#include "GameMain.h"
#include "protocol.h"
#include "logproc.h"
#include "DSProtocol.h"

CBossAttack g_BossAttack;

void CBossAttack::Init()
{
	for(int i=0;i<BOSS_MAXMONSTER;i++)
	{
		this->m_MonsterData[i].bIsAlive = -1;
		this->m_MonsterData[i].iClass = -1;
		this->m_MonsterData[i].iHeroMonster = -1;
		this->m_MonsterData[i].iIndex = -1;
		this->m_MonsterData[i].Count = -1;
		this->STATE = 0;

	}
}

int CBossAttack::GetActiveMonsterCount()
{
	int alive = 0;
	for(int i=0;i<BOSS_MAXMONSTER;i++)
	{
		if(this->m_MonsterData[i].bIsAlive == 1)
		{
			alive++;
		}
	}
	return alive;
}