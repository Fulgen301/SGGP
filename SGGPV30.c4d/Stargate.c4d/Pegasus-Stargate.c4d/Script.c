/*--Pegasus-Stargate --*/

#strict 2

#include STRG

protected func Initialize()
{
	return _inherited();
}

public func ChevronCount(object gate)
{
	if(gate->~IsDestinyGate())
	{
		if(gate->~GetName() == "Destiny" && gate->LocalN("destiny")) return 9;
		return 8;
	}
	if(gate->~IsMilkywayGate()) return 8;
	return 7;
}


public func IsStargate()	  { return true; }
public func IsPegasusGate()	  { return true; }


private func RollSound()	  { return Sound("pegasus_startroll"); }
private func ChevronSound()	  { return Sound("pegasus_chevron2");  }
private func FailSound()	  { return Sound("pegasus_fail",0,0,50); }

public func FindDHD()		  { return FindObject2(Find_Func("IsDHD"),Find_Or(Find_Func("IsPegasusDHD"),Find_Func("IsDialPC"))); }