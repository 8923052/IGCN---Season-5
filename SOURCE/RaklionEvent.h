#define RAKLION_NONE	0
#define RAKLION_START	1
#define RAKLION_NOTIFY	2
#define RAKLION_END		3
#define RAKLION_PHAZE1  4
#define RAKLION_PHAZE2  5
#define RAKLION_PHAZE3  6

class CRaklionEvent
{
	
private:
	int m_iBattleState;
	int m_iMinutesLeft;
	int m_iLiveSpiderCount;
	int m_iLiveEggCount;
	int m_iLiveSerupinCount;
	DWORD dwTick;	
public:	

	CRaklionEvent();
	~CRaklionEvent();
	void EnterEvent(int aIndex);
	void StartEvent();
	void Run();
	void GiveReward(int mobIndex);
	bool isRunning();
	void SetState(int iBattleState);
	void SetState_NONE();
	void SetState_START();
	void SetState_NOTIFY();
	void SetState_PHAZE1();
	void SetState_PHAZE2();
	void SetState_PHAZE3();
	void SetState_END();
	void SetBattleState(int iBattleState)
	{
		this->m_iBattleState = iBattleState;
	}
	void CheckTime();
	int indexEntrants[10];
	void Init();
	void MonsterManager(int Index);
	void GenerateMonster(int PHAZE);
	void delMonster(int index);
	// vars
	bool BlockBossEntry;
	int m_iEntrantCount;
}; extern CRaklionEvent g_Raklion;