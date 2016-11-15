/*-- Shieldemitter --*/


#include BAS3

local on;
local radius;
local target;
local help;
local energy, time;
local info;
local atlantis;
local cloaked;

func Initialize()
{
  SetAction("Off");
  radius = 200;
  energy = 0;
}

func ControlDigDouble(object pUser)
{
  if(GetAction() eq "Close")
  {
   SetAction("Opens");
   return(1);
  }

  if(GetAction() eq "Closes")
  {
   return(1);
  }
  
  if(GetAction() eq "Opens")
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
  if(GetAction() eq "Off")
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

func ControlRight(object pUser)
{
	if (radius > 150)
	{
		RadUp();
	}
}

func ControlLeft(object pUser)
{
	if (radius < 650)
	{
		RadDown();
	}
}

func RadUp()
{
	if(cloaked)
		return(1);
  if(radius < 550)
  {
   radius += 100;
   return(1);
  }
}

func RadDown()
{
	if(cloaked)
		return(1);
  if(radius > 250)
  {
   radius -= 100;
   return(1);
  }
}


func Close()
{
  SetAction("Closes");
  info = 0;
  return(1);
}
  
func Damage()
{
  if(GetDamage() > 200)
  {
   Explode(100);
   return(1);
  }
  return(1);
}


func Info()
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

func ToggleCloak()
{
	if(!cloaked)
	{
		cloaked=1;
		return(1);
	}
	cloaked=0;
	return(0);
}

func Switch()
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
   Message("<c ff0000>Aus</c>",this());
   return(1);
  }
  on = 1;
  SetAction("On");
  Message("<c 00ff00>An</c>",this());
  return(1);
}

func Check()
{
  if(info)
  {
   Message("<c ff0000>Energie:</c> <c 00ff00>%v</c>|<c ff0000>Radius:</c> <c 00ff00>%v</c>",this(),energy,radius);
  }

  if(FindObject(ZPM_,0,0,0,0,0,"Inactive",0,this()))
  {
   if(energy < 90)
   {
    if(LocalN("iEnergy",FindObject2(Find_Container(this()),Find_Not(Find_Action("Depledet")))) != 0)
    {
     LocalN("iEnergy",FindObject(ZPM_,0,0,0,0,0,"Inactive",0,this())) -= 1;
     energy += 10;
    }
   }
  }
  
  if(FindContents(ENAP))
  {
   if(energy < 80)
   {
    energy += 25;
    FindContents(ENAP)->RemoveObject();
   }
  }
  
  if(FindObject(ENRG))
  {
   if(EnergyCheck(10000))
   {
    if(energy != 100)
    {
     DoEnergy(-10000);
     energy += 1;
    }
   }
  }

  if(energy < 0)
  {
   energy = 0;
  }

  if(energy > 100)
  {
   energy = 100;
  }

  if(on)
  {
   //Depledetbearbeitung
   if(energy <= 5)
   {
    Switch();
    return(1);
   }
   
   if(cloaked)
   {
   	Cloak();
   	time += 1;
   	if(time == 10)
   	{
   		energy -= 1;
   		time = 0;
   	}	
   	return(1);
   }

   //Effektbearbeitung
   help += 10;
   var pX;
   var pY;
   var mat;
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
   /*while (i <= 360)
	{
		i++;
		if(i <= 90)
		{
			mat = ExtractLiquid(lX, lY);
			lX++;
			lY++;
		}
		if(i <= 180 && i > 90)
		{
			mat = ExtractLiquid(lX, lY);
			lX--;
			lY++;
		}
		if(i <= 270 && i > 180)
		{
			mat = ExtractLiquid(lX,lY);
			lX--;
			lY--;
		}
		if(i <= 360 && i > 270)
		{
			mat = ExtractLiquid(lX,lY);
			lX++;
			lY--;
		}
			
	}*/
   time += 1;
   if (time == 50)
   {
	   energy -= 1;
	   time = 0;
   }


   //ABSTOSSVERHALTEN
   for(target in FindObjects(Find_Distance(radius-10),Find_OCF(OCF_HitSpeed4())))
   {
    //Jumperdrohne
	   if (GetID(target) == PUDD)
	   {
		   target->~Hit();
		   energy -= 5;
		   if (!target)
		   {
			   return(1);
		   }
	   }
    
    //Meteorid
    if(GetID(target) == METO)
    {
     target->~Hit();
     return(1);
    }
   }
  
   //Trefferbearbeitung 2
   for(target in FindObjects(Find_Distance(radius),Find_Not(Find_Distance(radius - radius/8))))
   {
    //Objekt wird nicht abgestoßen, wenn es sich nicht bewegt!
    if((GetXDir(target) + GetYDir(target)) == 0)
    {
     return(1);
    }
    
    if (GetCategory(target) & C4D_Structure())
    {
    	return(1);
    }
    
    //Normale Kugel
    if(target->~IsBullet() == 1)
    {
     target->RemoveObject();
//     energy -= 2;
     return(1);
    }
    
    //KULL Ignorieren
    if(GetID(target) == KULL)
    {
     if(target->~HasGear())
     {
      return(1);
     }
    }
    
    //Jumperdrohne
    if(GetID(target) == PUDD)
    {
     target->~EMPShock();
     //energy -= 5;
     if(!target)
     {
      return(1);
     }
    }
    
    //Meteorid
    if(GetID(target) == METO)
    {
     target->~Hit();
	 energy -= 5;
     return(1);
    }

	if (GetID(target) == REDR)
	{
		target->~Hit();
		energy -= 5;
		return(1);
	}
    
    //Rakete
    if(GetID(target) == MISS)
    {
     target->~Hit();
     energy -= 10;
     if(!target)
     {
      return(1);
     }
    }
    
    //Lenkrakete
    if(GetID(target) == HMIS)
    {
     target->~Hit();
     energy -= 13;
     if(!target)
     {
      return(1);
     }
    }

    /*if(GetOCF(target) & OCF_Construct())
    {
     return(1);
    }*/

    target->~SetAction("Walk");
    target->SetXDir((GetX(target)-RandomX(GetX()+2,GetX()-2)) / 5);
    target->SetYDir((GetY(target)-GetY()) / 5);
   }
  }
  
  return(1);
}

func Cloak()
{
	var obj;
	for(obj in FindObjects(Find_InRect(-(radius/2),-(radius/2),radius,radius)))
	{
		if(!(GetCategory(obj) & C4D_Living))
		{
			obj->SetOwner(GetOwner());
		}
		obj->SetVisibility(VIS_Owner());
	}
	DrawParticleLine("PSpark",GetX()-(radius/2),GetY()-(radius/2),GetX()+(radius/2),GetY()+(radius/2),0,RandomX(40,60));
	return(1);
}

func UnCloak()
{
	var obj;
	for(obj in FindObjects(Find_InRect(-(radius/2),-(radius/2),radius,radius)))
	{
		if(!(GetCategory(obj) & C4D_Living))
		{
			obj->SetOwner(GetOwner());
		}
		obj->SetVisibility(VIS_All());
	}
	return(1);
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
local Touchable = 2;
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
