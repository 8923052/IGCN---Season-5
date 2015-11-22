#ifndef SUPPORTQUESTSYSTEM_H
#define SUPPORTQUESTSYSTEM_H
#include "..\include\prodef.h"


struct PWMSG_COUNT_CHAR{
	PBMSG_HEAD2 h;
	BYTE count;
};

struct PWMSG_COUNTQ {
	PBMSG_HEAD2 h;
	BYTE a;
	BYTE b;
	BYTE c;
	BYTE d;
};
struct PMSG_QUESTLISTSENDCHAR{
	BYTE indexL;
	BYTE indexH;
	BYTE typeL;
	BYTE typeH;
};

struct PMSG_QUESTLISTSEND
{
	BYTE indexL;
	BYTE indexH;
	BYTE typeL;
	BYTE typeH;
};
struct PMSG_SENDQUESTINDEX
{
	PBMSG_HEAD2 h;
	BYTE indexL;	// 4
	BYTE indexH;	// 5
	BYTE typeL;		// 6
	BYTE typeH;		// 7
};

//C1 09 F6 0B 01 00 01 00 00 00 00
struct PMSG_SENDQUESTCONT
{
	PBMSG_HEAD2 h;
	BYTE indexL;	// 4
	BYTE indexH;	// 5
	BYTE typeL;		// 6
	BYTE typeH;		// 7
	int var;		// 8
};
#pragma pack (1)

struct REQUIREMENT_INFO
{
	 int RequirementType;
	 short RequirementID;
	 int RequiredCount;
	 short Count;
	 BYTE RequirementItemInfo[12];
};

struct REWARD_INFO
{
	 int RewardType;
	 short RewardID;
	 int RewardCount;
	 BYTE RewardItemInfo[12];
};

struct PMSG_QUEST_DETAIL // C1:F6:0C (NPC) || C1:F6:1B (T MENU)
{
	 PBMSG_HEAD2 h;
	 short QuestID;
	 short QuestGroup;
	 unsigned char NeedsCount;
	 unsigned char PrizeCount;
	 unsigned char Unk1;
	 REQUIREMENT_INFO Needs[5];
	 REWARD_INFO Prizes[5];
};
struct PMSG_TUTORIAL_OPENWINDOW_REQ // C1:F6:10 (sent by main when you have special quest like open c windows (tutorial))
{
 PBMSG_HEAD2 h;
 short QuestID;
 short QuestGroup;
};
#pragma pack()

struct SUPPORTQUEST
{
	short NPCid;
	short QuestType;
	short QuestIndex;
	short LevelMin;
	short LevelMax;
	unsigned char ReqCount;
	unsigned char RewardCount;
	unsigned char unknown;
	unsigned char DWStart;
	unsigned char DKStart;
	unsigned char ELFStart;
	unsigned char MGStart;
	unsigned char DLStart;
	unsigned char SumStart;
	unsigned char RageStart;
	unsigned char cancelId;
	REQUIREMENT_INFO Requirements[5];
	REWARD_INFO Rewards[5];
};

struct PMSG_QUEST_FINISH_ANS
{
	 PBMSG_HEAD2 h;
	 short QuestAccept;
	 short QuestGroup;
	 BYTE Result;
};
class CSupportQuestSystem{
public:
	~CSupportQuestSystem();
	CSupportQuestSystem();

	void Init();
	
	void LoadFile(LPSTR szFile);

	void LoadRewardFile(LPSTR szFile,int qType, int qIndex);
	void LoadRequirementFile(LPSTR szFile,int qType, int qIndex);

	void SendListChar(int aIndex);
	void SendListNpc(int aIndex);
	void Accept(int aIndex, LPBYTE aRecv);
	void MonsterMng(int aIndex, int aTargetIndex);
	void Reward(int aIndex, LPBYTE aRecv);
	void SendRequirments(int aIndex, LPBYTE aRecv, bool ForCharacter,  short questid);
	void Continue(int aIndex, LPBYTE aRecv);
	
	SUPPORTQUEST m_QuestData[20][200];


}; extern CSupportQuestSystem g_SQuestSys;



struct SUPPORT_QUEST_INFO
{
	short Type1Taken;
	short Type1Index;
	short Type2Taken;
	short Type2Index;
	short Type3Taken;
	short Type3Index;
	short Type4Taken;
	short Type4Index;
	short Type5Taken;
	short Type5Index;
	short Type6Taken;
	short Type6Index;
	short Type7Taken;
	short Type7Index;
	short Type8Taken;
	short Type8Index;
	short Type9Taken;
	short Type9Index;
	short Type10Taken;
	short Type10Index;
	short Type11Taken;
	short Type11Index;
	short Type12Taken;
	short Type12Index;
	short Type13Taken;
	short Type13Index;
	short Type14Taken;
	short Type14Index;
	short Type15Taken;
	short Type15Index;
	short Type16Taken;
	short Type16Index;
	short Type17Taken;
	short Type17Index;
	short Type18Taken;
	short Type18Index;
	short Type19Taken;
	short Type19Index;
	short Type20Taken;
	short Type20Index;
	short Type15Count;
};
#endif