/*-- Shieldemitter --*/

#strict 2
#include BAS3

local on;
local radius;
local target;
local help;
local energy, time;
local info;
local atlantis;
local shield;

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
   shield->RemoveObject();
   return(1);
  }
  on = 1;
  SetAction("On");
  this->Message("<c 00ff00>An</c>");
  shield = CreateObject(GOSH);
  shield->SetAction("Field", this);
  shield->SetClrModulation(GetPlrColorDw(GetOwner()));
  shield->SetCon(radius*2);
  
  return true;
}

protected func RadiusChanged()
{
	if(!on || !shield) return;
	shield->SetCon(radius*2);
	shield->SetSolidMask(0, 0, radius*2, radius*2, -50*radius/100, -50*radius/100);
}

func Check()
{
  if(info)
  {
   Message("<c ff0000>Energie:</c> <c 00ff00>%v</c>|<c ff0000>Radius:</c> <c 00ff00>%v</c>",this,energy,radius);
  }
  
  var zpm = FindObject2([40, this], [10, ZPM_], [1, [30, "Depledet"]]);

  if(zpm && energy < 90 && zpm->LocalN("iEnergy") > 0)
  {
     zpm->LocalN("iEnergy") -= 1;
     energy += 10;
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
  }
  
  return true;
}

func IsAsgard()
{
	return(1);
}

func EMPShock()
{
EMPShockEffect(20);
Switch();
return(1);
}

func IsMachine() {return(1);}
public func Atlantis()
{
	return(1);
}

public func ToggleAtlantis()
{
	if(atlantis)
	{
		atlantis=0;
		return(atlantis);
	}
	atlantis=1;
	return(atlantis);
}
