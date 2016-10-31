/*-- Fackel --*/

#strict 2

public func Activate()
{
  if(GetAction() == "Burning") return Extinguishsh();
  SetAction("Burning");
  return this ;
}
  
private func Extinguishsh()
{
  SetAction("Idle");
  Sound("Pshshsh");
  return 1;
}

local Touchable = 1;
local ActMap = {
Burning = {
Prototype = Action,
Name = "Burning",
Procedure = DFA_NONE,
NextAction = "Burning",
Delay = 5,
Directions = 2,
Length = 4,
X = 14,
Y = 0,
Wdt = 14,
Hgt = 26,
OffX = 0,
OffY = -5,
},  };
local Name = "$Name$";
