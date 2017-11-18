/*-- Betäubungsgranate --*/
#strict 2
#include NADE
local Target;
local pStructure;

public func Color()	{return RGB(255,0,0);}	//Farbe

global func KnockWave(int Level,object pTarget)
{
  if(!pTarget)
  {
	  return false;
  }
  CreateObject(WRSW,0,0,GetOwner(pTarget))->SetMaxSize(Level);
  return true;
}

public func Fused(object container)
{
  CreateObject(WRSW, 0, 0, GetOwner())->SetMaxSize(300);
  RemoveObject();
}

protected func Hit()
{
  Sound("GRHit*");
}



func IsGoauldWeapon() { return(true); }
func AlchemProcessTime() { return(500); }
func IsGrenade() { return(true); }
public func IsReloading() {return(0);}
public func GetRace() { return SG1_Goauld; }
