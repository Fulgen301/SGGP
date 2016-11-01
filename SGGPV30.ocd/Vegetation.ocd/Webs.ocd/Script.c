/*-- Weben --*/

#strict 2

protected func Initialize() {
  SetAction("Be");
  if(Random(3))
  SetCategory(C4D_Foreground);
  SetPhase (Random(5), 0); 
  SetClrModulation(RGBa(255,255,255,55+RandomX(-7,12)));
}

public func Set(phase) {
  SetPhase(phase);
  var width = GetDefCoreVal("Width", "DefCore", GetID());
  var height = GetDefCoreVal("Height", "DefCore", GetID());
}

local ActMap = {
Be = {
Prototype = Action,
Name = "Be",
X = 0,
Y = 0,
Wdt = 34,
Hgt = 45,
Length = 5,
},  };
local Name = "$Name$";
