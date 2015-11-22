/*
-- XMAS Event WEBZEN Season 4 (JPN)
-- Coded by drakelv (c) 2009
*/
#ifndef XMASEVENT_H
#define XMASEVENT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "user.h"

struct XMAS_MONSTER_SETBASE_INFO
{
	WORD wType;	// 2
	BYTE btMapNumber;	// 4
	BYTE btDistance;	// 5
	BYTE btX;	// 6
	BYTE btY;	// 7
	BYTE btDir;	// 8
};

#define MAX_XMAS_OBJ_INDEX	800

class CXMasObjInfo
{

public:

	CXMasObjInfo()
	{
		this->Reset();
	}

	virtual ~CXMasObjInfo(){return;}

	void Reset()
	{
		for ( int iCount=0;iCount<MAX_XMAS_OBJ_INDEX;iCount++)
		{
			this->m_iObjIndex[iCount]=-1;
		}

		this->m_iObjCount=0;
	}

	BOOL AddObj(int iIndex)
	{
		if ( this->m_iObjCount >= MAX_XMAS_OBJ_INDEX )
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
	int m_iObjIndex[MAX_XMAS_OBJ_INDEX];	// 8
};

class XMasEvent
{
public:
	XMasEvent();
	virtual ~XMasEvent();
	void XMasEventRun();
	void XMasEventInvade();
	void XMasEventSantaBagLoad(unsigned char * filename);
	void XMasEventSantaRewardDrop(LPOBJ lpObj);
	void LoadData(LPSTR filename);
	void SetMonsterSetBaseInfo(int iIndex, WORD wType, BYTE btMapNumber, BYTE btDistance, BYTE btX, BYTE btY, BYTE btDir);
	void XMasEventEnd();
	void MonsterDie(int iIndex);
private:
	DWORD EventStartTime;
	int m_iMaxMonsterCount;	// 4
	int m_iAliveMonsterCount;
	XMAS_MONSTER_SETBASE_INFO m_SetBaseInfo[50];	// 8
	BYTE STATE;
	CXMasObjInfo m_XMasMonster;	// 7E0


}; extern XMasEvent gCXMasEvent;

#endif