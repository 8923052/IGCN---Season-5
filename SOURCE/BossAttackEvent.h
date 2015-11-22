#ifndef BOSSATTACKEVENT_H
#define BOSSATTACKEVENT_H

#define BOSS_MAXMONSTER  512
struct BOSSMONSTERSTRUCT
{
	BYTE bIsAlive;
	int iIndex;
	int iClass;
	BYTE iHeroMonster;
	int Count;
};

struct BOSSPLAYERSTRUCT
{
	BYTE bIsAlive;
	int iIndex;
};

class CBossAttack
{

public:
	void Init();
	void ReadEventFile(char *file);
	void Run();
	void AddMonster();
	void RemoveMonster();
	void CheckDieProc(OBJECTSTRUCT * lpObj, OBJECTSTRUCT *lpTargetObj);
	void EndEvent();
	void GiveReward(OBJECTSTRUCT *lpObj);
	int GetActiveMonsterCount();
	int GetActiveUserCount();
	BYTE STATE;

private:
	BOSSMONSTERSTRUCT m_MonsterData[BOSS_MAXMONSTER];
	BOSSPLAYERSTRUCT m_PlayerData[OBJ_STARTUSERINDEX];
	int MobCount;
	BYTE PlayerCount;

};
extern CBossAttack g_BossAttack;
#endif