/*---- Das DHD ----*/

#strict 2

#include DHD_

public func ChevronSound()
{
	Sound("pegasus_dhd");
	return(1);
}


public func FindStargate()
{
	return(FindObject2(Find_Func("IsStargate"),Find_Func("IsPegasusGate"),Find_Distance(1000),Sort_Distance()));
}

public func IsMilkywayDHD()	{return false;}
public func IsPegasusDHD()	{return true;}
public func IsDestinyDHD()	{return false;}

