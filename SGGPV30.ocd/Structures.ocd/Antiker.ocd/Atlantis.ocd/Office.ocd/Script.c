/*-- Kontor --*/



#include ALW2 // Burgteilfunktion
#include DOOR // Tuersteuerung

public func CastlePartWidth() { return (80); }
public func CastlePartHeight() { return (74); }
public func CastlePartTop() { return (-13); }
public func CastlePartBasement() { return(BSC3); }


/* Forschung */

public func GetResearchBase() { return(ALW2); }

public func Atlantis()
{
	return(1);
}
local ActMap = {
OpenDoor = {
Prototype = Action,
Name = "OpenDoor",
Procedure = DFA_NONE,
Length = 9,
Delay = 1,
X = 38,
Y = 74,
Wdt = 38,
Hgt = 26,
OffX = 22,
OffY = 48,
FacetBase = 1,
StartCall = "SoundOpenDoor",
NextAction = "DoorOpen",
},
DoorOpen = {
Prototype = Action,
Name = "DoorOpen",
Procedure = DFA_NONE,
Delay = 20,
X = 342,
Y = 74,
Wdt = 38,
Hgt = 26,
OffX = 22,
OffY = 48,
FacetBase = 1,
NextAction = "CloseDoor",
StartCall = "OpenEntrance",
EndCall = "CloseEntrance",
},
CloseDoor = {
Prototype = Action,
Name = "CloseDoor",
Procedure = DFA_NONE,
Length = 9,
Reverse = 1,
Delay = 1,
X = 38,
Y = 74,
Wdt = 38,
Hgt = 26,
OffX = 22,
OffY = 48,
FacetBase = 1,
StartCall = "SoundCloseDoor",
NextAction = "Idle",
},  };
local Name = "$Name$";
