#strict

local time;

public func Initialize()
{
  SetAction("Deactive");
  return(1);
}

public func ControlDigDouble()
{
  if(GetAction() eq "Active")
  {
   SetAction("Deactive");
   Sound("ring_button1");
   return(1);
  }

  if(GetAction() eq "Deactive")
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

func Test()
{
	if (GlobalN("energy", FindObject2(Find_ID(TEL_), Find_Distance(20)) > 10))
	{
		SetAction("Active");
	}
	else
	{
		SetAction("Deactive");
	}
}

public func Teltak()
{
	return(1);
}