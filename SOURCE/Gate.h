// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// gate.h

#ifndef GATE_H
#define GATE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_GATES 512

class CGate
{
public:

	CGate();
	virtual ~CGate();

	void Init();
	void Load(LPSTR Buffer, int iSize);
	void Load(LPSTR filename);
	int IsGate(int GateNumber);
	int GetGate(int mgt, short& x, short& y, BYTE& MapNumber, BYTE& dir, short& Level);
	int GetLevel(int GateNumber);
	int IsInGate(int aIndex, int GateNumber);
	int CheckGateLevel(int aIndex, int GateNumber);


private:

	WORD m_This[512];	// 4
	WORD m_Flag[512];	// 104
	WORD m_MapNumber[512];	// 204
	WORD m_Sx[512];	// 304
	WORD m_Sy[512];	// 404
	WORD m_Ex[512];	// 504
	WORD m_Ey[512];	// 604
	WORD m_TargetGate[512];	// 704
	WORD m_Dir[512];	// 804
	WORD m_Level[512];	// 904
};

extern CGate gGateC;

#endif