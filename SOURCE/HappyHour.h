#ifndef HAPPYHOUR_H
#define HAPPYHOUR_H

class CHappyHour
{
public:
	void Run();	
private:
	BYTE STATE; // 0 - not runing ; 1 - running
};
extern CHappyHour g_HappyHour;

#endif