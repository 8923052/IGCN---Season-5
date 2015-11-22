#ifndef NPCTALK_H
#define NPCTALK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_NPC_PHANTOM_BUFFER	180



struct GC_ANS_NPC_TALK_V1
{
	PHEADB	PHeader;	// C3:30
	BYTE NpcNumber;
	BYTE Param1;
	BYTE Param2;
	BYTE Param3;
	BYTE Param4;
};

struct GC_ANS_NPC_TALK_V2
{
	PHEADB	PHeader;	// C3:30
	BYTE NpcNumber;
	BYTE Param1;
	BYTE Param2;
	BYTE Param3;
	BYTE Param4;
	BYTE Param5;
	BYTE Param6;
};

struct GC_ANS_NPC_TALK_V3
{
	PBMSG_HEAD2		h;		// C3:F9:01
	WORD		NpcType;
	WORD		Index;
	DWORD		Points;
};

struct PMSG_QUEST_DIALOG {
	PBMSG_HEAD	head;
	unsigned char	quest_id;
	unsigned char	dialog_id;
};

struct TOPMSG_KILLED_INFO {
	unsigned char	killed_id;
	unsigned char	display;
	unsigned char	unk_2[2];
	unsigned char	killed_count;
	unsigned char	unk_3[3];
};

struct PMSG_QUEST_KILLEDCOUNT {
	PBMSG_HEAD		head;
	unsigned char		unk_1[5];
	TOPMSG_KILLED_INFO	killed[4];
};

BOOL NpcTalk(LPOBJ lpNpc, LPOBJ lpObj);

int NpcBattleAnnouncer(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcFasi(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcGuildMasterTalk(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRolensiaGuard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcChaosGoblelin(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRusipher(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcPosionGirl(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasWizard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasGuard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasWareHousemen(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcWarehouse(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcNoriaRara(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasMadam(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcEventChipNPC(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRorensiaSmith(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcNoriJangIn(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcQuestCheck(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcServerDivision(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRoadMerchant(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcAngelKing(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcAngelMessanger(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRolensiaMadam(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasWeapon(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDarkSpiritTrainer(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcJewelMixDealer(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSiegeMachine_Attack(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSiegeMachine_Defense(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcElderCircle(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleGuard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleGateLever(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleCrown(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleSwitch(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcShadowPhantom(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcMainatenceMachine(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcReira(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcChaosCardMaster(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcPriestDevin(LPOBJ lpNpc, LPOBJ lpObj);
BOOL ShopKepper13(LPOBJ lpNpc, LPOBJ lpObj);
BOOL ShopKepper14(LPOBJ lpNpc, LPOBJ lpObj);
BOOL ShopKepper15(LPOBJ lpNpc, LPOBJ lpObj);
BOOL ShopKepper16(LPOBJ lpNpc, LPOBJ lpObj);
BOOL ShopKepper17(LPOBJ lpNpc, LPOBJ lpObj);
BOOL ShopKepper18(LPOBJ lpNpc, LPOBJ lpObj);
BOOL ShopKepper19(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcWareWolfQwarell(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcGateKeeper(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcGreenSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcBlackSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcWhiteSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcYellowSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcPurpleSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcOrangeSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRedSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcBlueSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcLeoHelper(LPOBJ lpNpc,LPOBJ lpObj);
BOOL NpcGateKeeperTitus(OBJECTSTRUCT *lpNpc, OBJECTSTRUCT *lpObj);
BOOL SartigantheAngel(OBJECTSTRUCT *lpNpc, OBJECTSTRUCT *lpObj);
BOOL MossMerchant(OBJECTSTRUCT *lpNpc, OBJECTSTRUCT *lpObj);
BOOL NpcGens1(OBJECTSTRUCT *lpNpc,OBJECTSTRUCT *lpObj);
BOOL NpcGens2(OBJECTSTRUCT *lpNpc,OBJECTSTRUCT *lpObj);
BOOL BlossomGovernor(OBJECTSTRUCT *lpNpc,OBJECTSTRUCT *lpObj);
BOOL SokcetResearcher(OBJECTSTRUCT *lpNpc,OBJECTSTRUCT *lpObj);
BOOL NpcAlchemistMenssager(LPOBJ lpObj);
BOOL SokcetMaster(OBJECTSTRUCT *lpNpc,OBJECTSTRUCT *lpObj);
BOOL NpcSilverBox(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcGoldBox(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSantaClaus(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleHuntZoneGuard(LPOBJ lpNpc,LPOBJ lpObj);
BOOL NpcRaul(LPOBJ lpNpc,LPOBJ lpObj);
BOOL NpcChristina(LPOBJ lpNpc,LPOBJ lpObj);
bool NpcJulia(LPOBJ lpNpc, LPOBJ lpObj);
void QuestDialogEx(int aIndex);
void QuestApplyEx(int aIndex);
void QuestClearEx(int aIndex);
void QuestTeleport(int aIndex, int Type);
void QuestSetPrizeEx(int aIndex);
void QuestSetCharTransformationEx(int aIndex);
bool NpcJerint(LPOBJ lpNpc, LPOBJ lpObj);
bool NpcGens(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcStatue(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcBox(LPOBJ lpNpc, LPOBJ lpObj);

#endif