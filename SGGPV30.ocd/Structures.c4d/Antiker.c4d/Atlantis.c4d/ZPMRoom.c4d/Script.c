/*-- Wand --*/

#strict

#include ALW2

/* Ausrichtung von Burgbauteilen */

public func CastlePartWidth() { return (40); }
public func CastlePartHeight() { return (74); }
public func CastlePartTop() { return (-13); }
public func CastlePartBasement() { return(BSC1); }


/* Forschung */

public func GetResearchBase() { return(ALW2); }

public func Initialize()
{
	CreateObject(ZPMG,0,37,GetOwner())/*->Set(1)*/;
	FindObject2(Find_ID(BAS3),Sort_Distance())->RemoveObject();
	return(_inherited());
}

public func Atlantis()
{
	return(1);
}
