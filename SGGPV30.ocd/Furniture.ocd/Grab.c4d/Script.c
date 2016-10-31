#strict
local Can,Zahl;
func Initialize() 
{
	Can = 0;
	SetRandom();
	return(1);
}


func Enable()
{
	Can = 1;
}

func Disable()
{
	Can = 0;
}
	
func Damage()
{
	if(GetDamage() > 200)
	{
		CastObjects(ROCK,3,15);
		CastObjects(BONE,6,15);
	    var pZombie;
	    pZombie = CreateObject(ZCLK,0,0,-1);
	    pZombie -> SetColorDw(HSL(Random(256),255,127));
    	pZombie -> Zombize();
    	pZombie -> SetComDir(COMD_Left);
	    pZombie = CreateObject(ZCLK,0,0,-1);
	    pZombie -> SetColorDw(HSL(Random(256),255,127));
    	pZombie -> Zombize();
    	pZombie -> SetComDir(COMD_Left);
	    pZombie = CreateObject(ZCLK,0,0,-1);
	    pZombie -> SetColorDw(HSL(Random(256),255,127));
    	pZombie -> Zombize();
    	pZombie -> SetComDir(COMD_Left);
	    pZombie = CreateObject(ZCLK,0,0,-1);
	    pZombie -> SetColorDw(HSL(Random(256),255,127));
    	pZombie -> Zombize();
    	pZombie -> SetComDir(COMD_Left);
		RemoveObject();	
	}
}

func IsBulletTarget() 
{
	return(true);
}

func SetRandom()
{
	var iRand;
	iRand = RandomX(1,6);
	SetAction(Format("%d",iRand));
}

func Set(int iAct)
{
	SetAction(Format("%d",iAct));
}

func Create()
{
	Zahl++;
	if(Zahl > 200 - GetPlayerCount()*10) Zahl = 1;
	if(Can && Zahl == 1) 
	{
	    if(ObjectCount(ZCLK) > 100 * GetPlayerCount()) return();
	    var pZombie;
	    pZombie = CreateObject(ZCLK,0,0,-1);
	    pZombie -> SetColorDw(HSL(Random(256),255,127));
    	pZombie -> Zombize();
    	pZombie -> SetComDir(COMD_Left);
    }
}


global func ZombieSpawnOn()
{
		var pGrab;
		for(pGrab in FindObjects(Find_ID(GRAV)))
		{
			pGrab -> Enable();
		}
		return();
}

global func ZombieSpawnOff()
{
		var pGrab;
		for(pGrab in FindObjects(Find_ID(GRAV)))
		{
			pGrab -> Disable();
		}
		return(1);
}
local Name = "$Name$";
