/*---- Das DHD ----*/

#strict

#include DHD_

public func ChevronSound()
{
	Sound("pegasus_dhd");
	return(1);
}

public func ToggleAtlantis()
{
	if(atlantis)
	{
		atlantis=0;
	}
	atlantis=1;
	return(atlantis);
}

public func FindStargate()
{
	return(FindObject2(Find_Func("IsStargate"),Find_Func("IsPegasusGate"),Find_Distance(1000),Sort_Distance()));
}

public func IsMilkywayDHD()	{return false;}
public func IsPegasusDHD()	{return true;}
public func IsDestinyDHD()	{return false;}

