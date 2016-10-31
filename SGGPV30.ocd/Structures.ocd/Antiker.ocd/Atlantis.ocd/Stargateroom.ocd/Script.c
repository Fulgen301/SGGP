/*-- Stargateraum --*/

#strict

#include ALW2 // Burgteilfunktion

/* Ausrichtung von Burgbauteilen */

public func CastlePartWidth() { return (160); }
public func CastlePartHeight() { return (136); }
public func CastlePartTop() { return (-13); }
public func CastlePartBasement() { return(BC16); }

protected func Initialize()
{
	CreateGate(SGR1,SGAG,23,68,-1,"Atlantis");
	CreateObject(STWA,-57,68,GetOwner());
	return(_inherited());
}
/* Forschung */

public func GetResearchBase() { return(ALW2); }
public func Atlantis()
{
	return(1);
}
local Name = "$Name$";
