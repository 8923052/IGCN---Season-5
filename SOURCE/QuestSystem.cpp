#include "stdafx.h"
#include "QuestSystem.h"
#include "..\include\readscript.h"
#include "logproc.h"
#include "user.h"
#include "protocol.h"
#include "EDSProtocol.h"
#include "..\common\winutil.h"
#include "GameMain.h"
#include "DSProtocol.h"

CQuestManager CQuestSystem;

struct FHP_FRIEND_MEMO_SEND
{
	PWMSG_HEAD h;
	short Number;	// 4
	DWORD WindowGuid;	// 8
	char Name[10];	// C
	char ToName[10];	// 16
	char Subject[32];	// 20
	BYTE Dir;	// 40
	BYTE Action;	// 41
	short MemoSize;	// 42
	BYTE Photo[18];	// 44
	char Memo[1000];	// 56
};

void SendMail(PMSG_FRIEND_MEMO * lpMsg, int aIndex)
{
	if ( !gObjIsConnectedGP(aIndex))
	{
		LogAddTD("error-L2 : Index %s %d", __FILE__, __LINE__);
		return;
	}

	char_ID Name(lpMsg->Name);

	if ( gObj[aIndex].Money < 1000 )
	{
		FHP_FRIEND_MEMO_SEND_RESULT pResult;

		pResult.Number = aIndex;
		pResult.Result = 7;
		pResult.WindowGuid = lpMsg->WindowGuid;
		memcpy(pResult.Name, gObj[aIndex].Name, sizeof(pResult.Name));

		FriendMemoSendResult(&pResult);

		return;
	}

	if ( lpMsg->MemoSize < 0 || lpMsg->MemoSize > 1000 )
	{
		FHP_FRIEND_MEMO_SEND_RESULT pResult;

		pResult.Number = aIndex;
		pResult.Result = 0;
		pResult.WindowGuid = lpMsg->WindowGuid;
		memcpy(pResult.Name, gObj[aIndex].Name, sizeof(pResult.Name));

		FriendMemoSendResult(&pResult);

		return;
	}

	if ( Name.GetLength() < 1 )
	{
		FHP_FRIEND_MEMO_SEND_RESULT pResult;

		pResult.Number = aIndex;
		pResult.Result = 0;
		pResult.WindowGuid = lpMsg->WindowGuid;
		memcpy(pResult.Name, gObj[aIndex].Name, sizeof(pResult.Name));

		FriendMemoSendResult(&pResult);

		return;
	}

	FHP_FRIEND_MEMO_SEND pMsg;
	int bsize = lpMsg->MemoSize + sizeof(pMsg) - sizeof(pMsg.Memo);

	pMsg.h.set((LPBYTE)&pMsg, 0x70, bsize);
	pMsg.WindowGuid = lpMsg->WindowGuid;
	pMsg.MemoSize = lpMsg->MemoSize;
	pMsg.Number = aIndex;
	pMsg.Dir = lpMsg->Dir;
	pMsg.Action = lpMsg->Action;
	memcpy(pMsg.Subject, lpMsg->Subject, sizeof(pMsg.Subject));
	memcpy(pMsg.Name, gObj[aIndex].Name, sizeof(pMsg.Name));
	memcpy(pMsg.Photo, gObj[aIndex].CharSet, sizeof(pMsg.Photo));
	memcpy(pMsg.ToName, lpMsg->Name, sizeof(pMsg.ToName));
	memcpy(pMsg.Memo, lpMsg->Memo, lpMsg->MemoSize);

	wsExDbCli.DataSend((PCHAR)&pMsg, bsize);

	LogAdd("[%s] Friend mail send %s (Size:%d)", gObj[aIndex].Name, Name.GetBuffer(), bsize);
}

void CQuestManager::Init()
{
	for(int i=0;i<MAX_QUESTS;i++)
	{
		this->m_QuestData[i].iQuestIndex = -1;
		this->m_QuestData[i].iMapNumber = -1;
		this->m_QuestData[i].iMonsterLevel = -1;
		this->m_QuestData[i].iNeededItem = -1;
		this->m_QuestData[i].iRewardExp = 0;
		this->m_QuestData[i].iRewardExpUpd = 0;
		this->m_QuestData[i].iRewardItem = 0;
		this->m_QuestData[i].iRewardLvUpUpd = 0;
		this->m_QuestData[i].iRewardPoints = 0;
		this->m_QuestData[i].iRewardZen = 0;
		this->m_QuestData[i].isRewardLevelUp = 0;
		this->m_QuestData[i].wMinLevel = 0;
	}
}

void CQuestManager::LoadFile(char *filename)
{
	this->Init();
 if ( (SMDFile = fopen(filename, "r")) == NULL )
	 {
	    MessageBoxA(0,"CQuestManager::LoadFile() error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	 }

	 SMDToken Token;
	 int iIndex;
	int iQuestIndex =0;
	WORD wMinLevel =0;
	char szQuestName[100] = {0};
	char szQuestInfo[100] = {0};
	int iNeededItem = 0;
	int iRewardItem = 0;
	int iRewardZen = 0;
	int iRewardPoints = 0;
	int iRewardExp =0;
	int iRewardExpUpd = 0;
	int iRewardLvUpUpd = 0;
	BYTE isRewardLevelUp = 0;
	int iMonsterId = 0;
	int iMonsterLevel = 0;
	int iMapNumber = 0;
	int iMonsterCount =0;

	 while(true)
	 {
		 Token = GetToken();
		 if(Token == END)
			break;
		 if(Token == NUMBER)
		 {
			 iIndex = TokenNumber;

			 while(true)
			 {
				 Token = GetToken();
				 if(strcmp("end",TokenString) == 0)
					 break;

				iQuestIndex = TokenNumber;

			    Token = GetToken();
				memcpy(szQuestName,TokenString,sizeof(szQuestName));

				Token = GetToken();
				memcpy(szQuestInfo,TokenString,sizeof(szQuestInfo));

				Token = GetToken();
				iNeededItem = TokenNumber;

				Token = GetToken();
				iRewardItem = TokenNumber;

				Token = GetToken();
				iRewardZen = TokenNumber;

				Token = GetToken();
				iRewardPoints = TokenNumber;

				Token = GetToken();
				iRewardExp = TokenNumber;

				Token = GetToken();
				iRewardExpUpd = TokenNumber;

				Token = GetToken();
				iRewardLvUpUpd = TokenNumber;

				Token = GetToken();
				isRewardLevelUp = TokenNumber;

				Token = GetToken();
				iMonsterId = TokenNumber;

				Token = GetToken();
				iMonsterCount= TokenNumber;

				Token = GetToken();
				iMonsterLevel = TokenNumber;

				Token = GetToken();
				iMapNumber = TokenNumber;

				Token = GetToken();
				wMinLevel = TokenNumber;

				this->Insert(iQuestIndex,wMinLevel,szQuestName,szQuestInfo,iNeededItem,iRewardItem,iRewardZen,iRewardPoints,iRewardExp,iRewardExpUpd,iRewardLvUpUpd,isRewardLevelUp,iMonsterId,iMonsterCount,iMonsterLevel,iMapNumber);

			 }
		 }
	 }

	 fclose(SMDFile);
	 LogAddTD("[Quest Manager] File Loaded successfuly");
	 return;

}

void CQuestManager::Insert(int iQIndex, WORD wMinLevel, char *szQuestName, char *szQuestInfo, int iNeededItem, int iRewardItem, int iRewardZen, int iRewardPoints, int iRewardExp, int iRewardExpUpd, int iRewardLvUpUpd, BYTE isRewardLevelUp, int iMonsterId, int iMonsterCount, int iMonsterLv, int iMapNumber)
{
	this->m_QuestData[iQIndex].iQuestIndex = iQIndex;
	this->m_QuestData[iQIndex].iMapNumber = iMapNumber;
	this->m_QuestData[iQIndex].iMonsterId = iMonsterId;
	this->m_QuestData[iQIndex].iMonsterCount = iMonsterCount;
	this->m_QuestData[iQIndex].iMonsterLevel = iMonsterLv;
	this->m_QuestData[iQIndex].iNeededItem = iNeededItem;
	this->m_QuestData[iQIndex].iRewardExp = iRewardExp;
	this->m_QuestData[iQIndex].iRewardExpUpd = iRewardExpUpd;
	this->m_QuestData[iQIndex].iRewardItem = iRewardItem;
	this->m_QuestData[iQIndex].iRewardLvUpUpd = iRewardLvUpUpd;
	this->m_QuestData[iQIndex].iRewardPoints = iRewardPoints;
	this->m_QuestData[iQIndex].iRewardZen = iRewardZen;
	this->m_QuestData[iQIndex].isRewardLevelUp = isRewardLevelUp;
	strcpy(this->m_QuestData[iQIndex].szQuestInfo,szQuestInfo);
	strcpy(this->m_QuestData[iQIndex].szQuestName,szQuestName);
	this->m_QuestData[iQIndex].wMinLevel = wMinLevel;
}

void CQuestManager::NPCTalk(OBJECTSTRUCT *lpNpc,int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(!gIsCQSystem)
	{
		return;
	}
	if(lpObj->m_Quest[10] > gCQSystemQuestCount)
	{
		ChatTargetSend(lpNpc,"Currently no more quests. Check later",aIndex);
		return;
	}
	if(lpObj->m_Quest[10] == 0xFF)
	{
		lpObj->m_Quest[10] = 1; // Quest id
	}

	if(lpObj->m_Quest[9] == 0xFF)
	{
		lpObj->m_Quest[9] = 0; // State
	}

	if(lpObj->m_Quest[8] == 0xFF)
	{
		lpObj->m_Quest[8] = 0; // kill count
	}

	if(lpObj->m_Quest[9] == 2 || lpObj->m_Quest[9] == 0)
	{
		this->QuestStart(aIndex,lpObj->m_Quest[10]);
		ChatTargetSend(lpNpc,"Quest Info Sent to MuMail!!!",aIndex);
		return;
	}
//	this->QuestStart(aIndex,lpObj->m_Quest[10]);
	if(lpObj->m_Quest[9] == 1)
	{
		this->QuestFinish(aIndex,lpObj->m_Quest[10],lpNpc);
		return;
	}
	//ChatTargetSend(lpNpc,"Quest  in Progress",aIndex);
}

void CQuestManager::QuestStart(int aIndex, int QuestId)
{
	LPOBJ lpObj = &gObj[aIndex];
	char Message[100];
	char Title[100];

	sprintf(Title,"%s",this->m_QuestData[QuestId].szQuestName);
	sprintf(Message,"%s",this->m_QuestData[QuestId].szQuestInfo);

	PMSG_FRIEND_MEMO pMsg;
	pMsg.Action = 0;
	pMsg.Dir = 0;
	strcpy(pMsg.Memo,Message);
	pMsg.MemoSize = strlen(Message);
	strcpy(pMsg.Subject,Title);
	strcpy(pMsg.Name,gObj[aIndex].Name);
	pMsg.WindowGuid = 0;


	SendMail(&pMsg,aIndex);
	lpObj->m_Quest[9] = 1;
	LogAddTD("[%s][%s] [Quest Sys] Start Quest [%s]",lpObj->AccountID,lpObj->Name,this->m_QuestData[QuestId].szQuestName);
}

void CQuestManager::QuestManage(OBJECTSTRUCT *lpObj, OBJECTSTRUCT *lpTargetObj)
{
	if(this->m_QuestData[lpObj->m_Quest[10]].iMonsterId > 0)
	{
		if(lpTargetObj->Class == this->m_QuestData[lpObj->m_Quest[10]].iMonsterId && this->m_QuestData[lpObj->m_Quest[10]].iMonsterCount < lpObj->m_Quest[8])
		{
			lpObj->m_Quest[8]++;
			MsgOutput(lpObj->m_Index,"Quest Monster Kill [%d/%d]",lpObj->m_Quest[8],this->m_QuestData[lpObj->m_Quest[10]].iMonsterCount);
				return;
		}
	}
}

void CQuestManager::QuestFinish(int aIndex, int QuestId, OBJECTSTRUCT *lpNpc)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->m_Quest[8] == 1 && lpObj->m_Quest[9] == 1)
	{
		lpObj->m_Quest[8] = 0;
		lpObj->m_Quest[10]++;
		lpObj->m_Quest[9] = 2;
		//void ItemSerialCreateSend(int aIndex, BYTE MapNumber, BYTE x, BYTE y, int type, BYTE level, BYTE dur, BYTE Op1, BYTE Op2, BYTE Op3, int LootIndex, BYTE NewOption, BYTE SetOption);

		ItemSerialCreateSend(lpObj->m_Index,lpObj->MapNumber,lpObj->X,lpObj->Y,this->m_QuestData[QuestId].iRewardItem,0,0,0,0,0,lpObj->m_Index,0,0);
		ChatTargetSend(lpNpc,"Quest Finished, Enjoy Reward",aIndex);
		LogAddTD("[%s][%s] [Quest Sys] Finished Quest %s",lpObj->AccountID,lpObj->Name,this->m_QuestData[QuestId].szQuestName);
		return;
	}

	ChatTargetSend(lpNpc,"Quest not finished, please check conditions",aIndex);
	return;
}