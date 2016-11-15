/*-- Grünzeug --*/

// #include TREE - nope



protected func Initialize()
  {
  SetAction(Format("Green%d", Random(4)));
  SetR(Random(80)-40);
  return(1);
  }
  
  protected func Damage() 
{
  if (GetDamage() < 15) return(0);
  CastObjects(WOOD, 1, 25, 0, -5);
  RemoveObject();
  return(1);
}

local ActMap = {
Green0 = {
Prototype = Action,
Name = "Green0",
X = 0,
Y = 0,
Wdt = 32,
Hgt = 32,
Delay = 0,
Length = 1,
NextAction = "Hold",
},
Green1 = {
Prototype = Action,
Name = "Green1",
X = 32,
Y = 0,
Wdt = 32,
Hgt = 32,
Delay = 0,
Length = 1,
NextAction = "Hold",
},
Green2 = {
Prototype = Action,
Name = "Green2",
X = 0,
Y = 32,
Wdt = 32,
Hgt = 32,
Delay = 0,
Length = 1,
NextAction = "Hold",
},
Green3 = {
Prototype = Action,
Name = "Green3",
X = 32,
Y = 32,
Wdt = 32,
Hgt = 32,
Delay = 0,
Length = 1,
NextAction = "Hold",
},  };
local Name = "$Name$";
