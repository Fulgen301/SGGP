/*-- Shieldemitter --*/

#strict 2
#include BAS3

local on;
local radius;
local targets;
local help;
local energy, time;
local info;
local atlantis;
local shield;
local mode;

protected func Initialize()
{
  SetAction("Off");
  radius = 200;
  energy = 0;
}

protected func ControlDigDouble(object pUser)
{
  if(GetAction() == "Close")
  {
   SetAction("Opens");
   return(1);
  }

  if(GetAction() == "Closes" || GetAction() == "Opens")
  {
   return(1);
  }

  CreateMenu(GetID(this()), pUser, 0,0, "Schildgenerator", 0, 1);
  AddMenuItem("An/Aus", "Switch",MEPU,pUser);
  AddMenuItem("Info", "Info",MEPU,pUser);
  if(mode) AddMenuItem("Tarnschirm deaktivieren", "SwitchMode", MEPU, pUser);
  else AddMenuItem("Tarnschirm aktivieren", "SwitchMode", MEPU, pUser);
  if(radius < 550)
  {
   AddMenuItem("+ Radius", "RadUp",MEPU,pUser);
  }
  if(radius > 250)
  {
   AddMenuItem("- Radius", "RadDown",MEPU,pUser);
  }
  if(GetAction() == "Off")
  {
   AddMenuItem("Herunterfahren", "Close",MEPU,pUser);
  }
  if(atlantis)
  {
  	if(energy >= 60)
  	{
  		AddMenuItem("Tarnschirm ein/aus","ToggleCloak",MEPU,pUser);
  	}
  }
  return(1);
}

protected func ControlRight(object pUser)
{
	if (radius > 150)
	{
		RadUp();
	}
}

protected func ControlLeft(object pUser)
{
	if (radius < 650)
	{
		RadDown();
	}
}

private func RadUp()
{
  if(radius < 550)
  {
   radius += 100;
   RadiusChanged();
   return(1);
  }
}

private func RadDown()
{
  if(radius > 250)
  {
   radius -= 100;
   RadiusChanged();
   return(1);
  }
}


protected func Close()
{
  SetAction("Closes");
  info = 0;
  return(1);
}
  
protected func Damage()
{
  if(GetDamage() > 200)
  {
   Explode(100);
   return(1);
  }
  return(1);
}


protected func Info()
{
  Sound("Ding");
  if(info)
  {
   info = 0;
   return(1);
  }
  info = 1;
  return(1);
}

protected func SwitchMode()
{
	if(mode) mode = 0;
	else mode = 1;
}

public func Switch()
{
  if(energy < 20)
  {
   if(!on)
   {
    Sound("start");
    return(1);
   }
  }

  Sound("Ding");
  if(on)
  {
   on = 0;
   SetAction("Off");
   this->Message("<c ff0000>Aus</c>");
   if(shield) shield->RemoveObject();
   if(mode) Uncloak();
   return(1);
  }
  on = 1;
  SetAction("On");
  this->Message("<c 00ff00>An</c>");
  
  if(!mode) shield = this->CreateShield(radius, GetOwner());
  //shield->SetVisibility(VIS_None);
  return true;
}

protected func RadiusChanged()
{
	if(!on || !shield  || mode) return;
	else if(shield && shield->GetID() != C4Id(Format("SH%d", radius/10)))
	{
		var newshield = this->CreateShield(radius, GetOwner());
		shield->RemoveObject();
		shield = newshield;
		//shield->SetVisibility(VIS_None);
		return true;
	}
}

global func CreateShield(int iRadius, int iOwner, object pObj)
{
	if(!pObj) if(!(pObj = this)) return;
	if(!iRadius) iRadius = 300;
	
	var shield = CreateObject(C4Id(Format("SH%d",iRadius/10)));
	if(!shield) return;
	
	shield->SetAction("Field", this);
	shield->SetClrModulation(GetPlrColorDw(pObj->GetOwner()));
	return shield;
}

global func RemoveShield(object pObj)
{
	if(!pObj) if(!(pObj = this)) return;
	var shield;
	if(shield = FindObject2(Find_Func("IsShield"), Find_ActionTarget(pObj))) shield->RemoveObject();
	return true;
}


protected func Check()
{
  if(info)
  {
   Message("<c ff0000>Energie:</c> <c 00ff00>%v</c>|<c ff0000>Radius:</c> <c 00ff00>%v</c>",this,energy,radius);
  }
  
  if(FindContents(ENAP))
  {
   if(energy < 80)
   {
    energy += 25;
    FindContents(ENAP)->RemoveObject();
   }
  }
   if(EnergyCheck(10000) && energy < 100)
   {
     DoEnergy(-10000);
     energy += 1;
   }

  if(energy < 0)
  {
   energy = 0;
  }

  else if(energy > 100)
  {
   energy = 100;
  }

  if(on && energy <= 5)
  {
    Switch();
  }
  
  if(on)
  {
	  time++;
	  if(time % 50 == 0)
		  energy--;
	
	if(mode)
	{
		time++;
		targets = FindObjects(Find_Distance(radius));
		if(shield) shield->RemoveObject();
		for(var obj in FindObjects(Find_Distance(radius)))
		{
			if(obj && !GetEffect("IntGOSGInvisibility", obj))
			{
				AddEffect("IntGOSGInvisibility", obj, 1, 1, 0, GetID(), this);
			}
			for(var line in FindObjects(Find_Func("IsLine"), Find_Or(Find_ActionTarget(obj), Find_ActionTarget2(obj))))
			{
				if(line && !GetEffect("IntGOSGInvisibility", line)) AddEffect("IntGOSGInvisibility", line, 1, 1, 0, GetID(), this);
			}
		}
	}
	else
	{
		targets = [];
		Uncloak();
	}
	return;
	     //Effektbearbeitung
   help += 10;
   var pX;
   var pY;
   var i;
   var lX, lY;
   lX = 0;
   lY = 0;
   pX = Cos(help,radius);
   pY = Sin(help,radius);
   CreateParticle("PSpark",pX,pY,RandomX(-10,10),RandomX(-10,-20),RandomX(40,60),GetPlrColorDw(GetOwner()));
   pX = Cos(help+180,radius);
   pY = Sin(help+180,radius);
   CreateParticle("PSpark",pX,pY,RandomX(-10,10),RandomX(-10,-20),RandomX(40,60),GetPlrColorDw(GetOwner()));

  }
  else
	{
		Uncloak();
	}
  
  return true;
}

public func Uncloak()
{
	for(var obj in FindObjects(Find_Cloaked(this)))
	{
		if(obj) while(GetEffect("IntGOSGInvisibility", obj)) RemoveEffect("IntGOSGInvisibility", obj);
	}
}

global func Find_Cloaked(object pGen)
{
	if(!pGen) pGen = this;
	return [C4FO_Func, "Find_CloakedCheck", pGen];
}

global func Find_CloakedCheck(object pGen)
{
	if(GetEffect("IntGOSGInvisibility", this) && EffectVar(0, this, GetEffect("IntGOSGInvisibility", this)) == pGen) return true;
}

func IsAntiker()
{
	return(1);
}

func EMPShock()
{
EMPShockEffect(20);
return(1);
}

func IsMachine() {return(1);}
public func Atlantis()
{
	return(1);
}

protected func Destruction()
{
	if(shield) shield->RemoveObject();
	return _inherited();
}

public func GetRace() { return SG_All; }
public func IsShieldGenerator() { return true; }

public func FxIntGOSGInvisibilityStart(object pTarget, int iEffect, int iTemp, object pGen)
{
	if(iTemp) return;
	EffectVar(0, pTarget, iEffect) = pGen;
	EffectVar(1, pTarget, iEffect) = pTarget->GetVisibility();
	EffectVar(2, pTarget, iEffect) = pTarget->GetClrModulation();
}

public func FxIntGOSGInvisibilityTimer(object pTarget, int iEffect, int iTime)
{
	if(EffectVar(0, pTarget, iEffect) && !pTarget->~IsLine() && GetIndexOf(pTarget, EffectVar(0, pTarget, iEffect)->LocalN("targets")) == -1)
	{
		return -1;
	}
	pTarget->SetVisibility(VIS_Owner);
	pTarget->SetClrModulation(RGBa(0, 0, 100, 100));
}

public func FxIntGOSGInvisibilityStop(object pTarget, int iEffect, int iReason, bool fTemp)
{
	if(fTemp || !pTarget) return;
	pTarget->SetVisibility(EffectVar(1, pTarget, iEffect));
	pTarget->SetClrModulation(EffectVar(2, pTarget, iEffect));
}