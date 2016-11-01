#strict

Launch:
  SetAction(Par(0));
  SetLocal(0,Par(1));
  if(Local(0)) SetXDir(Par(2));
  if(Local(0)) SetYDir(Par(3));
  return(1);

ContactBottom:
  if(Not(InLiquid())) Sound("Wasser");
  if(Local(0)) return(RemoveObject());
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  RemoveObject();
  return(1);
  
local ActMap = {

Red1 = {

Prototype = Action,

Name = "Red1",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 2,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "Red1",

},

Red2 = {

Prototype = Action,

Name = "Red2",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 3,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "Red2",

},

Blue1 = {

Prototype = Action,

Name = "Blue1",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 0,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "Blue1",

},

Blue2 = {

Prototype = Action,

Name = "Blue2",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 1,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "Blue2",

},

Green1 = {

Prototype = Action,

Name = "Green1",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 4,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "Green1",

},

Green2 = {

Prototype = Action,

Name = "Green2",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 5,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "Green2",

},

Yellow1 = {

Prototype = Action,

Name = "Yellow1",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 6,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "Yellow1",

},

Yellow2 = {

Prototype = Action,

Name = "Yellow2",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 7,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "Yellow2",

},

White = {

Prototype = Action,

Name = "White",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 8,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "White",

},

Brown = {

Prototype = Action,

Name = "Brown",

Procedure = DFA_FLIGHT,

Length = 1,

Delay = 500,

X = 9,

Y = 0,

Wdt = 1,

Hgt = 1,

NextAction = "Brown",

},  };
local Name = "Tropfen";
