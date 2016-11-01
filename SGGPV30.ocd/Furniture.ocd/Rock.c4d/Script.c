/*-- Groﬂer Stein --*/

#strict

protected func Initialize() 
{
  SetAction("Standard");
  var phase = Random(6);
  SetPhase(phase);
  SetSolidMask(phase * 32, 0, 32, 32);
}

protected func Damage() 
{
  if (GetDamage() < 50) return(0);
  CastObjects(ROCK, 4, 15, 0, -5);
  RemoveObject();
  return(1);
}
local ActMap = {

Standard = {

Prototype = Action,

Name = "Standard",

Length = 6,

Delay = 0,

X = 0,

Y = 0,

Wdt = 32,

Hgt = 32,

NextAction = "Hold",

},  };
local Name = "$Name$";
