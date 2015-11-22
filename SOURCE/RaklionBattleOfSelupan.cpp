#include "stdafx.h"
#include "RaklionBattleOfSelupan.h"
#include "RaklionUtil.h"
#include "RaklionBattleUserMng.h"
#include "Raklion.h"
#include "GameMain.h"
#include "GameServer.h"
#include "gObjMonster.h"
#include "user.h"
#include "logproc.h"
#include "Protocol.h"
#include "..\common\winutil.h"
#include "TMonsterSkillManager.h"
#include "TNotice.h"

static CRaklionUtil RAKLION_UTIL;

CRaklionBattleOfSelupan::CRaklionBattleOfSelupan()
{
	this->m_iObjDamageMax = 0;
	this->m_iObjDamageMin = 0;
	this->m_iObjSelupanIndex = -1;
	this->m_iSkillDelay = 0;
	this->m_iSelupanSkillDelay = -1;
	this->m_bSelupanAppear = false;
	memset(&this->m_tiPatternCondition, 0x00, 6);
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_NONE);

}

CRaklionBattleOfSelupan::~CRaklionBattleOfSelupan()
{

}

void CRaklionBattleOfSelupan::UseFirstSkill()
{
	int iIndex = this->GetSelupanIndex();
	int iTargetIndex = iIndex;
	TMonsterSkillManager::UseMonsterSkill(iIndex, iTargetIndex, 31, 0, NULL);
	LogAddTD("[Raklion][FirstSkill] Skill Using: Index(%d) %s", iIndex, gObj[iIndex].Name);
}

void CRaklionBattleOfSelupan::UsePoisonAttack()
{
	int iIndex = this->GetSelupanIndex();
	int iTargetIndex = this->GetSelupanEnemy();
	if(iTargetIndex == -1)
	{
		TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 1, 7, NULL);
	}
	else
	{
		TMonsterSkillManager::UseMonsterSkill(iIndex, iTargetIndex, 1, 1, NULL);
	}
	LogAddTD("[Raklion][PoisonAttack] Skill Using: Index(%d) %s", iIndex, gObj[iIndex].Name);
}

void CRaklionBattleOfSelupan::UseIceStorm()
{
	int iIndex = this->GetSelupanIndex();
	int iTargetIndex = this->GetSelupanEnemy();
	if(iTargetIndex == -1)
	{
		TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 1, 7, NULL);
	}
	else
	{
		TMonsterSkillManager::UseMonsterSkill(iIndex, iTargetIndex, 1, 2, NULL);
	}
	LogAddTD("[Raklion][IceStorm] Skill Using: Index(%d) %s", iIndex, gObj[iIndex].Name);
}

void CRaklionBattleOfSelupan::UseIceStrike()
{
	int iIndex = this->GetSelupanIndex();
	int iTargetIndex = this->GetSelupanEnemy();
	if(iTargetIndex == -1)
	{
		TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 1, 7, NULL);
	}
	else
	{
		TMonsterSkillManager::UseMonsterSkill(iIndex, iTargetIndex, 1, 3, NULL);
	}
	LogAddTD("[Raklion][IceStrike] Skill Using: Index(%d) %s", iIndex, gObj[iIndex].Name);
}

void CRaklionBattleOfSelupan::UseSummon()
{
	int iIndex = this->GetSelupanIndex();
	TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 30, 4, NULL);
	this->SummonMonster();
	LogAddTD("[Raklion][SummonMonster] Skill Using: Index(%d) %s", iIndex, gObj[iIndex].Name);
}
void CRaklionBattleOfSelupan::UseHeal()
{
	int iIndex = this->GetSelupanIndex();
	TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 20, 5, NULL);
	LogAddTD("[Raklion][Heal] Skill Using : Index(%d) %s", iIndex, gObj[iIndex].Name);
}

void CRaklionBattleOfSelupan::UseFreeze()
{
	int iIndex = this->GetSelupanIndex();
	int iTargetIndex = this->GetSelupanEnemy();
	if(iTargetIndex == -1)
	{
		TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 1, 7, NULL);
	}
	else
	{
		TMonsterSkillManager::UseMonsterSkill(iIndex, iTargetIndex, 1, 6, NULL);
	}
	LogAddTD("[Raklion][Freeze] Skill Using : Index(%d) %s", iIndex, gObj[iIndex].Name);
}
void CRaklionBattleOfSelupan::UseTeleport()
{
	int iIndex = this->GetSelupanIndex();
	int iTargetIndex = this->GetSelupanEnemy();
	if(iTargetIndex == -1)
	{
		iTargetIndex = iIndex;
	}
	TMonsterSkillManager::UseMonsterSkill(iIndex, iTargetIndex, 1, 7, NULL);
	LogAddTD("[Raklion][Teleport] Skill Using : Index(%d) %s", iIndex, gObj[iIndex].Name);
}
void CRaklionBattleOfSelupan::UseInvisibility()
{
	int iIndex = this->GetSelupanIndex();
	TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 10, 8, NULL);
	LogAddTD("[Raklion][Invisibility] Skill Using : Index(%d) %s", iIndex, gObj[iIndex].Name);
}
void CRaklionBattleOfSelupan::UseBerserkerCancel()
{
	int iIndex = this->GetSelupanIndex();
	LPOBJ lpObj = &gObj[iIndex];
	lpObj->m_AttackDamageMin = this->m_iObjDamageMin;
	lpObj->m_AttackDamageMax = this->m_iObjDamageMax;
	LogAddTD("[Raklion][Berserk Cancel] MinDamage(%d) Damage(%d~%d)", lpObj->m_AttackDamageMin, lpObj->m_AttackDamageMin, lpObj->m_AttackDamageMax);
}
void CRaklionBattleOfSelupan::UseBerserker1()
{
	int iIndex = this->GetSelupanIndex();
	LPOBJ lpObj = &gObj[iIndex];
	TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 1, 9, NULL);
	this->m_iSkillBerserker = 1;
	int IncDamage = lpObj->m_MonsterSkillElementInfo.m_iSkillElementAttack * this->m_iSkillBerserker;
	lpObj->m_AttackDamageMin = IncDamage + this->m_iObjDamageMin;
	lpObj->m_AttackDamageMax = IncDamage + this->m_iObjDamageMax;
	LogAddTD("[Raklion][Berserk 1] Skill Using: Index(%d) Damage(%d~%d)", iIndex, lpObj->m_AttackDamageMin, lpObj->m_AttackDamageMax);
}
void CRaklionBattleOfSelupan::UseBerserker2()
{
	int iIndex = this->GetSelupanIndex();
	LPOBJ lpObj = &gObj[iIndex];
	TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 1, 9, NULL);
	this->m_iSkillBerserker = 2;
	int IncDamage = lpObj->m_MonsterSkillElementInfo.m_iSkillElementAttack * this->m_iSkillBerserker;
	lpObj->m_AttackDamageMin = IncDamage + this->m_iObjDamageMin;
	lpObj->m_AttackDamageMax = IncDamage + this->m_iObjDamageMax;
	LogAddTD("[Raklion][Berserk 2] Skill Using: Index(%d) Damage(%d~%d)", iIndex, lpObj->m_AttackDamageMin, lpObj->m_AttackDamageMax);
}
void CRaklionBattleOfSelupan::UseBerserker3()
{
	int iIndex = this->GetSelupanIndex();
	LPOBJ lpObj = &gObj[iIndex];
	TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 1, 9, NULL);
	this->m_iSkillBerserker = 3;
	int IncDamage = lpObj->m_MonsterSkillElementInfo.m_iSkillElementAttack * this->m_iSkillBerserker;
	lpObj->m_AttackDamageMin = IncDamage + this->m_iObjDamageMin;
	lpObj->m_AttackDamageMax = IncDamage + this->m_iObjDamageMax;
	LogAddTD("[Raklion][Berserk 3] Skill Using: Index(%d) Damage(%d~%d)", iIndex, lpObj->m_AttackDamageMin, lpObj->m_AttackDamageMax);
}
void CRaklionBattleOfSelupan::UseBerserker4()
{
	int iIndex = this->GetSelupanIndex();
	LPOBJ lpObj = &gObj[iIndex];
	TMonsterSkillManager::UseMonsterSkill(iIndex, iIndex, 1, 9, NULL);
	this->m_iSkillBerserker = 4;
	int IncDamage = lpObj->m_MonsterSkillElementInfo.m_iSkillElementAttack * this->m_iSkillBerserker;
	lpObj->m_AttackDamageMin = IncDamage + this->m_iObjDamageMin;
	lpObj->m_AttackDamageMax = IncDamage + this->m_iObjDamageMax;
	LogAddTD("[Raklion][Berserk 4] Skill Using: Index(%d) Damage(%d~%d)", iIndex, lpObj->m_AttackDamageMin, lpObj->m_AttackDamageMax);
}
bool CRaklionBattleOfSelupan::CreateSelupan()
{
	int iTableNum = -1;
	int iIndex;

	for(int i=0;i<gMSetBase.m_Count;++i)
	{
		if(gMSetBase.m_Mp[i].m_Type == 459) // Selupan
		{
			iTableNum = i;
			break;
		}
	}

	if(iTableNum == -1)
	{
		LogAddC(2, "[Raklion] CreateSelupan error");
		return 0;
	}

	iIndex = gObjAddMonster(MAP_INDEX_RAKLIONBOSS);
	if(iIndex >= 0)
	{
		LPOBJ lpSelupanObj = &gObj[iIndex];
		gObjSetPosMonster(iIndex, iTableNum);
		gObjSetMonster(iIndex, 459); // Selupan
		LogAddTD("[Raklion] Create Selupan : X (%d) / Y(%d)", lpSelupanObj->X, lpSelupanObj->Y);
		for(int j=0;j<OBJMAX;++j)
		{
			if(gObj[j].MapNumber == MAP_INDEX_RAKLIONBOSS )
				gObjStateSetCreate(j);
		}
		for(int k=0;k<OBJMAX;++k)
		{
			if(gObj[k].MapNumber == MAP_INDEX_RAKLIONBOSS )
				gObjViewportListDestroy(k);
		}
		for(int j=0;j<OBJMAX;++j)
		{
			if(gObj[j].MapNumber == MAP_INDEX_RAKLIONBOSS )
				gObjViewportListCreate(j);
		}
		for(int j=0;j<OBJMAX;++j)
		{
			if(gObj[j].MapNumber == MAP_INDEX_RAKLIONBOSS )
				gObjViewportListProtocol(j);
		}
		gObjSetState();
		this->m_iObjDamageMin = lpSelupanObj->m_AttackDamageMin;
		this->m_iObjDamageMax = lpSelupanObj->m_AttackDamageMax;
		this->m_bSelupanAppear = false;
		return 1;
	}
	else
	{
		LogAddC(2, "[Raklion] CreateSelupan error");
		return 0;
	}
	return 0;
}
void CRaklionBattleOfSelupan::InitSelupanIndex()
{
	for(int i=0;i<OBJ_MAXMONSTER;++i)
	{
		if(gObj[i].Connected == PLAYER_PLAYING)
		{
			if(gObj[i].Class == 459) // SELUPAN
			{
				this->m_iObjSelupanIndex = i;
				return;
			}
		}
	}
	if(this->m_iObjSelupanIndex == -1)
	{
		LogAddC(2, "[Raklion][InitSelupanIndex] error : SelupanObjIndex(%d)", this->m_iObjSelupanIndex);
	}
}
int CRaklionBattleOfSelupan::GetSelupanSkillDelay()
{
	if(this->m_iSelupanSkillDelay < 0 || this->m_iSelupanSkillDelay > 50000)
	{
		LogAddC(2, "[Raklion][GetSelupanSkillDelay] SkillDelay error: Delay(%d)",
			this->m_iSelupanSkillDelay);
		return -1;
	}
	else return this->m_iSelupanSkillDelay;
}
void CRaklionBattleOfSelupan::SetSelupanSkillDelay(int iSkillDelay)
{
	if(iSkillDelay < 0 || iSkillDelay > 50000)
	{
		LogAddC(2, "[Raklion][SetSelupanSkillDelay] SkillDelay error: Delay(%d)",
			this->m_iSelupanSkillDelay);
		return;
	}
	this->m_iSelupanSkillDelay = iSkillDelay;
}
void CRaklionBattleOfSelupan::SummonMonster()
{
	LPOBJ lpObj;
	int iTableNum;
	int iClass;
	int iIndex;
	for (int i=0;i<OBJ_MAXMONSTER;++i)
	{
		lpObj = &gObj[i];
		if(lpObj->MapNumber == MAP_INDEX_RAKLIONBOSS && (lpObj->Class == 457 || lpObj->Class == 458) && (lpObj->Connected != PLAYER_PLAYING || lpObj->DieRegen || !lpObj->Live))
		{
			iClass = lpObj->Class;
			iTableNum = lpObj->m_PosNum;
			lpObj->Class = 0;
			iIndex = gObjAddMonster(MAP_INDEX_RAKLIONBOSS);
			if(iIndex < 0)
			{
				LogAddC(2, "[Raklion] CreateSelupan error");
				return;
			}
			gObjSetPosMonster(iIndex, iTableNum);
			gObjSetMonster(iIndex, iClass);
			lpObj->Live = TRUE;
			lpObj->DieRegen = FALSE;
			LogAddTD("[Raklion] Summoned Monster: %s => X-(%d) Y-(%d)", lpObj->Name, lpObj->X, lpObj->Y);
		}
	}	
}
void CRaklionBattleOfSelupan::DeleteSelupan()
{
	int iIndex = this->GetSelupanIndex();
	if(!OBJMAX_RANGE(iIndex))
	{
		return;
	}
	LPOBJ lpObj = &gObj[iIndex];

	gObjViewportListProtocolDestroy(lpObj);
	gObjViewportClose(lpObj);
	gObjDel(lpObj->m_Index);
}

void CRaklionBattleOfSelupan::DeleteSummonMonster()
{
	LPOBJ lpObj;
	for(int i=0;i<OBJ_MAXMONSTER;++i)
	{
		lpObj = &gObj[i];
		if(lpObj->MapNumber == MAP_INDEX_RAKLIONBOSS && (lpObj->Class == 457 || lpObj->Class == 458))
		{
			gObjViewportListProtocolDestroy(lpObj);
			gObjViewportClose(lpObj);
			gObjDel(lpObj->m_Index);
			lpObj->Live = FALSE;
			lpObj->DieRegen = TRUE;
		}
	}
	LogAddC(5, "[Raklion][DeleteSummonMonster] Delete All Monster");
}

float CRaklionBattleOfSelupan::GetSelupanHP()
{
	return gObj[this->GetSelupanIndex()].Life;
}
int CRaklionBattleOfSelupan::GetSelupanIndex()
{
	this->InitSelupanIndex();
	return this->m_iObjSelupanIndex;
}
int CRaklionBattleOfSelupan::GetSelupanBerserker()
{
	return this->m_iSkillBerserker;
}
int CRaklionBattleOfSelupan::GetSelupanEnemy()
{
	int iIndex = this->GetSelupanIndex();
	if(gObj[iIndex].TargetNumber < 0 || gObj[iIndex].TargetNumber > OBJMAX)
	{
		gObjMonsterSearchEnemy(&gObj[iIndex], OBJ_MONSTER);
	}
	return gObj[iIndex].TargetNumber;
}
void CRaklionBattleOfSelupan::SetState_NONE()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> NONE", this->m_iBattleOfSelupanState);
	this->UseBerserkerCancel();
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_NONE);
}
void CRaklionBattleOfSelupan::SetState_STANDBY()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> STANDBY", this->m_iBattleOfSelupanState);
	this->InitSelupanIndex();
	this->CreateSelupan();
	this->UseBerserkerCancel();
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_STANDBY);
}
void CRaklionBattleOfSelupan::SetState_PATTERN1()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> PATTERN_1 // Life(%d/4800000)", this->m_iBattleOfSelupanState, (int)this->GetSelupanHP());
	this->UseBerserkerCancel();
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_PATTERN1);
}
void CRaklionBattleOfSelupan::SetState_PATTERN2()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> PATTERN_2 // Life(%d/4800000)", this->m_iBattleOfSelupanState, (int)this->GetSelupanHP());
	this->UseBerserker1();
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_PATTERN2);
}
void CRaklionBattleOfSelupan::SetState_PATTERN3()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> PATTERN_3 // Life(%d/4800000)", this->m_iBattleOfSelupanState, (int)this->GetSelupanHP());
	this->UseBerserker2();
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_PATTERN3);
}
void CRaklionBattleOfSelupan::SetState_PATTERN4()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> PATTERN_4 // Life(%d/4800000)", this->m_iBattleOfSelupanState, (int)this->GetSelupanHP());
	if(this->GetSelupanBerserker() != 2)
	{
		this->UseBerserker2();
	}
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_PATTERN4);
}
void CRaklionBattleOfSelupan::SetState_PATTERN5()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> PATTERN_5 // Life(%d/4800000)", this->m_iBattleOfSelupanState, (int)this->GetSelupanHP());
	this->UseBerserker3();
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_PATTERN5);
}
void CRaklionBattleOfSelupan::SetState_PATTERN6()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> PATTERN_6 // Life(%d/4800000)", this->m_iBattleOfSelupanState, (int)this->GetSelupanHP());
	this->UseBerserker4();
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_PATTERN6);
}
void CRaklionBattleOfSelupan::SetState_PATTERN7()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> PATTERN_7 // Life(%d/4800000)", this->m_iBattleOfSelupanState, (int)this->GetSelupanHP());
	if(this->GetSelupanBerserker() != 4)
	{
		this->UseBerserker4();
	}
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_PATTERN7);
}
void CRaklionBattleOfSelupan::SetState_DIE()
{
	LogAddC(5, "[Raklion][BattleOfSelupan] State(%d) -> DIE", this->m_iBattleOfSelupanState);
	this->UseBerserkerCancel();
	this->DeleteSummonMonster();
	int iTargetIndex = this->GetSelupanEnemy();
	SYSTEMTIME Time;
	GetLocalTime(&Time);
	for(int i=0; i < g_RaklionBattleUserMng.GetUserCount(); ++i)
	{
		LogAdd("[Raklion][SelupanDie] %d/%d/%d %d:%d:%d %dth Winner : %s (%s)",
			Time.wYear, Time.wMonth, Time.wDay, Time.wHour, Time.wMinute, Time.wSecond, i+1, gObj[g_RaklionBattleUserMng.m_BattleUser[i].GetIndex()].Name,
			gObj[g_RaklionBattleUserMng.m_BattleUser[i].GetIndex()].AccountID);
	}
	this->SetBattleOfSelupanState(RAKLION_SELUPAN_DIE);
}

void CRaklionBattleOfSelupan::SetPatternCondition(int iPatternCondition[6])
{
	for(int i=0;i<6;++i)
	{
		if(iPatternCondition[i] <= 0)
		{
			LogAddC(2, "[Raklion][SetPatternCondition] error : PatternNum(%d), Condition(%d)", i, iPatternCondition[i]);
			this->~CRaklionBattleOfSelupan();
			return;
		}
		this->m_tiPatternCondition[i] = iPatternCondition[i];
	}
}

void CRaklionBattleOfSelupan::ProcState_NONE()
{
	return;
}
void CRaklionBattleOfSelupan::ProcState_STANDBY()
{
	return;
}
void CRaklionBattleOfSelupan::ProcState_PATTERN1()
{
	int skill;
	while(true)
	{
		skill = rand()%9;
		if(this->m_tbSkillRule[skill][0] == true)
		{
			this->UseSelupanSkill(skill);
			return;
		}
	}
}
		
void CRaklionBattleOfSelupan::ProcState_PATTERN2()
{
	int skill;
	while(true)
	{
		skill = rand()%9;
		if(this->m_tbSkillRule[skill][1] == true)
		{
			this->UseSelupanSkill(skill);
			return;
		}
	}
}
void CRaklionBattleOfSelupan::ProcState_PATTERN3()
{
	int skill;
	while(true)
	{
		skill = rand()%9;
		if(this->m_tbSkillRule[skill][2] == true)
		{
			this->UseSelupanSkill(skill);
			return;
		}
	}
}
void CRaklionBattleOfSelupan::ProcState_PATTERN4()
{
	int skill;
	while(true)
	{
		skill = rand()%9;
		if(this->m_tbSkillRule[skill][3] == true)
		{
			this->UseSelupanSkill(skill);
			return;
		}
	}
}
void CRaklionBattleOfSelupan::ProcState_PATTERN5()
{
	int skill;
	while(true)
	{
		skill = rand()%9;
		if(this->m_tbSkillRule[skill][3] == true)
		{
			this->UseSelupanSkill(skill);
			return;
		}
	}
}
void CRaklionBattleOfSelupan::ProcState_PATTERN6()
{
	int skill;
	while(true)
	{
		skill = rand()%9;
		if(this->m_tbSkillRule[skill][5] == true)
		{
			this->UseSelupanSkill(skill);
			return;
		}
	}
}
void CRaklionBattleOfSelupan::ProcState_PATTERN7()
{
	int skill;
	while(true)
	{
		skill = rand()%9;
		if(this->m_tbSkillRule[skill][6] == true)
		{
			this->UseSelupanSkill(skill);
			return;
		}
	}
}
void CRaklionBattleOfSelupan::ProcState_DIE()
{
	return;
}
void CRaklionBattleOfSelupan::UseSelupanSkill(int iMonsterSkill)
{
	int iIndex = this->GetSelupanIndex();
	if(!gObjIsConnected(iIndex))
	{
		return;
	}
	if(!gObj[iIndex].Teleport)
	{
		if(!gObj[iIndex].m_ActState.Move)
		{
			if(iMonsterSkill >= 0)
			{
				if(iMonsterSkill < 9)
				{
					switch ( iMonsterSkill )
					{
						case 0:
							this->UseFirstSkill();
							break;
						case 1:
							this->UsePoisonAttack();
							break;
						case 2:
							this->UseIceStorm();
							break;
						case 3:
							this->UseIceStrike();
							break;
						case 4:
							this->SummonMonster();
							break;
						case 5:
							this->UseHeal();
							break;
						case 6:
							this->UseFreeze();
							break;
						case 7:
							this->UseTeleport();
							break;
						case 8:
							this->UseInvisibility();
							break;
					}
					this->m_iSkillDelay = GetTickCount();
				}
			}
		}
	}
}

void CRaklionBattleOfSelupan::SetSkillRule()
{
	for(int i=0;i<7;++i)
	{
		memset(&this->m_tbSkillRule[0][i], false, 9);
	}
	for(int i=0;i<7;++i)
	{
		this->m_tbSkillRule[1][i] = true;
		this->m_tbSkillRule[2][i] = true;
		this->m_tbSkillRule[3][i] = true;
		this->m_tbSkillRule[7][i] = true;
	}
	this->m_tbSkillRule[6][1] = true;
	this->m_tbSkillRule[6][2] = true;
	this->m_tbSkillRule[6][3] = true;
	this->m_tbSkillRule[6][4] = true;
	this->m_tbSkillRule[6][5] = true;
	this->m_tbSkillRule[6][6] = true;
	this->m_tbSkillRule[5][3] = true;
	this->m_tbSkillRule[5][4] = true;
	this->m_tbSkillRule[5][5] = true;
	this->m_tbSkillRule[5][6] = true;
	this->m_tbSkillRule[4][4] = true;
	this->m_tbSkillRule[4][5] = true;
	this->m_tbSkillRule[4][6] = true;
	this->m_tbSkillRule[8][6] = true;

	this->SetSuccessValue(FALSE);
}
void CRaklionBattleOfSelupan::Run()
{
	g_RaklionBattleUserMng.CheckUserState();
	int iIndex = this->GetSelupanIndex();

	if((gObj[iIndex].Life <= 0.0f || gObj[iIndex].Live == 0) && this->m_iBattleOfSelupanState != RAKLION_SELUPAN_DIE)
	{
		this->SetState(RAKLION_SELUPAN_DIE);
		return;
	}
	else
	{
		if(this->m_iSelupanSkillDelay < GetTickCount() - this->m_iSkillDelay && this->m_bSelupanAppear)
		{
			switch(this->m_iBattleOfSelupanState)
			{
				case RAKLION_SELUPAN_NONE:
					{
						this->ProcState_NONE();
						break;
					}
				case RAKLION_SELUPAN_STANDBY:
					{
						this->ProcState_STANDBY();
						break;
					}
				case RAKLION_SELUPAN_PATTERN1:
					{
						this->ProcState_PATTERN1();
						break;
					}
				case RAKLION_SELUPAN_PATTERN2:
					{
						this->ProcState_PATTERN2();
						break;
					}
				case RAKLION_SELUPAN_PATTERN3:
					{
						this->ProcState_PATTERN3();
						break;
					}
				case RAKLION_SELUPAN_PATTERN4:
					{
						this->ProcState_PATTERN4();
						break;
					}
				case RAKLION_SELUPAN_PATTERN5:
					{
						this->ProcState_PATTERN5();
						break;
					}
				case RAKLION_SELUPAN_PATTERN6:
					{
						this->ProcState_PATTERN6();
						break;
					}
				case RAKLION_SELUPAN_PATTERN7:
					{
						this->ProcState_PATTERN7();
						break;
					}
				case RAKLION_SELUPAN_DIE:
					{
						this->ProcState_DIE();
						break;
					}
			}
		}
	}
}

void CRaklionBattleOfSelupan::SetState(int iBattleOfSelupanState)
{
	if(this->m_iSelupanSkillDelay < GetTickCount() - this->m_iSkillDelay)
	{
		switch(iBattleOfSelupanState)
		{
			case RAKLION_SELUPAN_NONE:
				{
					this->SetState_NONE();
					break;
				}
			case RAKLION_SELUPAN_STANDBY:
				{
					this->SetState_STANDBY();
					break;
				}
			case RAKLION_SELUPAN_PATTERN1:
				{
					this->SetState_PATTERN1();
					break;
				}
			case RAKLION_SELUPAN_PATTERN2:
				{
					this->SetState_PATTERN2();
					break;
				}
			case RAKLION_SELUPAN_PATTERN3:
				{
					this->SetState_PATTERN3();
					break;
				}
			case RAKLION_SELUPAN_PATTERN4:
				{
					this->SetState_PATTERN4();
					break;
				}
			case RAKLION_SELUPAN_PATTERN5:
				{
					this->SetState_PATTERN5();
					break;
				}
			case RAKLION_SELUPAN_PATTERN6:
				{
					this->SetState_PATTERN6();
					break;
				}
			case RAKLION_SELUPAN_PATTERN7:
				{
					this->SetState_PATTERN7();
					break;
				}
			case RAKLION_SELUPAN_DIE:
				{
					this->SetState_DIE();
					break;
				}
			default:
				{
					break;
				}
		}
		RAKLION_UTIL.NotifyRaklionChangeState(RAKLION_SELUPAN_STATE_INFO, this->m_iBattleOfSelupanState);
	}
}
void CRaklionBattleOfSelupan::ManageSelupanHP()
{
	int iIndex = this->GetSelupanIndex();
	if(!gObjIsConnected(iIndex))
	{
		return;
	}
	if((gObj[iIndex].Life <= 0.0f || gObj[iIndex].Live == 0 || gObj[iIndex].DieRegen == TRUE) && this->m_iBattleOfSelupanState != RAKLION_SELUPAN_DIE)
	{
		this->SetState(RAKLION_SELUPAN_DIE);
		return;
	}
	if(this->m_iBattleOfSelupanState == RAKLION_SELUPAN_DIE)
	{
		return;
	}
	float fHP = gObj[iIndex].Life;
	float fPercent = (float)gObj[iIndex].Life / (float)gObj[iIndex].MaxLife * 100.0f;
	if(this->m_bSelupanAppear == false)
	{
		this->UseSelupanSkill(0);
		this->m_iSkillDelay = GetTickCount();
		this->m_bSelupanAppear = true;
		return;
	}
	if(fHP > 0.0f)
	{
		if(fPercent > 0.00)
		{
			if(fPercent < this->m_tiPatternCondition[0])
			{
				if(fPercent < this->m_tiPatternCondition[1])
				{
					if(fPercent < this->m_tiPatternCondition[2])
					{
						if(fPercent < this->m_tiPatternCondition[3])
						{
							if(fPercent < this->m_tiPatternCondition[4])
							{
								if(fPercent < this->m_tiPatternCondition[5])
								{
									if(this->m_iBattleOfSelupanState != RAKLION_SELUPAN_PATTERN7)
									{
										this->SetState(RAKLION_SELUPAN_PATTERN7);
									}
								}
								else
								{
									if(this->m_iBattleOfSelupanState != RAKLION_SELUPAN_PATTERN6)
									{
										this->SetState(RAKLION_SELUPAN_PATTERN6);
									}
								}
							}
							else
							{
								if(this->m_iBattleOfSelupanState != RAKLION_SELUPAN_PATTERN5)
								{
									this->SetState(RAKLION_SELUPAN_PATTERN5);
								}
							}
						}
						else
						{
							if(this->m_iBattleOfSelupanState != RAKLION_SELUPAN_PATTERN4)
							{
								this->SetState(RAKLION_SELUPAN_PATTERN4);
							}
						}
					}
					else
					{
						if(this->m_iBattleOfSelupanState != RAKLION_SELUPAN_PATTERN3)
						{
							this->SetState(RAKLION_SELUPAN_PATTERN3);
						}
					}
				}
				else
				{
					if(this->m_iBattleOfSelupanState != RAKLION_SELUPAN_PATTERN2)
					{
						this->SetState(RAKLION_SELUPAN_PATTERN2);
					}
				}
			}
			else
			{
				if(this->m_iBattleOfSelupanState != RAKLION_SELUPAN_PATTERN1)
				{
					this->SetState(RAKLION_SELUPAN_PATTERN1);
				}
			}
		}
		else
		{
			LogAddC(2, "[Raklion] SelupanLifePercent error : Index(%d), MaxLife(%d)",
				iIndex, gObj[iIndex].Life);
		}
	}
	else
	{
		LogAddC(2, "[Raklion] SelupanMaxLife error : Index(%d), MaxLife(%d)",
			iIndex, gObj[iIndex].MaxLife);
	}
}
									

