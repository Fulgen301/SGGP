/*-- Basis --*/

#strict 2

#include DOOR
#include BA15

local energy;

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

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
	if(energy >= 200000)
	{
		energy -= 200000;
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

protected func Timer()
{
	if(EnergyCheck(10000))
	{
		DoEnergy(-10000);
		energy += 100;
	}
	if(energy >= 10000000)
	{
		energy = 10000000;
	}
	return(1);
}