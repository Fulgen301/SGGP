/*-- Drohnedefence --*/

#strict

local target;
local dist;
local off;
local time;
local frequ;
local force;
local aArray;

func Initialize()
{
  aArray = CreateArray(5);
  aArray[0] = PUDD;
  aArray[1] = DRDR;
  aArray[2] = DRVE;
  aArray[3] = BIRD;
  aArray[4] = ZAP1;
  
  SetAction("Close");
  dist = 1000;
  off = 1;
  frequ = 20;
  force = 50;
  return(1);
}

func Check()
{
  if(GetCon() != 100)
  {
   return(1);
  }

  if(off)
  {
   return(1);
  }

  if(time > 0)
  {
   time --;
  }
  
  if(GetAction() eq "Opens")
  {
   return(1);
  }
  
  if(GetAction() eq "Closes")
  {
   return(1);
  }

  var i;
  for (i in aArray)
  {
   if(FindObject2(Find_ID(i),Find_PathFree(),Find_Distance(dist)))
   {
    if(GetAction() eq "Open")
    {
     if(time == 0)
     {
      target = FindObject2(Find_ID(i),Find_PathFree(),Find_Distance(dist));
      Fire();
      SetAction("Open");
      return(1);
     }
     return(1);
    }
    SetAction("Opens");
   }
  }
  return(1);
}

func Fire()
{
  if(GetID(target) == PUDD)
  {
   if(GetAction(target) eq "Dead")
   {
    return(1);
   }
   
   if(GetAction(target) eq "Over")
   {
    return(1);
   }
  }
  time = frequ;
  var laser = CreateObject(LASR,0,-5);
  MuzzleFlash(100,this(),0,-5,0,RGB(255,0,0));
  var angle = Angle(Abs(GetX()),Abs(GetY()),Abs(GetX(target)),Abs(GetY(target)));
  laser->SetClrModulation(RGB(255,0,0));
  laser->Set(angle,5,ObjectDistance(target),15,this());
  target->DoDamage(force);
  if(target)
  {
   target->DoEnergy(-1*force);
  }
  Sound("EnergyRifle");
  return(1);
}

func ControlDigDouble()
{
  if(GetCon() != 100)
  {
   return(1);
  }

  if(off == 0)
  {
   off = 1;
   Message("<c ff0000>Aus</c>",this());
   Sound("Connect");
   return(1);
  }
  
  if(off == 1)
  {
   off = 0;
   Message("<c 00ff00>An</c>",this());
   Sound("Connect");
   return(1);
  }
  return(1);
}

func Damage()
{
  if(GetDamage() >= 50)
  {
   Explode(30);
  }
  return(1);
}
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
NextAction = "Closes",
},  };
local Name = "$Name$";
