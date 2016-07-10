/*-- Puddle-Jumper-Training --*/

#strict
#include SGGP

func Initialize() 
{
	_inherited();
	var Goal;
	RemoveAll(RMOB);
	Goal = CreateObject(RMOB);
	Goal -> AddType(TRGT);
	Goal -> SetMissionAccess("SGGP 3");
	SetSkyParallax(0,14,30);
	ScriptGo(1);
	return(1);
	CreateGate(SGR2, STGT, 3333, 1090, -1, "Tempel 1");
	CreateGate(SGR2, STGT, 4548, 128, -1, "Tempel 2");
}

func Script2()
{
	RemoveAll(CLNK);
	CreateContents(KRST,FindObject(PUD_));
	return(1);
}

func RelaunchPlayer(int iPlayer) 
{
    var Clonk;
    Clonk = CreateObject(SGK_,1,1500,iPlayer);
    Clonk->SetPosition(13,524);
    MakeCrewMember(Clonk, iPlayer);
    SetCursor(iPlayer, Clonk);
}

func InitializePlayer(int iPlr)
{
	_inherited();
	RelaunchPlayer(iPlr);
}
