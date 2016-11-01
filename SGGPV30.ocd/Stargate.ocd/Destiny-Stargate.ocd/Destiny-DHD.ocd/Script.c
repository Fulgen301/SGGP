/*---- Das DHD ----*/

#include DHD

public func ChevronSound()
{
	Sound("destiny_chevron");
	return(1);
}

public func FindStargate()
{
	return(FindObject([C4FO_Func, "IsStargate"],[C4FO_Func, "IsDestinyGate"],Find_Distance(1000),Sort_Distance()));
}

public func IsMilkywayDHD()	{return false;}
public func IsPegasusDHD()	{return false;}
public func IsDestinyDHD()	{return true;}
local Touchable = 2;
local Name = "$Name$";
