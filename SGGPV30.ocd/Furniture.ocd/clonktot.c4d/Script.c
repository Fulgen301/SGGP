

Initialize:
  SetAction(Format("Blood%d",1+Random(8)));
  return(1);
local ActMap = {
Blood1 = {
Prototype = Action,
Name = "Blood1",
Length = 1,
X = 0,
Y = 0,
Wdt = 16,
Hgt = 14,
NextAction = "Hold",
},
Blood2 = {
Prototype = Action,
Name = "Blood2",
Length = 1,
X = 16,
Y = 0,
Wdt = 16,
Hgt = 14,
NextAction = "Hold",
},
Blood3 = {
Prototype = Action,
Name = "Blood3",
Length = 1,
X = 34,
Y = 0,
Wdt = 16,
Hgt = 14,
NextAction = "Hold",
},
Blood4 = {
Prototype = Action,
Name = "Blood4",
Length = 1,
X = 52,
Y = 0,
Wdt = 24,
Hgt = 14,
NextAction = "Hold",
},
Blood5 = {
Prototype = Action,
Name = "Blood5",
Length = 1,
X = 75,
Y = 0,
Wdt = 17,
Hgt = 14,
NextAction = "Hold",
},
Blood6 = {
Prototype = Action,
Name = "Blood6",
Length = 1,
X = 94,
Y = 0,
Wdt = 16,
Hgt = 14,
NextAction = "Hold",
},
Blood7 = {
Prototype = Action,
Name = "Blood7",
Length = 1,
X = 112,
Y = 0,
Wdt = 16,
Hgt = 14,
NextAction = "Hold",
},
Blood8 = {
Prototype = Action,
Name = "Blood8",
Length = 1,
X = 129,
Y = 0,
Wdt = 18,
Hgt = 14,
NextAction = "Hold",
},  };
local Name = "$Name$";
