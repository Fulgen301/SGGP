/*-- Basis --*/

#strict

#include DOOR
#include BAS9

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }
local ActMap = {
OpenDoor = {
Prototype = Action,
Name = "OpenDoor",
Length = 1,
Delay = 1,
FacetBase = 1,
NextAction = "DoorOpen",
},
DoorOpen = {
Prototype = Action,
Name = "DoorOpen",
Length = 1,
Delay = 10,
FacetBase = 1,
NextAction = "CloseDoor",
StartCall = "OpenEntrance",
EndCall = "CloseEntrance",
},
CloseDoor = {
Prototype = Action,
Name = "CloseDoor",
Length = 1,
Delay = 1,
FacetBase = 1,
NextAction = "Idle",
},  };
local Name = "$Name$";
