#strict

SetSize:
  DoCon(Sub(Div(Mul(Par(0),100),40),100));
  SetLocal(0,Par(0));
  SetVar(0,Mul(Div(Sub(40,Div(Mul(40,GetCon()),100)),2),-1));
  SetPosition(GetX(),Sum(GetY(),Var(0)));
  return(1);
Initialize:
  SetAction(Format("Blood%d",1+Random(14)));
  SetLocal(0,40);
  return(1);  
local ActMap = {
Blood1 = {
Prototype = Action,
Name = "Blood1",
Length = 1,
X = 0,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood2 = {
Prototype = Action,
Name = "Blood2",
Length = 1,
X = 40,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood3 = {
Prototype = Action,
Name = "Blood3",
Length = 1,
X = 80,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood4 = {
Prototype = Action,
Name = "Blood4",
Length = 1,
X = 120,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood5 = {
Prototype = Action,
Name = "Blood5",
Length = 1,
X = 160,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood6 = {
Prototype = Action,
Name = "Blood6",
Length = 1,
X = 200,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood7 = {
Prototype = Action,
Name = "Blood7",
Length = 1,
X = 240,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood8 = {
Prototype = Action,
Name = "Blood8",
Length = 1,
X = 280,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood9 = {
Prototype = Action,
Name = "Blood9",
Length = 1,
X = 320,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood10 = {
Prototype = Action,
Name = "Blood10",
Length = 1,
X = 360,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood11 = {
Prototype = Action,
Name = "Blood11",
Length = 1,
X = 400,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood12 = {
Prototype = Action,
Name = "Blood12",
Length = 1,
X = 440,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood13 = {
Prototype = Action,
Name = "Blood13",
Length = 1,
X = 480,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},
Blood14 = {
Prototype = Action,
Name = "Blood14",
Length = 1,
X = 520,
Y = 0,
Wdt = 40,
Hgt = 40,
NextAction = "Hold",
},  };
local Name = "Blutfleck";
