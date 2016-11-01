/*-- Fundament --*/

#strict

/* Alle Fundamente leiten ihre Grundfunktionalität von BAS7 ab */

#include BAS7

private func BasementID() { return(BA15); }
private func BasementWidth() { return(150); }
local ActMap = {
Consolidate = {
Prototype = Action,
Name = "Consolidate",
Length = 1,
Delay = 20,
NextAction = "None",
FacetBase = 1,
EndCall = "Consolidated",
},  };
local Name = "$Name$";
