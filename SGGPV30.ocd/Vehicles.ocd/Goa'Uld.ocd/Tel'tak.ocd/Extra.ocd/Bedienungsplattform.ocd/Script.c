

local door;

public func Initialize()
{
  ScheduleCall(0,"SetDoor",5);
  return(1);
}

public func SetDoor()
{
  door = FindObject(TEL3,0,0,-1,-1);
  return(1);
}

public func ControlDigDouble()
{
  if(GetAction(door) eq "Open")
  {
   ObjectSetAction(door, "Close");
   Sound("ring_button2");
   return(1);
  }

  if(GetAction(door) eq "Close")
  {
   ObjectSetAction(door, "Open");
   Sound("ring_button1");
   return(1);
  }
  return(1);
}

public func Teltak()
{
	return(1);
}
local Touchable = 2;
local ActMap = {
 };
local Name = "Pult";
