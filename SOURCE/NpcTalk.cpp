#include "stdafx.h"
#include "user.h"
#include "NpcTalk.h"
#include "gObjMonster.h"
#include "..\common\winutil.h"
#include "protocol.h"
#include "GameMain.h"
#include "BloodCastle.h"
#include "gObjMonster.h"
#include "DevilSquare.h"
#include "QuestInfo.h"
#include "CastleSiegeSync.h"
#include "KanturuEntranceNPC.h"
#include "JewelOfHarmonySystem.h"
#include "Gamemain.h"
#include "Event.h"
#include "ObjCalCharacter.h"
#include "QuestSystem.h"
#include "IllusionTemple.h"
#include "GensSystem.h"
#include "DoubleGoer.h"
#include "DSProtocol.h"
#include "CastleSiege.h"
#include "BuffEffect.h"
// GS-N 0.99.60T 0x005211D0
//	GS-N	1.00.18	JPN	0x005527F0	-	Completed





BOOL NpcTalk(LPOBJ lpNpc, LPOBJ lpObj)
{
	int npcnum = lpNpc->Class;

	if ( npcnum < 0 )
	{
		return FALSE;
	}

/*	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}*/

	if ( npcnum == 229 ) // Marlon
	{
		gQeustNpcTeleport.TalkRefAdd();
		lpObj->TargetShopNumber = npcnum;
	}

	if ( NpcQuestCheck(lpNpc, lpObj) != FALSE )
	{
		return TRUE;
	}

	switch ( npcnum )
	{
		case 367:
			if ( NpcMainatenceMachine ( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 259:
			if ( NpcReira ( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 254:
			if ( NpcFasi ( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 241:
			if ( NpcGuildMasterTalk( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		
		case 239:
			if ( NpcBattleAnnouncer( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 249:
			if ( NpcRolensiaGuard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 238:
			if ( NpcChaosGoblelin( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 237:
			if ( NpcRusipher( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 253:
			if ( NpcPosionGirl( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 245:
			if ( NpcDeviasWizard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 247:
			if ( NpcDeviasGuard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 240:
			if ( NpcWarehouse( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 226:
			if ( NpcDarkSpiritTrainer( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 242:
			if ( NpcNoriaRara( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 244:
			if ( NpcDeviasMadam( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 236:
			if ( NpcEventChipNPC( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 234:
			if ( NpcServerDivision( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 232:
			if ( NpcAngelKing( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 233:
			if ( NpcAngelMessanger( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 255:
			if ( NpcRolensiaMadam( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 250:
			if ( NpcRoadMerchant( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 246:
			if ( NpcDeviasWeapon( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 251:
			if ( NpcRorensiaSmith( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 243:
			if ( NpcNoriJangIn( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 256:
			if ( NpcJewelMixDealer( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 221:
			if ( NpcSiegeMachine_Attack( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 222:
			if ( NpcSiegeMachine_Defense( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 223:
			if ( NpcElderCircle( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 224:
			if ( NpcCastleGuard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 219:
			if ( NpcCastleGateLever( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 216:
			if ( NpcCastleCrown( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 217:
		case 218:
			if ( NpcCastleSwitch( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 220:
			if( ::NpcCastleHuntZoneGuard(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}
		case 257:
			if ( NpcShadowPhantom( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 371:
			{
				if ( NpcLeoHelper( lpNpc, lpObj) == TRUE)
				{
					return TRUE;
				}
			} 
			break;

		case 368:
		case 369:
		case 370:
			if ( g_kJewelOfHarmonySystem.NpcJewelOfHarmony( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 375:
			if ( NpcChaosCardMaster( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 406:
			if ( NpcPriestDevin(lpNpc, lpObj ) == TRUE)
			{
				return TRUE;
			}
			break;

		case 374:
			if ( ShopKepper13(lpNpc, lpObj ) == TRUE)
			{
				return TRUE;
			}
			break;
	
		case 376:
			if ( ShopKepper14(lpNpc, lpObj ) == TRUE)
			{
				return TRUE;
			}
			break;

		case 377:
			if ( ShopKepper15(lpNpc, lpObj ) == TRUE)
			{
				return TRUE;
			}
			break;

		case 379:
			if ( ShopKepper16(lpNpc, lpObj ) == TRUE)
			{
				return TRUE;
			}
			break;

		case 415:
			if ( ShopKepper17(lpNpc, lpObj ) == TRUE)
			{
				return TRUE;
			}
			break;

		case 416:
			if ( ShopKepper18(lpNpc, lpObj ) == TRUE)
			{
				return TRUE;
			}
			break;

		case 417:
			if ( ShopKepper19(lpNpc, lpObj ) == TRUE)
			{
				return TRUE;
			}
			break;
	
		case 407:
			if ( NpcWareWolfQwarell(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}
			break;	
			
		case 408:	
			if ( NpcGateKeeper(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}
			break;

		case 469:
			if ( NpcGreenSnowMan( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case  472:
			if ( NpcWhiteSnowMan( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case  473:
			if ( NpcBlackSnowMan( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 468:
			if ( NpcYellowSnowMan( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 474:
			if ( NpcOrangeSnowMan( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 475:
			if ( NpcPurpleSnowMan( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 470:
			if ( NpcRedSnowMan( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 471:
			if ( NpcBlueSnowMan( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 467:
			if ( NpcSnowMan( lpNpc, lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
		case 465:
			if ( NpcSantaClaus(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
		case 479:
			if ( NpcGateKeeperTitus( lpNpc, lpObj) == TRUE)
			{
				return TRUE;
			}
			break;

		case 522: // jerint imperial font
			if(NpcJerint(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}
			break;

		case 540: //double goer angel
			if(SartigantheAngel(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}
			break;

		case 492: //moss
			if(MossMerchant(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}
			break;

		case 450:
			if(BlossomGovernor(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}	
			break;
		case 452:
			if(SokcetMaster(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}	
			break;

		case 453:
			if(SokcetResearcher(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}	
			break;

		case 385:
			if ( NpcAlchemistMenssager(lpObj) == TRUE )
			{
				return TRUE;
			}
			break;

		case 380:
			if(NpcStatue(lpNpc, lpObj) == TRUE )
			{
				return TRUE;
			}
			break;
		case 383:
		case 384:
			if(NpcBox(lpNpc, lpObj) == TRUE )
			{
				return TRUE;
			}
			break;
		case 541:
			NpcSilverBox(lpNpc,lpObj);
			break;
		case 543:
		case 544:
			{
				NpcGens(lpNpc, lpObj);
				return true;
			}
			break;
		case 542:
			NpcGoldBox(lpNpc,lpObj);
			break;
		case 545:
			NpcChristina(lpNpc,lpObj);
			break;
		case 546:
			NpcRaul(lpNpc,lpObj);
			break;
		case 547:
			if(NpcJulia(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
	}

	return FALSE;
}
//	pMsg.result = 0x18; = Socket Researcher
//	pMsg.result = 0x17; = Socket Master
BOOL NpcAlchemistMenssager(LPOBJ lpObj)
{
	int ITLevel = g_IllusionTemple.GetUserLevelRoom(lpObj->m_Index);
	if(ITLevel == -1)
	{
		GCServerMsgStringSend("Error", lpObj->m_Index, 1);
		return false;
	}
	GC_ANS_NPC_TALK_V1 pTalk;
	pTalk.PHeader.uHead = 0x30;
	pTalk.PHeader.uPacketType = 0xC3;
	pTalk.PHeader.uSize = 0x06;
	pTalk.NpcNumber = 20;
	pTalk.Param1 = 0;
	pTalk.Param2 = g_IllusionTemple.GetWaitingUserCount(ITLevel);
	DataSend(lpObj->m_Index, (LPBYTE)&pTalk, pTalk.PHeader.uSize);
	lpObj->TargetShopNumber = 385;
	return true;
}

BOOL NpcStatue(LPOBJ lpNpc, LPOBJ lpObj)
{
	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;
	lpNpc->Life = 0.0f;
	gObjLifeCheck(lpNpc, lpNpc, 1, 0, 0, 0, 0, 0);
	g_IllusionTemple.DropSacredItem(lpObj->m_cIllusionTempleIndex, lpNpc, lpObj);
	return true;
}

BOOL NpcBox(LPOBJ lpNpc, LPOBJ lpObj)
{
	if(lpNpc->Class == 383 && lpObj->m_cIllusionTempleTeam != 0)
	{
		return true;
	}
	if(lpNpc->Class == 384 && lpObj->m_cIllusionTempleTeam != 1)
	{
		return true;
	}
	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;
	g_IllusionTemple.GiveSacredItem(lpObj->m_cIllusionTempleIndex, lpNpc, lpObj);
}
BOOL SokcetResearcher(OBJECTSTRUCT *lpNpc,OBJECTSTRUCT *lpObj)
{
	if ( lpObj->m_bPShopOpen == true )
	{
		LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed",
			lpObj->AccountID, lpObj->Name);
		ChatTargetSend(lpNpc,"Please close personal store",lpObj->m_Index);
		return TRUE;
	}
	PMSG_TALKRESULT pMsg;
	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x18;
	DataSend(lpObj->m_Index,(LPBYTE)&pMsg,pMsg.h.size);
	lpObj->m_IfState.type = 45;
	//(2,"[Gatekeeper Titus] [%s][%s] Talk's to Duel Manager Titus",lpObj->AccountID,lpObj->Name);
	return TRUE;
}

BOOL SokcetMaster(OBJECTSTRUCT *lpNpc,OBJECTSTRUCT *lpObj)
{
	if ( lpObj->m_bPShopOpen == true )
	{
		LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed",
			lpObj->AccountID, lpObj->Name);
		ChatTargetSend(lpNpc,"Please close personal store",lpObj->m_Index);
		return TRUE;
	}
	PMSG_TALKRESULT pMsg;
	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x17;
	DataSend(lpObj->m_Index,(LPBYTE)&pMsg,pMsg.h.size);
	lpObj->m_IfState.type = 45;
	//(2,"[Gatekeeper Titus] [%s][%s] Talk's to Duel Manager Titus",lpObj->AccountID,lpObj->Name);
	return TRUE;
}
BOOL BlossomGovernor(OBJECTSTRUCT *lpNpc,OBJECTSTRUCT *lpObj)
{
	PMSG_TALKRESULT pMsg;
	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x16;
	DataSend(lpObj->m_Index,(LPBYTE)&pMsg,pMsg.h.size);
	lpObj->m_IfState.type = 50;
	//(2,"[Gatekeeper Titus] [%s][%s] Talk's to Duel Manager Titus",lpObj->AccountID,lpObj->Name);
	return TRUE;
}

BOOL NpcGateKeeperTitus(OBJECTSTRUCT *lpNpc, OBJECTSTRUCT *lpObj)
{
	PMSG_TALKRESULT pMsg;
	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x21;//21
	DataSend(lpObj->m_Index,(LPBYTE)&pMsg,pMsg.h.size);
	lpObj->m_IfState.type = 20;
	lpObj->m_IfState.use =1;
	//(2,"[Gatekeeper Titus] [%s][%s] Talk's to Duel Manager Titus",lpObj->AccountID,lpObj->Name);
	return TRUE;
}

BOOL SartigantheAngel(OBJECTSTRUCT *lpNpc, OBJECTSTRUCT *lpObj)
{

	 PMSG_TALKRESULT pMsg;
	 PHeadSetBE((LPBYTE)&pMsg, 0x30, 5);
	 pMsg.result = 0x23;
	 pMsg.level1 = ((g_DoppelGanger.GetEventTime(lpObj)/1000)/10/60);
	 lpObj->TargetShopNumber = 540;
	 DataSend(lpObj->m_Index, (LPBYTE)&pMsg, 5);
	return true;

}

BOOL MossMerchant(OBJECTSTRUCT *lpNpc, OBJECTSTRUCT *lpObj)
{
	//lpObj->m_IfState.use = 492;
	return FALSE;

}
BOOL NpcPriestDevin(LPOBJ lpNpc, LPOBJ lpObj)
{

	PMSG_QUEST_KILLEDCOUNT msgKilled = {0xc1, 0x31, 0xa4};

	msgKilled.killed[0].killed_id = 0x99;
	msgKilled.killed[0].display = 0x01;
	msgKilled.killed[0].killed_count = gObj->m_Quest[30];

	msgKilled.killed[1].killed_id = 0x9a;
	msgKilled.killed[1].display = 0x01;
	msgKilled.killed[1].killed_count = gObj->m_Quest[31];

	msgKilled.killed[2].killed_id = 0x9b;
	msgKilled.killed[2].display = 0x01;
	msgKilled.killed[2].killed_count = 5; //gObj->m_Quest[32];

	msgKilled.killed[3].killed_id = 0x9c;
	msgKilled.killed[3].display = 0x01;
	msgKilled.killed[3].killed_count = gObj->m_Quest[34];

	if(gObj[lpObj->m_Index].m_Quest[1] == 0xf6)
	{
	DataSend(lpObj->m_Index, (LPBYTE)&msgKilled, sizeof(msgKilled));
	}
	return false;

}

BOOL NpcWareWolfQwarell(LPOBJ lpNpc, LPOBJ lpObj)
{
	
	/*if (lpObj->m_Quest[1] == 0xF6 || lpObj->m_Quest[1] == 0xDA || lpObj->m_Quest[1] == 0xEA) //Anti-Hack
	{
		gObjTeleport(lpObj->m_Index,41,59,128);
	}*/
	return true;
}

BOOL NpcGateKeeper(LPOBJ lpNpc, LPOBJ lpObj)
{
	return true;
}

BOOL NpcMainatenceMachine(LPOBJ lpNpc, LPOBJ lpObj)
{
	g_KanturuEntranceNPC.NotifyEntranceInfo(lpObj->m_Index);
	return TRUE;
}


BOOL NpcReira(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcBattleAnnouncer(LPOBJ lpNpc, LPOBJ lpObj)
{
#if (GS_CASTLE==1)

#endif

	return 0;
}


BOOL NpcFasi(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gLanguage != 0 )
	{
		if ( gDevilSquareEvent != FALSE )
		{
			GCServerCmd(lpObj->m_Index, 1, 6, 0);
		}
	}

	if ( lpObj->m_PK_Level > 4 )
	{
		int hour = 0;
		int min = 0;

		if ( lpNpc->TargetNumber != lpObj->m_Index )
		{
			if ( gObjGetPkTime(lpObj, hour, min) == TRUE )
			{
				char szTemp[100];

				wsprintf(szTemp, lMsg.Get(MSGGET(4, 79)), hour, min);

				ChatTargetSend(lpNpc, szTemp, lpObj->m_Index);

				lpNpc->TargetNumber = lpObj->m_Index;

				/*if ( gPkLimitFree == FALSE )
				{
					return TRUE;
				}*/
			}
		}
		else if ( gPkLimitFree == FALSE )
		{
			int numbertext = rand() % 3;

			switch ( numbertext )
			{
				case 0:
					ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 98)), lpObj->m_Index);
					break;

				case 1:
					ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 99)), lpObj->m_Index);
					break;

				case 2:
					ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 100)), lpObj->m_Index);
					break;
			}

			lpNpc->TargetNumber = -1;	// Apply Deathway Fix, change 0 to -1;
			return TRUE;
		}
	}

	return FALSE;
}




BOOL NpcGuildMasterTalk(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gGuildCreate == FALSE )
	{
		ChatTargetSend(lpNpc, "¼­¹öºÐÇÒ ±â°£¿¡´Â ±æµå¸¦ »ý¼ºÇÒ¼ö°¡ ¾ø½À´Ï´Ù", lpObj->m_Index);
		return TRUE;
	}

	if ( lpObj->GuildNumber > 0 )
	{
		ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 116)), lpObj->m_Index);
		return TRUE;
	}

	int capacity = gObjGuildMasterCapacityTest(lpObj);

	if ( capacity == 0 )
	{
		ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 117)), lpObj->m_Index);
	}
	else if ( capacity == 2 )
	{
		ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 118)), lpObj->m_Index);
	}
	else
	{
		GCGuildMasterQuestionSend(lpObj->m_Index);
	}

	return TRUE;
}




BOOL NpcRolensiaGuard(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gLanguage != 0 )
	{
	
	}
	else if ( gEnableEventNPCTalk != FALSE )
	{
		GCServerCmd(lpObj->m_Index, 4, 0, 0);
	}

	return TRUE;
}





BOOL NpcChaosGoblelin(LPOBJ lpNpc, LPOBJ lpObj)
{
		if ( lpObj->m_bPShopOpen == true )
		{
			LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed",
				lpObj->AccountID, lpObj->Name);
			ChatTargetSend(lpNpc,"Please close personal store",lpObj->m_Index);
			return TRUE;
		}
	gUserFindDevilSquareKeyEyes(lpObj->m_Index);

	return FALSE;
}



BOOL g_bUseLotterySystem = TRUE;


BOOL NpcChaosCardMaster(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( g_bUseLotterySystem == FALSE )
		return FALSE;

	if ( bCanChaosBox == TRUE )
	{
		if ( lpObj->m_IfState.use > 0 )
			return FALSE;

		if ( lpObj->m_bPShopOpen == true )
		{
			LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed",
				lpObj->AccountID, lpObj->Name);

			GCServerMsgStringSend(lMsg.Get(MSGGET(4,194)), lpObj->m_Index, 1);
			return TRUE;
		}

		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x15;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 7;

		LogAddTD("[JewelMix] [%s][%s] Jewel Mix Dealer Start",
			lpObj->AccountID, lpObj->Name);

		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	}

	return TRUE;
}




BOOL NpcRusipher(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gDevilSquareEvent == FALSE )
	{
		return TRUE;
	}


	int aIndex = lpObj->m_Index;

	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	if ( gUserFindDevilSquareInvitation(aIndex) == FALSE )
	{
		GCServerCmd(lpObj->m_Index, 1, 2 ,0);
	}
	else if ( g_DevilSquare.GetState() == 1 )
	{
		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x04;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 12;
	}
	else
	{
		GCServerCmd(lpObj->m_Index, 1, 3, 0);
	}

	return TRUE;
}
BOOL NpcPosionGirl(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}
BOOL NpcRaul(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}
BOOL NpcChristina(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}
BOOL NpcDeviasWizard(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}
BOOL NpcDeviasGuard(LPOBJ lpNpc, LPOBJ lpObj)
{
	return TRUE;
}

BOOL NpcDeviasWareHousemen(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}


BOOL NpcWarehouse(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}



BOOL NpcNoriaRara(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gLanguage != 0 )
	{
	
	}
	else if ( gEnableEventNPCTalk != FALSE )
	{
		GCServerCmd(lpObj->m_Index, 4, 2, 0);
	}

	return FALSE;
}


BOOL NpcDeviasMadam(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gLanguage != 0 )
	{
	
	}
	else if ( gEnableEventNPCTalk != FALSE )
	{
		GCServerCmd(lpObj->m_Index, 4, 1, 0);
	}

	return FALSE;
}


struct PMSG_REQ_VIEW_EC_MN
{
	PBMSG_HEAD h;	// C1:01
	int iINDEX;	// 4
	char szUID[11];	// 8
};


BOOL NpcEventChipNPC(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}
	
	if ( lpNpc->MapNumber == 0 )
	{
		PMSG_REQ_VIEW_EC_MN pMsgTha;

		PHeadSetB((LPBYTE)&pMsgTha, 0x01, sizeof(pMsgTha));
		pMsgTha.iINDEX = lpObj->m_Index;
		strcpy(pMsgTha.szUID, lpObj->AccountID);
		pEventObj = lpNpc;

		DataSendEventChip((char*)&pMsgTha, sizeof(pMsgTha));
		
		lpObj->m_IfState.type = 9;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;

		return TRUE;
	}

	if ( lpNpc->MapNumber == 2 )
	{
		PMSG_EVENTCHIPINFO Result;

		PHeadSetB((LPBYTE)&Result, 0x94, sizeof(Result));
		Result.Type = 2;
		
		DataSend(lpObj->m_Index, (LPBYTE)&Result, Result.h.size);

		lpObj->m_IfState.type = 9;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;

		return TRUE;
	}

	return FALSE;
}



BOOL NpcRorensiaSmith(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL ShopKepper13(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL ShopKepper14(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL ShopKepper15(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL ShopKepper16(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL ShopKepper17(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL ShopKepper18(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL ShopKepper19(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}




BOOL NpcNoriJangIn(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}





BOOL NpcQuestCheck(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( g_QuestInfo.NpcTalk(lpNpc, lpObj) != FALSE )
	{
		return TRUE;
	}

	return FALSE;
}




BOOL NpcServerDivision(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gEnableServerDivision == FALSE )
	{
		return TRUE;
	}

	if ( lpObj->lpGuild != NULL )
	{
		GCServerCmd(lpObj->m_Index, 6, 0, 0);
		return TRUE;
	}

	lpObj->m_IfState.type = 11;
	lpObj->m_IfState.state = 0;
	lpObj->m_IfState.use = 1;

	return FALSE;
}



BOOL NpcRoadMerchant(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}





BOOL NpcAngelKing(LPOBJ lpNpc, LPOBJ lpObj)
{
	int iITEM_LEVEL = 0;

	if ( (  (lpObj->m_cBloodCastleIndex < 0)?FALSE:(lpObj->m_cBloodCastleIndex > MAX_BLOOD_CASTLE_LEVEL-1)?FALSE:TRUE ) == FALSE )
	{
		GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
		return FALSE;
	}

	LogAddTD("[Blood Castle] (%d) [%s][%s] Talk to Angel King",
		lpObj->m_cBloodCastleIndex+1, lpObj->AccountID, lpObj->Name);

	if ( g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_bBC_REWARDED != false )
	{
		GCServerCmd(lpObj->m_Index, 1, 0x2E, 0);
		return FALSE;
	}

	if ( g_BloodCastle.GetCurrentState(lpObj->m_cBloodCastleIndex) != 2 || g_BloodCastle.CheckPlayStart(lpObj->m_cBloodCastleIndex) == false)
	{
		GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
		return FALSE;
	}

	if ( lpObj->m_bBloodCastleComplete == true)
	{
		GCServerCmd(lpObj->m_Index, 1, 0x2E, 0);
		return FALSE;
	}

	if ( iITEM_LEVEL = iITEM_LEVEL = CHECK_LIMIT( g_BloodCastle.CheckQuestItem(lpObj->m_Index), 3)  )
	{
		if ( lpNpc->m_cBloodCastleIndex != lpObj->m_cBloodCastleIndex )
		{
			GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
			return FALSE;
		}

		if ( g_BloodCastle.CheckUserBridgeMember(lpObj->m_cBloodCastleIndex, lpObj->m_Index) == false )
		{
			GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
			return FALSE;
		}

		g_BloodCastle.SetUserState(lpObj->m_Index, 2);
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_iExtraEXP_Win_Quest_Party = lpObj->PartyNumber;
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_iExtraEXP_Win_Quest_Index = lpObj->m_Index;
		memcpy(g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_CharName, lpObj->Name, 10);
		memcpy(g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_AccountID, lpObj->AccountID, 10);
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_CharName[10] = 0;	// Zero String terminated
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_AccountID[10] = 0;	// Zero String Terminated
		
		LogAddTD("[Blood Castle] (%d) Blood Castle Quest Succeed Result -> Destroy Castle Door [%s][%s]",
			lpObj->m_cBloodCastleIndex+1, g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Door_AccountID,
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Door_CharName);
		LogAddTD("[Blood Castle] (%d) Blood Castle Quest Succeed Result -> Destroy Saint Status [%s][%s]",
			lpObj->m_cBloodCastleIndex+1, g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Door_AccountID,	// #error Correct this
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Status_CharName);
		LogAddTD("[Blood Castle] (%d) Blood Castle Quest Succeed Result -> Win Quest [%s][%s]",
			lpObj->m_cBloodCastleIndex+1, g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_AccountID,
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_CharName);

		if ( g_BloodCastle.SetBridgeWinner(lpObj->m_cBloodCastleIndex, lpObj->m_Index) == TRUE )
		{
			lpObj->m_bBloodCastleComplete = true;

			if ( g_BloodCastle.CheckPartyExist(lpObj->m_Index) == FALSE )
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);

				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest",
					lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);
			}
			else
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);
				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest - More Party to register",
					lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);
			}
		}
		else
		{
			LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Winner Already Exist !!",
				lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);

			return FALSE;
		}

		g_BloodCastle.SearchUserDeleteQuestItem(lpObj->m_Index);
	}
	else
	{
		if ( g_BloodCastle.CheckUserWinnerParty(lpObj->m_cBloodCastleIndex, lpObj->m_Index) == TRUE )
		{
			lpObj->m_bBloodCastleComplete = true;

			if ( g_BloodCastle.CheckPartyExist(lpObj->m_Index) == FALSE )
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);

				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest",
					lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);
			}
			else
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);
				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest - More Party to register",
					lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);
			}

			return FALSE;
		}

		GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
	}
	
	return FALSE;
}



BOOL NpcAngelMessanger(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	int iIndex = lpObj->m_Index;

	if ( gObj[iIndex].m_PK_Level >= 4 )
	{
		GCServerCmd(iIndex, 0x39, 0, 0);
		return TRUE;
	}

	int iITEM_LEVEL = 0;

	iITEM_LEVEL = g_BloodCastle.CheckEnterItem(lpObj->m_Index);

	if ( iITEM_LEVEL != 0 )
	{
		if ( iITEM_LEVEL != 10 && g_BloodCastle.CheckEnterLevel(lpObj->m_Index, iITEM_LEVEL-1) )
		{
			if ( g_BloodCastle.CheckEnterFreeTicket(lpObj->m_Index) == true )
			{
				iITEM_LEVEL = 10;
			}
		}

		if ( iITEM_LEVEL == 10 )
		{
			for (int i=0;i<MAX_CLOACK_LEVEL;i++)
			{
				if ( g_BloodCastle.CheckEnterLevel(lpObj->m_Index, i) == FALSE )
				{
					iITEM_LEVEL = i;
				}
			}
		}

		if ( g_BloodCastle.GetCurrentState(iITEM_LEVEL-1) == BC_STATE_CLOSED && g_BloodCastle.CheckCanEnter(iITEM_LEVEL-1) != false )
		{
			PMSG_TALKRESULT pMsg;

			pMsg.h.c = 0xC3;
			pMsg.h.headcode = 0x30;
			pMsg.h.size = sizeof(pMsg);
			pMsg.result = 0x06;

			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

			lpObj->m_IfState.use = 1;
			lpObj->m_IfState.type = 12;
		}
		else
		{
			GCServerCmd(lpObj->m_Index, 1, 0x14, 0);
		}
	}
	else
	{
		GCServerCmd(lpObj->m_Index, 1, 0x15, 0);
	}

	return FALSE;
}




BOOL NpcRolensiaMadam(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}





BOOL NpcDeviasWeapon(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}




BOOL NpcDarkSpiritTrainer(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( bCanChaosBox == TRUE )
	{
		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		
		if ( lpObj->m_bPShopOpen == true )
		{
			LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed",
				lpObj->AccountID, lpObj->Name);
			GCServerMsgStringSend(lMsg.Get(MSGGET(4, 194)), lpObj->m_Index, 1);

			return TRUE;
		}

		lpObj->m_IfState.type = 13;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;
		
		pMsg.result = 0x07;
		lpObj->bIsChaosMixCompleted = false;
		pMsg.level1 = gDQChaosSuccessRateLevel1;
		pMsg.level2 = gDQChaosSuccessRateLevel2;
		pMsg.level3 = gDQChaosSuccessRateLevel3;
		pMsg.level4 = gDQChaosSuccessRateLevel4;
		pMsg.level5 = gDQChaosSuccessRateLevel5;
		pMsg.level6 = gDQChaosSuccessRateLevel6;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		GCAnsCsMapSvrTaxInfo(lpObj->m_Index, 1, g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index));
		gObjInventoryTrans(lpObj->m_Index);

		LogAddTD("[%s][%s] Open Chaos Box", lpObj->AccountID, lpObj->Name);
		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	}

	return TRUE;
}





BOOL NpcJewelMixDealer(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( bCanChaosBox == TRUE )
	{
		if ( (lpObj->m_IfState.use) > 0 )
		{
			return TRUE;
		}

		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x09;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 12;

		LogAddTD("[JewelMix] [%s][%s] Jewel Mix Dealer Start", lpObj->AccountID, lpObj->Name);

		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);

	}

	return TRUE;
}



struct PMSG_ANS_USE_WEAPON_INTERFACE
{
	PBMSG_HEAD2 h;	// C1:B7:00
	BYTE btResult;	// 4
	BYTE btWeaponType;	// 5
	BYTE btObjIndexH;	// 6
	BYTE btObjIndexL;	// 7
};


BOOL NpcSiegeMachine_Attack(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}

	PMSG_ANS_USE_WEAPON_INTERFACE pResult = {0};

	PHeadSubSetB((LPBYTE)&pResult, 0xB7, 0x00, sizeof(pResult));

	pResult.btResult = 0;
	pResult.btWeaponType = 1;
	pResult.btObjIndexH = SET_NUMBERH(lpNpc->m_Index);
	pResult.btObjIndexL = SET_NUMBERL(lpNpc->m_Index);

	if ( gObjIsConnectedGP(lpNpc->m_iWeaponUser) == FALSE )
	{
		lpNpc->m_iWeaponUser = 0;
		lpNpc->m_btWeaponState = 1;
	}

	lpNpc->m_btWeaponState = 1;


	if ( lpNpc->m_btWeaponState == 1 )
	{
		pResult.btResult = 1;
		lpNpc->m_btWeaponState = 2;
		lpNpc->m_iWeaponUser = lpObj->m_Index;

		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 15;
	}
	else
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);
	}

	return TRUE;
}



BOOL NpcSiegeMachine_Defense(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	PMSG_ANS_USE_WEAPON_INTERFACE pResult = {0};

	PHeadSubSetB((LPBYTE)&pResult, 0xB7, 0x00, sizeof(pResult));

	pResult.btResult = 0;
	pResult.btWeaponType = 2;
	pResult.btObjIndexH = SET_NUMBERH(lpNpc->m_Index);
	pResult.btObjIndexL = SET_NUMBERL(lpNpc->m_Index);

	if ( gObjIsConnectedGP(lpNpc->m_iWeaponUser) == FALSE )
	{
		lpNpc->m_iWeaponUser = 0;
		lpNpc->m_btWeaponState = 1;
	}

	lpNpc->m_btWeaponState = 1;


	if ( lpNpc->m_btWeaponState == 1 )
	{
		pResult.btResult = 1;
		lpNpc->m_btWeaponState = 2;
		lpNpc->m_iWeaponUser = lpObj->m_Index;

		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 16;
	}
	else
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);
	}

	return TRUE;
}




BOOL NpcElderCircle(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	PMSG_TALKRESULT pMsg;

	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x0C;
	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	return TRUE;
}





BOOL NpcCastleGuard(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}


	if(g_CastleSiege.GetCastleState() == 7)
	{
		ChatTargetSend(lpNpc,lMsg.Get(0x657),lpObj->m_Index);
		return TRUE;
	}


	PMSG_TALKRESULT pMsg;

	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x0D;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;


	return TRUE;
}




BOOL NpcCastleGateLever(LPOBJ lpNpc, LPOBJ lpObj)
{
	/*if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}*/
	BOOL bControlEnable = 0;
	BYTE btResult = 0;
	int iGateIndex = -1;
	
	if(g_CastleSiege.GetCastleState() == 7)
	{
		if(lpObj->m_btCsJoinSide != 1)
		{
			btResult = 4;
			bControlEnable = FALSE;
		}
		else
		{
			bControlEnable = TRUE;
		}
	}
	else{
		if(g_CastleSiege.CheckCastleOwnerMember(lpObj->m_Index) == FALSE)
		{
			if(g_CastleSiege.CheckCastleOwnerUnionMember(lpObj->m_Index) == FALSE)
			{
				btResult = 4;
				bControlEnable = FALSE;
			}
		}
		else
		{
			bControlEnable = TRUE;
		}
	}

	if(bControlEnable != FALSE)
	{
		if(g_CastleSiege.CheckLeverAlive(lpNpc->m_Index) == TRUE)
		{
			if(g_CastleSiege.CheckCsGateAlive(lpObj->m_iCsGateLeverLinkIndex) == TRUE)
			{
				btResult = 1;
				iGateIndex = lpNpc->m_iCsGateLeverLinkIndex;
			}
			else
			{
				btResult = 2;
			}
		}
		else
		{
			btResult = 3;
		}
	}

	::GCAnsCsGateState(lpObj->m_Index,btResult,iGateIndex);

	if(btResult != 1)
	{
		return TRUE;
	}

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;

	return TRUE;
}





BOOL NpcCastleCrown(LPOBJ lpNpc, LPOBJ lpObj)
{
	int iUserIndex;

	if(!gObjIsConnected(lpObj->m_Index))
		return TRUE;

	if( g_CastleSiege.GetCastleState() != 7 )
		return TRUE;
	
	if( (lpObj->m_btCsJoinSide < 2) || (lpObj->m_bCsGuildInvolved == FALSE) )
		return TRUE;

	if(g_CastleSiege.CheckUnionGuildMaster(lpObj->m_Index) == FALSE)
		return TRUE;

	if( abs(lpNpc->Y - lpObj->Y) > 3 ||
		abs(lpNpc->X - lpObj->X) > 3 )
		return TRUE;

	if(g_CastleSiege.GetRegCrownAvailable() == FALSE)
		return TRUE;

	iUserIndex = g_CastleSiege.GetCrownUserIndex();

	if(gObjIsConnected(iUserIndex) == FALSE)
	{
		int iCrownSwitchIndex1,iCrownSwitchIndex2;//Não é o nome da variável
		iCrownSwitchIndex1 = g_CastleSiege.GetCrownSwitchUserIndex(217);
		iCrownSwitchIndex2 = g_CastleSiege.GetCrownSwitchUserIndex(218);
		
		if(gObjIsConnected(iCrownSwitchIndex1) == FALSE ||
			gObjIsConnected(iCrownSwitchIndex2) == FALSE)
		{
			::GCAnsCsAccessCrownState(lpObj->m_Index,4);
			LogAddTD("[CastleSiege] [%s][%s] Failed to Register Castle Crown (GUILD:%s)",
				lpObj->AccountID,lpObj->Name,lpObj->GuildName);
			return TRUE;
		}

		if(lpObj->m_btCsJoinSide != gObj[iCrownSwitchIndex1].m_btCsJoinSide ||
			lpObj->m_btCsJoinSide != gObj[iCrownSwitchIndex2].m_btCsJoinSide)
		{
			::GCAnsCsAccessCrownState(lpObj->m_Index,4);
			LogAddTD("[CastleSiege] [%s][%s] Failed to Register Castle Crown (GUILD:%s) (S1:%s/%s)(S2:%s/%s)",
				lpObj->AccountID,lpObj->Name,lpObj->GuildName,gObj[iCrownSwitchIndex1].Name,gObj[iCrownSwitchIndex1].GuildName,
				gObj[iCrownSwitchIndex2].Name,gObj[iCrownSwitchIndex2].GuildName);
			return TRUE;
		}

		::GCAnsCsAccessCrownState(lpObj->m_Index,0);
		g_CastleSiege.SetCrownUserIndex(lpObj->m_Index);
		g_CastleSiege.SetCrownAccessUserX(lpObj->X);
		g_CastleSiege.SetCrownAccessUserY(lpObj->Y);
		g_CastleSiege.SetCrownAccessTickCount();
		g_CastleSiege.NotifyAllUserCsProgState(0,lpObj->GuildName);
		
		LogAddTD("[CastleSiege] [%s][%s] Start to Register Castle Crown (GUILD:%s)",lpObj->AccountID,lpObj->Name,
			lpObj->GuildName);
	}
	else
	{	
		::GCAnsCsAccessCrownState(lpObj->m_Index,3);
	}
	return TRUE;
}




BOOL NpcCastleSwitch(LPOBJ lpNpc, LPOBJ lpObj)
{
	int iUserIndex;
	
	if(!gObjIsConnected(lpObj->m_Index))
		return TRUE;
	
	if(g_CastleSiege.GetCastleState() != 7)
		return TRUE;

	if(lpObj->m_btCsJoinSide < 2 )
		return TRUE;

	if( (abs(lpObj->Y - lpNpc->Y) >= 3) ||
		(abs(lpObj->X - lpNpc->X) > 3) )
	{
		return TRUE;
	}

	if(g_CastleSiege.CheckGuardianStatueExist() == TRUE)
	{
		MsgOutput(lpObj->m_Index,lMsg.Get(0x6c8));
		return TRUE;
	}

	iUserIndex = g_CastleSiege.GetCrownSwitchUserIndex(lpNpc->Class);

	if(gObjIsConnected(iUserIndex) == 0)
	{
		::GCAnsCsAccessSwitchState(lpObj->m_Index,lpNpc->m_Index,-1,TRUE);

		g_CastleSiege.SetCrownSwitchUserIndex(lpNpc->Class,lpObj->m_Index);

		LogAddTD("[CastleSiege] [%s][%s] Start to Push Castle Crown Switch (GUILD:%s) - CS X:%d/Y:%d",lpObj->AccountID,
			lpObj->Name,lpObj->GuildName,lpNpc->X,lpNpc->Y);
	}
	else
	{
		if(lpObj->m_Index != iUserIndex)
		{
			::GCAnsCsAccessSwitchState(lpObj->m_Index,lpNpc->m_Index,iUserIndex,2);
		}
	}	
	return TRUE;
}



BOOL NpcShadowPhantom(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	/*if ( lpObj->Level > gMaxElfSoldierBuffLevel )
	{
		GCServerCmd(lpObj->m_Index, 0x0D, 0, 0);
		
		return TRUE;
	}*/

//	lpObj->m_iSkillNPCHelpTime = GetTickCount();
//	lpObj->m_iSkillNPCDefense = lpObj->Level / 5 + 50;	// FORMULA
//	lpObj->m_iSkillNPCAttack = lpObj->Level / 3 + 45;	// FORMULA

//	lpObj->m_ViewSkillState |= 0x2000000;

	
	BYTE Packet[12] = { 0xC3,0x0C,0xF9,0x01,0x01,0x01,1,1,1,1,1,1};
	lpObj->TargetNumber = lpNpc->m_Index;
	DataSend(lpObj->m_Index, &Packet[0], Packet[1]);
	return TRUE;
}

BOOL NpcLeoHelper(LPOBJ lpNpc,LPOBJ lpObj)
{
	if(gObjIsConnected(lpObj->m_Index) == FALSE)
	{
		return TRUE;
	}

	CQuestSystem.NPCTalk(lpNpc,lpObj->m_Index);
	return TRUE;
}
/*BOOL NpcGreenSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}


	lpObj->m_iSkillNPCHelpTime = GetTickCount();
	lpObj->m_iSkillNPCDefense = 100;
	lpObj->m_ViewSkillState |= 0x2000000;

	GCStateInfoSend(lpObj, 1, 95); 

	return TRUE;
}
*/
/*
int gXMasPurpleSnowmanAGRaise;
int gXMasWhiteSnowmanHPRaise;
int gXMasBlackSnowmanMPRaise;
int gXMasOrangeSnowmanSpeedRaise;
int gXMasYellowSnowmanDMGRaise;
int gXMasGreenSnowmanDefRaise;*/
BOOL NpcGreenSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if(lpObj->m_BuffEffect != 0)
	{
		BuffEffectC.DelEffect(lpObj,lpObj->m_BuffEffect);
	}

	lpObj->m_iSkillNPCHelpTime = GetTickCount();
	lpObj->m_iSkillNPCDefense = gXMasGreenSnowmanDefRaise;
//	lpObj->m_ViewSkillState |= 0x2000000;
	lpObj->m_BuffEffect = 95;
//	GCStateInfoSend(lpObj, 1, 95,0,0); 

	return TRUE;
}

BOOL NpcWhiteSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if(lpObj->m_BuffEffect != 0)
	{
//		GCStateInfoSend(lpObj,0,lpObj->m_BuffEffect,0,0);
		lpObj->m_iSkillNPCDefense = 0;
		lpObj->m_iSkillNPCAG = 0;
		lpObj->m_iSkillNPCHelpTime = 0;
		lpObj->m_iSkillNPCAttack = 0;
		lpObj->m_iSkillNPCHP = 0;
		lpObj->m_iSkillNPCMP = 0;
		lpObj->m_iSkillNPCSpeed = 0;
		lpObj->m_BuffEffect = 0;
	}

	lpObj->m_iSkillNPCHelpTime = GetTickCount();
	lpObj->m_iSkillNPCHP = gXMasWhiteSnowmanHPRaise;
//	lpObj->m_ViewSkillState |= 0x2000000;
	lpObj->m_BuffEffect = 92;
	gObjCalCharacter(lpObj->m_Index);
////	GCStateInfoSend(lpObj, 1, 92,0,0); 
	return TRUE;
}

BOOL NpcBlackSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if(lpObj->m_BuffEffect != 0)
	{
//		GCStateInfoSend(lpObj,0,lpObj->m_BuffEffect,0,0);
		lpObj->m_iSkillNPCDefense = 0;
		lpObj->m_iSkillNPCAG = 0;
		lpObj->m_iSkillNPCHelpTime = 0;
		lpObj->m_iSkillNPCAttack = 0;
		lpObj->m_iSkillNPCHP = 0;
		lpObj->m_iSkillNPCMP = 0;
		lpObj->m_iSkillNPCSpeed = 0;
		lpObj->m_BuffEffect = 0;
	}

	lpObj->m_iSkillNPCHelpTime = GetTickCount();
	lpObj->m_iSkillNPCMP = gXMasBlackSnowmanMPRaise;
//	lpObj->m_ViewSkillState |= 0x2000000;
	lpObj->m_BuffEffect = 93;
	gObjCalCharacter(lpObj->m_Index);
//	GCStateInfoSend(lpObj, 1, 93,0,0); 
	return TRUE;
}

BOOL NpcYellowSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if(lpObj->m_BuffEffect != 0)
	{
//		GCStateInfoSend(lpObj,0,lpObj->m_BuffEffect,0,0);
		lpObj->m_iSkillNPCDefense = 0;
		lpObj->m_iSkillNPCAG = 0;
		lpObj->m_iSkillNPCHelpTime = 0;
		lpObj->m_iSkillNPCAttack = 0;
		lpObj->m_iSkillNPCHP = 0;
		lpObj->m_iSkillNPCMP = 0;
		lpObj->m_iSkillNPCSpeed = 0;
		lpObj->m_BuffEffect = 0;
	}

	lpObj->m_iSkillNPCHelpTime = GetTickCount();
	lpObj->m_iSkillNPCAttack = gXMasYellowSnowmanDMGRaise;
//	lpObj->m_ViewSkillState |= 0x2000000;
	lpObj->m_BuffEffect = 94;
	gObjCalCharacter(lpObj->m_Index);
//	GCStateInfoSend(lpObj, 1, 94,0,0); 
	return TRUE;
}

BOOL NpcOrangeSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if(lpObj->m_BuffEffect != 0)
	{
//		GCStateInfoSend(lpObj,0,lpObj->m_BuffEffect,0,0);
		lpObj->m_iSkillNPCDefense = 0;
		lpObj->m_iSkillNPCAG = 0;
		lpObj->m_iSkillNPCHelpTime = 0;
		lpObj->m_iSkillNPCAttack = 0;
		lpObj->m_iSkillNPCHP = 0;
		lpObj->m_iSkillNPCMP = 0;
		lpObj->m_iSkillNPCSpeed = 0;
		lpObj->m_BuffEffect = 0;
	}

	lpObj->m_iSkillNPCHelpTime = GetTickCount();
	lpObj->m_iSkillNPCSpeed = gXMasOrangeSnowmanSpeedRaise;
//	lpObj->m_ViewSkillState |= 0x2000000;
	lpObj->m_BuffEffect = 96;
	gObjCalCharacter(lpObj->m_Index);
//	GCStateInfoSend(lpObj, 1, 96,0,0); 
//	MsgOutput(lpObj->m_Index,"Orange snowman");
	return TRUE;

}

BOOL NpcPurpleSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if(lpObj->m_BuffEffect != 0)
	{
//		GCStateInfoSend(lpObj,0,lpObj->m_BuffEffect,0,0);
		lpObj->m_iSkillNPCDefense = 0;
		lpObj->m_iSkillNPCAG = 0;
		lpObj->m_iSkillNPCHelpTime = 0;
		lpObj->m_iSkillNPCAttack = 0;
		lpObj->m_iSkillNPCHP = 0;
		lpObj->m_iSkillNPCMP = 0;
		lpObj->m_iSkillNPCSpeed = 0;
		lpObj->m_BuffEffect = 0;
	}

	lpObj->m_iSkillNPCHelpTime = GetTickCount();
	lpObj->m_iSkillNPCAG = gXMasPurpleSnowmanAGRaise;
//	lpObj->m_ViewSkillState |= 0x2000000;
	lpObj->m_BuffEffect = 97;
	gObjCalCharacter(lpObj->m_Index);
	//..GCStateInfoSend(lpObj, 1, 97,0,0); 
	return TRUE;

}

BOOL NpcRedSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	lpObj->Life = lpObj->MaxLife + lpObj->AddLife;
	GCReFillSend(lpObj->m_Index,lpObj->MaxLife,0xFF,0,lpObj->iShield);
	return TRUE;

}
BOOL NpcBlueSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	lpObj->Mana = lpObj->MaxMana + lpObj->AddMana;
	GCManaSend(lpObj->m_Index,lpObj->MaxMana,0xFF,0,lpObj->MaxBP);
	return TRUE;

}

BOOL NpcSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	gObjMoveGate(lpObj->m_Index,22);

	return TRUE;

}
int santaopen =0; // replace this later
int santaday =0;
BOOL NpcSantaClaus(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	
	  time_t rawtime;
	  struct tm * timeinfo;

	  time ( &rawtime );
	  timeinfo = localtime ( &rawtime );

	if(santaopen == 0)
	{
		SantaClausItemBagOpen(lpObj);
		santaopen = 1;
		santaday = timeinfo->tm_mday;
	}

	if(santaday != timeinfo->tm_mday)
	{
		santaopen = 0;
	}
	  
	return TRUE;

}
BOOL NpcSilverBox(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

/*	int dropitem = rand()%3;

	if(dropitem < 2)
	{
		ItemSerialCreateSend(lpObj->m_Index,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(14,16),0,1,0,0,0,lpObj->m_Index,0,0);
		ItemSerialCreateSend(lpObj->m_Index,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(14,13),0,1,0,0,0,lpObj->m_Index,0,0);
	}
	else
	{
		g_DoppelGanger.m_DGData[lpObj->m_btDoubleGoerRoom].CaterpillarIndex = gObjAddMonster(lpObj->MapNumber);
		gObjSetMonster(g_DoubleGoer.m_DGData[lpObj->m_btDoubleGoerRoom].CaterpillarIndex,532);
		gObj[g_DoubleGoer.m_DGData[lpObj->m_btDoubleGoerRoom].CaterpillarIndex].MapNumber = lpObj->MapNumber;
		gObj[g_DoubleGoer.m_DGData[lpObj->m_btDoubleGoerRoom].CaterpillarIndex].X = lpObj->X;
		gObj[g_DoubleGoer.m_DGData[lpObj->m_btDoubleGoerRoom].CaterpillarIndex].Y = lpObj->Y;
	}
	for(int i=0;i<3;i++)
	{
		gObjDel(g_DoubleGoer.m_DGData[lpObj->m_btDoubleGoerRoom].SilverBoxIndex[i]);
	}*/
	return true;
}
BOOL NpcCastleHuntZoneGuard(LPOBJ lpNpc,LPOBJ lpObj)
{
	if(!gObjIsConnected(lpObj->m_Index))
		return TRUE;

	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}



	PMSG_ANS_GUARD_IN_CASTLE_HUNTZONE pResult = {0};

	PHeadSubSetB((LPBYTE)&pResult,0xB9,0x03,sizeof(PMSG_ANS_GUARD_IN_CASTLE_HUNTZONE));
	pResult.btResult = TRUE;
	pResult.iMaxPrice = 300000;
	pResult.iUnitOfPrice = 10000;
	pResult.btUsable = 0;
	pResult.iCurrentPrice = 0;

	pResult.iCurrentPrice = g_CastleSiegeSync.GetTaxHuntZone(lpObj->m_Index,FALSE);

	if(g_CastleSiege.GetHuntZoneEnter())
	{
		pResult.btUsable = TRUE;
	}

	if(lpObj->lpGuild != NULL)
	{
		if(g_CastleSiege.CheckCastleOwnerUnionMember(lpObj->m_Index))
		{
			pResult.btResult = 2;
		}

		if(g_CastleSiege.CheckCastleOwnerMember(lpObj->m_Index))
		{
			if(lpObj->GuildStatus == 128)
			{
				pResult.btResult = 3;
			}
		}
	}
	else
	{
		if(g_CastleSiege.GetHuntZoneEnter())
		{
			pResult.btResult = TRUE;
		}
	}

	DataSend(lpObj->m_Index,(LPBYTE)&pResult,pResult.h.size);

	return TRUE;
}
BOOL NpcGoldBox(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

		ItemSerialCreateSend(lpObj->m_Index,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(14,16),0,1,0,0,0,lpObj->m_Index,0,0);
		ItemSerialCreateSend(lpObj->m_Index,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(14,13),0,1,0,0,0,lpObj->m_Index,0,0);
	
//		gObjDel(g_DoubleGoer.m_DGData[lpObj->m_btDoubleGoerRoom].GoldBoxIndex);
		return true;
}
//92 - +500 hp
//93 - mana +500
//94 - attack power +30
//96 - attack speed +15

bool NpcJerint(LPOBJ lpNpc, LPOBJ lpObj)
{
	PMSG_TALKRESULT pMsg;
	PHeadSetBE((LPBYTE)&pMsg, 0x30, 5);
	pMsg.result = 0x24;
	pMsg.level1 = 0;
	lpObj->TargetShopNumber = 522;
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, 5);
	return true;
}
bool NpcJulia(LPOBJ lpNpc, LPOBJ lpObj)
{
	PMSG_TALKRESULT pMsg;
	PHeadSetBE((LPBYTE)&pMsg, 0x30, 5);
	pMsg.result = 0x25;
	pMsg.level1 = 0;
	//lpObj->TargetShopNumber = 522;
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, 5);
	return true;
}
bool NpcGens(LPOBJ lpNpc, LPOBJ lpObj)
{
	GC_ANS_NPC_TALK_V3 pMsg;

	PHeadSubSetBE((LPBYTE)&pMsg, 0xF9, 0x01, sizeof(pMsg));
	pMsg.Index = lpObj->m_Index;
	pMsg.NpcType = lpNpc->Class;
	pMsg.Points = lpObj->GensExp; // GENS POINTS

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;
	lpObj->TargetShopNumber = lpNpc->Class;
	lpObj->TargetNumber = lpNpc->m_Index;
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	return true;
}
