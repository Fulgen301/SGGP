/*-- Wand --*/

#strict 2

#include ALW2
local zpmGenerator;

/* Ausrichtung von Burgbauteilen */

public func CastlePartWidth() { return (40); }
public func CastlePartHeight() { return (74); }
public func CastlePartTop() { return (-13); }
public func CastlePartBasement() { return(BSC1); }


/* Forschung */

public func GetResearchBase() { return(ALW2); }

public func Initialize()
{
	zpmGenerator = CreateObject(ZPMG,0,37,GetOwner())/*->Set(1)*/;
	if(zpmGenerator->LocalN("basement")) zpmGenerator->LocalN("basement")->RemoveObject();
	return(_inherited());
}

public func Atlantis()
{
	return(1);
}

public func & GetZPMGenerator()
{
	return zpmGenerator;
}
