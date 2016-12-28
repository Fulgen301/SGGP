#strict
#include SGGP
static CanClose;

func Initialize() 
{
	_inherited(...);
	SetSkyParallax(1, 20,20, 20,0,0,0);
	ScriptGo(1);
	return(1);
}

func Script10()
{
		CreateMenu(MEPU, GC(), 0, 0,"Geldeinstellungen", 0, 1,1,17);
		CanClose = 0;
		AddMenuItem("100 Clunker", Format("Geld(%d)",100),MEPU, GC());
		AddMenuItem("200 Clunker", Format("Geld(%d)",200),MEPU, GC());
		AddMenuItem("500 Clunker", Format("Geld(%d)",500),MEPU, GC());
		AddMenuItem("1000 Clunker", Format("Geld(%d)",1000),MEPU, GC());
		AddMenuItem("2000 Clunker", Format("Geld(%d)",2000),MEPU, GC());
	ScriptGo();
}

func Geld(int iGeld)
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
