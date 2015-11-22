#include "stdafx.h"
#include "GameServer.h"
#include "Shop.h"
#include "LogProc.h"
#include "..\include\readscript.h"
#include "GameMain.h"
#include "..\common\WzMemScript.h"
// GS-N 0.99.60T 0x004EF0A0
//	GS-N	1.00.18	JPN	0x00518EA0	-	Completed

CShop ShopC[MAX_SHOP];


CShop::CShop()
{
	return;
}


CShop::~CShop()
{
	return;
}

void CShop::Init()
{
	this->SendItemDataLen = 0;
	this->ItemCount = 0;
	memset(this->ShopInventoryMap, 0, sizeof(this->ShopInventoryMap));
}

BOOL CShop::InsertItem(int type, int index, int level, int dur, int op1, int op2 ,int op3, int excopt)
{
	int itemp;
	int width;
	int height;
	int x;
	int y;
	int blank;

	blank = -1;
	itemp = type * MAX_SUBTYPE_ITEMS + index;
	
	if ( itemp < 0 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 53)), __FILE__, __LINE__, type, index);
		return false;
	}
	
	ItemGetSize(itemp, width, height);

	if ( width < 0 || height < 0 )
	{
		// Error in getting item size in shop %s %d
		MsgBox(lMsg.Get(MSGGET(2, 54)), __FILE__, __LINE__);
		return FALSE;
	}

	for ( y=0;y<15;y++)
	{
		for ( x=0;x<8;x++)
		{
			if ( this->ShopInventoryMap[x + y*8] == 0 )
			{
				blank = this->InentoryMapCheck(x, y, width, height);

				if ( blank >= 0 )
				{
					goto skiploop;
				}
			}
		}
	}

	if ( blank < 0 )
	{
		MsgBox("error-L2 : %s %d", __FILE__, __LINE__);
		return FALSE;
	}

skiploop:

	this->m_item[blank].m_Level = level;

	if ( dur == 0 )
	{
		dur = ItemGetDurability(ITEMGET(type, index), level, 0, 0);
	}

	this->m_item[blank].m_Durability = dur;
	this->m_item[blank].Convert(itemp, op1, op2, op3, excopt, 0, 2, CURRENT_DB_VERSION,0);
	this->m_item[blank].Value();
	this->SendItemData[this->SendItemDataLen] = blank;
	this->SendItemData[this->SendItemDataLen+5] = 0xFF;
	this->SendItemData[this->SendItemDataLen+6] = 0xFF;
	this->SendItemData[this->SendItemDataLen+7] = 0xFF;
	this->SendItemData[this->SendItemDataLen+8] = 0xFF;
	this->SendItemData[this->SendItemDataLen+9] = 0xFF;
	this->SendItemDataLen++;
	ItemByteConvert((LPBYTE)&this->SendItemData[this->SendItemDataLen], this->m_item[blank]);
	this->SendItemDataLen += 12;
	this->ItemCount++;

	return TRUE;
}

int CShop::InentoryMapCheck(int sx, int sy, int width, int height)
{
	int x;
	int y;
	int blank = 0;

	if ( (sx+width) > 8 )
		return -1;

	if ( (sy+height) > 15 )
		return -1;

	for(y=0;y<height;y++)
	{
		for(x=0;x<width;x++)
		{
			if ( this->ShopInventoryMap[( sy + y) * 8 + (sx + x)] )
			{
				blank++;
				break;
			}
		}
	}

	if ( blank == 0 )
	{
		for(y=0;y<height;y++)
		{
			for(x=0;x<width;x++)
			{
				this->ShopInventoryMap[( sy + y) * 8 + (sx + x)] = 1;
			}
		}

		return (sx + sy*8);
	}

	return -1;
}

BOOL CShop::LoadShopItem(char* filename )
{
	int Token;
	int type;
	int index;
	int level;
	int dur;
	int op1;
	int op2;
	int op3;
	int excopt;
	this->Init();

	SMDFile = fopen(filename, "r");

	if ( SMDFile == NULL )
	{
		MsgBox("Shop data load error %s", filename);
		return FALSE;
	}

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			type = TokenNumber;

			Token = GetToken();
			index = TokenNumber;

			Token = GetToken();
			level = TokenNumber;

			Token = GetToken();
			dur = TokenNumber;

			Token = GetToken();
			op1 = TokenNumber;

			Token = GetToken();
			op2 = TokenNumber;

			Token = GetToken();
			op3 = TokenNumber;

			Token = GetToken();
			excopt = TokenNumber;

			if (this->InsertItem(type, index, level, dur, op1, op2, op3, excopt) == FALSE )
			{
				MsgBox("error-L3 : %s %s %d", filename, __FILE__, __LINE__);
			}
		}
	}

	fclose(SMDFile);
	return true;
}

BOOL ShopDataLoad()
{
	ShopC[0].LoadShopItem("..\\Data\\Shops\\LorenciaBlackSmith.txt");
	ShopC[1].LoadShopItem("..\\Data\\Shops\\LorenciaBarmid.txt");
	ShopC[2].LoadShopItem("..\\Data\\Shops\\LorenciaPassiWizzardShop.txt");
	ShopC[3].LoadShopItem("..\\Data\\Shops\\LorenciaDKPeddler.txt");
	ShopC[4].LoadShopItem("..\\Data\\Shops\\LorenciaRiverMerchant.txt");
	ShopC[5].LoadShopItem("..\\Data\\Shops\\PotionGirl.txt");
	ShopC[6].LoadShopItem("..\\Data\\Shops\\DeviasBarmid.txt");
	ShopC[7].LoadShopItem("..\\Data\\Shops\\DeviasWizard.txt");
	ShopC[8].LoadShopItem("..\\Data\\Shops\\DeviasWeaponMerchant.txt");
	ShopC[9].LoadShopItem("..\\Data\\Shops\\NoriaWeaponMerchant.txt");
	ShopC[10].LoadShopItem("..\\Data\\Shops\\NoriaElfLala.txt");
	ShopC[11].LoadShopItem("..\\Data\\Shops\\Alex(NPC230).txt");
	ShopC[12].LoadShopItem("..\\Data\\Shops\\ThomsonCannel(NPC231).txt");
	ShopC[13].LoadShopItem("..\\Data\\Shops\\SantaGirl(NPC374).txt");
	ShopC[14].LoadShopItem("..\\Data\\Shops\\ElbelandDrinkSellerHillary.txt");
	ShopC[15].LoadShopItem("..\\Data\\Shops\\ElbelandDrinkSellerLindsay.txt");
	ShopC[16].LoadShopItem("..\\Data\\Shops\\FireworksGirl(NPC379).txt");
	ShopC[17].LoadShopItem("..\\Data\\Shops\\Sylvia(NPC415).txt");
	ShopC[18].LoadShopItem("..\\Data\\Shops\\Leah(NPC416).txt");
	ShopC[19].LoadShopItem("..\\Data\\Shops\\Marseille(NPC417).txt");
	ShopC[20].LoadShopItem("..\\Data\\Shops\\MossMerchant.txt");
	ShopC[21].LoadShopItem("..\\Data\\Shops\\ChristinaTheMerchant(NPC545).txt");
	ShopC[22].LoadShopItem("..\\Data\\Shops\\JewelerRaul(NPC546).txt");
//	ShopC[20].LoadShopItem(38);
	LogAdd("[IGC] Shop information loaded");
	//LogAdd(lMsg.Get(MSGGET(1, 209)));

	return TRUE;
}