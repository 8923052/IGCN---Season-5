#include "user.h"

#define MAX_BOSS_OBJ_INDEX	800

class CBossObjInfo
{

public:

	CBossObjInfo()
	{
		this->Reset();
	}

	virtual ~CBossObjInfo(){return;}

	void Reset()
	{
		for ( int iCount=0;iCount<MAX_BOSS_OBJ_INDEX;iCount++)
		{
			this->m_iObjIndex[iCount]=-1;
		}

		this->m_iObjCount=0;
	}

	BOOL AddObj(int iIndex)
	{
		if ( this->m_iObjCount >= MAX_BOSS_OBJ_INDEX )
		{
			return FALSE;
		}

		this->m_iObjIndex[this->m_iObjCount] = iIndex;
		this->m_iObjCount++;

		return TRUE;
	}

	int GetCount()
	{
		return this->m_iObjCount;
	}
	
public:

	int m_iObjCount;	// 4
	int m_iObjIndex[MAX_BOSS_OBJ_INDEX];	// 8
};

class BossInv
{
public:
		BossInv();
		virtual ~BossInv();

		void MonsterInvade();
		void End();
		void UserReward(LPOBJ lpObj);
		void Run();

private:
	DWORD EventStartTime;
	DWORD LiveMonsterCount;
	BYTE STATE;
}; 
extern BossInv cBossInv;