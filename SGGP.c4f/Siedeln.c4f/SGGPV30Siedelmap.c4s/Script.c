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
		CreateMenu(MEPU, GetCursor(), 0, 0,"Geldeinstellungen", 0, 1,1,17);
		CanClose = 0;
		AddMenuItem("100 Clunker", Format("Geld(%d)",100),MEPU, GetCursor());
		AddMenuItem("200 Clunker", Format("Geld(%d)",200),MEPU, GetCursor());
		AddMenuItem("500 Clunker", Format("Geld(%d)",500),MEPU, GetCursor());
		AddMenuItem("1000 Clunker", Format("Geld(%d)",1000),MEPU, GetCursor());
		AddMenuItem("2000 Clunker", Format("Geld(%d)",2000),MEPU, GetCursor());
	ScriptGo();
}

func Geld(int iGeld)
{
	CanClose = 1;
	CloseMenu(GetCursor());
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
