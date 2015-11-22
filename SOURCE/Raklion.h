#pragma once

#include "MapClass.h"
#include "RaklionBattleOfSelupan.h"
#include "RaklionStateInfo.h"

#define MAX_RAKLION_STATE_INFO			11

#define RAKLION_STATE_IDLE				0
#define RAKLION_STATE_NOTIFY_1			1
#define RAKLION_STATE_STANDBY			2
#define RAKLION_STATE_NOTIFY_2			3
#define RAKLION_STATE_READY				4
#define RAKLION_STATE_START_BATTLE		5
#define RAKLION_STATE_NOTIFY_3			6
#define RAKLION_STATE_CLOSE_DOOR		7
#define RAKLION_STATE_ALL_USER_DIE		8
#define RAKLION_STATE_NOTIFY_4			9
#define RAKLION_STATE_END				10

#define RAKLION_EGG_CLASS_RANGE(x)  ( ((x)< 460 )?FALSE:((x) > 462 )?FALSE:TRUE   ) 



class CRaklion
{
public:
	CRaklion();
	virtual ~CRaklion();

	bool LoadData(LPSTR lpszFileName);
	void ResetAllData();
	void SetTimeData(int iAppearanceTime, int iBossZoneCloseTime, int iEndTime);
	void SetEggData(int iEggCount, int iEggHalf);
	void Run();
	void SetState(int iRaklionState);
	void SetState_IDLE();
	void SetState_NOTIFY_1();
	void SetState_STANDBY();
	void SetState_NOTIFY_2();
	void SetState_READY();
	void SetState_START_BATTLE();
	void SetState_NOTIFY_3();
	void SetState_CLOSE_DOOR();
	void SetState_ALL_USER_DIE();
	void SetState_NOTIFY_4();
	void SetState_END();
	void ProcState_IDLE();
	void ProcState_NOTIFY_1();
	void ProcState_STANDBY();
	void ProcState_NOTIFY_2();
	void ProcState_READY();
	void ProcState_START_BATTLE();
	void ProcState_NOTIFY_3();
	void ProcState_CLOSE_DOOR();
	void ProcState_ALL_USER_DIE();
	void ProcState_NOTIFY_4();
	void ProcState_END();
	void SetRaklionEnable(bool bEnable){this->m_bRaklionEnable = bEnable;};
	bool IsRaklionEnable(){return this->m_bRaklionEnable;};
	void SetRaklionState(int iRaklionState){this->m_iRaklionState = iRaklionState;};
	int GetRaklionState(){return this->m_iRaklionState;};
	int GetRaklionDetailState(){return this->m_BattleOfSelupan.GetBattleOfSelupanState();};
	int GetCurrentEggCount(){return this->m_iCurrEggCount;};
	void IncEggCount();
	void DecEggCount();
	void BossEggRegen();
	void BossEggDelete();
	void CheckUserOnRaklionBossMap();

private:
	bool					m_bFileDataLoad;
	int						m_iAppearanceTime;
	DWORD						m_iBossZoneCloseTime;
	int						m_iEndTime;
	int						m_iEggCount;
	int						m_iEggHalf;
	int						m_iRaklionState;
	bool					m_bDateChanged;
	bool					m_bRaklionEnable;
	DWORD					m_dwAppearanceTimeLeft;
	DWORD					m_dwBossZoneCloseTimeLeft;
	DWORD					m_dwEndTimeLeft;
	SYSTEMTIME				m_Time;
	CRaklionBattleOfSelupan m_BattleOfSelupan;
	int						m_iCurrEggCount;
	bool					m_bNotify_1;
};

extern CRaklion g_Raklion;