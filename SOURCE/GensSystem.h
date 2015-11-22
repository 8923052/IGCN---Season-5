#include "DSProtocol.h"
struct PMSG_GENS_INFO
{
	PBMSG_HEAD2 h;
	int	GensID;
	int	GensLevel;
	int Position;
	int Contribution;
	int NextPosition;
};
struct PMSG_REQ_GENS_JOIN
{
	PBMSG_HEAD2 h;
	BYTE GensID;
};

struct PMSG_GENS_JOIN
{
	PBMSG_HEAD2 h;
	BYTE result;
	BYTE unk;
};

struct PMSG_GENS_LEAVE
{
	PBMSG_HEAD2 h;
	BYTE result;
};
struct PMSG_REQ_GENS_REWARD
{
	PBMSG_HEAD2 h;
	BYTE GensID;
};
struct PMSG_ANS_GENS_REWARD
{
	PBMSG_HEAD2 h;
	BYTE result;
};

struct PMSG_ANS_GENS_QUEST
{
	PBMSG_HEAD2 h;
	short NpcID;
	BYTE Unk1;
	BYTE Unk2;
};

struct PMSG_VIEWPORT_GENS
{
	BYTE	GensID;
	BYTE	IndexH;
	BYTE	IndexL;
	BYTE	Unknown;
	WORD	Ranking;
	int		Level;
	int		Unknown2;
};
struct PWMSG_VIEWPORT_GENS_COUNT 
{
	PWMSG_HEAD2 h;
	unsigned char count;
};

class CPvPGens
{
public:
	CPvPGens(void);
	virtual ~CPvPGens(void);

	void CGReqJoinGens(PMSG_REQ_GENS_JOIN *lpMsg, LPOBJ lpObj);
	void GCAnsJoinGens(LPOBJ lpObj, int Result, int GensID, int GensExp, int GensNextExp, int GensPos);
	void CGReqGensInfo(LPOBJ lpObj);
	void GCAnsGensInfo(GSP_ANS_GENS_INFO *aRecv);
	void CGReqQuitGens(LPOBJ lpObj);
	void GCAnsGensQuit(LPOBJ lpObj, int Result);
	void CGReqGensReward(PMSG_REQ_GENS_REWARD *aRecv, LPOBJ lpObj);

	void SendInfo(LPOBJ lpObj);
	int CalcPoint(LPOBJ lpObj, LPOBJ lpTargetObj, bool DeadMode);
	int CalcNextPosition(LPOBJ lpObj);
	int CalcPositionByRank(LPOBJ lpObj);
	void KillUserProc(LPOBJ lpObj, LPOBJ lpTargetObj);
	bool GensCheck(LPOBJ lpObj, LPOBJ lpTargetObj);
	void RefreshPlayerRank(LPOBJ lpObj, int Rank);

	void Run();

	inline bool IsBattleZone(short MapNumber)
	{
		if(MapNumber == MAP_INDEX_VULCAN)
			return true;
		else return false;
	};

private:
	SYSTEMTIME		Time;
	char			UpdateStatus;
	DWORD			Tick;
};

extern CPvPGens PvPGens;
