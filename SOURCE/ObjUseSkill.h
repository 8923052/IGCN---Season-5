#ifndef OBJUSESKILL_H
#define OBJUSESKILL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MagicInf.h"
#include "user.h"

class CObjUseSkill
{

public:

	CObjUseSkill();
	virtual ~CObjUseSkill();

	int SpeedHackCheck(int aIndex);
	int EnableSkill(BYTE Skill);
	int GetUseMana(int aIndex, CMagicInf* lpMagic);
	int GetAddUseMana(LPOBJ lpObj, CMagicInf* lpMagic);
	int GetUseBP(int aIndex, CMagicInf* lpMagic);
	void UseSkill(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	void UseSkill(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	int RunningSkill(int aIndex, int aTargetIndex, CMagicInf* lpMagic, BOOL bCombo);
	void MaGumSkillDefenseDown(int aIndex, int aTargetIndex, int skill_level);
	void KnightSkillAddLife(int aIndex, CMagicInf * lpMagic);
	void WizardMagicDefense(int aIndex, int aTargetIndex, CMagicInf * lpMagic);
	void MagicCircle(int aIndex, int aTargetIndex, int skill_level);
	void SkillDefense(int aIndex, int aTargetIndex, CMagicInf * lpMagic);
	void SkillAttack(int aIndex, int aTargetIndex, CMagicInf * lpMagic, bool Master);
	int SkillChangeUse(int aIndex);
	void SkillHealing(int aIndex, int aTargetIndex, CMagicInf * lpMagic);
	int SkillMonsterCall(int aIndex, int MonsterType, int x, int y);
	int SkillDeathPoison(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	int SkillSuddenIce(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	int SkillHellFire2Start(int aIndex, CMagicInf* lpMagic);
	int SkillHellFire2(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	void SkillBlowOfFury(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex, BOOL isCombo);
	void SkillWheel(int aIndex, CMagicInf* lpMagic, int aTargetIndex, BOOL isCombo);
	int SkillKnightBlow(int aIndex, int aTargetIndex, CMagicInf* lpMagic, BOOL isCombo);
	void SkillPowerSlash(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE Targetangle, int aTargetIndex);
	void SkillFrustrum(int aIndex, float fangle, float tx, float ty);
	int GetTargetLinePath(int sx, int sy, int tx, int ty,  int* PathX,int* PathY, int distance);
	int GetAngle(int x, int y, int tx,  int ty);
	int CalDistance(int x, int y, int x1, int y1);
	void SkillFrustrum2(int aIndex, float fangle, float tx, float ty);
	void SkillFrustrum3(int aIndex, float fangle, float tx, float ty, float f1, float f2);
	int SkillAreaCheck(int angel, int x, int y,  int tx, int ty,  int dis,  int arc);
	int SkillSpear(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillFireBurst(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillDarkHorseAttack(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int RecallPartyCheck(int aIndex, int skill_level);
	void SkillRecallParty(int aIndex, int skill_level);
	void SkillAddCriticalDamage(int aIndex, int skill_level);
	void SkillElectricSpark(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	int SkillSummon(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillImmuneToMagic(int aIndex, CMagicInf* lpMagic);
	int SkillImmuneToHarm(int aIndex, CMagicInf* lpMagic);
	int SkillKnightRush(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillWizardJavalin(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillElfRush(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillMagumOneFlash(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillMagumDeathCannon(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillDarklordSpaceSplit(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillBrandOfSkill(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillRemoveStun(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillAddMana(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillCloaking(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillRemoveCloaking(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillRemoveMagic(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int RemoveCloakingEffect(int aIndex);
	int SkillStun(int aIndex, int aTargetIndex, CMagicInf* lpMagic, BYTE btX, BYTE btY, BYTE btDir, BYTE btTargetPos);
	int RemoveAllCharacterInvalidMagicAndSkillState(LPOBJ lpObj);
	int RemoveSpecificSkillState(LPOBJ lpObj, int iSkillNumber);
	int SkillFenrirAttack(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillInfinityArrow(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillFireScream(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int FireScreamExplosionAttack(LPOBJ lpObj, LPOBJ lpTargetObj, int iAttackDamage);
	void SpecificSkillAdditionTreat(LPOBJ lpObj, LPOBJ lpTargetObj, CMagicInf* lpMagic, int iAttackDamage);
	void SkillDrainLife(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE targetangle, int aTargetIndex);
	int SkillChainLightning(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	int SkillLightningStorm(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	int SkillRedStorm(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	void SkillSleep(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	void SkillBirds(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	bool SkillGhostPhantomAttack(int aIndex, CMagicInf *lpMagic, BYTE x, BYTE y, int aTargetIndex, int Distance, int MultiAttack, int AttackDelay);
	bool SkillBookNumber12(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	void SkillSwordPower(int aIndex, int aTargetIndex, int skill_level);
	void SkillWeakness(int aIndex,int aTargetIndex, CMagicInf * lpMagic);
	void SkillInnovation(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	void SkillReflex(int aIndex, CMagicInf *lpMagic, int aTargetIndex);
	void SkillFiveShot(int aIndex, CMagicInf * lpMagic, BYTE TargetPos, int aTargetIndex);
	int SkillLightingShock(int aIndex, CMagicInf *lpMagic, BYTE x, BYTE y, int aTargetIndex);
	int RunningMasterSkill(int aIndex, int aTargetIndex, CMagicInf *lpMagic, BOOL bCombo);
	void NewSkillProc(int aIndex, CMagicInf *lpMagic, BYTE x, BYTE y, int aTargetIndex, int aMsgSubCode);
	int SkillFlameStrike(int aIndex, CMagicInf *lpMagic, BYTE TargetPos, int aTargetIndex);
	int SkillBlowOfDestruction(int aIndex, CMagicInf *lpMagic, BYTE x, BYTE y, int aTargetIndex, BOOL bCombo);
	int SkillShieldRefill(int aIndex, CMagicInf *lpMagic, int aTargetIndex);
};


int  DecPartyMemberHPandMP(LPOBJ lpObj);

extern CObjUseSkill gObjUseSkill;

#endif