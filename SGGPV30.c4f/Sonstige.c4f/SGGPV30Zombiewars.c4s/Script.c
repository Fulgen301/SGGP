#strict
#include SGGP
static passed;
func Initialize() 
{
	_inherited();
	CreateObject(NOFO);
	CreateObject(NOAM);
	CreateObject(NOKR);
	CreateObject(AUBA);
	CreateObject(AUBA);
	CreateObject(HELP);
	SetTime(4,30);
	var pCol;
	for(pCol in FindObjects(Find_Or(Find_ID(CLM1),Find_ID(CLM2))))
	{
		pCol -> SetCategory(C4D_StaticBack);
	}
	ChangeTimerCount(-1);
	ScriptGo(1);
	return(1);
}

func Script1()
{
	var i;
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			DoWealth(i,100);
		}
		i++;
	}
}

func InitializePlayer(int iPlayer)
{
	if(GetPlayerName(iPlayer))
	{
		var i;
		var pCrew;
		var Flag;
		while(pCrew = GetCrew(iPlayer,i))
		{
			pCrew -> SetPosition(1935,851);
			pCrew -> CreateObject(CNKT,0,20,iPlayer);
			if(!Flag)
			{
				pCrew -> CreateObject(FLAG,0,20,iPlayer);
				Flag = 1;
			}
			i++;
		}
	}
}

func TimerDown()
{
	if(!passed)
	{
		CreateObject(G_ZH);
		ZombieSpawnOn();
		passed = 2;
		RemoveAll(TIMR);
		return();
	}
}

func Script10()
{
	if(passed > 1) passed++;
	if(passed > 8) passed = 2;
	if(passed == 2)
	{
	}
	Schedule("Smoke(RandomX(3462,LandscapeWidth()),843,RandomX(5,40))",1,30);
}

func Script15()
{
	Schedule("Smoke(RandomX(3462,LandscapeWidth()),843,RandomX(5,40))",1,30);
}
 
func Script20()
{
	Schedule("Smoke(RandomX(3462,LandscapeWidth()),843,RandomX(5,40))",1,30);

	goto(1);
}