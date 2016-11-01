#strict
local TimeToLive;
func Initialize()
{
	SetAction(Format("%d",RandomX(1,15)));
	TimeToLive = 0;
	SetRDir(RandomX(-10,10));
}

func Timer()
{
	TimeToLive++;
	SetYDir(RandomX(5,-5));
//	if(TimeToLive < 200) CastPXS("FlyAshes",1,5,RandomX(-20,20),RandomX(-20,20));
	SetXDir(RandomX(-5,5));
	SetClrModulation(RGBa(255,255,255,TimeToLive));
	var pCl;
	for(pCl in FindObjects(Find_Distance(GetCon()/2),Find_OCF(OCF_Alive)))
	{
		SetClrModulation(RGB(128,64,64),pCl);
		if(!GetEffect("Genuced",pCl)) AddEffect("Genuced",pCl, 3,40, pCl);
	}		
	if(TimeToLive > 254)
	{
		RemoveObject();
	}	
}

global func FxGenucedTimer(object pTarget)
{	
	pTarget -> DoDamage(1);
	pTarget -> DoEnergy(-1);
	if(InLiquid(pTarget)) 
	{
		SetClrModulation(0,pTarget);
		return(-1);
	}
	if(GetID(Contained(pTarget)) == GOSA) 
	{
		SetClrModulation(0,pTarget);
		return(-1);
	}
}
local ActMap = {
1 = {
Prototype = Action,
Name = "1",
Procedure = DFA_FLOAT,
NextAction = "1",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 194,
Y = 190,
Wdt = 62,
Hgt = 60,
},
2 = {
Prototype = Action,
Name = "2",
Procedure = DFA_FLOAT,
NextAction = "2",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 63,
Y = 0,
Wdt = 62,
Hgt = 60,
},
3 = {
Prototype = Action,
Name = "3",
Procedure = DFA_FLOAT,
NextAction = "3",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 126,
Y = 0,
Wdt = 63,
Hgt = 60,
},
4 = {
Prototype = Action,
Name = "4",
Procedure = DFA_FLOAT,
NextAction = "4",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 191,
Y = 0,
Wdt = 63,
Hgt = 60,
},
5 = {
Prototype = Action,
Name = "5",
Procedure = DFA_FLOAT,
NextAction = "5",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 0,
Y = 62,
Wdt = 63,
Hgt = 60,
},
6 = {
Prototype = Action,
Name = "6",
Procedure = DFA_FLOAT,
NextAction = "6",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 63,
Y = 62,
Wdt = 63,
Hgt = 60,
},
7 = {
Prototype = Action,
Name = "7",
Procedure = DFA_FLOAT,
NextAction = "7",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 126,
Y = 62,
Wdt = 63,
Hgt = 60,
},
8 = {
Prototype = Action,
Name = "8",
Procedure = DFA_FLOAT,
NextAction = "8",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 193,
Y = 62,
Wdt = 63,
Hgt = 60,
},
9 = {
Prototype = Action,
Name = "9",
Procedure = DFA_FLOAT,
NextAction = "9",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 0,
Y = 126,
Wdt = 63,
Hgt = 60,
},
10 = {
Prototype = Action,
Name = "10",
Procedure = DFA_FLOAT,
NextAction = "10",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 63,
Y = 126,
Wdt = 63,
Hgt = 60,
},
11 = {
Prototype = Action,
Name = "11",
Procedure = DFA_FLOAT,
NextAction = "11",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 128,
Y = 126,
Wdt = 63,
Hgt = 60,
},
12 = {
Prototype = Action,
Name = "12",
Procedure = DFA_FLOAT,
NextAction = "12",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 194,
Y = 126,
Wdt = 63,
Hgt = 60,
},
13 = {
Prototype = Action,
Name = "13",
Procedure = DFA_FLOAT,
NextAction = "13",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 0,
Y = 190,
Wdt = 63,
Hgt = 60,
},
14 = {
Prototype = Action,
Name = "14",
Procedure = DFA_FLOAT,
NextAction = "14",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 63,
Y = 190,
Wdt = 63,
Hgt = 60,
},
15 = {
Prototype = Action,
Name = "15",
Procedure = DFA_FLOAT,
NextAction = "15",
StartCall = "Timer",
Delay = 8,
FacetBase = 1,
X = 130,
Y = 190,
Wdt = 63,
Hgt = 60,
},  };
local Name = "$Name$";
