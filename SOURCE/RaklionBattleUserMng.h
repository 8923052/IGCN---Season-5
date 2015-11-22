#pragma once

#include "RaklionBattleUser.h"

#define MAX_RAKLION_BATTLE_USER	100

class CRaklionBattleUserMng
{

public:

	CRaklionBattleUserMng();
	virtual ~CRaklionBattleUserMng();

	void ResetAllData();
	int AddUserData(int iIndex);
	int DeleteUserData(int iIndex);
	void CheckUserState();
	int MoveAllUser(int iGateNumber);
	int GetUserCount();
	int IsEmpty();
	int IsOverMaxUser();
	//int __thiscall IsBattleUser(int);
	void SetMaxUser(int iMaxUser);
	int GetMaxUser();
	BOOL CheckUserIsInEvent(int iIndex);
	void LogBattleWinnerUserInfo(BYTE btFlag, int iElapsedTime);

public:

	CRaklionBattleUser m_BattleUser[MAX_RAKLION_BATTLE_USER];	// 4
	int m_iBattleUserCount;	// B8
	int m_iBattleMaxUser;	// BC

};


extern CRaklionBattleUserMng g_RaklionBattleUserMng;