/*--Pegasus-Stargate --*/

#include Stargate

protected func Initialize()
{
	return inherited();
}

public func ChevronCount(object gate)
{
	if(gate->~IsDestinyGate())
	{
		if(gate->~GetName() == "Destiny" && gate.destiny) return 9;
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

public func FindDHD()		  { return FindObject([C4FO_Func, "IsDHD"],[C4FO_Or, [C4FO_Func, "IsPegasusDHD"],[C4FO_Func, "IsDialPC"]]); }
local Name = "$Name$";
