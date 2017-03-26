/*-- Sternenantrieb --*/

// Stellt die Grundfunktionalität für alle Burgbauteile bereit

#strict 2
#include ALW2

local targets;

public func CastlePartWidth() { return (80); }
public func CastlePartHeight() { return (74); }
public func CastlePartTop() { return (-13); }
public func CastlePartBasement() { return; }
public func GetResearchBase() { return(ALW2); }
public func Atlantis()	{return(1);}
public func Height()		{return(GetY()+20);}
private func ExplodeSize()	{return 75;}

protected func Initialize()
{
	_inherited();
	GetALOS(GetOwner())->RegisterStructure(CreateObject(ALSK,0,0,GetOwner()));
}

protected func Check()
{
	return(1);
}


public func ControlUp(pCaller)
{
	for(obj in FindObjects(Find_InRect(-40,AbsY(0),80,Height()),Find_Or(Find_Owner(GetOwner()),Find_Owner(NO_OWNER))))
	{
		if(obj && (FindObject2(obj->Find_AtPoint(), Find_Func("IsPartOfAtlantis")) || GetIndexOf(obj, GetALOS(GetOwner())->GetStructures(EffectVar(0, GetALOS(GetOwner()), GetEffect("IntAtlantisOS", GetALOS(GetOwner()))))) != -1))
			obj->SetPosition(GetX(obj),GetY(obj)-1);
	}
	Sound("engine");
	return(1);
}

public func ControlDown(pCaller)
{
		for(obj in FindObjects(Find_InRect(-40,AbsY(0),80,Height()),Find_Or(Find_Owner(GetOwner()),Find_Owner(NO_OWNER))))
		{
			if(obj && (FindObject2(obj->Find_AtPoint(), Find_Func("IsPartOfAtlantis")) || GetIndexOf(obj, GetALOS(GetOwner())->GetStructures(EffectVar(0, GetALOS(GetOwner()), GetEffect("IntAtlantisOS", GetALOS(GetOwner()))))) != -1))
				obj->SetPosition(GetX(obj),GetY(obj)+1);
		}
		Sound("engine");
	return(1);
}

public func ControlLeft(pCaller)
{
		for(obj in FindObjects(Find_InRect(-40,AbsY(0),80,Height()),Find_Or(Find_Owner(GetOwner()),Find_Owner(NO_OWNER))))
		{
			if(obj && (FindObject2(obj->Find_AtPoint(), Find_Func("IsPartOfAtlantis")) || GetIndexOf(obj, GetALOS(GetOwner())->GetStructures(EffectVar(0, GetALOS(GetOwner()), GetEffect("IntAtlantisOS", GetALOS(GetOwner()))))) != -1))
				obj->SetPosition(GetX(obj)-1,GetY(obj));
		}
		Sound("engine");
	return(1);
}

public func ControlRight(pCaller)
{
		for(obj in FindObjects(Find_InRect(-40,AbsY(0),80,Height()),Find_Or(Find_Owner(GetOwner()),Find_Owner(NO_OWNER))))
		{
			if(obj && (FindObject2(obj->Find_AtPoint(), Find_Func("IsPartOfAtlantis")) || GetIndexOf(obj, GetALOS(GetOwner())->GetStructures(EffectVar(0, GetALOS(GetOwner()), GetEffect("IntAtlantisOS", GetALOS(GetOwner()))))) != -1))
				obj->SetPosition(GetX(obj)+1,GetY(obj));
		}
		Sound("engine");
	return(1);
}
