#strict
#include SGGP
static aRels;
func Initialize() 
{  
	_inherited();
	aRels = CreateArray(12);
	CreateGate(SGR1, STGT, 1869, 2540, -1,[8,9,13,14,15,12,4]);
	CreateGate(SGR1, STGT, 1905, 1585, -1,[9,2,6,12,15,4,8]);
	CreateObject(DHD_,1693,1454,-1);
	CreateObject(DHD_,1892,2524,-1);
}

func InitializePlayer(int iPlayer)
{
	_inherited();
	aRels[iPlayer] = 10;
	UpdateScoreboard();
}

func RelaunchPlayer(int iPlayer)
{
	aRels[iPlayer]--;
	if(aRels[iPlayer] >= 0)
	{
		var pClonk;
		var Ran;
		Ran = RandomX(0,8);
		pClonk = CreateObject(RandCl(),RandX(Ran),RandY(Ran),iPlayer);
		pClonk -> CreateContents(PIWP);
		MakeCrewMember(pClonk,iPlayer);
		SetCursor(iPlayer,pClonk);
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
	a = CreateArray(9);
	a = [555,466,1250,1148,652,207,237,1025,1737];
	return(a[i]);
}

func RandY(int i)
{
	var a;
	a = CreateArray(9);
	a = [539,691,691,1371,1523,1331,2160,2290,2130];
	return(a[i]);
}

func UpdateScoreboard()
{
	var i;
	SetScoreboardData(SBRD_Caption,SBRD_Caption,"Relaunches");
	SetScoreboardData(1,0,"Name",100);
	SetScoreboardData(1,1,"Relaunches",100);
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			SetScoreboardData(i+2,0,GetTaggedPlayerName(i));
			SetScoreboardData(i+2,1,Format("%d",aRels[i]),aRels[i]);
		}
		i++;
	}
	SortScoreboard(1,1);
}
