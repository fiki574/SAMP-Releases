/*

Time ban system by fiki574

*/

#if defined _fban_included
	#endinput
#endif
#define _fban_included

//include SAMP file include (Credits: SAMP team)
#include <a_samp>
//include Blazing User Database (Credits: Slice)
#include <bud>
//include string file include (Credits: Pawno creators)
#include <string>

/*fban.inc functions:
native InitBanDatabase(dbname[]);
native TimeBan(playerid, reason[], bantype = BAN_TYPE_PERMANENT, hours = 0, minutes = 0, seconds = 0);
native TimeBanEx(name[], bantype = BAN_TYPE_PERMANENT, hours = 0, minutes = 0, seconds = 0);
native IsPlayerBanned(playerid);
native IsPlayerBannedEx(name[]);
native GetPlayerBanTime(playerid, &year, &month, &day, &hour, &min, &sec);
native GetPlayerBanTimeEx(name[], &year, &month, &day, &hour, &min, &sec);
native UnbanPlayer(playerid);
native UnbanPlayerEx(name[]);
*/

//permanent ban, just like from "samp.ban" file
#define BAN_TYPE_PERMANENT      (1)
//normal, temporar ban
#define BAN_TYPE_TEMP_NORMAL 	(2)

stock InitBanDatabase(dbname[])
{
	//initialize our database
	BUD::Setting(opt.Database, dbname);
	BUD::Setting(opt.Asynchronous, true);
	BUD::Setting(opt.KeepAliveTime, 3000);
	BUD::Setting(opt.CheckForUpdates, true);
	BUD::Initialize();
	BUD::VerifyColumn("name", BUD::TYPE_STRING);
	BUD::VerifyColumn("bantype", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expiryyear", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expirymonth", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expiryday", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expiryhour", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expirymin", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("expirysec", BUD::TYPE_NUMBER);
	BUD::VerifyColumn("ip", BUD::TYPE_STRING);
	BUD::VerifyColumn("isipbanned", BUD::TYPE_NUMBER);
}

stock TimeBan(playerid, reason[], bantype = BAN_TYPE_PERMANENT, hours = 0, minutes = 0, seconds = 0)
{
	//declare our time variables
	new hour, 
	    min,
	    sec; 

	//declare our date variables
	new year,
            month,
	    day;

	//declare new time variables used for calculating
	new newhour,
	    newmin,
	    newsec;

	//declare new date variable used for calculating
	new newyear,
	    newmonth,
            newday;

	//get current time and date
	gettime(hour, min, sec);
	getdate(year, month, day);
	
	//assign values to our new variables
	newday = day;
	newmonth = month;
	newyear = year;
	
	//calculate seconds
	newsec = sec + seconds;

	//calculate minutes
	newmin = min + minutes;

	//calculate hours
	newhour = hour + hours;
	
	//is there maybe a new minute calculated? if yes, increase minutes ammount
	if(newsec >= 60)
	{
		//calculate seconds and minutes
		do
		{
			newmin++;
			newsec = newsec - 60;
		} 
		//check if seconds exceed the value of 60
		while(newsec >= 60);
	}
	
	//check for hour switch if there's more than 60 minutes
	if(newmin >= 60)
	{
		//calculate minutes and hours
		do
		{
			newhour++;
			newmin = newmin - 60;
		}
		//check if minutes exceed the value of 60
		while(newmin >= 60);
	}
	
	//new day calculation if hours larger than 24
	if(newhour >= 24)
	{
		//calculate hours and days
		do
		{
			newday++;
			newhour = newhour - 24;
		}
		//check if hours exceed the value of 24
		while(newhour >= 24);
	}
	
	//calculate new month (months with 31 days)
	if(month == 1 && newday > 31 || month == 3 && newday > 31 || month == 5 && newday > 31 || month == 7 && newday > 31 || month == 9 && newday > 31 || month == 11 && newday > 31)
	{
	    newmonth++;
	    newday = newday - 31;
	}

	//calculate new month (months with 30 days)
	if(month == 2 && newday > 30 || month == 4 && newday > 30 || month == 6 && newday > 30 || month == 8 && newday > 30 || month == 10 && newday > 30 || month == 12 && newday > 30)
	{
	    newmonth++;
	    newday = newday - 30;
	}
	
	//calculate if there's any changes to year
	if(newmonth > 12)
	{
	    newyear++;
	    newmonth = newmonth - 12;
	}
	
	//get player's name
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	
	//declare player IP variable
	new pip[32];

	//get player's IP address
	GetPlayerIp(playerid, pip, sizeof(pip));
	
	//register player in bans database
	if(BUD::RegisterName(name, name))
	{
	    //different ban types use different DB saving
	    switch(bantype)
	    {
			//permanent IP ban (just like in "samp.ban" file)
			case BAN_TYPE_PERMANENT:
			{
			    //insert data in table
			    BUD::MultiSet(BUD::GetNameUID(name), "siiiiiiisi", "name", name, "bantype", BAN_TYPE_PERMANENT, "expiryyear", 0, "expirymonth", 0, "expiryday", 0, "expiryhour", 0, "expirymin", 0, "expirysec", 0, "ip", pip, "isipbanned", 1);
			    SendClientMessageToAll(0xFFFFFF, reason);
			}
			
	                //normal, temporar ban that will expire in choosen ammount of time
			case BAN_TYPE_TEMP_NORMAL:
			{
			    //insert data in table
			    BUD::MultiSet(BUD::GetNameUID(name), "siiiiiiisi", "name", name, "bantype", BAN_TYPE_TEMP_NORMAL, "expiryyear", newyear, "expirymonth", newmonth, "expiryday", newday, "expiryhour", newhour, "expirymin", newmin, "expirysec", newsec, "ip", pip, "isipbanned", 1);
			    SendClientMessageToAll(0xFFFFFF, reason);
			}
	    }
	    Kick(playerid);
	}
	else return 0;
	return 1;
}

stock TimeBanEx(name[], bantype = BAN_TYPE_PERMANENT, hours = 0, minutes = 0, seconds = 0)
{
	//declare our time variables
	new hour, 
	    min,
	    sec; 

	//declare our date variables
	new year,
            month,
	    day;

	//declare new time variables used for calculating
	new newhour,
	    newmin,
	    newsec;

	//declare new date variable used for calculating
	new newyear,
	    newmonth,
            newday;

	//get current time and date
	gettime(hour, min, sec);
	getdate(year, month, day);
	
	//assign values to our new variables
	newday = day;
	newmonth = month;
	newyear = year;
	
	//calculate seconds
	newsec = sec + seconds;

	//calculate minutes
	newmin = min + minutes;

	//calculate hours
	newhour = hour + hours;
	
	//is there maybe a new minute calculated? if yes, increase minutes ammount
	if(newsec >= 60)
	{
		//calculate seconds and minutes
		do
		{
			newmin++;
			newsec = newsec - 60;
		} 
		//check if seconds exceed the value of 60
		while(newsec >= 60);
	}
	
	//check for hour switch if there's more than 60 minutes
	if(newmin >= 60)
	{
		//calculate minutes and hours
		do
		{
			newhour++;
			newmin = newmin - 60;
		}
		//check if minutes exceed the value of 60
		while(newmin >= 60);
	}
	
	//new day calculation if hours larger than 24
	if(newhour >= 24)
	{
		//calculate hours and days
		do
		{
			newday++;
			newhour = newhour - 24;
		}
		//check if hours exceed the value of 24
		while(newhour >= 24);
	}
	
	//calculate new month (months with 31 days)
	if(month == 1 && newday > 31 || month == 3 && newday > 31 || month == 5 && newday > 31 || month == 7 && newday > 31 || month == 9 && newday > 31 || month == 11 && newday > 31)
	{
	    newmonth++;
	    newday = newday - 31;
	}

	//calculate new month (months with 30 days)
	if(month == 2 && newday > 30 || month == 4 && newday > 30 || month == 6 && newday > 30 || month == 8 && newday > 30 || month == 10 && newday > 30 || month == 12 && newday > 30)
	{
	    newmonth++;
	    newday = newday - 30;
	}
	
	//calculate if there's any changes to year
	if(newmonth > 12)
	{
	    newyear++;
	    newmonth = newmonth - 12;
	}
	
	//register player in bans database
	if(BUD::RegisterName(name, name))
	{
	    //different ban types use different DB saving
	    switch(bantype)
	    {
			//permanent IP ban (just like in "samp.ban" file)
			case BAN_TYPE_PERMANENT:
			{
			    //insert data in table
			    BUD::MultiSet(BUD::GetNameUID(name), "siiiiiiisi", "name", name, "bantype", BAN_TYPE_PERMANENT, "expiryyear", 0, "expirymonth", 0, "expiryday", 0, "expiryhour", 0, "expirymin", 0, "expirysec", 0, "ip", pip, "isipbanned", 1);
			    SendClientMessageToAll(0xFFFFFF, reason);
			}
			
	                //normal, temporar ban that will expire in choosen ammount of time
			case BAN_TYPE_TEMP_NORMAL:
			{
			    //insert data in table
			    BUD::MultiSet(BUD::GetNameUID(name), "siiiiiiisi", "name", name, "bantype", BAN_TYPE_TEMP_NORMAL, "expiryyear", newyear, "expirymonth", newmonth, "expiryday", newday, "expiryhour", newhour, "expirymin", newmin, "expirysec", newsec, "ip", 0, "isipbanned", 1);
			    SendClientMessageToAll(0xFFFFFF, reason);
			}
	    }
	}
	else return 0;
	return 1;
}

stock IsPlayerBanned(playerid)
{
	//declare our name variable
	new name[MAX_PLAYER_NAME];
	
	//get player's name
	GetPlayerName(playerid, name, sizeof(name));
	
	//declare a variable for ban type of a player
	new bantype;
	
	//check if player is actually in ban database
	if(BUD::IsNameRegistered(name))
	{
 		//get player ban type
   		bantype = BUD::GetIntEntry(BUD::GetNameUID(name), "bantype");
   		
   		//return ban type
	    return bantype;
	}
	//player doesnt exist in ban database
	else return 0;
}

stock IsPlayerBannedEx(name[])
{
	//declare a variable for ban type of a player
	new bantype;

	//check if player is actually in ban database
	if(BUD::IsNameRegistered(name))
	{
 		//get player ban type
   		bantype = BUD::GetIntEntry(BUD::GetNameUID(name), "bantype");

   		//return ban type
	    return bantype;
	}
	//player doesnt exist in ban database
	else return 0;
}

stock GetPlayerBanTime(playerid, &year, &month, &day, &hour, &min, &sec)
{
        //declare our name variable
	new name[MAX_PLAYER_NAME];

	//get player's name
	GetPlayerName(playerid, name, sizeof(name));
	
	//declare our date variables
	new getyear,
	    getmonth,
	    getday;
	    
	//declare our time variables
	new gethour,
	    getmin,
   	    getsec;
	
	//check if player is actually in ban database
	if(BUD::IsNameRegistered(name))
	{
	    //get remaining ban time
	    BUD::MultiGet(BUD::GetNameUID(name), "iiiiii",
	                                         "expiryyear", getyear,
	                                         "expirymonth", getmonth,
	                                         "expiryday", getday,
	                                         "expiryhour", gethour,
	                                         "expirymin", getmin,
	                                         "expirysec", getsec);

		//assign to date variables
		year = getyear;
		month = getmonth;
		day = getday;
		
		//assign to time variables
		hour = gethour;
		min = getmin;
		sec = getsec;
		
		//success
		return 1;
	}
	//player doesnt exist in ban database
	else return 0;
}

stock GetPlayerBanTimeEx(name[], &year, &month, &day, &hour, &min, &sec)
{
	//declare our date variables
	new getyear,
	    getmonth,
	    getday;

	//declare our time variables
	new gethour,
	    getmin,
	    getsec;

	//check if player is actually in ban database
	if(BUD::IsNameRegistered(name))
	{
	    //get remaining ban time
	    BUD::MultiGet(BUD::GetNameUID(name), "iiiiii",
	                                         "expiryyear", getyear,
	                                         "expirymonth", getmonth,
	                                         "expiryday", getday,
	                                         "expiryhour", gethour,
	                                         "expirymin", getmin,
	                                         "expirysec", getsec);

		//assign to date variables
		year = getyear;
		month = getmonth;
		day = getday;

		//assign to time variables
		hour = gethour;
		min = getmin;
		sec = getsec;

		//success
		return 1;
	}
	//player doesnt exist in ban database
	else return 0;
}

stock UnbanPlayer(playerid)
{
    //declare our name variable
	new name[MAX_PLAYER_NAME];

	//get player's name
	GetPlayerName(playerid, name, sizeof(name));
	
	//check if player is actually in ban database
	if(BUD::IsNameRegistered(name))
	{
	    //delete player from ban database
	    BUD::UnregisterName(name);

	    //successfully unbanned player
	    return 1;
	}
	//fail, player not banned
	else return 0;
}

stock UnbanPlayerEx(name[])
{
	//check if player is actually in ban database
	if(BUD::IsNameRegistered(name))
	{
	    //delete player from ban database
	    BUD::UnregisterName(name);
	    
	    //successfully unbanned player
	    return 1;
	}
	//fail, player not banned
	else return 0;
}