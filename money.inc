/*

Old, custom money system by fiki574

NOTE:
Extremely crappy, outdated and laggy. Use on your own!

*/

#if defined _money_included
	#endinput
#endif
#define _money_included
#include <Dini>

new Text:MoneyTD[MAX_PLAYERS];
new Text:MoneyTD2[MAX_PLAYERS];
new Text:MoneyTD3[MAX_PLAYERS];
new PCash[MAX_PLAYERS];
new file[100];

/*Natives:
native GiveMoney(playerid,ammount);
native TakeMoney(playerid,ammount);
native SetMoney(playerid,ammount);
native ResetMoney(playerid);
native GetMoney(playerid);
*/

forward M_OnGameModeInit();
public OnGameModeInit()
{
	for(new playerid=0; playerid < MAX_PLAYERS; playerid++)
    {
        MoneyTD[playerid] = TextDrawCreate(498.000000, 88.000000,"_");
		TextDrawBackgroundColor(MoneyTD[playerid], 255);
		TextDrawFont(MoneyTD[playerid], 1);
		TextDrawLetterSize(MoneyTD[playerid], 0.500000, 1.000000);
		TextDrawColor(MoneyTD[playerid], -1);
		TextDrawSetOutline(MoneyTD[playerid], 0);
		TextDrawSetProportional(MoneyTD[playerid], 1);
		TextDrawSetShadow(MoneyTD[playerid], 1);
		TextDrawUseBox(MoneyTD[playerid], 1);
		TextDrawBoxColor(MoneyTD[playerid], 255);
		TextDrawTextSize(MoneyTD[playerid], 625.000000, 480.000000);
		
		MoneyTD2[playerid] = TextDrawCreate(498.000000, 78.000000,"_");
		TextDrawBackgroundColor(MoneyTD2[playerid], 255);
		TextDrawFont(MoneyTD2[playerid], 1);
		TextDrawLetterSize(MoneyTD2[playerid], 0.500000, 1.000000);
		TextDrawColor(MoneyTD2[playerid], -1);
		TextDrawSetOutline(MoneyTD2[playerid], 0);
		TextDrawSetProportional(MoneyTD2[playerid], 1);
		TextDrawSetShadow(MoneyTD2[playerid], 1);
		TextDrawUseBox(MoneyTD2[playerid], 1);
		TextDrawBoxColor(MoneyTD2[playerid], 255);
		TextDrawTextSize(MoneyTD2[playerid], 625.000000, 480.000000);
		
		MoneyTD3[playerid] = TextDrawCreate(498.000000, 83.000000,"_");
		TextDrawBackgroundColor(MoneyTD3[playerid], 255);
		TextDrawFont(MoneyTD3[playerid], 3);
		TextDrawLetterSize(MoneyTD3[playerid], 0.750000, 1.800000);
		TextDrawColor(MoneyTD3[playerid], -1);
		TextDrawSetOutline(MoneyTD3[playerid], 0);
		TextDrawSetProportional(MoneyTD3[playerid], 1);
		TextDrawSetShadow(MoneyTD3[playerid], 1);
		TextDrawUseBox(MoneyTD3[playerid], 1);
		TextDrawBoxColor(MoneyTD3[playerid], 255);
		TextDrawTextSize(MoneyTD3[playerid], 625.000000, 480.000000);
		
		if(funcidx("M_OnGameModeInit") != -1) CallLocalFunction("M_OnGameModeInit", "");
	}
	return 1;
}
#if defined _ALS_OnGameModeInit
        #undef OnGameModeInit
#else
        #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit M_OnGameModeInit

forward M_OnPlayerConnect(playerid);
public OnPlayerConnect(playerid)
{
	TextDrawShowForPlayer(playerid,MoneyTD2[playerid]);
	TextDrawShowForPlayer(playerid,MoneyTD[playerid]);
	TextDrawShowForPlayer(playerid,MoneyTD3[playerid]);	
	new playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid,playername,sizeof(playername));
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",playername);
	if(dini_Exists(file))
	{
		PCash[playerid] = dini_Int(file,"Money");
	}
	if(funcidx("M_OnPlayerConnect") != -1) CallLocalFunction("M_OnPlayerConnect", "i", playerid);
	return 1;
}
#if defined _ALS_OnPlayerConnect
        #undef OnPlayerConnect
#else
        #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect M_OnPlayerConnect

forward M_OnPlayerUpdate(playerid);
public OnPlayerUpdate(playerid)
{
	new cashstr[100];
	format(cashstr,sizeof(cashstr),"~g~$~w~%d", PCash[playerid]);
	TextDrawSetString(MoneyTD3[playerid],cashstr);
	new playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid,playername,sizeof(playername));
	format(file,sizeof(file),"/Players/%s.txt",playername);
	if(dini_Exists(file))
	{
		dini_IntSet(file, "Money", PCash[playerid]);
	}
	if(funcidx("M_OnPlayerUpdate") != -1) CallLocalFunction("OnPlayerUpdate", "i", playerid);
	return 1;
}
#if defined _ALS_OnPlayerUpdate
        #undef OnPlayerUpdate
#else
        #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate M_OnPlayerUpdate

stock GiveMoney(playerid,ammount)
{
	PCash[playerid] += ammount;
	return 1;
}

stock TakeMoney(playerid,ammount)
{
	PCash[playerid] -= ammount;
	return 1;
}

stock SetMoney(playerid,ammount)
{
	PCash[playerid] = ammount;
	return 1;
}

stock ResetMoney(playerid)
{
	PCash[playerid] = 0;
	return 1;
}

stock GetMoney(playerid)
{
	return PCash[playerid];
}