#include "stdafx.h"
#include "GameMain.h"
#include "GameServer.h"
#include "..\include\readscript.h"
#include "user.h"
#include "BuffEffect.h"
#include "LogProc.h"
#include "ItemAddOption.h"
#include "ObjCalCharacter.h"
#include "IllusionTemple.h"
#include "MoveCommand.h"
// TODO
// REMOVE ALL SKILLS INFO FROM GOBJ
// AND TRANSFER IT TO SkillInfo STRUCT

CBuffEffect BuffEffectC;

CBuffEffect::CBuffEffect(void)
{
}

CBuffEffect::~CBuffEffect(void)
{
}
void CBuffEffect::Init()
{
	for(int i=0;i<MAX_BUFF;++i)
	{
		this->BuffIndex[i] = -1;
		this->ViewportNumber[i] = -1;
		this->BuffType[i] = -1;
	}
	this->TickCount = GetTickCount();
}
void CBuffEffect::LoadBuffFile(char *file)
{
	this->Init();
	SMDFile = fopen(file, "r");
	if(SMDFile == NULL)
	{
		MsgBox("%s file not found", file);
		return;
	}
	int Token;
	int count = 0;
	unsigned char type;
	char Name[100];
	unsigned char viewport;
	unsigned char index;
	unsigned char itemgroup;
	unsigned char itemindex;
	unsigned char bufftype;
	unsigned char unk1;
	unsigned char unk2;
	char Description[100];

	while(true)
	{
		Token = GetToken();
		if(Token == 2)
			break;
		type = TokenNumber;

		if(type == 0)
		{
			while(true)
			{
				Token = GetToken();
				if(strcmp(TokenString, "end") == 0)
					break;

				viewport = TokenNumber;

				Token = GetToken();
				index = TokenNumber;

				Token = GetToken();
				itemgroup = TokenNumber;

				Token = GetToken();
				itemindex = TokenNumber;

				Token = GetToken();
				strcpy(Name, TokenString);

				Token = GetToken();
				bufftype = TokenNumber;

				Token = GetToken();
				unk1 = TokenNumber;

				Token = GetToken();
				unk2 = TokenNumber;

				Token = GetToken();
				strcpy(Description, TokenString);
				this->SetBuff(viewport, index, itemgroup, itemindex, Name, bufftype, unk1, unk2, Description);
				count++;
			}
		}
	}
	LogAddTD("[Buff Effect Manager] Load %d buffs", count);
}
bool CBuffEffect::SetBuff(BYTE Viewport, BYTE Index, BYTE ItemGroup, BYTE ItemIndex, char BuffName[], BYTE BuffType, BYTE Unk, BYTE Unk2, char BuffDesc[])
{
	if(Viewport > MAX_BUFF || Index > MAX_BUFF || Viewport < 0 || Index < 0)
	{
		LogAddC(2, "Buff Effect Overflow %d %d %s %s", Viewport, Index, __FILE__, __LINE__);
		return false;
	}
	this->ViewportNumber[Viewport] = Viewport;
	this->BuffIndex[Viewport] = Index;
	this->BuffItemGroup[Viewport] = ItemGroup;
	this->BuffItemIndex[Viewport] = ItemIndex;
	strcpy(this->BuffName[Viewport], BuffName);
	this->BuffType[Viewport] = BuffType;
	this->Undefined[Viewport] = Unk;
	this->Undefined2[Viewport] = Unk2;
	strcpy(this->BuffDescription[Viewport], BuffDesc);
	return true;
}

int CBuffEffect::AddEffect(LPOBJ lpObj, BYTE Viewport, int Time, int ItemNumber)
{
	CEffect * prevEffect = this->BuffSearch(lpObj, Viewport);
	if(prevEffect != 0)
	{
		if(prevEffect->m_itemcode != -1)
		{
			g_ItemAddOption.ClearItemEffect2(lpObj, prevEffect->m_itemcode, prevEffect->m_effecttype1);
		}
		else if(ItemNumber > 0)
		{
			this->DelEffect(lpObj, prevEffect->m_effect);
		}
		else
		{
			this->ResetEffectTime(lpObj, prevEffect, Time);
		}
	}

	for(int i=0;i<MAX_PLAYER_BUFF;++i)
	{
		if(lpObj->lpEffect[i].IsEffect() != false)
			continue;

		if(lpObj->lpEffect[i].Set(Viewport) == 0)
			return -1;

		return i;
	}
	return -1;
}

int CBuffEffect::DelEffect(LPOBJ lpObj, BYTE Viewport)
{
	if(!gObjIsConnected(lpObj->m_Index))
	{
		return -1;
	}
	for(int n=0;n < MAX_PLAYER_BUFF;n++)
	{
	    if(lpObj->lpEffect[n].IsEffect() == 0)
		{
		    continue;
		}

		if(lpObj->lpEffect[n].m_effect == Viewport)
		{
			this->RemoveEffect(lpObj,&lpObj->lpEffect[n]); 

	        lpObj->lpEffect[n].Clear();

			GCStateInfoSend(lpObj, 0, Viewport);

			return n;
		}
	}
	return -1;
}

void CBuffEffect::EnableBuff(int aIndex, BYTE Viewport, int Time, int Value1, int Value2, int Value3)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}
	if(Viewport < 0 || Viewport > MAX_BUFF)
	{
		return;
	}
	if(!gObjIsConnected(aIndex))
	{
		return;
	}
	
	int pos = this->AddEffect(&gObj[aIndex], Viewport, Time, 0);

	if(pos < 0)
		return;

	this->ApplyEffect(&gObj[aIndex], pos, Time, Value1, Value2, Value3, 0, 0, 0, 0, -1);
	GCStateInfoSend(&gObj[aIndex], 1, Viewport);
}

CEffect * CBuffEffect::BuffSearch(LPOBJ lpObj, BYTE Viewport)
{
	CEffect * lpEffect;
	for(int i=0;i<MAX_PLAYER_BUFF;++i)
	{
		lpEffect = &lpObj->lpEffect[i];
		
		if(lpEffect->IsEffect() != true)
			continue;

		if(lpEffect->m_effect == Viewport)
			return lpEffect;
	}
	return 0;
}

int CBuffEffect::GetBuffIndexByItemNumber(int ItemIndex)
{
	for(int i=0;i<MAX_BUFF;++i)
	{
		if(ItemIndex == ITEMGET(this->BuffItemGroup[i], this->BuffItemIndex[i]))
		{
			return this->ViewportNumber[i];
		}
	}
	return -1;
}

void CBuffEffect::EnableBuff(int aIndex, int ItemNumber, int EffectUseOption, int OptionType, int EffectType1, int EffectType2, int ValidTime, BYTE BuffIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}
	if(!gObjIsConnected(aIndex))
	{
		return;
	}
	BYTE Viewport;
	if(BuffIndex == 255)
	{
		if(ItemNumber < 0 || ItemNumber > 65535)
		{
			return;
		}
		Viewport = this->GetBuffIndexByItemNumber(ItemNumber);
	}
	else
	{
		Viewport = BuffIndex;
	}

	if(Viewport < 0 || Viewport > MAX_BUFF)
	{
		return;
	}

	// disabling this buff first (prevent showing buff without period time)
	GCUseEffectItem(&gObj[aIndex], EffectUseOption, OptionType, EffectType1, 0, Viewport);
	GCUseEffectItem(&gObj[aIndex], EffectUseOption, OptionType, EffectType2, 0, Viewport);
	GCStateInfoSend(&gObj[aIndex], 0, Viewport);

	if(this->HalloweenBuff(Viewport) == true || this->BlossomBuff(Viewport) || this->SantaBuff(Viewport))
	{
		this->DisableSpecificBuff(&gObj[aIndex]);
	}
	
	int pos = this->AddEffect(&gObj[aIndex], Viewport, ValidTime, ItemNumber);

	if(pos < 0)
		return;

	this->ApplyEffect(&gObj[aIndex], pos, ValidTime, 0, 0, 0, EffectUseOption, OptionType, EffectType1, EffectType2, ItemNumber);

	GCUseEffectItem(&gObj[aIndex], 0, OptionType, EffectType1, ValidTime, Viewport); // Period time info & effect
	GCUseEffectItem(&gObj[aIndex], 0, OptionType, EffectType2, ValidTime, Viewport); // Period time info & effect
	GCStateInfoSend(&gObj[aIndex], 1, Viewport); // normal buff
}
int CBuffEffect::DelEffect(int aIndex, int ItemNumber, int EffectUseOption, int OptionType, int EffectType1, int EffectType2)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return -1;
	}
	if(ItemNumber < 0 || ItemNumber > 65535)
	{
		return -1;
	}
	if(!gObjIsConnected(aIndex))
	{
		return -1;
	}

	BYTE Viewport = this->GetBuffIndexByItemNumber(ItemNumber);

	if(Viewport < 0 || Viewport > MAX_BUFF)
	{
		return -1;
	}

	for(int i=0;i<MAX_PLAYER_BUFF;++i)
	{
		if(gObj[aIndex].lpEffect[i].IsEffect() == true)
		{
			if(gObj[aIndex].lpEffect[i].m_effect == Viewport)
			{
				g_ItemAddOption.ClearItemEffect2(&gObj[aIndex], gObj[aIndex].lpEffect[i].m_itemcode,  gObj[aIndex].lpEffect[i].m_effect);

				this->RemoveEffect(&gObj[aIndex], &gObj[aIndex].lpEffect[i]);

				GCUseEffectItem(&gObj[aIndex], gObj[aIndex].lpEffect[i].m_effectuseoption, gObj[aIndex].lpEffect[i].m_optiontype, gObj[aIndex].lpEffect[i].m_effecttype1, 0, gObj[aIndex].lpEffect[i].m_effect);
				GCUseEffectItem(&gObj[aIndex], gObj[aIndex].lpEffect[i].m_effectuseoption, gObj[aIndex].lpEffect[i].m_optiontype, gObj[aIndex].lpEffect[i].m_effecttype2, 0, gObj[aIndex].lpEffect[i].m_effect);
				GCStateInfoSend(&gObj[aIndex], 0, Viewport);

				gObj[aIndex].lpEffect[i].Clear();

				return i;
			}
		}
	}
}
void CBuffEffect::DisableSiegeBuff(int aIndex)
{
#if (GS_CASTLE == 1)
	switch(gObj[aIndex].m_btCsJoinSide)
	{
	case 1:
		this->DelEffect(&gObj[aIndex], 14);
		break;
	case 2:
		this->DelEffect(&gObj[aIndex], 15);
		break;
	case 3:
		this->DelEffect(&gObj[aIndex], 16);
		break;
	case 4:
		this->DelEffect(&gObj[aIndex], 17);
		break;
	}
#endif
}

void CBuffEffect::ApplyEffect(LPOBJ lpObj, int effectpos, int Time, int Value1, int Value2, int Value3, int EffectUseOption, int OptionType, int EffectType1, int EffectType2, int ItemCode)
{
	CEffect * Effect = &lpObj->lpEffect[effectpos];

	Effect->m_count = Time;
	Effect->m_value1 = Value1;
	Effect->m_value2 = Value2;
	Effect->m_value3 = Value3;
	Effect->m_effectuseoption = EffectUseOption;
	Effect->m_optiontype = OptionType;
	Effect->m_effecttype1 = EffectType1;
	Effect->m_effecttype2 = EffectType2;
	Effect->m_itemcode = ItemCode;

	switch ( Effect->m_effect )
	{
		case EFFECT_GREATER_ATTACK:
			lpObj->m_SkillDefense += Value1;
			break;
		case EFFECT_GREATER_DEFENSE:
			lpObj->m_SkillAttack += Value1;
			break;
		case EFFECT_NPC_BUFF:
			lpObj->m_iSkillNPCDefense += Value1;
			lpObj->m_iSkillNPCAttack += Value2;
			break;
		case EFFECT_WIZARD_DEFENSE:
			lpObj->m_SkillInfo.WizardDefenseVal += Value1;
			break;
		case EFFECT_CRITICAL_DAMAGE:
			lpObj->SkillAddCriticalDamage += Value1;
			break;
		case EFFECT_INFINITY_ARROW:
			break;
		case EFFECT_SWELL_LIFE:
			lpObj->m_SkillInfo.SkillAddLife += Value1;
			break;
		case EFFECT_SWELL_MANA:
			lpObj->AddMana += Value1;
			break;
		case EFFECT_BLESS_POTION:
			break;
		case EFFECT_SOUL_POTION:
			break;
		case EFFECT_INVISIBLE:
			break;
		case EFFECT_BRAND_OF_SKILL:
			break;
		case EFFECT_ILLUSION_SHIELD:
			break;
		case EFFECT_POISON:
			lpObj->m_SkillInfo.PoisonType = Value1;
			lpObj->lpAttackObj = &gObj[Value2];
			break;
		case EFFECT_ICE:
			lpObj->m_SkillInfo.IceType = Value1;
			lpObj->lpAttackObj = &gObj[Value2];
			break;
		case EFFECT_HARDEN:
			break;
		case EFFECT_MAGUMSADEFENSEDOWN:
			lpObj->m_SkillMagumReduceDefense += Value1;
			break;
		case EFFECT_STERN:
			break;
		case EFFECT_IMMUNETOMAGIC:
			break;
		case EFFECT_IMMUNETOHARM:
			break;
		case EFFECT_ILLUSIONPARALYZE:
			break;
		case EFFECT_DAMAGEREF:
			lpObj->m_SkillInfo.DamageRefVal += Value1;
			break;
		case EFFECT_SLEEP:
			break;
		case EFFECT_NEIL:
			lpObj->m_SkillInfo.NeilDamage += Value1;
			lpObj->lpAttackObj = &gObj[Value2];
			break;
		case EFFECT_SAHAMUTT:
			lpObj->m_SkillInfo.SahamuttDamage += Value1;
			lpObj->lpAttackObj = &gObj[Value2];
			break;
		case EFFECT_DAMAGEDOWN:
			lpObj->m_SkillInfo.DecDamageValue += Value1;
			break;
		case EFFECT_DEFENSEDOWN:
			lpObj->m_SkillInfo.DecDefenseValue += Value1;
			break;
		case EFFECT_SWORDPOWER:
			lpObj->m_SkillInfo.SwordPowerIncVal += Value1;
			lpObj->m_SkillInfo.SwordPowerDecVal += Value2;
			break;
		case EFFECT_MAGICCIRCLE:
			lpObj->m_SkillInfo.MagicCircleVal += Value1;
			break;
		case EFFECT_FLAMESTRIKE:
			break;
		case EFFECT_GIGANTICSTORM:
			break;
		case EFFECT_LIGHTINGSHOCK:
			break;
		case EFFECT_PARALYZE:
			break;
		case EFFECT_SANTABLESS:
			lpObj->m_SkillInfo.SantaBlessingVal += Value1;
			break;
		case EFFECT_SANTAHEALING:
			lpObj->m_SkillInfo.SantaHealingVal += Value1;
			break;
		case EFFECT_SANTAPROTECTION:
			lpObj->m_SkillInfo.SantaProtectionVal += Value1;
			break;
		case EFFECT_SANTASTRENGTH:
			lpObj->m_SkillInfo.SantaStrengthVal += Value1;
			break;
		case EFFECT_SANTADEFENSE:
			lpObj->m_SkillInfo.SantaDefenceVal += Value1;
			break;
		case EFFECT_SANTAQUICKNESS:
			lpObj->m_SkillInfo.SantaQuicknessVal += Value1;
			break;
		case EFFECT_SANTAFORTUNE:
			lpObj->m_SkillInfo.SantaFortuneVal += Value1;
			break;
		case EFFECT_GLADIATORBUFF:
			lpObj->m_SkillInfo.GladiatorBuffVal += Value1;
			break;
		default:
			break;
	}
	if(lpObj->Type == OBJ_USER)
	{
		LogAddTD("[Buff Effect] (%s)(%s) Apply Effect ID: %d Time: %d Val1: %d Val2:%d Val3:", lpObj->AccountID, lpObj->Name, Effect->m_effect, Time, Value1, Value2, Value3);
		gObjCalCharacter(lpObj->m_Index);
	}
}

void CBuffEffect::RemoveEffect(LPOBJ lpObj, CEffect * lpEffect)
{
	switch ( lpEffect->m_effect )
	{
		case EFFECT_GREATER_ATTACK:
			lpObj->m_SkillAttack-= lpEffect->m_value1;
			GCMagicCancelSend(lpObj,28);
			break;
		case EFFECT_GREATER_DEFENSE:
			lpObj->m_SkillDefense -= lpEffect->m_value1;
			break;
		case EFFECT_NPC_BUFF:
			lpObj->m_iSkillNPCDefense -= lpEffect->m_value1;
			lpObj->m_iSkillNPCAttack -= lpEffect->m_value2;
			break;
		case EFFECT_WIZARD_DEFENSE:
			lpObj->m_SkillInfo.WizardDefenseVal -= lpEffect->m_value1;
			GCMagicCancelSend(lpObj,16);
			break;
		case EFFECT_CRITICAL_DAMAGE:
			lpObj->SkillAddCriticalDamage -= lpEffect->m_value1;
			break;
		case EFFECT_INFINITY_ARROW:
			break;
		case EFFECT_SWELL_LIFE:
			lpObj->m_SkillInfo.SkillAddLife -= lpEffect->m_value1;
			GCMagicCancelSend(lpObj,48);
			break;
		case EFFECT_SWELL_MANA:
			lpObj->AddMana -= lpEffect->m_value1;
			break;
		case EFFECT_BLESS_POTION:
			break;
		case EFFECT_SOUL_POTION:
			break;
		case EFFECT_INVISIBLE:
			break;
		case EFFECT_BRAND_OF_SKILL:
			break;
		case EFFECT_ILLUSION_SHIELD:
			{
				if(IT_BATTLEZONE_RANGE(lpObj->m_cIllusionTempleIndex))
				{
					g_IllusionTemple.DisableSkill(lpObj->m_cIllusionTempleIndex, lpObj, AT_SKILL_ILLUSION_SHIELD);
				}
			}
			break;
		case EFFECT_POISON:
			if(lpObj->m_SkillInfo.PoisonType != 38)
			{
				GCMagicCancelSend(lpObj,1);
			}
			lpObj->m_SkillInfo.PoisonType = 0;
			lpObj->lpAttackObj = 0;
			break;
		case EFFECT_ICE:
			if(lpEffect->m_effect != 39)
			{
				GCMagicCancelSend(lpObj,7);
			}
			lpObj->m_SkillInfo.IceType = 0;
			lpObj->lpAttackObj = 0;
			break;
		case EFFECT_HARDEN:
			GCMagicCancelSend(lpObj, 51);
			break;
		case EFFECT_MAGUMSADEFENSEDOWN:
			lpObj->m_SkillMagumReduceDefense -= lpEffect->m_value1;
			GCMagicCancelSend(lpObj,55);
			break;
		case EFFECT_STERN:
			break;
		case EFFECT_IMMUNETOMAGIC:
			break;
		case EFFECT_IMMUNETOHARM:
			break;
		case EFFECT_ILLUSIONPARALYZE:
			{
				if(IT_BATTLEZONE_RANGE(lpObj->m_cIllusionTempleIndex))
				{
					g_IllusionTemple.DisableSkill(lpObj->m_cIllusionTempleIndex, lpObj, AT_SKILL_ILLUSION_PARALYZE);
				}
			}
			break;
		case EFFECT_DAMAGEREF:
			lpObj->m_SkillInfo.DamageRefVal -= lpEffect->m_value1;
			break;
		case EFFECT_SLEEP:
			break;
		case EFFECT_NEIL:
			lpObj->m_SkillInfo.NeilDamage -= lpEffect->m_value1;
			lpObj->lpAttackObj = 0;
			break;
		case EFFECT_SAHAMUTT:
			lpObj->m_SkillInfo.SahamuttDamage -= lpEffect->m_value1;
			lpObj->lpAttackObj = 0;
			break;
		case EFFECT_DAMAGEDOWN:
			lpObj->m_SkillInfo.DecDamageValue -= lpEffect->m_value1;
			break;
		case EFFECT_DEFENSEDOWN:
			lpObj->m_SkillInfo.DecDefenseValue -= lpEffect->m_value1;
			break;
		case EFFECT_SWORDPOWER:
			lpObj->m_SkillInfo.SwordPowerIncVal -= lpEffect->m_value1;
			lpObj->m_SkillInfo.SwordPowerDecVal -= lpEffect->m_value2;
			break;
		case EFFECT_MAGICCIRCLE:
			lpObj->m_SkillInfo.MagicCircleVal -= lpEffect->m_value1;
			break;
		case EFFECT_FLAMESTRIKE:
			break;
		case EFFECT_GIGANTICSTORM:
			break;
		case EFFECT_LIGHTINGSHOCK:
			break;
		case EFFECT_PARALYZE:
			break;
		case EFFECT_SANTABLESS:
			lpObj->m_SkillInfo.SantaBlessingVal -= lpEffect->m_value1;
			break;
		case EFFECT_SANTAHEALING:
			lpObj->m_SkillInfo.SantaHealingVal -= lpEffect->m_value1;
			break;
		case EFFECT_SANTAPROTECTION:
			lpObj->m_SkillInfo.SantaProtectionVal -= lpEffect->m_value1;
			break;
		case EFFECT_SANTASTRENGTH:
			lpObj->m_SkillInfo.SantaStrengthVal -= lpEffect->m_value1;
			break;
		case EFFECT_SANTADEFENSE:
			lpObj->m_SkillInfo.SantaDefenceVal -= lpEffect->m_value1;
			break;
		case EFFECT_SANTAQUICKNESS:
			lpObj->m_SkillInfo.SantaQuicknessVal -= lpEffect->m_value1;
			break;
		case EFFECT_SANTAFORTUNE:
			lpObj->m_SkillInfo.SantaFortuneVal -= lpEffect->m_value1;
			break;
		case EFFECT_GLADIATORBUFF:
			lpObj->m_SkillInfo.GladiatorBuffVal -= lpEffect->m_value1;
			break;
		default:
			break;
	}
	if(lpObj->Type == OBJ_USER)
	{
		LogAddTD("[Buff Effect] (%s)(%s) Remove Effect ID: %d", lpObj->AccountID, lpObj->Name, lpEffect->m_effect);
		gObjCalCharacter(lpObj->m_Index);
	}
}

void CBuffEffect::Run()
{
	LPOBJ lpObj;

	int Tick = GetTickCount() - this->TickCount;
	if(Tick >= 1000)
	{
		this->TickCount = GetTickCount();
		for(int k=0;k<OBJMAX;++k)
		{
			lpObj = &gObj[k];
			if(gObjIsConnected(lpObj->m_Index))
			{
				TMonsterSkillElementInfo::CheckSkillElementInfoProc(lpObj);
				for(int i=0;i<MAX_PLAYER_BUFF;++i)
				{
					if(lpObj->lpEffect[i].IsEffect() == true)
					{
						if(lpObj->lpEffect[i].m_count > 0)
						{
							lpObj->lpEffect[i].m_count--;
							this->PeriodEffect(lpObj, &lpObj->lpEffect[i]);
							if(lpObj->lpEffect[i].m_count <= 0 && lpObj->lpEffect[i].m_count != -1)
							{
								if(lpObj->lpEffect[i].m_itemcode > 0)
								{
									this->DelEffect(lpObj->m_Index, lpObj->lpEffect[i].m_itemcode, lpObj->lpEffect[i].m_effectuseoption, lpObj->lpEffect[i].m_optiontype, lpObj->lpEffect[i].m_effecttype1, lpObj->lpEffect[i].m_effecttype2);
								}
								else
								{
									this->DelEffect(lpObj, lpObj->lpEffect[i].m_effect);
								}
							}
						}
					}
				}
				if(lpObj->Class == 77)
				{
					lpObj->m_SkyBossMonSheildTime++;

					if(lpObj->m_SkyBossMonSheildTime > 5)
					{
						lpObj->m_SkyBossMonSheildTime = 0;

						if(lpObj->m_SkyBossMonSheild != 0)
						{
							lpObj->m_SkyBossMonSheild = 0;
							this->DelEffect(lpObj, 64);

							GCMagicCancelSend(lpObj,16);
						}
						else
						{
							lpObj->m_SkyBossMonSheild = 1;
							this->EnableBuff(lpObj->m_Index, 64, -1, 0, 0, 0);

							GCMagicAttackNumberSend(lpObj,16,lpObj->m_Index,1);
						}
					}
				}
			}
		}
	}
}

void CBuffEffect::PeriodEffect(LPOBJ lpObj, CEffect * lpEffect)
{
	if(lpEffect->m_effect == EFFECT_SAHAMUTT || lpEffect->m_effect == EFFECT_NEIL)
	{
		gObjAttack(lpObj->lpAttackObj, lpObj, 0, 0, 0, lpEffect->m_value1, 0);
	}

	int ad,iShieldDamage = 0;

	if(lpEffect->m_effect == EFFECT_POISON)
	{
		if(lpEffect->m_count % 3 == 0)
		{
			if(lpObj->Life > 0.0f)
			{
				if(lpObj->m_SkillInfo.PoisonType == 38)
				{
					ad = lpObj->Life * 3 / 100;
				}
				else
				{
					ad = lpObj->Life * 3 / 100;
				}
			}
			else
			{
				ad = 1;
			}

			if(ad < 0)
			{
				ad = 0;
			}

			if(lpObj->lpAttackObj == NULL)
				return;

			if(g_ShieldSystemOn == 1)
			{
				if(lpObj->Type == OBJ_USER && lpObj->lpAttackObj->Type == OBJ_USER)
				{
					if(lpObj->iShield > ad)
					{
						lpObj->iShield -= ad;
						iShieldDamage = ad;
						ad = 0;
					}
					else
					{
						ad -= lpObj->iShield;
						iShieldDamage = lpObj->iShield;
						lpObj->iShield = 0;

						lpObj->Life -= ad;

						if(lpObj->Life < 0)
						{
							lpObj->Life = 0;
						}
					}
				}
				else
				{
					lpObj->Life -= ad;

					if(lpObj->Life < 0)
					{
						lpObj->Life = 0;
					}
				}
			}
			else
			{
				lpObj->Life -= ad;

				if(lpObj->Life < 0)
				{
					lpObj->Life = 0;
				}
			}

			if(lpObj->lpAttackObj != 0)
			{
				gObjLifeCheck(lpObj,lpObj->lpAttackObj,ad,2,0,0,1,iShieldDamage);
			}
		}
	}
}


void CBuffEffect::ClearBuff(LPOBJ lpObj)
{
	for(int i=0;i<MAX_PLAYER_BUFF;++i)
	{
		if(lpObj->lpEffect[i].IsEffect() == true && !this->CheckPeriodEffect(lpObj->lpEffect[i].m_effect)) // gm
		{
			if(lpObj->lpEffect[i].m_itemcode > 0)
			{
				this->DelEffect(lpObj->m_Index, lpObj->lpEffect[i].m_itemcode, lpObj->lpEffect[i].m_effectuseoption,
					lpObj->lpEffect[i].m_optiontype, lpObj->lpEffect[i].m_effecttype1, lpObj->lpEffect[i].m_effecttype2);
			}
			else
			{
				this->DelEffect(lpObj, lpObj->lpEffect[i].m_effect);
			}
		}
	}
}

void CBuffEffect::InitEffect(LPOBJ lpObj)
{
	lpObj->m_SkillInfo.PoisonType = 0;
	lpObj->m_SkillInfo.DamageRefVal = 0;
	lpObj->m_SkillInfo.SkillAddLife = 0;
	lpObj->m_SkillInfo.GladiatorBuffVal = 0;
	lpObj->m_SkillInfo.MagicCircleVal = 0;
	lpObj->m_SkillInfo.SantaBlessingVal = 0;
	lpObj->m_SkillInfo.SantaDefenceVal = 0;
	lpObj->m_SkillInfo.SantaFortuneVal = 0;
	lpObj->m_SkillInfo.SantaHealingVal = 0;
	lpObj->m_SkillInfo.SantaProtectionVal = 0;
	lpObj->m_SkillInfo.SantaQuicknessVal = 0;
	lpObj->m_SkillInfo.SantaStrengthVal = 0;
	lpObj->m_SkillInfo.DecDamageValue = 0;
	lpObj->m_SkillInfo.DecDefenseValue = 0;
	lpObj->m_SkillInfo.IceType = 0;
	lpObj->m_SkillInfo.WizardDefenseVal = 0;
}
						
bool CBuffEffect::CheckPeriodEffect(BYTE Viewport)
{
	if (
		   Viewport == EFFECT_GAMEMASTER
		|| Viewport == EFFECT_EXPDROP1_INCREASE
		|| Viewport == EFFECT_EXP1_INCREASE
		|| Viewport == EFFECT_EXP_DISABLE1
		|| Viewport == EFFECT_EXP2_INCREASE
		|| Viewport == EFFECT_EXPDROP2_INCREASE
		|| Viewport == EFFECT_EXPDISABLE2_INCREASE
		|| Viewport == EFFECT_MOBILITY
		|| Viewport == EFFECT_QUICKNESS
		|| Viewport == EFFECT_DEFENSE
		|| Viewport == EFFECT_WRATH
		|| Viewport == EFFECT_WIZARDRY
		|| Viewport == EFFECT_MANA
		|| Viewport == EFFECT_HEALTH
		|| Viewport == EFFECT_ADDSTRENGTH
		|| Viewport == EFFECT_ADDAGILITY
		|| Viewport == EFFECT_ADDVITALITY
		|| Viewport == EFFECT_ADDENERGY
		|| Viewport == EFFECT_ADDLEADERSHIP
		|| Viewport == EFFECT_SEALHELING
		|| Viewport == EFFECT_SEALDIVINITY
		|| Viewport == EFFECT_SCROLLBATTLE
		|| Viewport == EFFECT_SCROLLSTRENGTH
		|| Viewport == EFFECT_GUARDIANTALISMAN
		|| Viewport == EFFECT_ITEMPROTECTIONTALISMAN
		|| Viewport == EFFECT_MASTEREXP_INCREASE
		|| Viewport == EFFECT_MASTEREXPDROP_INCREASE
		|| Viewport == EFFECT_GLADIATORBUFF)
	{
		return true;
	}
	return false;
}

void CBuffEffect::DisableSpecificBuff(LPOBJ lpObj) // scanning lpEffect for halloween,blossom & santa buffs
{
	for(int i=0;i<MAX_PLAYER_BUFF;++i)
	{
		if(lpObj->lpEffect[i].m_effect >= EFFECT_HALLOWEEN_BLESS && lpObj->lpEffect[i].m_effect <= EFFECT_HALLOWEEN_DRINK)
		{
			this->DelEffect(lpObj->m_Index, lpObj->lpEffect[i].m_itemcode, lpObj->lpEffect[i].m_effectuseoption, lpObj->lpEffect[i].m_optiontype, lpObj->lpEffect[i].m_effecttype1, lpObj->lpEffect[i].m_effecttype2);
		}
		else if(lpObj->lpEffect[i].m_effect >= EFFECT_BLOSSOMWINE && lpObj->lpEffect[i].m_effect <= EFFECT_BLOSSOMPETAL)
		{
			this->DelEffect(lpObj->m_Index, lpObj->lpEffect[i].m_itemcode, lpObj->lpEffect[i].m_effectuseoption, lpObj->lpEffect[i].m_optiontype, lpObj->lpEffect[i].m_effecttype1, lpObj->lpEffect[i].m_effecttype2);
		}
		else if(lpObj->lpEffect[i].m_effect >= EFFECT_SANTABLESS && lpObj->lpEffect[i].m_effect <= EFFECT_SANTAFORTUNE)
		{
			this->DelEffect(lpObj->m_Index, lpObj->lpEffect[i].m_itemcode, lpObj->lpEffect[i].m_effectuseoption, lpObj->lpEffect[i].m_optiontype, lpObj->lpEffect[i].m_effecttype1, lpObj->lpEffect[i].m_effecttype2);
		}
	}
}

void CBuffEffect::ResetEffectTime(LPOBJ lpObj, CEffect * Effect, int Time)
{
	Effect->m_count = Time;
	LogAddTD("[Buff Effect] Reset Effect: %d Time: %d", Effect->m_effect, Effect->m_count);
}