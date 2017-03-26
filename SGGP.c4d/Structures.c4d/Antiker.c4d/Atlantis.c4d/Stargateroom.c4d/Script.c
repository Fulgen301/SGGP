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
	_inherited();
	var gate = CreateGate(SGR1,SGAG,23,68,GetOwner());
	gate->LocalN("target")->InstallShield();
	FindObject2(Find_ID(ALOS),Find_Owner(GetOwner()))->RegisterStructure(gate);
	FindObject2(Find_ID(ALOS),Find_Owner(GetOwner()))->RegisterStructure(CreateObject(STWA,-57,68,GetOwner()));
}
/* Forschung */

public func GetResearchBase() { return(ALW2); }
public func Atlantis()
{
	return(1);
}
