#strict

#include SGGP


func Initialize()
{
	_inherited();
	ScriptGo(1);
	static aRel;
	static aRek;
	static aKil;
	static Counter;
	static aDea;
	SetSkyParallax(0,100,100,2);
	aRel = CreateArray(GetPlayerCount());
	aDea = CreateArray(GetPlayerCount());
	aRek = CreateArray(GetPlayerCount());
	aKil = CreateArray(GetPlayerCount());
	var i;
	while(i < GetLength(aRel))
	{
		aRel[i] = 10;
		i++;
	}
	CreateObject(MEL2);
	UpdateScoreboard();
	var pRa;
	FreeRect(0,0,LandscapeWidth(),LandscapeHeight());
	pRa = RandomX(1,7);
	if(pRa == 1) 
	{
		DrawMaterialQuad("Ashes", 0,400, LandscapeWidth(),400, LandscapeWidth(),LandscapeHeight(), 0,LandscapeHeight(),1);
		while(i < 10)
		{
			i++;
			PlaceVegetation(TRB1,0,0,LandscapeWidth(),LandscapeHeight(),-1);
			PlaceVegetation(TRB2,0,0,LandscapeWidth(),LandscapeHeight(),-1);
			PlaceVegetation(TRB3,0,0,LandscapeWidth(),LandscapeHeight(),-1);
		}
	}
	if(pRa == 2) 
	{
		DrawMaterialQuad("FlyAshes", 0,400, LandscapeWidth(),400, LandscapeWidth(),LandscapeHeight(), 0,LandscapeHeight(),1);
		while(i < 10)
		{
			i++;
			PlaceVegetation(TRB1,0,0,LandscapeWidth(),LandscapeHeight(),-1);
			PlaceVegetation(TRB2,0,0,LandscapeWidth(),LandscapeHeight(),-1);
			PlaceVegetation(TRB3,0,0,LandscapeWidth(),LandscapeHeight(),-1);
		}
	}
	if(pRa == 3) 
	{
		DrawMaterialQuad("Snow", 0,400, LandscapeWidth(),400, LandscapeWidth(),LandscapeHeight(), 0,LandscapeHeight(),1);
		while(i < 30)
		{
			i++;
			PlaceVegetation(TRE4,0,0,LandscapeWidth(),LandscapeHeight(),-1);
		}
	}
	if(pRa == 4) 
	{
		DrawMaterialQuad("Sand", 0,400, LandscapeWidth(),400, LandscapeWidth(),LandscapeHeight(), 0,LandscapeHeight(),1);
		while(i < 15)
		{
			i++;
			PlaceVegetation(CACT,0,0,LandscapeWidth(),LandscapeHeight(),-1);
			PlaceVegetation(CAC2,0,0,LandscapeWidth(),LandscapeHeight(),-1);
		}
	}
	if(pRa == 5) 
	{
		DrawMaterialQuad("FlySand", 0,400, LandscapeWidth(),400, LandscapeWidth(),LandscapeHeight(), 0,LandscapeHeight(),1);
		while(i < 15)
		{
			i++;
			PlaceVegetation(PLM1,0,0,LandscapeWidth(),LandscapeHeight(),-1);
			PlaceVegetation(PLM2,0,0,LandscapeWidth(),LandscapeHeight(),-1);
		}
	}
	if(pRa == 6) 
	{
		DrawMaterialQuad("Earth", 0,400, LandscapeWidth(),400, LandscapeWidth(),LandscapeHeight(), 0,LandscapeHeight(),1);
		while(i < 10)
		{
			i++;
			PlaceVegetation(TRE1,0,0,LandscapeWidth(),LandscapeHeight(),-1);
			PlaceVegetation(TRE2,0,0,LandscapeWidth(),LandscapeHeight(),-1);
			PlaceVegetation(TRE3,0,0,LandscapeWidth(),LandscapeHeight(),-1);
		}
	}
	if(pRa == 7) 
	{
		DrawMaterialQuad("Ice", 0,400, LandscapeWidth(),400, LandscapeWidth(),LandscapeHeight(), 0,LandscapeHeight());
	}
}

func OnClonkCreation(object pClonk)
{
	SetClrModulation(RGBa(50,50,255,128),pClonk);
	SetVisibility(VIS_God,pClonk);
	SetVisibility(VIS_Owner,pClonk);
	var pWepn;
	pWepn = CreateObject(JTPK);
	pWepn -> Enter(pClonk);
	pWepn -> Activate(pClonk);
	pWepn = CreateObject(BZWP);
	pWepn -> Upgrade(KLAS);
	pWepn -> Enter(pClonk);
	pWepn = CreateObject(GLWP);
	pWepn -> Upgrade(KLAS);
	pWepn -> Upgrade(KRFL);
	pWepn -> Upgrade(KSLM);
	pWepn -> Enter(pClonk);
	pWepn = CreateObject(LZD_);
	CreateContents(P90_,pClonk);
	pWepn -> Upgrade(KRFL);
	pWepn -> Enter(pClonk);
	return(1);
}

func InitializePlayer(int iPlr)
{
	_inherited();
	SetLength(aRel,GetPlayerCount());
	SetLength(aDea,GetPlayerCount());
	aRel[iPlr] = 10;
	aDea[iPlr] = 0;
	UpdateScoreboard();
}

func RelaunchPlayer(int iPlr,object pClonk,int iKiller)
{
	if(iKiller != iPlr) 
	{
		aRel[iPlr]--;
		aDea[iPlr]++;
		aKil[iKiller]++;
		aRek[iKiller]++;
		if(aRek[iKiller] > 2)
		{
			aRel[iKiller]++;
			Log("%s <c ffcc00>Hat sich einen Relaunch verdient!</c>",GetTaggedPlayerName(iKiller));
			aRek[iKiller] = 0;
			GetCursor(iKiller) -> CastParticles("FSpark", 10,100, 0,0, 100, 200, RGBa(50,50,255,0),RGBa(0,0,255,128));
		}
	}
	if(aRel[iPlr] < 0) return();
	var Clonk;
	Clonk = CreateObject(SGK_,Random(LandscapeWidth()),Random(300),iPlr);
	MakeCrewMember(Clonk,iPlr);
	SetCursor(iPlr,Clonk);
	UpdateScoreboard();
}

func UpdateScoreboard()
{
	var i;
	SetScoreboardData(SBRD_Caption ,SBRD_Caption ,"Scoreboard",12);
	SetScoreboardData(0,0,"Name",11);
	SetScoreboardData(0,1,"{{JAFA}}",11);
	SetScoreboardData(0,2,"{{BONE}}",11);
	SetScoreboardData(0,3,"{{ROGN}}",11);
	while(i < GetLength(aRel))
	{
		if(GetPlayerName(i) && GetPlayerType(i) == C4PT_User)
		{
			SetScoreboardData(i+1,0,GetTaggedPlayerName(i));
			SetScoreboardData(i+1,1,Format("<c %x>%d</c>",GetPlrColorDw(i),aRel[i]),aRel[i]);
			SetScoreboardData(i+1,2,Format("<c %x>%d</c>",GetPlrColorDw(i),aDea[i]),aDea[i]);
			SetScoreboardData(i+1,3,Format("<c %x>%d</c>",GetPlrColorDw(i),aKil[i]),aKil[i]);
		}
		i++;
	}
	SortScoreboard(1,3);
}

func Script40()
{
	goto(2);
	var aBonus;
	aBonus = CreateArray(20);
	aBonus = [ZATN,PGWP,PIWP,MEDI,MEDI,MEDI,MEDI,MEDI,MEDI,MEDI,HEGR,HEGR,HEGR,GOBE,GOBE,GOBE,ZATN,NANO,ROGN,STBW];
	var pBonus;
	var idID;
	idID = aBonus[Random(GetLength(aBonus))];
	pBonus = CreateObject(idID,Random(LandscapeWidth()),RandomX(300,400));
	pBonus -> CastParticles("FSpark", 10,100, 0,0, 100, 200, RGBa(255,0,0,0),RGBa(255,128,0,128));
	if(idID == PGWP)
	{
		pBonus -> Upgrade(KRFL);
	}
	if(idID == PIWP)
	{
		pBonus -> Upgrade(KRFL);
		pBonus -> Upgrade(KLAS);
		pBonus -> Upgrade(KSLM);
	}
	if(Counter < 15) Counter++;
	if(Counter == 15)
	{
		Counter = 20;
		var pRa;
		pRa = RandomX(1,2);
		if(pRa == 1) 
		{
			CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,100000);
			CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,100000);
			CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,100000);
		}
		if(pRa == 2)
		{
			CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,100000);
			CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,100000);
			CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("DuroLava"),LandscapeWidth()-10,100000);
		}
	}
}