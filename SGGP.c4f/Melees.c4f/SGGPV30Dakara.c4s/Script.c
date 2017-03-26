
#strict

#include SGGP

static aRels,aDeaths,aKills,RanX,aPoints;

func Initialize() 
{
	_inherited();
	aRels = CreateArray(12);
	aDeaths = CreateArray(12);
	aKills = CreateArray(12);
	aPoints = CreateArray(12);
	CreateObject(DARK);
	CreateObject(DARK);
	CreateObject(DARK);
	CreateGate(SGR2,STGT, 2501, 700, NO_OWNER);
	CreateObject(DHD_, 2410, 692, NO_OWNER);
	ScriptGo(1);
	SetSkyParallax(1, 20,20, 20,0, SkyPar_Keep(),SkyPar_Keep());  
	PlaceSpawnpoint(GOBE,485,1080,1000);
	PlaceSpawnpoint(GOBE,1130,665,1000);
	PlaceSpawnpoint(ROGN,690,665,1000);
	PlaceSpawnpoint(ZATN,1500,1080,1000);
	PlaceSpawnpoint(WRGR,1390,1035,1000);
	PlaceSpawnpoint(HEGR,200,1020,1000);
	PlaceSpawnpoint(WRST,1180,770,1000);
	PlaceSpawnpoint(TACM,1310,660,1000);
	PlaceSpawnpoint(P90_,1875,780,1000);
	PlaceSpawnpoint(WRGR,1730,1000,1000);
	PlaceSpawnpoint(STBW,1567,754,1000);
	PlaceSpawnpoint(WRBO,303,662,1000);
	PlaceSpawnpoint(GOBE,2498,659,1000);
	PlaceSpawnpoint(GOTA,1000,659,1000);
	CreateObject(NODR,100,100);
	RemoveAll(WPST);
	RemoveAll(TEL_);
	RemoveAll(TELO);
	
	var ring1 = CreateObject(RIG1, 399, 671, NO_OWNER);
	ring1->SetName("Dakara 1");
	CreateObject(RIG2,354,693,NO_OWNER)->SetTransporter(ring1);
	
	var ring2 = CreateObject(RIG1, 1713, 1062, NO_OWNER);
	ring2->SetName("Dakara 2");
	CreateObject(RIG2, 1760, 1084, NO_OWNER)->SetTransporter(ring2);
	return(1);
}


func UpdateScoreboard()
{
	var i;
	SetScoreboardData(SBRD_Caption,SBRD_Caption,"Relaunches");
	SetScoreboardData(1,0,"Name",100);
	SetScoreboardData(1,1,"{{WRAT}}",10000);
	SetScoreboardData(1,2,"{{SKUL}}",10000);
	SetScoreboardData(1,3,"{{ROGN}}",10000);
	SetScoreboardData(1,4,"{{GOLD}}",10000);
	SetScoreboardData(1,5,"{{MEPU}}",10000);
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			SetScoreboardData(i+2,0,GetTaggedPlayerName(i));
			SetScoreboardData(i+2,1,Format("%d",aRels[i]),aRels[i]);
			SetScoreboardData(i+2,2,Format("%d",aDeaths[i]),aDeaths[i]);
			SetScoreboardData(i+2,3,Format("%d",aKills[i]),aKills[i]);
			SetScoreboardData(i+2,4,Format("<c ffcc00>%d</c>",GetWealth(i)),GetWealth(i));
			SetScoreboardData(i+2,5,Format("<c 00ff00>%d</c>",5-aPoints[i]),5-aPoints[i]);
		}
		else
		{
			SetScoreboardData(i+2,0,GetTaggedPlayerName(i));
			SetScoreboardData(i+2,1,"<c ff0000>Eliminiert</c>",0);
			SetScoreboardData(i+2,2," ",0);
			SetScoreboardData(i+2,3," ",0);
			SetScoreboardData(i+2,4," ",0);
			SetScoreboardData(i+2,5," ",0);
		}	
		i++;
	}
	SortScoreboard(4,1);
}

func InitializePlayer(int iPlayer)
{
	_inherited();
	aRels[iPlayer] = 13;
	UpdateScoreboard();
	SetFoW(0,iPlayer);
	RelaunchPlayer(iPlayer);
}

func RelaunchPlayer(int iPlayer)
{
	if(GetPlayerName(iPlayer))
	{
		aRels[iPlayer]--;
		if(aRels[iPlayer] >= 0)
		{
			var pClonk;
			/*var Ran;
			Ran = RandomX(0,5);*/
			RanX = RandX();
			pClonk = CreateObject(RandCl(),RanX,RandY(),iPlayer);
			MakeCrewMember(pClonk,iPlayer);
			SetCursor(iPlayer,pClonk);
			pClonk -> SetPlrViewRange(250);
		}
		UpdateScoreboard();
	}
}

func OnClonkDeath(object pKill)
{
	if(GetID(pKill) == S23F) return(RelaunchPlayer());
	var iKilledBy;
	iKilledBy = GetKiller(pKill);
	aDeaths[GetOwner(pKill)]++;
	if(iKilledBy != GetOwner(pKill) && iKilledBy > NO_OWNER) 
	{
		aKills[iKilledBy]++;
		DoWealth(iKilledBy,50 + aPoints[iKilledBy] * 50);
		aPoints[iKilledBy] ++;
		if(aPoints[iKilledBy] >= 5)
		{
			aRels[iKilledBy]++;
			Log("%s hat sich einen Relaunch verdient!",GetTaggedPlayerName(iKilledBy));
			GetCursor(iKilledBy) -> CastParticles("FSpark", 10,100, 0,0, 100, 200, RGBa(50,50,255,0),RGBa(0,0,255,128));
			aPoints[iKilledBy] = 0;
		}
	}
	DoWealth(GetOwner(pKill), -50);
	aPoints[GetOwner(pKill)] = 0;
	UpdateScoreboard();
}

func RandCl()
{
	return [SGK_,JAFA,WRAT][Random(3)];
}

func RandX(int i)
{
	/*var a;
	a = CreateArray(6);
	a = [25,343,1125,1006,1176,1921];*/
	return(Random(LandscapeWidth()));
}

func RandY(int i)
{
	var a;
	a = LandscapeHeight() -20;
	while(GBackSolid(RanX,a)||GBackLiquid(RanX,a)) a-=2;
	/*var a;
	a = CreateArray(6);
	a = [460,240,319,190,90,310];*/
	return(a);
}
