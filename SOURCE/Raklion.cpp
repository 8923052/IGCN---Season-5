// MAIN RAKLION HATCHERY EVENT FILE
// RAKLION EVENT MAIN PROCESS
// FULLY CODED BY [WOG TEAM] Dudas
// 25/01/2011
// STATUS: 99% (not tested, but should work)

#include "stdafx.h"
#include "Raklion.h"
#include "RaklionBattleUserMng.h"
#include "RaklionUtil.h"
#include "user.h"
#include "..\common\readscript.h"
#include "..\common\winutil.h"
#include "logproc.h"
#include "GameMain.h"
#include "gObjMonster.h"
static CRaklionUtil RAKLION_UTIL;
CRaklion g_Raklion;

CRaklion::CRaklion()
{
	this->m_bFileDataLoad = FALSE;
}

CRaklion::~CRaklion()
{
}

void CRaklion::ResetAllData()
{
	this->m_bNotify_1 = 0;
	this->m_dwAppearanceTimeLeft = 0;
	this->m_dwBossZoneCloseTimeLeft = 0;
	this->m_dwEndTimeLeft = 0;
}

void CRaklion::SetTimeData(int iAppearanceTime, int iBossZoneCloseTime, int iEndTime)
{
	if(iAppearanceTime < 0 || iBossZoneCloseTime < 0 || iEndTime < 0)
	{
		LogAddC(2, "[Raklion][SetTimeData] Exception error");
		return;
	}
	this->m_iAppearanceTime = iAppearanceTime;
	this->m_iBossZoneCloseTime = iBossZoneCloseTime;
	this->m_iEndTime = iEndTime;
}

void CRaklion::SetEggData(int iEggCount, int iEggHalf)
{
	if(iEggCount < 0 || iEggHalf < 0)
	{
		LogAddC(2, "[Raklion][SetEggData] Exception error");
		return;
	}
	this->m_iEggCount= iEggCount;
	this->m_iEggHalf = iEggHalf;
}
int loaded = 0;
bool CRaklion::LoadData(LPSTR lpszFileName)
{
	this->m_bFileDataLoad = FALSE;
	//MsgBox("STOP");

	if( !lpszFileName || !strcmp(lpszFileName, "") )
	{
		MsgBox("[Raklion] - File load error : File Name Error");
		return false;
	}

	try
	{
		int Token;
		int iType = -1;
		int iAppearanceTime;
		int iBossZoneCloseTime;
		int iEndTime;
		int iEggCount;
		int iEggHalf;
		int iSkillDelay;
		int iPatternCondition[6];
		SMDFile = fopen(lpszFileName, "r");

		if ( SMDFile == NULL )
		{
			DWORD dwError = GetLastError();
			MsgBox("[Raklion] - Can't Open %s ", lpszFileName);
			return FALSE;
		}

		this->ResetAllData();

		while ( true )
		{
			Token = GetToken();

			if(Token == END)
			{
				break;
			}

			iType = TokenNumber;
			
			while ( true )
			{
				if( iType == 0 )
				{
					iAppearanceTime = 0;
					iBossZoneCloseTime = 0;
					iEndTime = 0;

					Token = GetToken();

					if(!strcmp("end", TokenString))
					{
						break;
					}

					iAppearanceTime = TokenNumber;

					Token = GetToken();
					iBossZoneCloseTime = TokenNumber;

					Token = GetToken();
					iEndTime = TokenNumber;

					this->m_iAppearanceTime = iAppearanceTime;
					this->m_iBossZoneCloseTime = iBossZoneCloseTime;
					this->m_iEndTime = iEndTime;
				}

				else if ( iType == 1 )
				{
					iEggCount = 0;
					iEggHalf = 0;

					Token = GetToken();

					if(!strcmp("end", TokenString))
					{
						break;
					}

					iEggHalf = TokenNumber;

					Token = GetToken();
					iEggCount = TokenNumber;

					if(iEggHalf < 0)
					{
						MsgBox("[Raklion] - BossEggHalf count error : (%d)", iEggHalf);
						break;
					}

					if(iEggCount < 0)
					{
						MsgBox("[Raklion] - BossEggMax count error : (%d)", iEggCount);
						break;
					}

					this->m_iEggCount= iEggCount;
					this->m_iEggHalf = iEggHalf;
				}
				else if ( iType == 2 )
				{
					iSkillDelay = 0;

					Token = GetToken();

					if(!strcmp("end", TokenString))
					{
						break;
					}

					iSkillDelay = TokenNumber;

					this->m_BattleOfSelupan.SetSelupanSkillDelay(iSkillDelay);
				}
				else if ( iType == 3 )
				{
					memset(&iPatternCondition[0], 0x00, 6);
					if(!strcmp("end", TokenString))
					{
						break;
					}
					for(int i=0;i<6;++i)
					{
						Token = GetToken();
						if(!strcmp("end", TokenString))
						{
							break;
						}
						iPatternCondition[i] = TokenNumber;
					}
					if(loaded == 0)
					{
						this->m_BattleOfSelupan.SetPatternCondition(iPatternCondition);
					}
					loaded = 1;
				}
			}
		}
		fclose(SMDFile);
		LogAddC(2, "[Raklion] - %s file is Loaded", lpszFileName);
		this->m_bFileDataLoad = TRUE;
	}
	catch ( DWORD )
	{
		MsgBox("[Raklion] - Loading Exception Error (%s) File. ", lpszFileName);
	}
	return this->m_bFileDataLoad;
}

void CRaklion::Run()
{
	SYSTEMTIME CurrTime;
	int iCount = 0;
	GetLocalTime(&CurrTime);
	if(this->m_Time.wYear != CurrTime.wYear || this->m_Time.wMonth != CurrTime.wMonth
		|| this->m_Time.wDay != CurrTime.wDay)
	{
		this->m_Time.wDay = CurrTime.wDay;
		this->m_Time.wMonth = CurrTime.wMonth;
		this->m_Time.wYear = CurrTime.wYear;
		this->m_bDateChanged = false;
	}
	if(!this->m_bDateChanged)
	{
		if(CurrTime.wHour == 0)
		{
			if(CurrTime.wMinute == 0)
			{
				if(CurrTime.wSecond == 0)
				{
					for(int i = OBJ_STARTUSERINDEX ; i < OBJMAX ; ++i)
					{
						iCount = 0;
						if(gObj[i].MapNumber != MAP_INDEX_RAKLION)
						{
							if(gObj[i].MapNumber != MAP_INDEX_RAKLIONBOSS)
								continue;
						}

						if(gObj[i].Connected == PLAYER_PLAYING)
						{
							if(gObj[i].Type == OBJ_USER)
							{
								++iCount;
								LogAdd("[Raklion][IsInRaklionEvent] %d/%d/%d %dth User : %s (%s)", CurrTime.wYear, CurrTime.wMonth, CurrTime.wDay, iCount, gObj[i].Name, gObj[i].AccountID);
							}
						}
					}
					this->m_bDateChanged = true;
				}
			}
		}
	}
	if(this->IsRaklionEnable())
	{
		g_RaklionBattleUserMng.CheckUserState();
		this->CheckUserOnRaklionBossMap();

		switch ( this->m_iRaklionState )
		{
			case RAKLION_STATE_IDLE:
				this->ProcState_IDLE();
				break;
			case RAKLION_STATE_NOTIFY_1:
				this->ProcState_NOTIFY_1();
				break;
			case RAKLION_STATE_STANDBY:
				this->ProcState_STANDBY();
				break;
			case RAKLION_STATE_NOTIFY_2:
				this->ProcState_NOTIFY_2();
				break;
			case RAKLION_STATE_READY:
				this->ProcState_READY();
				break;
			case RAKLION_STATE_START_BATTLE:
				this->ProcState_START_BATTLE();
				break;
			case RAKLION_STATE_NOTIFY_3:
				this->ProcState_NOTIFY_3();
				break;
			case RAKLION_STATE_CLOSE_DOOR:
				this->ProcState_CLOSE_DOOR();
				break;
			case RAKLION_STATE_ALL_USER_DIE:
				this->ProcState_ALL_USER_DIE();
				break;
			case RAKLION_STATE_NOTIFY_4:
				this->ProcState_NOTIFY_4();
				break;
			case RAKLION_STATE_END:
				this->ProcState_END();
				break;
		}
	}
}

void CRaklion::SetState(int iRaklionState)
{
	switch ( iRaklionState )
	{
		case RAKLION_STATE_IDLE:
			this->SetState_IDLE();
			break;
		case RAKLION_STATE_NOTIFY_1:
			this->SetState_NOTIFY_1();
			break;
		case RAKLION_STATE_STANDBY:
			this->SetState_STANDBY();
			break;
		case RAKLION_STATE_NOTIFY_2:
			this->SetState_NOTIFY_2();
			break;
		case RAKLION_STATE_READY:
			this->SetState_READY();
			break;
		case RAKLION_STATE_START_BATTLE:
			this->SetState_START_BATTLE();
			break;
		case RAKLION_STATE_NOTIFY_3:
			this->SetState_NOTIFY_3();
			break;
		case RAKLION_STATE_CLOSE_DOOR:
			this->SetState_CLOSE_DOOR();
			break;
		case RAKLION_STATE_ALL_USER_DIE:
			this->SetState_ALL_USER_DIE();
			break;
		case RAKLION_STATE_NOTIFY_4:
			this->SetState_NOTIFY_4();
			break;
		case RAKLION_STATE_END:
			this->SetState_END();
			break;
	}
	RAKLION_UTIL.NotifyRaklionChangeState(this->m_iRaklionState, this->m_BattleOfSelupan.GetBattleOfSelupanState());
}

void CRaklion::SetState_IDLE()
{
	LogAddC(7, "[Raklion] State(%d) -> IDLE", this->m_iRaklionState);
	this->SetRaklionState(RAKLION_STATE_IDLE);
}

void CRaklion::SetState_NOTIFY_1()
{
	LogAddC(7, "[Raklion] State(%d) -> NOTIFY_1", this->m_iRaklionState);
	this->SetRaklionState(RAKLION_STATE_NOTIFY_1);
}

void CRaklion::SetState_STANDBY()
{
	LogAddC(7, "[Raklion] State(%d) -> STANDBY", this->m_iRaklionState);
	this->m_dwAppearanceTimeLeft = GetTickCount();
	this->SetRaklionState(RAKLION_STATE_STANDBY);
}

void CRaklion::SetState_NOTIFY_2()
{
	LogAddC(7, "[Raklion] State(%d) -> NOTIFY_2", this->m_iRaklionState);
	RAKLION_UTIL.SendMsgAllUser(lMsg.Get(MSGGET(13,52)), this->m_iBossZoneCloseTime / 60);
	this->SetRaklionState(RAKLION_STATE_NOTIFY_2);
}

void CRaklion::SetState_READY()
{
	LogAddC(7, "[Raklion] State(%d) -> READY", this->m_iRaklionState);
	this->m_BattleOfSelupan.SetState(RAKLION_SELUPAN_STANDBY);
	this->SetRaklionState(RAKLION_STATE_READY);
}

void CRaklion::SetState_START_BATTLE()
{
	LogAddC(7, "[Raklion] State(%d) -> START_BATTLE", this->m_iRaklionState);
	this->m_dwBossZoneCloseTimeLeft = GetTickCount();
	this->SetRaklionState(RAKLION_STATE_START_BATTLE);
}

void CRaklion::SetState_NOTIFY_3()
{
	LogAddC(7, "[Raklion] State(%d) -> NOTIFY_3", this->m_iRaklionState);
	RAKLION_UTIL.SendMsgAllUser(lMsg.Get(MSGGET(13,53)));
	this->SetRaklionState(RAKLION_STATE_NOTIFY_3);
}

void CRaklion::SetState_CLOSE_DOOR()
{
	LogAddC(7, "[Raklion] State(%d) -> CLOSE_DOOR", this->m_iRaklionState);
	this->SetRaklionState(RAKLION_STATE_CLOSE_DOOR);
}

void CRaklion::SetState_ALL_USER_DIE()
{
	LogAddC(7, "[Raklion] State(%d) -> ALL_USER_DIE", this->m_iRaklionState);
	this->m_BattleOfSelupan.DeleteSelupan();
	this->m_BattleOfSelupan.DeleteSummonMonster();
	this->SetRaklionState(RAKLION_STATE_ALL_USER_DIE);
}

void CRaklion::SetState_NOTIFY_4()
{
	LogAddC(7, "[Raklion] State(%d) -> NOTIFY_4", this->m_iRaklionState);
	this->m_dwEndTimeLeft = GetTickCount();
	BOOL bSuccess = this->m_BattleOfSelupan.GetSuccessValue();
	RAKLION_UTIL.SendMsgAllUser(lMsg.Get(MSGGET(13,55)), this->m_iEndTime / 60);
	RAKLION_UTIL.NotifyRaklionSuccessValue(bSuccess);
	this->SetRaklionState(RAKLION_STATE_NOTIFY_4);
}

void CRaklion::SetState_END()
{
	LogAddC(7, "[Raklion] State(%d) -> END", this->m_iRaklionState);
	this->m_BattleOfSelupan.DeleteSelupan();
	this->m_BattleOfSelupan.DeleteSummonMonster();
	this->m_BattleOfSelupan.SetSkillRule();
	this->ResetAllData();
	RAKLION_UTIL.SendMsgAllUser(lMsg.Get(MSGGET(13,56)));
	this->SetRaklionState(RAKLION_STATE_END);
	this->BossEggRegen();
}

void CRaklion::ProcState_IDLE()
{
	if(this->GetCurrentEggCount())
	{
		if(this->m_bNotify_1 == false)
		{
			if(this->GetCurrentEggCount() <= this->m_iEggHalf)
			{
				this->SetState(RAKLION_STATE_NOTIFY_1);
				this->m_bNotify_1 = true;
			}
		}
	}
	else
	{
		this->SetState(RAKLION_STATE_STANDBY);
	}
}

void CRaklion::ProcState_NOTIFY_1()
{
	this->SetState(RAKLION_STATE_IDLE);
}

void CRaklion::ProcState_STANDBY()
{
	DWORD iAppearanceTimeMSEC = 1000 * this->m_iAppearanceTime;

	if(iAppearanceTimeMSEC <= GetTickCount() - this->m_dwAppearanceTimeLeft)
	{
		this->SetState(RAKLION_STATE_NOTIFY_2);
	}
}

void CRaklion::ProcState_NOTIFY_2()
{
	this->SetState(RAKLION_STATE_READY);
}

void CRaklion::ProcState_READY()
{
	this->SetState(RAKLION_STATE_START_BATTLE);
}

void CRaklion::ProcState_START_BATTLE()
{
	if ( 1000 * this->m_iBossZoneCloseTime < GetTickCount() - this->m_dwBossZoneCloseTimeLeft )
	{
		this->SetState(RAKLION_STATE_NOTIFY_3);
	}
	this->m_BattleOfSelupan.ManageSelupanHP();
	this->m_BattleOfSelupan.Run();
}

void CRaklion::ProcState_NOTIFY_3()
{
	this->m_BattleOfSelupan.ManageSelupanHP();
	this->m_BattleOfSelupan.Run();
	this->SetState(RAKLION_STATE_CLOSE_DOOR);
}

void CRaklion::ProcState_CLOSE_DOOR()
{
	if ( g_RaklionBattleUserMng.IsEmpty() == TRUE )
	{
		this->m_BattleOfSelupan.SetSuccessValue(FALSE);
		this->SetState(RAKLION_STATE_ALL_USER_DIE);
	}
	else
	{
		if ( this->m_BattleOfSelupan.GetBattleOfSelupanState() == RAKLION_SELUPAN_DIE )
		{
			this->m_BattleOfSelupan.SetSuccessValue(TRUE);
			this->SetState(RAKLION_STATE_NOTIFY_4);
		}
		else
		{
			this->m_BattleOfSelupan.ManageSelupanHP();
			this->m_BattleOfSelupan.Run();
		}
	}
}

void CRaklion::ProcState_ALL_USER_DIE()
{
	this->SetState(RAKLION_STATE_NOTIFY_4);
}

void CRaklion::ProcState_NOTIFY_4()
{
	int iEndTimeMSEC = 1000 * this->m_iEndTime;

	if(iEndTimeMSEC <= GetTickCount() - this->m_dwEndTimeLeft)
	{
		this->SetState(RAKLION_STATE_END);
	}
}

void CRaklion::ProcState_END()
{
	this->SetState(RAKLION_STATE_IDLE);
}

void CRaklion::IncEggCount()
{
	if ( this->GetCurrentEggCount() < this->m_iEggCount )
	{
		++this->m_iCurrEggCount;
	}
	else
	{
		LogAddC(2, "[Raklion] BossEggDieCount Error : (%d)", this->m_iCurrEggCount);
	}
}

void CRaklion::DecEggCount()
{
	if ( this->GetCurrentEggCount() > 0 )
	{
		--this->m_iCurrEggCount;
	}
	else
	{
		return;
	}
}

void CRaklion::BossEggRegen()
{
	this->BossEggDelete();
	for ( int i=0 ; i<OBJ_MAXMONSTER ; ++i )
	{
		if ( RAKLION_EGG_CLASS_RANGE(gObj[i].Class) )
		{
			gObjSetMonster(i, gObj[i].Class);
			if ( gObjMonsterRegen(&gObj[i]) )
			{
				gObj[i].Live = TRUE;
				gObj[i].DieRegen = FALSE;
			}
			this->IncEggCount();
		}
	}
	LogAddC(5, "[Raklion][BossEggRegen] : BossEgg(%d eggs)", this->GetCurrentEggCount());
}

void CRaklion::BossEggDelete()
{
	for ( int i=0; i<OBJ_MAXMONSTER; ++i )
	{
		if ( RAKLION_EGG_CLASS_RANGE(gObj[i].Class) )
		{
			gObjDel(i);
			gObj[i].Live = FALSE;
			gObj[i].m_State = FALSE;
			gObjViewportListProtocolDestroy(&gObj[i]);
			gObjViewportClose(&gObj[i]);
			this->DecEggCount();
		}
	}
	LogAddC(5, "[Raklion][BossEggDelete] : BossEgg(%d eggs)", this->GetCurrentEggCount());
}




void CRaklion::CheckUserOnRaklionBossMap()
{
	for ( int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i )
	{
		if ( gObj[i].Connected == PLAYER_PLAYING )
		{
			if ( gObj[i].Type == OBJ_USER )
			{
				if ( gObj[i].MapNumber == MAP_INDEX_RAKLIONBOSS ) 
				{
					if ( (gObj[i].Authority & 2) != 2 )
					{
						if ( !g_RaklionBattleUserMng.CheckUserIsInEvent(i) )
						{
							if ( !gObj[i].RegenOk )
							{
								if ( gObj[i].m_State == 2 )
								{
									if ( gObj[i].Live == TRUE )
									{
										gObjMoveGate(i, 287);
										LogAddC(2, "[Raklion][Invalid User] Invalid Raklion Boss Map User[%s][%s]",
											gObj[i].AccountID, gObj[i].Name);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

