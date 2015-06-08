/*

Angle changing detection by fiki574

*/

#if defined _OnPlayerChangeAngle_included
	#endinput
#endif
#define _OnPlayerChangeAngle_included

#define ATIME 1*1000

new timer_used2[MAX_PLAYERS];
new CheckTimer2[MAX_PLAYERS];

forward OPCA_OnPlayerUpdate(playerid);
public OnPlayerUpdate(playerid)
{
	if(timer_used2[playerid] == 0)
	{
		new Float:old_angle;
		GetPlayerFacingAngle(playerid, old_angle);
		CheckTimer2[playerid] = SetTimerEx("CheckAngle", ATIME, true, "df", playerid, old_angle);
		timer_used2[playerid] = 1;
	}
	else return 0;
	return 1;
}
#if defined _OPCA_OnPlayerUpdate
        #undef OnPlayerUpdate
#else
        #define _OPCA_OnPlayerUpdate
#endif
#define OnPlayerUpdate OPCA_OnPlayerUpdate

forward CheckAngle(playerid, Float:old_angle);
public CheckAngle(playerid, Float:old_angle)
{
	new Float:new_angle;
	GetPlayerFacingAngle(playerid, new_angle);
	CallLocalFunction("OnPlayerChangeAngle", "dff", playerid, old_angle, new_angle);
	timer_used2[playerid] = 0;
	KillTimer(CheckTimer2[playerid]);
	return 1;
}

forward OnPlayerChangeAngle(playerid, Float:old_angle, Float:new_angle);
