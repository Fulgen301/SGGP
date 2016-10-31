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
local Touchable = 2;
local ActMap = {
Opens = {
Prototype = Action,
Name = "Opens",
Length = 25,
Delay = 1,
Reverse = 1,
X = 0,
Y = 0,
Wdt = 30,
Hgt = 20,
Sound = "SarkTr",
NextAction = "Open",
},
Closes = {
Prototype = Action,
Name = "Closes",
Length = 25,
Delay = 1,
X = 0,
Y = 0,
Wdt = 30,
Hgt = 20,
Sound = "SarkTr",
NextAction = "Close",
},
Close = {
Prototype = Action,
Name = "Close",
Length = 1,
Delay = 1,
X = 750,
Y = 0,
Wdt = 30,
Hgt = 20,
NextAction = "Close",
},
Open = {
Prototype = Action,
Name = "Open",
Length = 1,
Delay = 100,
X = 0,
Y = 0,
Wdt = 30,
Hgt = 20,
NextAction = "Open",
},  };
local Name = "$Name$";
