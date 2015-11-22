/*
############################################################
---------------- Happy Hour Event -------------------------
############################################################
; Coded by drakelv
; for IGCNetwork
; Jan 11/2010
; Copyrights IGCNetwork (c) 2010
############################################################
*/
#include "stdafx.h"
#include "happyhour.h"
#include "GameMain.h"
#include "user.h"
#include "protocol.h"
#include "logproc.h"

CHappyHour g_HappyHour;

void CHappyHour::Run()
{
	SYSTEMTIME strSystime;
	GetLocalTime(&strSystime);

	if(this->STATE == 1)
	{
		if(strSystime.wHour == HappyHourHour+1)
		{
			gAddExperience -= HappyHourExpIncrease;
			gItemDropPer -= HappyHourDropIncrease;
			AllSendServerMsg("[HappyHour] Exp & drop has been set back to normal");
			LogAddTD("[HappyHour] Event has been ended");
			this->STATE = 0;
			return;
		}
		return;
	}

	if(strSystime.wHour == HappyHourHour)
	{
		this->STATE = 1;
		gAddExperience += HappyHourExpIncrease;
		gItemDropPer += HappyHourDropIncrease;
		AllSendServerMsg("[HappyHour] Exp & drop has been increased for 60 minutes");
		LogAddTD("[HappyHour] Event has been started");
		return;
	}


}