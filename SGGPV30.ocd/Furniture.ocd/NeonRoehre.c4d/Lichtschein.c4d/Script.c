#strict

func Initialize()
{
  SetClrModulation(RGBa(255,255,255,170));
  return(1);
}
local ActMap = {

Lampe = {

Prototype = Action,

Name = "Lampe",

Procedure = DFA_FLOAT,

Delay = 2,

Length = 1,

X = 0,

Y = 0,

Wdt = 40,

Hgt = 20,

NextAction = "Hold",

FacetTopFace = 1,

},

Neon = {

Prototype = Action,

Name = "Neon",

Procedure = DFA_FLOAT,

Delay = 2,

Length = 1,

X = 80,

Y = 0,

Wdt = 80,

Hgt = 32,

NextAction = "Hold",

FacetTopFace = 1,

},

Aus = {

Prototype = Action,

Name = "Aus",

Procedure = DFA_FLOAT,

Delay = 2,

Length = 1,

X = 160,

Y = 0,

Wdt = 10,

Hgt = 10,

NextAction = "Hold",

FacetTopFace = 1,

},  };
local Name = "Lichtschein";
