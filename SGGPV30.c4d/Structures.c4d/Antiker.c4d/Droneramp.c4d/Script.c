/*-- Drohnenabschussrampe --*/

#strict 2

local pDrone;
local pTarget;
local fire;

protected func Initialize()
{
  return(1);
}

protected func Check()
{
	if(fire) return Fire();
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
	//CreateMenu(GetID(),pCaller,0,0,GetName(),0,1,1);
	//AddMenuItem("$Fire$","Fire",PUDD,pCaller);
	
	CreateNewMenu([
	Menu_Style_Context(),
	Menu_Symbol(GetID()),
	Menu_Object(pCaller),
	Menu_Caption(GetName()),
	Menu_Adaptor([Menu_Adaptor_Caption("$Fire$"), Menu_Adaptor_Symbol(PUDD), Menu_Adaptor_Callbacks([ObjectCallback("Fire",this)])])
	]);
}

protected func Fire()
{
	if(EnergyCheck(1000))
	{
		DoEnergy(-1000);
		pDrone = CreateObject(PUDD, 0, 0, this->GetOwner());
		pDrone->SetYDir(-100);
		
		var random = RandomX(-10,10);
		pDrone->SetXDir(random);
		pDrone->SetR(random);
		pDrone->SetAction("Fliegen");
		if(pTarget) pDrone->LocalN("target") = pTarget;
		return true;
	}
}

public func SetTarget(object pObj)
{
	if(pObj) pTarget = pObj;
	return this;
}

public func Atlantis()	{return true;}
public func IsAntiker()	{return true;}