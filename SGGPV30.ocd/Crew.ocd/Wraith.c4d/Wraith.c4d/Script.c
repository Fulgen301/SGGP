
/*---- Wraith ----*/

#strict 2
#include JAFA

local SDestroy;

public func Zated()
{
  if(GetAction() == "Lie")
  {
   SetAction("Lie");
   EMPShockEffect(50);
   return(1);
  }
  SetAction("Zatfall");
  EMPShockEffect(50);
  return(1);
}

protected func Initialize()
{
  SDestroy=1;
  return(inherited());
}

/* Kontextmenü */

public func FindKnockClonk() 
{
  if(FindObject(0,-15,-15,30,30,OCF_Alive,"Lie",0,NoContainer()))
  {
   return(1); 
  }
  return;
}

//Die Funktion zum Aussaugen des Feindes

protected func ContextSuck() 
{
  [$CtxSuck$|Image=MEPU:4|Condition=FindKnockClonk]
  // Lebensenergie aussaugen

  if(GetAction(this()) == "Suck")
  {
   SetAction("Walk");
   return(1);
  }

  if(!FindObject(0,-10,-10,20,20,OCF_Alive))
  {
   Message("Hier ist keine Nahrung!",this());
   return(1);
  }

  SetAction("Suck");

  Sound("Confirm*");
}

protected func Suck()
{
  if(FindObject(0,-10,-10,20,20,OCF_Alive))
  {
   FindObject(0,-10,-10,20,20,OCF_Alive)->SetAction("Lie");
   DoEnergy(-1,FindObject(0,-10,-10,20,20,OCF_Alive));
   DoEnergy(1,this);
   SetAction("Suck");
   return(1);
  }
  SetAction("Walk");
  return(1);
}

protected func ContextDestroy()
{
  [$CtxSDestroy$|Image=MEPU:1|Condition=DestroyerCheck]
  Schedule("Explode(60)",100);
  Sound("WRReady");
  return(1);
}


private func DestroyerCheck() 
{
  if(this->GetAction() == "Lie")
  {
   return;
  }

  if(SDestroy == 1)
  {
   return(1);
  }
  return;
}


private func Control2Contents (string command, par1, par2, par3, par4)
{
  if(GetAction() == "Push")
    return(0);
  if(ObjectCall(Contents(), command, this, par1, par2, par3, par4))
    return(1);
  return(0);
}

public func IsWraith()	{return true;}
public func GetRace()	{ return SGA_Wraith; }
local ActMap = {
Suck = {
Prototype = Action,
Name = "Suck",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 1,
Delay = 1,
X = 32,
Y = 240,
Wdt = 16,
Hgt = 20,
EndCall = "Suck",
NextAction = "Walk",
},
Zatfall = {
Prototype = Action,
Name = "Zatfall",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 6,
Delay = 3,
X = 0,
Y = 240,
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
X = 80,
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
OffX = 0,
OffY = 0,
NextAction = "Walk",
StartCall = "CheckArmed",
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
OffX = 0,
OffY = 0,
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
Reverse = 1,
Delay = 15,
X = 0,
Y = 20,
Wdt = 16,
Hgt = 20,
OffX = 0,
OffY = 0,
NextAction = "ScaleDown",
StartCall = "Scaling",
},
ScaleLadder = {
Prototype = Action,
Name = "ScaleLadder",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 16,
X = 0,
Y = 20,
Wdt = 16,
Hgt = 20,
OffX = 0,
OffY = 0,
NextAction = "ScaleLadder",
StartCall = "PauseReloading",
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
OffX = 0,
OffY = 0,
NextAction = "Tumble",
EndCall = "MacroComTumble",
InLiquidAction = "Swim",
ObjectDisabled = 1,
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
OffX = 0,
OffY = 0,
NextAction = "Dig",
StartCall = "Digging",
InLiquidAction = "Swim",
DigFree = 11,
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
OffX = 0,
OffY = 0,
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
OffX = 0,
OffY = 0,
NextAction = "Swim",
StartCall = "CheckArmed",
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
OffX = 0,
OffY = 0,
NextAction = "Hangle",
StartCall = "Hangling",
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
OffX = 0,
OffY = 0,
NextAction = "Hold",
StartCall = "JumpStart",
PhaseCall = "CheckStuck",
InLiquidAction = "Swim",
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
OffX = 0,
OffY = 0,
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
OffX = 0,
OffY = 0,
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
OffX = 0,
OffY = 0,
NextAction = "Hold",
StartCall = "JumpStart",
PhaseCall = "CheckStuck",
InLiquidAction = "Swim",
ObjectDisabled = 1,
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
OffX = 0,
OffY = 0,
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
OffX = 0,
OffY = 0,
NextAction = "Walk",
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
OffX = 0,
OffY = 0,
NextAction = "Fight",
EndCall = "Punching",
ObjectDisabled = 1,
},
Dead = {
Prototype = Action,
Name = "Dead",
Directions = 2,
FlipDir = 1,
Length = 6,
Delay = 3,
X = 0,
Y = 240,
Wdt = 16,
Hgt = 20,
OffX = 0,
OffY = 0,
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
OffX = 0,
OffY = 0,
NextAction = "Ride",
StartCall = "Riding",
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
OffX = 0,
OffY = 0,
NextAction = "RideStill",
StartCall = "Riding",
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
OffX = 0,
OffY = 0,
NextAction = "Push",
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
OffX = 0,
OffY = 0,
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
OffX = 0,
OffY = 0,
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
OffX = 0,
OffY = 0,
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
OffX = 0,
OffY = 0,
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
OffX = 0,
OffY = 0,
NextAction = "Ride",
StartCall = "Throwing",
},
WalkArmed = {
Prototype = Action,
Name = "WalkArmed",
Procedure = DFA_WALK,
Directions = 2,
FlipDir = 1,
Length = 16,
Delay = 15,
X = 0,
Y = 260,
Wdt = 16,
Hgt = 20,
OffX = 0,
OffY = 0,
NextAction = "WalkArmed",
StartCall = "CheckArmed",
},
SwimArmed = {
Prototype = Action,
Name = "SwimArmed",
Procedure = DFA_SWIM,
Directions = 2,
FlipDir = 1,
Length = 16,
Delay = 15,
X = 0,
Y = 280,
Wdt = 16,
Hgt = 20,
OffX = 0,
OffY = 0,
NextAction = "SwimArmed",
StartCall = "CheckArmed",
},
JumpArmed = {
Prototype = Action,
Name = "JumpArmed",
Procedure = DFA_FLIGHT,
Directions = 2,
FlipDir = 1,
Length = 8,
Delay = 3,
X = 0,
Y = 300,
Wdt = 16,
Hgt = 20,
OffX = 0,
OffY = 0,
NextAction = "Hold",
StartCall = "JumpStart",
InLiquidAction = "SwimArmed",
},
Aim = {
Prototype = Action,
Name = "Aim",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 7,
Attach = 8,
X = 0,
Y = 340,
Wdt = 24,
Hgt = 20,
OffX = -4,
OffY = 0,
NextAction = "Hold",
},
AimLow = {
Prototype = Action,
Name = "AimLow",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 7,
Attach = 8,
X = 0,
Y = 360,
Wdt = 24,
Hgt = 20,
OffX = -4,
OffY = 0,
NextAction = "Hold",
},
AimSquat = {
Prototype = Action,
Name = "AimSquat",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 7,
Attach = 8,
X = 0,
Y = 380,
Wdt = 24,
Hgt = 20,
OffX = -4,
OffY = 0,
NextAction = "Hold",
},
AimSquatLow = {
Prototype = Action,
Name = "AimSquatLow",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 7,
Attach = 8,
X = 0,
Y = 400,
Wdt = 24,
Hgt = 20,
OffX = -4,
OffY = 0,
NextAction = "Hold",
},
BackFlip = {
Prototype = Action,
Name = "BackFlip",
Procedure = DFA_FLIGHT,
Directions = 2,
FlipDir = 1,
Length = 13,
Delay = 2,
X = 0,
Y = 320,
Wdt = 16,
Hgt = 20,
OffX = 0,
OffY = 0,
NextAction = "Jump",
PhaseCall = "CheckStuck",
AbortCall = "ComNone",
InLiquidAction = "Swim",
},
ForwardFlip = {
Prototype = Action,
Name = "ForwardFlip",
Procedure = DFA_FLIGHT,
Directions = 2,
FlipDir = 1,
Length = 13,
Delay = 2,
X = 0,
Y = 320,
Wdt = 16,
Hgt = 20,
OffX = 0,
OffY = 0,
NextAction = "Jump",
PhaseCall = "CheckStuck",
AbortCall = "ComNone",
InLiquidAction = "Swim",
Reverse = 1,
},
JetpackFlight = {
Prototype = Action,
Name = "JetpackFlight",
Procedure = DFA_FLIGHT,
Directions = 2,
FlipDir = 1,
Length = 1,
Delay = 70,
X = 32,
Y = 80,
Wdt = 16,
Hgt = 20,
OffX = 0,
OffY = 0,
NextAction = "Hold",
InLiquidAction = "Swim",
},
Heal = {
Prototype = Action,
Name = "Heal",
Procedure = DFA_NONE,
Directions = 2,
FlipDir = 1,
Length = 1,
Delay = 90,
Attach = 8,
X = 144,
Y = 400,
Wdt = 24,
Hgt = 20,
OffX = -4,
OffY = 0,
NextAction = "Heal",
ObjectDisabled = 1,
},  };
local Name = "Wraith";
