#include "stdafx.h"
#include "ObjUseSkill.h"
#include "ObjCalCharacter.h"
#include "GameMain.h"
#include "ChaosCastle.h"
#include "GameServer.h"
#include "user.h"
#include "zzzmathlib.h"
#include "SkillHitBox.h"
#include "MoveCommand.h"
#include "SkillAdditionInfo.h"
#include "DuelManager.h"
#include "CastleSiegeSync.h"
#include "gObjMonster.h"
#include "LogProc.h"
#include "..\common\winutil.h"
#include "BuffEffect.h"
// GS-N 0.99.60T 0x0049AE30
//	GS-N	1.00.18	JPN	0x004B7770 - Completed

CObjUseSkill gObjUseSkill;


CObjUseSkill::CObjUseSkill()
{
	return ;
}




CObjUseSkill::~CObjUseSkill()
{
	return;
}



int  CObjUseSkill::GetTargetLinePath(int sx, int sy, int tx, int ty, int * PathX, int * PathY, int distance)
{
	int x,y;
	int delta_x,delta_y;
	int half;

	int error = 0;

	int incx = 1,incy = 1;
	int dis;
	int count;

	if(sx > tx)
	{
		incx = -1;
		delta_x = sx - tx;
	}
	else
	{
		delta_x = tx - sx;
	}

	if(sy > ty)
	{
		incy = -1;
		delta_y = sy - ty;
	}
	else
	{
		delta_y = ty - sy;
	}

	dis = sqrt((float)(delta_x * delta_x + delta_y * delta_y));
	dis = distance - dis;

	count = 0;
	PathX[count] = sx;
	PathY[count] = sy;
	count++;

	if(delta_x > delta_y)
	{
		y = sy;
		half = delta_x / 2;

		if(incx > 0)
		{
			for(x = (sx+1); x <= (tx + dis); x++)
			{
				error += delta_y;

				if(error > half)
				{
					y += incy;
					error -= delta_x;
				}

				PathX[count] = x;
				PathY[count] = y;

				count++;
			}
		}
		else
		{
			for(x = (sx-1); x >= (tx - dis);x--)
			{
				error += delta_y;

				if(error > half)
				{
					y += incy;
					error -= delta_x;
				}

				PathX[count] = x;
				PathY[count] = y;

				count++;
			}
		}
	}
	else
	{
		x = sx;
		half = delta_y / 2;

		if(incy > 0)
		{
			for(y = (sy+1); y <= (ty + dis);y++)
			{
				error += delta_x;

				if(error > half)
				{
					x += incx;
					error -= delta_y;
				}

				PathX[count] = x;
				PathY[count] = y;
				count++;
			}
		}
		else
		{
			for(y = (sy-1);y >= (ty - dis);y--)
			{
				error += delta_x;

				if(error > half)
				{
					x += incx;
					error -= delta_y;
				}

				PathX[count] = x;
				PathY[count] = y;
				count++;
			}
		}
	}
	return count;
}




BOOL CObjUseSkill::SpeedHackCheck(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];


	int iTimeCalc = GetTickCount() - lpObj->m_LastAttackTime;

/*	if(iTimeCalc < lpObj->m_DetectSpeedHackTime && iTimeCalc != 0)
	{
		lpObj->m_DetectCount++;
		lpObj->m_SumLastAttackTime += iTimeCalc;

		if(lpObj->m_DetectCount > gHackCheckCount)
		{
			lpObj->m_DetectedHackKickCount++;

			if(gIsKickDetecHackCountLimit != 0 && lpObj->m_DetectedHackKickCount > gDetectedHackKickCount)
			{
				LogAddTD("[%s][%s] %s Kick DetecHackCountLimit Over User (%d)",
					lpObj->AccountID,lpObj->Name,lMsg.Get(lpObj->Class+1900),lpObj->m_DetectedHackKickCount);
				CloseClient(aIndex);
				return false;
			}

			lpObj->m_SpeedHackPenalty = gSpeedHackPenalty;
//			LogAddTD("[%s][%s] %s Attack Speed Is Wrong MagicSkill (%d)(%d) Penalty %d",
//				lpObj->AccountID,lpObj->Name,lMsg.Get(lpObj->Class+1900),lpObj->m_DetectSpeedHackTime,lpObj->m_SumLastAttackTime / lpObj->m_DetectCount,lpObj->m_SpeedHackPenalty);
		}
	}
	else
	{
		lpObj->m_SumLastAttackTime = 0;
		lpObj->m_DetectCount = 0;
	}

	lpObj->m_LastAttackTime = GetTickCount();

	if(bIsIgnorePacketSpeedHackDetect != 0 && lpObj->m_SpeedHackPenalty > 0)
	{
		lpObj->m_SpeedHackPenalty--;
		LogAddTD("[%s][%s] %s Apply Attack Speed Penalty (%d left)",
			lpObj->AccountID,lpObj->Name,lMsg.Get(lpObj->Class + 1900),lpObj->m_SpeedHackPenalty);
		return false;
	}*/
	return true;
}




BOOL CObjUseSkill::EnableSkill(BYTE Skill)
{
	if(Skill != AT_SKILL_STORM
		&& Skill != AT_SKILL_EVIL
		&& Skill != AT_SKILL_FLAME
		&& Skill != AT_SKILL_HELL
		&& Skill != AT_SKILL_BLAST
		&& Skill != AT_SKILL_INFERNO
		&& Skill != AT_SKILL_CROSSBOW
		&& Skill != AT_SKILL_DEVILFIRE
		&& Skill != AT_SKILL_FLASH
		&& Skill != AT_SKILL_WHEEL
		&& Skill != AT_SKILL_SWORD6
		&& Skill != AT_SKILL_KNIGHTSPEAR
		&& Skill != AT_SKILL_KNIGHTADDLIFE
		&& Skill != AT_SKILL_STRIKE
		&& Skill != AT_SKILL_KNIGHTDINORANT
		&& Skill != AT_SKILL_ELFHARDEN
		&& Skill != AT_SKILL_PENETRATION
		&& Skill != AT_SKILL_DEFENSEDOWN
		&& Skill != AT_SKILL_MAGICDEFENSE
		&& Skill != AT_SKILL_BLOWOFFURY
		&& Skill != AT_SKILL_EXPPOISON
		&& Skill != AT_SKILL_EXPICE
		&& Skill != AT_SKILL_EXPHELL
		&& Skill != AT_SKILL_ELECTRICSPARK
		&& Skill != AT_SKILL_DARKHORSE_ATTACK
		&& Skill != AT_SKILL_BRAND_OF_SKILL
		&& Skill != AT_SKILL_STUN
		&& Skill != AT_SKILL_REMOVAL_STUN
		&& Skill != AT_SKILL_ADD_MANA
		&& Skill != AT_SKILL_INVISIBLE 
		&& Skill != AT_SKILL_REMOVAL_INVISIBLE
		&& Skill != AT_SKILL_REMOVAL_MAGIC
		&& Skill != AT_SKILL_FENRIR_ATTACK
		&& Skill != AT_SKILL_INFINITY_ARROW
		&& Skill != AT_SKILL_FIRESCREAM
		&& Skill != AT_SKILL_DRAIN_LIFE
		&& Skill != AT_SKILL_CHAIN_LIGHTNING
		&& Skill != AT_SKILL_ELECTRIC_SURGE
		&& Skill != AT_SKILL_REFLEX
		&& Skill != AT_SKILL_NIGHT
		&& Skill != AT_SKILL_SLEEP
		&& Skill != AT_SKILL_INNOVATION
		&& Skill != AT_SKILL_WEAKNESS
		&& Skill != AT_SKILL_GHOST_PHANTOM
		&& Skill != AT_SKILL_RED_STORM
		&& Skill != AT_SKILL_EXPLOTION
		&& Skill != AT_SKILL_MAGIC_CIRCLE
		&& Skill != AT_SKILL_REDUCEDMGSHIELD
		&& Skill != AT_SKIL_FIVE_SHOT
		&& Skill != AT_SKILL_SWORDSLASH
		&& Skill != AT_SKILL_LIGHT_STORM
		&& Skill != AT_SKILL_BIRDS
		&& Skill != AT_SKILL_SAHAMUTT
		&& Skill != AT_SKILL_NEIL
		)
	{
		return false;
	}
	return true;
}


int CObjUseSkill::RunningMasterSkill(int aIndex, int aTargetIndex, CMagicInf *lpMagic, BOOL bCombo)
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	WORD MagicNumber = lpMagic->m_Skill;

	lpObj->m_SkillNumber = MagicNumber;

	if(lpObj->m_iSkillInvisibleTime > 0)
	{
		this->RemoveCloakingEffect(lpObj->m_Index);
	}
	if(MagicNumber >= 435 && MagicNumber <= 439)
	{
		this->WizardMagicDefense(aIndex, aTargetIndex, lpMagic);
		return 1;
	}
	else if(MagicNumber >= 440 && MagicNumber <= 444)
	{
		return this->SkillHellFire2(aIndex, aTargetIndex, lpMagic);
	}
	else if(MagicNumber >= 460 && MagicNumber <= 464)
	{
		return this->SkillKnightBlow(aIndex, aTargetIndex, lpMagic, bCombo);
	}
	else if(MagicNumber >= 470 && MagicNumber <= 474)
	{
		this->KnightSkillAddLife(aIndex, lpMagic);
		return 1;
	}
	else if(MagicNumber >= 475 && MagicNumber <= 479)
	{
		this->SkillHealing(aIndex, aTargetIndex, lpMagic);
		return 1;
	}
	else if(MagicNumber >= 480 && MagicNumber <= 484)
	{
		this->SkillDefense(aIndex, aTargetIndex, lpMagic);
		return 1;
	}
	else if(MagicNumber >= 485 && MagicNumber <= 489)
	{
		this->SkillAttack(aIndex, aTargetIndex, lpMagic, true);
		return 1;
	}
	/*else if(MagicNumber >= 500 && MagicNumber <= 504)
	{
		this->MaGumSkillDefenseDown(aIndex, aTargetIndex, lpMagic->m_Level);
		return 1;
	}*/
	else if(MagicNumber >= 515 && MagicNumber <= 519)
	{
		return this->SkillDarkHorseAttack(aIndex, aTargetIndex, lpMagic);
	}
	else if(MagicNumber >= 520 && MagicNumber <= 524)
	{
		return this->SkillFireBurst(aIndex, aTargetIndex, lpMagic);
	}
	else if(MagicNumber >= 525 && MagicNumber <= 529)
	{
		return this->SkillFireScream(aIndex,aTargetIndex,lpMagic);
	}

	else if(MagicNumber >= 550 && MagicNumber <= 554)
	{
		this->SkillDrainLife(aIndex,lpMagic,0,0,0,0,aTargetIndex);
		return true;
	}
	else if(MagicNumber >= 435 && MagicNumber <= 439)
	{
		this->WizardMagicDefense(aIndex,aTargetIndex,lpMagic);
		return true;
	}
	else if(MagicNumber >= 535 && MagicNumber <= 539)
	{
		this->SkillSleep(aIndex,aTargetIndex,lpMagic);
		return true;
	}


//	gObjAttack(lpObj, lpTargetObj, lpMagic, 1,0,0,0);
	return 1;
}

int  CObjUseSkill::GetUseMana(int aIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj =&gObj[aIndex];
	float mana = lpObj->Mana;

	if ( lpObj->Type != OBJ_USER )
	{
		return 0;
	}

	if ( lpMagic == NULL )
	{
		return 0;
	}

	mana -= MagicDamageC.SkillGetMana(lpMagic->m_Skill);

	mana -= this->GetAddUseMana(lpObj,lpMagic);

	if(mana < 0.0f)
	{
		return -1;
	}
	return mana;
}




int  CObjUseSkill::GetUseBP(int aIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];

	int bp = lpObj->BP;

	if(lpObj->Type != OBJ_USER)
	{
		return 0;
	}

	if(lpMagic == 0)
	{
		return 0;
	}

	int usingbp = MagicDamageC.SkillGetBP(lpMagic->m_Skill);

	usingbp -= usingbp * lpObj->SetOpDecreaseAG / 100;

	bp -= usingbp;

	if(bp < 0)
	{
		return -1;
	}

	return bp;
}


struct PMSG_DURATION_MAGIC_SEND {

  // static data ------------------------------------

  // non-static data --------------------------------
  /*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char MagicNumberH;
  unsigned char MagicNumberL;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char NumberH;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char NumberL;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char X;
  /*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char Y;
  /*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char Dir;

  // base classes -----------------------------------

  // friends ----------------------------------------

  // static functions -------------------------------

  // non-virtual functions --------------------------

  // virtual functions ------------------------------
};
// <size 0x9>

void CObjUseSkill::UseSkill(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	int bCombo = 0;

	if(gComboAttack.CheckCombo(aIndex,lpMagic->m_Skill))
	{
		bCombo = 1;
	}

	if(lpObj->SkillHellFire2State && lpMagic->m_Skill != AT_SKILL_EXPHELL)
	{
		CMagicInf * lpMagic = gObjGetMagicSearch(lpObj,AT_SKILL_EXPHELL);

		if(lpMagic != 0)
		{
			gObjUseSkill.RunningSkill(lpObj->m_Index,0,lpMagic,0);
		}

		return;
	}

	int usemana = this->GetUseMana(aIndex,lpMagic);

	PMSG_DURATION_MAGIC_SEND pMsg;

	if(usemana >= 0)
	{
		if(!gObj[aIndex].SkillDelay.Check(lpMagic->m_Skill))
		{
			LogAddTD("[%] ???? µ?·?????°? ????",gObj[aIndex].AccountID);
			return;
		}

		int usebp = gObjMagicBPUse(&gObj[aIndex],lpMagic);

		if(usebp >= 0)
		{
			lpObj->UseMagicNumber = lpMagic->m_Skill;
			lpObj->UseMagicTime = GetTickCount();
			lpObj->UseMagicCount = 0;

			lpObj->Mana = usemana;
			lpObj->BP = usebp;

			GCManaSend(lpObj->m_Index,lpObj->Mana,0xFF,0,lpObj->BP);

			PHeadSetBE((PBYTE)&pMsg,0x1E,sizeof(pMsg));

			pMsg.MagicNumberH = SET_NUMBERH(lpMagic->m_Skill);
			pMsg.MagicNumberL = SET_NUMBERL(lpMagic->m_Skill);
			pMsg.X = x;
			pMsg.Y = y;
			pMsg.Dir = dir;
			pMsg.NumberH = SET_NUMBERH(aIndex);
			pMsg.NumberL = SET_NUMBERL(aIndex);
	//		pMsg.UNK1 = 0x00;
			if(lpObj->Type == OBJ_USER)
			{
				DataSend(lpObj->m_Index,(PBYTE)&pMsg,pMsg.h.size);
			}

			if(CC_MAP_RANGE(lpObj->MapNumber))
			{
				switch(lpMagic->m_Skill)
				{
				case AT_SKILL_MAGICDEFENSE:
				case AT_SKILL_HEALING:
				case AT_SKILL_DEFENSE:
				case AT_SKILL_ATTACK:
				case AT_SKILL_KNIGHTADDLIFE:
					break;
				default: 
					MsgSendV2(lpObj,(PBYTE)&pMsg,pMsg.h.size);
				}
			}
			else
			{
				MsgSendV2(lpObj,(PBYTE)&pMsg,pMsg.h.size);
			}
		}

		if(lpMagic->m_Skill == AT_SKILL_SWORD6 || lpMagic->m_Skill >= 505 && lpMagic->m_Skill <= 509 )
		{
			this->SkillPowerSlash(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}

		if(lpMagic->m_Skill == AT_SKILL_DRAIN_LIFE)
		{
			this->SkillDrainLife(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		if(lpMagic->m_Skill == AT_SKILL_CHAIN_LIGHTNING || lpMagic->m_Skill >= 540 && lpMagic->m_Skill <= 544)
		{
			this->SkillChainLightning(aIndex,aTargetIndex,lpMagic);
		}
		if(lpMagic->m_Skill == AT_SKILL_SLEEP || lpMagic->m_Skill >= 535 && lpMagic->m_Skill <= 535)
		{
			this->SkillSleep(aIndex,aTargetIndex,lpMagic);
		}
		if(lpMagic->m_Skill == AT_SKILL_LIGHT_STORM)
		{
			this->SkillLightningStorm(aIndex,aTargetIndex,lpMagic);
		}
		if(lpMagic->m_Skill == AT_SKILL_EXPPOISON)
		{
			this->SkillDeathPoison(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_EXPICE || lpMagic->m_Skill >= 450 && lpMagic->m_Skill <= 454)
		{
			this->SkillSuddenIce(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_BLOWOFFURY || lpMagic->m_Skill >= 465 && lpMagic->m_Skill <= 469)
		{
			this->SkillBlowOfFury(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex,bCombo);
		}
		else if(lpMagic->m_Skill == AT_SKILL_WHEEL || (lpMagic->m_Skill >= 455 && lpMagic->m_Skill <= 459) || (lpMagic->m_Skill >= 495 && lpMagic->m_Skill <= 499) )
		{
			this->SkillWheel(aIndex,lpMagic,aTargetIndex,bCombo);
		}
		else if(lpMagic->m_Skill == AT_SKILL_ELECTRICSPARK)
		{
			this->SkillElectricSpark(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_BIRDS)
		{
			this->SkillBirds(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_DARKHORSE_ATTACK)
		{
			this->SkillDarkHorseAttack(lpObj->m_Index,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == AT_SKILL_STUN)
		{
			this->SkillStun(aIndex,aTargetIndex,lpMagic,x,y,dir,TargetPos);
		}
		else if(lpMagic->m_Skill == AT_SKILL_FENRIR_ATTACK)
		{
			this->SkillFenrirAttack(aIndex,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == AT_SKILL_GHOST_PHANTOM )
		{ 
			gObj[aIndex].m_iSkillPollusionX = x;
			gObj[aIndex].m_iSkillPollusionY = y;
			this->NewSkillProc(aIndex,lpMagic,gObj[aIndex].m_iSkillPollusionX,gObj[aIndex].m_iSkillPollusionY,aTargetIndex,59);
			//this->SkillGhostPhantomAttack(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_SAHAMUTT || lpMagic->m_Skill == AT_SKILL_NEIL )
		{ 
			this->SkillBookNumber12(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_WEAKNESS )
		{ 
			this->SkillWeakness(aIndex,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == AT_SKILL_INNOVATION )
		{ 
			this->SkillInnovation(aIndex,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == AT_SKILL_RED_STORM || lpMagic->m_Skill >= 545 && lpMagic->m_Skill <= 549)
		{
			this->SkillLightingShock(aIndex,lpMagic,x,y,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKIL_FIVE_SHOT)
		{
			this->SkillFiveShot(aIndex,lpMagic,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_SWORDSLASH)
		{
			this->SkillFlameStrike(aIndex,lpMagic,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_EXPLOTION)
		{
			this->SkillBlowOfDestruction(aIndex,lpMagic,x,y,aTargetIndex, bCombo);
		}
		else if(lpMagic->m_Skill > 300 && lpMagic->m_Skill < 525 || lpMagic->m_Skill > 529)
		{
			this->RunningMasterSkill(aIndex,aTargetIndex,lpMagic,bCombo);
		}
	}
}




void CObjUseSkill::UseSkill(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	int bCombo = 0;

	if(gComboAttack.CheckCombo(aIndex,lpMagic->m_Skill))
	{
		bCombo = 1;
	}

	if(lpObj->SkillHellFire2State && lpMagic->m_Skill != AT_SKILL_EXPHELL)
	{
		CMagicInf * lpMagic = gObjGetMagicSearch(lpObj,AT_SKILL_EXPHELL);

		if(lpMagic != 0)
		{
			gObjUseSkill.RunningSkill(lpObj->m_Index,0,lpMagic,0);
		}

		return;
	}

	if(lpMagic->m_Skill == AT_SKILL_EXPHELL && aTargetIndex != 58)
	{
		this->RunningSkill(aIndex,aTargetIndex,lpMagic,bCombo);
		lpObj->UseMagicNumber = lpMagic->m_Skill;
		lpObj->UseMagicTime = GetTickCount();
		lpObj->UseMagicCount = 0;
		return;
	}

	int usemana = this->GetUseMana(aIndex,lpMagic);

	if(usemana >= 0)
	{
		if(!gObj[aIndex].SkillDelay.Check(lpMagic->m_Skill))
		{
			LogAddTD("[%] ???? µ?·?????°? ????",gObj[aIndex].AccountID);
			return;
		}

		int usebp = this->GetUseBP(aIndex,lpMagic);

		if(usebp >= 0)
		{
			if(this->RunningSkill(aIndex,aTargetIndex,lpMagic,bCombo)==1)
			{
				lpObj->UseMagicNumber = lpMagic->m_Skill;
				lpObj->UseMagicTime = GetTickCount();
				lpObj->UseMagicCount = 0;

				lpObj->Mana = usemana;
				lpObj->BP = usebp;

				GCManaSend(aIndex,lpObj->Mana,0xFF,0,lpObj->BP);
			}
		}
	}
}

void CObjUseSkill::NewSkillProc(int aIndex, CMagicInf *lpMagic, BYTE x, BYTE y, int aTargetIndex, int aMsgSubCode)
{
	if (aMsgSubCode == 59)
	{
		GCMagicAttackNumberSend(&gObj[aIndex], lpMagic->m_Skill, aTargetIndex, 1);
	}
	this->SkillGhostPhantomAttack(aIndex, lpMagic, gObj[aIndex].m_iSkillPollusionX, gObj[aIndex].m_iSkillPollusionY, aTargetIndex, 3, 1, 0);

	if (aMsgSubCode >= 59 && aMsgSubCode <= 64)
	{
		gObjAddMsgSendDelay(&gObj[aIndex], 59, aTargetIndex, 1000, aMsgSubCode);
	}
}


BOOL CObjUseSkill::RunningSkill(int aIndex, int aTargetIndex, CMagicInf * lpMagic, BOOL bCombo)
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int MagicNumber = lpMagic->m_Skill;

	lpObj->m_SkillNumber = MagicNumber;

	if(lpObj->m_iSkillInvisibleTime > 0)
	{
		this->RemoveCloakingEffect(lpObj->m_Index);
	}
	if(MagicNumber >= 300)
	{
		this->RunningMasterSkill(aIndex,aTargetIndex,lpMagic,bCombo);
		return 1;
	}
	switch(MagicNumber)
	{
	case AT_SKILL_BLOCKING:
		if(lpObj->pInventory[1].IsItem() == 1)
		{
			if(lpObj->pInventory[1].m_Type >= ITEMGET(6,4) && lpObj->pInventory[1].m_Type < ITEMGET(7,0))
			{
				if(lpObj->pInventory[1].m_Option1 != 0)
				{
					lpObj->m_SkillTime = GetTickCount() + 4000;
					GCActionSend(lpObj,18,lpObj->m_Index,aTargetIndex);
				}
			}
		}
		break;
	case AT_SKILL_POISON:
	case AT_SKILL_METEO:
	case AT_SKILL_THUNDER:
	case AT_SKILL_FIREBALL:
	case AT_SKILL_FLAME:
	case AT_SKILL_SLOW:
	case AT_SKILL_ENERGYBALL:
	case AT_SKILL_SWORD1:
	case AT_SKILL_SWORD2:
	case AT_SKILL_SWORD3:
	case AT_SKILL_SWORD4:
	case AT_SKILL_SWORD5:
	case AT_SKILL_CROSSBOW:
	case AT_SKILL_BOW:
	case AT_SKILL_WHEEL:
	case AT_SKILL_BLOWOFFURY:
	case AT_SKILL_KNIGHTSPEAR:
	case AT_SKILL_PENETRATION:
	case AT_SKILL_SWORD6:
	case AT_SKILL_DRAIN_LIFE: 
	case AT_SKILL_CHAIN_LIGHTNING:
	case AT_SKILL_ELECTRIC_SURGE:
	//case AT_SKILL_REFLEX:
	case AT_SKILL_NIGHT:
	//case AT_SKILL_SLEEP:
	//case AT_SKILL_MAGIC_SPEED_UP:
//	case AT_SKILL_MAGIC_DEF_UP:
		gObjAttack(lpObj,lpTargetObj,lpMagic,1,0,0,0);
		break;
	case AT_SKILL_HEALING:	this->SkillHealing(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_MAGICDEFENSE:	this->WizardMagicDefense(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_KNIGHTADDLIFE:	this->KnightSkillAddLife(aIndex,lpMagic);break;
	case AT_SKILL_MAGIC_CIRCLE: this->MagicCircle(aIndex,aTargetIndex,lpMagic->m_Level);break;
	case AT_SKILL_DEFENSE:	this->SkillDefense(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_ATTACK:	this->SkillAttack(aIndex,aTargetIndex,lpMagic,false);break;
	case AT_SKILL_SLEEP: this->SkillSleep(aIndex,aTargetIndex,lpMagic); break;
	case AT_SKILL_CALLMON1:	return this->SkillMonsterCall(lpObj->m_Index,26,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON2:	return this->SkillMonsterCall(lpObj->m_Index,32,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON3:	return this->SkillMonsterCall(lpObj->m_Index,21,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON4:	return this->SkillMonsterCall(lpObj->m_Index,20,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON5:	return this->SkillMonsterCall(lpObj->m_Index,10,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON6:	return this->SkillMonsterCall(lpObj->m_Index,150,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON7:	return this->SkillMonsterCall(lpObj->m_Index,151,lpObj->X-1,lpObj->Y+1);

	case AT_SKILL_EXPHELL:	return this->SkillHellFire2(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_STRIKE:	return this->SkillKnightBlow(lpObj->m_Index,aTargetIndex,lpMagic,bCombo);

	case AT_SKILL_SPEAR:	return this->SkillSpear(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_FIREBURST:	return this->SkillFireBurst(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_DARKHORSE_ATTACK:	return this->SkillDarkHorseAttack(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_RECALL_PARTY:	this->SkillRecallParty(aIndex,lpMagic->m_Level);break;
	case AT_SKILL_ADD_CRITICALDAMAGE:	this->SkillAddCriticalDamage(aIndex,lpMagic->m_Level);break;

	case AT_SKILL_DEFENSEDOWN:	this->MaGumSkillDefenseDown(lpObj->m_Index,aTargetIndex,1);break;

	case AT_SKILL_SUMMON:	this->SkillSummon(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_IMMUNE_TO_MAGIC:	this->SkillImmuneToMagic(lpObj->m_Index,lpMagic);break;
	case AT_SKILL_IMMUNE_TO_HARM:	this->SkillImmuneToHarm(lpObj->m_Index,lpMagic);break;

	case AT_SKILL_RUSH:	this->SkillKnightRush(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_JAVALIN:	this->SkillWizardJavalin(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_DEEPIMPACT:	this->SkillElfRush(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_ONE_FLASH:	this->SkillMagumOneFlash(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_DEATH_CANNON:	this->SkillMagumDeathCannon(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_SPACE_SPLIT:	this->SkillDarklordSpaceSplit(lpObj->m_Index,aTargetIndex,lpMagic);break;

	case AT_SKILL_BRAND_OF_SKILL:	this->SkillBrandOfSkill(aIndex,aTargetIndex,lpMagic);break;

	case AT_SKILL_REMOVAL_STUN:	this->SkillRemoveStun(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_ADD_MANA:	this->SkillAddMana(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_INVISIBLE:	this->SkillCloaking(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_REMOVAL_INVISIBLE:	this->SkillRemoveCloaking(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_REMOVAL_MAGIC:	this->SkillRemoveMagic(aIndex,aTargetIndex,lpMagic);break;

	case AT_SKILL_INFINITY_ARROW:	this->SkillInfinityArrow(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_SWORD_POWER:    this->SkillSwordPower(aIndex,aTargetIndex,0);break;
	case AT_SKILL_REFLEX:   this->SkillReflex(aIndex,lpMagic,aTargetIndex);break;
	case AT_SKILL_INNOVATION: this->SkillInnovation(aIndex,aTargetIndex,lpMagic); break;
	case AT_SKILL_WEAKNESS: this->SkillWeakness(aIndex,aTargetIndex,lpMagic); break;
	case AT_SKILL_REDUCEDMGSHIELD: this->SkillShieldRefill(aIndex,lpMagic,aTargetIndex);break;
	default:	gObjAttack(lpObj,lpTargetObj,lpMagic,1,0,0,0);break;
	}

	return true;
}




void CObjUseSkill::MaGumSkillDefenseDown(int aIndex, int aTargetIndex, int skill_level)
{
	int skillSuccess = 1;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpObj->Type == OBJ_USER && lpObj->Class != CLASS_MAGUMSA)
	{
		return;
	}

	//LogAdd("?¶°?»? ??????????·?°??? : %d",10); // !!! Need Translation

	if(retCalcSkillResistance(lpTargetObj,1))
	{
		lpTargetObj->m_SkillMagumReduceDefense = 10;
		lpTargetObj->m_SkillMagumReduceDefenseTime = 10;
		lpTargetObj->m_ViewSkillState[eVS_DEFENSE_DOWN] = 1;

		GCMagicAttackNumberSend(lpObj,AT_SKILL_DEFENSEDOWN,lpTargetObj->m_Index,skillSuccess);
	}
}




void CObjUseSkill::KnightSkillAddLife(int aIndex, CMagicInf * lpMagic)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_KNIGHT && lpObj->Class != CLASS_MAGUMSA)
	{
		return;
	}

	int number;
	int partynum = 0;
	int totallevel = 0;
	int partycount;
	int dis;
	int skillbonus = 0;

	int ApplyPartyIndex[MAX_USER_IN_PARTY];

	int viewplayer = 0;
	int viewpercent = 0;

	LPOBJ lpPartyObj;

	memset(ApplyPartyIndex,-1,sizeof(ApplyPartyIndex));

	partynum = lpObj->PartyNumber;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpObj->MapNumber == lpPartyObj->MapNumber)
				{
					dis = gObjCalDistance(lpObj,&gObj[number]);

					if(dis < 10)
					{
						ApplyPartyIndex[n] = lpPartyObj->m_Index;
						viewplayer++;
					}
				}
			}
		}
	}

	if(viewplayer > 1)
	{
		if(viewplayer == 2)
		{
			viewpercent = 1;
		}
		else if(viewplayer == 3)
		{
			viewpercent = 2;
		}
		else if(viewplayer == 4)
		{
			viewpercent = 3;
		}
		else
		{
			viewpercent = 4;
		}
	}

	int iaddLifepower = 12 + (lpObj->Vitality + lpObj->AddVitality) / 100 + (lpObj->Energy + lpObj->AddEnergy)/ 20 + viewpercent;
	int iLifeTime = 60 + (lpObj->Energy + lpObj->AddEnergy) / 10;
	int iaddlife;
	if(MagicDamageC.GetMasterSkillType(lpMagic->m_Skill) == 4)
	{
		skillbonus = 2 * (lpMagic->m_Skill - 469);
	}
	if(skillbonus > 0)
	{
		iaddLifepower += (iaddLifepower * skillbonus) / 100.0f;
	}

	if(partynum == -1)
	{
		iaddlife = int(lpObj->MaxLife) * iaddLifepower / 100;
		//lpObj->AddLife -= lpObj->m_SkillAddLife;
		//lpObj->AddLife += iaddlife;

		//GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);

		//lpObj->m_SkillAddLife = iaddlife;
		//lpObj->m_SkillAddLifeTime = iLifeTime;

		if(BuffEffectC.BuffSearch(lpObj, 8) == 0)
		{
			BuffEffectC.EnableBuff(lpObj->m_Index, 8, iLifeTime, iaddlife, 0, 0);
		}
		GCMagicAttackNumberSend(lpObj,AT_SKILL_KNIGHTADDLIFE,lpObj->m_Index,skillSuccess);
	}
	else
	{
		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			if(ApplyPartyIndex[n]!= -1)
			{
				lpPartyObj = &gObj[ApplyPartyIndex[n]];

				iaddlife = int(lpPartyObj->MaxLife) * iaddLifepower / 100;
				//lpPartyObj->AddLife -= lpPartyObj->m_SkillAddLife;
				//lpPartyObj->AddLife += iaddlife;

				//GCReFillSend(lpPartyObj->m_Index,lpPartyObj->MaxLife + lpPartyObj->AddLife,0xFE,0,lpPartyObj->iMaxShield + lpPartyObj->iAddShield);

				//lpPartyObj->m_SkillAddLife = iaddlife;
				//lpPartyObj->m_SkillAddLifeTime = iLifeTime;

				if(BuffEffectC.BuffSearch(lpPartyObj, 8) == 0)
				{
					BuffEffectC.EnableBuff(lpPartyObj->m_Index, 8, iLifeTime, iaddlife, 0, 0);
				}
				GCMagicAttackNumberSend(lpObj,AT_SKILL_KNIGHTADDLIFE,lpPartyObj->m_Index,skillSuccess);
			}
		}
	}
}



void CObjUseSkill::WizardMagicDefense(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	int skillSuccess = true;
	int skillbonus = 0;
	int skillInc = 0;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon== -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_WIZARD && lpObj->Class != CLASS_MAGUMSA)
	{
		return;
	}

	if(lpObj->PartyNumber != lpTargetObj->PartyNumber)
	{
		return;
	}
	if(MagicDamageC.GetMasterSkillType(lpMagic->m_Skill) == 4)
	{
		skillbonus = 5 * (lpMagic->m_Skill - 434);
	}

	skillInc = 10 + (lpObj->Dexterity + lpObj->AddDexterity) / 50 + (lpObj->Energy + lpObj->AddEnergy) / 200;
	if(skillbonus > 0)
	{
		skillInc += (float)skillInc * ((float)skillbonus / 100.0f);
	}
	if(skillInc > 70)
	{
		skillInc = 70;
	}
	BuffEffectC.EnableBuff(lpTargetObj->m_Index, 4, (60 + (lpObj->Energy + lpObj->AddEnergy) /110), skillInc, 0, 0 );

	GCMagicAttackNumberSend(lpObj,AT_SKILL_MAGICDEFENSE,lpTargetObj->m_Index,skillSuccess);
}

void CObjUseSkill::MagicCircle(int aIndex, int aTargetIndex, int skill_level)
{
	BuffEffectC.EnableBuff(aIndex, 82, 1800, 20, 0, 0);
	GCMagicAttackNumberSend(&gObj[aIndex], AT_SKILL_MAGIC_CIRCLE, aIndex, 1);
}



void CObjUseSkill::SkillDefense(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
		int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int skill_level = lpMagic->m_Level;

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}
	
	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}

	float skill_defense = float(skill_level + 1)*2 + (lpObj->Energy + lpObj->AddEnergy) / 8;

	if(lpTargetObj->Class == CLASS_KNIGHT)
	{
		skill_defense += skill_defense/10.0f;
	}

	lpTargetObj->m_SkillDefense = skill_defense;
	lpTargetObj->m_SkillDefenseTime = 60;

	lpTargetObj->m_ViewSkillState[eVS_DEFENSE_AURA] = 1;

	for(int n = 0; n < MAX_VIEWPORT; n++)
	{
		if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
		{
			LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
			if(lpMonster->m_iCurrentAI != 0)
			{
				lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(skill_defense)/10);
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_DEFENSE,lpTargetObj->m_Index,skillSuccess);

}


//look

void CObjUseSkill::SkillAttack(int aIndex, int aTargetIndex, CMagicInf * lpMagic, bool Master)
{
		int skillSuccess = true;
	int skill_level = lpMagic->m_Level;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}
	
	float skill_attack;
	if(!Master)
	{
		skill_attack = float((skill_level + 1) * 3) + (lpObj->Energy + lpObj->AddEnergy) / 7.0f;
	}
	else
	{
		float divider = (float)MagicDamageC.SkillGet(lpMagic->m_Skill) / 10.0f;
		skill_attack = float((skill_level + 1) * 3) + (lpObj->Energy + lpObj->AddEnergy) / divider;
	}
	if(lpTargetObj->Class == CLASS_KNIGHT)
	{
		skill_attack += skill_attack/10.0f;
	}

	lpTargetObj->m_SkillAttack = skill_attack;
	lpTargetObj->m_SkillAttackTime = 60;
	lpTargetObj->m_ViewSkillState[eVS_ATTACK_AURA] = 1;

	for(int n = 0; n < MAX_VIEWPORT; n++)
	{
		if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
		{
			LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
			if(lpMonster->m_iCurrentAI != 0)
			{
				lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(skill_attack)/10);
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_ATTACK,lpTargetObj->m_Index,skillSuccess);

/*	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}

	float skill_attack = float((skill_level + 1) * 3) + (lpObj->Energy + lpObj->AddEnergy) / 7.0f;

	if(lpTargetObj->Class == CLASS_KNIGHT)
	{
		skill_attack += skill_attack/10.0f;
	}

	lpTargetObj->m_SkillAttack = skill_attack;
	lpTargetObj->m_SkillAttackTime = 60;
	lpTargetObj->m_ViewSkillState[eVS_ATTACK_AURA] = 1;

	for(int n = 0; n < MAX_VIEWPORT; n++)
	{
		if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
		{
			LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
			if(lpMonster->m_iCurrentAI != 0)
			{
				lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(skill_attack)/10);
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_ATTACK,lpTargetObj->m_Index,skillSuccess);*/
}




BOOL CObjUseSkill::SkillChangeUse(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	int skill_level = -1;

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,10))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = lpObj->pInventory[10].m_Level;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,10))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = lpObj->pInventory[11].m_Level;
		}
	}

	if(skill_level > 7)
	{
		return false;
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,39))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 372;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,39))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 372;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,40))//Halloween Ring
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 373;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,40))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 373;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,41))//X-Mas Ring
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 374;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,41))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 374;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,42))//GM Ring
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 378;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,42))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 378;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,68))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 477;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,76))// Panda Ring slot 1
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 503;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,76)) // Panda Ring slot2
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 503;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && skill_level == -1 && lpObj->pInventory[10].m_Type == ITEMGET(13,68))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 477;
		}
	}

	int change = -1;

	switch(skill_level)
	{
	case 0: change = 2;	break;
	case 1: change = 7; break;
	case 2: change = 14;	break;
	case 3: change = 8;	break;
	case 4:	change = 9;	break;
	case 5:	change = 41;	break;
	case 372:	change = skill_level;	break;
	case 373:	change = skill_level;	break;
	case 374:	change = skill_level;	break;
	case 378:	change = skill_level;	break;
	case 477:   change = skill_level;   break;
	case 503:	change = skill_level;   break;
	default: change = -1;	break;
	}

	if(lpObj->m_Change >= 0 && lpObj->m_Change == change)
	{
		return false;
	}

	if(lpObj->m_Change == 41 && change != 41)
	{
		lpObj->AddLife = 0;

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}

	if(lpObj->m_Change == 372 && change != 372)
	{
		lpObj->AddLife = 0;
		gObjCalCharacter(lpObj->m_Index);

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}

	if(lpObj->m_Change == 373 && change != 373)
	{
		lpObj->AddLife = 0;
		gObjCalCharacter(lpObj->m_Index);

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}
	if(lpObj->m_Change == 374 && change != 374)
	{
		lpObj->AddLife = 0;
		gObjCalCharacter(lpObj->m_Index);

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}
	if(lpObj->m_Change == 378 && change != 378)
	{
		lpObj->AddLife = 0;
		gObjCalCharacter(lpObj->m_Index);

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}

	if(lpObj->m_Change == 477 && change != 477)
	{
		lpObj->AddLife = 0;
		gObjCalCharacter(lpObj->m_Index);

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}

	if(lpObj->m_Change == 503 && change != 503)
	{
		lpObj->AddLife = 0;
		gObjCalCharacter(lpObj->m_Index);

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}

	lpObj->m_Change = change;
	gObjViewportListProtocolCreate(lpObj);

	PMSG_KILLCOUNT pMsg = {0};

	PHeadSubSetB((LPBYTE)&pMsg,0xB8,0x01,sizeof(pMsg));

	pMsg.btKillCount = lpObj->m_btKillCount;

	DataSend(aIndex,(PBYTE)&pMsg,sizeof(pMsg));
	return true;
}





void CObjUseSkill::SkillHealing(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
		int skillSuccess = true;
	int skillbonus = 0;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(lpMagic->m_Level < 0 || lpMagic->m_Level  > 7)
	{
		lpMagic->m_Level = 0;
	}

	int addlife = ((lpMagic->m_Level + 1) * 5 + (lpObj->Energy + lpObj->AddEnergy) / 5) + lpTargetObj->Life;
	if(MagicDamageC.GetMasterSkillType(lpMagic->m_Skill) == 4)
	{
		skillbonus = 10 * (lpMagic->m_Skill - 474);
	}
	if(skillbonus > 0)
	{
		addlife += (addlife * skillbonus) / 100.0f;
	}
	lpTargetObj->Life = addlife;
	if((lpTargetObj->MaxLife + lpTargetObj->AddLife) < lpTargetObj->Life)
	{
		lpTargetObj->Life = lpTargetObj->MaxLife + lpTargetObj->AddLife;
	}

	if(lpTargetObj->Type == OBJ_USER)
	{
		GCReFillSend(lpTargetObj->m_Index,lpTargetObj->Life,0xFF,0,lpTargetObj->iShield);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_HEALING,lpTargetObj->m_Index,skillSuccess);

		for(int n = 0; n < MAX_VIEWPORT; n++)
		{
			if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
			{
				LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
				if(lpMonster->m_iCurrentAI != 0)
				{
					lpMonster->m_Agro.IncAgro(lpObj->m_Index,(lpObj->Energy / 5)/40);
				}
			}
		}
	}
	else if(lpTargetObj->m_RecallMon >= 0)
	{
		GCRecallMonLife(lpTargetObj->m_RecallMon,lpTargetObj->MaxLife,lpTargetObj->Life);
	}
/*	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}

	lpTargetObj->Life = ((skill_level + 1) * 5 + (lpObj->Energy + lpObj->AddEnergy) / 5) + lpTargetObj->Life;

	if((lpTargetObj->MaxLife + lpTargetObj->AddLife) < lpTargetObj->Life)
	{
		lpTargetObj->Life = lpTargetObj->MaxLife + lpTargetObj->AddLife;
	}

	if(lpTargetObj->Type == OBJ_USER)
	{
		GCReFillSend(lpTargetObj->m_Index,lpTargetObj->Life,0xFF,0,lpTargetObj->iShield);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_HEALING,lpTargetObj->m_Index,skillSuccess);

		for(int n = 0; n < MAX_VIEWPORT; n++)
		{
			if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
			{
				LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
				if(lpMonster->m_iCurrentAI != 0)
				{
					lpMonster->m_Agro.IncAgro(lpObj->m_Index,(lpObj->Energy / 5)/40);
				}
			}
		}
	}
	else if(lpTargetObj->m_RecallMon >= 0)
	{
		GCRecallMonLife(lpTargetObj->m_RecallMon,lpTargetObj->MaxLife,lpTargetObj->Life);
	}*/
}




int CObjUseSkill::SkillMonsterCall(int aIndex, int MonsterType, int x, int y)
{
	if(gObj[aIndex].MapNumber == MAP_INDEX_ICARUS)
	{
		return false;
	}

	if(CC_MAP_RANGE(gObj[aIndex].MapNumber))
	{
		return false;
	}

	if(gObj[aIndex].m_RecallMon >= 0)
	{
		GCRecallMonLife(aIndex,60,0);
		gObjMonsterCallKill(aIndex);
		return false;
	}

	int result = gObjAddCallMon();

	if(result >= 0)
	{
		gObj[result].X = x;
		gObj[result].Y = y;
		gObj[result].MTX = x;
		gObj[result].MTY = y;
		gObj[result].Dir = 2;
		gObj[result].MapNumber = gObj[aIndex].MapNumber;
		gObjSetMonster(result,MonsterType);
		gObj[result].m_RecallMon = aIndex;
		gObj[result].m_Attribute = 100;
		gObj[result].TargetNumber = (WORD)-1;
		gObj[result].m_ActState.Emotion = 0;
		gObj[result].m_ActState.Attack = 0;
		gObj[result].m_ActState.EmotionCount = 0;
		gObj[result].PathCount = 0;

		gObj[aIndex].m_RecallMon = result;
		gObj[result].m_MoveRange = 15;

		GCRecallMonLife(gObj[result].m_RecallMon,gObj[result].MaxLife,gObj[result].Life);
		return true;
	}
	return false;
}




void CObjUseSkill::SkillBlowOfFury(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex, BOOL isCombo)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int DuelIndex = lpObj->m_iDuelUser;
	int HitCount = 0;
	int bAttack = 0;
	int EnableAttack;

	if(lpObj->pInventory[1].m_Type <= 0 && lpObj->pInventory[0].m_Type <= 0)
	{
		MsgOutput(aIndex,"You need weapon to use skill");
		return;
	}
	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 4)
					{
						bAttack = 0;

						if(HitCount > 15)
						{
							bAttack = 0;
						}

						if(HitCount >= 10)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,500,lpMagic->m_Skill,isCombo);

							if(isCombo != 0)
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_COMBO,aIndex,1);
							}
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}




void CObjUseSkill::SkillWheel(int aIndex, CMagicInf* lpMagic, int aTargetIndex, BOOL isCombo)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
	if(lpObj->pInventory[1].m_Type <= 0 && lpObj->pInventory[0].m_Type <= 0)
	{
		MsgOutput(aIndex,"You need weapon to use skill");
		return;
	}

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 3)
					{
						bAttack = 0;

						if(HitCount > 15)
						{
							bAttack = 0;
						}

						if(HitCount >= 10)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{

							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,0,1,0,isCombo);

							if(isCombo != 0)
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_COMBO,gObj[tObjNum].m_Index,1);
							}
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}




void CObjUseSkill::SkillPowerSlash(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE targetangle, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;
	::SkillFrustrum(targetangle,aIndex);
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex))
					{
						bAttack = 0;

						if(HitCount > 10)
						{
							bAttack = 0;
						}
						
						if(HitCount >= 5)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,1,0,0);
						}

						HitCount++;
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}

void CObjUseSkill::SkillDrainLife(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE targetangle, int aTargetIndex)
{ 
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int StartDis = 1;
	::SkillFrustrum(targetangle,aIndex);
	int count = 0;
	int HitCount = 0;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack = 0;
	GCMagicAttackNumberSend(lpObj, lpMagic->m_Skill, aTargetIndex, 1);
	if(lpTargetObj->Type == OBJ_MONSTER || lpTargetObj->Type == OBJ_USER)
	{
		EnableAttack = 1;
	}
	
	else if(lpTargetObj->m_iDuelUser == lpObj->m_Index)
	{
		EnableAttack = 1;
	}
	else
	{
		int CallMonIndex = lpTargetObj->m_Index;

		if(gObj[aTargetIndex].Type == OBJ_MONSTER && gObj[aTargetIndex].m_RecallMon >= 0)
			{
				CallMonIndex = gObj[lpTargetObj->m_RecallMon].m_Index;
			}

		if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
			{
				EnableAttack = 1;
			}
	}

	if(EnableAttack != 0)
	{
		gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,1,1,0,0);
		int DrainLife = (((lpObj->Energy * 100)/32000) * lpObj->MaxLife)/1000;
		if ( lpObj->MaxLife > lpObj->Life + DrainLife )
		{
			lpObj->Life += DrainLife;
		}
		else
		{
			lpObj->Life = lpObj->MaxLife;

		}
		GCReFillSend(gObj[aIndex].m_Index, gObj[aIndex].Life, 0xFF, FALSE, gObj[aIndex].iShield);
	}
}
#pragma pack (1)
struct PMSG_SPECIAL_SKILL // C1:BF:0A
{
	PBMSG_HEAD2 h;
	BYTE MagicNumberH;
	BYTE MagicNumberL;
	WORD AttackerIndex;
	WORD count;
	WORD TargetIndex[3];
};
#pragma pack ()
int CObjUseSkill::SkillChainLightning(int aIndex,int aTargetIndex,CMagicInf * lpMagic)
{
	PMSG_SPECIAL_SKILL pSkill = {0};
	PHeadSubSetB((LPBYTE)&pSkill, 0xBF, 0x0A, sizeof(pSkill));
	WORD Target[3] = {0};
	int EnableAttack;
	int countattacked = 1;
	int count = 0;
	int tObjNum;
	int DuelIndex = gObj[aIndex].m_iDuelUser;
	LPOBJ lpObj = &gObj[aIndex];
	GCMagicAttackNumberSend(lpObj, lpMagic->m_Skill, aTargetIndex, 1);
	Target[0] = aTargetIndex;
	if(!gCheckSkillDistance(aIndex, aTargetIndex, lpMagic->m_Skill))
	{
		return 0;
	}
	while(true)
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}
				if(EnableAttack)
				{
					if(gObj[tObjNum].X >= gObj[aTargetIndex].X-1 && gObj[tObjNum].X <= gObj[aTargetIndex].X+1
						&& gObj[tObjNum].Y >= gObj[aTargetIndex].Y-1 && gObj[tObjNum].Y <= gObj[aTargetIndex].Y+1)
					{
						for(int i=0;i<3;++i)
						{
							if(Target[i] <= 0)
							{
								Target[i] = tObjNum;
								++countattacked;
								break;
							}
						}
						if(countattacked == 3)
						{
							break;
						}
					}
					else if(gObj[tObjNum].X >= gObj[aTargetIndex].X-2 && gObj[tObjNum].X <= gObj[aTargetIndex].X+2
						&& gObj[tObjNum].Y >= gObj[aTargetIndex].Y-2 && gObj[tObjNum].Y <= gObj[aTargetIndex].Y+2)
					{
						for(int i=0;i<3;++i)
						{
							if(Target[i] <= 0)
							{
								Target[i] = tObjNum;
								++countattacked;
								break;
							}
						}
						if(countattacked == 3)
						{
							break;
						}
					}
				}
			}
		}
		++count;
		if(count > MAX_VIEWPORT-1)
			break;
	}
	pSkill.count = countattacked;
	for(int i=0;i<countattacked;++i)
	{
		pSkill.TargetIndex[i] = Target[i];
	}
	pSkill.MagicNumberH = LOBYTE(lpMagic->m_Skill);
	pSkill.MagicNumberL = HIBYTE(lpMagic->m_Skill);
	pSkill.AttackerIndex = aIndex;
	if(lpObj->Type == OBJ_USER)
	{
		DataSend(aIndex, (LPBYTE)&pSkill, pSkill.h.size);
	}
	MsgSendV2(lpObj, (LPBYTE)&pSkill, pSkill.h.size);
	for(int i=0;i<countattacked;++i)
	{
		gObjAddAttackProcMsgSendDelay(lpObj, 50, Target[i], (200 * i + 200), lpMagic->m_Skill, 0);
	}
}

int CObjUseSkill::SkillLightningStorm(int aIndex,int aTargetIndex,CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
//	GCMagicAttackNumberSend(lpObj, 3, lpObj->m_Index, 1);
	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					}
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;


						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex]) == 1)
						{
							EnableAttack = 1;
						}
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 4)
					{
						bAttack = 0;

						if(HitCount >= 5)
						{
							bAttack = 0;
						}
						else
						{
							bAttack = 1;
						}

						if(tObjNum == aTargetIndex)
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
						//gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,1,1,0,0);
							gObjAddAttackProcMsgSendDelay(lpObj,53,tObjNum,30,lpMagic->m_Skill,0);
							HitCount++;
						}
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}
int CObjUseSkill::SkillRedStorm(int aIndex,int aTargetIndex,CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
//	GCMagicAttackNumberSend(lpObj, 3, lpObj->m_Index, 1);
	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					}
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;


						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex]) == 1)
						{
							EnableAttack = 1;
						}
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6)
					{
						bAttack = 0;

						if(HitCount >= 5)
						{
							bAttack = 0;
						}
						else
						{
							bAttack = 1;
						}

						if(tObjNum == aTargetIndex)
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
						//gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,1,1,0,0);
							gObjAddAttackProcMsgSendDelay(lpObj,53,tObjNum,30,lpMagic->m_Skill,0);
							HitCount++;
						}
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}
int CObjUseSkill::SkillDeathPoison(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int FirstHit = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
	LPOBJ lpTargetObj = &gObj[aTargetIndex];


	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(this->CalDistance(x,y,gObj[tObjNum].X,gObj[tObjNum].Y) < 4)
					{
						bAttack = 0;

						if(HitCount > 10)
						{
							bAttack = 0;
						}
						
						if(HitCount >= 5)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							int delay = rand()%500;
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delay,lpMagic->m_Skill,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}




int CObjUseSkill::SkillSuddenIce(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int FirstHit = 0;
	int HitCount = 0;
	int bAttack;
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(this->CalDistance(x,y,gObj[tObjNum].X,gObj[tObjNum].Y) < 4)
					{
						bAttack = 0;

						if(HitCount > 10)
						{
							bAttack = 0;
						}
						
						if(HitCount >= 5)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							int delay = rand()%500;
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,1,0,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillHellFire2(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(aTargetIndex == 58)
	{
		return this->SkillHellFire2Start(aIndex,lpMagic);
	}

	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;

	if(lpObj->SkillHellFire2State == 0)
	{
		LogAddTD("[%s][%s] ????????2 ???° ?­·?????µµ ??????µ? ??·?°? µ?????",lpObj->AccountID,lpObj->Name);
		return false;
	}

	lpObj->SkillHellFire2State = 0;
	int count = 0;
	lpObj->SkillHellFire2Time = 0;

	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(aTargetIndex == tObjNum || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) <= 6)
					{
						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,600,lpMagic->m_Skill,0);
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_EXPHELL,lpObj->m_Index,1);
	return true;
}




BOOL CObjUseSkill::SkillHellFire2Start(int aIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->SkillHellFire2State != 0)
	{
		LogAddTD("[%s][%s] ????????2 ???° ?­·?????µ? ¶? ?­·???????°? ????",lpObj->AccountID,lpObj->Name);
		return false;
	}

	lpObj->SkillHellFire2Time = GetTickCount();
	lpObj->SkillHellFire2State = 1;
	lpObj->SkillHellFire2Count = 0;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_EXPHELL_START,aIndex,1);
	return true;
}




BOOL CObjUseSkill::SkillKnightBlow(int aIndex, int aTargetIndex, CMagicInf* lpMagic, BOOL isCombo)
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;

	float fangle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y);

	this->SkillFrustrum(aIndex,fangle,1.5f,3.0f);

	int count = 0;
	int loopcount = 0;
	int attackcheck;
	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	if(lpObj->pInventory[1].m_Type <= 0 && lpObj->pInventory[0].m_Type <= 0)
	{
		MsgOutput(aIndex,"You need weapon to use skill");
		return true;
	}
	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					attackcheck = 0;

					if(loopcount == 0)
					{
						attackcheck = 1;
					}
					else if(rand()%3==0)
					{
						attackcheck = 1;
					}

					if(attackcheck != 0)
					{
						if(::SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex))
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,0,1,0,isCombo);
							if(isCombo != 0)
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_COMBO,gObj[tObjNum].m_Index,1);
							}
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			loopcount++;
			count = 0;
			if(loopcount >= 3)
			{
				break;
			}
		}
	}
	return true;
}




void CObjUseSkill::SkillFrustrum(int aIndex, float fangle, float tx, float ty)
{
	LPOBJ lpObj = &gObj[aIndex];

	float p[MAX_ARRAY_FRUSTRUM][3];

	p[0][0] = -tx;
	p[0][1] = ty;
	p[0][2] = 0;
	p[1][0] = tx;
	p[1][1] = ty;
	p[1][2] = 0;
	p[2][0] = 1.0f;
	p[2][1] = 0;
	p[2][2] = 0;
	p[3][0] = -1.0f;
	p[3][1] = 0;
	p[3][2] = 0;

	float Angle[3];

	Angle[0] = 0;
	Angle[1] = 0;
	Angle[2] = fangle;

	float Matrix[3][MAX_ARRAY_FRUSTRUM];
	float vFrustrum[MAX_ARRAY_FRUSTRUM][3];

	AngleMatrix(Angle,Matrix);

	for(int i = 0; i < MAX_ARRAY_FRUSTRUM; i++)
	{
		VectorRotate((const float *)&p[i],(const float *)&Matrix[0],(float *)&vFrustrum[i]);

		lpObj->fSkillFrustrumX[i] = (int)vFrustrum[i][0] + lpObj->X;
		lpObj->fSkillFrustrumY[i] = (int)vFrustrum[i][1] + lpObj->Y;
	}
}




void CObjUseSkill::SkillFrustrum2(int aIndex, float fangle, float tx, float ty)
{
	LPOBJ lpObj = &gObj[aIndex];


	float p[MAX_ARRAY_FRUSTRUM][3];

	p[0][0] = 0;
	p[0][1] = ty;
	p[0][2] = 0;
	p[1][0] = 0;
	p[1][1] = ty;
	p[1][2] = 0;
	p[2][0] = tx;
	p[2][1] = 1.0f;
	p[2][2] = 0;
	p[3][0] = -tx;
	p[3][1] = 1.0f;
	p[3][2] = 0;

	float Angle[3];

	Angle[0] = 0;
	Angle[1] = 0;
	Angle[2] = fangle;

	float Matrix[3][MAX_ARRAY_FRUSTRUM];
	float vFrustrum[MAX_ARRAY_FRUSTRUM][3];

	AngleMatrix(Angle,Matrix);

	for(int i = 0; i < MAX_ARRAY_FRUSTRUM; i++)
	{
		VectorRotate((const float *)&p[i],(const float *)&Matrix[0],(float *)&vFrustrum[i]);

		lpObj->fSkillFrustrumX[i] = (int)vFrustrum[i][0] + lpObj->X;
		lpObj->fSkillFrustrumY[i] = (int)vFrustrum[i][1] + lpObj->Y;
	}
}

void CObjUseSkill::SkillFrustrum3(int aIndex, float fangle, float tx, float ty, float f1, float f2)
{
	LPOBJ lpObj = &gObj[aIndex];

	float p[MAX_ARRAY_FRUSTRUM][3];

	p[0][0] = 0;
	p[0][1] = ty;
	p[0][2] = 0;
	p[1][0] = tx;
	p[1][1] = ty;
	p[1][2] = 0;
	p[2][0] = f1;
	p[2][1] = f2;
	p[2][2] = 0;
	p[3][0] = -f1;
	p[3][1] = f2;
	p[3][2] = 0;

	float Angle[3];

	Angle[0] = 0;
	Angle[1] = 0;
	Angle[2] = (float)(360 * fangle / 255);

	float Matrix[3][MAX_ARRAY_FRUSTRUM];
	float vFrustrum[MAX_ARRAY_FRUSTRUM][3];

	AngleMatrix(Angle,Matrix);

	for(int i = 0; i < MAX_ARRAY_FRUSTRUM; i++)
	{
		VectorRotate((const float *)&p[i],(const float *)&Matrix[0],(float *)&vFrustrum[i]);

		lpObj->fSkillFrustrumX[i] = (int)vFrustrum[i][0] + lpObj->X;
		lpObj->fSkillFrustrumY[i] = (int)vFrustrum[i][1] + lpObj->Y;
	}
}



int  CObjUseSkill::GetAngle(int x, int y, int tx, int ty)
{
	double diffX = x - tx;
	double diffY = y - ty;

	double rad = atan2(diffY,diffX);

	int angle = rad * 180 / 3.141592741012573 + 90;

	if(angle < 0)
	{
		angle += 360;
	}
	return angle;
}




int  CObjUseSkill::CalDistance(int x, int y, int x1, int y1)
{
	if(x == x1 && y == y1)
	{
		return 0;
	}

	float tx = x - x1;
	float ty = y - y1;

	return sqrt(tx*tx + ty*ty);
}




BOOL CObjUseSkill::SkillAreaCheck(int angel, int x, int y, int tx, int ty, int dis, int arc)
{
	int minangel = angel - arc;
	int maxangel = angel + arc;

	if(this->CalDistance(x,y,tx,ty) > dis)
	{
		return false;
	}

	int targetangle = this->GetAngle(x,y,tx,ty);

	if(minangel < 0)
	{
		if(targetangle > maxangel)
		{
			if(targetangle > minangel + 360)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(maxangel < targetangle)
		{
			return false;
		}
	}
	else if(maxangel > 360)
	{
		if(targetangle < minangel)
		{
			if(targetangle < maxangel - 360)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(maxangel < targetangle)
		{
			return false;
		}
	}
	else if(minangel > targetangle)
	{
		return false;
	}
	else if(maxangel < targetangle)
	{
		return false;
	}
	return true;
}




BOOL CObjUseSkill::SkillSpear(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;

	int iangle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y);
	int count = 0;
	int loopcount = 0;
	int attackcheck;

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	if(lpObj->SkillLongSpearChange == 0)
	{
		gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);
		return true;
	}

	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					attackcheck = 0;

					if(loopcount == 0)
					{
						attackcheck = 1;
					}
					else if(rand()%3==0)
					{
						attackcheck = 1;
					}

					if(attackcheck != 0)
					{
						if(SkillSpearHitBox.HitCheck(iangle,lpObj->X,lpObj->Y,gObj[tObjNum].X,gObj[tObjNum].Y))
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,0,1,0,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillFireBurst(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;
	int count = 0;
	int loopcount = 0;

	GCMagicAttackNumberSend(lpObj,61,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);

	int attackcheck;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
	int delaytime;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0 && aTargetIndex != tObjNum)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					attackcheck = 0;

					if(loopcount == 0)
					{
						attackcheck = 1;
					}
					else if(rand()%3==0)
					{
						attackcheck = 1;
					}

					if(attackcheck != 0)
					{
						if(gObjCalDistance(&gObj[aTargetIndex],&gObj[tObjNum]) < 3)
						{
							delaytime = (rand()*17)%300 + 500;

							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delaytime,lpMagic->m_Skill,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillDarkHorseAttack(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_DARKHORSE_ATTACK,lpObj->m_Index,1);

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;
				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
	
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					}
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;
	
						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}
	
						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
						{
							EnableAttack = 1;
						}
					}
	
					if(EnableAttack != 0)
					{
						if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
						{
							bAttack = 0;
	
							if(HitCount > 15)
							{
								bAttack = 0;
							}
	
							if(HitCount >= 10)
							{
								if(rand()%2)
								{
									bAttack = 1;
								}
							}
							else
							{
								bAttack = 1;
							}
	
							if(bAttack != 0)
							{
								gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,500,lpMagic->m_Skill,0);
							}
						}
					}
				}
			}
		}
	
		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
return true;
}




BOOL CObjUseSkill::RecallPartyCheck(int aIndex, int skill_level)
{
	LPOBJ lpObj = &gObj[aIndex];
	int number;
	int partynum = 0;

	partynum = lpObj->PartyNumber;

	int partycount;
	LPOBJ lpPartyObj;
	int recallcount = 0;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY;n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpPartyObj->m_Index != lpObj->m_Index)
				{
					if(lpPartyObj->MapNumber == lpObj->MapNumber)
					{
						if(lpPartyObj->SkillRecallParty_Time != 0)
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}




void CObjUseSkill::SkillRecallParty(int aIndex, int skill_level)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1)
	{
		return;
	}

	if(this->RecallPartyCheck(aIndex,skill_level) == 0)
	{
		MsgOutput(aIndex,lMsg.Get(1238));
		return;
	}

	if(gMoveCommand.CheckMainToMove(lpObj) == 0)
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(1249));
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
		return;
	}

	if(gMoveCommand.CheckInterfaceToMove(lpObj) == 0)
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(1239));
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
		return;
	}

	int number;
	int partynum;
	int partycount;
	LPOBJ lpPartyObj;
	int recallcount;

	partynum = 0;
	partynum = lpObj->PartyNumber;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_RECALL_PARTY,lpObj->m_Index,skillSuccess);

	recallcount = 0;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY;n ++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpPartyObj->m_Index != lpObj->m_Index)
				{
					int movelevel = gMoveCommand.GetMoveLevel(lpObj->MapNumber,lpObj->X,lpObj->Y,lpPartyObj->Class);
					int bCheckMainToMove = gMoveCommand.CheckMainToMove(lpPartyObj);
					int bCheckEquipmentToMove = gMoveCommand.CheckEquipmentToMove(lpPartyObj,lpObj->MapNumber);
					int bCheckInterfaceToMove = gMoveCommand.CheckInterfaceToMove(lpPartyObj);

					if(lpPartyObj->Level >= movelevel
						&& movelevel != -1
						&& bCheckMainToMove != false
						&& bCheckEquipmentToMove != false
						&& bCheckInterfaceToMove != false)
					{
						int addx;
						int addy;
						int count = 50;
						int Find = 0;

						while(count--)
						{
							addx = lpObj->X + rand()%9 - 4;
							addy = lpObj->Y + rand()%9 - 4;

							if(gObjCheckTeleportArea(lpObj->m_Index,addx,addy))
							{
								Find = 1;
								break;
							}
						}

						if(Find == 0)
						{
							addx = lpObj->X;
							addy = lpObj->Y;
						}

						lpPartyObj->SkillRecallParty_Time = 7;
						lpPartyObj->SkillRecallParty_MapNumber = lpObj->MapNumber;
						lpPartyObj->SkillRecallParty_X = addx;
						lpPartyObj->SkillRecallParty_Y = addy;

						char msg[255];

						wsprintf(msg,lMsg.Get(1251));
						GCServerMsgStringSend(msg,lpPartyObj->m_Index,1);
						recallcount++;
					}
					else
					{
						char msg[255];
						wsprintf(msg,lMsg.Get(1252));
						GCServerMsgStringSend(msg,lpPartyObj->m_Index,1);
					}
				}
			}
		}
	}

	if(recallcount != 0)
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(1244),recallcount);
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
	}
}




void CObjUseSkill::SkillAddCriticalDamage(int aIndex, int skill_level)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	int number;

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_DARKLORD)
	{
		return;
	}


	int partynum = 0;
	int totallevel = 0;
	int partycount;
	int dis;

	int ApplyPartyIndex[MAX_USER_IN_PARTY];
	LPOBJ lpPartyObj;
	memset(ApplyPartyIndex,-1,sizeof(ApplyPartyIndex));

	partynum = lpObj->PartyNumber;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpObj->MapNumber == lpPartyObj->MapNumber)
				{
					dis = gObjCalDistance(lpObj,&gObj[number]);
					if(dis < 10)
					{
						ApplyPartyIndex[n] = lpPartyObj->m_Index;
					}
				}
			}
		}
	}

	int addcriticaldamagevalue = (lpObj->Leadership + lpObj->AddLeadership)/25 + (lpObj->Energy + lpObj->AddEnergy)/30;
	int SkillTime = (lpObj->Energy + lpObj->AddEnergy)/10 + 60;

	if(partynum == -1)
	{
		lpObj->SkillAddCriticalDamageTime = SkillTime;
		lpObj->SkillAddCriticalDamage = addcriticaldamagevalue;
	lpObj->m_ViewSkillState[eVS_CRITICAL_DAMAGE] = 1;

		MsgOutput(aIndex,lMsg.Get(1240),SkillTime);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_CRITICALDAMAGE,lpObj->m_Index,skillSuccess);
	}
	else
	{
		for(int n = 0;n < MAX_USER_IN_PARTY;n++)
		{
			if(ApplyPartyIndex[n] != -1)
			{
				lpPartyObj = &gObj[ApplyPartyIndex[n]];

				lpPartyObj->SkillAddCriticalDamageTime = SkillTime;
				lpPartyObj->SkillAddCriticalDamage = addcriticaldamagevalue;
			lpPartyObj->m_ViewSkillState[eVS_CRITICAL_DAMAGE] = 1;

				MsgOutput(aIndex,lMsg.Get(1240),SkillTime);
				GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_CRITICALDAMAGE,lpPartyObj->m_Index,skillSuccess);
			}
		}
	}
}



void CObjUseSkill::SkillSleep(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
    int skillSuccess = 1;
	LPOBJ lpObj = &gObj[aIndex];
    LPOBJ lpTargetObj = &gObj[aTargetIndex];


	if(lpObj->Class != CLASS_SUMMONER)
	{
	    return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber))
	{
		return;
	}



	int sleeptime = ((lpObj->AddEnergy+lpObj->Energy)/10+2)*1000;

	if(sleeptime > 15*1000)
	{
		sleeptime = 15*1000;
	}
	
	lpTargetObj->NextActionTime = sleeptime;
	lpTargetObj->m_SummonerSkillSleepTime = sleeptime / 1000;
	BuffEffectC.EnableBuff(aIndex,eVS_SKILL_SLEEP,sleeptime,0,0,0);
	//GCStateInfoSend(lpTargetObj,1, eVS_SKILL_SLEEP,0,0 );
	GCMagicAttackNumberSend(lpObj,0xDB,lpTargetObj->m_Index,skillSuccess);
	
}

bool CObjUseSkill::SkillBookNumber12(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
    LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
	
	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
					if(lpObj->VpPlayer2[count].type == 2 && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					}
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;


						if(gObj[tObjNum].Type == 2 && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex]) == 1)
						{
							EnableAttack = 1;
						}
					}
				}

				if(EnableAttack != 0)
				{
					if(this->CalDistance(x,y,gObj[tObjNum].X,gObj[tObjNum].Y) < 3)
					{
						bAttack = 0;

						if(HitCount >= 11)
						{
							bAttack = 0;
						}
						else
						{
							bAttack = 1;
						}

						if(tObjNum == aTargetIndex)
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,300,lpMagic->m_Skill,0);
							if(lpMagic->m_Skill == AT_SKILL_SAHAMUTT)
							{
								gObjMonsterStateProc(&gObj[tObjNum], 58, lpObj->m_Index, 7);
							}
							else
							{
								int DrainLife = (((lpObj->Energy * 100)/32000) * lpObj->MaxLife)/1000;
								if ( lpObj->MaxLife > lpObj->Life + DrainLife )
								{
									lpObj->Life += DrainLife;
								}
								else
								{
									lpObj->Life = lpObj->MaxLife;

								}
								GCReFillSend(gObj[aIndex].m_Index, gObj[aIndex].Life, 0xFF, FALSE, gObj[aIndex].iShield);

							}
							HitCount++;
						}
					}
				}
			}
		}

		count++;

		if(count > 74)
		{
			break;
		}
	}
	return true;

}
void CObjUseSkill::SkillElectricSpark(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	int TargePosx = lpObj->X - (8 - (TargetPos & 15));
	int TargePosy = lpObj->Y - (8 - ((TargetPos & 240) >> 4));

	int tObjNum;
	int count = 0;
	int DuelIndex = lpObj->m_iDuelUser;
	int iangle = this->GetAngle(lpObj->X,lpObj->Y,TargePosx,TargePosy);
	int delaytime;
	int Hit = 0;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(SkillElectricSparkHitBox.HitCheck(iangle,gObj[aIndex].X,gObj[aIndex].Y,gObj[tObjNum].X,gObj[tObjNum].Y))
					{
						delaytime = 500;
						Hit = 1;

						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delaytime,lpMagic->m_Skill,0);
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	if(Hit != 0)
	{
		DecPartyMemberHPandMP(lpObj);
	}
}


void CObjUseSkill::SkillBirds(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
	/*LPOBJ lpObj = &gObj[aIndex];

	int TargePosx = lpObj->X - (8 - (TargetPos & 15));
	int TargePosy = lpObj->Y - (8 - ((TargetPos & 240) >> 4));

	int tObjNum;
	int count = 0;
	int DuelIndex = lpObj->m_iDuelUser;
	int iangle = this->GetAngle(lpObj->X,lpObj->Y,TargePosx,TargePosy);
	int delaytime;
	int Hit = 0;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6)
					{
						delaytime = 500;
						Hit = 1;

						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delaytime,lpMagic->m_Skill,0);
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}*/
	LPOBJ lpObj = &gObj[aIndex];
	this->SkillFrustrum3(aIndex, TargetPos, 6.0, 7.0, 1.0, 0);
	float Matrix[3][4];
	float Angle[3];
	float p[4][3];
	float Frustrum[5][3];
	float NewFrustrum[5][3];
	int FrustrumX[5];
	int FrustrumY[5];
	int AttackTable[5];
	// one shot per angle of 20 degress
	Angle[0] = 0;
	Angle[1] = 6.0;
	Angle[2] = 0;
	p[0][0] = 0;
	p[0][1] = 0;
	p[0][2] = 40.0;
	p[1][0] = 0;
	p[1][1] = 0;
	p[1][2] = 20.0;
	p[2][0] = 0;
	p[2][1] = 0;
	p[2][2] = 340.0;
	p[3][0] = 0;
	p[3][1] = 0;
	p[3][2] = 320.0;
	AngleMatrix(p[0], Matrix);
	VectorRotate((const float *)&Angle[0], (const float *)&Matrix[0], (float *)&Frustrum[0]);
	AngleMatrix(p[1], Matrix);
	VectorRotate((const float *)&Angle[0], (const float *)&Matrix[0], (float *)&Frustrum[1]);
	Frustrum[2][0] = 0.0;
	Frustrum[2][1] = 6.0;
	Frustrum[2][2] = 0.0;
	AngleMatrix(p[2], Matrix);
	VectorRotate((const float *)&Angle[0], (const float *)&Matrix[0], (float *)&Frustrum[3]);
	AngleMatrix(p[3], Matrix);
	VectorRotate((const float *)&Angle[0], (const float *)&Matrix[0], (float *)&Frustrum[4]);
	p[0][0] = 0;
	p[0][1] = 0;
	p[0][2] = (360 * TargetPos / 255);
	AngleMatrix(p[0], Matrix);
	for(int i=0;i<5;++i)
	{
		VectorRotate((const float *)&Frustrum[i], (const float *)&Matrix[0], (float *)&NewFrustrum[i]);
		FrustrumX[i] = (int)NewFrustrum[i][0] + lpObj->X;
		FrustrumY[i] = (int)NewFrustrum[i][1] + lpObj->Y;
	}

	int tObjNum;
	int count = 0;
	int EnableAttack;
	int DuelIndex = lpObj->m_iDuelUser;

	while(true)
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;
			EnableAttack = 0;
			if(tObjNum >= 0)
			{
				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				if(lpObj->VpPlayer2[count].type == OBJ_NPC || lpObj->MapNumber != MAP_INDEX_CASTLESIEGE || g_CastleSiegeSync.GetCastleState() != 7)
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}
				else
				{
					EnableAttack = 1;
				}
				if(g_DuelManager.DuelCheck(lpObj, &gObj[tObjNum]))
				{
					EnableAttack = 1;
				}
			}
			if ( EnableAttack )
			{
				if(gObj[aIndex].Type == OBJ_USER)
				{
					for ( int j=0;j<5;++j)
					{
						AttackTable[j] = ((gObj[tObjNum].Y - lpObj->Y) * (FrustrumX[j] - lpObj->X))
							- ((gObj[tObjNum].X - lpObj->X) * (FrustrumY[j] - lpObj->Y));
						if(SkillTestFrustrum(gObj[tObjNum].X, gObj[tObjNum].Y, aIndex) == TRUE)
						{
							if(AttackTable[j] > -5 && AttackTable[j] < 5)
							{
							//	gObjAttack(lpObj, &gObj[tObjNum], lpMagic, 1, 0 ,0 ,0);
								gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,500,lpMagic->m_Skill,0);
							}
						}
					}
				}
				else if(gObj[aIndex].Type == OBJ_MONSTER)
				{
					gObjAttack(lpObj, &gObj[tObjNum], lpMagic, 1, 0, 0, 0);
				}
			}
		}
		++count;
		if(count > MAX_VIEWPORT-1)
			break;
	}
}

int  DecPartyMemberHPandMP(LPOBJ lpObj)
{
	LPOBJ lpPartyObj;
	int partynum = lpObj->PartyNumber;

	if(OBJMAX_RANGE(partynum)==false)
	{
		LogAdd("error : DecPartyMemberHPandMP %s %d",__FILE__,__LINE__);
		return false;
	}

	int partycount = gParty.m_PartyS[partynum].Count;
	int retcount = 0;

	for(int n = 0; n < MAX_USER_IN_PARTY;n++)
	{
		int number = gParty.m_PartyS[partynum].Number[n];

		if(number >= 0)
		{
			lpPartyObj = &gObj[number];

			if(lpObj->MapNumber == lpPartyObj->MapNumber && lpObj->m_Index != number)
			{
				int dis = gObjCalDistance(lpObj,&gObj[number]);
				if(dis < 10)
				{
					lpPartyObj = &gObj[number];

					int declife = lpPartyObj->Life * 20.0f / 100.0f;
					int decmana = lpPartyObj->Mana * 5.0f / 100.0f;

					lpPartyObj->Life = lpPartyObj->Life - declife;
					lpPartyObj->Mana = lpPartyObj->Mana - decmana;

					GCReFillSend(lpPartyObj->m_Index,lpPartyObj->Life,0xFF,0,lpPartyObj->iShield);
					GCManaSend(lpPartyObj->m_Index,lpPartyObj->Mana,0xFF,0,lpPartyObj->BP);
					retcount++;
				}
			}
		}
	}

	return retcount;
}




BOOL CObjUseSkill::SkillSummon(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex)==false)
	{
		return false;
	}

	int iSummonCount = 1;
	int iSummonMonterType = 0;
	BYTE bDoSummon = 1;
	BYTE bSummonSuccess = 0;
	BYTE cSummonX = 0;
	BYTE cSummonY = 0;

	LPOBJ lpObj = &gObj[aIndex];

	switch(lpObj->Class)
	{
	case 161:
		iSummonMonterType = rand()%2+ 147;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 181:
		iSummonMonterType = rand()%2+ 177;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 189:
		iSummonMonterType = rand()%2+ 185;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 197:
		iSummonMonterType = rand()%2+ 193;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 267:
		iSummonMonterType = rand()%2+ 263;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 275:
		iSummonMonterType = rand()%2+ 271;
		bDoSummon = (rand()%15) ? false : true;
		break;
	}

	if(bDoSummon == false)
	{
		return false;
	}

	for(int iSC = 0; iSC < iSummonCount; iSC++)
	{
		BYTE cSX = lpObj->X;
		BYTE cSY = lpObj->Y;

		if(gObjGetRandomFreeLocation(lpObj->MapNumber,(BYTE &)cSX,(BYTE &)cSY,2,2,30)==1)
		{
			int result = gObjAddMonster(lpObj->MapNumber);

			if(result >= 0)
			{
				gObj[result].m_PosNum = (WORD)-1;
				gObj[result].X = cSX;
				gObj[result].Y = cSY;
				gObj[result].MapNumber = lpObj->MapNumber;
				gObj[result].TX = gObj[result].X;
				gObj[result].TY = gObj[result].Y;
				gObj[result].m_OldX = gObj[result].X;
				gObj[result].m_OldY = gObj[result].Y;
				gObj[result].Dir = 1;
				gObj[result].StartX = gObj[result].X;
				gObj[result].StartY = gObj[result].Y;
				gObjSetMonster(result,iSummonMonterType);
				gObj[result].m_Attribute = 60;
				gObj[result].MaxRegenTime = 0;
				gObj[result].Dir = rand()%8;
				bSummonSuccess = 1;
				cSummonX = gObj[result].StartX;
				cSummonY = gObj[result].StartY;
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_SUMMON,(((cSummonX & 0xFF)&0xFF) | ((cSummonY & 0xFF)&0xFF) << 8) & 0xFFFF,bSummonSuccess);
	return bSummonSuccess;
}




BOOL CObjUseSkill::SkillImmuneToMagic(int aIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->m_ImmuneToMagicCount <= 0 && lpObj->m_ImmuneToHarmCount <= 0)
	{
		//lpObj->m_ImmuneToMagicCount = 10;
		//lpObj->m_ViewSkillState[eVS_INMUNE_TO_MAGIC] = 1;
		//GCStateInfoSend(lpObj,1,eVS_INMUNE_TO_MAGIC,0,0);
		BuffEffectC.EnableBuff(lpObj->m_Index, 64, 10, 0, 0, 0);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_IMMUNE_TO_MAGIC,lpObj->m_Index,1);
		return true;
	}
	return false;
}


BOOL CObjUseSkill::SkillImmuneToHarm(int aIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->m_ImmuneToMagicCount <= 0 && lpObj->m_ImmuneToHarmCount <= 0)
	{
		lpObj->m_ImmuneToHarmCount = 10;
		//lpObj->m_ViewSkillState[eVS_DEFENSE_AURA] = 1;
		//GCStateInfoSend(lpObj,1,eVS_DEFENSE_AURA,0,0);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_IMMUNE_TO_HARM,lpObj->m_Index,1);
		return true;
	}
	return false;
}



BOOL CObjUseSkill::RemoveAllCharacterInvalidMagicAndSkillState(LPOBJ lpObj)
{
	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

lpObj->m_SkillAttackTime = 0;
	lpObj->m_SkillAttack = 0;

	lpObj->m_ViewSkillState[eVS_DEFENSE_AURA] = 0;

	lpObj->m_SkillAttackTime2 = 0;
	lpObj->m_SkillAttack2 = 0;
	lpObj->m_SkillDefenseTime = 0;
	lpObj->m_SkillDefense = 0;

	lpObj->m_ViewSkillState[eVS_ATTACK_AURA] = 0;

	lpObj->m_WizardSkillDefenseTime = 0;
	lpObj->m_WizardSkillDefense = 0;

	lpObj->m_ViewSkillState[eVS_SOUL_BARRIER] = 0;

	lpObj->m_SkillAddLifeTime = 0;
	lpObj->m_SkillAddLife = 0;

	lpObj->m_ViewSkillState[eVS_SWELL_LIFE] = 0;

	lpObj->m_SkillHardenTime = 0;
	lpObj->m_SkillHarden = 0;

	lpObj->m_ViewSkillState[eVS_ICE_ARROW] = 0;

	lpObj->m_SkillMagumReduceDefenseTime = 0;
	lpObj->m_SkillMagumReduceDefense = 0;

	lpObj->m_ViewSkillState[eVS_DEFENSE_DOWN] = 0;

	lpObj->SkillRecallParty_Time = 0;
	lpObj->SkillAddCriticalDamageTime = 0;
	lpObj->SkillAddCriticalDamage = 0;

	lpObj->m_ViewSkillState[eVS_CRITICAL_DAMAGE] = 0;

	lpObj->m_iSkillStunTime = 0;

	lpObj->m_ViewSkillState[eVS_STUN] = 0;

	lpObj->m_iSkillBrandOfSkillTime = 0;

	lpObj->m_ViewSkillState[eVS_SACRIFICE] = 0;

	lpObj->m_iSkillInvisibleTime = 0;

	lpObj->m_ViewSkillState[eVS_TRANSPARENCY] = 0;

	lpObj->m_iSkillManaSwellTime = 0;
	lpObj->m_iSkillManaSwell = 0;

	lpObj->m_ViewSkillState[eVS_SWELL_MANA] = 0;

	lpObj->m_PoisonBeattackCount = 0;
	lpObj->m_PoisonType = 0;

	lpObj->m_ViewSkillState[eVS_POISON] = 0;

	lpObj->m_ColdBeattackCount = 0;
	lpObj->m_IceType = 0;

	lpObj->m_ViewSkillState[eVS_ICE] = 0;

	lpObj->m_ImmuneToMagicCount = 0;
	lpObj->m_ImmuneToHarmCount = 0;

	lpObj->m_ViewSkillState[eVS_ICE_ARROW] = 0;
	lpObj->m_ViewSkillState[eVS_DEFENSE_AURA] = 0;

	lpObj->m_iMuseElfInfinityArrowSkillTime = 0;

	lpObj->m_ViewSkillState[eVS_INFINITY_ARROW] = 0;

	lpObj->m_ViewSkillState[eVS_SKILL_MAGICCIRCLE] = 0;

	lpObj->m_ViewSkillState[eVS_SKILL_DAMAGEREFLECTION] = 0;
	lpObj->m_SummonerSkillReflex = 0;
	lpObj->m_SummonerSkillReflexTime = 0;

	lpObj->m_ViewSkillState[eVS_SKILL_SWORDPOWER] = 0;
	lpObj->m_SummonerSkillSwordPower = 0;
	lpObj->m_SummonerSkillSwordPowerTime = 0;
	BuffEffectC.ClearBuff(lpObj);
	return true;
}




BOOL CObjUseSkill::SkillKnightRush(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);
	return true;
}




BOOL CObjUseSkill::SkillWizardJavalin(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int iDelay = 500;

	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,iDelay,lpMagic->m_Skill,0);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,iDelay+200,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillElfRush(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,800,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillMagumOneFlash(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,100,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillMagumDeathCannon(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);
	return true;
}




BOOL CObjUseSkill::SkillDarklordSpaceSplit(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,500,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillBrandOfSkill(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int count = 0;

	//lpObj->m_iSkillBrandOfSkillTime = 10;
	BuffEffectC.EnableBuff(lpObj->m_Index, 19, 10, 0, 0, 0);

	GCMagicAttackNumberSend(lpObj,AT_SKILL_BRAND_OF_SKILL,lpObj->m_Index,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum))
			{
				if(lpObj->VpPlayer2[count].type == OBJ_USER)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
					{
						//gObj[tObjNum].m_iSkillBrandOfSkillTime = 10;
						BuffEffectC.EnableBuff(tObjNum, 19, 10, 0, 0, 0);
						GCMagicAttackNumberSend(lpObj,AT_SKILL_BRAND_OF_SKILL,tObjNum,1);
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillStun(int aIndex, int aTargetIndex, CMagicInf * lpMagic, BYTE btX, BYTE btY, BYTE btDir, BYTE btTargetPos)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	int TargePosx = lpObj->X - (8 - (btTargetPos & 15));
	int TargePosy = lpObj->Y - (8 - ((btTargetPos & 240) >> 4));

	int iangle = this->GetAngle(lpObj->X,lpObj->Y,TargePosx,TargePosy);

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			if(lpObj->VpPlayer2[count].type == OBJ_USER || lpObj->VpPlayer2[count].type == OBJ_MONSTER)
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if(OBJMAX_RANGE(tObjNum))
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) <= 4)
					{
						if(SkillElectricSparkHitBox.HitCheck(iangle,lpObj->X,lpObj->Y,gObj[tObjNum].X,gObj[tObjNum].Y))
						{
							//gObj[tObjNum].m_iSkillStunTime = 10;
							BuffEffectC.EnableBuff(tObjNum, 61, 10, 0, 0, 0);
							GCMagicAttackNumberSend(lpObj,AT_SKILL_STUN,tObjNum,1);
							gObjSetPosition(tObjNum,gObj[tObjNum].X,gObj[tObjNum].Y);
						}
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillRemoveStun(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{

	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_STUN,lpObj->m_Index,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{

			tObjNum = lpObj->VpPlayer2[count].number;
			if(OBJMAX_RANGE(tObjNum))
			{
				if(lpObj->VpPlayer2[count].type == OBJ_USER)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6)
					{
						//gObj[tObjNum].m_iSkillStunTime = 0;
						BuffEffectC.DelEffect(&gObj[tObjNum], 61);
						GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_STUN,tObjNum,1);
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
return true;
}




BOOL CObjUseSkill::SkillAddMana(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;
	gObjSetKillCount(aIndex,0);

	lpObj->AddMana -= lpObj->m_iSkillManaSwell;

	int iSwelledMana = short(lpObj->MaxMana + lpObj->AddMana) * 50 / 100;
	lpObj->AddMana += iSwelledMana;
	lpObj->m_iSkillManaSwellTime = 60;
	lpObj->m_iSkillManaSwell = iSwelledMana;

	GCManaSend(lpObj->m_Index,lpObj->MaxMana + lpObj->AddMana,0xFE,0,lpObj->MaxBP + lpObj->AddBP);

	if( (lpObj->MaxMana + lpObj->AddMana) < lpObj->Mana)
	{
		lpObj->Mana = lpObj->MaxMana + lpObj->AddMana;
	}

	GCManaSend(lpObj->m_Index,lpObj->Mana,0xFF,0,lpObj->BP);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_MANA,lpObj->m_Index,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum) && lpObj->VpPlayer2[count].type == OBJ_USER)
			{
				if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
				{
					if(lpObj->GuildNumber > 0 && gObj[tObjNum].GuildNumber > 0)
					{
						if(lpObj->GuildNumber != gObj[tObjNum].GuildNumber)
						{
							count++;
							continue;
						}

						gObj[tObjNum].AddMana -= gObj[tObjNum].m_iSkillManaSwell;
						iSwelledMana = short(gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana) * 50 / 100;
						//gObj[tObjNum].AddMana += iSwelledMana;

						//gObj[tObjNum].m_iSkillManaSwellTime = 60;
						//gObj[tObjNum].m_iSkillManaSwell = iSwelledMana;


						GCManaSend(tObjNum,gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana,0xFE,0,gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP);

						if(gObj[tObjNum].Mana > gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana)
						{
							gObj[tObjNum].Mana = gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana;
						}

						GCManaSend(tObjNum,gObj[tObjNum].Mana,0xFF,0,gObj[tObjNum].BP);

						BuffEffectC.EnableBuff(tObjNum, 9, 60, iSwelledMana, 0, 0);
						GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_MANA,tObjNum,1);
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillCloaking(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	if(OBJMAX_RANGE(aTargetIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	if(lpTargetObj->Type != OBJ_USER)
	{
		LogAddTD("[ANTI-HACK][Cloaking Skill] [%s][%s] Invalid Targeting  TargetType [%d] TargetClass [%d]",
			lpObj->AccountID,lpObj->Name,lpTargetObj->Type,lpTargetObj->Class);
		return false;
	}

	gObjSetKillCount(aIndex,0);

	GCMagicAttackNumberSend(lpObj,AT_SKILL_INVISIBLE,lpObj->m_Index,1);
	//lpTargetObj->m_iSkillInvisibleTime = 60;

	BuffEffectC.EnableBuff(lpTargetObj->m_Index, 18, 60, 0, 0, 0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_INVISIBLE,aTargetIndex,1);
	return true;
}




BOOL CObjUseSkill::SkillRemoveCloaking(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_INVISIBLE,lpObj->m_Index,1);

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum) && lpObj->VpPlayer2[count].type == OBJ_USER)
			{
				if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
				{
					//gObj[tObjNum].m_iSkillInvisibleTime = 0;
					BuffEffectC.DelEffect(&gObj[tObjNum], 18);
					GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_INVISIBLE,tObjNum,1);
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillRemoveMagic(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_MAGIC,lpObj->m_Index,1);

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum) && lpObj->VpPlayer2[count].type == OBJ_USER)
			{
				if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
				{
					this->RemoveAllCharacterInvalidMagicAndSkillState(&gObj[tObjNum]);
					GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_MAGIC,tObjNum,1);
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}


////////////////////////////////////////////////////////////////

BOOL CObjUseSkill::SkillFireScream(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(g_SkillAdditionInfo.GetFireScreamSkill() == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(gObjIsConnected(lpObj->m_Index) == false && gObjIsConnected(lpTargetObj->m_Index) == false)
	{
		return false;
	}

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(lpObj->Class != CLASS_DARKLORD)
	{
		return false;
	}

	gObjAttack(lpObj,lpTargetObj,lpMagic,0,0,0,0);
	return true;
}



BOOL CObjUseSkill::FireScreamExplosionAttack(LPOBJ lpObj, LPOBJ lpTargetObj, int iAttackDamage)
{

	if(gObjIsConnected(lpObj->m_Index) == false && gObjIsConnected(lpTargetObj->m_Index) == false)
	{
		return false;
	}

	if(rand()%10000 > g_SkillAdditionInfo.GetFireScreamExplosionRate())
	{
		return false;
	}

	int iExplosionDamage = iAttackDamage / 10;
	int iTarObjNum;

	if(iExplosionDamage < 1)
	{
		return true;
	}

	int iCount = 0;
	int bEnableAttack;

	while( true )
	{
		if(lpObj->VpPlayer2[iCount].state != 0)
		{
			iTarObjNum = lpObj->VpPlayer2[iCount].number;

			if(iTarObjNum >= 0)
			{
				bEnableAttack = 0;

				if(gObj[iTarObjNum].Type == OBJ_MONSTER && gObj[iTarObjNum].m_RecallMon < 0)
				{
					bEnableAttack = 1;
				}
				else if(lpTargetObj->Type == OBJ_USER && lpObj->Type == OBJ_USER && gObj[iTarObjNum].Type != OBJ_NPC)
				{
					bEnableAttack = 1;
				}
				else if(lpTargetObj->m_cChaosCastleIndex == gObj[iTarObjNum].m_cChaosCastleIndex && lpTargetObj->m_cChaosCastleIndex != -1)
				{
					bEnableAttack = 1;
				}

				if(bEnableAttack != 0)
				{
					if(lpObj->m_Index != gObj[iTarObjNum].m_Index)
					{
						int iSkillDistance = gObjCalDistance(lpTargetObj,&gObj[iTarObjNum]);

						if(iSkillDistance <= g_SkillAdditionInfo.GetFireScreamExplosionAttackDistance())
						{
							gObjAddMsgSendDelay(lpObj,54,iTarObjNum,100,iExplosionDamage);
						}
					}
				}
			}
		}

		iCount++;

		if(iCount > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}


BOOL CObjUseSkill::RemoveCloakingEffect(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	gObj[aIndex].m_iSkillInvisibleTime = 0;
	BuffEffectC.DelEffect(&gObj[aIndex], 18);
	return true;
}


void CObjUseSkill::SpecificSkillAdditionTreat(LPOBJ lpObj, LPOBJ lpTargetObj, CMagicInf * lpMagic, int iAttackDamage)
{
	BYTE bySkillNum = lpMagic->m_Skill;

	if(bySkillNum == AT_SKILL_FIRESCREAM)
	{
		gObjUseSkill.FireScreamExplosionAttack(lpObj,lpTargetObj,iAttackDamage);
	}
}

int CObjUseSkill::RemoveSpecificSkillState(LPOBJ lpObj, int iSkillNumber)
{
	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	int BuffNum = 0;

	if(iSkillNumber == AT_SKILL_ATTACK)
	{
		lpObj->m_SkillAttackTime = 0;
		lpObj->m_SkillAttack = 0;
		BuffNum = 1;
	}
	else if(iSkillNumber == AT_SKILL_DEFENSE)
	{
		lpObj->m_SkillDefenseTime = 0;
		lpObj->m_SkillDefense = 0;
		BuffNum = 2;
	}
	BuffEffectC.DelEffect(lpObj, BuffNum);
	return true;
}

int CObjUseSkill::SkillFenrirAttack(int aIndex,int aTargetIndex,CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	if(lpObj->Level < 300)
	{
		return false;
	}

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					}
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;


						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex]) == 1)
						{
							EnableAttack = 1;
						}
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6)
					{
						bAttack = 0;

						if(HitCount >= 5)
						{
							bAttack = 0;
						}
						else
						{
							bAttack = 1;
						}

						if(tObjNum == aTargetIndex)
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,53,tObjNum,300,lpMagic->m_Skill,0);
							HitCount++;
						}
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}

int CObjUseSkill::SkillInfinityArrow(int aIndex,int aTargetIndex,CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(lpObj->Class != CLASS_ELF || lpObj->ChangeUP == 0)
	{
		return false;
	}

	if(lpObj->m_Index != aTargetIndex)
	{
		return false;
	}

	if(lpObj->m_iMuseElfInfinityArrowSkillTime > 0)
	{
		return false;
	}

	//lpObj->m_iMuseElfInfinityArrowSkillTime = g_SkillAdditionInfo.GetInfinityArrowSkillTime();
	BuffEffectC.EnableBuff(lpObj->m_Index, 6, g_SkillAdditionInfo.GetInfinityArrowSkillTime(), 0, 0, 0);
	GCMagicAttackNumberSend(lpObj,0x4D,lpObj->m_Index,1);
	LogAddTD("[%s][%s] Use Infinity Arrow Skill (Time:%d)(Character Level : %d)(ChangeUp: %d)",
		lpObj->AccountID,lpObj->Name,lpObj->m_iMuseElfInfinityArrowSkillTime,lpObj->Level,lpObj->ChangeUP);
	return true;
}

int CObjUseSkill::GetAddUseMana(LPOBJ lpObj,CMagicInf * lpMagic)
{
	int iRetValue = 0;

	if(lpObj->Class == CLASS_ELF && lpObj->Type == OBJ_USER && lpObj->ChangeUP == 1 && lpObj->m_iMuseElfInfinityArrowSkillTime > 0)
	{
		if(lpMagic->m_Skill == AT_SKILL_CROSSBOW
			|| lpMagic->m_Skill == AT_SKILL_BOW
			|| lpMagic->m_Skill == AT_SKILL_ELFHARDEN
			|| lpMagic->m_Skill == AT_SKILL_PENETRATION
			|| lpMagic->m_Skill == AT_SKILL_5CROSSBOW)
		{
			int iArrowLevel = 0;

			CItem * Right = &lpObj->pInventory[0];
			CItem * Left = &lpObj->pInventory[1];

			if(Right->m_Type >= ITEMGET(4,8) && Right->m_Type <= ITEMGET(4,14)
				|| Right->m_Type == ITEMGET(4,16)
				|| Right->m_Type == ITEMGET(4,18)
				|| Right->m_Type == ITEMGET(4,19))
			{
				if(Left->m_Type == ITEMGET(4,7))
				{
					iArrowLevel = Left->m_Level;
				}
			}
			else if(Left->m_Type >= ITEMGET(4,0) && Left->m_Type <= ITEMGET(4,6)
				|| Left->m_Type == ITEMGET(4,17)
				|| Left->m_Type == ITEMGET(4,20)
				|| Left->m_Type == ITEMGET(4,21)
				|| Left->m_Type == ITEMGET(4,22))
			{
				if(Right->m_Type == ITEMGET(4,15))
				{
					iArrowLevel = Right->m_Level;
				}
			}

			if(iArrowLevel == 0)
			{
				iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus0();
			}
			else if(iArrowLevel == 1)
			{
				iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus1();
			}
			else if(iArrowLevel == 2)
			{
				iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus2();
			}
		}
	}
	return iRetValue;
}

bool CObjUseSkill::SkillGhostPhantomAttack(int aIndex, CMagicInf *lpMagic, BYTE x, BYTE y, int aTargetIndex, int Distance, int MultiAttack, int AttackDelay)
{
  	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	int HitCount = 4;
	int MaxHitCount = 8;
	int CurrHitCount = 0;
	int count = 0;
	int tObjNum;
	int EnableAttack;
	int DuelIndex = lpObj->m_iDuelUser;

	if(lpMagic->m_Skill == 237)
	{
		HitCount = 8;
		MaxHitCount = 12;
	}

	int iSkillDistance = MagicDamageC.GetSkillDistance(lpMagic->m_Skill);

	if(this->CalDistance(x, y, lpObj->X, lpObj->Y) <= iSkillDistance)
	{
		while(true)
		{
			if(lpObj->VpPlayer2[count].state != 0)
			{
				tObjNum = lpObj->VpPlayer2[count].number;
				if(tObjNum >= 0)
				{
					EnableAttack = 0;
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					if(tObjNum == lpObj->m_iDuelUser)// || MultiAttack == 1)
					{
						EnableAttack = 1;
					}
					if(lpObj->VpPlayer2[count].type == OBJ_NPC || lpObj->MapNumber != MAP_INDEX_CASTLESIEGE || g_CastleSiegeSync.GetCastleState() != 7)
					{
						int CallMonIndex = gObj[tObjNum].m_Index;

						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
						{
							EnableAttack = 1;
						}
					}
					else
					{
						EnableAttack = 1;
					}

					if(EnableAttack)
					{
						if(gObj[tObjNum].X >= x-Distance)
						{
							if(gObj[tObjNum].X <= x+Distance)
							{
								if(gObj[tObjNum].Y >= y-Distance)
								{
									if(gObj[tObjNum].Y <= y+Distance)
									{
										gObj[tObjNum].lpAttackObj = lpObj;
										++CurrHitCount;

										BOOL Attack;

										if(CurrHitCount <= HitCount)
										{
											Attack = TRUE;
										}
										else
										{
											Attack = rand()%2;
										}
										if(CurrHitCount > MaxHitCount)
										{
											Attack = FALSE;
										}

										if(Attack)
										{
											if(AttackDelay)
											{
												gObjAddAttackProcMsgSendDelay(lpObj, 50, tObjNum, AttackDelay, lpMagic->m_Skill, 0);
											}
											else
											{
												gObjAttack(lpObj, &gObj[tObjNum], lpMagic, 1, 0, 0, 0);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			++count;
			if(count > MAX_VIEWPORT-1)
				break;
		}
	}
	return 1;
}

void CObjUseSkill::SkillSwordPower(int aIndex, int aTargetIndex, int skill_level)
{
	if(!OBJMAX_RANGE(aIndex))
		return ;

	int inc = (gObj[aIndex].Energy / 30);
	int dec = 10;
	int Time = (gObj[aIndex].Energy / 20) + 30;

	BuffEffectC.EnableBuff(aIndex, 81, Time, inc, dec, 0);
	GCMagicAttackNumberSend(&gObj[aIndex], 218, aIndex, 1);
}

void CObjUseSkill::SkillInnovation(int aIndex, int aTargetIndex, CMagicInf* lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int DefenseDown = ((lpObj->AddEnergy+lpObj->Energy)/10+2);
		int atdmgmin;
	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{			
						if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6 && gObj[tObjNum].m_ViewSkillState[eVS_SKILL_NICEWEEK] == 0)
						{		

							if(DefenseDown > 100)
							{
								DefenseDown = 70;
							}
	

							gObj[tObjNum].m_Defense -= DefenseDown;
							//GCStateInfoSend(&gObj[tObjNum],1, eVS_SKILL_NICEWEEK,0,0 );
							BuffEffectC.EnableBuff(tObjNum,eVS_SKILL_NICEWEEK,20,DefenseDown,0,0);
							GCMagicAttackNumberSend(lpObj,0xDD,tObjNum,skillSuccess);
							gObj[tObjNum].m_SummonerSkillInnovationTime = 20;
							
						}
					}
					else
					{

					}
				}
			}
		}
		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return ;
/*    int skillSuccess = 1;
	LPOBJ lpObj = &gObj[aIndex];
    LPOBJ lpTargetObj = &gObj[aTargetIndex];


	if(lpObj->Class != CLASS_SUMMONER)
	{
	    return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber))
	{
		return;
	}

	int DefenseDown = ((lpObj->AddEnergy+lpObj->Energy)/10+2);

	if(DefenseDown > 100)
	{
		DefenseDown = 100;
	}
	lpTargetObj->m_Defense -= DefenseDown;
	//lpTargetObj->m_SummonerSkillSleepTime = sleeptime / 1000;
	GCStateInfoSend(lpTargetObj,1, eVS_SKILL_NICEWEEK,0,0 );
	GCMagicAttackNumberSend(lpObj,0xDD,lpTargetObj->m_Index,skillSuccess);*/
}
void CObjUseSkill::SkillWeakness(int aIndex, int aTargetIndex, CMagicInf* lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int bAttack;
	int atdmgmax;
	int val;
	int val2;
	int AttackDown = ((lpObj->AddEnergy+lpObj->Energy)/10+2);
		int atdmgmin;
	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{			
						if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6 && gObj[tObjNum].m_ViewSkillState[eVS_SKILL_INNERBEIYSEYON] == 0)
						{		
							atdmgmin = gObj[tObjNum].m_AttackDamageMin;
							atdmgmax = gObj[tObjNum].m_AttackDamageMax;
							if(AttackDown > 70)
							{
								AttackDown = 70;
							}
	
							 val = atdmgmin/100;
							 val2 = atdmgmax/100;

							gObj[tObjNum].m_AttackDamageMax -= val2*AttackDown;
							gObj[tObjNum].m_AttackDamageMin -= val*AttackDown;
//							GCStateInfoSend(&gObj[tObjNum],1, eVS_SKILL_INNERBEIYSEYON,0,0 );
							BuffEffectC.EnableBuff(aIndex,eVS_SKILL_INNERBEIYSEYON,20,val2*AttackDown,val*AttackDown,0);
							GCMagicAttackNumberSend(lpObj,0xDE,tObjNum,skillSuccess);
							gObj[tObjNum].m_SummonerSkillWeaknessTime = 20;
						}
					}
					else
					{

					}
				}
			}
		}
		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return ;

}

void CObjUseSkill::SkillReflex(int aIndex, CMagicInf *lpMagic, int aTargetIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return ;
	}
	int Index = aIndex;
	if(OBJMAX_RANGE(aTargetIndex))
	{
		Index = aTargetIndex;
	}

	int RefDmg = gObj[aIndex].Energy / 42;
	RefDmg += 30;

	int Time = ((gObj[aIndex].Energy / 25) + 30);
	if(BuffEffectC.BuffSearch(&gObj[Index], 71) != 0)
	{
		if(RefDmg == gObj[Index].m_SkillInfo.DamageRefVal)
		{
			GCMagicAttackNumberSend(&gObj[aIndex], lpMagic->m_Skill, Index, 0);
			return;
		}
	}
	//gObj[aTargetIndex].m_iSkillDamageRefTime = Time;
	//gObj[aTargetIndex].m_iSkillDamageRefValue = RefDmg;
	//gObj[aTargetIndex].DamageReflect += RefDmg;
	BuffEffectC.EnableBuff(Index, 71, Time, RefDmg, 0, 0);
	GCMagicAttackNumberSend(&gObj[aIndex], lpMagic->m_Skill, Index, 1);
}

// Decompiled from 1.00.90 GS

void CObjUseSkill::SkillFiveShot(int aIndex, CMagicInf * lpMagic, BYTE TargetPos, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	this->SkillFrustrum3(aIndex, TargetPos, 6.0, 7.0, 1.0, 0);
	float Matrix[3][4];
	float Angle[3];
	float p[4][3];
	float Frustrum[5][3];
	float NewFrustrum[5][3];
	int FrustrumX[5];
	int FrustrumY[5];
	int AttackTable[5];
	// one shot per angle of 20 degress
	Angle[0] = 0;
	Angle[1] = 6.0;
	Angle[2] = 0;
	p[0][0] = 0;
	p[0][1] = 0;
	p[0][2] = 40.0;
	p[1][0] = 0;
	p[1][1] = 0;
	p[1][2] = 20.0;
	p[2][0] = 0;
	p[2][1] = 0;
	p[2][2] = 340.0;
	p[3][0] = 0;
	p[3][1] = 0;
	p[3][2] = 320.0;
	AngleMatrix(p[0], Matrix);
	VectorRotate((const float *)&Angle[0], (const float *)&Matrix[0], (float *)&Frustrum[0]);
	AngleMatrix(p[1], Matrix);
	VectorRotate((const float *)&Angle[0], (const float *)&Matrix[0], (float *)&Frustrum[1]);
	Frustrum[2][0] = 0.0;
	Frustrum[2][1] = 6.0;
	Frustrum[2][2] = 0.0;
	AngleMatrix(p[2], Matrix);
	VectorRotate((const float *)&Angle[0], (const float *)&Matrix[0], (float *)&Frustrum[3]);
	AngleMatrix(p[3], Matrix);
	VectorRotate((const float *)&Angle[0], (const float *)&Matrix[0], (float *)&Frustrum[4]);
	p[0][0] = 0;
	p[0][1] = 0;
	p[0][2] = (360 * TargetPos / 255);
	AngleMatrix(p[0], Matrix);
	for(int i=0;i<5;++i)
	{
		VectorRotate((const float *)&Frustrum[i], (const float *)&Matrix[0], (float *)&NewFrustrum[i]);
		FrustrumX[i] = (int)NewFrustrum[i][0] + lpObj->X;
		FrustrumY[i] = (int)NewFrustrum[i][1] + lpObj->Y;
	}

	int tObjNum;
	int count = 0;
	int EnableAttack;
	int DuelIndex = lpObj->m_iDuelUser;

	while(true)
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;
			EnableAttack = 0;
			if(tObjNum >= 0)
			{
				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				if(lpObj->VpPlayer2[count].type == OBJ_NPC || lpObj->MapNumber != MAP_INDEX_CASTLESIEGE || g_CastleSiegeSync.GetCastleState() != 7)
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}
				else
				{
					EnableAttack = 1;
				}
				if(g_DuelManager.DuelCheck(lpObj, &gObj[tObjNum]))
				{
					EnableAttack = 1;
				}
			}
			if ( EnableAttack )
			{
				if(gObj[aIndex].Type == OBJ_USER)
				{
					for ( int j=0;j<5;++j)
					{
						AttackTable[j] = ((gObj[tObjNum].Y - lpObj->Y) * (FrustrumX[j] - lpObj->X))
							- ((gObj[tObjNum].X - lpObj->X) * (FrustrumY[j] - lpObj->Y));
						if(SkillTestFrustrum(gObj[tObjNum].X, gObj[tObjNum].Y, aIndex) == TRUE)
						{
							if(AttackTable[j] > -5 && AttackTable[j] < 5)
							{
								gObjAttack(lpObj, &gObj[tObjNum], lpMagic, 1, 0 ,0 ,0);
							}
						}
					}
				}
				else if(gObj[aIndex].Type == OBJ_MONSTER)
				{
					gObjAttack(lpObj, &gObj[tObjNum], lpMagic, 1, 0, 0, 0);
				}
			}
		}
		++count;
		if(count > MAX_VIEWPORT-1)
			break;
	}
}

int CObjUseSkill::SkillLightingShock(int aIndex, CMagicInf *lpMagic, BYTE x, BYTE y, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	int count = 0;
	BOOL EnableAttack = false;
	int tObjNum;
	int DuelIndex = lpObj->m_iDuelUser;

    for(int n=0;n < MAX_VIEWPORT;n++)
	{
        if(lpObj->VpPlayer2[n].state <= 0)
		{
		    continue;
		}
		tObjNum = lpObj->VpPlayer2[count].number;

		if(tObjNum >= 0)
		{
			EnableAttack = 0;

			if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
			{
				EnableAttack = 1;
			}
			else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
			{
				EnableAttack = 1;
			}
			else
			{
				int CallMonIndex = gObj[tObjNum].m_Index;

				if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
				{
					CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
				}

				if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
				{
					EnableAttack = 1;
				}
			}
		
		if(EnableAttack)
		{
			if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
			{
				gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,300,lpMagic->m_Skill,0);
				count++;

				if(count >= 5)
				{
					break;
				}
			}
		}
	}
	}
	return 1;
}

int CObjUseSkill::SkillFlameStrike(int aIndex, CMagicInf *lpMagic, BYTE TargetPos, int aTargetIndex)
{
	int count = 0;
	int tObjNum;
	int EnableAttack = 0;
	int HitCount = 0;
	this->SkillFrustrum3(aIndex, TargetPos, 2.0, 4.0, 5.0, 0.0);
	LPOBJ lpObj = &gObj[aIndex];
	while(true)
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;
			EnableAttack = 0;
			if(tObjNum >= 0)
			{
				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				if(lpObj->VpPlayer2[count].type == OBJ_NPC || lpObj->MapNumber != MAP_INDEX_CASTLESIEGE || g_CastleSiegeSync.GetCastleState() != 7)
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}
				else
				{
					EnableAttack = 1;
				}
				if(g_DuelManager.DuelCheck(lpObj, &gObj[tObjNum]))
				{
					EnableAttack = 1;
				}
			}
			if ( EnableAttack )
			{
			if(gObjCalDistance(&gObj[aIndex],&gObj[tObjNum]) < 4 && EnableAttack)
			{
				int Attack = 0;
				if( HitCount < 8 )
				{
					Attack = 1;
				}
				else
				{
					Attack = rand()%2;
				}
				if(Attack)
				{
					gObjAttack(lpObj, &gObj[tObjNum], lpMagic, 1, 0, 0, 0);
					gObjAttack(lpObj, &gObj[tObjNum], lpMagic, 1, 0, 0, 0);
				}
			//	gObjAddAttackProcMsgSendDelay(lpObj,50,index,400,lpMagic->m_Skill,bCombo);
			}
				/*if(SkillTestFrustrum(gObj[tObjNum].X, gObj[tObjNum].Y, aIndex) == true)
				{
					int Attack = 0;
					if( HitCount < 8 )
					{
						Attack = 1;
					}
					else
					{
						Attack = rand()%2;
					}
					if(Attack)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, 1, 0, 0, 0);
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, 1, 0, 0, 0);
					}
				}*/
			}
		}
		++count;
		if(count > MAX_VIEWPORT-1)
			break;
	}
	return 1;
}

int CObjUseSkill::SkillBlowOfDestruction(int aIndex, CMagicInf *lpMagic, BYTE x, BYTE y, int aTargetIndex, BOOL bCombo)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
	    return 0;
	}
	LPOBJ lpObj = &gObj[aIndex];
	BOOL EnableAttack;

    for(int n=0;n < MAX_VIEWPORT;n++)
	{
        if(lpObj->VpPlayer2[n].state <= 0)
		{
		    continue;
		}
		EnableAttack = FALSE;
		int index = lpObj->VpPlayer2[n].number;


		if(gObj[index].Type == OBJ_MONSTER && gObj[aIndex].m_RecallMon < 0)
		{
			EnableAttack = TRUE;
		}

		if(aTargetIndex == index || index == lpObj->m_iDuelUser)
		{
			EnableAttack = TRUE;
		}

		int summon = aIndex;

		if(gObj[aIndex].Type == OBJ_MONSTER && gObj[aIndex].m_RecallMon >= 0)
		{
			summon = gObj[aIndex].m_RecallMon;
		}

		if(gObjTargetGuildWarCheck(&gObj[summon],lpObj) != 0)
		{
			EnableAttack = TRUE;
		}

		if(this->CalDistance(x,y,gObj[index].X,gObj[index].Y) < 3 && EnableAttack)
		{
            gObjAddAttackProcMsgSendDelay(lpObj,50,index,400,lpMagic->m_Skill,bCombo);

			if(bCombo != 0)
			{
		        GCMagicAttackNumberSend(lpObj,59,aIndex,1);
			}
		}
	}
}

int CObjUseSkill::SkillShieldRefill(int aIndex, CMagicInf *lpMagic, int aTargetIndex)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int skill_level = lpMagic->m_Level;

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		GCMagicAttackNumberSend(lpObj, lpMagic->m_Skill, aTargetIndex, 0);
		return 0;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		GCMagicAttackNumberSend(lpObj, lpMagic->m_Skill, aTargetIndex, 0);
		return 0;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		GCMagicAttackNumberSend(lpObj, lpMagic->m_Skill, aTargetIndex, 0);
		return 0;
	}
	if(g_DuelManager.DuelCheck(lpTargetObj))
	{
		lpTargetObj = lpObj;
	}
	if(lpObj->iShield < lpObj->iAddShield + lpObj->iMaxShield)
	{
		float skill_shield = ((lpObj->Level + lpObj->Energy)/4);
		lpObj->iShield += skill_shield;
		if(lpObj->iShield > lpObj->iAddShield + lpObj->iMaxShield)
		{
			lpObj->iShield = lpObj->iAddShield + lpObj->iMaxShield;
		}
		if(lpTargetObj->Type == OBJ_USER)
		{
			GCReFillSend(lpTargetObj->m_Index, lpTargetObj->Life, 0xFF, 0, lpObj->iShield);
			GCMagicAttackNumberSend(lpObj, AT_SKILL_REDUCEDMGSHIELD, lpTargetObj->m_Index, 1);

			for(int n = 0; n < MAX_VIEWPORT; n++)
			{
				if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
				{
					LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
					if(lpMonster->m_iCurrentAI != 0)
					{
						lpMonster->m_Agro.IncAgro(lpObj->m_Index, lpObj->Energy / 5 / 40);
					}
				}
			}
		}
	}
	else
	{
		GCMagicAttackNumberSend(lpObj, AT_SKILL_REDUCEDMGSHIELD, lpTargetObj->m_Index, 0);
	}
}
