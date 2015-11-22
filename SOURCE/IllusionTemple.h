#define MAX_ILLUSION_TEMPLE_LEVEL 6
#define MAX_ILLUSION_TEMPLE_TEAMS 2
#define MAX_ILLUSION_TEMPLE_USER 10

#define IT_MAP_RANGE(value) ( (( (value)   )<MAP_INDEX_ILLUSION_TEMPLE1)?FALSE:(( (value)  )>MAP_INDEX_ILLUSION_TEMPLE6)?FALSE:TRUE  )
#define IT_BATTLEZONE_RANGE(x) ( ((x)<0)?FALSE:((x)>MAX_ILLUSION_TEMPLE_LEVEL-1)?FALSE:TRUE  )

#define IT_STATE_NONE 0
#define IT_STATE_CLOSED 1
#define IT_STATE_PLAYING 2
#define IT_STATE_PLAYEND 3
#pragma once
static struct ILLUSION_PLAYERLEVEL
{
	int MinLevel;
	int MaxLevel;
} g_IllusionLevel[MAX_ILLUSION_TEMPLE_LEVEL] = {
	220, 270,
	271, 320,
	321, 350,
	351, 380,
	381, 400,
	1, 400,
};

static struct ILLUSION_GATES
{
	int Gate;
} g_IllusionGatesYellow[MAX_ILLUSION_TEMPLE_LEVEL] = {
	148,
	149,
	150,
	151,
	152,
	153
}, g_IllusionGatesBlue[MAX_ILLUSION_TEMPLE_LEVEL] = {
	154,
	155,
	156,
	157,
	158,
	159
};

struct PMSG_ILLUSION_ENTER_RESULT // C1:BF:00
{
	PBMSG_HEAD2 h;
	WORD Result;
};

struct PMSG_ILLUSION_SET_STATE // C1:BF:09
{
	PBMSG_HEAD2 h;
	BYTE IllusionTempleIndex;
	BYTE State;
};

struct PMSG_ILLUSION_WAITING_ROOM // C1:BF:03 // TODO
{
	PBMSG_HEAD2 h;
	DWORD IllusionTempleIndex;
	WORD Unk;
};

struct PMSG_ILLUSION_KILL_POINT // C1:BF:06
{
	PBMSG_HEAD2 h;
	BYTE KillPoint;
};
#pragma pack (1)
struct INTERFACE_POSITION
{
	WORD aIndex;
	BYTE unk;
	BYTE X;
	BYTE Y;
	BYTE unk2;
};
struct PMSG_ILLUSION_INTERFACE // C1:BF:01
{
	PBMSG_HEAD2 h;
	WORD Time;
	WORD HeroIndex;
	BYTE HeroX;
	BYTE HeroY;
	BYTE AlliesPoint;
	BYTE IllusionsPoint;
	BYTE PlayerTeam;
	BYTE Teammates;
	INTERFACE_POSITION Teammate[5];
};
#pragma pack ()
struct PMSG_ILLUSION_ENABLESKILL // C1:BF:02
{
	PBMSG_HEAD2 h;
	WORD SkillTime;
	WORD SkillID;
	WORD aIndex;
	WORD TargetIndex;
};

struct PMSG_ILLUSION_DISABLESKILL // C1:BF:07
{
	PBMSG_HEAD2 h;
	BYTE SkillIDH;
	BYTE SkillIDL;
	WORD aIndex;
};

struct PMSG_ILLUSION_STATISTICS_DATA {
	char		  Name[10];
	BYTE		  ChangeUP;
	BYTE		  Team;
	BYTE		  Class;
	BYTE		  Unk[3];
	DWORD		  Experience;
};

struct PMSG_ILLUSION_STATISTICS {
	PBMSG_HEAD2		h;
	unsigned char	AlliedTeam;
	unsigned char	IllusionTeam;
	unsigned char	PlayersCount;
};

struct ILLUSION_START_TIME
{
	int Hour;
	int Minute;
};

struct _ILLUSION_WAITING_PLAYER_DATA
{
	int UserIndex;
	int Team;
	void Clear()
	{
		UserIndex = -1;
		Team = -1;
	}
};

struct _ILLUSION_PLAYER_DATA
{
	int UserIndex;
	int Exp;
	int Score;
	int KillPoints;
	int KillCount;
	int DeadCount;
	bool IsHero;
	void Clear()
	{
		UserIndex = -1;
		Exp = 0;
		Score = 0;
		KillPoints = 10;
		KillCount = 0;
		DeadCount = 0;
		IsHero = false;
	}
};

struct _ILLUSION_TEAM_DATA
{
	_ILLUSION_PLAYER_DATA TeamMate[5];
	int Score;
	int PartyID;
	int Count;
	void Clear()
	{
		Score = 0;
		PartyID = -1;
		Count = 0;
	}
};

struct _ILLUSION_TEMPLE_DATA
{
	int State;
	_ILLUSION_TEAM_DATA Teams[2];
	_ILLUSION_WAITING_PLAYER_DATA WaitingPlayers[10];
	int StatuePosNum[2];
	int IllusionGuardianPosNum;
	int AlliesGuardianPosNum;
	int IllusionBoxPosNum;
	int AlliesBoxPosNum;
	int RemainMSEC;
	int Tick;
	int Notify;
	bool Open;
	bool CanParty;
	int UserCount;
	int HeroIndex;
	int SacredItemSerial;
	bool PlayStarted;
	bool BeforeEnter;
	bool BeforeSemiPlay;
	bool BeforePlay;
	bool BeforeSemiPlayEnd;
	bool BeforePlayEnd;
	bool BeforeClosed;
	bool BeforeStatue;
	bool MonstersCreated;
	short WinTeam;
	void Clear()
	{
		Open = false;
		CanParty = false;
		UserCount = 0;
		PlayStarted = false;
		BeforeEnter = false;
		BeforeSemiPlay = false;
		BeforePlay = false;
		BeforeSemiPlayEnd = false;
		BeforePlayEnd = false;
		BeforeClosed = false;
		BeforeStatue = false;
		MonstersCreated = false;
		Notify = -1;
		HeroIndex = -1;
		SacredItemSerial = -1;
		WinTeam = -1;
		for(int i=0;i<2;++i)
		{
			for(int n=0;n<5;++n)
			{
				Teams[i].TeamMate[n].Clear();
			}
			Teams[i].Clear();
		}
		for(int k=0;k<10;++k)
		{
			WaitingPlayers[k].Clear();
		}
	}
};

class CIllusionTemple {
public:
	CIllusionTemple();
	virtual ~CIllusionTemple();
	void Load(char * file);
	void Init(bool Enabled);
	void Run();
	int GetViewportState();
	int GetTime();
	bool CheckCanEnter(int aIndex, int IllusionTempleIndex);
	void SendAllUserAnyMsg(LPBYTE Msg, int Size);
	void SendIllusionTempleTeamAnyMsg(LPBYTE Msg, int Size, int IllusionTempleIndex);
	void SendIllusionTempleRoomAnyMsg(LPBYTE Msg, int Size, int IllusionTempleIndex);
	void EnterToWaitingRoom(int aIndex, int IllusionTempleIndex);
	void LeaveUser(int aIndex, int IllusionTempleIndex);
	int GetUserLevelRoom(int aIndex);
	int GetWaitingUserCount(int IllusionTempleIndex);
	int GetCurPlayUser(int IllusionTempleIndex);
	int GetRemainTime(int IllusionTempleIndex);
	void DropSacredItem(int IllusionTempleIndex, LPOBJ Statue, LPOBJ User);
	bool CheckSacredItemSerial(int IllusionTempleIndex, CMapItem * Item);
	void GiveSacredItem(int IllusionTempleIndex, LPOBJ Statue, LPOBJ User);
	void DropSacredItemFromHero(int IllusionTempleIndex);
	bool AttackCheck(LPOBJ lpObj, LPOBJ lpTargetObj);
	void SetKillPoint(int IllusionTempleIndex, bool ForAll, int aIndex, int KillPoint);
	void AddKillPoint(int IllusionTempleIndex, int aIndex, int Points);
	void DecKillPoint(int IllusionTempleIndex, int aIndex, int Points);
	void UseSkill(int IllusionTempleIndex, PMSG_REQ_USEILLUSIONTEMPLESKILL * aRecv, int aIndex);
	void DisableSkill(int IllusionTempleIndex, LPOBJ lpObj, int Skill);
	int CheckWinnerTeam(int IllusionTempleIndex, bool EndTime);
	void RankingInfo(int IllusionTempleIndex);
	void TeleportToSecureArea(int IllusionTempleIndex);
	void PlayerProcess(int IllusionTempleIndex);
	void PlayerWaitingProcess(int IllusionTempleIndex);
	void GiveReward(int aIndex);
	void SetSacredItemSerial(int IllusionTempleIndex, int Serial) { this->m_IllusionTempleData[IllusionTempleIndex].SacredItemSerial = Serial; }
	void SetHero(int IllusionTempleIndex, int aIndex) { this->m_IllusionTempleData[IllusionTempleIndex].HeroIndex = aIndex; }
	int GetHeroIndex(int IllusionTempleIndex) { return this->m_IllusionTempleData[IllusionTempleIndex].HeroIndex; }

private:
	void ProcState_None(int IllusionTempleIndex);
	void ProcState_Closed(int IllusionTempleIndex);
	void ProcState_Playing(int IllusionTempleIndex);
	void ProcState_Playend(int IllusionTempleIndex);
	void SetState(int IllusionTempleIndex, int State);
	void SetState_None(int IllusionTempleIndex);
	void SetState_Closed(int IllusionTempleIndex);
	void SetState_Playing(int IllusionTempleIndex);
	void SetState_PlayEnd(int IllusionTempleIndex);
	void CheckSync(int IllusionTempleIndex);
	void DeleteMonsters(int IllusionTempleIndex);
	void CreateGuards(int IllusionTempleIndex);
	void CreateBoxes(int IllusionTempleIndex);
	void CreateStatues(int IllusionTempleIndex);
	void CreateMonsters(int IllusionTempleIndex);
	void SetTeams(int IllusionTempleIndex);
	void SetPartyTeam(int IllusionTempleIndex);
	void SendStateMsg(int IllusionTempleIndex, bool ForAll, int aIndex, int Destination, BYTE Msg);
	void IllusionPlayers(int IllusionTempleIndex);
	void MoveToBattleArea(int IllusionTempleIndex);
	void MinimapProcess(int IllusionTempleIndex, int IllusionTempleSubIndex, int Team, int aIndex);
	void DeletePlayer(int IllusionTempleIndex, int aIndex, bool WaitingRoom);
	int GiveRewardExp(int IllusionTempleIndex);
	int LevelUp(int UserIndex, int Exp, int Event);

	bool EventEnabled;
	int OpenTime;
	int ReadyTime;
	int PlayTime;
	int RestTime;
	static const int YellowIllusion = 404;
	static const int BlueIllusion = 405;
	std::vector<ILLUSION_START_TIME> v_IllusionStartTime;
	_ILLUSION_TEMPLE_DATA m_IllusionTempleData[MAX_ILLUSION_TEMPLE_LEVEL];
};

extern CIllusionTemple g_IllusionTemple;