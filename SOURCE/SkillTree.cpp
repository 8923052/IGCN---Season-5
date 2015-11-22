// ################################################
// ### SkillTree System							###
// ### Coded By [UCD]drakelv & [UCD]leo123		###
// ### Version : 0.1							###
// ################################################

#include "stdafx.h" 
#include "MagicDamage.h"
#include "SkillTree.h"
#include "user.h"
#include "..\include\prodef.h"
#include "..\include\readscript.h"
#include "..\common\WzMemScript.h"

cObjSkillTree gSkillTree;

struct PMSG_SKILLTREESEND
{
	PBMSG_HEAD2	m_Head;
	WORD		m_uLevel;
	BYTE UNK6;
	BYTE UNK7;
	WORD		m_uPoint;
	BYTE UNK10;
	BYTE UNK11;
	WORD Life;
	WORD Mana;
	WORD Shield;
	WORD Stamina;
};


cObjSkillTree::cObjSkillTree()
{
	return ;
}


cObjSkillTree::~cObjSkillTree()
{
	return;
}

void cObjSkillTree::Init()
{
	for ( int n=0; n< MAX_SKILL;n++)
	{
		this->m_Damage[n] = -1;
	}
}

void cObjSkillTree::MasterLevelUpSend(LPOBJ lpObj)
{
	PMSG_SKILLTREESEND pMsg = {0};
	pMsg.m_Head.set((LPBYTE)&pMsg, 0xF3,0x51,sizeof(pMsg));
	pMsg.m_uLevel = lpObj->m_uMasterLevel;
	pMsg.m_uPoint = lpObj->m_uMasterPoints;
	pMsg.UNK10 = 200; // ??
	
	DataSend(lpObj->m_Index, (unsigned char*)&pMsg, sizeof(pMsg));

}

void cObjSkillTree::LoadData(unsigned char * FileName)
{
	

}

void cObjSkillTree::AddPoint(LPOBJ lpObj, DWORD SkillID)
{
	MsgOutput(lpObj->m_Index,"USE OF COMMAND ADD ML SKILL");
	int Pos = gObjMagicAdd(lpObj,315,2);
	GCMagicListOneSend(lpObj->m_Index,Pos,315,2,0,0);
}
struct PMSG_MLMAGICLISTONESEND
{

};
void cObjSkillTree::MasterLevelMagicListSend(int aIndex, char Pos, unsigned char type, unsigned char level, unsigned char skill, BYTE btListType)
{

}
void cObjSkillTree::SendMasteringInfo(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	PMSG_SKILLTREESEND pMsg = {0};
	pMsg.m_Head.set((LPBYTE)&pMsg, 0xF3,0x51,sizeof(pMsg));
	pMsg.m_uLevel = lpObj->m_uMasterLevel;// wait
	pMsg.m_uPoint = lpObj->m_uMasterPoints;

	DataSend(aIndex, (unsigned char*)&pMsg, sizeof(pMsg));

}
