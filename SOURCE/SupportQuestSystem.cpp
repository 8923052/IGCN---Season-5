#include "stdafx.h"
#include "SupportQuestSystem.h"
#include "user.h"
#include "..\include\ReadScript.h"
#include "logproc.h"
#include "DSProtocol.h"
#include "GensSystem.h"
CSupportQuestSystem g_SQuestSys;

CSupportQuestSystem::~CSupportQuestSystem()
{

}
CSupportQuestSystem::CSupportQuestSystem()
{

}

void CSupportQuestSystem::Init()
{

}
void CSupportQuestSystem::LoadRequirementFile(LPSTR szFile, int qType, int qId)
{

	SMDFile = fopen(szFile, "r");

	if ( SMDFile == NULL )
	{ 
		MsgBox("[SupportQuestSystem] Quest Reqs file Load Fail [%s]", szFile);
		return;
	}
	int Token;
	int type = -1;
	int count = 0;

    while ( true )
	{
	    Token = GetToken();

        if( Token == 2)
		{
            break;
		}

		type = TokenNumber;

		while ( true )
		{
		    if( type == 0 )
			{
			    Token = GetToken();

				if ( strcmp("end", TokenString ) == 0)
				{
					count = 0;
					break;
				}

				this->m_QuestData[qType][qId].Requirements[count].RequirementType = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Requirements[count].RequirementID = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Requirements[count].RequiredCount = TokenNumber;
				Token = GetToken();

				memset(this->m_QuestData[qType][qId].Requirements[count].RequirementItemInfo,0x00,12);
				
				this->m_QuestData[qType][qId].Requirements[count].RequirementItemInfo[0] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Requirements[count].RequirementItemInfo[1] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Requirements[count].RequirementItemInfo[2] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Requirements[count].RequirementItemInfo[3] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Requirements[count].RequirementItemInfo[4] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Requirements[count].RequirementItemInfo[5] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Requirements[count].RequirementItemInfo[6] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Requirements[count].RequirementItemInfo[7] = TokenNumber;
				count++;
			}
			else
			{
				break;
			}
		}
	}
	fclose(SMDFile);
	LogAdd("%s file load!", szFile);
	return;
	
}

void CSupportQuestSystem::LoadRewardFile(LPSTR szFile,int qType, int qId)
{

	SMDFile = fopen(szFile, "r");
	
	if ( SMDFile == NULL )
	{ 
		MsgBox("[SupportQuestSystem] Quest Rewards file Load Fail [%s]", szFile);
		return;
	}
	int Token;
	int type = -1;
	int count = 0;

    while ( true )
	{
	    Token = GetToken();

        if( Token == 2)
		{
            break;
		}

		type = TokenNumber;

		while ( true )
		{
		    if( type == 0 )
			{
			    Token = GetToken();

				if ( strcmp("end", TokenString ) == 0)
				{
					count = 0;
					break;
				}
				this->m_QuestData[qType][qId].Rewards[count].RewardType = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Rewards[count].RewardCount = TokenNumber;
				Token = GetToken();
				
			//	Token = GetToken();
			//	Token=GetToken();
				this->m_QuestData[qType][qId].Rewards[count].RewardItemInfo[0] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Rewards[count].RewardItemInfo[1] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Rewards[count].RewardItemInfo[2] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Rewards[count].RewardItemInfo[3] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Rewards[count].RewardItemInfo[4] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Rewards[count].RewardItemInfo[5] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Rewards[count].RewardItemInfo[6] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Rewards[count].RewardItemInfo[7] = TokenNumber;
				Token = GetToken();

				this->m_QuestData[qType][qId].Rewards[count].RewardItemInfo[8] = TokenNumber;
				count++;
			}
		}
	}
	fclose(SMDFile);
	LogAdd("%s file load!", szFile);
	return;

}	
void CSupportQuestSystem::LoadFile(LPSTR szFile)
{
	char RequirmentPath[MAX_PATH];
	char RewardPath[MAX_PATH];
	FILE* test;
	for(int i=0;i<20;i++)
	{
		for(int n=0;n<200;n++)
		{
			sprintf(RewardPath,"..\\data\\SupportQuest\\Rewards\\%d\\%d-%d.txt",i,i,n);
			sprintf(RequirmentPath,"..\\data\\SupportQuest\\Requirements\\%d\\%d-%d.txt",i,i,n);
			test = fopen(RewardPath, "r");
			if(test != NULL)
			{
				this->LoadRewardFile(RewardPath,i,n);
				this->LoadRequirementFile(RequirmentPath,i,n);

			}
		}
	}
	
	SMDFile = fopen(szFile, "r");

	if ( SMDFile == NULL )
	{ 
		MsgBox("[SupportQuestSystem] Quest file Load Fail [%s]", szFile);
		return;
	}

	int Token;
	int type = -1;
	int count = 0;
////	char RequirmentPath[MAX_PATH];
//	char RewardPath[MAX_PATH];
//	FILE* test;
    while ( true )
	{
			Token = GetToken();

			if( Token == 2)
			{
				break;
			}
			type = TokenNumber;
	for(int i=0;i<20;i++)
	{	


		while ( true )
		{	

				if( type == i )
				{
					Token = GetToken();

					if ( strcmp("end", TokenString ) == 0)
					{
						count = 0;
						break;
					}

					this->m_QuestData[i][count].NPCid = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].QuestType = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].QuestIndex = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].LevelMin = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].LevelMax = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].ReqCount = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].RewardCount = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].unknown = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].DWStart = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].DKStart = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].ELFStart = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].MGStart = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].DLStart = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].SumStart = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].RageStart = TokenNumber;

					Token = GetToken();
					this->m_QuestData[i][count].cancelId = TokenNumber;

					count++;
				}
				else
				{
					break;
				}
		}
		}
	}

	fclose(SMDFile);
	LogAdd("%s file load!", szFile);
	return;

}
void CSupportQuestSystem::SendListChar(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	BYTE SendBuf[0x2000];
	int lOfs,count;


	PWMSG_COUNT_CHAR pwCount;
	PMSG_QUESTLISTSENDCHAR pListCreate;

	count = 0;

	lOfs = sizeof(pwCount);
/*	pListCreate.indexH = HIBYTE(1);//lpObj->SupportQuestInfo.Type1Index);
	pListCreate.indexL = LOBYTE(1);//lpObj->SupportQuestInfo.Type1Index);
	pListCreate.typeH = HIBYTE(18);
	pListCreate.typeL = LOBYTE(18);	
	
	memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
		lOfs += sizeof(pListCreate);
	count++;*/
	if(lpObj->SupportQuestInfo.Type1Taken != 0 
		|| lpObj->SupportQuestInfo.Type2Taken != 0 
		|| lpObj->SupportQuestInfo.Type3Taken != 0
		|| lpObj->SupportQuestInfo.Type4Taken != 0
		|| lpObj->SupportQuestInfo.Type5Taken != 0
		|| lpObj->SupportQuestInfo.Type6Taken != 0
		|| lpObj->SupportQuestInfo.Type7Taken != 0
		|| lpObj->SupportQuestInfo.Type8Taken != 0
		|| lpObj->SupportQuestInfo.Type9Taken != 0
		|| lpObj->SupportQuestInfo.Type10Taken != 0
		|| lpObj->SupportQuestInfo.Type11Taken != 0
		|| lpObj->SupportQuestInfo.Type12Taken != 0
		|| lpObj->SupportQuestInfo.Type13Taken != 0
		|| lpObj->SupportQuestInfo.Type14Taken != 0
		|| lpObj->SupportQuestInfo.Type15Taken != 0
		|| lpObj->SupportQuestInfo.Type16Taken != 0
		|| lpObj->SupportQuestInfo.Type17Taken != 0
		|| lpObj->SupportQuestInfo.Type18Taken != 0
		|| lpObj->SupportQuestInfo.Type19Taken != 0
		|| lpObj->SupportQuestInfo.Type20Taken != 0)
	{
		//if quest type 1 taken
		/*if(lpObj->Level >= this->m_QuestData[0][lpObj->SupportQuestInfo.Type1Index].LevelMin
			&& lpObj->Level <= this->m_QuestData[0][lpObj->SupportQuestInfo.Type1Index].LevelMax
			&& lpObj->SupportQuestInfo.Type1Taken >= 1)
		{*/
		if(lpObj->SupportQuestInfo.Type1Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type1Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type1Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(1);
			pListCreate.typeL = LOBYTE(1);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type2Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type2Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type2Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(2);
			pListCreate.typeL = LOBYTE(2);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type3Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type3Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type3Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(3);
			pListCreate.typeL = LOBYTE(3);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type4Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type4Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type4Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(4);
			pListCreate.typeL = LOBYTE(4);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type5Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type5Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type5Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(5);
			pListCreate.typeL = LOBYTE(5);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type6Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type6Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type6Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(6);
			pListCreate.typeL = LOBYTE(6);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		
		}
		if(lpObj->SupportQuestInfo.Type7Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type7Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type7Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(7);
			pListCreate.typeL = LOBYTE(7);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type8Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type8Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type8Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(8);
			pListCreate.typeL = LOBYTE(8);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type9Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type9Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type9Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(9);
			pListCreate.typeL = LOBYTE(9);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type10Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type10Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type10Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(10);
			pListCreate.typeL = LOBYTE(10);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type11Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type11Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type11Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(11);
			pListCreate.typeL = LOBYTE(11);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type12Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type12Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type12Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(12);
			pListCreate.typeL = LOBYTE(12);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type13Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type13Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type13Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(13);
			pListCreate.typeL = LOBYTE(13);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type14Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type14Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type14Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(14);
			pListCreate.typeL = LOBYTE(14);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type15Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type15Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type15Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(15);
			pListCreate.typeL = LOBYTE(15);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type16Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type16Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type16Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(16);
			pListCreate.typeL = LOBYTE(16);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type17Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type17Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type17Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(17);
			pListCreate.typeL = LOBYTE(17);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type18Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type18Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type18Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(18);
			pListCreate.typeL = LOBYTE(18);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type19Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type19Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type19Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(19);
			pListCreate.typeL = LOBYTE(19);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}
		if(lpObj->SupportQuestInfo.Type20Taken > 0)
		{
			pListCreate.indexH = HIBYTE(lpObj->SupportQuestInfo.Type20Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(lpObj->SupportQuestInfo.Type20Index);//lpObj->SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(20);
			pListCreate.typeL = LOBYTE(20);	
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs += sizeof(pListCreate);
			count++;
		}

	}
	pwCount.h.headcode = 0xF6;	

	pwCount.h.c = 0xC1;
	pwCount.h.size = lOfs;
	pwCount.h.subcode = 0x1A;
	pwCount.count = count;
	memcpy(SendBuf,&pwCount,sizeof(pwCount));

	DataSend(aIndex,SendBuf,lOfs);

}
void CSupportQuestSystem::SendListNpc(int aIndex)
{

	LPOBJ lpObj = &gObj[aIndex];
	BYTE SendBuf[0x2000];
	PWMSG_COUNTQ pwCount;
	PMSG_QUESTLISTSEND pListCreate ={0};

	int lOfs, count = 0;

	lOfs = sizeof(pwCount);
	if(gObj[lpObj->TargetNumber].Class == 257)
	{
		/*if(lpObj->Level >= m_QuestData[1][gObj[aIndex].SupportQuestInfo.Type1Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type1Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type1Index);
			pListCreate.typeH = HIBYTE(1);
			pListCreate.typeL = LOBYTE(1);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}*/

		if(lpObj->Level >= m_QuestData[2][gObj[aIndex].SupportQuestInfo.Type2Index].LevelMin && lpObj->SupportQuestInfo.Type2Index != -1) // chaos castle
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type2Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type2Index);
			pListCreate.typeH = HIBYTE(2);
			pListCreate.typeL = LOBYTE(2);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}

		if(lpObj->Level >= m_QuestData[3][gObj[aIndex].SupportQuestInfo.Type3Index].LevelMin && lpObj->SupportQuestInfo.Type3Index != -1) // Blood Castle
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type3Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type3Index);
			pListCreate.typeH = HIBYTE(3);
			pListCreate.typeL = LOBYTE(3);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}

		if(lpObj->Level >= m_QuestData[4][gObj[aIndex].SupportQuestInfo.Type4Index].LevelMin && lpObj->SupportQuestInfo.Type4Index != -1) // Devil Square
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type4Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type4Index);
			pListCreate.typeH = HIBYTE(4);
			pListCreate.typeL = LOBYTE(4);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}

	if(lpObj->Level >= m_QuestData[5][gObj[aIndex].SupportQuestInfo.Type5Index].LevelMin && lpObj->SupportQuestInfo.Type5Index != -1) // Illusion
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type5Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type5Index);
			pListCreate.typeH = HIBYTE(5);
			pListCreate.typeL = LOBYTE(5);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}/*
		if(lpObj->Level >= m_QuestData[6][gObj[aIndex].SupportQuestInfo.Type6Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type6Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type6Index);
			pListCreate.typeH = HIBYTE(6);
			pListCreate.typeL = LOBYTE(6);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}/*
		if(lpObj->Level >= m_QuestData[7][gObj[aIndex].SupportQuestInfo.Type7Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type7Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type7Index);
			pListCreate.typeH = HIBYTE(7);
			pListCreate.typeL = LOBYTE(7);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
		if(lpObj->Level >= m_QuestData[8][gObj[aIndex].SupportQuestInfo.Type8Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type8Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type8Index);
			pListCreate.typeH = HIBYTE(8);
			pListCreate.typeL = LOBYTE(8);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
		if(lpObj->Level >= m_QuestData[9][gObj[aIndex].SupportQuestInfo.Type9Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type9Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type9Index);
			pListCreate.typeH = HIBYTE(9);
			pListCreate.typeL = LOBYTE(9);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
		if(lpObj->Level >= m_QuestData[10][gObj[aIndex].SupportQuestInfo.Type10Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type10Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type10Index);
			pListCreate.typeH = HIBYTE(10);
			pListCreate.typeL = LOBYTE(10);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}*/
/*		if(lpObj->Level >= m_QuestData[11][gObj[aIndex].SupportQuestInfo.Type11Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type11Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type11Index);
			pListCreate.typeH = HIBYTE(11);
			pListCreate.typeL = LOBYTE(11);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
		if(lpObj->Level >= m_QuestData[12][gObj[aIndex].SupportQuestInfo.Type12Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type12Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type12Index);
			pListCreate.typeH = HIBYTE(12);
			pListCreate.typeL = LOBYTE(12);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
		if(lpObj->Level >= m_QuestData[13][gObj[aIndex].SupportQuestInfo.Type13Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type13Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type13Index);
			pListCreate.typeH = HIBYTE(13);
			pListCreate.typeL = LOBYTE(13);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
		if(lpObj->Level >= m_QuestData[14][gObj[aIndex].SupportQuestInfo.Type14Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type14Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type14Index);
			pListCreate.typeH = HIBYTE(14);
			pListCreate.typeL = LOBYTE(14);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}*/
		if(lpObj->Level >= m_QuestData[15][gObj[aIndex].SupportQuestInfo.Type15Index].LevelMin && lpObj->SupportQuestInfo.Type15Index != -1)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type15Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type15Index);
			pListCreate.typeH = HIBYTE(15);
			pListCreate.typeL = LOBYTE(15);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
		/*if(lpObj->Level >= m_QuestData[16][gObj[aIndex].SupportQuestInfo.Type16Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type16Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type16Index);
			pListCreate.typeH = HIBYTE(16);
			pListCreate.typeL = LOBYTE(16);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
		if(lpObj->Level >= m_QuestData[17][gObj[aIndex].SupportQuestInfo.Type17Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type17Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type17Index);
			pListCreate.typeH = HIBYTE(17);
			pListCreate.typeL = LOBYTE(17);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}*/
		if(lpObj->Level >= m_QuestData[18][gObj[aIndex].SupportQuestInfo.Type18Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type18Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type18Index);
			pListCreate.typeH = HIBYTE(18);
			pListCreate.typeL = LOBYTE(18);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
/*		if(lpObj->Level >= m_QuestData[19][gObj[aIndex].SupportQuestInfo.Type19Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type19Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type19Index);
			pListCreate.typeH = HIBYTE(19);
			pListCreate.typeL = LOBYTE(19);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}*/
		/*if(lpObj->Level >= m_QuestData[20][gObj[aIndex].SupportQuestInfo.Type20Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type20Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type20Index);
			pListCreate.typeH = HIBYTE(20);
			pListCreate.typeL = LOBYTE(20);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}*/
	}
	else if(gObj[lpObj->TargetNumber].Class == 544 && lpObj->GensNumber == 2)
	{
		if(lpObj->Level >= m_QuestData[17][lpObj->SupportQuestInfo.Type17Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type17Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type17Index);
			pListCreate.typeH = HIBYTE(17);
			pListCreate.typeL = LOBYTE(17);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
	}
	else if (gObj[lpObj->TargetNumber].Class == 543 && lpObj->GensNumber == 1)
	{
		if(lpObj->Level >= m_QuestData[16][lpObj->SupportQuestInfo.Type16Index].LevelMin)
		{
			pListCreate.indexH = HIBYTE(gObj[aIndex].SupportQuestInfo.Type16Index);
			pListCreate.indexL = LOBYTE(gObj[aIndex].SupportQuestInfo.Type16Index);
			pListCreate.typeH = HIBYTE(16);
			pListCreate.typeL = LOBYTE(16);
			memcpy(&SendBuf[lOfs],&pListCreate,sizeof(pListCreate));
			lOfs+=sizeof(pListCreate);
			count +=1;
		}
	}



	pwCount.h.c = 0xC1;
	pwCount.h.size = lOfs;
	pwCount.h.headcode = 0xF6;	
	pwCount.h.subcode = 0x0A;
	pwCount.a = 1;
	pwCount.b = 1;
	pwCount.c = count;
	pwCount.d = 0;

	memcpy(SendBuf,&pwCount,sizeof(pwCount));

	DataSend(aIndex,SendBuf,lOfs);




}
void CSupportQuestSystem::Accept(int aIndex, LPBYTE aRecv)
{
	BYTE QuestIndex;
	BYTE QuestType;
	int starttype;
	QuestIndex = (aRecv[4] + aRecv[5] * 256);
	QuestType = (aRecv[6] + aRecv[7] * 256);
	int qt = QuestType;
	//rewritelater

	switch(gObj[aIndex].Class)
	{
	case CLASS_WIZARD:
		starttype = m_QuestData[qt][QuestIndex].DWStart;
		break;
	case CLASS_DARKLORD:
		starttype = m_QuestData[qt][QuestIndex].DLStart;
		break;
	case CLASS_ELF:
		starttype = m_QuestData[qt][QuestIndex].ELFStart;
		break;
	case CLASS_MAGUMSA:
		starttype = m_QuestData[qt][QuestIndex].MGStart;
		break;
	case CLASS_KNIGHT:
		starttype = m_QuestData[qt][QuestIndex].DKStart;
		break;
	case CLASS_SUMMONER:
		starttype = m_QuestData[qt][QuestIndex].SumStart;
		break;
	case CLASS_RAGEFIGHTER:
		starttype = m_QuestData[qt][QuestIndex].RageStart;
		break;
	}
	
	this->SendRequirments(aIndex,aRecv,false,QuestIndex);
}
void CSupportQuestSystem::MonsterMng(int aIndex, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTargetIndex];

	if(lpTarget->Class == m_QuestData[1][lpObj->SupportQuestInfo.Type1Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type1Taken++;
	}
	if(lpTarget->Class == m_QuestData[2][lpObj->SupportQuestInfo.Type2Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type2Taken++;
	}
	if(lpTarget->Class == m_QuestData[3][lpObj->SupportQuestInfo.Type3Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type3Taken++;
	}
	if(lpTarget->Class == m_QuestData[4][lpObj->SupportQuestInfo.Type4Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type4Taken++;
	}
	if(lpTarget->Class == m_QuestData[5][lpObj->SupportQuestInfo.Type5Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type5Taken++;
	}
	if(lpTarget->Class == m_QuestData[6][lpObj->SupportQuestInfo.Type6Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type6Taken++;
	}
	if(lpTarget->Class == m_QuestData[7][lpObj->SupportQuestInfo.Type7Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type7Taken++;
	}
	if(lpTarget->Class == m_QuestData[8][lpObj->SupportQuestInfo.Type8Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type8Taken++;
	}
	if(lpTarget->Class == m_QuestData[9][lpObj->SupportQuestInfo.Type9Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type9Taken++;
	}
	if(lpTarget->Class == m_QuestData[10][lpObj->SupportQuestInfo.Type10Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type10Taken++;
	}
	if(lpTarget->Class == m_QuestData[11][lpObj->SupportQuestInfo.Type11Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type11Taken++;
	}
	if(lpTarget->Class == m_QuestData[12][lpObj->SupportQuestInfo.Type12Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type12Taken++;
	}
	if(lpTarget->Class == m_QuestData[13][lpObj->SupportQuestInfo.Type13Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type13Taken++;
	}
	if(lpTarget->Class == m_QuestData[14][lpObj->SupportQuestInfo.Type14Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type14Taken++;
	}
	if(lpTarget->Class == m_QuestData[15][lpObj->SupportQuestInfo.Type15Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type15Taken++;
	}
	if(lpTarget->Class == m_QuestData[15][lpObj->SupportQuestInfo.Type15Index].Requirements[1].RequirementID)
	{
		lpObj->SupportQuestInfo.Type15Count++;
	}
	if(lpTarget->Class == m_QuestData[16][lpObj->SupportQuestInfo.Type16Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type16Taken++;
	}
	if(lpTarget->Class == m_QuestData[17][lpObj->SupportQuestInfo.Type17Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type17Taken++;
	}
	if(lpTarget->Class == m_QuestData[18][lpObj->SupportQuestInfo.Type18Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type18Taken++;
	}
	if(lpTarget->Class == m_QuestData[19][lpObj->SupportQuestInfo.Type19Index].Requirements[0].RequirementID)
	{
		lpObj->SupportQuestInfo.Type19Taken++;
	}
}

void CSupportQuestSystem::Reward(int aIndex, LPBYTE aRecv)
{
	int QuestIndex;
	int QuestType;
	QuestIndex = (aRecv[4] + aRecv[5] * 256);
	QuestType = (aRecv[6] + aRecv[7] * 256);
	int qt = QuestType;
	bool validquest = false;
	if(m_QuestData[QuestType][QuestIndex].cancelId != -1)

	switch(QuestType)
	{
		case 1:
			{
				if(gObj[aIndex].SupportQuestInfo.Type1Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{

					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type1Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type1Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type1Index = -1;
					}

				}
			}
			break;
		case 2:
			{
				if(gObj[aIndex].SupportQuestInfo.Type2Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type2Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type2Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type2Index = -1;
					}
				}
			}
			break;
		case 3:
			{
				if(gObj[aIndex].SupportQuestInfo.Type3Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type3Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type3Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type3Index = -1;
					}
				}
			}
			break;
		case 4:
			{
				if(gObj[aIndex].SupportQuestInfo.Type4Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type4Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type4Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type4Index = -1;
					}
				}
			}
			break;
		case 5:
			{
				if(gObj[aIndex].SupportQuestInfo.Type5Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type5Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type5Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type5Index = -1;
					}
				}
			}
			break;
		case 6:
			{
				if(gObj[aIndex].SupportQuestInfo.Type6Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					gObj[aIndex].SupportQuestInfo.Type6Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
					gObj[aIndex].SupportQuestInfo.Type6Taken = 0;
				}
			}
			break;
		case 7:
			{
				if(gObj[aIndex].SupportQuestInfo.Type7Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					gObj[aIndex].SupportQuestInfo.Type7Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
					gObj[aIndex].SupportQuestInfo.Type7Taken = 0;
				}
			}
			break;
		case 8:
			{
				if(gObj[aIndex].SupportQuestInfo.Type8Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					gObj[aIndex].SupportQuestInfo.Type8Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
					gObj[aIndex].SupportQuestInfo.Type8Taken = 0;
				}
			}
			break;
		case 9:
			{
				if(gObj[aIndex].SupportQuestInfo.Type9Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					gObj[aIndex].SupportQuestInfo.Type9Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
					gObj[aIndex].SupportQuestInfo.Type9Taken = 0;
				}
			}
			break;
		case 10:
			{
				if(gObj[aIndex].SupportQuestInfo.Type10Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					gObj[aIndex].SupportQuestInfo.Type10Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
					gObj[aIndex].SupportQuestInfo.Type10Taken = 0;
				}
			}
			break;
		case 11:
			{
				if(gObj[aIndex].SupportQuestInfo.Type11Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					gObj[aIndex].SupportQuestInfo.Type11Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
					gObj[aIndex].SupportQuestInfo.Type11Taken = 0;
				}
			}
			break;
		case 12:
			{
				if(gObj[aIndex].SupportQuestInfo.Type12Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					gObj[aIndex].SupportQuestInfo.Type12Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
					gObj[aIndex].SupportQuestInfo.Type12Taken = 0;
				}
			}
			break;
		case 13:
			{
				if(gObj[aIndex].SupportQuestInfo.Type13Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					gObj[aIndex].SupportQuestInfo.Type13Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
					gObj[aIndex].SupportQuestInfo.Type13Taken = 0;
				}
			}
			break;
		case 14:
			{
				if(gObj[aIndex].SupportQuestInfo.Type14Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					gObj[aIndex].SupportQuestInfo.Type14Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
					gObj[aIndex].SupportQuestInfo.Type14Taken = 0;
				}
			}
			break;
		case 15:
			{
				if(gObj[aIndex].SupportQuestInfo.Type15Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount )
				{
					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type15Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type15Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type15Index = -1;
					}
				}
			}
			break;
		case 16:
			{
				if(gObj[aIndex].SupportQuestInfo.Type16Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type16Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type16Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type16Index = -1;
					}
				}
			}
			break;
		case 17:
			{
				if(gObj[aIndex].SupportQuestInfo.Type17Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type17Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type17Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type17Index = -1;
					}
				}
			}
			break;
		case 18:
			{
				if(gObj[aIndex].SupportQuestInfo.Type18Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type18Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type18Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type18Index = -1;
					}
				}
			}
			break;
		case 19:
			{
				if(gObj[aIndex].SupportQuestInfo.Type19Taken-1 >= m_QuestData[QuestType][QuestIndex].Requirements[0].RequiredCount)
				{
					validquest = true;
					if(m_QuestData[QuestType][QuestIndex].cancelId != -1)
					{
						gObj[aIndex].SupportQuestInfo.Type19Index = m_QuestData[QuestType][QuestIndex].cancelId+1;
						gObj[aIndex].SupportQuestInfo.Type19Taken = 0;
					}
					else
					{
						gObj[aIndex].SupportQuestInfo.Type15Index = -1;
					}
				}
			}
			break;
	}
	if(validquest)
	{
		for(int i=0;i<m_QuestData[QuestType][QuestIndex].RewardCount;i++)
		{
			switch(m_QuestData[QuestType][QuestIndex].Rewards[i].RewardType)
			{
			case 1:
				{
					gObj[aIndex].Experience += m_QuestData[QuestType][QuestIndex].Rewards[i].RewardCount;
					GCKillPlayerExpSend(aIndex,0,m_QuestData[QuestType][QuestIndex].Rewards[i].RewardCount,0,0);
					gObjLevelUp(&gObj[aIndex],m_QuestData[QuestType][QuestIndex].Rewards[i].RewardCount,0,0);
				}
				break;
			case 2:
				{
					gObj[aIndex].Money +=  m_QuestData[QuestType][QuestIndex].Rewards[i].RewardCount;
					GCMoneySend(aIndex,gObj[aIndex].Money);
				}
				break;
			case 4:
				{
					CItem prize;
					prize.m_Type = ITEMGET(m_QuestData[QuestType][QuestIndex].Rewards[i].RewardItemInfo[0],m_QuestData[QuestType][QuestIndex].Rewards[i].RewardItemInfo[1]);
					prize.m_Level = m_QuestData[QuestType][QuestIndex].Rewards[i].RewardItemInfo[2];
					prize.m_Durability = m_QuestData[QuestType][QuestIndex].Rewards[i].RewardItemInfo[3];
					prize.m_Option1 = m_QuestData[QuestType][QuestIndex].Rewards[i].RewardItemInfo[4];
					prize.m_Option2 =  m_QuestData[QuestType][QuestIndex].Rewards[i].RewardItemInfo[5];
					prize.m_Option3 =  m_QuestData[QuestType][QuestIndex].Rewards[i].RewardItemInfo[6];
					prize.m_NewOption =  m_QuestData[QuestType][QuestIndex].Rewards[i].RewardItemInfo[7];
					prize.m_ItemOptionEx =  m_QuestData[QuestType][QuestIndex].Rewards[i].RewardItemInfo[8];
					//priz
					//ItemByteConvert(pMsg.Prizes[i].RewardItemInfo,prize);
					for(int n=0;n<m_QuestData[QuestType][QuestIndex].Rewards[i].RewardCount;n++)
					{
						ItemSerialCreateSend(aIndex,235,gObj[aIndex].X,gObj[aIndex].Y,prize.m_Type,prize.m_Level,prize.m_Durability,prize.m_Option1,prize.m_Option2,prize.m_Option3,aIndex,prize.m_NewOption,prize.m_ItemOptionEx);
					}
				}
			case 16:
				{
					gObj[aIndex].GensExp +=m_QuestData[QuestType][QuestIndex].Rewards[i].RewardCount ;
					PvPGens.SendInfo(&gObj[aIndex]);
				}
				break;
			}
		}
	}
	else
	{
		LogAddC(2,"[%s][%s] Quest Hack attempt",gObj[aIndex].AccountID,gObj[aIndex].Name);
		return;
	}

	LogAddTD("[%s][%s] Finish Quest Index %d next index %d",gObj[aIndex].AccountID,gObj[aIndex].Name,QuestIndex,m_QuestData[QuestType][QuestIndex].cancelId+1);
	//this->SendListNpc(aIndex);
	this->SendListChar(aIndex);
	 PMSG_QUEST_FINISH_ANS pMsg;
	 pMsg.h.c = 0xC1;
	 pMsg.h.headcode = 0xF6;
	 pMsg.h.size = sizeof(pMsg);
	 pMsg.h.subcode = 0x0D;
	 pMsg.QuestAccept = QuestIndex;
	 pMsg.QuestGroup = qt;
	 pMsg.Result = 1;
	 DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
	 return;
}
void CSupportQuestSystem::SendRequirments(int aIndex, LPBYTE aRecv, bool ForCharacter, short questid /*for npc*/)
{

	int QuestIndex;
	int QuestType;
	
	QuestIndex = (aRecv[4] + aRecv[5] * 256);
	QuestType = (aRecv[6] + aRecv[7] * 256);
	int qType = QuestType;
	PMSG_QUEST_DETAIL pMsg = {0};

	pMsg.h.c = 0xC1;
	pMsg.h.size = 0xF1;
	pMsg.h.headcode = 0xF6;
	pMsg.h.subcode = 0x0C;
	if(ForCharacter) pMsg.h.subcode = 0x1B;
	pMsg.QuestGroup = qType;// this->m_QuestData[QuestType][QuestIndex].QuestType;
	pMsg.QuestID = questid;
	pMsg.NeedsCount = m_QuestData[QuestType][questid].ReqCount;
	pMsg.PrizeCount = m_QuestData[QuestType][questid].RewardCount;
	for(int i=0;i<m_QuestData[QuestType][questid].ReqCount;i++)
	{
		pMsg.Needs[i].RequirementID = this->m_QuestData[QuestType][questid].Requirements[i].RequirementID;
		pMsg.Needs[i].RequiredCount = this->m_QuestData[QuestType][questid].Requirements[i].RequiredCount;
		pMsg.Needs[i].RequirementType = this->m_QuestData[QuestType][questid].Requirements[i].RequirementType;
		if(i == 0)
		{
			if(pMsg.Needs[i].RequirementType == 1)
			{
				switch(QuestType)
				{
					case 1:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type1Taken-1;
						break;
					case 2:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type2Taken-1;
						break;
					case 3:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type3Taken-1;
						break;
					case 4:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type4Taken-1;
						break;
					case 5:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type5Taken-1;
						break;
					case 6:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type6Taken-1;
						break;
					case 7:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type7Taken-1;
						break;
					case 8:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type8Taken-1;
						break;
					case 9:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type9Taken-1;
						break;
					case 10:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type10Taken-1;
						break;
					case 11:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type11Taken-1;
						break;
					case 12:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type12Taken-1;
						break;
					case 13:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type13Taken-1;
						break;
					case 14:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type14Taken-1;
						break;
					case 15: // because this type needs 2 monster types to be killed and i dont want to rewrite all xD
						{
							pMsg.Needs[0].Count = gObj[aIndex].SupportQuestInfo.Type15Taken-1;
							pMsg.Needs[1].Count = gObj[aIndex].SupportQuestInfo.Type15Count;
						}
						break;
					case 16:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type16Taken-1;
						break;
					case 17:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type17Taken-1;
						break;
					case 18:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type18Taken-1;
						break;
					case 19:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type19Taken-1;
						break;
					case 20:
						pMsg.Needs[i].Count = gObj[aIndex].SupportQuestInfo.Type20Taken-1;
						break;
				}
				 //-1 cuz storing info
			}

			if(pMsg.Needs[i].RequirementType == 4)
			{
				pMsg.Needs[i].Count = gObjGetItemCountInIventory(aIndex,ITEMGET(m_QuestData[QuestType][questid].Requirements[i].RequirementItemInfo[0],m_QuestData[QuestType][QuestIndex].Requirements[i].RequirementItemInfo[1]));//gObj[aIndex].SupportQuestInfo.Type1Taken-1; //-1 cuz storing info for start in same place
			}

		//	if(pMsg.Needs[i].RequirementType == 
		}
	}
	
	for(int i=0;i<m_QuestData[QuestType][questid].RewardCount;i++)
	{
		pMsg.Prizes[i].RewardType = this->m_QuestData[QuestType][questid].Rewards[i].RewardType;

		if(pMsg.Prizes[i].RewardType == 1)
		{
			pMsg.Prizes[i].RewardID = this->m_QuestData[QuestType][questid].Rewards[i].RewardID;
			pMsg.Prizes[i].RewardCount = this->m_QuestData[QuestType][questid].Rewards[i].RewardCount;
		}
		else if(pMsg.Prizes[i].RewardType == 2)
		{
			pMsg.Prizes[i].RewardID = this->m_QuestData[QuestType][questid].Rewards[i].RewardID;
			pMsg.Prizes[i].RewardCount = this->m_QuestData[QuestType][questid].Rewards[i].RewardCount;
		}
		else if(pMsg.Prizes[i].RewardType == 4)
		{
			CItem prize;
			prize.m_Type =ITEMGET(m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[0],m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[1]);
			prize.m_Level = m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[2];
			prize.m_Durability = m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[3];
			prize.m_Option1 = m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[4];
			prize.m_Option2 =  m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[5];
			prize.m_Option3 =  m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[6];
			prize.m_NewOption =  m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[7];
			prize.m_ItemOptionEx =  m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[8];
			//priz
			ItemByteConvert(pMsg.Prizes[i].RewardItemInfo,prize);
			pMsg.Prizes[i].RewardID = prize.m_Type;//12*512+15;//ITEMGET(m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[0],m_QuestData[QuestType][questid].Rewards[i].RewardItemInfo[1]);
			pMsg.Prizes[i].RewardCount = m_QuestData[QuestType][questid].Rewards[i].RewardCount;
		}
		else if(pMsg.Prizes[i].RewardType == 16)
		{
			pMsg.Prizes[i].RewardCount = m_QuestData[QuestType][questid].Rewards[i].RewardCount;

		}
	}
	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);



}

void CSupportQuestSystem::Continue(int aIndex, LPBYTE aRecv)
{

	int QuestIndex;
	int QuestType;
	bool AcceptQuest = false;
		QuestIndex = (aRecv[4] + aRecv[5] * 256);
		QuestType = (aRecv[6] + aRecv[7] * 256);
		int starttype;
		int qt = QuestType;
		//rewritelater
		/*switch(qt)
		{
		case 18:
			qt = 0;
			break;
		}*/
		switch(gObj[aIndex].Class)
		{
		case CLASS_WIZARD:
			starttype = m_QuestData[qt][QuestIndex].DWStart;
			break;
		case CLASS_DARKLORD:
			starttype = m_QuestData[qt][QuestIndex].DLStart;
			break;
		case CLASS_ELF:
			starttype = m_QuestData[qt][QuestIndex].ELFStart;
			break;
		case CLASS_MAGUMSA:
			starttype = m_QuestData[qt][QuestIndex].MGStart;
			break;
		case CLASS_KNIGHT:
			starttype = m_QuestData[qt][QuestIndex].DKStart;
			break;
		case CLASS_SUMMONER:
			starttype = m_QuestData[qt][QuestIndex].SumStart;
			break;
		case CLASS_RAGEFIGHTER:
			starttype = m_QuestData[qt][QuestIndex].RageStart;
			break;
		}
		
		switch(QuestType)
		{
			case 1:
				if(gObj[aIndex].SupportQuestInfo.Type1Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type1Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type1Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 2:
				if(gObj[aIndex].SupportQuestInfo.Type2Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type2Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type2Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 3:
				if(gObj[aIndex].SupportQuestInfo.Type3Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type3Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type3Taken = 1;
					AcceptQuest = true;
				}			
				break;
			case 4:
				if(gObj[aIndex].SupportQuestInfo.Type4Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type4Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type4Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 5:
				if(gObj[aIndex].SupportQuestInfo.Type5Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type5Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type5Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 6:
				if(gObj[aIndex].SupportQuestInfo.Type6Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type6Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type6Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 7:
				if(gObj[aIndex].SupportQuestInfo.Type7Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type7Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type7Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 8:
				if(gObj[aIndex].SupportQuestInfo.Type8Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type8Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type8Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 9:
				if(gObj[aIndex].SupportQuestInfo.Type9Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type9Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type9Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 10:
				if(gObj[aIndex].SupportQuestInfo.Type10Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type10Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type10Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 11:
				if(gObj[aIndex].SupportQuestInfo.Type11Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type11Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type11Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 12:
				if(gObj[aIndex].SupportQuestInfo.Type12Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type12Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type12Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 13:
				if(gObj[aIndex].SupportQuestInfo.Type13Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type13Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type13Taken = 1;
					AcceptQuest = true;
				}
				break;

			case 14:
				if(gObj[aIndex].SupportQuestInfo.Type14Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type14Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type14Taken = 1;
					AcceptQuest = true;
				}
				break;


			case 15:
				if(gObj[aIndex].SupportQuestInfo.Type15Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type15Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type15Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 16:
				if(gObj[aIndex].SupportQuestInfo.Type16Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type16Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type16Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 17:
				if(gObj[aIndex].SupportQuestInfo.Type17Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type17Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type17Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 18:
				if(gObj[aIndex].SupportQuestInfo.Type18Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type18Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type18Taken = 1;
					AcceptQuest = true;
				}
				break;
			case 19:
				if(gObj[aIndex].SupportQuestInfo.Type19Taken == 0 )
				{
					gObj[aIndex].SupportQuestInfo.Type19Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type19Taken = 1;
					AcceptQuest = true;
				}
				break;
		}
		if(AcceptQuest == true)
		{
			PMSG_SENDQUESTINDEX pMsg;
			pMsg.h.c = 0xC1;
			pMsg.h.size = 0x0B;
			pMsg.h.headcode = 0xF6;
			pMsg.h.subcode = 0x0B;
			pMsg.indexL = LOBYTE(starttype);
			pMsg.indexH = HIBYTE(starttype);
			pMsg.typeL = LOBYTE(QuestType);
			pMsg.typeH = HIBYTE(QuestType);

			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

			/*switch(QuestType)
			{
			case 18:
				{
					gObj[aIndex].SupportQuestInfo.Type1Index = starttype;
					gObj[aIndex].SupportQuestInfo.Type1Taken = 1;
				}
				break;
			}*/
		}
	
	this->SendRequirments(aIndex,aRecv,false,starttype);
	/*	PMSG_SENDQUESTCONT pMsg;
		pMsg.h.c = 0xC1;
		pMsg.h.size = 0x0B;
		pMsg.h.headcode = 0xF6;
		pMsg.h.subcode = 0x0B;
		pMsg.indexL = QuestIndex;//LOBYTE(this->m_QuestData[0][QuestIndex].QuestIndex);
		pMsg.indexH = QuestIndex;// HIBYTE(this->m_QuestData[0][QuestIndex].QuestIndex);
		pMsg.typeL = LOBYTE(this->m_QuestData[0][QuestIndex].QuestType);
		pMsg.typeH = HIBYTE(this->m_QuestData[0][QuestIndex].QuestType);
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);*/
}