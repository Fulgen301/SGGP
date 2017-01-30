/*--Destiny-Stargate --*/

#strict 2

#include STRG

protected func Initialize()
{
	return _inherited();
}

public func ChevronCount(object gate)
{
	if(IsDestinyGate() && Name == "Destiny" && gate->LocalN("destiny")) return 9;
	if(gate->~IsMilkywayGate() || gate->~IsPegasusGate()) return 8;
	return 7;
}

public func IsStargate()	  { return true; }
public func IsDestinyGate()	  { return true; }


private func RollSound()	  { return Sound("destiny_roll"); }
private func ChevronSound()	  { return Sound("destiny_chevron");  }
//private func OpenSound()	  { return Sound("destiny_kawoosh"); }
private func FailSound()	  { return Sound("pegasus_fail",0,0,50); }
public func ChevronPrefix()   { return "UN"; }

public func FindDHD()		  { return FindObject2(Find_Func("IsDHD"),Find_Or(Find_Func("IsDestinyDHD"),Find_Func("IsDialPC"))); }

protected func SmokeEffect()
{
	if(ramp)
	{
		for(var i = 0; i < 20; i++)
		{
			CreateParticle("Smoke", 58, 59, 0, 0, 100, RGB(0,0,0), ramp);
			CreateParticle("Smoke", 98, 59, 0, 0, 100, RGB(0,0,0), ramp);
		}
	}
}

protected func DialSounds()
{
  if(GetPhase() == 1)
  {
   RollSound();
  }
  
  if(GetPhase() == 14)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 33)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 44)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 49)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 78)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 92)
  {
   ChevronSound();
  }

  if(GetPhase() == 98)
  {
	  if(fake)
	  {
		  FailSound();
		  Deactivate();
	  }
  }
  if(GetPhase() == 99)
  {
   ChevronSound();
  }
  return(1);
}


public func ChevronPhase()
{
	return [1, 14, 33, 44, 49, 78, 92, 98];
}