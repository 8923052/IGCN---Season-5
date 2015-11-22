#include "StdAfx.h"
#include "protection.h"
#pragma comment(lib, "rpcrt4.lib")


BOOL Check()
{
	unsigned char MACData[6];

	UUID uuid;
    UuidCreateSequential( &uuid );			

    for (int i=2; i<8; i++)					
		MACData[i - 2] = uuid.Data4[i];

	char sBuf[18];
	sprintf_s(sBuf, "%02X-%02X-%02X-%02X-%02X-%02X", MACData[1], MACData[0], MACData[3], MACData[5], MACData[4], MACData[2]);
	//cLog.ConsoleOutput(sBuf);
	if(!Checking(sBuf))
	{

		return false;
	}
	else
	{
		return true;
	}
	//return true;
}

char* GetByName(int i)
{
	if(i == 0)
		return "Wizzy";
	if (i == 1)
		return "Colins";
	if(i == 2 || i == 3)
		return "Supron";
	if(i == 4 || i == 5)
		return "P.Zilelidis";
	if(i == 6)
		return "MMONATIONS";
	return "unknow";
}
BOOL Checking(LPCSTR MacID)
{
#define clientcount 3
	//MAC Protection
	char ClientMacs[clientcount][18] = 
	{
		//
		"25-00-30-1C-20-90", // IGCN
		"0C-00-0F-91-68-29", // EtniesMU
		"1A-00-49-85-1A-4D", // Unreal MU
	};
	for(int x=0;x<clientcount;x++)
	{
		if(!strcmp(MacID,ClientMacs[x]))
		{
		//	cLog.ConsoleOutput("Files licensed to : %s",GetByName(x));
			return true;
		}
	}
	return false;
}
