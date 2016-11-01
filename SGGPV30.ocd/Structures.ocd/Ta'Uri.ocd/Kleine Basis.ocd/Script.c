/*-- Basis --*/

#strict

#include DOOR
#include BAS8

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

func Damage()
{
  if(GetDamage() >= 100)
  {
   Explode(50);
  }
  return(1);
}
local ActMap = {
OpenDoor = {
Prototype = Action,
Name = "OpenDoor",
Length = 16,
Delay = 1,
X = 0,
Y = 0,
Wdt = 80,
Hgt = 60,
NextAction = "DoorOpen",
},
DoorOpen = {
Prototype = Action,
Name = "DoorOpen",
Length = 1,
Delay = 10,
X = 1200,
Y = 0,
Wdt = 80,
Hgt = 60,
NextAction = "CloseDoor",
StartCall = "OpenEntrance",
EndCall = "CloseEntrance",
},
CloseDoor = {
Prototype = Action,
Name = "CloseDoor",
Length = 16,
Delay = 1,
Reverse = 1,
X = 0,
Y = 0,
Wdt = 80,
Hgt = 60,
NextAction = "Idle",
},  };
local Name = "$Name$";
