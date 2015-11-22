#ifndef BUFFMANAGER_H
#define BUFFMANAGER_H
#define MAX_BUFF 512

struct BUFFEFFECTINFO
{
	BYTE Index;
	BYTE Viewport;
	BYTE ItemCat;
	BYTE ItemIndex;
	char Name[1024];
	BYTE Type;
	BYTE Unk1;
	BYTE ClearType;
	char Info[1024];
};
class CBuffManage
{
public:
	void Init();
	void LoadFile(char *file);
	void Insert(BYTE Index, BYTE Viewport,BYTE ItemCat,BYTE ItemIndex, char *Name,BYTE Type,BYTE Unk1,BYTE ClearType,char *info);
private:
	BUFFEFFECTINFO m_BuffData[MAX_BUFF];

}; extern CBuffManage g_BuffManager;



#endif