#pragma once

class CRaklionUtil
{
public:
	CRaklionUtil();
	virtual ~CRaklionUtil();

	void NotifyRaklionUserEggCount(int iEggCount);
	void NotifyRaklionCurrentState(int iIndex, int iState, int iDetailState);
	void NotifyRaklionChangeState(int iState, int iDetailState);
	void NotifyRaklionSuccessValue(int iSuccessValue);
	void __cdecl SendMsgRaklionMapUser(LPSTR lpMsg, ...);
	void SendDataRaklionMapUser(LPBYTE lpMsg, int iSize);
	void __cdecl SendMsgRaklionBossMapUser(LPSTR lpMsg, ...);
	void SendDataRaklionBossMapUser(LPBYTE lpMsg, int iSize);
	void __cdecl SendMsgAllUser(LPSTR lpMsg, ...);
};
