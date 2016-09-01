/*-- Drohnenabschussrampe --*/

#strict 2

local iDrone;

protected func Initialize()
{
  return(1);
}

protected func Check()
{
	return EnergyCheck(1000);
}

protected func Damage()
{
  if(GetDamage() >= 50)
  {
   Explode(30);
  }
  return(1);
}

public func ControlDigDouble(object pCaller)
{
	SetOwner(pCaller->GetOwner());
	CreateMenu(GetID(),pCaller,0,0,GetName(),0,1,1);
	AddMenuItem("$Fire$","Fire",PUDD,pCaller);
}

protected func Fire(id type)
{
	if(EnergyCheck(1000))
	{
		DoEnergy(-1000);
		iDrone = CreateObject(type, 0, 0, this->GetOwner());
		iDrone->SetYDir(-100);
		
		var random = RandomX(-10,10);
		iDrone->SetXDir(random);
		iDrone->SetR(random);
		return true;
	}
	else
	{
		return Message("$NotEnoughEnergy$",this);
	}
}

public func Atlantis()	{return true;}
public func IsAntiker()	{return true;}