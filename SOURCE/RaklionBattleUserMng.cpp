// RaklionBattleUserMng.cpp: implementation of the CRaklionBattleUserMng class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RaklionBattleUserMng.h"
#include "RaklionUtil.h"
#include "Raklion.h"
#include "user.h"

#include "LogProc.h"

CRaklionBattleUserMng g_RaklionBattleUserMng;
static CRaklionUtil RAKLION_UTIL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRaklionBattleUserMng::CRaklionBattleUserMng()
{
	this->ResetAllData();
}

CRaklionBattleUserMng::~CRaklionBattleUserMng()
{
	return;
}



void CRaklionBattleUserMng::ResetAllData()
{
	this->m_iBattleUserCount = 0;
	this->SetMaxUser(MAX_RAKLION_BATTLE_USER);

	for ( int iCount=0;iCount<MAX_RAKLION_BATTLE_USER;iCount++)
	{
		this->m_BattleUser[iCount].ResetData();
	}
}



BOOL CRaklionBattleUserMng::AddUserData(int iIndex)
{
	if ( !gObjIsConnected(iIndex))
	{
		LogAddTD("[Raklion][User Mng] Add User Fail - Disconnect User [%s][%s]",
			gObj[iIndex].AccountID, gObj[iIndex].Name);

		return FALSE;
	}

	for ( int iCount=0;iCount<MAX_RAKLION_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == FALSE )
		{
			this->m_BattleUser[iCount].SetIndex(iIndex);
			this->m_iBattleUserCount++;

			RAKLION_UTIL.NotifyRaklionCurrentState(iIndex, g_Raklion.GetRaklionState(), g_Raklion.GetRaklionDetailState());
			
			return TRUE;
		}
	}

	return FALSE;
}


BOOL CRaklionBattleUserMng::DeleteUserData(int iIndex)
{
	if ( iIndex < 0 || iIndex > OBJMAX-1)
	{
		LogAddTD("[Raklion][User Mng] Delete User Fail - Unvalid Index:%d",
			iIndex);

		return FALSE;
	}

	for ( int iCount=0;iCount<MAX_RAKLION_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == TRUE )
		{
			if ( this->m_BattleUser[iCount].GetIndex() == iIndex )
			{
				this->m_BattleUser[iCount].ResetData();
				this->m_iBattleUserCount--;
				LogAddTD("[Raklion][User Mng] Delete User - [%s][%s] Current Battle User:%d",
					gObj[iIndex].AccountID, gObj[iIndex].Name, this->m_iBattleUserCount);

				return TRUE;
			}
		}
	}

	return FALSE;
}



void CRaklionBattleUserMng::CheckUserState()
{
	int iIndex;

	for ( int iCount=0;iCount<MAX_RAKLION_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == TRUE )
		{
			iIndex = this->m_BattleUser[iCount].GetIndex();

			if ( !gObjIsConnected(iIndex))
			{
				this->DeleteUserData(iIndex);

				LogAddTD("[Raklion][User Mng] Delete User - Disconnect [%s][%s]",
					gObj[iIndex].AccountID, gObj[iIndex].Name);
			}

			if ( gObj[iIndex].MapNumber != MAP_INDEX_RAKLIONBOSS &&
				 gObj[iIndex].m_State == 2 &&
				 gObj[iIndex].Live == 1 )
			{
				this->DeleteUserData(iIndex);

				LogAddTD("[Raklion][User Mng] Delete User - Map Move [%s][%s]",
					gObj[iIndex].AccountID, gObj[iIndex].Name);
			}
		}
	}
}

BOOL CRaklionBattleUserMng::CheckUserIsInEvent(int iIndex)
{
	for ( int i = 0; i < MAX_RAKLION_BATTLE_USER ; ++i )
	{
		if ( iIndex == this->m_BattleUser[i].GetIndex() )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CRaklionBattleUserMng::MoveAllUser(int iGateNumber)
{
	int iIndex;
	BOOL bMoveGateSuccess = FALSE;

	for ( int iCount=0;iCount<MAX_RAKLION_BATTLE_USER;iCount++)
	{
		iIndex = this->m_BattleUser[iCount].GetIndex();

		if ( this->m_BattleUser[iCount].IsUseData()  )
		{
			bMoveGateSuccess = gObjMoveGate(iIndex, iGateNumber);

			if ( bMoveGateSuccess == TRUE )
			{
				LogAddTD("[Raklion][User Mng] [%s][%s] MoveGate(%d)",
					gObj[iIndex].AccountID, gObj[iIndex].Name, iGateNumber);
			}
			else
			{
				this->DeleteUserData(iIndex);

				LogAddTD( "[Raklion][User Mng] [%s][%s] MoveGate Fail (%d)",
					gObj[iIndex].AccountID, gObj[iIndex].Name, iGateNumber);

				gObjMoveGate(iIndex, 137);
			}
		}
	}

	return TRUE;
}



void CRaklionBattleUserMng::SetMaxUser(int iMaxUser)
{
	this->m_iBattleMaxUser = iMaxUser;

	if ( iMaxUser > MAX_RAKLION_BATTLE_USER )
	{
		this->m_iBattleMaxUser = MAX_RAKLION_BATTLE_USER;

		LogAddTD("[Raklion][User Mng] Set Max User:%d",
			iMaxUser);
	}
}



int CRaklionBattleUserMng::GetMaxUser()
{
	return this->m_iBattleMaxUser;
}


int CRaklionBattleUserMng::GetUserCount()
{
	return this->m_iBattleUserCount;
}


BOOL CRaklionBattleUserMng::IsEmpty()
{
	if ( this->m_iBattleUserCount <= 0 )
	{
		return TRUE;
	}

	return FALSE;
}


BOOL CRaklionBattleUserMng::IsOverMaxUser()
{
	if ( this->m_iBattleUserCount >=  MAX_RAKLION_BATTLE_USER )
	{
		return TRUE;
	}

	return FALSE;
}

/*

void CRaklionBattleUserMng::LogBattleWinnerUserInfo(BYTE btFlag, int iElapsedTime)
{
	int iIndex = -1;
	float fTime = iElapsedTime / 1000.0f;

	for ( int iCount=0;iCount<MAX_Raklion_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == TRUE )
		{
			iIndex = this->m_BattleUser[iCount].GetIndex();
			
			LogAddTD("[Raklion][User Mng] WINNER: [%d/ElapsedTime:%0.3f] [%s][%s] MapNumber[%d]-(%d/%d)",
				btFlag, fTime, gObj[iIndex].AccountID, gObj[iIndex].Name,
				gObj[iIndex].MapNumber, gObj[iIndex].X, gObj[iIndex].Y);

			Raklion_UTIL.SendDataRaklionTimeAttackEvent(iIndex, btFlag, fTime);
		}
	}
}
*/