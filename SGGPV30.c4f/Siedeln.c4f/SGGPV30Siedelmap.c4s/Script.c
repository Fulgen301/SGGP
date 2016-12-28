#strict
#include SGGP
static CanClose;

func Initialize() 
{
	_inherited(...);
	SetSkyParallax(1, 20,20, 20,0,0,0);
	return(1);
}

protected func InitializePlayer(int iPlr)
{
	if(iPlr) return;
		CreateMenu(MEPU, GetCursor(iPlr), 0, 0,"Geldeinstellungen", 0, 1,1,17);
		CanClose = 0;
		AddMenuItem("100 Clunker", Format("Geld(%d)",100),MEPU, GetCursor(iPlr));
		AddMenuItem("200 Clunker", Format("Geld(%d)",200),MEPU, GetCursor(iPlr));
		AddMenuItem("500 Clunker", Format("Geld(%d)",500),MEPU, GetCursor(iPlr));
		AddMenuItem("1000 Clunker", Format("Geld(%d)",1000),MEPU, GetCursor(iPlr));
		AddMenuItem("2000 Clunker", Format("Geld(%d)",2000),MEPU, GetCursor(iPlr));
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
