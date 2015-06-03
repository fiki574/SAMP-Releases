/*

Angle and position changing detection by fiki574

*/

#if defined _opc_included
	#endinput
#endif
#define _opc_included

new timer_used[MAX_PLAYERS] = 0;
new timer_used2[MAX_PLAYERS] = 0;
new CheckTimer[MAX_PLAYERS];
new CheckTimer2[MAX_PLAYERS];
#define TIMER_TIME 1*1000

forward OPC_OnPlayerUpdate(playerid);
public OnPlayerUpdate(playerid)
{
	if(timer_used[playerid] == 0)
	{
		new Float:old_angle;
		GetPlayerFacingAngle(playerid, old_angle);
		CheckTimer[playerid] = SetTimerEx("CheckAngle", TIMER_TIME, 1, "df", playerid, old_angle);
		timer_used[playerid] = 1;
	}
	else return 0;
	
	if(timer_used2[playerid] == 0)
	{
	    new Float:old_x, Float:old_y, Float:old_z;
	    GetPlayerPos(playerid,old_x,old_y,old_z);
	    CheckTimer2[playerid] = SetTimerEx("CheckPos", TIMER_TIME, 1, "dfff", playerid, old_x, old_y, old_z);
	    timer_used2[playerid] = 1;
	}
	else return 0;
	return 1;
}
#if defined _OPC_OnPlayerUpdate
        #undef OnPlayerUpdate
#else
        #define _OPC_OnPlayerUpdate
#endif
#define OnPlayerUpdate OPC_OnPlayerUpdate

forward CheckAngle(playerid, Float:old_angle);
public CheckAngle(playerid, Float:old_angle)
{
	new Float:new_angle;
	GetPlayerFacingAngle(playerid, new_angle);
	CallLocalFunction("OnPlayerChangeAngle", "dff", playerid, old_angle, new_angle);
	timer_used[playerid] = 0;
	return 1;
}

forward CheckPos(playerid, Float:old_x, Float:old_y, Float:old_z);
public CheckPos(playerid, Float:old_x, Float:old_y, Float:old_z)
{
	new Float:new_x, Float:new_y, Float:new_z;
	GetPlayerPos(playerid,new_x,new_y,new_z);
	CallLocalFunction("OnPlayerChangePosition", "dffffff", playerid, old_x, old_y, old_z, new_x, new_y, new_z);
	timer_used2[playerid] = 0;
	return 1;
}

forward OnPlayerChangeAngle(playerid, Float:old_angle, Float:new_angle);
forward OnPlayerChangePosition(playerid, Float:old_x, Float:old_y, Float:old_z, Float:new_x, Float:new_y, Float:new_z);