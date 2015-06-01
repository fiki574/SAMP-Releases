/*

Custom admin system include by fiki574

NOTE:
Should be used if you're using my fAdmin system.

*/

#if defined _fadmin_included
	#endinput
#endif
#define _fadmin_included
/*Natives:
native IsPlayerFadmin(playerid);
native IsPlayerFadminLevel(playerid, level);
native IsPlayerVip(playerid);
native IsPlayerVipLevel(playerid, level);
native IsPlayerRegistered(playerid);
native IsPlayerMuted(playerid);
native IsPlayerFrozen(playerid);
native IsAccountBanned(account[]);
native GetPlayerAdminRank(playerid);
native GetPlayerAdminLevel(playerid);
native GetPlayerVipRank(playerid);
native GetPlayerVipLevel(playerid);
native GetPlayerWarnings(playerid);
native GetKills(playerid);
native GetDeaths(playerid);
*/

stock IsPlayerFadmin(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new Afile[256];
	new isAdmin[MAX_PLAYERS] = 0;
	new bool:admin = false;
	format(Afile,256,"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(Afile))
	{
	    fopen(Afile,io_read);
		isAdmin[playerid] = dini_Int(Afile,"AdminLevel");
		if(isAdmin[playerid] >= 1)
		{
			admin = true;
		}
		else
		{
			admin = false;
		}
	}
	return admin;
}

stock IsPlayerFadminLevel(playerid, level)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new Afile[256];
	new isAdmin[MAX_PLAYERS] = 0;
	format(Afile,256,"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(Afile))
	{
	    fopen(Afile,io_read);
		isAdmin[playerid] = dini_Int(Afile,"AdminLevel");
		if(isAdmin[playerid] >= level)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return 0;
}

stock IsPlayerVip(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new Vfile[256];
	new isVip[MAX_PLAYERS] = 0;
	format(Vfile,256,"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(Vfile))
	{
	    fopen(Vfile,io_read);
		isVip[playerid] = dini_Int(Vfile,"VIPlevel");
		if(isVip[playerid] >= 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return 0;
}

stock IsPlayerVipLevel(playerid, level)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new Vfile[256];
	new isVip[MAX_PLAYERS] = 0;
	format(Vfile,256,"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(Vfile))
	{
	    fopen(Vfile,io_read);
		isVip[playerid] = dini_Int(Vfile,"VIPlevel");
		if(isVip[playerid] >= level)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return 0;
}

stock IsPlayerRegistered(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new file[256];
	new isRegged[MAX_PLAYERS] = 0;
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(file))
	{
	    fopen(file,io_read);
		isRegged[playerid] = dini_Int(file,"Registered");
		if(isRegged[playerid] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return 0;
}

stock IsPlayerMuted(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new file[256];
	new isMuted[MAX_PLAYERS] = 0;
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(file))
	{
	    fopen(file,io_read);
		isMuted[playerid] = dini_Int(file,"Muted");
		if(isMuted[playerid] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return 0;
}

stock IsPlayerFrozen(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new file[256];
	new isFrozen[MAX_PLAYERS] = 0;
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(file))
	{
	    fopen(file,io_read);
		isFrozen[playerid] = dini_Int(file,"Frozen");
		if(isFrozen[playerid] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return 0;
}

stock IsAccountBanned(account[])
{
	new file[256];
	new isBanned = 0;
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",account);
	if(dini_Exists(file))
	{
	    fopen(file,io_read);
		isBanned = dini_Int(file,"AccBanned");
		if(isBanned == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return 0;
}

stock GetPlayerAdminRank(playerid)
{
	new rank[10] = "";
	if(GetPlayerAdminLevel(playerid) == 1) rank = "Moderator";
	if(GetPlayerAdminLevel(playerid) == 2) rank = "Global Moderator";
	if(GetPlayerAdminLevel(playerid) == 3) rank = "Administrator";
	if(GetPlayerAdminLevel(playerid) == 4) rank = "Master Administrator";
	if(GetPlayerAdminLevel(playerid) == 5) rank = "Owner";
	return rank;
}

stock GetPlayerAdminLevel(playerid)
{
	new file[256];
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new AdminLevel[MAX_PLAYERS] = 0;
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(file))
	{
	    fopen(file,io_read);
		AdminLevel[playerid] = dini_Int(file,"AdminLevel");
	}
	return AdminLevel[playerid];
}

stock GetPlayerVipRank(playerid)
{
	new rank[10] = "";
	if(GetPlayerAdminLevel(playerid) == 1) rank = "Silver";
	if(GetPlayerAdminLevel(playerid) == 2) rank = "Gold";
	if(GetPlayerAdminLevel(playerid) == 3) rank = "Premium";
	return rank;
}

stock GetPlayerVipLevel(playerid)
{
	new file[256];
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new VipLevel[MAX_PLAYERS] = 0;
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(file))
	{
	    fopen(file,io_read);
		VipLevel[playerid] = dini_Int(file,"VIPlevel");
	}
	return VipLevel[playerid];
}

stock GetPlayerWarnings(playerid)
{
	new file[256];
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new Warnings[MAX_PLAYERS] = 0;
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(file))
	{
	    fopen(file,io_read);
		Warnings[playerid] = dini_Int(file,"Warnings");
	}
	return Warnings[playerid];
}

stock GetPlayerKills(playerid)
{
	new file[256];
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new pkills[MAX_PLAYERS] = 0;
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(file))
	{
	    fopen(file,io_read);
		pkills[playerid] = dini_Int(file,"Kills");
	}
	return pkills[playerid];
}

stock GetPlayerDeaths(playerid)
{
	new file[256];
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	new pdeaths[MAX_PLAYERS] = 0;
	format(file,sizeof(file),"/fAdmin/Players/%s.txt",name);
	if(dini_Exists(file))
	{
	    fopen(file,io_read);
		pdeaths[playerid] = dini_Int(file,"Deaths");
	}
	return pdeaths[playerid];
}