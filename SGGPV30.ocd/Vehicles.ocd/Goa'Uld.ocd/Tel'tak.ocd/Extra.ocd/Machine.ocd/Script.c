#strict 2

local time;

public func Initialize()
{
  SetAction("Deactive");
  return(1);
}

public func ControlDigDouble()
{
  if(GetAction() == "Active")
  {
   SetAction("Deactive");
   Sound("ring_button1");
   return(1);
  }

  if(GetAction() == "Deactive")
  {
	SetAction("Active");
	Sound("ring_button2");
  }
  return(1);
}

func Deactivate()
{
	SetAction("Deactive");
	return(1);
}

func Activate()
{
	SetAction("Active");
	return(1);
}

public func Teltak()
{
	return(1);
}
local ActMap = {
Active = {
Prototype = Action,
Name = "Active",
Length = 10,
Delay = 3,
X = 0,
Y = 0,
Wdt = 17,
Hgt = 43,
NextAction = "Active",
Sound = "Elevator",
},
Deactive = {
Prototype = Action,
Name = "Deactive",
Length = 1,
Delay = 1,
X = 0,
Y = 43,
Wdt = 17,
Hgt = 43,
NextAction = "Deactive",
},  };
local Name = "Hyperraumgenerator";
