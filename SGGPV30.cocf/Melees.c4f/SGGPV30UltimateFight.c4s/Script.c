#strict
#include SGGP
static aRels,aDeaths,aKills;
func Initialize() 
{
	_inherited();
	aRels = CreateArray(12);
	aDeaths = CreateArray(12);
	aKills = CreateArray(12);
	CreateObject(DARK);
	CreateObject(DARK);
	CreateObject(DARK);
   	ScriptGo(1);
	return(1);
}

func InitializePlayer(int iPlayer)
{
	_inherited();
	SetWealth(iPlayer,50);
	aRels[iPlayer] = 13;
	UpdateScoreboard();
	RelaunchPlayer(iPlayer);
}

func RelaunchPlayer(int iPlayer)
{
	aRels[iPlayer]--;
	if(aRels[iPlayer] >= 0)
	{
		var pClonk;
		var Ran;
		Ran = RandomX(0,5);
		pClonk = CreateObject(RandCl(),RandX(Ran),RandY(Ran),iPlayer);
		MakeCrewMember(pClonk,iPlayer);
		SetCursor(iPlayer,pClonk);
		pClonk -> SetPlrViewRange(250);
	}
	UpdateScoreboard();
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
		DoWealth(iKilledBy,50);
	}
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
	var a;
	a = CreateArray(6);
	a = [25,343,1125,1006,1176,1921];
	return(a[i]);
}

func RandY(int i)
{
	var a;
	a = CreateArray(6);
	a = [460,240,319,190,90,310];
	return(a[i]);
}

func Script1()
{
	var pCl;
	for(pCl in FindObjects(Find_OCF(OCF_CrewMember)))
	{
		pCl -> SetPlrViewRange(250);
	}
}
	
func Script2()
{
	var i;
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			DoWealth(i,5);
		}
		i++;
	}
	Sound("Cash",1);
}

func Script50()
{
	goto(2);
}

func UpdateScoreboard()
{
	var i;
	SetScoreboardData(SBRD_Caption,SBRD_Caption,"Relaunches");
	SetScoreboardData(1,0,"Name",100);
	SetScoreboardData(1,1,"{{WRAT}}",100);
	SetScoreboardData(1,2,"{{SKUL}}",100);
	SetScoreboardData(1,3,"{{ROGN}}",100);
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			SetScoreboardData(i+2,0,GetTaggedPlayerName(i));
			SetScoreboardData(i+2,1,Format("%d",aRels[i]),aRels[i]);
			SetScoreboardData(i+2,2,Format("%d",aDeaths[i]),aDeaths[i]);
			SetScoreboardData(i+2,3,Format("%d",aKills[i]),aKills[i]);
		}
		i++;
	}
	SortScoreboard(3,1);
}