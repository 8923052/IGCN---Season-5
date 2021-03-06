//------------------------------------------
// GameServer.cpp
// Webzen Mu Game Server
// Date: 02-02-2007
// Decompilation by: Deathway
// Description : Main entry of the Program, 
//				 Start all servers
//------------------------------------------
//	GS-N	1.00.18	JPN	0x0052D520	-	Completed
#include "stdafx.h"
#include "MonsterHerd.h"
#include "resource.h"
#include "GameServer.h"
#include "Gamemain.h"
#include "Giocp.h"
#include "logproc.h"
#include "RingAttackEvent.h"
#include "CWhatsUpDummyServer.h"
#include "DBSockMng.h"
#include "DSProtocol.h"
#include "EDSProtocol.h"
#include "SProtocol.h"
#include "ChaosCastle.h"
#include "Protocol.h"
#include "AcceptIP.h"
#include "user.h"
#include "closeplayer.h"
#include "MapServerManager.h"
#include "protocol.h"
#include "Shop.h"
#include "Weapon.h"
#include "CastleSiegeSync.h"
#include "BloodCastle.h"
#include "EledoradoEvent.h"
#include "EventManagement.h"
#include "CashShop.h"
#include "TServerInfoDisplayer.h"
#include "TMonsterAI.h"
#include "Kanturu.h"
#include "XMasEvent.h"
#include "DuelManager.h"
#include "HappyHour.h"
#include "IllusionTemple.h"
#include "CastleSiege.h"
#include "CastleDeepEvent.h"
#include "Crywolf.h"
#include "DoubleGoer.h"
#include "Raklion.h"
#include "PropertyItem.h"
#include "Imperial.h"
#include "BuffEffect.h"
#include "protection.h"
//#include "protect.h"

char ExDbIp[256];
char DataServerIp2[256];
char DataServerIp[256];
char JoinServerIp[256];
int gServerReady;
int gCloseMsg;
int gCloseMsgTime;
int gCurPaintPlayer;
int gCurPaintType;
int gCurPaintMapNumber;




CRingMonsterHerd g_MonsterHerdTest;
CRingAttackEvent g_RingAttackEvent;
CWhatsUpDummyServer gWhatsUpDummyServer;

HINSTANCE hInst; // Current Instance
HWND ghWnd;

char szTitle[100];
char szWindowClass[64];




BOOL GameServerStart(void);
int InitInstance(HINSTANCE, int);	// Init GameServer
ATOM MyRegisterClass(HINSTANCE);	// Register Window Class
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);// Brain of the GameServer
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//#pragma pack(2)
//#pragma pack(show)  // C4810


#if (GS_PROTECTED==1)
DWORD GetFunctionRVA(void* FuncName)
{
      void *_tempFuncName=FuncName;
      char *ptempFuncName=PCHAR(_tempFuncName);
      DWORD _jmpdwRVA,dwRVA;
      CopyMemory(&_jmpdwRVA,ptempFuncName+1,4);
      dwRVA=DWORD(ptempFuncName)+_jmpdwRVA+5;
      return(dwRVA);
}

DWORD GetFunctionSize(void* FuncName)
{
      /*DWORD dwRVA=GetFunctionRVA(FuncName);
      char* pFuncBody=PCHAR(dwRVA);
      UCHAR _temp;
      bool notEnd=TRUE;
      char *DepackerCodeEnd=new TCHAR[10];
      DWORD l=0;
      do
      {
            CopyMemory(&_temp,pFuncBody+l,1);
            if(_temp==0xC3)
            {
                  CopyMemory(DepackerCodeEnd,pFuncBody+l+0x01,10);
                  DepackerCodeEnd[9]=0x00;
                  if(strcmp(DepackerCodeEnd,"ETGXZKATZ")==0)
                  {
                        notEnd=FALSE;
                  }
            }
            l++;
      }while(notEnd);
      return(l);*/
	DWORD dwConstant = 0x3456933F;
	DWORD dwOtherConstant = 0x5C39FD51;
	dwConstant--;
	dwOtherConstant--;
	dwConstant = dwConstant + dwOtherConstant + 2;

	DWORD dwSize = 0;
	DWORD dwRVA = (DWORD)FuncName;

	while ( *(DWORD *)(dwRVA+dwSize) != dwConstant )
	{
		dwSize++;
	}

	return dwSize;
}


#define KEY_LEN	20
static unsigned char Key[KEY_LEN] = { 0xAF, 0x23, 0x4F, 0x7D,0x98, 0x0D,0x3D, 0xCC,0xE1, 0xB6,
								 0x15, 0xDE, 0x8A, 0x67,0x1E, 0x4C,0x24, 0xFA,0x32, 0xF4 };

BOOL UnProtectProtocolCore()
{
	DWORD dwOldProtect;
	DWORD dwSize = GetFunctionSize(ProtocolCore);
	
	if ( VirtualProtect(ProtocolCore, dwSize, PAGE_EXECUTE_READWRITE, &dwOldProtect) == FALSE )
	{
		return FALSE;
	}

	LPBYTE Temp = (LPBYTE)(ProtocolCore);

	for ( DWORD dwCount = 0 ; dwCount < dwSize ; dwCount++)
	{
		Temp[ dwCount ] ^= Key [ dwCount % KEY_LEN ];
	}

	return TRUE;
}
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

/*-----------------------------------------
    GameServer.exe
	Company: Webzen
	Country: Korea
	Decompiled by: Deathway
------------------------------------------*/

	MSG msg;
	HACCEL hAccelTable;

	if(!Check())
	{
		MessageBox(NULL,"Files not licensed","license fail", MB_OK|MB_ICONHAND|MB_APPLMODAL);
		return 0;
	}
/*	HANDLE hMutex=CreateMutex(NULL, FALSE, "WZ_MU_GS_MUTEX");
	if (GetLastError()==ERROR_ALREADY_EXISTS) 
	{
		CloseHandle(hMutex);
		MessageBox(NULL, "Webzen Mu Game Server is already Running.","Error", MB_OK|MB_ICONHAND|MB_APPLMODAL);
		return 0;
	}*/

	// Check if the original language == KOREA
	if (gLanguage==0) 
	{
		WIN32_FIND_DATA  wfd;	// Nice trick from WebZen local Scope
		if (FindFirstFile(COMMONSERVER_PATH,&wfd)==INVALID_HANDLE_VALUE)
		{
			//MsgBox(COMMONSERVER_PATH);
			MessageBox(NULL, "Cannot find M:\\ Drive.", "Error", MB_OK|MB_ICONHAND|MB_APPLMODAL);
			return 0; 
		}
	}	
	//Load Title and WindowClass Name
	LoadString(hInstance,IDS_APP_TITLE, szTitle, 100);
	LoadString(hInstance,IDS_GAMESERVER, szWindowClass, 100);

	MyRegisterClass(hInstance);

	InitCommonControls();
	
	// Check if error ocurs
	if (!InitInstance(hInstance, nCmdShow))
	{
		return 0;
	}

	ShowWindow(ghWnd, SW_SHOWMAXIMIZED);// Showm GameServer Window

	hAccelTable=LoadAccelerators(hInstance,(LPCSTR)IDA_GAMESERVER);// Load Accelerators

	GiocpInit();
	GameMainInit(ghWnd);

#if (TEST_PROCEDURES==1)
	LogTextPaintProc(ghWnd);
	gObjViewportPaint( ghWnd, OBJ_STARTUSERINDEX);
	GameServerStart();
#endif


	WORD serverport;	// Server Port

	memset(DataServerIp2, 0, sizeof(DataServerIp2));
	memset(ExDbIp, 0, sizeof(ExDbIp));
	DataServerPort2=0;
	ExDbPort=0;

	// Port Configuration from Cmd Line
	if (strlen(lpCmdLine)>1) 
	{
		sscanf(lpCmdLine, "%s %d %s %d %d %s %d %s %d" ,JoinServerIp, &JoinServerPort, DataServerIp, &DataServerPort, &serverport, DataServerIp2, &DataServerPort2, ExDbIp, &ExDbPort);
	}
	else 
	{ 
		serverport=55900;
		JoinServerPort=55970;
		DataServerPort=55960;
		DataServerPort2=55962;
		ExDbPort=55906;
		MsgBox(lMsg.Get( MSGGET(0, 114)) );
	}
	
	if ( DataServerIp2[0] == 0 )
		memcpy(DataServerIp2, DataServerIp, sizeof(DataServerIp2));

	if ( DataServerPort2 == 0 )
		DataServerPort2 = 55962;

	if ( ExDbIp[0] == 0 )
		memcpy(ExDbIp, DataServerIp, sizeof(ExDbIp));

	if ( ExDbPort == 0 )
		ExDbPort = 55906;

	GameServerPort=serverport; 
	gWhatsUpDummyServer.Start(ghWnd, GameServerPort+1);
	AllServerStart();

	// Main Message Loop
	while(GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (!TranslateAccelerator(msg.hwnd,hAccelTable,&msg))
		{
		    TranslateMessage(&msg);
		    DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}


		
BOOL AllServerStart(void){
	
	if (JoinServerConnected==0)
	{
		if (GMJoinServerConnect(JoinServerIp, WM_GM_JOIN_CLIENT_MSG_PROC) == 0)
		{	
			// LoginServer connect fail
			MsgBox(lMsg.Get(MSGGET(1, 144)));
			return 0;
		}
	}

	if ((DevilSquareEventConnect==0) && (IsDevilSquareEventConnected==0))
	{
		if (GMRankingServerConnect(gDevilSquareEventServerIp, WM_GM_RANKING_CLIENT_MSG_PROC) == 0)
		{
			MsgBox("Ranking Server is not respomding");
			return 0;
		}
		IsDevilSquareEventConnected=1;
	}

	if ((EventChipServerConnect!=0) && (IsEventChipServerConnected==0))
	{
		if (GMEventChipServerConnect(gEventChipServerIp, WM_GM_EVENTCHIP_CLIENT_MSG_PROC) == 0)
		{
			MsgBox("Event Chip Server is not respomding");
			return 0;
		}
		IsEventChipServerConnected=1;
	}

	
	cDBSMng.Connect();
	return TRUE;
}



BOOL GameServerStart(void) 
{
	if (GameMainServerCreate(WM_GM_SERVER_MSG_PROC, WM_GM_CLIENT_MSG_PROC) == FALSE )
	{
		MsgBox(lMsg.Get(MSGGET( 1, 142) ));
		return FALSE;
	}


	CreateGIocp(GameServerPort);

	SetTimer(ghWnd, WM_LOG_PAINT, 2000, NULL);
	SetTimer(ghWnd, WM_FIRST_MSG_PROCESS, 1000, NULL);

	SetTimer(ghWnd, WM_SET_DATE, 60000, NULL);
	SetTimer(ghWnd, WM_LOG_DATE_CHANGE, 60000, NULL);
	SetTimer(ghWnd, WM_CONNECT_DATASERVER, 10000, NULL);


	SetTimer(ghWnd, WM_SECOND_MSG_PROCESS, 1000, NULL);
	SetTimer(ghWnd, WM_GS_CLOSE, 1000, NULL);
	SetTimer(ghWnd, WM_MONSTER_AND_MSG_PROC, 500, NULL);


	SetTimer(ghWnd, WM_MOVE_MONSTER_PROC, 300, NULL);
	SetTimer(ghWnd, WM_EVENT_RUN_PROC, 100, NULL);

	SetTimer(ghWnd, WM_AI_MONSTER_MOVE_PROC, 100, NULL);
	SetTimer(ghWnd, WM_AI_MONSTER_PROC, 1011, NULL);

	SetTimer(ghWnd, WM_GUILD_LIST_REQUEST, 1000, NULL);

	return TRUE;
}




//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_NORMAL_V1);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDR_MENU;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON_MINIMIZED);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HWND hWnd;
	hInst=hInstance;


    hWnd = CreateWindowEx(
        0,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT,0,
        NULL, NULL, hInstance, NULL);
	
	if (hWnd==0) 
	{
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	ghWnd=hWnd;
	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INT wmId, wmEvent;
	
	switch (message) 
	{
		case WM_CREATE:
			//gWhatsUpDummyServer.Start(hWnd, 55902);
			return 0;
		case WM_COMMAND:
			wmId    = wParam & 0xFFFF & 0xFFFF; 
			wmEvent = (wParam >> 16) & 0xFFFF; 
					
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUT_BOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   SendMessage(hWnd, WM_CLOSE, 0, 0);
				   break;
				case IDM_CLOSE_PLAYER:
					{
						Ccloseplayer closeplayer;
						closeplayer.Load("closeplayer.txt");
					}
					break;
				case IDM_ALL_USER_CLOSE:
					gObjAllDisconnect();
					break;
				case IDM_ALL_USER_LOGOUT:
					gObjAllLogOut();
					break;
				case IDM_MONSTER_POSITION_RELOAD:
					GameMonsterAllCloseAndReLoad();
					break;
				case IDM_SHOP_RELOAD:
					ShopDataLoad();
					break;
				case IDM_MAP_SERVER_INFO_RELOAD:
					g_MapServerManager.LoadData(gDirPath.GetNewPath("MapServerInfo.dat") );
					break;
				case IDM_IP_LOAD:
					acceptIP.Load(gDirPath.GetNewPath("Iplist.dat"));
					break;
				case IDM_OPTION_RELOAD:
					ReadCommonServerInfo();
					break;
				case IDM_CASHSHOP_OPTION_RELOAD:
					g_CashShop.CashShopOptioNReload();
					break;
				case IDM_LOG_PAINT:
					gCurPaintType=0;
					break;
				case IDM_MAP1:
					gCurPaintMapNumber = 0;	// Lorencia
					gCurPaintType=1;
					break;
				case IDM_MAP2:
					gCurPaintType=1;
					gCurPaintMapNumber = 2;	// Dungeon
					break;
				case IDM_MAP3:
					gCurPaintType=1;
					gCurPaintMapNumber = 3;	// Devias
					break;
				case IDM_MAP4:
					gCurPaintType=1;
					gCurPaintMapNumber = 4;	// Noria
					break;
				case IDM_CRYWOLF:
					gCurPaintType=1;
					gCurPaintMapNumber = 65;	// Crywolf
					break;
	/*			case ID_VIEW_DG6:
					gCurPaintType=1;
					gCurPaintMapNumber = 34;	// Crywolf
					break;*/
				case IDM_DRAGON_EVENT:
					if (  DragonEvent->GetState() != 0 )
						DragonEvent->End();
					else
						DragonEvent->Start();
					break;
				case IDM_STARTOFXMAS_EVENT:
					if ( gXMasEvent != 0 )
						gXMasEvent = 0;
					else
						gXMasEvent=1;
					break;
				case IDM_FIRECRACKER:
					if ( gFireCrackerEvent != 0 )
					{
						gFireCrackerEvent = 0;
						LogAdd("FireCrack event stop");
					}
						
					else
					{
						gFireCrackerEvent=1;
						LogAdd("FireCrack event start");
					}
					break;
				case IDM_5_MINUTE_CLOSE:
					if ( gCloseMsg == 0 )
					{
						gCloseMsgTime = 300;
						gCloseMsg=1;
						AllSendServerMsg( lMsg.Get(MSGGET(4, 104)) );
					}
					break;
				case IDM_3_MINUTE_CLOSE:
					if ( gCloseMsg == 0 )
					{
						gCloseMsgTime = 180;
						gCloseMsg=2;
						AllSendServerMsg(lMsg.Get(MSGGET(4, 105)) );
					}
					break;
				case IDM_1_MINUTE_CLOSE:
					if ( gCloseMsg == 0 )
					{
						gCloseMsgTime = 60;
						gCloseMsg=3;
						AllSendServerMsg(lMsg.Get(MSGGET(4, 106)) );
					}
					break;
				case IDM_RELOAD_ALL_EVENT:
					ReadEventInfo(MU_EVENT_ALL );
					break;
				case IDM_RELOAD_DEVILSQUARE:
					ReadEventInfo(MU_EVENT_DEVILSQUARE );
					break;
				case IDM_RELOAD_BLOODCASTLE:
					ReadEventInfo(MU_EVENT_BLOODCASTLE );
					break;
				case IDM_RELOAD_UNDERWORLD_ATTACK:
					ReadEventInfo(MU_EVENT_ATTACKEVENTTROOP );
					break;
				case IDM_RELOAD_GOLDENTROOP_ATTACK:
					ReadEventInfo(MU_EVENT_GOLDENTROOP );
					break;
				case IDM_RELOAD_WHITEMAGE_ATTACK:
					ReadEventInfo(MU_EVENT_WHITEMAGETROOP );
					break;
				case IDM_RELOAD_LOVE_PANGPANG:
					ReadEventInfo(MU_EVENT_LOVEPANGPANG );
					break;
				case IDM_RELOAD_FIRECRACKER:
					ReadEventInfo(MU_EVENT_FIRECRACKER );
					break;
				case IDM_RELOAD_XMAS_STAR:
					ReadEventInfo(MU_EVENT_XMASSTAR );
					break;
				case IDM_RELOAD_HEART_OF_LOVE:
					ReadEventInfo(MU_EVENT_HEARTOFLOVE );
					break;
				case IDM_RELOAD_NPC_SAY_HAPPY_NEW_YEAR:
					ReadEventInfo(MU_EVENT_SAY_HAPPYNEWYEAR );
					break;
				case IDM_RELOAD_NPC_SAY_MERRY_XMAS:
					ReadEventInfo(MU_EVENT_SAY_MERRYXMAS );
					break;
				case IDM_RELOAD_CHAOSCASTLE:
					ReadEventInfo(MU_EVENT_CHAOSCASTLE );
					break;
				case IDM_RELOAD_CHRISTMAS_RIBBONBOX:
					ReadEventInfo(MU_EVENT_CHRISTMAS_RIBBONBOX );
					break;
				case IDM_RELOAD_VALENTINE_DAY_CHOCOLATE_BOX:
					ReadEventInfo(MU_EVENT_VALENTINESDAY_CHOCOLATEBOX );
					break;
				case IDM_RELOAD_WHITE_DAY_CANDY_BOX:
					ReadEventInfo(MU_EVENT_WHITEDAY_CANDYBOX  );
					break;
				case IDM_RELOAD_ALL_ETC_OPTION:
					ReadGameEtcInfo(MU_ETC_ALL );
					break;
				case IDM_RELOAD_CREATE_CHARACTER:
					ReadGameEtcInfo(MU_ETC_CREATECHARACTER );
					break;
				case IDM_RELOAD_GUILD:
					ReadGameEtcInfo(MU_ETC_GUILD );
					break;
				case IDM_RELOAD_TRADE:
					ReadGameEtcInfo(MU_ETC_TRADE );
					break;
				case IDM_RELOAD_CHAOSBOX:
					ReadGameEtcInfo(MU_ETC_USECHAOSBOX );
					break;
				case IDM_RELOAD_PERSONAL_SHOP:
					ReadGameEtcInfo(MU_ETC_PERSONALSHOP );
					break;
				case IDM_RELOAD_PK_ITEM_DROP:
					ReadGameEtcInfo(MU_ETC_PKITEMDROP );
					break;
				case IDM_RELOAD_ITEM_DROP_RATE:
					ReadGameEtcInfo(MU_ETC_ITEMDROPRATE );
					break;
				case IDM_RELOAD_SPEEDHACK:
					ReadGameEtcInfo(MU_ETC_SPEEDHACK );
					break;
				case IDM_RELOAD_GAMEGUARD_CHECKSUM_CHECK:
					ReadGameEtcInfo(MU_ETC_GAMEGUARD );
					break;
				case IDM_CASTLE_SIEGE_RELOAD:
					if( g_CastleSiege.Ready(g_MapServerManager.GetMapSvrGroup()) == TRUE )
					{
						if( g_CastleSiege.LoadData(gDirPath.GetNewPath("MuCastleData.dat")) )
						{
							g_CastleSiege.LoadPreFixData(gDirPath.GetNewPath("commonserver.cfg"));
							g_CastleSiege.SetDataLoadState(CASTLESIEGE_DATALOAD_2);
						}
					}
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
					break;
			}
			break;
		case WM_GM_SERVER_MSG_PROC:
			GMServerMsgProc(wParam, lParam);
			break;
		case WM_GM_CLIENT_MSG_PROC:
			{
				int wp = wParam;
				int lp = lParam;
				GMClientMsgProc(wParam, lParam);
			}
			break;
		case WM_GM_JOIN_CLIENT_MSG_PROC:
			GMJoinClientMsgProc(wParam, lParam);
			break;
		case WM_GM_RANKING_CLIENT_MSG_PROC:
			GMRankingClientMsgProc(wParam, lParam);
			break;
		case WM_GM_EVENTCHIP_CLIENT_MSG_PROC:
			GMEventChipClientMsgProc(wParam, lParam);
			break;
		case WM_GM_DATA1_CLIENT_MSG_PROC:
			cDBSMng.MsgProc(0, wParam, lParam);
			break;
		case WM_GM_DATA2_CLIENT_MSG_PROC:
			cDBSMng.MsgProc(1, wParam, lParam);
			break;
		case WM_GM_EXDATA_CLIENT_MSG_PROC:
			ExDataClientMsgProc(wParam, lParam);
			break;
		case WM_START_SERVER:
			if ( gServerReady == 2 )
				GameServerStart();
			break;
		case WM_TIMER:
			switch ( wParam )
			{
				case WM_GUILD_LIST_REQUEST:
					DGGuildListRequest();
					KillTimer(ghWnd, WM_GUILD_LIST_REQUEST);
					break;
				case WM_LOG_PAINT:
					{
						RECT rect;
						HDC hdc = GetDC(hWnd);
						GetClientRect(hWnd, &rect);
						FillRect(hdc, &rect, (HBRUSH)GetStockObject(0));
						ReleaseDC(hWnd, hdc);

						if ( gCurPaintType == 0)
						{
							if ( LogTextPaint != NULL )
							{
								LogTextPaint(hWnd);
							}
						}
						
						gObjViewportPaint(hWnd, gCurPaintPlayer);
						g_ServerInfoDisplayer.Run(hWnd);
						GJNotifyMaxUserCount();
					}
					break;
				case WM_MONSTER_AND_MSG_PROC:
					MonsterAndMsgProc();
					break;
				case WM_MOVE_MONSTER_PROC:
					MoveMonsterProc();
					g_Kanturu.UserMonsterCountCheck();
					break;
				case WM_EVENT_RUN_PROC: 
					g_BloodCastle.Run();
					g_RingAttackEvent.Run();
					g_ChaosCastle.Run();
					g_CsNPC_Weapon.WeaponAttackProc();
					g_Kanturu.Run();
					g_PropItems.Run();
					gCXMasEvent.XMasEventRun();
					g_DuelManager.Run();
					g_HappyHour.Run();
					g_IllusionTemple.Run();
					g_CastleSiege.Run();
					g_CastleDeepEvent.Run();
					g_Crywolf.Run();
					g_DoppelGanger.Run();
					//g_Raklion.Run();
					g_Raklion.Run();
					g_Imperial.Run();
					g_IllusionTemple.Run();
					BuffEffectC.Run();
					if(!Check())
					{
						for(int i=0;i<OBJ_MAXMONSTER;i++)
						{
							delete &gObj[i];
						}
						__asm 
						{ 
							mov eax,0x00030
							call eax;
						}
					}
					break;
				case WM_AI_MONSTER_MOVE_PROC:
					TMonsterAI::MonsterMoveProc();
					break;
				case WM_AI_MONSTER_PROC:
					TMonsterAI::MonsterAIProc();
					break;
int n;
      case WM_FIRST_MSG_PROCESS:

            {

            for( n = 0; n < OBJMAX; n++ )

                  {
                     gObjStateSetCreate(n);
                     gObjViewportListDestroy(n);
                     gObjViewportListCreate(n);
				     gObjViewportListProtocol(n);
					 
					 if( n >= OBJ_STARTUSERINDEX )
						{
						//GCStateInfoSend(&gObj[n],1,40);
					if ( gDoPShopOpen )
							{
						PShop_ViewportListRegenarate(n);

					if( gObjIsConnected(n) != PLAYER_EMPTY )

							gObj[n].m_bPShopItemChange = false;

								}
							 gObjUnionUpdateProc(n);
								}
								}
							gObjSetState();
						GameServerInfoSend();


			}
					break;

				case WM_SECOND_MSG_PROCESS:
					{
						for (int n = 0;n<MAX_NUMBER_MAP;n++)
						{
							MapC[n].WeatherVariationProcess();
						}
						wsGServer.m_SendSec = wsGServer.m_SendSecTmp;
						wsGServer.m_RecvSec = wsGServer.m_RecvSecTmp;
						wsGServer.m_SendSecTmp = 0;
						wsGServer.m_RecvSecTmp = 0;
						DragonEvent->Run();
						AttackEvent->Run();
						gEledoradoEvent.Run();
						g_EventManager.Run();
					}
					break;
				case WM_GS_CLOSE:
					if ( gCloseMsg != 0 )
					{
						gCloseMsgTime--;

						if ( gCloseMsgTime <= 1 )
						{
							if ( gCloseMsgTime == 1 )
							{
								AllSendServerMsg(lMsg.Get(MSGGET(1, 193)));
								LogAddC(2, lMsg.Get(MSGGET(1, 193)));
							}
						}
						else
						{
							if ( (gCloseMsgTime % 10) == 0 )
							{
								char szTemp[256];

								wsprintf( szTemp, lMsg.Get(MSGGET(1, 194)), gCloseMsgTime);
								AllSendServerMsg(szTemp);
								LogAddC(2, szTemp);
							}
						}

						if ( gCloseMsgTime < 0 )
						{
							KillTimer(ghWnd, WM_GS_CLOSE);
							gObjAllLogOut();
							gCloseMsgTime = 0;
							gCloseMsg = 0;
						}
					}
					gObjSecondProc();
					if( cDBSMng.m_ActiveServer > DS_UNINITIALIZED && g_CastleSiege.GetDataLoadState() == 2 )
					{
						g_CastleSiege.DataRequest();
					}
					
					g_CastleSiege.SendCastleStateSync();
					g_CastleSiegeSync.AdjustTributeMoney();
					g_Crywolf.CrywolfSecondAct();
					break;
				case WM_SET_DATE:
					gSetDate();
					WhisperCash.TimeCheckCashDelete();
					break;
				case WM_CONNECT_DATASERVER:
					cDBSMng.Connect();
					gObjCheckAllUserDuelStop();
					break;
				case WM_LOG_DATE_CHANGE:
					LogDateChange();
					break;
			}
			break;
		case WM_CLOSE:
			if ( gLanguage != 3 )
			{
				if (MessageBox(ghWnd, "GameServer close?", "Close", MB_YESNO|MB_APPLMODAL) == IDYES)
				{
					DestroyWindow(hWnd);
				}
			}
			else
			{
				DestroyWindow(hWnd);
			}
			break;
		case WM_KEYDOWN:
			switch ( wParam )
			{
				case 'p':
					gCurPaintPlayer--;
					if ( gCurPaintPlayer<0)
						gCurPaintPlayer=0;
					break;
				case 'q':
					gCurPaintPlayer++;
					if ( gCurPaintPlayer > OBJMAX -1 )
						gCurPaintPlayer = OBJMAX -1;
					break;
				case 't':
					gServerMaxUser -= 10;
					if ( gServerMaxUser < 10 )
						gServerMaxUser = 10;
					break;

				case 'u':
					gServerMaxUser += 10;
					if ( gServerMaxUser > 1500 )
						gServerMaxUser = 1500;
					break;
				case 'v':
					{
						PMSG_CHARMAPJOIN szMsg;
						strcpy(szMsg.Name, "�׽�Ʈ");		// Test
						CGPCharacterMapJoinRequest(&szMsg, 0);
					}
					break;
			}
			break;
		case WM_DESTROY:
			GameMainFree();
			GiocpDelete();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}


// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if ( ( wParam & 0xFFFF & 0xFFFF ) == IDOK || (wParam & 0xFFFF & 0xFFFF ) == IDCANCEL) 
			{
				EndDialog(hDlg, (wParam& 0xFFFF & 0xFFFF ));
				return TRUE;
			}
			break;
	}
    return FALSE;
}


