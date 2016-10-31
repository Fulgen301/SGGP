/*-- Atlantis Door --*/

#strict

#include GBDR

local pathfree;
local Quar;
local crashed;
local solid;
local oClose;

public func Initialize() 
{
	pathfree = false;
	SetAction("Closed");
	_inherited();
	// not destroyable
	SetMaxDamage(-1);
}

public func OnOpen()
{
	if(GetAction() eq "Open" || GetAction() eq "Opened") return();
	SetAction("Open");
	Sound("AtlantisDoor");
}

public func OnClose()
{
	if(GetAction() eq "Closed" || GetAction() eq "Close") return();
	SetAction("Close");
	SetSolidMask(5, 0, 8, 30, 5, 0);
	Sound("AtlantisDoor");
}

public func SetPathFree()
{
	pathfree = true;
	SetSolidMask();
}

public func Damage()
{
  if(GetDamage() >= 150)
  {
   if(!crashed)
   {
    crashed = 1;
    CreateObject(ROCK)->Explode(5);
    Crash();
   }
  }
  return(1);
}

public func Crash()
{
  SetSolidMask(0,60,20,30);
  SetAction("Crash");
  Lock();
  crashed = 1;
  return(1);
}

public func IsBulletTarget()
{
  if(GetAction() eq "Crash")
  {
   return();
  }
  return(1);
}

public func Check()
{
  if(Quar == 1)
  {
   if(GetAction() eq "Opened")
   {
    OnClose();
    Close();
   }
   Lock();
  }
  return(1);
}

public func Locked()
{
  if(Quar == 0)
  {
   return();
  }
  return(1);
}

public func Opened()
{
  if(Quar == 1)
  {
   return();
  }
  return(1);
}

public func QuarOn()
{
  Quar = 1;
  while(FindObject2(Find_Func("Opened"),Find_ID(ATDO)))
  {
   LocalN("Quar",FindObject2(Find_Func("Opened"),Find_ID(ATDO))) = 1;
  }
  return(1);
}
  
public func QuarOff()
{
  Quar = 0;
  Unlock();
  while(FindObject2(Find_Func("Locked"),Find_ID(ATDO)))
  {
   FindObject2(Find_Func("Opened"),Find_ID(ATDO))->Unlock();
   LocalN("Quar",FindObject2(Find_Func("Locked"),Find_ID(ATDO))) = 0;
  }
  return(1);
}

public func Switch()
{
  if(solid == 0)
  {
   SetGraphics("Solid");
   solid = 1;
   return(1);
  }
  
  if(solid == 1)
  {
   SetGraphics("Blast");
   solid = 2;
   return(1);
  }
  
  if(solid == 2)
  {
   SetGraphics("");
   solid = 0;
   return(1);
  }
  
  return(1);
}

public func AlwaysOpen()
{
  if(!oClose)
  {
   oClose = 1;
   Lock();
   SetAction("Opened");
   SetSolidMask();
   Message("<c ff0000>Tür ist jetzt immer Offen!</c>",this());
   return(1);
  }
  
  if(oClose)
  {
   oClose = 0;
   Unlock();
   SetAction("Closed");
   SetSolidMask(5,0,8,30,5,0);
   Message("<c 00ff00>Tür ist jetzt normal!</c>",this());
   return(1);
  }
  return(1);
}


/* Serialisierung */

public func Serialize(array& extra)
{
	_inherited(extra);
	if (pathfree)
		extra[GetLength(extra)] = "SetPathFree()";
}
local ActMap = {
Closed = {
Prototype = Action,
Name = "Closed",
Procedure = DFA_NONE,
X = 0,
Y = 0,
Wdt = 20,
Hgt = 30,
Directions = 1,
Length = 1,
FlipDir = 0,
FacetTopFace = 1,
NextAction = "Hold",
},
Open = {
Prototype = Action,
Name = "Open",
Procedure = DFA_NONE,
X = 0,
Y = 0,
Wdt = 20,
Hgt = 30,
Length = 20,
Directions = 1,
FlipDir = 0,
FacetTopFace = 1,
Delay = 1,
EndCall = "SetPathFree",
NextAction = "Opened",
},
Opened = {
Prototype = Action,
Name = "Opened",
Procedure = DFA_NONE,
X = 400,
Y = 0,
Wdt = 20,
Hgt = 30,
Length = 1,
Directions = 1,
FlipDir = 0,
FacetTopFace = 1,
NextAction = "Hold",
},
Close = {
Prototype = Action,
Name = "Close",
Procedure = DFA_NONE,
X = 0,
Y = 0,
Wdt = 20,
Hgt = 30,
Length = 20,
Directions = 1,
FlipDir = 0,
FacetTopFace = 1,
Delay = 1,
Reverse = 1,
NextAction = "Closed",
},
Crash = {
Prototype = Action,
Name = "Crash",
Procedure = DFA_NONE,
X = 0,
Y = 30,
Wdt = 20,
Hgt = 30,
Directions = 1,
Length = 1,
Delay = 1,
FacetTopFace = 1,
NextAction = "Crash",
EndCall = "Crash",
},  };
local Name = "$Name$";
