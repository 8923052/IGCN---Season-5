#pragma pack (1)
struct PMSG_MASTER_INFO_SEND
{
    PBMSG_HEAD2 h; //C1:F3:50
	short MasterLevel;
	__int64 MasterExp;
	__int64 MasterNextExp;
	short MasterPoint;
	short MaxLife;
	short MaxMana;
	short MaxShield;
	short MaxBP;
};
/*struct PMSG_MASTERLEVEL_SEND
{
	PBMSG_HEAD2 h;		//0xC1,0x20,0xF3,0x50
	short MasterLevel;
	__int64 Exp;
	__int64 NextExp;
	short MasterPoints;
	short MaxLife;
	short MaxMana;
	short iMaxShield;
	short MaxBP;
};*/
struct PMSG_MASTER_LEVEL_UP_SEND
{
    PBMSG_HEAD2 h; //C1:F3:51
	WORD MasterLevel;
	WORD MinusPoint;
	WORD MasterPoint;
	WORD MaxMinusPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
    WORD MaxBP;
};

struct PMSG_MASTER_SKILL_RECV
{
    PBMSG_HEAD2 h; //C1:F3:52
	WORD MasterSkill;
    WORD MasterEmpty;
};

struct PMSG_MASTER_SKILL_SEND
{
    PBMSG_HEAD2 h; //C1:F3:52
    BYTE type;
	BYTE flag;
	WORD MasterPoint;
	WORD MasterSkill;
    WORD MasterEmpty;
	DWORD ChkSum;
};


#pragma pack ()
class CMasterSkillSystem
{
public:
	CMasterSkillSystem(void);
	virtual ~CMasterSkillSystem(void);
	void SetInfo(int MasterLevel, int MasterPoint, __int64 MasterExp, __int64 MasterNextExp, int aIndex);
	void SetEffect(int aIndex, CMagicInf * lpMagic);
	void SetObjEffect(int aIndex);
	void Init(int aIndex);
	bool IsMasterSkill(int SkillID);
	bool LevelUp(LPOBJ lpObj, __int64 addexp, int iMonsterType, int iEventType);
	__int64 NextExpCal(LPOBJ lpObj);
	__int64 ExpConvert(__int64 val);
	bool CanGainMasterExp(LPOBJ lpObj);
	void CGReqAddMasterPoint(int aIndex, PMSG_MASTER_SKILL_RECV * lpMsg);
	void GCAnsAddMasterPoint(int aIndex, BYTE type, BYTE flag, int MasterSkill, int MasterEmpty);
	int CheckGroupSkill(int aIndex, int SkillID, int Group);
	void ReplaceSkill(int aIndex, int NewSkill, int OldSkill);
	int GetActiveSkill(int aIndex, int NewSkill);

	static const __int64 ExpStat = 35507050;
};
extern CMasterSkillSystem MasterLevelSystem;