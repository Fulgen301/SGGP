/*-- Liane --*/

#strict 2

protected func Construction()
{
  // Zufälliges Aussehen
  SetAction("Vine");
  SetPhase(Random(10));
  // In Kürze Position anpassen
  AddEffect("AdjustGrowthPos", this, 1, 1, this);
}

public func GetVineLength()
{
  return (GetCon() * GetDefCoreVal("Height") / 100);
}

public func FxAdjustGrowthPosTimer()
{
  // Effekt entfernen
  RemoveEffect("AdjustGrowthPos", this);
  // Y-Position anpassen (Wachstumsverschiebung der Engine ausgleichen)
  SetPosition(GetX(), GetY() + GetVineLength());   
}
local ActMap = {

Vine = {

Prototype = Action,

Name = "Vine",

Directions = 1,

Length = 10,

Delay = 0,

X = 0,

Y = 0,

Wdt = 18,

Hgt = 64,

FacetBase = 0,

NextAction = "Vine",

},  };
local Name = "$Name$";
