/*

Small logger include by fiki574

*/

#include <a_samp>
#define LOG_LOCATION    	"Logger.log"   
#define S_S_CAPACITY    	256         
#define DAMN_THAT_MEMORY    	2015        
#define Log::           	Log_        

stock Log::Write(log[])
{
   	if(fexist(LOG_LOCATION))
    	{
        	new File:logf = fopen(LOG_LOCATION, io_append);
		if(logf)
		{
        		fwrite(logf, log);
        		fclose(logf);
		}
		else return 0;
    	}
    	else
    	{
		new File:logf = fopen(LOG_LOCATION, io_write);
		if(logf)
		{
			fwrite(logf, log);
        		fclose(logf);
		}		
		else return 0;    	
	}
    	return 1;
}

stock Log::Read()
{
    	new string[S_S_CAPACITY], bigstring[DAMN_THAT_MEMORY];
    	if(fexist(LOG_LOCATION))
    	{
		new File:f = fopen(LOG_LOCATION, io_read);
		if(f)
		{
			while(fread(f, string)) strcat(bigstring, string);
			fclose(f);
		}
		else return 0;
    	}
	return bigstring;
}

stock Log::print(string[])
{
	new str[S_S_CAPACITY];
	format(str, sizeof(str), "[print] %s\r\n", string);
	Log::Write(str);
	printf("%s", str);
	return 1;
}
#define print Log::print

stock Log::SendClientMessage(playerid, color, message[])
{
	new str[S_S_CAPACITY];
	format(str, sizeof(str), "[SendClientMessage(%d)] %s\r\n", playerid, message);
	Log::Write(str);
	SendClientMessage(playerid, color, message);
	printf("%s", str);
	return 1;
}
#define SendClientMessage Log::SendClientMessage

stock Log::SendClientMessageToAll(color, message[])
{
	new str[S_S_CAPACITY];
	format(str, sizeof(str), "[SendClientMessageToAll] %s\r\n", message);
	Log::Write(str);
	new hpid = GetPlayerPoolSize();
	for(new x = 0; x <= hpid; x++) if(IsPlayerConnected(x)) SendClientMessage(x, color, message);
	printf("%s", str);
	return 1;
}
#define SendClientMessageToAll Log::SendClientMessageToAll

stock Log::GameTextForPlayer(playerid, string[], time, style)
{
	new str[S_S_CAPACITY];
	format(str, sizeof(str), "[GameTextForPlayer(%d)] %s\r\n", playerid, string);
	Log::Write(str);
	GameTextForPlayer(playerid, string, time, style);
	printf("%s", str);
	return 1;
}
#define GameTextForPlayer Log::GameTextForPlayer

stock Log::GameTextForAll(string[], time, style)
{
	new str[S_S_CAPACITY];
	format(str, sizeof(str), "[GameTextForAll] %s\r\n", string);
	Log::Write(str);
	new hpid = GetPlayerPoolSize();
	for(new x = 0; x <= hpid; x++) if(IsPlayerConnected(x)) GameTextForPlayer(x, string, time, style);
	printf("%s", str);
	return 1;
}
#define GameTextForAll Log::GameTextForAll

