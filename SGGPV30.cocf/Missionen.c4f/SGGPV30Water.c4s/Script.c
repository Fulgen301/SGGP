#strict
#include SGGP
func RelaunchPlayer(int iPlayer) 
{
    var Clonk;
    Clonk = CreateObject(SGK_,1,1500,iPlayer);
    Clonk->SetPosition(120,880);
    CreateContents(HEGR,Clonk);
    CreateContents(P90_,Clonk);
    CreateContents(FLSH,Clonk);
    CreateContents(LZD_,Clonk);
    CreateContents(HARM,Clonk);
    MakeCrewMember(Clonk, iPlayer);
    Clonk = CreateObject(SGK_,1,1500,iPlayer);
    Clonk->SetPosition(120,880);
    MakeCrewMember(Clonk, iPlayer);
    CreateContents(HEGR,Clonk);
    CreateContents(SP12,Clonk);
    CreateContents(FLSH,Clonk);
    CreateContents(HARM,Clonk);
    SetCursor(iPlayer, Clonk);
	RemoveAll(NOKR);
	RemoveAll(UMBE);
	RemoveAll(NOPW);
}



func InitializePlayer(int iPlr)
{
	_inherited();
	RelaunchPlayer(iPlr);
}


func Initialize()
{
	_inherited();
	CreateGate(SGR1,STGT, 268, 1428, -1,"Russen");
	CreateGate(SGR2,STGT, 2638, 2358, -1,"Wasser");
	FindObject(_CST)->CreateContents(DHDK);
	ScriptGo(1);
	CreateObject(NQSH)-> SetMissionAccess("SGGP 2");
	SetDarkness(3);
	Music("Joel Goldsmith - Gate to Atlantis.ogg");
	FindObject(ALGH)->TurnOff();
	FindObject(ALGH)->TurnOn();
	IsNight();
	RemoveAll(NODR);
  return(1);
}
