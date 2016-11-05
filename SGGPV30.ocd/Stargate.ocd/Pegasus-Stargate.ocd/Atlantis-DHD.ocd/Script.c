/*---- Das DHD ----*/

#include DHD

public func ChevronSound()
{
	Sound("pegasus_dhd");
	return(1);
}

public func FindStargate()
{
	return(FindObject([C4FO_Func, "IsStargate"],[C4FO_Func, "IsPegasusGate"],Find_Distance(1000),Sort_Distance()));
}
    
public func IsMilkywayDHD()	{return false;}
public func IsPegasusDHD()	{return true;}
public func IsDestinyDHD()	{return false;}

local Touchable = 2;
local Name = "$Name$";
