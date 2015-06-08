/*

Time ban system by fiki574

*/

#if defined _TimeBan_included
	#endinput
#endif
#define _TimeBan_included

#include <a_samp>
#include <bud>
#include <string>

new DelayedKickTimer[MAX_PLAYERS];

#define DC_REASON_TIMEBAN	(95)
#define TIME_BAN_DB_NAME	"timebans.db"

/*Functions:
native TimeBan(name[], reason[], hours, minutes, seconds);
native IsPlayerTimeBanned(name[]);
native GetPlayerTimeBanInfo(name[], &year, &month, &day, &hour, &min, &sec);
native UnbanPlayer(name[]);
native GetPlayerId(name[]);
native GetName(playerid);
*/

forward TB_OnFilterScriptInit();
public OnFilterScriptInit()
{
	BUD::Setting(opt.Database, TIME_BAN_DB_NAME);
	BUD::Setting(opt.Asynchronous, true);
	BUD::Setting(opt.KeepAliveTime, 3000);
	BUD::Setting(opt.CheckForUpdates, true);
	BUD::Initialize();
	BUD::VerifyColumn("name", BUD::TYPE_STRING);
	BUD::VerifyColumn("reason", BUD::TYPE_STRING);
	BUD::VerifyColumn("expiryyear", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expirymonth", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expiryday", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expiryhour", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expirymin", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expirysec", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("ip", BUD::TYPE_STRING);
	return 1;
}
#if defined _ALS_OnFilterScriptInit
        #undef OnFilterScriptInit
#else
        #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit TB_OnFilterScriptInit

stock TimeBan(name[], reason[], hours, minutes, seconds)
{
	new hour, mins, sec; 
	gettime(hour, mins, sec);
	new year, month, day;
	getdate(year, month, day);
	new newhour, newmin, newsec;
	new newyear, newmonth, newday;
	newday = day;
	newmonth = month;
	newyear = year;
	newsec = sec + seconds;
	newmin = mins + minutes;
	newhour = hour + hours;

	if(newsec >= 60)
	{
		do
		{
			newmin++;
			newsec = newsec - 60;
		} 
		while(newsec >= 60);
	}
	
	if(newmin >= 60)
	{
		do
		{
			newhour++;
			newmin = newmin - 60;
		}
		while(newmin >= 60);
	}
	
	if(newhour >= 24)
	{
		do
		{
			newday++;
			newhour = newhour - 24;
		}
		while(newhour >= 24);
	}
	
	if(month == 1 && newday > 31 || month == 3 && newday > 31 || month == 5 && newday > 31 || month == 7 && newday > 31 || month == 9 && newday > 31 || month == 11 && newday > 31)
	{
	    newmonth++;
	    newday = newday - 31;
	}

	if(month == 2 && newday > 30 || month == 4 && newday > 30 || month == 6 && newday > 30 || month == 8 && newday > 30 || month == 10 && newday > 30 || month == 12 && newday > 30)
	{
	    newmonth++;
	    newday = newday - 30;
	}
	
	if(newmonth > 12)
	{
	    newyear++;
	    newmonth = newmonth - 12;
	}
	
	new playerid = GetPlayerId(name);
	new pip[32];
	GetPlayerIp(playerid, pip, sizeof(pip));
	if(!IsPlayerConnected(playerid) || playerid == INVALID_PLAYER_ID) pip = "0.0.0.0";
	if(BUD::RegisterName(name, name))
	{
		BUD::MultiSet(BUD::GetNameUID(name), "ssiiiiiis", "name", name, "reason", reason, "expiryyear", newyear, "expirymonth", newmonth, "expiryday", newday, "expiryhour", newhour, "expirymin", newmin, "expirysec", newsec, "ip", pip);
	    	CallLocalFunction("OnPlayerTimeBanned", "dsiii", playerid, reason, hours, minutes, seconds);
		CallLocalFunction("OnPlayerDisconnect", "di", playerid, DC_REASON_TIMEBAN);
		DelayedKickTimer[playerid] =  SetTimerEx("DelayedKick", 100, false, "d", playerid);
	}
	else return 0;
	return 1;
}

stock IsPlayerTimeBanned(name[])
{	
	if(BUD::IsNameRegistered(name)) return 1;
	else return 0;
}

stock GetPlayerTimeBanInfo(name[], &year, &month, &day, &hour, &min, &sec)
{
	new getyear, getmonth, getday;
	new gethour, getmin, getsec;
	new getreason[256], getip[16];
	if(IsPlayerTimeBanned(name) == 1)
	{
	    	BUD::MultiGet(BUD::GetNameUID(name), "iiiiii", "expiryyear", getyear, "expirymonth", getmonth, "expiryday", getday, "expiryhour", gethour, "expirymin", getmin, "expirysec", getsec);
		year = getyear;
		month = getmonth;
		day = getday;
		hour = gethour;
		min = getmin;
		sec = getsec;
		return 1;
	}
	else return 0;
}

stock UnbanPlayer(name[])
{
	if(IsPlayerTimeBanned(name) == 1)
	{
	    	BUD::UnregisterName(name);
		CallLocalFunction("OnPlayerUnban", "s", name);
	    	return 1;
	}
	else return 0;
}

stock GetPlayerId(name[])
{
	new playerid = INVALID_PLAYER_ID;
	new hpid = GetPlayerPoolSize();
	for(new x = 0; x <= hpid; x++)
	{ 
    		if(IsPlayerConnected(x))
		{
			new pname[MAX_PLAYER_NAME];
			GetPlayerName(x, pname, sizeof(pname));
			if(strcmp(pname, name, true, strlen(name)) == 0) playerid = x;
			else playerid = INVALID_PLAYER_ID;
    		}
	}
	return playerid;
}

stock GetName(playerid)
{
	new pname[MAX_PLAYER_NAME];
	GetPlayerName(playerid, pname, sizeof(pname));
	return pname;
}

forward DelayedKick(playerid);
public DelayedKick(playerid)
{
	Kick(playerid);
	KillTimer(DelayedKickTimer[playerid]);
	return 0;
}

forward OnPlayerTimeBanned(playerid, reason[], hours, minutes, seconds);
forward OnPlayerUnbanned(name[]);