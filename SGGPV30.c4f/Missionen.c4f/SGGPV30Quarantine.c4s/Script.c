/*-- Quarantine --*/

#strict
#include SGGP
func Initialize()
{
	_inherited();
	RemoveAll(HELP);
	CreateObject(HELP);
	LocalN("lock",FindObject(TAMA)) = 1;
	FindObject(TAMA) -> SetAction("Active");
	CreateObject(MAGO) -> SetMissionAccess("SGGP 4");
	SetTime(6,0);
	ChangeTimerCount(-1);
}

func RelaunchPlayer(int iPlayer) 
{
    var Clonk;
    Clonk = CreateObject(SGK_,1,1500,iPlayer);
    Clonk->SetPosition(955,1490);
    Clonk->SetName("John Sheppard");
    Clonk->CreateContents(C4ZU);
    Clonk->CreateContents(C4EP,0,15);
    MakeCrewMember(Clonk, iPlayer);
    SetCursor(iPlayer, Clonk);
}

func InitializePlayer(int iPlr)
{
	_inherited();
	RelaunchPlayer(iPlr);
}

func TimerDown()
{
	var i;
	while(i < GetPlayerCount())
	{
		EliminatePlayer(i);
		i++;
	}
}