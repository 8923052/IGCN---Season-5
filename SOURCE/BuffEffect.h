
#include "MagicInf.h"
#include "user.h"

#define MAX_BUFF 200

enum EFFECT_LIST
{
	EFFECT_GREATER_ATTACK = 1,
	EFFECT_GREATER_DEFENSE = 2,
	EFFECT_NPC_BUFF = 3,
	EFFECT_WIZARD_DEFENSE = 4,
	EFFECT_CRITICAL_DAMAGE = 5,
	EFFECT_INFINITY_ARROW = 6,
	EFFECT_SWELL_LIFE = 8,
	EFFECT_SWELL_MANA = 9,
	EFFECT_BLESS_POTION = 10,
	EFFECT_SOUL_POTION = 11,
	EFFECT_INVISIBLE = 18,
	EFFECT_BRAND_OF_SKILL = 19,
	EFFECT_GAMEMASTER = 28,
	EFFECT_EXP1_INCREASE = 29,
	EFFECT_EXPDROP1_INCREASE = 30,
	EFFECT_EXP_DISABLE1 = 31,
	EFFECT_ILLUSION_SHIELD = 34,
	EFFECT_HALLOWEEN_BLESS = 35,
	EFFECT_HALLOWEEN_WRATH = 36,
	EFFECT_HALLOWEEN_CRY = 37,
	EFFECT_HALLOWEEN_FOOD = 38,
	EFFECT_HALLOWEEN_DRINK = 39,
	EFFECT_EXP2_INCREASE = 40,
	EFFECT_EXPDROP2_INCREASE = 41,
	EFFECT_EXPDISABLE2_INCREASE = 42,
	EFFECT_MOBILITY = 43,
	EFFECT_QUICKNESS = 44,
	EFFECT_DEFENSE = 45,
	EFFECT_WRATH = 46,
	EFFECT_WIZARDRY = 47,
	EFFECT_HEALTH = 48,
	EFFECT_MANA = 49,
	EFFECT_ADDSTRENGTH = 50,
	EFFECT_ADDAGILITY = 51,
	EFFECT_ADDVITALITY = 52,
	EFFECT_ADDENERGY = 53,
	EFFECT_ADDLEADERSHIP = 54,
	EFFECT_POISON = 55,
	EFFECT_ICE = 56,
	EFFECT_HARDEN = 57,
	EFFECT_MAGUMSADEFENSEDOWN = 58,
	EFFECT_STERN = 61,
	EFFECT_IMMUNETOMAGIC = 63,
	EFFECT_IMMUNETOHARM = 64,
	EFFECT_ILLUSIONPARALYZE = 65,
	EFFECT_DAMAGEREF = 71,
	EFFECT_SLEEP = 72,
	EFFECT_NEIL = 74,
	EFFECT_SAHAMUTT = 75,
	EFFECT_DAMAGEDOWN = 76,
	EFFECT_DEFENSEDOWN = 77,
	EFFECT_BLOSSOMWINE = 78,
	EFFECT_BLOSSOMCAKE = 79,
	EFFECT_BLOSSOMPETAL = 80,
	EFFECT_SWORDPOWER = 81,
	EFFECT_MAGICCIRCLE = 82,
	EFFECT_FLAMESTRIKE = 83,
	EFFECT_GIGANTICSTORM = 84,
	EFFECT_LIGHTINGSHOCK = 85,
	EFFECT_PARALYZE = 86,
	EFFECT_SEALHELING = 87,
	EFFECT_SEALDIVINITY = 88,
	EFFECT_SCROLLBATTLE = 89,
	EFFECT_SCROLLSTRENGTH = 90,
	EFFECT_SANTABLESS = 91,
	EFFECT_SANTAHEALING = 92,
	EFFECT_SANTAPROTECTION = 93,
	EFFECT_SANTASTRENGTH = 94,
	EFFECT_SANTADEFENSE = 95,
	EFFECT_SANTAQUICKNESS = 96,
	EFFECT_SANTAFORTUNE = 97,
	EFFECT_GUARDIANTALISMAN = 99,
	EFFECT_ITEMPROTECTIONTALISMAN = 100,
	EFFECT_MASTEREXP_INCREASE = 101,
	EFFECT_MASTEREXPDROP_INCREASE = 102,
	EFFECT_GLADIATORBUFF = 103
};

class CBuffEffect
{
public:
	CBuffEffect(void);
	virtual ~CBuffEffect(void);

	void LoadBuffFile(char* file);
	void Init();
	bool SetBuff(BYTE Viewport, BYTE Index, BYTE ItemGroup, BYTE ItemIndex, char BuffName[100], BYTE BuffType, BYTE Unk, BYTE Unk2, char BuffDesc[100]);

	void EnableBuff(int aIndex, BYTE BuffIndex, int Time, int Value1, int Value2, int Value3);
	CEffect * BuffSearch(LPOBJ lpObj, BYTE Viewport);
	int GetBuffIndexByItemNumber(int ItemIndex);
	void EnableBuff(int aIndex, int ItemNumber, int EffectUseOption, int OptionType, int EffectType1, int EffectType2, int ValidTime, BYTE BuffIndex);
	int DelEffect(int aIndex, int ItemNumber, int EffectUseOption, int OptionType, int EffectType1, int EffectType2);
	void DisableSiegeBuff(int aIndex);
	void ApplyEffect(LPOBJ lpObj, int effectpos, int Time, int Value1, int Value2, int Value3, int EffectUseOption, int OptionType, int EffectType1, int EffectType2, int ItemCode);
	void RemoveEffect(LPOBJ lpObj, CEffect * lpEffect);
	void Run();
	int AddEffect(LPOBJ lpObj, BYTE Viewport, int Time, int ItemNumber);
	int DelEffect(LPOBJ lpObj, BYTE Viewport);
	void ClearBuff(LPOBJ lpObj);
	void InitEffect(LPOBJ lpObj);
	bool CheckPeriodEffect(BYTE Viewport);
	void PeriodEffect(LPOBJ LPOBJ, CEffect * lpEffect);
	void ResetEffectTime(LPOBJ lpObj, CEffect * lpEffect, int Time);

	inline bool HalloweenBuff(BYTE Buff)
	{
		if(Buff >= 35 && Buff <= 39)
			return true;
		return false;
	}

	inline bool BlossomBuff(BYTE Buff)
	{
		if(Buff >= 78 && Buff <= 80)
			return true;
		return false;
	}

	inline bool SantaBuff(BYTE Buff)
	{
		if(Buff >= 91 && Buff <= 97)
			return true;
		return false;
	}

private:

	short ViewportNumber[MAX_BUFF];
	BYTE BuffIndex[MAX_BUFF];
	BYTE BuffItemGroup[MAX_BUFF];
	BYTE BuffItemIndex[MAX_BUFF];
	char BuffName[MAX_BUFF][100];
	BYTE BuffType[MAX_BUFF];
	BYTE Undefined[MAX_BUFF];
	BYTE Undefined2[MAX_BUFF];
	char BuffDescription[MAX_BUFF][100];
	int TickCount;

	enum BUFF_TYPES {
		B_BUFF = 0,
		B_MAGIC = 1,
	};

	void DisableSpecificBuff(LPOBJ lpObj);
	
};


extern CBuffEffect BuffEffectC;
