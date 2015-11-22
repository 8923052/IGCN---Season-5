#include "stdafx.h"
#include "BuffManager.h"
#include "..\include\readscript.h"
#include "logproc.h"

CBuffManage g_BuffManager;


void CBuffManage::Init()
{
	for(int i=0;i<MAX_BUFF;i++)
	{
		this->m_BuffData[i].Index =-1;
		this->m_BuffData[i].ClearType =-1;
		memset((PBYTE)this->m_BuffData[i].Info,0x00,sizeof(this->m_BuffData[i].Info));
		memset((PBYTE)this->m_BuffData[i].Name,0x00,sizeof(this->m_BuffData[i].Name));
		this->m_BuffData[i].ItemCat = -1;
		this->m_BuffData[i].ItemIndex = -1;
		this->m_BuffData[i].Type = -1;
		this->m_BuffData[i].Unk1 = -1;
		this->m_BuffData[i].Viewport = -1;
	}
}

void CBuffManage::LoadFile(char *file)
{
	this->Init();
	
	 if ( (SMDFile = fopen(file, "r")) == NULL )
	 {
	    MessageBoxA(0,"CBuffManage::LoadFile() error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	 }

	SMDToken Token;
	BYTE Index;
	BYTE Viewport;
	BYTE ItemCat;
	BYTE ItemIndex;
	char Name[1024];
	BYTE Type;
	BYTE Unk1;
	BYTE ClearType;
	char Info[1024];
	int iIndex;

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
				Index = TokenNumber;
				Token = GetToken();	Viewport = TokenNumber;
				Token = GetToken();	ItemCat = TokenNumber;
				Token = GetToken(); ItemIndex = TokenNumber;
			    Token = GetToken(); memcpy(Name,TokenString,sizeof(Name));
				Token = GetToken();	Type = TokenNumber;
				Token = GetToken();	Unk1 = TokenNumber;
				Token = GetToken();	ClearType = TokenNumber;
				Token = GetToken(); memcpy(Info,TokenString,sizeof(Info));

				this->Insert(Index,Viewport,ItemCat,ItemIndex,Name,Type,Unk1,ClearType,Info);
			 }
		 }
	   }
	LogAddTD("[BuffManager] BuffEffect.txt has been loaded");
}

void CBuffManage::Insert(BYTE Index, BYTE Viewport, BYTE ItemCat, BYTE ItemIndex, char *Name, BYTE Type, BYTE Unk1, BYTE ClearType, char *info)
{
	this->m_BuffData[Index].Index = Index;
	this->m_BuffData[Index].ClearType = ClearType;
	this->m_BuffData[Index].Viewport = Viewport;
	this->m_BuffData[Index].Type = Type;
	this->m_BuffData[Index].ItemCat = ItemCat;
	this->m_BuffData[Index].ItemIndex = ItemIndex;
	strcpy(this->m_BuffData[Index].Name,Name);
	strcpy(this->m_BuffData[Index].Info,info);
	this->m_BuffData[Index].Unk1 = Unk1;
}