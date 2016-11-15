// Zombie Clonk
// Author: Jeason



#include CLNK

local gate;
local gatepos;

protected func Hurt()
{
  Sound("UHurt*");
  return(1);
}

protected func Death()
{
  Sound("UDie*");
  return(1);
}

func IsBulletTarget()    { return(1); }
public func IsZombie()	 {return true;}

func Check()
{
  if(FindObject(STGT,-300,-300,600,600,OCF_InFree(),"Worm"))
  {
   gate = FindObject(STGT,-300,-300,600,600,OCF_InFree(),"Worm");
  }
  
  if(gate)
  {
   if(!LocalN("pFrom",gate))
   {
    if((GetX() - GetX(gate)) < 0)
    {
     SetComDir(COMD_Right());
    }
    
    if((GetX() - GetX(gate)) > 0)
    {
     SetComDir(COMD_Left());
    }
   }
  }

  if(FindContents(NVDN))
  {
   FindContents(NVDN)->Activate(this());
  }

  if(FindContents(MEDI))
  {
   FindContents(MEDI)->Activate(this());
  }
  
  if(FindContents(HEGR))
  {
   FindContents(HEGR)->Activate(Contained());
  }

  if(FindObject(HEGR,-50,-50,100,100))
  {
   if((GetX() - GetX(FindObject(HEGR,-50,-50,100,100,OCF_InFree(),"Scharf"))) < 0)
   {
    SetComDir(COMD_Left());
    return(1);
   }
   
   if((GetX() - GetX(FindObject(HEGR,-50,-50,100,100,OCF_InFree(),"Scharf"))) > 0)
   {
    SetComDir(COMD_Right());
    return(1);
   }
  }
  
  return(1);
}
local ActMap = {
Zatfall = {
Prototype = Action,
Name = "Zatfall",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 4,
Delay = 1,
X = 64,
Y = 140,
Wdt = 16,
Hgt = 20,
NextAction = "Lie",
},
Lie = {
Prototype = Action,
Name = "Lie",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 1,
Delay = 300,
X = 0,
Y = 240,
Wdt = 16,
Hgt = 20,
NextAction = "FlatUp",
},
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
local Name = "ZombieClonk";
