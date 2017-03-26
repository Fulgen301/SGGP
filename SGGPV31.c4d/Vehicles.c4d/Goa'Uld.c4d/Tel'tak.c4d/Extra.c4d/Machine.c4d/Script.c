#strict 2

local time;

local target;

public func Initialize()
{
  SetAction("Deactive");
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