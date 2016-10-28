/*-- Drohnenabschussrampe --*/

#strict 2

local pDrone;
local pTarget;

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
		pDrone = CreateObject(type, 0, 0, this->GetOwner());
		pDrone->SetYDir(-100);
		
		var random = RandomX(-10,10);
		pDrone->SetXDir(random);
		pDrone->SetR(random);
		pDrone->SetAction("Fliegen");
		if(pTarget) pDrone->LocalN("target") = pTarget;
		return true;
	}
	else
	{
		return Message("$NotEnoughEnergy$",this);
	}
}

public func SetTarget(object pObj)
{
	if(!pObj) return;
	pTarget = pObj;
	return this;
}

public func Atlantis()	{return true;}
public func IsAntiker()	{return true;}