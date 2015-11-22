class CVipSystem
{
public:
	void ReadFile(char *filename);
	void ApplyVip(int aIndex, BYTE Type);
}; extern CVipSystem g_VipSystem;

extern int IsVipServer;
extern int BronzeVipExpDay;
extern int BronzeVipExpNight;
extern int SilverVipExpDay;
extern int SilverVipExpNight;
extern int PlatinumVipExpDay;
extern int PlatinumVipExpNight;
extern int BronzeVipDropDay;
extern int BronzeVipDropNight;
extern int SilverVipDropDay;
extern int SilverVipDropNight;
extern int PlatinumVipDropDay;
extern int PlatinumVipDropNight;