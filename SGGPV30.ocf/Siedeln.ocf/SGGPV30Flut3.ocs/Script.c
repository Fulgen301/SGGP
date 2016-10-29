#strict
#include SGGP
static Regen,CanClose;

func Initialize() 
{
	_inherited();
	SetSkyParallax(1, 20,20, 20,0,0,0);
	ScriptGo(1);
	return(1);
}

func Script10()
{
	CreateMenu(MEPU, GC(), 0, 0,"Regeneinstellungen", 0, 1,1,17);
	CanClose = 0;
	AddMenuItem("S‰ure", Format("bRegen(%d)",1),MEPU, GC());
	AddMenuItem("Lava", Format("bRegen(%d)",2),MEPU, GC());
	AddMenuItem("Wasser", Format("bRegen(%d)",3),MEPU, GC());
	ScriptGo();
}

func bRegen(int iRegen)
{
	CanClose = 1;
	CloseMenu(GC());
	Regen = iRegen;
	if(iRegen == 1) Log("<c ffcc00>Es regnet S‰ure</c>");
	if(iRegen == 2) Log("<c ffcc00>Es regnet Lava</c>");
	if(iRegen == 3) Log("<c ffcc00>Es regnet Wasser</c>");
	if(iRegen == 2)
	{
		CreateMenu(MEPU, GC(), 0, 0,"Lavaeinstellungen", 0, 1,1,17);
		CanClose = 0;
		AddMenuItem("Heiﬂe Lave", Format("bLava(%d)",1),MEPU, GC());
		AddMenuItem("Normale Lava", Format("bLava(%d)",2),MEPU, GC());
	}
	else
	{
		bLava(0);
	}
}
	
func bLava(int iLava)
{
	CanClose = 1;
	CloseMenu(GC());
	if(iLava == 1)
	{
		Log("<c ffcc00>Lava ist heiﬂ</c>");
		CreateObject(HLAV);
	}
	CreateMenu(MEPU, GC(), 0, 0,"Zeiteinstellungen", 0, 1,1,17);
	CanClose = 0;
	AddMenuItem("1 Minuten", Format("Zeit(%d)",1),MEPU, GC());
	AddMenuItem("2 Minuten", Format("Zeit(%d)",2),MEPU, GC());
	AddMenuItem("5 Minuten", Format("Zeit(%d)",5),MEPU, GC());
	AddMenuItem("10 Minuten", Format("Zeit(%d)",10),MEPU, GC());
	AddMenuItem("15 Minuten", Format("Zeit(%d)",15),MEPU, GC());
	AddMenuItem("20 Minuten", Format("Zeit(%d)",20),MEPU, GC());
	AddMenuItem("30 Minuten", Format("Zeit(%d)",30),MEPU, GC());
	AddMenuItem("40 Minuten", Format("Zeit(%d)",40),MEPU, GC());
}

func Zeit(int iZeit)
{
	CanClose = 1;
	CloseMenu(GC());
	Log("<c ffcc00>%d Minuten Aufbauzeit</c>",iZeit);
	SetTime(iZeit,0);
	CreateMenu(MEPU, GC(), 0, 0,"Geldeinstellungen", 0, 1,1,17);
	CanClose = 0;
	AddMenuItem("100 Clunker", Format("Geld(%d)",100),MEPU, GC());
	AddMenuItem("200 Clunker", Format("Geld(%d)",200),MEPU, GC());
	AddMenuItem("500 Clunker", Format("Geld(%d)",500),MEPU, GC());
	AddMenuItem("1000 Clunker", Format("Geld(%d)",1000),MEPU, GC());
	AddMenuItem("2000 Clunker", Format("Geld(%d)",2000),MEPU, GC());
}

func Geld(iGeld)
{
	CanClose = 1;
	CloseMenu(GC());
	Log("<c ffcc00>%d Clunker Geld</c>",iGeld);
	var i;
	while(i < GetPlayerCount())
	{
		SetWealth(i,iGeld);
		i++;
	}
}

func MenuQueryCancel(int iSelection, object pCaller)
{
	if(GetMenu(pCaller) == 17 && !CanClose) return(1);
}

func TimerDown()
{
	if(Regen == 1)
	{ 
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,999999);
	}
	if(Regen == 2)
	{
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,999999);
	}
	if(Regen == 3) 
	{
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Water"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Water"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Water"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Water"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Water"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Water"),LandscapeWidth()-10,999999);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Water"),LandscapeWidth()-10,999999);
	}
}