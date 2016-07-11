/*-- Basis --*/

#strict 2

#include DOOR
#include BA15

local energy;

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

protected func Initialize()
{
	_inherited(...);
	AddEffect("IntEnergy",this,1,1,this);
}
protected func Damage()
{
  if(GetDamage() >= 250)
  {
   Explode(80);
  }
  return(1);
}

protected func ContainedUp(pCaller)
{
	if(EnergyCheck(200000))
	{
		for(var i = 0; i < 100; i++)
		{
			DoEnergy(-2000);
		}
		var clonk = CreateContents(GetID(pCaller));
		MakeCrewMember(clonk,GetOwner(pCaller));
		clonk->SetAction("Walk");
		clonk->SetOwner(pCaller->GetOwner());
		Message("<c 00ff00>Klonen erfolgreich!</c>",this);
	}
	else
	{
		Message("<c ff0000>Zu wenig Energie!</c>", this);
	}
}

protected func ContextClone(object pCaller)
{
	[$Clone$|Image=WRKF]
	return ContainedUp(pCaller);
}

protected func FxIntEnergyTimer(object pTarget, int iEffect)
{
	EnergyCheck(100);
}