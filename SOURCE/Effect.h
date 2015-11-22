#pragma once

#define MAX_PLAYER_BUFF 40

class CEffect
{
public:
	CEffect(void);
	virtual ~CEffect(void);

	bool IsEffect();
	bool Set(int effect);
	bool Set(int effect, int item);
	void Clear();

	BYTE m_effect;
	int m_count;
	int m_value1;
	int m_value2;
	int m_value3;
	int m_effectuseoption;
	int m_optiontype;
	int m_effecttype1;
	int m_effecttype2;
	int m_tick;
	int m_itemcode;
};

