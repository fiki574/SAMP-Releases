/*

Updated ban feature by fiki574

*/

#if defined _BanClient_included
	#endinput
#endif
#define _BanClient_included

#include <a_samp>

#define NOTIFY_TYPE_MSG				(0)
#define NOTIFY_TYPE_DIALOG			(1)
#define NOTIFY_ALL					(2)
#define NOTIFY_PLAYER				(3)
#define NOTIFY_RCON					(4)
#define BAN_TYPE_NORMAL				(5)
#define BAN_TYPE_IP					(6)
#define DC_REASON_BAN				(97)
#define DC_REASON_BAN_IP			(99)

new BanTimer[MAX_PLAYERS];

/*Natives:
native BanClient(...);
*/

stock BanClient(...)
{
    new action = -1, playerid = INVALID_PLAYER_ID, notification = -1, notify_who = -1;
	if(numargs() == 0) 
	{
		printf("BanClient(): Must have at least one argument");
		return 0;
	}
	else if(numargs() > 7) 
	{
		printf("BanClient(): Too many arguments");
		return 0;
	}
    else if(numargs() == 1)
    {
		action = getarg(0);
		switch(action)
		{
			case BAN_TYPE_NORMAL:
			{
    			new hpid = GetPlayerPoolSize();
				for(new x = 0; x <= hpid; x++)
				{ 
    				if(IsPlayerConnected(x))
					{
						CallLocalFunction("OnPlayerDisconnect", "dd", x, DC_REASON_BAN);
    					BanTimer[x] = SetTimerEx("BanPlayer", 100, false, "d", x);
						return 0;
					}
    			}
			}

			case BAN_TYPE_IP:
			{
				new hpid = GetPlayerPoolSize();
				for(new x = 0; x <= hpid; x++)
				{ 
    				if(IsPlayerConnected(x))
					{
						CallLocalFunction("OnPlayerDisconnect", "dd", x, DC_REASON_BAN_IP);
						new ip[32];
						GetPlayerIp(x, ip, sizeof(ip));
						new banit[40];
						format(banit, sizeof(banit), "banip %s", ip);
						SendRconCommand(banit);
						BanTimer[x] = SetTimerEx("BanPlayer", 100, false, "d", x);
					}
				}
			}
		}
    }
    else if(numargs() == 2)
    {
		action = getarg(0);
		playerid = getarg(1);
		switch(action)
		{
			case BAN_TYPE_NORMAL:
			{
				CallLocalFunction("OnPlayerDisconnect", "dd", playerid, DC_REASON_BAN);
    			BanTimer[playerid] = SetTimerEx("BanPlayer", 100, false, "d", playerid);
			}

			case BAN_TYPE_IP:
			{
				new ip[32];
				GetPlayerIp(playerid, ip, sizeof(ip));
				new banit[40];
				format(banit, sizeof(banit), "banip %s", ip);
				CallLocalFunction("OnPlayerDisconnect", "dd", playerid, DC_REASON_BAN_IP);
				SendRconCommand(banit);
				BanTimer[playerid] = SetTimerEx("BanPlayer", 100, false, "d", playerid);
			}
		}
		return 0;
    }
    else if(numargs() >= 3)
    {
		action = getarg(0);
    	playerid = getarg(1);
        notification = getarg(2);
		switch(notification)
		{
			case NOTIFY_TYPE_MSG:
			{
				notify_who = getarg(3);
				new msg[100];
				for(new k = 0; getarg(4, k) != 0; k++) msg[k] = getarg(4, k);
				new msgcolor;
				if(numargs() == 5) msgcolor = 0xFFFFFFFF;
				else if(numargs() == 6) msgcolor = getarg(5);
				
				switch(notify_who)
				{
					case NOTIFY_ALL:
					{
						SendClientMessageToAll(msgcolor, msg);
						printf("[BanClient(%d)] %s", playerid, msg);
					}

					case NOTIFY_PLAYER:
					{
						SendClientMessage(playerid, msgcolor, msg);
					}

					case NOTIFY_RCON:
					{
						if(IsPlayerAdmin(playerid) == 1) SendClientMessage(playerid, msgcolor, msg);
						printf("[BanClient(%d)] %s", playerid, msg);
					}
				}
			}

			case NOTIFY_TYPE_DIALOG:
			{
				notify_who = getarg(3);
				new caption[20];
				for(new k = 0; getarg(4, k) != 0; k++) caption[k] = getarg(4, k);
				new info[256];
				for(new k = 0; getarg(5, k) != 0; k++) info[k] = getarg(5, k);
				new button[10];
				for(new k = 0; getarg(6, k) != 0; k++) button[k] = getarg(6, k);
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
						printf("[BanClient(%d)] %s", playerid, info);
					}
				}
			}
		}

		switch(action)
		{
			case BAN_TYPE_NORMAL:
			{
				CallLocalFunction("OnPlayerDisconnect", "dd", playerid, DC_REASON_BAN);
    			BanTimer[playerid] = SetTimerEx("BanPlayer", 100, false, "d", playerid);
			}

			case BAN_TYPE_IP:
			{
				new ip[32];
				GetPlayerIp(playerid, ip, sizeof(ip));
				new banit[40];
				format(banit, sizeof(banit), "banip %s", ip);
				CallLocalFunction("OnPlayerDisconnect", "dd", playerid, DC_REASON_BAN_IP);
				SendRconCommand(banit);
				BanTimer[playerid] = SetTimerEx("BanPlayer", 100, false, "d", playerid);
			}
		}
		return 0;
	}
	return 0;
}

forward BanPlayer(playerid);
public BanPlayer(playerid)
{
	Ban(playerid);
	KillTimer(BanTimer[playerid]);
	return 0;
}