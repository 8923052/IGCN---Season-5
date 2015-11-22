#include "stdafx.h"
#include "DSProtocol.h"
#include "protocol.h"
#include "user.h"
#include "GameMain.h"
#include "MasterLevelSystem.h"
#include "LogProc.h"
#include "CrywolfSync.h"
#include "Crywolf.h"
#include "BloodCastle.h"
#include "ObjCalCharacter.h"
#include "..\common\winutil.h"
CMasterSkillSystem MasterLevelSystem;
CMasterSkillSystem::CMasterSkillSystem()
{
}
CMasterSkillSystem::~CMasterSkillSystem()
{
}
void CMasterSkillSystem::SetInfo(int MasterLevel, int MasterPoint, __int64 MasterExp, __int64 MasterNextExp, int aIndex)
{
	PMSG_MASTER_INFO_SEND pMsg;
	PHeadSubSetB((LPBYTE)&pMsg, 0xF3, 0x50, sizeof(pMsg));
	gObj[aIndex].m_uMasterLevel = MasterLevel;
	gObj[aIndex].m_uMasterPoints = MasterPoint;
	gObj[aIndex].m_uMasterExp = MasterExp;
	gObj[aIndex].m_uMasterNextExp = MasterNextExp;
	pMsg.MasterExp = this->ExpConvert(MasterExp);
	pMsg.MasterNextExp = this->ExpConvert(MasterNextExp);
	pMsg.MasterLevel = MasterLevel;
	pMsg.MasterPoint = MasterPoint;
	pMsg.MaxLife = gObj[aIndex].MaxLife + gObj[aIndex].AddLife;
	pMsg.MaxMana = gObj[aIndex].MaxMana + gObj[aIndex].AddMana;
	pMsg.MaxBP = gObj[aIndex].MaxBP + gObj[aIndex].AddBP;
	pMsg.MaxShield = gObj[aIndex].iMaxShield + gObj[aIndex].iAddShield;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}
void CMasterSkillSystem::Init(int aIndex)
{
	gObj[aIndex].MasterSkillTreeEffect.IncreaseDefense = 0;
	gObj[aIndex].MasterSkillTreeEffect.RepairLevel1 = 0;
	gObj[aIndex].MasterSkillTreeEffect.RepairLevel2 = 0;
	gObj[aIndex].MasterSkillTreeEffect.IncreaseExperience = 0;
	gObj[aIndex].MasterSkillTreeEffect.IncreaseRecoverLife = 0;
	gObj[aIndex].MasterSkillTreeEffect.IceResistance = 0;
	gObj[aIndex].MasterSkillTreeEffect.LightningResistance = 0;
	gObj[aIndex].MasterSkillTreeEffect.PoisonResistance = 0;
	gObj[aIndex].MasterSkillTreeEffect.IncreaseMaxAG = 0;
	gObj[aIndex].MasterSkillTreeEffect.IncreaseMaxHP = 0;
	gObj[aIndex].MasterSkillTreeEffect.IncreaseMaxDamage = 0;
	gObj[aIndex].MasterSkillTreeEffect.IncreaseManaReduction = 0;
	gObj[aIndex].MasterSkillTreeEffect.IncreaseMaxSD = 0;
	gObj[aIndex].MasterSkillTreeEffect.DecreasePetDurabilityWane = 0;
	//gObj[aIndex].MasterSkillTreeEffect. = 0;
	gObj[aIndex].MasterSkillTreeEffect.AdvancedAttackSuccessRate = 0;
	gObj[aIndex].MasterSkillTreeEffect.AdvancedDefenseSuccessRate = 0;
	gObj[aIndex].MasterSkillTreeEffect.IncreaseZen = 0;
}
void CMasterSkillSystem::SetEffect(int aIndex, CMagicInf *lpMagic)
{
	if(lpMagic == NULL)
	{
		LogAddTD("[error] lpMagic == NULL");
		return;
	}
	if(MagicDamageC.GetMasterSkillType(lpMagic->m_Skill) != 3) // PASSIVE
	{
		return;
	}
	int Effect = MagicDamageC.SkillGet(lpMagic->m_Skill);

	if(lpMagic->m_Skill >= 300 && lpMagic->m_Skill <= 304)
	{
	//	gObj[aIndex].Mastering.PvMAttackSuccessRate = Effect;
		LogAddC(4, "Master debug: Added Option 300-304 %d", Effect);
	}
	else if(lpMagic->m_Skill >= 305 && lpMagic->m_Skill <= 309)
	{
		gObj[aIndex].MasterSkillTreeEffect.AdvancedAttackSuccessRate = Effect;		
		LogAddC(4, "Master debug: Added option 305-309 %d", Effect);
	}
	else if(lpMagic->m_Skill >= 310 && lpMagic->m_Skill <= 314)
	{
		gObj[aIndex].MasterSkillTreeEffect.AdvancedDefenseSuccessRate = Effect;
		LogAddC(4, "Master debug: Added option 310-314 %d", Effect);
	}
	else if(lpMagic->m_Skill >= 315 && lpMagic->m_Skill <= 319)
	{	
		gObj[aIndex].MasterSkillTreeEffect.RepairLevel1 = Effect;
		LogAddC(4, "Master debug: Added option 310-314 %d", Effect);
	}
	else if(lpMagic->m_Skill >= 320 && lpMagic->m_Skill <= 324)
	{
		gObj[aIndex].MasterSkillTreeEffect.RepairLevel2 = Effect;
		LogAddC(4, "Master debug: Added option 315-319 %d", Effect);
	}
	else if(lpMagic->m_Skill >= 325 && lpMagic->m_Skill <= 329)
	{
		gObj[aIndex].MasterSkillTreeEffect.PoisonResistance = Effect;
	}
	else if(lpMagic->m_Skill >= 330 && lpMagic->m_Skill <= 334)
	{
		gObj[aIndex].MasterSkillTreeEffect.LightningResistance = Effect;
	}
	else if(lpMagic->m_Skill >= 335 && lpMagic->m_Skill <= 339)
	{
		gObj[aIndex].MasterSkillTreeEffect.IceResistance = Effect;
	}
	else if(lpMagic->m_Skill >= 340 && lpMagic->m_Skill <= 344)
	{
		gObj[aIndex].MasterSkillTreeEffect.IncreaseAutoRegeneration = Effect;
	}
	else if(lpMagic->m_Skill >= 345 && lpMagic->m_Skill <= 349)
	{
		gObj[aIndex].MasterSkillTreeEffect.IncreaseZen = Effect;
	}
	else if(lpMagic->m_Skill >= 350 && lpMagic->m_Skill <= 354)
	{
		gObj[aIndex].MasterSkillTreeEffect.IncreaseDefense = Effect;
	}
	else if(lpMagic->m_Skill >= 355 && lpMagic->m_Skill <= 359)
	{
		gObj[aIndex].MasterSkillTreeEffect.IncreaseMaxHP = Effect;
		gObjCalCharacter(aIndex);
	}
	else if(lpMagic->m_Skill >= 360 && lpMagic->m_Skill <= 364)
	{
		gObj[aIndex].MasterSkillTreeEffect.IncreaseMaxAG = Effect;
		gObjCalCharacter(aIndex);
	}
	else if(lpMagic->m_Skill >= 365 && lpMagic->m_Skill <= 369)
	{
		gObj[aIndex].MasterSkillTreeEffect.IncreaseManaReduction = Effect;
	}
	else if(lpMagic->m_Skill >= 370 && lpMagic->m_Skill <= 374)
	{
	//	gObj[aIndex].Mastering.MonsterAttackLifeIncrease = Effect;
	}
	else if(lpMagic->m_Skill >= 375 && lpMagic->m_Skill <= 379)
	{
		//gObj[aIndex].Mastering.MonsterAttackSDIncrease = Effect;
	}
	else if(lpMagic->m_Skill >= 380 && lpMagic->m_Skill <= 384)
	{
		gObj[aIndex].MasterSkillTreeEffect.IncreaseExperience = Effect;
	}
}
__int64 CMasterSkillSystem::ExpConvert(__int64 val)
{
	return
(val << 56 & 0xFF00000000000000) | 
(val << 40 & 0x00FF000000000000) | 
(val << 24 & 0x0000FF0000000000) | 
(val << 8 & 0x000000FF00000000) |
(val >> 8 & 0x00000000FF000000) |
(val >> 24 & 0x0000000000FF0000) |
(val >> 40 & 0x000000000000FF00) |
(val >> 56 & 0x00000000000000FF);

}
bool CMasterSkillSystem::IsMasterSkill(int SkillID)
{
	if(SkillID >= 300 && SkillID <= 570)
	{
		return true;
	}
	else return false;
}
bool CMasterSkillSystem::LevelUp(LPOBJ lpObj, __int64 addexp, int iMonsterType, int iEventType)
{
	LogAddTD("Master Experience : Map[%d]-(%d,%d) [%s][%s](%d) %u %d MonsterIndex : %d, EventType : %d",
		lpObj->MapNumber,lpObj->X,lpObj->Y,lpObj->AccountID,lpObj->Name,lpObj->Level,lpObj->Experience - addexp,addexp,iMonsterType,iEventType);
	if(lpObj->ChangeUP < 2)
	{
		return false;
	}
	if (lpObj->m_uMasterLevel >= 201)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 112)), lpObj->m_Index, 1);
		return false;
	}
	gObjSetExpPetItem(lpObj->m_Index, addexp);
	if ( lpObj->m_uMasterExp < lpObj->m_uMasterNextExp )
	{
		return true;
	}
	lpObj->m_uMasterLevel++;
	lpObj->m_uMasterPoints++;
	lpObj->m_uMasterExp = lpObj->m_uMasterNextExp;

	gObjCalCharacter(lpObj->m_Index);

	lpObj->MaxLife += DCInfo.DefClass[ lpObj->Class ].LevelLife;
	lpObj->MaxMana += DCInfo.DefClass[ lpObj->Class ].LevelMana;
	lpObj->Life = lpObj->MaxLife;
	lpObj->Mana = lpObj->MaxMana;

	lpObj->Life = lpObj->MaxLife + lpObj->AddLife;
	lpObj->Mana = lpObj->MaxMana + lpObj->AddMana;
	
	gObjCalcShieldPoint(lpObj);
	lpObj->iShield = lpObj->iMaxShield + lpObj->iAddShield;
	GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
	lpObj->m_uMasterNextExp = this->NextExpCal(lpObj);
	GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
	gObjSetBP(lpObj->m_Index);
	gObjCalcMaxLifePower(lpObj->m_Index);
	GCMasterLevelUpMsgSend(lpObj->m_Index, 1);

	LogAddTD("Master Level Up: %d (%s)(%s)", lpObj->m_uMasterLevel, lpObj->AccountID, lpObj->Name);

}
__int64 CMasterSkillSystem::NextExpCal(LPOBJ lpObj)
{
	return this->ExpStat + (this->ExpStat * lpObj->m_uMasterLevel);
}
bool CMasterSkillSystem::CanGainMasterExp(LPOBJ lpObj)
{
	if(lpObj->ChangeUP < 2)
	{
		return false;
	}
	if(lpObj->Level < MAX_CHAR_LEVEL)
	{
		return false;
	}
	return true;
}
void CMasterSkillSystem::CGReqAddMasterPoint(int aIndex, PMSG_MASTER_SKILL_RECV * lpMsg)
{
	int OldSkill = 0;
	int MasterP = 0;
	int SkillType = 0;
	/*if(!this->CanGainMasterExp(&gObj[aIndex]))
	{
		return;
	}*/
	CMagicInf * MagicInf = gObjGetMagicSearch(&gObj[aIndex], lpMsg->MasterSkill);
	/*if(MagicInf != NULL)
	{
		return;
	}*/
	MasterP = MagicDamageC.GetMasterPoint(lpMsg->MasterSkill);
	SkillType = MagicDamageC.GetMasterSkillType(lpMsg->MasterSkill);
	if(SkillType == 3)
	{
			if(MagicDamageC.SkillGetRequireClass(gObj[aIndex].Class, gObj[aIndex].ChangeUP, lpMsg->MasterSkill))
			{
				if(gObj[aIndex].m_uMasterPoints >= MasterP)
				{
					OldSkill = this->CheckGroupSkill(aIndex, lpMsg->MasterSkill, MagicDamageC.GetMasterGroup(lpMsg->MasterSkill));
					if(OldSkill != NULL)
					{
						this->ReplaceSkill(aIndex, lpMsg->MasterSkill, OldSkill);
					}
					else
					{
						int pos = gObjMagicAdd(&gObj[aIndex], lpMsg->MasterSkill, 0);
					}
					gObj[aIndex].m_uMasterPoints -= MasterP;
					MagicInf = gObjGetMagicSearch(&gObj[aIndex], lpMsg->MasterSkill);
					this->SetEffect(aIndex, MagicInf);
					this->GCAnsAddMasterPoint(aIndex, 0, 1, lpMsg->MasterSkill, lpMsg->MasterEmpty);
					LogAddTD("[Mastering] (%s)(%s) Added passive skill: %d", gObj[aIndex].AccountID, gObj[aIndex].Name, lpMsg->MasterSkill);
				}
				else
				{
					LogAddTD("[Mastering] (%s)(%s) Not enough MasterPoints for skill: %d", gObj[aIndex].AccountID, gObj[aIndex].Name, lpMsg->MasterSkill);
					return;
				}
			}
			else
			{
				LogAddTD("[Mastering] (%s)(%s) Invalid class for this skill: %d", gObj[aIndex].AccountID, gObj[aIndex].Name, lpMsg->MasterSkill);
				return;
			}
	}
	if(SkillType == 4)
	{
		if(OldSkill = this->GetActiveSkill(aIndex, lpMsg->MasterSkill) > 0)
		{
			this->ReplaceSkill(aIndex, lpMsg->MasterSkill, this->GetActiveSkill(aIndex, lpMsg->MasterSkill));
			this->GCAnsAddMasterPoint(aIndex, 0, 1, lpMsg->MasterSkill, lpMsg->MasterEmpty);
			LogAddTD("[Mastering] (%s)(%s) Added active skill: %d", gObj[aIndex].AccountID, gObj[aIndex].Name, lpMsg->MasterSkill);
		}
		else
		{
			LogAddTD("[Mastering] (%s)(%s) Cannot add active skill when old skill is not exist: %d", gObj[aIndex].AccountID, gObj[aIndex].Name, lpMsg->MasterSkill);
		}	
	}
}
void CMasterSkillSystem::GCAnsAddMasterPoint(int aIndex, BYTE type, BYTE flag, int MasterSkill, int MasterEmpty)
{
	PMSG_MASTER_SKILL_SEND pMsg;
	PHeadSubSetB((LPBYTE)&pMsg, 0xF3, 0x52, sizeof(pMsg));
	pMsg.flag = 0;
	pMsg.MasterPoint = gObj[aIndex].m_uMasterPoints;
	pMsg.type = 1;
	pMsg.MasterSkill = MasterSkill;
	pMsg.MasterEmpty = MasterEmpty;
	pMsg.ChkSum = 1;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}
int CMasterSkillSystem::CheckGroupSkill(int aIndex, int SkillID, int Group)
{
	int SkillGroup;
	for(int i=0;i<MAX_MAGIC;++i)
	{
		if(this->IsMasterSkill(gObj[aIndex].Magic[i].m_Skill))
		{
			SkillGroup = MagicDamageC.GetMasterGroup(gObj[aIndex].Magic[i].m_Skill);
			if(SkillGroup == Group)
			{
				return gObj[aIndex].Magic[i].m_Skill;
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}
	return false;
}
void CMasterSkillSystem::ReplaceSkill(int aIndex, int NewSkill, int OldSkill)
{
	int pos;
	for(int i=0;i<MAX_MAGIC;++i)
	{
		if(gObj[aIndex].Magic[i].m_Skill == OldSkill)
		{
			gObjMagicDel(&gObj[aIndex], OldSkill, gObj[aIndex].Magic[i].m_Level);
			pos=gObjMagicAdd(&gObj[aIndex], NewSkill, 0);
			LogAddC(4, "Replaced skill");
			return;
		}
	}
	return;
}
int CMasterSkillSystem::GetActiveSkill(int aIndex, int NewSkill)
{
	CMagicInf * skillresult;
/*	if(!this->CanGainMasterExp(&gObj[aIndex]))
	{
		return false;
	}*/
	int m_iBrand = MagicDamageC.GetBrandOfSkill(NewSkill);
	skillresult = gObjGetMagicSearch(&gObj[aIndex], m_iBrand);
	if(skillresult)
	{
		return skillresult->m_Skill;
	}
}
void CMasterSkillSystem::SetObjEffect(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->m_Defense += lpObj->MasterSkillTreeEffect.IncreaseDefense;
	lpObj->m_Resistance[R_ICE] += lpObj->MasterSkillTreeEffect.IceResistance;
	lpObj->m_Resistance[R_POISON] += lpObj->MasterSkillTreeEffect.PoisonResistance;
	lpObj->m_Resistance[R_LIGHTNING] += lpObj->MasterSkillTreeEffect.LightningResistance;
	lpObj->m_wExprienceRate += lpObj->MasterSkillTreeEffect.IncreaseExperience;
	lpObj->AddLife += lpObj->MasterSkillTreeEffect.IncreaseMaxHP;
	lpObj->AddBP += lpObj->MasterSkillTreeEffect.IncreaseMaxAG;
	lpObj->iAddShield += lpObj->MasterSkillTreeEffect.IncreaseMaxSD;

}