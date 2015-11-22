#include "stdafx.h"
#include "VipSys.h"
#include "user.h"
#include "protocol.h"

CVipSystem g_VipSystem;

int IsVipServer;
int BronzeVipExpDay;
int BronzeVipExpNight;
int SilverVipExpDay;
int SilverVipExpNight;
int GoldVipExpDay;
int GoldVipExpNight;
int PlatinumVipExpDay;
int PlatinumVipExpNight;
int BronzeVipDropDay;
int BronzeVipDropNight;
int SilverVipDropDay;
int SilverVipDropNight;
int GoldVipDropDay;
int GoldVipDropNight;
int PlatinumVipDropDay;
int PlatinumVipDropNight;

//modified by Dudi for wizzy's request

void CVipSystem::ReadFile(char *filename)
{
	IsVipServer = GetPrivateProfileIntA("main","IsServerVip",1,filename);
	BronzeVipExpDay = GetPrivateProfileIntA("main","BronzeVipExpRaiseDay",1,filename);
	BronzeVipExpNight= GetPrivateProfileIntA("main","BronzeVipExpRaiseNight",1,filename);
	SilverVipExpDay = GetPrivateProfileIntA("main","SilverVipExpRaiseDay",1,filename);
	SilverVipExpNight = GetPrivateProfileIntA("main","SilverVipExpRaiseNight",1,filename);
	GoldVipExpDay = GetPrivateProfileIntA("main","GoldVipExpRaiseDay",1,filename);
	GoldVipExpNight = GetPrivateProfileIntA("main","GoldVipExpRaiseNight",1,filename);
	PlatinumVipExpDay = GetPrivateProfileIntA("main","PlatinumVipExpRaiseDay",1,filename);
	PlatinumVipExpNight = GetPrivateProfileIntA("main","PlatinumVipExpRaiseNight",1,filename);
	BronzeVipDropDay = GetPrivateProfileIntA("main","BronzeVipDropRaiseDay",1,filename);
	BronzeVipDropNight = GetPrivateProfileIntA("main","BronzeVipDropRaiseNight",1,filename);
	SilverVipDropDay = GetPrivateProfileIntA("main","SilverVipDropRaiseDay",1,filename);
	SilverVipDropNight = GetPrivateProfileIntA("main","SilverVipDropRaiseNight",1,filename);
	GoldVipDropDay = GetPrivateProfileIntA("main","GoldVipDropRaiseDay",1,filename);
	GoldVipDropNight = GetPrivateProfileIntA("main","GoldVipDropRaiseNight",1,filename);
	PlatinumVipDropDay = GetPrivateProfileIntA("main","PlatinumVipDropRaiseDay",1,filename);
	PlatinumVipDropNight = GetPrivateProfileIntA("main","PlatinumVipDropRaiseNight",1,filename);
	
}

void CVipSystem::ApplyVip(int aIndex, BYTE Type)
{
	SYSTEMTIME strSystime;
	GetLocalTime(&strSystime);

	LPOBJ lpObj = &gObj[aIndex];
	
	if(Type == 1 )
	{
		if(strSystime.wHour < 7)
		{
			lpObj->m_iVipExpAdd = BronzeVipExpNight;
			lpObj->m_iVipDropAdd = BronzeVipDropNight;
		}	
		else
		{
			lpObj->m_iVipExpAdd = BronzeVipExpDay;
			lpObj->m_iVipDropAdd = BronzeVipDropDay;
		}
	}

	if(Type == 2 )
	{
		if(strSystime.wHour < 7)
		{
			lpObj->m_iVipExpAdd = SilverVipExpNight;
			lpObj->m_iVipDropAdd = SilverVipDropNight;
		}	
		else
		{
			lpObj->m_iVipExpAdd = SilverVipExpDay;
			lpObj->m_iVipDropAdd = SilverVipDropDay;
		}
	}

	if(Type == 3 )
	{
		if(strSystime.wHour < 7)
		{
			lpObj->m_iVipExpAdd = GoldVipExpNight;
			lpObj->m_iVipDropAdd = GoldVipDropNight;
		}	
		else
		{
			lpObj->m_iVipExpAdd = GoldVipExpDay;
			lpObj->m_iVipDropAdd = GoldVipDropDay;
		}
	}
	if(Type == 4 )
	{
		if(strSystime.wHour < 7)
		{
			lpObj->m_iVipExpAdd = PlatinumVipExpNight;
			lpObj->m_iVipDropAdd = PlatinumVipDropNight;
		}	
		else
		{
			lpObj->m_iVipExpAdd = PlatinumVipExpDay;
			lpObj->m_iVipDropAdd = PlatinumVipDropDay;
		}
	}
	else
	{
		lpObj->m_iVipExpAdd =0;
		lpObj->m_iVipDropAdd =0;
	}
}