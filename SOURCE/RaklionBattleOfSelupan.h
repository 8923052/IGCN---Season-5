#pragma once

#define RAKLION_SELUPAN_STATE_INFO	 11

#define RAKLION_SELUPAN_NONE		0
#define RAKLION_SELUPAN_STANDBY		1
#define RAKLION_SELUPAN_PATTERN1	2
#define RAKLION_SELUPAN_PATTERN2	3
#define RAKLION_SELUPAN_PATTERN3	4
#define RAKLION_SELUPAN_PATTERN4	5
#define RAKLION_SELUPAN_PATTERN5	6
#define RAKLION_SELUPAN_PATTERN6	7
#define RAKLION_SELUPAN_PATTERN7	8
#define RAKLION_SELUPAN_DIE			9


class CRaklionBattleOfSelupan
{
public:

	CRaklionBattleOfSelupan();
	virtual ~CRaklionBattleOfSelupan();

	int GetSelupanSkillDelay();
	void SetSelupanSkillDelay(int iSkillDelay);
	void DeleteSummonMonster();
	void DeleteSelupan();
	float GetSelupanHP();
	int GetSelupanIndex();
	int GetSelupanBerserker();
	int GetSelupanEnemy();
	void SummonMonster();
	bool CreateSelupan();
	void SetState(int iBattleOfSelupanState);
	void SetPatternCondition(int iPatternCondition[6]);
	void ManageSelupanHP();
	void SetState_NONE();
	void SetState_STANDBY();
	void SetState_PATTERN1();
	void SetState_PATTERN2();
	void SetState_PATTERN3();
	void SetState_PATTERN4();
	void SetState_PATTERN5();
	void SetState_PATTERN6();
	void SetState_PATTERN7();
	void SetState_DIE();
	void ProcState_NONE();
	void ProcState_STANDBY();
	void ProcState_PATTERN1();
	void ProcState_PATTERN2();
	void ProcState_PATTERN3();
	void ProcState_PATTERN4();
	void ProcState_PATTERN5();
	void ProcState_PATTERN6();
	void ProcState_PATTERN7();
	void ProcState_DIE();
	int  GetBattleOfSelupanState() { return this->m_iBattleOfSelupanState; };
	void SetBattleOfSelupanState(int iState) {this->m_iBattleOfSelupanState = iState; };
	void SetSuccessValue(BOOL bIsSuccess){this->m_bIsSuccess = bIsSuccess;}
	BOOL GetSuccessValue(){return this->m_bIsSuccess;}
	void Run();
	void UseSelupanSkill(int iMonsterSkill);
	void UseFirstSkill();
	void UsePoisonAttack();
	void UseIceStorm();
	void UseIceStrike();
	void UseSummon();
	void UseHeal();
	void UseFreeze();
	void UseTeleport();
	void UseInvisibility();
	void UseBerserkerCancel();
	void UseBerserker1();
	void UseBerserker2();
	void UseBerserker3();
	void UseBerserker4();
	void InitSelupanIndex();
	void SetSkillRule();

private:
	int m_iObjSelupanIndex;
	int m_iObjDamageMin;
	int m_iObjDamageMax;
	int m_iSelupanSkillDelay;
	int m_iSkillDelay;
	int m_iSkillBerserker;
	int m_iLastSkill;
	bool m_tbSkillRule[9][7];
	int m_tiPatternCondition[6];
	bool m_bSelupanAppear;
	bool m_bIsSuccess;

	int m_iBattleOfSelupanState;
};