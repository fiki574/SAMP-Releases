/*

Position changing detection by fiki574

*/

#if defined _OnPlayerChangePosition_included
	#endinput
#endif
#define _OnPlayerChangePosition_included

#define PTIME 1*1000

new timer_used[MAX_PLAYERS];
new CheckTimer[MAX_PLAYERS];

forward OPCP_OnPlayerUpdate(playerid);
public OnPlayerUpdate(playerid)
{
	if(timer_used[playerid] == 0)
	{
	    new Float:old_x, Float:old_y, Float:old_z;
	    GetPlayerPos(playerid, old_x, old_y, old_z);
	    CheckTimer[playerid] = SetTimerEx("CheckPos", PTIME, true, "dfff", playerid, old_x, old_y, old_z);
	    timer_used[playerid] = 1;
	}
	else return 0;
	return 1;
}
#if defined _OPCP_OnPlayerUpdate
        #undef OnPlayerUpdate
#else
        #define _OPCP_OnPlayerUpdate
#endif
#define OnPlayerUpdate OPCP_OnPlayerUpdate

forward CheckPos(playerid, Float:old_x, Float:old_y, Float:old_z);
public CheckPos(playerid, Float:old_x, Float:old_y, Float:old_z)
{
	new Float:new_x, Float:new_y, Float:new_z;
	GetPlayerPos(playerid, new_x, new_y, new_z);
	CallLocalFunction("OnPlayerChangePosition", "dffffff", playerid, old_x, old_y, old_z, new_x, new_y, new_z);
	timer_used[playerid] = 0;
	return 1;
}

forward OnPlayerChangePosition(playerid, Float:old_x, Float:old_y, Float:old_z, Float:new_x, Float:new_y, Float:new_z);