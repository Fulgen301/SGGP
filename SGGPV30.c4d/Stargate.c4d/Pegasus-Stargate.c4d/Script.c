/*--Pegasus-Stargate --*/

#strict 2

#include STRG

func Initialize()
{
	return(_inherited());
}

public func IsStargate()
{
	return true;
}

public func IsPegasusGate()
{
	return true;
}

public func RollSound()
{
	Sound("pegasus_startroll");
	return(1);
}

public func ChevronSound()
{
	Sound("pegasus_chevron2");
	return(1);
}

public func FailSound()
{
	Sound("pegasus_fail",0,0,50);
	return(1);
}

public func ChevronCount(object gate)
{
	if(gate->~IsDestinyGate())
	{
		if(gate->~GiveName() == "Destiny")
		{
			return(9);
		}
		return(8);
	}
	if(gate->~IsMilkywayGate())
	{
		return(8);
	}
	return(7);
}

public func FindDHD()
{
	return FindObject2(Find_Func("IsDHD"),Find_Or(Find_Func("IsPegasusDHD"),Find_Func("IsDialPC")));
}

