/*-- Shieldemitter --*/
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

  CreateMenu(GetID(), pUser, 0,0, "Schildgenerator", 0, 1);
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
}

func Check()
{
  if(info)
  {
   Message("<c ff0000>Energie:</c> <c 00ff00>%v</c>|<c ff0000>Radius:</c> <c 00ff00>%v</c>",this,energy,radius);
  }
  
  var zpm = FindObject([40, this], [10, ZPM_], [1, [30, "Depledet"]]);

  if(zpm && energy < 90 && zpm.iEnergy > 0)
  {
     zpm.iEnergy -= 1;
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
   if(energy < 100)
   {
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
Switch();
return(1);
}

func IsMachine() {return(1);}
public func Atlantis()
{
	return(1);
}
local ActMap = {
Off = {
Prototype = Action,
Name = "Off",
Length = 1,
Delay = 1,
X = 0,
Y = 0,
Wdt = 40,
Hgt = 25,
NextAction = "Off",
EnergyUsage = 100,
},
On = {
Prototype = Action,
Name = "On",
Length = 36,
Delay = 1,
X = 0,
Y = 25,
Wdt = 40,
Hgt = 25,
NextAction = "On",
},
Opens = {
Prototype = Action,
Name = "Opens",
Length = 26,
Delay = 2,
Reverse = 1,
X = 0,
Y = 50,
Wdt = 40,
Hgt = 25,
NextAction = "Off",
Sound = "SarkTr",
},
Closes = {
Prototype = Action,
Name = "Closes",
Length = 26,
Delay = 2,
X = 0,
Y = 50,
Wdt = 40,
Hgt = 25,
NextAction = "Close",
Sound = "SarkTr",
},
Close = {
Prototype = Action,
Name = "Close",
Length = 1,
Delay = 1,
X = 40,
Y = 0,
Wdt = 40,
Hgt = 25,
NextAction = "Close",
},  };
local Name = "$Name$";
local Touchable = 2;
