/*

Updated kick and ban feature by fiki574

*/

#if defined _newkb_included
	#endinput
#endif
#define _newkb_included

#define NOTIFICATION_TYPE_MSG		(0)
#define NOTIFICATION_TYPE_DIALOG	(1)
#define NOTIFY_ALL					(2)
#define NOTIFY_PLAYER				(3)
#define NOTIFY_RCON					(4)
#define CLIENT_ACTION_KICK			(5)
#define CLIENT_ACTION_BAN			(6)
#define CLIENT_ACTION_BAN_IP		(7)
#define DC_REASON_BAN				(97)
#define DC_REASON_KICK				(98)
#define DC_REASON_BAN_IP			(99)

new KickTimer[MAX_PLAYERS], BanTimer[MAX_PLAYERS];

/*Natives:
native Client(...);
*/

stock Client(...)
{
	new action = -1, playerid = INVALID_PLAYER_ID, notification = -1, notify_who = -1;
	action = getarg(0);
	playerid = getarg(1);
	if(numargs() >= 2)
	{
		notification = getarg(2);
		switch(notification)
		{
			case NOTIFICATION_TYPE_MSG:
			{
				notify_who = getarg(3);
				new msg[100];
				for(new k = 0; getarg(4, k) != 0; k++) 
				{
					msg[k] = getarg(4,k);
				}
				new msgcolor = getarg(5);

				switch(notify_who)
				{
					case NOTIFY_ALL:
					{
						SendClientMessageToAll(msgcolor, msg);
					}

					case NOTIFY_PLAYER:
					{
						SendClientMessage(playerid, msgcolor, msg);
					}

					case NOTIFY_RCON:
					{
						if(IsPlayerAdmin(playerid) == 1) SendClientMessage(playerid, msgcolor, msg);
						printf("%s", msg);
					}
				}
			}

			case NOTIFICATION_TYPE_DIALOG:
			{
				notify_who = getarg(3);
				new caption[20];
				for(new k = 0; getarg(4, k) != 0; k++) 
				{
					caption[k] = getarg(4,k);
				}
				new info[256];
				for(new k = 0; getarg(5, k) != 0; k++) 
				{
					info[k] = getarg(5,k);
				}
				new button[10];
				for(new k = 0; getarg(6, k) != 0; k++) 
				{
					button[k] = getarg(6,k);
				}

				switch(notify_who)
				{
					case NOTIFY_PLAYER:
					{
						ShowPlayerDialog(playerid,0,DIALOG_STYLE_MSGBOX,caption,info,button,"");
					}

					case NOTIFY_ALL, NOTIFY_RCON:
					{
						return 0;
					}
				}
			}	
		}	
		
		switch(action)
		{
			case CLIENT_ACTION_BAN:
			{
				OnPlayerDisconnectEx(playerid, DC_REASON_BAN);
				BanTimer[playerid] = SetTimerEx("BanPlayer", 100, false, "d", playerid);
				if(numargs() == 1) for(new i = 0; i < MAX_PLAYERS; i++) OnPlayerDisconnectEx(playerid, DC_REASON_BAN), Ban(i);
				
			}

			case CLIENT_ACTION_KICK:
			{
				OnPlayerDisconnectEx(playerid, DC_REASON_KICK);
				KickTimer[playerid] = SetTimerEx("KickPlayer", 100, false, "d", playerid);
				if(numargs() == 1) for(new i = 0; i < MAX_PLAYERS; i++) OnPlayerDisconnectEx(i, DC_REASON_KICK), Kick(i);
			}

			case CLIENT_ACTION_BAN_IP:
			{
				OnPlayerDisconnectEx(playerid, DC_REASON_BAN_IP);
				new ip[32];
				GetPlayerIp(playerid,ip,sizeof(ip));
				new banit[40];
				format(banit,sizeof(banit),"banip %s", ip);
				SendRconCommand(banit);
				if(numargs() == 1) 
				{
					new pip[32];
					for(new i = 0; i < MAX_PLAYERS; i++)
					{	
						GetPlayerIp(i,pip,sizeof(pip));
						new banit2[40];
						format(banit2,sizeof(banit2),"banip %s", ip);
						SendRconCommand(banit2);
						OnPlayerDisconnectEx(i, DC_REASON_BAN_IP);
					}
				}
				KickTimer[playerid] = SetTimerEx("KickPlayer", 100, false, "d", playerid);
			}
		}	
	}
	return 1;
}

forward KickPlayer(playerid);
public KickPlayer(playerid)
{
	Kick(playerid);
	KillTimer(KickTimer[playerid]);
	return 0;
}

forward BanPlayer(playerid);
public BanPlayer(playerid)
{
	Ban(playerid);
	KillTimer(BanTimer[playerid]);
	return 0;
}

forward OnPlayerDisconnectEx(playerid, reason);
public OnPlayerDisconnectEx(playerid, reason)
{
	return CallLocalFunction("OnPlayerDisconnect", "dd", playerid, reason);
}