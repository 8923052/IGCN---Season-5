#ifndef MEDUSAEVENT_H
#define MEDUSAEVENT_H
struct MEDUSA_INFO
{
	int MedusaIndex;
	int HelperIndex[30];
	BYTE StartTimes;
	BYTE StartHours[24];
};

class CMedusaEvent
{
public:
	CMedusaEvent();
	~CMedusaEvent();

	bool running;
	void StartEvent();
	void SpawnMonster(int Class, int map, int X, int Y);
	void EndEvent();
	void Run();

	MEDUSA_INFO m_info;
}; extern CMedusaEvent gMedusaEvent;

#endif