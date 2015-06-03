/*

4 different cam views by fiki574

*/

#if defined _views_included
	#endinput
#endif
#define _views_included
#include <ZCMD>

new inBird[MAX_PLAYERS];
new inFrog[MAX_PLAYERS];
new inFP[MAX_PLAYERS];
new inFree[MAX_PLAYERS];

/*Natives:
native SetPlayerView(playerid,cam_view);
*/

stock SetPlayerView(playerid,cam_view)
{
	switch(cam_view)
	{
		case 0:
		{
			SetCameraBehindPlayer(playerid);
			SendClientMessage(playerid,-1,"Custom view disabled!");
			inBird[playerid] = 0;
			inFrog[playerid] = 0;
			inFP[playerid] = 0;
			inFree[playerid] = 0;
		}
		case 1:
		{
			if(!IsPlayerInAnyVehicle(playerid))
			{
				if(inBird[playerid] == 0)
				{
					inBird[playerid] = 1;
					inFrog[playerid] = 0;
					inFP[playerid] = 0;
					new Float:X;
					new Float:Y;
					new Float:Z;
					GetPlayerPos(playerid,X,Y,Z);
					SetPlayerCameraPos(playerid,X,Y,Z+12);
					SetPlayerCameraLookAt(playerid,X,Y,Z);
					SendClientMessage(playerid,-1,"Bird view enabled!");
					return 1;
				}
				else SendClientMessage(playerid,-1,"ERROR: You are already in Bird View!");
			}
			else SendClientMessage(playerid,-1,"ERROR: You cant activate Bird View while in vehicle!");
		}
		case 2:
		{
			if(!IsPlayerInAnyVehicle(playerid))
			{
				if(inFrog[playerid] == 0)
				{
					inFrog[playerid] = 1;
					inBird[playerid] = 0;
					inFP[playerid] = 0;
					inFree[playerid] = 0;
					new Float:X;
					new Float:Y;
					new Float:Z;
					GetPlayerPos(playerid,X,Y,Z);
					SetPlayerCameraPos(playerid,X,Y,Z-2);
					SetPlayerCameraLookAt(playerid,X,Y,Z+0.5);
					SendClientMessage(playerid,-1,"Frog view enabled!");
					return 1;
				}
				else SendClientMessage(playerid,-1,"ERROR: You are already in Frog View!");
			}
			else SendClientMessage(playerid,-1,"ERROR: You cant activate Frog View while in vehicle!");
		}
		case 3:
		{
			if(!IsPlayerInAnyVehicle(playerid))
			{
				if(inFP[playerid] == 0)
				{
					inFP[playerid] = 1;
					inFrog[playerid] = 0;
					inBird[playerid] = 0;
					inFree[playerid] = 0;
					new Float:X;
					new Float:Y;
					new Float:Z;
					GetPlayerPos(playerid,X,Y,Z);
					SetPlayerCameraPos(playerid,X,Y,Z);
					SetPlayerCameraLookAt(playerid,X,Y,Z);
					SendClientMessage(playerid,-1,"First Person view enabled!");
					return 1;
				}
				else SendClientMessage(playerid,-1,"ERROR: You are already in First Person View!");
			}
			else SendClientMessage(playerid,-1,"ERROR: You cant activate First Person View while in vehicle!");
		}
		case 4:
		{
			if(inFree[playerid] == 0)
			{
				inFree[playerid] = 1;
				inFP[playerid] = 0;
				inFrog[playerid] = 0;
				inBird[playerid] = 0;
				new Float:X;
				new Float:Y;
				new Float:Z;
				GetPlayerPos(playerid,X,Y,Z);
				SetPlayerCameraPos(playerid,X,Y,Z);
				SetPlayerCameraLookAt(playerid,X,Y,Z);
				SendClientMessage(playerid,-1,"Free view enabled!");
				return 1;
			}
			else SendClientMessage(playerid,-1,"ERROR: You are already in Free View!");
		}
	}
	return 1;
}

forward V_OnPlayerUpdate(playerid);
public OnPlayerUpdate(playerid)
{    
	if(inBird[playerid] == 1)
	{
		if(IsPlayerInAnyVehicle(playerid)) return RemovePlayerFromVehicle(playerid);
		new Float:X;
		new Float:Y;
		new Float:Z;
		GetPlayerPos(playerid,X,Y,Z);
		SetPlayerCameraPos(playerid,X,Y,Z+12);
		SetPlayerCameraLookAt(playerid,X,Y,Z);
		return 1;
	}
	else if(inFrog[playerid] == 1)
	{
		if(IsPlayerInAnyVehicle(playerid)) return RemovePlayerFromVehicle(playerid);
		new Float:X;
		new Float:Y;
		new Float:Z;
		GetPlayerPos(playerid,X,Y,Z);
		SetPlayerCameraPos(playerid,X,Y,Z-2);
		SetPlayerCameraLookAt(playerid,X,Y,Z+0.5);
		return 1;
	}
	else if(inFP[playerid] == 1)
	{
		if(IsPlayerInAnyVehicle(playerid)) return RemovePlayerFromVehicle(playerid);
		new Float:X;
		new Float:Y;
		new Float:Z;
		GetPlayerPos(playerid,X,Y,Z);
		SetPlayerCameraLookAt(playerid,X,Y,Z);
		SetPlayerCameraPos(playerid,X,Y,Z);
		return 1;
	}	
	else if(inFree[playerid] == 1)
	{
		new Float:X;
		new Float:Y;
		new Float:Z;
		GetPlayerPos(playerid,X,Y,Z);
		SetPlayerCameraLookAt(playerid,X,Y,Z);
		return 1;
	}
	if(funcidx("F_OnPlayerUpdate") != -1) CallLocalFunction("OnPlayerUpdate", "i", playerid);
	return 1;
}
#if defined _ALS_OnPlayerUpdate
        #undef OnPlayerUpdate
#else
        #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate V_OnPlayerUpdate

COMMAND:view(playerid,params[])
{
	return SetPlayerView(playerid,strval(params));
}