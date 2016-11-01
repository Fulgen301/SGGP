#strict

Completion:
  SetAction("Scroll");
  return(1);
Damage:
  if (SEqual(GetAction(),"Broken")) return(0);
  SetAction("Broken");
  CastObjects(SHRD,20,10,0,0);
  Sound("GlassBreak");
  return(1);
local ActMap = {

Scroll = {

Prototype = Action,

Name = "Scroll",

Procedure = DFA_NONE,

NextAction = "Scroll",

Delay = 4,

Length = 6,

X = 0,

Y = 0,

Wdt = 39,

Hgt = 39,

},

Broken = {

Prototype = Action,

Name = "Broken",

Procedure = DFA_NONE,

Length = 1,

X = 234,

Y = 0,

Wdt = 39,

Hgt = 39,

},  };
local Name = "$Name$";
