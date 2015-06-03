/*

UNFINISHED!!

Crappy, unfinished attemp at creating custom mod shops
wherever on the map by fiki574

*/

#if defined _cms_included
	#endinput
#endif
#define _cms_included

#define MOD_SHOP_LOCO	(0)
#define MOD_SHOP_TF		(1)
#define MOD_SHOP_ARCH	(2)
#define MAX_MOD_SHOPS	(100)
#define INVALID_MODSHOP	(-1)

new LOCO_VEH[MAX_PLAYERS], TF_VEH[MAX_PLAYERS], ARCH_VEH[MAX_PLAYERS];
new Text:MOD_TD;

enum ModShopData
{
	Float:Pos[3],
	Text3D:Label,
	MapIcon,
	Pickup,
	Type
}
new msData[MAX_MOD_SHOPS][ModShopData];

/*Natives:
native InitCMS();
native CreateModShop(playerid, shopid, type, Float:X, Float:Y, Float:Z);
native DestroyModShop(shopid);
native ExitModShop(playerid);
native IsInLocoVehicle(playerid);
native IsInTfVehicle(playerid);
native IsInArchVehicle(playerid);
native ModShopCreated(shopid);
*/

stock InitCMS()
{
    printf("-------------------------------------");
    printf("=====================================");
   	printf("\"CreateModShop.inc\" initialised!");
   	printf(" ");
   	printf("   Copyright: fiki574_CRO");
   	printf(" ");
   	printf("     Date: 14.07.2012");
   	printf(" ");
   	printf("      Version: 1.0 ");
   	printf(" ");
   	printf("   All rights reserved!");
   	printf(" ");
   	printf("=====================================");
   	printf("-------------------------------------");
   	
   	MOD_TD = TextDrawCreate(26.000000, 138.000000, "~g~Mod installed!");
	TextDrawBackgroundColor(MOD_TD, 255);
	TextDrawFont(MOD_TD, 1);
	TextDrawLetterSize(MOD_TD, 0.500000, 1.000000);
	TextDrawColor(MOD_TD, -1);
	TextDrawSetOutline(MOD_TD, 0);
	TextDrawSetProportional(MOD_TD, 1);
	TextDrawSetShadow(MOD_TD, 1);
	TextDrawUseBox(MOD_TD, 1);
	TextDrawBoxColor(MOD_TD, 255);
	TextDrawTextSize(MOD_TD, 143.000000, 18.000000);
    return 1;
}

stock DestroyModShop(shopid)
{
	for(new playerid; playerid < MAX_PLAYERS; playerid++) RemovePlayerMapIcon(playerid, shopid);
	DestroyPickup(msData[shopid][Pickup]);
	Delete3DTextLabel(msData[shopid][Label]);
	msData[shopid][Pos][0] = 0.0;
	msData[shopid][Pos][1] = 0.0;
	msData[shopid][Pos][2] = 0.0;
	Delete3DTextLabel(msData[shopid][Label]);
	msData[shopid][MapIcon] = 0;
	msData[shopid][Pickup] = 0;
	msData[shopid][Type] = INVALID_MODSHOP;
	return 1;
}

stock CreateModShop(playerid, shopid, type, Float:X, Float:Y, Float:Z)
{	
	if(ModShopCreated(shopid)) printf("ERROR: Shop ID %d already in use!", shopid); 
	switch(type)
	{
		case MOD_SHOP_LOCO:
		{
			msData[shopid][Pickup] = CreatePickup(1318, 14, X, Y, Z);
			msData[shopid][Type] = MOD_SHOP_LOCO;
			SetPlayerMapIcon(playerid, shopid, X, Y, Z, 23, 0, MAPICON_LOCAL);
			msData[shopid][Label] = Create3DTextLabel("{00FF00}Loco Low Co.", -1, X, Y, Z+0.5, 40, 0, 0);
		}
		case MOD_SHOP_TF:
		{
			msData[shopid][Pickup] = CreatePickup(1318, 14, X, Y, Z);
			msData[shopid][Type] = MOD_SHOP_TF;
			SetPlayerMapIcon(playerid, shopid, X, Y, Z, 27, 0, MAPICON_LOCAL);
			msData[shopid][Label] = Create3DTextLabel("{00FF00}TransFender", -1, X, Y, Z+0.5, 40, 0, 0);
		}
		case MOD_SHOP_ARCH:
		{
			msData[shopid][Pickup] = CreatePickup(1318, 14, X, Y, Z);
			msData[shopid][Type] = MOD_SHOP_ARCH;
			SetPlayerMapIcon(playerid, shopid, X, Y, Z, 55, 0, MAPICON_LOCAL);
			msData[shopid][Label] = Create3DTextLabel("{00FF00}Wheel Arch Angels", -1, X, Y, Z+0.5, 40, 0, 0);
		}
	}	
	return shopid;
}
					
stock IsInLocoVehicle(playerid)
{
	new vehicleid = GetVehicleModel(GetPlayerVehicleID(playerid));
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			switch(vehicleid)
			{
				case 400..411: LOCO_VEH[playerid] = 0;
				case 413..533: LOCO_VEH[playerid] = 0;
				case 537..565: LOCO_VEH[playerid] = 0;
				case 568..574: LOCO_VEH[playerid] = 0;
				case 577..611: LOCO_VEH[playerid] = 0;
				case 412: LOCO_VEH[playerid] = 0;
				case 566: LOCO_VEH[playerid] = 0;
				case 534..536: LOCO_VEH[playerid] = 1;
				case 567: LOCO_VEH[playerid] = 1;
				case 575: LOCO_VEH[playerid] = 1;
				case 576: LOCO_VEH[playerid] = 1;
			}
		}
	}
	return LOCO_VEH[playerid];
}

stock IsInTfVehicle(playerid)
{
	new vehicleid = GetVehicleModel(GetPlayerVehicleID(playerid));
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			switch(vehicleid)
			{
				case 400..402: TF_VEH[playerid] = 1;
				case 403: TF_VEH[playerid] = 0;
				case 404..405: TF_VEH[playerid] = 1;
				case 406..408: TF_VEH[playerid] = 0;
				case 409..411: TF_VEH[playerid] = 1;
				case 412..414: TF_VEH[playerid] = 0;
				case 415: TF_VEH[playerid] = 1;
				case 416..417: TF_VEH[playerid] = 0;
				case 418..422: TF_VEH[playerid] = 1;
				case 423: TF_VEH[playerid] = 0;
				case 424: TF_VEH[playerid] = 1;
				case 425: TF_VEH[playerid] = 0;
				case 426: TF_VEH[playerid] = 1;
				case 427..428:TF_VEH[playerid] = 0;
				case 429: TF_VEH[playerid] = 1;
				case 430..435: TF_VEH[playerid] = 0;
				case 436: TF_VEH[playerid] = 1;
				case 437: TF_VEH[playerid] = 0;
				case 438..439: TF_VEH[playerid] = 1;
				case 440..441: TF_VEH[playerid] = 0;
				case 442: TF_VEH[playerid] = 1;
				case 443..444: TF_VEH[playerid] = 0;
				case 445: TF_VEH[playerid] = 1;
				case 446..450: TF_VEH[playerid] = 0;
				case 451: TF_VEH[playerid] = 1;
				case 452..457: TF_VEH[playerid] = 0;
				case 458: TF_VEH[playerid] = 1;
				case 459..465: TF_VEH[playerid] = 0;
				case 466..467: TF_VEH[playerid] = 1;
				case 468..473: TF_VEH[playerid] = 0;
				case 474..475: TF_VEH[playerid] = 1;
				case 476: TF_VEH[playerid] = 0;
				case 477..480: TF_VEH[playerid] = 1;
				case 481..488: TF_VEH[playerid] = 0;
				case 489: TF_VEH[playerid] = 1;
				case 490: TF_VEH[playerid] = 0;
				case 491..492: TF_VEH[playerid] = 1;
				case 493..495: TF_VEH[playerid] = 0;
				case 496: TF_VEH[playerid] = 0;
				case 497..499: TF_VEH[playerid] = 0;
				case 500: TF_VEH[playerid] = 1;
				case 501..504: TF_VEH[playerid] = 0;
				case 505..507: TF_VEH[playerid] = 1;
				case 508..515: TF_VEH[playerid] = 0;
				case 516..518: TF_VEH[playerid] = 1;
				case 519..525: TF_VEH[playerid] = 0;
				case 526..527: TF_VEH[playerid] = 1;
				case 528: TF_VEH[playerid] = 0;
				case 529: TF_VEH[playerid] = 1;
				case 530..532: TF_VEH[playerid] = 0;
				case 533: TF_VEH[playerid] = 1;
				case 534..539: TF_VEH[playerid] = 0;
				case 540..542: TF_VEH[playerid] = 1;
				case 543..544: TF_VEH[playerid] = 0;
				case 545..547: TF_VEH[playerid] = 1;
				case 548: TF_VEH[playerid] = 0;
				case 549..551: TF_VEH[playerid] = 1;
				case 552..554: TF_VEH[playerid] = 0;
				case 555: TF_VEH[playerid] = 1;
				case 556..574: TF_VEH[playerid] = 0;
				case 575: TF_VEH[playerid] = 0;
				case 576..578: TF_VEH[playerid] = 0;
				case 579..580: TF_VEH[playerid] = 1;
				case 581..584: TF_VEH[playerid] = 0;
				case 585: TF_VEH[playerid] = 1;
				case 586: TF_VEH[playerid] = 0;
				case 587: TF_VEH[playerid] = 1;
				case 588: TF_VEH[playerid] = 0;
				case 589: TF_VEH[playerid] = 1;
				case 590..599: TF_VEH[playerid] = 0;
				case 600: TF_VEH[playerid] = 1;
				case 601: TF_VEH[playerid] = 0;
				case 602..603: TF_VEH[playerid] = 1;
				case 604..611: TF_VEH[playerid] = 0;
			}
		}
	}
	return TF_VEH[playerid];
}

stock IsInArchVehicle(playerid)
{
	new vehicleid = GetVehicleModel(GetPlayerVehicleID(playerid));
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			switch(vehicleid)
			{ 
				case 558..562: ARCH_VEH[playerid] = 1;
				case 565: ARCH_VEH[playerid] = 1;
				case 400..557: ARCH_VEH[playerid] = 0;
				case 563..564: ARCH_VEH[playerid] = 0;
				case 566..611: ARCH_VEH[playerid] = 0;
			}
		}
	}
	return ARCH_VEH[playerid];
}

forward MS_OnPlayerPickUpPickup(playerid, pickupid);
public OnPlayerPickUpPickup(playerid, pickupid)
{
	for(new shopid = 0; shopid != MAX_MOD_SHOPS; shopid++)
	{
		if(pickupid == msData[shopid][Pickup] && msData[shopid][Type] == MOD_SHOP_LOCO && IsInLocoVehicle(playerid) == 1 && IsInTfVehicle(playerid) == 0 && IsInArchVehicle(playerid) == 0)
		{
			new Float:X, Float:Y, Float:Z, Float:A;
			GetPlayerPos(playerid,X,Y,Z);
			GetPlayerFacingAngle(playerid,A);
			SetPVarFloat(playerid,"Xpos",X);
			SetPVarFloat(playerid,"Ypos",Y);
			SetPVarFloat(playerid,"Zpos",Z);
			SetPVarFloat(playerid,"ENTER_X",X);
			SetPVarFloat(playerid,"ENTER_Y",Y);
			SetPVarFloat(playerid,"ENTER_Z",Z);
			SetPVarFloat(playerid,"ENTER_A",A);
			SetPlayerVirtualWorld(playerid,random(100));
			new wid = GetPlayerVirtualWorld(playerid);
			SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), wid);
			SetPlayerInterior(playerid,2);
			LinkVehicleToInterior(GetPlayerVehicleID(playerid),2);
			SetVehiclePos(GetPlayerVehicleID(playerid),616.7867,-74.8150,997.7409);
			SetVehicleZAngle(GetPlayerVehicleID(playerid),90.0000);				
			SetPlayerCameraPos(playerid,610.4537,-80.1562,997.9922);
			SetPlayerCameraLookAt(playerid,616.7867,-74.8150,997.7409);
			TogglePlayerControllable(playerid,0);
			SendClientMessage(playerid,-1,"Welcome to Loco!");
			msData[shopid][Pickup] = CreatePickup(1318, 14, X, Y, Z);
			break;
		}
		else if(pickupid == msData[shopid][Pickup] && msData[shopid][Type] == MOD_SHOP_TF && IsInTfVehicle(playerid) == 1 && IsInLocoVehicle(playerid) == 0 && IsInArchVehicle(playerid) == 0)
		{
			new Float:X, Float:Y, Float:Z, Float:A;
			GetPlayerPos(playerid,X,Y,Z);
			GetPlayerFacingAngle(playerid,A);
			SetPVarFloat(playerid,"Xpos1",X);
			SetPVarFloat(playerid,"Ypos1",Y);
			SetPVarFloat(playerid,"Zpos1",Z);			
			SetPVarFloat(playerid,"ENTER_X",X);
			SetPVarFloat(playerid,"ENTER_Y",Y);
			SetPVarFloat(playerid,"ENTER_Z",Z);
			SetPVarFloat(playerid,"ENTER_A",A);
			SetPlayerVirtualWorld(playerid,random(100));
			new wid = GetPlayerVirtualWorld(playerid);
			SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), wid);
			SetPlayerInterior(playerid,1);
			LinkVehicleToInterior(GetPlayerVehicleID(playerid),1);
			SetVehiclePos(GetPlayerVehicleID(playerid),617.5360,-1.9900,1000.6625);
			SetVehicleZAngle(GetPlayerVehicleID(playerid),90.0000);
			SetPlayerCameraPos(playerid,610.8965,0.9562,1000.9219);
			SetPlayerCameraLookAt(playerid,617.5360,-1.9900,1000.6625);
			TogglePlayerControllable(playerid,0);
			SendClientMessage(playerid,-1,"Welcome to TransFender!");
			msData[shopid][Pickup] = CreatePickup(1318, 14, X, Y, Z);
			break;
		}
		else if(pickupid == msData[shopid][Pickup] && msData[shopid][Type] == MOD_SHOP_ARCH && IsInArchVehicle(playerid) == 1 && IsInLocoVehicle(playerid) == 0 && IsInTfVehicle(playerid) == 0)
		{
			new Float:X, Float:Y, Float:Z, Float:A;
			GetPlayerPos(playerid,X,Y,Z);
			GetPlayerFacingAngle(playerid,A);
			SetPVarFloat(playerid,"Xpos2",X);
			SetPVarFloat(playerid,"Ypos2",Y);
			SetPVarFloat(playerid,"Zpos2",Z);
			SetPVarFloat(playerid,"ENTER_X",X);
			SetPVarFloat(playerid,"ENTER_Y",Y);
			SetPVarFloat(playerid,"ENTER_Z",Z);
			SetPVarFloat(playerid,"ENTER_A",A);
			SetPlayerVirtualWorld(playerid,random(100));
			new wid = GetPlayerVirtualWorld(playerid);
			SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), wid);
			SetPlayerInterior(playerid,2);
			LinkVehicleToInterior(GetPlayerVehicleID(playerid),2);
			SetVehiclePos(GetPlayerVehicleID(playerid),616.7867,-74.8150,997.7409);
			SetVehicleZAngle(GetPlayerVehicleID(playerid),90.0000);
			SetPlayerCameraPos(playerid,612.0862,-72.9689,997.9922);
			SetPlayerCameraLookAt(playerid,616.7867,-74.8150,997.7409);
			TogglePlayerControllable(playerid,0);
			SendClientMessage(playerid,-1,"Welcome to Wheel Arch Angels!");
			msData[shopid][Pickup] = CreatePickup(1318, 14, X, Y, Z);
			break;
		}
		break;
	}
	return 1;
}
#if defined _ALS_OnPlayerPickUpPickup
        #undef OnPlayerPickUpPickup
#else
        #define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup MS_OnPlayerPickUpPickup

stock ExitModShop(playerid)
{
	TogglePlayerControllable(playerid,1);
	SetPlayerVirtualWorld(playerid,0);
	SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),0);
	SetPlayerInterior(playerid,0);
	LinkVehicleToInterior(GetPlayerVehicleID(playerid),0);
	SetVehiclePos(GetPlayerVehicleID(playerid),GetPVarFloat(playerid,"ENTER_X")+10,GetPVarFloat(playerid,"ENTER_Y")+10,GetPVarFloat(playerid,"ENTER_Z")+2);
	SetVehicleZAngle(GetPlayerVehicleID(playerid),GetPVarFloat(playerid,"ENTER_A"));
	SetCameraBehindPlayer(playerid);
	DeletePVar(playerid,"ENTER_X");
	DeletePVar(playerid,"ENTER_Y");
	DeletePVar(playerid,"ENTER_Z");
	DeletePVar(playerid,"ENTER_A");
	return 1;
}

stock ModShopCreated(shopid)
{
	if(msData[shopid][Type] != INVALID_MODSHOP) return true;
	else return false;
}