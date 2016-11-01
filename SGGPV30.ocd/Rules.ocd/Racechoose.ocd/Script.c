#strict
#include CLNK

local life;

func Initialize()
{
	SetAction("Walk");
  	life = 128;
  	return(1);
}

func ControlDigDouble()
{
	var User;
	CreateMenu(0,this(),this()); 
	var i; 
	var id; 
	if(FindObject(ONSG))
	{
  		while (id = GetDefinition(i++))
  		{
  			if(id != FCLK) if(id !=  GetID(this())) 
  			if(GetValue(0,id) > 0) 
  			if(GetWealth(GetOwner()) >= GetValue(0,id) - GetValue()) 
  			if(GetDefCoreVal("CrewMember", "DefCore", id)) 
  			AddMenuItem("%s",Format("ChangeTo(%i,%d)",id,GetValue(0,id) - GetValue()),id,this(),GetValue(0,id) - GetValue());	
  		}
	}
	else
	{
  		if(GetWealth(GetOwner()) >= GetValue(0,SGK_) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",SGK_,GetValue(0,SGK_) - GetValue()),SGK_,this(),GetValue(0,SGK_) - GetValue());
  		if(GetWealth(GetOwner()) >= GetValue(0,CLNK) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",CLNK,GetValue(0,CLNK) - GetValue()),CLNK,this(),GetValue(0,CLNK) - GetValue());
  		if(GetWealth(GetOwner()) >= GetValue(0,JAFA) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",JAFA,GetValue(0,JAFA) - GetValue()),JAFA,this(),GetValue(0,JAFA) - GetValue());
  		if(GetWealth(GetOwner()) >= GetValue(0,KULL) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",KULL,GetValue(0,KULL) - GetValue()),KULL,this(),GetValue(0,KULL) - GetValue());
  		if(GetWealth(GetOwner()) >= GetValue(0,WRAT) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",WRAT,GetValue(0,WRAT) - GetValue()),WRAT,this(),GetValue(0,WRAT) - GetValue());
	}
	return(true);
}

func ChangeTo(id IdTyp,int iValue)
{
	DoWealth(GetOwner(),-iValue);
	var Clk;
	Clk = CreateObject(IdTyp,0,10,GetOwner());
	Clk->CastParticles("FSpark", 10,100, 0,0, 100, 200, RGBa(255,0,0,0),RGBa(255,128,0,128));
	MakeCrewMember(Clk,GetOwner());
	SetCursor(GetOwner(),Clk);
	RemoveObject();
}

func Checks()
{
	life --;
	Message("Wähle per <c 000000>Doppelgraben</c> einen Clonktyp!|<c %x>%d</c>",this(),RGB(255-life*2,life*2,0),life);
	if(life == 0)
	{
		ChangeTo(CLNK,0);
	}
	return(1);
}

func MaxContentsCount() { return(0); }
local ActMap = {
Walk = {
Prototype = Action,
Name = "Walk",
Procedure = DFA_WALK,
Directions = 2,
FlipDir = 1,
Length = 16,
Delay = 15,
X = 0,
Y = 0,
Wdt = 16,
Hgt = 20,
NextAction = "Walk",
InLiquidAction = "Swim",
},
Scale = {
Prototype = Action,
Name = "Scale",
Procedure = DFA_SCALE,
Directions = 2,
FlipDir = 1,
Length = 16,
Delay = 15,
X = 0,
Y = 20,
Wdt = 16,
Hgt = 20,
NextAction = "Scale",
StartCall = "Scaling",
},
ScaleDown = {
Prototype = Action,
Name = "ScaleDown",
Procedure = DFA_SCALE,
Directions = 2,
FlipDir = 1,
Length = 16,
Delay = 15,
X = 0,
Y = 20,
Wdt = 16,
Hgt = 20,
Reverse = 1,
NextAction = "ScaleDown",
StartCall = "Scaling",
},
Tumble = {
Prototype = Action,
Name = "Tumble",
Procedure = DFA_FLIGHT,
Directions = 2,
FlipDir = 1,
Length = 16,
Delay = 1,
X = 0,
Y = 40,
Wdt = 16,
Hgt = 20,
NextAction = "Tumble",
ObjectDisabled = 1,
InLiquidAction = "Swim",
EndCall = "CheckStuck",
},
Dig = {
Prototype = Action,
Name = "Dig",
Procedure = DFA_DIG,
Directions = 2,
FlipDir = 1,
Length = 16,
Delay = 15,
X = 0,
Y = 60,
Wdt = 16,
Hgt = 20,
NextAction = "Dig",
StartCall = "Digging",
DigFree = 11,
InLiquidAction = "Swim",
},
Bridge = {
Prototype = Action,
Name = "Bridge",
Procedure = DFA_BRIDGE,
Directions = 2,
FlipDir = 1,
Length = 16,
Delay = 1,
X = 0,
Y = 60,
Wdt = 16,
Hgt = 20,
NextAction = "Bridge",
StartCall = "Digging",
InLiquidAction = "Swim",
},
Swim = {
Prototype = Action,
Name = "Swim",
Procedure = DFA_SWIM,
Directions = 2,
FlipDir = 1,
Length = 16,
Delay = 15,
X = 0,
Y = 80,
Wdt = 16,
Hgt = 20,
NextAction = "Swim",
},
Hangle = {
Prototype = Action,
Name = "Hangle",
Procedure = DFA_HANGLE,
Directions = 2,
FlipDir = 1,
Length = 11,
Delay = 16,
X = 0,
Y = 100,
Wdt = 16,
Hgt = 20,
NextAction = "Hangle",
InLiquidAction = "Swim",
},
Jump = {
Prototype = Action,
Name = "Jump",
Procedure = DFA_FLIGHT,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 3,
X = 0,
Y = 120,
Wdt = 16,
Hgt = 20,
NextAction = "Hold",
InLiquidAction = "Swim",
PhaseCall = "CheckStuck",
},
KneelDown = {
Prototype = Action,
Name = "KneelDown",
Procedure = DFA_KNEEL,
Directions = 2,
FlipDir = 1,
Length = 4,
Delay = 1,
X = 0,
Y = 140,
Wdt = 16,
Hgt = 20,
NextAction = "KneelUp",
},
KneelUp = {
Prototype = Action,
Name = "KneelUp",
Procedure = DFA_KNEEL,
Directions = 2,
FlipDir = 1,
Length = 4,
Delay = 1,
X = 64,
Y = 140,
Wdt = 16,
Hgt = 20,
NextAction = "Walk",
},
Dive = {
Prototype = Action,
Name = "Dive",
Procedure = DFA_FLIGHT,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 4,
X = 0,
Y = 160,
Wdt = 16,
Hgt = 20,
NextAction = "Hold",
ObjectDisabled = 1,
InLiquidAction = "Swim",
PhaseCall = "CheckStuck",
},
FlatUp = {
Prototype = Action,
Name = "FlatUp",
Procedure = DFA_KNEEL,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 1,
X = 0,
Y = 180,
Wdt = 16,
Hgt = 20,
NextAction = "KneelUp",
ObjectDisabled = 1,
},
Throw = {
Prototype = Action,
Name = "Throw",
Procedure = DFA_THROW,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 1,
X = 0,
Y = 200,
Wdt = 16,
Hgt = 20,
NextAction = "Walk",
InLiquidAction = "Swim",
},
Punch = {
Prototype = Action,
Name = "Punch",
Procedure = DFA_FIGHT,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 2,
X = 0,
Y = 220,
Wdt = 16,
Hgt = 20,
NextAction = "Fight",
EndCall = "Punching",
ObjectDisabled = 1,
},
Dead = {
Prototype = Action,
Name = "Dead",
Directions = 2,
FlipDir = 1,
X = 0,
Y = 240,
Wdt = 16,
Hgt = 20,
Length = 6,
Delay = 3,
NextAction = "Hold",
NoOtherAction = 1,
ObjectDisabled = 1,
},
Ride = {
Prototype = Action,
Name = "Ride",
Procedure = DFA_ATTACH,
Directions = 2,
FlipDir = 1,
Length = 4,
Delay = 3,
X = 128,
Y = 120,
Wdt = 16,
Hgt = 20,
NextAction = "Ride",
StartCall = "Riding",
InLiquidAction = "Swim",
},
RideStill = {
Prototype = Action,
Name = "RideStill",
Procedure = DFA_ATTACH,
Directions = 2,
FlipDir = 1,
Length = 1,
Delay = 10,
X = 128,
Y = 120,
Wdt = 16,
Hgt = 20,
NextAction = "RideStill",
StartCall = "Riding",
InLiquidAction = "Swim",
},
Push = {
Prototype = Action,
Name = "Push",
Procedure = DFA_PUSH,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 15,
X = 128,
Y = 140,
Wdt = 16,
Hgt = 20,
NextAction = "Push",
InLiquidAction = "Swim",
},
Chop = {
Prototype = Action,
Name = "Chop",
Procedure = DFA_CHOP,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 3,
X = 128,
Y = 160,
Wdt = 16,
Hgt = 20,
NextAction = "Chop",
StartCall = "Chopping",
InLiquidAction = "Swim",
},
Fight = {
Prototype = Action,
Name = "Fight",
Procedure = DFA_FIGHT,
Directions = 2,
FlipDir = 1,
Length = 7,
Delay = 4,
X = 128,
Y = 180,
Wdt = 16,
Hgt = 20,
NextAction = "Fight",
StartCall = "Fighting",
ObjectDisabled = 1,
},
GetPunched = {
Prototype = Action,
Name = "GetPunched",
Procedure = DFA_FIGHT,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 3,
X = 128,
Y = 200,
Wdt = 16,
Hgt = 20,
NextAction = "Fight",
ObjectDisabled = 1,
},
Build = {
Prototype = Action,
Name = "Build",
Procedure = DFA_BUILD,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 2,
X = 128,
Y = 220,
Wdt = 16,
Hgt = 20,
NextAction = "Build",
StartCall = "Building",
InLiquidAction = "Swim",
},
RideThrow = {
Prototype = Action,
Name = "RideThrow",
Procedure = DFA_ATTACH,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 1,
X = 128,
Y = 240,
Wdt = 16,
Hgt = 20,
NextAction = "Ride",
StartCall = "Throwing",
InLiquidAction = "Swim",
},
Process = {
Prototype = Action,
Name = "Process",
Procedure = DFA_THROW,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 3,
X = 0,
Y = 260,
Wdt = 16,
Hgt = 20,
NextAction = "Process",
EndCall = "Processing",
},
Drink = {
Prototype = Action,
Name = "Drink",
Procedure = DFA_THROW,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 3,
X = 128,
Y = 260,
Wdt = 16,
Hgt = 20,
NextAction = "Walk",
},  };
local Name = "Rassenwahl";
