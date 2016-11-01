/*-- Ranken --*/

#strict 2

protected func Initialize() {
  SetAction("Be");
  if(Random(3))
  SetCategory(C4D_Foreground);
  SetPhase (Random(5), 0); 
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
