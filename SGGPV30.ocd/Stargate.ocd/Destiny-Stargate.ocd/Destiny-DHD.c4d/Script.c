/*---- Das DHD ----*/

#strict

#include DHD_

public func ChevronSound()
{
	Sound("destiny_chevron");
	return(1);
}

public func FindStargate()
{
	return(FindObject2(Find_Func("IsStargate"),Find_Func("IsDestinyGate"),Find_Distance(1000),Sort_Distance()));
}

public func IsMilkywayDHD()	{return false;}
public func IsPegasusDHD()	{return false;}
public func IsDestinyDHD()	{return true;}
local Name = "$Name$";
local Touchable = 2;
