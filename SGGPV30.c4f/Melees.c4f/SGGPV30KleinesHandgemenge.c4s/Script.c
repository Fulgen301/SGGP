/*-- Kleines Handgemenge --*/

#strict

#include SGGP

static g_iSpawnCount,aRels,aDeaths,aKills,RanX,aPoints;

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
	ScriptGo(1);
	SetSkyParallax(1, 20,20, 20,0, SkyPar_Keep(),SkyPar_Keep());  
	return(1);
}

func Script100()
{
	for (var i=0; i<GetPlayerCount(); ++i)
	{
		var id = getSpawnType();
		var x = 10 + Random(LandscapeWidth() - 20);
		var h = GetHorizonHeight(x);
		var y = h + 10 + Random(LandscapeHeight() - h - 20);
		if (GetMaterial(x, y) != Material("Earth")) continue;
		var effect = AddEffect("SpawnSparkle", 0, 1, 5, 0, 0);
		EffectVar(0, 0, effect) = id; EffectVar(1, 0, effect) = x; EffectVar(2, 0, effect) = y;
	}
	g_iSpawnCount++;  
	goto(30);  
}

func getSpawnType()
{
	var id = [PIWP,WRBO,P90_,WRST,STBW,HARM,TACM,NANO,GOBE,HEGR];
	return (id[Random(1 + Min(g_iSpawnCount/2, GetLength(id)))]);
}  

func GetHorizonHeight(x)
{
	var y;
	while (y < LandscapeHeight() && !GBackSemiSolid(x, y))
	y += 10;
	while (y > LandscapeHeight() && GBackSemiSolid(x, y))
	--y;
	return(y);
}

global func FxSpawnSparkleTimer(obj, effect, time)
{
	var id = EffectVar(0, 0, effect); var x = EffectVar(1, 0, effect); var y = EffectVar(2, 0, effect);
	CreateParticle("NoGravSpark", x + RandomX(-6,+6), y + RandomX(-6,+6), 0, -3, RandomX(30,50), RGB(64,64,255));
	if ((time >= 100) && !EffectVar(3, 0, effect)) 
	EffectVar(3, 0, effect) = CreateObject(id, x, y);
	if (time >= 150) return(-1);
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
	aRels[iPlayer] = 9;
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
	DoWealth(-50,GetOwner(pKill));
	aPoints[GetOwner(pKill)] = 0;
	UpdateScoreboard();
}

func RandCl()
{
	var aCl;
	aCl = CreateArray(3);
	aCl = [SGK_,JAFA,WRAT];
	return(aCl[Random(3)]);
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