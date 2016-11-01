/*-- Bruchteil eines Stalaktiten --*/

#strict

local alpha;

/* Langsam verschwinden */
func FadeMeOut() {
  SetClrModulation(RGBa(255,255,255,alpha++));
	if(alpha==255) return(RemoveObject());
	return(1);
}

func Hit() { return(Sound("RockHit*")); }
local ActMap = {

Exist = {

Prototype = Action,

Name = "Exist",

Procedure = DFA_None,

Delay = 0,

Length = 8,

Directions = 1,

X = 0,

Y = 0,

Wdt = 7,

Hgt = 19,

NextAction = "Hold",

},

LameExist = {

Prototype = Action,

Name = "LameExist",

Procedure = DFA_None,

Delay = 0,

Length = 4,

Directions = 1,

X = 0,

Y = 19,

Wdt = 14,

Hgt = 19,

NextAction = "Hold",

},  };
local Name = "$Name$";
