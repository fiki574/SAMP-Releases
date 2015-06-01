/*

Small logger include by fiki574

*/

#include <a_samp>
#define LOG_LOCATION    	"my.log"   
#define S_S_CAPACITY    	128         
#define DAMN_THAT_MEMORY    	2015        
#define Log::           	Log_        

stock Log::Write(log[])
{
    if(fexist(LOG_LOCATION))
    {
        new File:logf = fopen(LOG_LOCATION, io_append);
        fwrite(logf, log);
        fclose(logf);
    }
    else
    {
	new File:logf = fopen(LOG_LOCATION, io_write);
	fwrite(logf, log);
        fclose(logf);
    }
    return 1;
}

stock Log::Read()
{
    new string[S_S_CAPACITY], bigstring[DAMN_THAT_MEMORY];
    if(fexist(LOG_LOCATION))
    {
	new File:f = fopen(LOG_LOCATION, io_read);
	while(fread(f, string)) strcat(bigstring, string);
	fclose(f);
    }
    return bigstring;
}

stock Log::print(string[])
{
	new str[S_S_CAPACITY];
	format(str, sizeof(str), "[print] %s\r\n", string);
	Log::Write(str);
	print(string);
	return 1;
}
#define print Log::print

stock Log::SendClientMessage(playerid, color, message[])
{
	new str[S_S_CAPACITY];
	format(str, sizeof(str), "[SendClientMessage] ID %d: %s\r\n", playerid, message);
	Log::Write(str);
	SendClientMessage(playerid, color, message);
	return 1;
}
#define SendClientMessage Log::SendClientMessage