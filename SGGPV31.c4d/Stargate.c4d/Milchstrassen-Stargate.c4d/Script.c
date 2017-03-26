/*--Milchstrassen-Stargate --*/

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
	if(gate->~IsPegasusGate()) return 8;
	return 7;
}

public func IsStargate()	  { return true; }
public func IsMilkywayGate()  { return true; }
public func FindDHD()		  {return FindObject2(Find_Func("IsDHD"),Find_Or(Find_Func("IsMilkywayDHD"),Find_Func("IsDialPC"))); }

private func RollSound()	  { return Sound("Roll"); }
private func ChevronSound()	  { return Sound("Chevron"); }
private func FailSound()	  { return Sound("Fail",0,0,50); }
public func ChevronPrefix()   { return "CH"; }
