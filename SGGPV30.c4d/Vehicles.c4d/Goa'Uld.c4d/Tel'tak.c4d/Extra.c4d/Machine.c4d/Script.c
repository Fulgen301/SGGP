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

public func GetRace() { return SG1_Goauld; }