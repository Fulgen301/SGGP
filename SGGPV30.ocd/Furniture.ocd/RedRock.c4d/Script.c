/*-- Groﬂer roter Stein --*/

#strict

protected func Initialize() 
{
  SetAction("Standard");
  var phase = Random(3);
  SetPhase(phase);
  SetSolidMask(phase * 32, 0, 32, 32);
}

protected func Damage() 
{
  if (GetDamage() < 25) return(0);
  CastObjects(FLNT, 4, 25, 0, -5);
  RemoveObject();
  return(1);
}
local ActMap = {

Standard = {

Prototype = Action,

Name = "Standard",

Delay = 0,

Length = 3,

X = 0,

Y = 0,

Wdt = 32,

Hgt = 32,

NextAction = "Hold",

},  };
local Name = "$Name$";
