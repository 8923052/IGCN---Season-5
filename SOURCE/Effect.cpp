#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect(void)
{
}


CEffect::~CEffect(void)
{
}

bool CEffect::IsEffect()
{
    if(this->m_effect == 0xFF)
	{
	    return 0;
	}

	return 1;
}

bool CEffect::Set(int effect)
{
    if(this->m_effect != 0xFF)
	{
        return 0;
	}

	this->m_effect = effect;
	this->m_count = 0;
	this->m_value1 = 0;
	this->m_value2 = 0;
	this->m_value3 = 0;
	this->m_effectuseoption = 0;
	this->m_optiontype = 0;
	this->m_effecttype1 = 0;
	this->m_effecttype2 = 0;
	this->m_tick = 0;
	this->m_itemcode = -1;
	return 1;
}

bool CEffect::Set(int effect, int item)
{
	if(this->m_effect != 0xFF)
	{
		return 0;
	}
	this->m_effect = effect;
	this->m_count = 0;
	this->m_value1 = 0;
	this->m_value2 = 0;
	this->m_value3 = 0;
	this->m_effectuseoption = 0;
	this->m_optiontype = 0;
	this->m_effecttype1 = 0;
	this->m_effecttype2 = 0;
	this->m_tick = 0;
	this->m_itemcode = item;
	return 1;
}

void CEffect::Clear()
{
    this->m_effect = 0xFF;
	this->m_count = 0;
	this->m_value1 = 0;
	this->m_value2 = 0;
	this->m_value3 = 0;
	this->m_effectuseoption = 0;
	this->m_optiontype = 0;
	this->m_effecttype1 = 0;
	this->m_effecttype2 = 0;
	this->m_tick = 0;
	this->m_itemcode = -1;
}
