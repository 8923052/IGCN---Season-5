#include "stdafx.h"
#include "RaklionUtil.h"
#include "user.h"
#include "protocol.h"
#include "Raklion.h"
#include "giocp.h"
#include "TNotice.h"
#include "..\common\winutil.h"
CRaklionUtil::CRaklionUtil()
{
}

CRaklionUtil::~CRaklionUtil()
{
}
struct PMSG_NOTIFY_RAKLION_CHANGE_STATE
{
	PBMSG_HEAD2 h;
	BYTE btState;
	BYTE btDetailState;
};
void CRaklionUtil::NotifyRaklionChangeState(int iState, int iDetailState)
{
	PMSG_NOTIFY_RAKLION_CHANGE_STATE pMsg = {0};

	PHeadSubSetB((LPBYTE)&pMsg, 0xD1, 0x12, sizeof(pMsg));
	pMsg.btState = iState;
	pMsg.btDetailState = iDetailState;

	if(iState == 1)
	{
		this->SendDataRaklionMapUser((LPBYTE)&pMsg, pMsg.h.size);
	}
	else
	{
		this->SendDataRaklionBossMapUser((LPBYTE)&pMsg, pMsg.h.size);
	}
}
struct PMSG_NOTIFY_RAKLION_BATTLE_RESULT
{
	PBMSG_HEAD2 h;
	BYTE btResult;
};
void CRaklionUtil::NotifyRaklionSuccessValue(int iSuccessValue)
{
	PMSG_NOTIFY_RAKLION_BATTLE_RESULT pMsg = {0};

	pMsg.btResult = iSuccessValue;
	
	this->SendDataRaklionBossMapUser((LPBYTE)&pMsg, pMsg.h.size);
}
struct PMSG_NOTIFY_RAKLION_USER_EGG_COUNT
{
	PBMSG_HEAD2 h;
	BYTE btEggCount;
	BYTE btUserCount;
};
void CRaklionUtil::NotifyRaklionUserEggCount(int iEggCount)
{
	PMSG_NOTIFY_RAKLION_USER_EGG_COUNT pMsg = {0};

	PHeadSubSetB((LPBYTE)&pMsg, 0xD1, 0x15, sizeof(pMsg));
	pMsg.btEggCount = iEggCount;
	pMsg.btUserCount = 0;
	PMSG_NOTICE pNotice;
	TNotice::MakeNoticeMsgEx(&pNotice, 1, "Current egg count: %d", iEggCount);
	TNotice::SendNoticeToAllUser(&pNotice);
	this->SendDataRaklionBossMapUser((LPBYTE)&pMsg, sizeof(pMsg));
}
struct PMSG_NOTIFY_RAKLION_CURRENT_STATE
{
	PBMSG_HEAD2 h;
	BYTE btState;
	BYTE btDetailState;
};
void CRaklionUtil::NotifyRaklionCurrentState(int iIndex, int iState, int iDetailState)
{
	PMSG_NOTIFY_RAKLION_CURRENT_STATE pMsg = {0};

	PHeadSubSetB((LPBYTE)&pMsg, 0xD1, 0x11, sizeof(pMsg));
	pMsg.btState = iState;
	pMsg.btDetailState = iDetailState;

	DataSend(iIndex, (LPBYTE)&pMsg, pMsg.h.size);
}
void CRaklionUtil::SendMsgRaklionMapUser(LPSTR lpMsg, ...)
{
	if( !lpMsg )
		return;

	char szBuffer[512] = "";
	va_list pArguments;

	va_start(pArguments, lpMsg);
	vsprintf(szBuffer, lpMsg, pArguments);
	va_end(pArguments);

	PMSG_NOTICE pNotice;
	TNotice::MakeNoticeMsg(&pNotice, 0, szBuffer);

	for( int iCount=OBJ_STARTUSERINDEX;iCount<OBJMAX;++iCount )
	{
		if(gObj[iCount].Connected == PLAYER_PLAYING &&
			gObj[iCount].Type == OBJ_USER && (gObj[iCount].MapNumber
			== MAP_INDEX_RAKLION || gObj[iCount].MapNumber == MAP_INDEX_RAKLIONBOSS))
		{
			TNotice::SendNoticeToUser(iCount, &pNotice);
		}
	}
}
void CRaklionUtil::SendDataRaklionMapUser(LPBYTE lpMsg, int iSize)
{
	for( int iCount=OBJ_STARTUSERINDEX;iCount<OBJMAX;++iCount )
	{
		if(gObj[iCount].Connected == PLAYER_PLAYING &&
			gObj[iCount].Type == OBJ_USER && (gObj[iCount].MapNumber
			== MAP_INDEX_RAKLION || gObj[iCount].MapNumber == MAP_INDEX_RAKLIONBOSS))
		{
			DataSend(iCount, lpMsg, iSize);
		}
	}
}

void CRaklionUtil::SendMsgRaklionBossMapUser(LPSTR lpMsg, ...)
{
	if( !lpMsg )
		return;

	char szBuffer[512] = "";
	va_list pArguments;

	va_start(pArguments, lpMsg);
	vsprintf(szBuffer, lpMsg, pArguments);
	va_end(pArguments);

	PMSG_NOTICE pNotice;
	TNotice::MakeNoticeMsg(&pNotice, 0, szBuffer);

	for( int iCount=OBJ_STARTUSERINDEX;iCount<OBJMAX;++iCount )
	{
		if(gObj[iCount].Connected == PLAYER_PLAYING &&
			gObj[iCount].Type == OBJ_USER && gObj[iCount].MapNumber
			== MAP_INDEX_RAKLIONBOSS)
		{
			TNotice::SendNoticeToUser(iCount, &pNotice);
		}
	}
}

void CRaklionUtil::SendDataRaklionBossMapUser(LPBYTE lpMsg, int iSize)
{
	for( int iCount=OBJ_STARTUSERINDEX;iCount<OBJMAX;++iCount )
	{
		if(gObj[iCount].Connected == PLAYER_PLAYING &&
			gObj[iCount].Type == OBJ_USER && gObj[iCount].MapNumber == 
			MAP_INDEX_RAKLIONBOSS)
		{
			DataSend(iCount, lpMsg, iSize);
		}
	}
}

void CRaklionUtil::SendMsgAllUser(LPSTR lpMsg, ...)
{
	if( !lpMsg )
		return;

	char szBuffer[512] = "";
	va_list pArguments;

	va_start(pArguments, lpMsg);
	vsprintf(szBuffer, lpMsg, pArguments);
	va_end(pArguments);

	PMSG_NOTICE pNotice;
	TNotice::MakeNoticeMsg(&pNotice, 0, szBuffer);

	for( int iCount=OBJ_STARTUSERINDEX;iCount<OBJMAX;++iCount )
	{
		if(gObj[iCount].Connected == PLAYER_PLAYING &&
			gObj[iCount].Type == OBJ_USER)
		{
			TNotice::SendNoticeToUser(iCount, &pNotice);
		}
	}
}
