/*-- Basis --*/



#include DOOR
#include BA15

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

protected func ContainedLeft(pCursor)
{
  pCursor->Exit();
  pCursor->SetPosition(GetX(),GetY()+10);
  return(1);
}

protected func ContextAufstieg(object pClonk)
{
  [Tower betreten|Image=MEPU]
  pClonk->ContainedCall("ContainedLeft", this());
}

func Damage()
{
  if(GetDamage() >= 200)
  {
   Explode(90);
  }
  return(1);
}
local ActMap = {
OpenDoor = {
Prototype = Action,
Name = "OpenDoor",
Length = 19,
Delay = 1,
X = 0,
Y = 0,
Wdt = 120,
Hgt = 150,
NextAction = "DoorOpen",
Sound = "luke1",
},
DoorOpen = {
Prototype = Action,
Name = "DoorOpen",
Length = 1,
Delay = 15,
X = 2400,
Y = 0,
Wdt = 120,
Hgt = 150,
NextAction = "CloseDoor",
StartCall = "OpenEntrance",
EndCall = "CloseEntrance",
},
CloseDoor = {
Prototype = Action,
Name = "CloseDoor",
Length = 19,
Delay = 1,
Reverse = 1,
X = 0,
Y = 0,
Wdt = 120,
Hgt = 150,
NextAction = "Idle",
Sound = "luke1",
},  };
local Name = "$Name$";
