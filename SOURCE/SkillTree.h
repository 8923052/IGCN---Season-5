////////////////////////////////////////
// Skill Tree Code
////////////////////////////////////////
#include "user.h"
#ifndef SKILLTREE_H
#define SKILLTREE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXMASTERLEVEL 50
#define MAXSKILLLEVEL 5

class cObjSkillTree
{

public:

	cObjSkillTree();
	virtual ~cObjSkillTree();
	void	Init();
	void	LoadData(unsigned char * FileName);
	void	SendMasteringInfo(int aIndex);
	void	MasterLevelUpSend(LPOBJ lpObj);
	void	AddPoint(LPOBJ lpObj, DWORD SkillID);
	void	MasterLevelMagicListSend(int aIndex, char Pos, unsigned char type, unsigned char level, unsigned char skill, BYTE btListType);

private:

	int m_Damage[MAX_SKILL];	// 4
	char m_Name[MAX_SKILL][50];	// 404
	unsigned char m_rLevel[MAX_SKILL];	// 3604
	unsigned short m_Mana[MAX_SKILL];	// 3704
	unsigned char m_Distance[MAX_SKILL];	// 3904
	int m_RequireEnergy[MAX_SKILL];	// 3A04
	unsigned char m_RequireClass[MAX_SKILL][MAX_TYPE_PLAYER];	// 3E04
	int m_RequireLevel[MAX_SKILL];	// 4304
	int m_RequireLeadership[MAX_SKILL];	// 4704
	int m_Delay[MAX_SKILL];	// 4B04
	WORD m_BrainPower[MAX_SKILL];	// 4F04
	int m_Attr[MAX_SKILL];	// 5104
	int m_iSkillType[MAX_SKILL];	// 5504
	int m_iSkillUseType[MAX_SKILL];	// 5904
	int m_iSkillBrand[MAX_SKILL];	// 5D04
	int m_iKillCount[MAX_SKILL];	// 6104
	int m_iRequireStatus[MAX_SKILL][MAX_REQ_SKILL_STATUS];	// 6504
}; extern cObjSkillTree gSkillTree;

struct SkillTreeConfig
{

};



#endif
