#strict

#include SGGP

static Deaths1,Deaths2,helper;
func Initialize() 
{
	_inherited();
	SetSkyParallax(1, 20,20, 0,0, SkyPar_Keep(),SkyPar_Keep());
	CreateGate(SGR2,STGT, 2555, 280, -1,"Jaffa");
	CreateObject(DHD_,2503,185,-1);
	CreateGate(SGR2,STGT, 2553, 1378, -1,"Wraith");
	CreateObject(DHD_,2478,1375,-1);
	UpdateScoreboard();
	helper = 1;
	ScriptGo(0);
	return(1);
}

func InitializePlayer(int iPlayer)
{
	_inherited();
	var pClonk;
	if(GetPlayerTeam(iPlayer) == 1)
	{
		pClonk = CreateObject(JAFA,0,0,iPlayer);
		pClonk -> Enter(FindObject(GOEB,0,0,LandscapeWidth(),LandscapeHeight()/2));
		MakeCrewMember(pClonk,iPlayer);
		CreateContents(FLAG,pClonk);
		SetCursor(iPlayer,pClonk);
		pClonk = CreateObject(JAFA,0,0,iPlayer);
		pClonk -> Enter(FindObject(GOEB,0,0,LandscapeWidth(),LandscapeHeight()/2));
		MakeCrewMember(pClonk,iPlayer);
	}
	if(GetPlayerTeam(iPlayer) == 2)
	{
		pClonk = CreateObject(WRAT,0,0,iPlayer);
		pClonk -> Enter(FindObject(GOEB,0,LandscapeHeight()/2,LandscapeWidth(),LandscapeHeight()/2));
		MakeCrewMember(pClonk,iPlayer);
		CreateContents(FLAG,pClonk);
		SetCursor(iPlayer,pClonk);
		pClonk = CreateObject(WRAT,0,0,iPlayer);
		pClonk -> Enter(FindObject(GOEB,0,LandscapeHeight()/2,LandscapeWidth(),LandscapeHeight()/2));
		MakeCrewMember(pClonk,iPlayer);
	}
}

func OnClonkDeath(object pClonk)
{
	if(GetPlayerTeam(GetOwner(pClonk)) == 1) Deaths1++;
	if(GetPlayerTeam(GetOwner(pClonk)) == 2) Deaths2++;
	UpdateScoreboard();
}

func UpdateScoreboard()
{
	SetScoreboardData(1,1,"Team");
	SetScoreboardData(1,2,"Tode");
	SetScoreboardData(1,1,"Jaffa");
	SetScoreboardData(2,1,"Wraith");
	SetScoreboardData(1,2,Format("%d",Deaths1));
	SetScoreboardData(2,2,Format("%d",Deaths2));
	SetScoreboardData(SBRD_Caption,SBRD_Caption,"Tode");
}

func Script21600()
{
	helper = 0;
}
