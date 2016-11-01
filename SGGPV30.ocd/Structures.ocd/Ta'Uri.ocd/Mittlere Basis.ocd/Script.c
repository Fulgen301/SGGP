/*-- Basis --*/

#strict 2

#include DOOR
#include BA15

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

func Damage()
{
  if(GetDamage() >= 200)
  {
   Explode(70);
  }
  return(1);
}
local ActMap = {

OpenDoor = {

Prototype = Action,

Name = "OpenDoor",

Length = 20,

Delay = 1,

X = 0,

Y = 0,

Wdt = 120,

Hgt = 30,

NextAction = "DoorOpen",

Sound = "luke1",

},

DoorOpen = {

Prototype = Action,

Name = "DoorOpen",

Length = 1,

Delay = 10,

X = 2400,

Y = 0,

Wdt = 120,

Hgt = 30,

NextAction = "CloseDoor",

StartCall = "OpenEntrance",

EndCall = "CloseEntrance",

},

CloseDoor = {

Prototype = Action,

Name = "CloseDoor",

Length = 20,

Delay = 1,

Reverse = 1,

X = 0,

Y = 0,

Wdt = 120,

Hgt = 30,

NextAction = "Idle",

Sound = "luke1",

},  };
local Name = "$Name$";
