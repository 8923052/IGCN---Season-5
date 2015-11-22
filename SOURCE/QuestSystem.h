#ifndef QUESTSYSTEM_H
#define QUESTSYSTEM_H

#include "user.h"

#define MAX_QUESTS 200

struct QUESTINFODATA
{
	int iQuestIndex;
	WORD wMinLevel;
	char szQuestName[100];
	char szQuestInfo[100];
	int iNeededItem;
	int iRewardItem;
	int iRewardZen;
	int iRewardPoints;
	int iRewardExp;
	int iRewardExpUpd;
	int iRewardLvUpUpd;
	BYTE isRewardLevelUp;
	int iMonsterId;
	int iMonsterCount;
	int iMonsterLevel;
	int iMapNumber;
};

class CQuestManager
{
public:
	void Init();
	void LoadFile(char *filename);
	void Insert(int iQIndex,WORD wMinLevel,char *szQuestName,char *szQuestInfo, int iNeededItem,int iRewardItem,int iRewardZen,int iRewardPoints,int iRewardExp,int iRewardExpUpd,int iRewardLvUpUpd,BYTE isRewardLevelUp, int iMonsterId,int iMonsterCount,int iMonsterLv, int iMapNumber);
	void NPCTalk(OBJECTSTRUCT *lpNpc,int aIndex);
	void QuestStart(int aIndex,int QuestId);
	void QuestManage(OBJECTSTRUCT *lpObj, OBJECTSTRUCT *lpTargetObj);
	void QuestFinish(int aIndex,int QuestId,OBJECTSTRUCT *lpNpc);

	QUESTINFODATA m_QuestData[MAX_QUESTS];

}; extern CQuestManager CQuestSystem;

#endif