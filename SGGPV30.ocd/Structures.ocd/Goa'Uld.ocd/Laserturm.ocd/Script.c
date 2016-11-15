/*-- Laserturm --*/



local on;
local dist;

func Initialize()
{
  dist = 500;
  SetAction("Close");
  return(1);
}

func ControlDigDouble(pCaller)
{
  if(on)
  {
   on = 0;
   Message("<c ff0000>DEAKTIVIERT!</c>",this());
   Sound("Ding");
  }
  else
  {
   on = 1;
   Message("<c 00ff00>AKTIVIERT!</c>",this());
   Sound("Ding");
  }
  return(1);
}

func Fire()
{
  ScheduleCall(0,"Laser",2,4);
  return(1);
}

func Laser()
{
  Sound("ParticleShot");
  var laser = CreateObject(LASR,0,0,GetOwner());
  laser->SetClrModulation(RGB(255,0,0));
  laser->Set(Random(360),10,650,30,this());
  return(1);
}

func LaserStrike(pVictim, iTime)
{
  pVictim->DoDamage(50);
  if(pVictim)
  {
   pVictim->DoEnergy(-50);
  }
  return(1);
}

func Check()
{
  if(!on) { return(1); }
  if(FindObject2(Find_Distance(dist),Find_Or(Find_Category(C4D_Vehicle()),Find_OCF(OCF_Alive())),Find_Hostile(GetOwner())))
  {
   if(GetAction() eq "Close")
   {
    Sound("BipBipBip");
    SetAction("Opens");
    return(1);
   }
  }
  return(1);
}
local Touchable = 2;
local ActMap = {
Opens = {
Prototype = Action,
Name = "Opens",
Length = 50,
Delay = 1,
X = 0,
Y = 0,
Wdt = 60,
Hgt = 75,
NextAction = "Open",
Sound = "SarkTr",
EnergyUsage = 100,
},
Open = {
Prototype = Action,
Name = "Open",
Length = 1,
Delay = 37,
X = 3000,
Y = 0,
Wdt = 60,
Hgt = 75,
NextAction = "Closes",
StartCall = "Fire",
Sound = "LasertowerCharge",
},
Closes = {
Prototype = Action,
Name = "Closes",
Length = 50,
Reverse = 1,
Delay = 1,
X = 0,
Y = 0,
Wdt = 60,
Hgt = 75,
NextAction = "Close",
Sound = "SarkTr",
},
Close = {
Prototype = Action,
Name = "Close",
Length = 1,
Delay = 1,
X = 0,
Y = 0,
Wdt = 60,
Hgt = 75,
NextAction = "Close",
},  };
local Name = "$Name$";
