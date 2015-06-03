/*

Updated kick feature by fiki574

*/

#if defined _KickClient_included
	#endinput
#endif
#define _KickClient_included

#include <a_samp>

#define NOTIFY_TYPE_MSG				(0)
#define NOTIFY_TYPE_DIALOG			(1)
#define NOTIFY_ALL					(2)
#define NOTIFY_PLAYER				(3)
#define NOTIFY_RCON					(4)
#define DC_REASON_KICK				(98)

new KickTimer[MAX_PLAYERS];

/*Natives:
native KickClient(...);
*/

stock KickClient(...)
{
    new playerid = INVALID_PLAYER_ID, notification = -1, notify_who = -1;
	if(numargs() > 6)
	{
		printf("KickClient(): Too many arguments");
		return 0;
	}
    else if(numargs() == 0)
    {
    	new hpid = GetPlayerPoolSize();
		for(new x = 0; x <= hpid; x++)
		{ 
    		if(IsPlayerConnected(x))
			{
				CallLocalFunction("OnPlayerDisconnect", "dd", x, DC_REASON_KICK);
				KickTimer[x] = SetTimerEx("KickPlayer", 100, false, "d", x);
				return 0;
			}
    	}
    }
    else if(numargs() == 1)
    {
        playerid = getarg(0);
		CallLocalFunction("OnPlayerDisconnect", "dd", playerid, DC_REASON_KICK);
		KickTimer[playerid] = SetTimerEx("KickPlayer", 100, false, "d", playerid);
		return 0;
    }
    else if(numargs() >= 2)
    {
    	playerid = getarg(0);
        notification = getarg(1);
		switch(notification)
		{
			case NOTIFY_TYPE_MSG:
			{
				notify_who = getarg(2);
				new msg[100];
				for(new k = 0; getarg(3, k) != 0; k++) msg[k] = getarg(3, k);
				new msgcolor;
				if(numargs() == 4) msgcolor = 0xFFFFFFFF;
				else if(numargs() == 5) msgcolor = getarg(4);
				
				switch(notify_who)
				{
					case NOTIFY_ALL:
					{
						SendClientMessageToAll(msgcolor, msg);
						printf("[KickClient(%d)] %s", playerid, msg);
					}

					case NOTIFY_PLAYER:
					{
						SendClientMessage(playerid, msgcolor, msg);
					}

					case NOTIFY_RCON:
					{
						if(IsPlayerAdmin(playerid) == 1) SendClientMessage(playerid, msgcolor, msg);
						printf("[KickClient(%d)] %s", playerid, msg);
					}
				}
			}

			case NOTIFY_TYPE_DIALOG:
			{
				notify_who = getarg(2);
				new caption[20];
				for(new k = 0; getarg(3, k) != 0; k++) caption[k] = getarg(3, k);
				new info[256];
				for(new k = 0; getarg(4, k) != 0; k++) info[k] = getarg(4, k);
				new button[10];
				for(new k = 0; getarg(5, k) != 0; k++) button[k] = getarg(5, k);
				switch(notify_who)
				{
					case NOTIFY_PLAYER:
					{
						ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, caption, info, button,"");
					}

					case NOTIFY_ALL:
     				{
					}

					case NOTIFY_RCON:
					{
						printf("[KickClient(%d)] %s", playerid, info);
					}
				}
			}
		}
		CallLocalFunction("OnPlayerDisconnect", "dd", playerid, DC_REASON_KICK);
		KickTimer[playerid] = SetTimerEx("KickPlayer", 100, false, "d", playerid);
		return 0;
	}
	return 0;
}

forward KickPlayer(playerid);
public KickPlayer(playerid)
{
	Kick(playerid);
	KillTimer(KickTimer[playerid]);
	return 0;
}