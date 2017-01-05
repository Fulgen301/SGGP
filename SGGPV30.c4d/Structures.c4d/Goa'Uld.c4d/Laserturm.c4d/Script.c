/*-- Laserturm --*/

#strict

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

public func GetRace() { return SG1_Goauld; }