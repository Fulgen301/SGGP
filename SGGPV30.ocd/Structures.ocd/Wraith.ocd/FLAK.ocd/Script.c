/*-- FLAK Geschutz --*/


#include BAS4

local pTarget;
local MaxDist;
local angl;
local timer;
local manuell;

func Initialize()
{
  SetGraphics(0);
  MaxDist = 500;
  SetAction("Turn");
  return(1);
}

func ControlDigDouble()
{
  if(manuell == 1)
  {
   manuell = 0;
   Message("Manuelle Steuerung:|<c 00ff00>INAKTIV</c>",this());
  }
  else
  {
   manuell = 1;
   Message("Manuelle Steuerung:|<c ff0000>AKTIV</c>",this());
  }
  Sound("BipBipBip");
  return(1);
}


func ClearDir(int What)
{
  if(What == 1)
  {
    ControlLeft();
  }
  if(What == 2)
  {
    ControlRight();
  }
}

func ControlUpdate(object controller, int comdir, bool dig, bool throw)
{
  var User = controller;
  SetComDir(comdir);
  ClearScheduleCall(this(), "ClearDir");
  if(comdir == COMD_Left) ScheduleCall(this(), "ClearDir", 1, 90, 1);
  if(comdir == COMD_Right) ScheduleCall(this(), "ClearDir", 1, 90, 2);
  return(1);
}

func ControlLeft()
{
  if(!manuell) { return(false); }
  if(angl > 0)
  {
   angl --;
   var angle = (GetPhase()*2)-90;
   var x,y;
   x = Sin(angle,40);
   y = -Cos(angle,40);
   CreateParticle("PSpark",x,y,0,0,20,RGB(255,0,0));
   SetPhase(angl);
  }
  return(1);
}

func ControlRight()
{
  if(!manuell) { return(false); }
  if(angl < 90)
  {
   angl ++;
   var angle = (GetPhase()*2)-90;
   var x,y;
   x = Sin(angle,40);
   y = -Cos(angle,40);
   CreateParticle("PSpark",x,y,0,0,20,RGB(255,0,0));
   SetPhase(angl);
  }
  return(1);
}

func ControlThrow()
{
  if(!manuell) { return(false); }
  if(!timer)
  {
   Fire();
  }
  return(1);
}

func Damage()
{
  if(GetDamage() > 200)
  {
   ScheduleCall(0,"DestructLaser",2,8);
   ScheduleCall(0,"Explosion",17);
   return(1);
  }
  return(1);
}

func DestructLaser()
{
  Sound("wr_flakfire");
  var laser = CreateObject(LASR,0,0,GetOwner());
  laser->SetClrModulation(RGB(0,255,0));
  laser->Set(Random(360),10,650,30,this());
  return(1);
}

func Explosion()
{
  Explode(50);
  return(1);
}

func SetRot(int iRot)
{
  angl = (iRot - 90)/2;
  if(angl > 180) 
  {
   SoundStop();
   return(1); 
  }
  if(GetPhase() > angl)
  {
   SoundStart();
   SetPhase(GetPhase() - 1);
  }
  if(GetPhase() < angl)
  {
   SoundStart();
   SetPhase(GetPhase() + 1);
  }
  if(GetPhase() == angl)
  {
   if(GetXDir(pTarget) + GetYDir(pTarget) == 0)
   {
    SoundStop();
   }
   if(timer == 0)
   {
    timer = 100;
    Sound("BipBipBip");
    ScheduleCall(0,"Fire",20);
   }
  }
  return(1);
}

func Check()
{
  if(timer > 0)
  {
   timer --;
  }
  
  if(manuell) { return(1); }
  
  if(FindObject2(Find_InRect(-10000,-10000,20000,10000),Find_Distance(MaxDist),Find_Or(Find_Category(C4D_Vehicle),Find_OCF(OCF_CrewMember())),Find_Hostile(GetOwner()),Sort_Distance()))
  {
   pTarget = FindObject2(Find_InRect(-10000,-10000,20000,10000),Find_Distance(MaxDist),Find_Or(Find_Category(C4D_Vehicle),Find_OCF(OCF_CrewMember())),Find_Hostile(GetOwner()),Sort_Distance());
  }
  
  if(!GetAlive(pTarget))
  {
   pTarget = 0;
  }
  
  if(pTarget)
  {
   if(ObjectDistance(pTarget) > MaxDist)
   {
    pTarget = 0;
   }
  }
  if(pTarget)
  {
   if(GetY() - GetY(pTarget) > 0)
   {
    SetRot(Angle(GetX(pTarget),GetY(pTarget),GetX(),GetY()));
   }
   else
   {
    SoundStop();
   }
  }
  else
  {
   SoundStop();
  }
  return(1);
}

func SoundStart()
{
  SetGraphics(0);
  Sound("luke1",0,0,50,0,1);
  return(1);
}

func SoundStop()
{
  SetGraphics("Green");
  Sound("luke1",0,0,50,0,-1);
  return(1);
}

public func Fire()
{
  ScheduleCall(0,"FireLaser",2,2);
  timer = 100;
  return(1);
}

public func FireLaser(int iRota)
{
  Sound("wr_flakfire");
  var user = GetOwner();
  var x,y;
  var angle = (GetPhase()*2)-90;
  x = Sin(angle,25);
  y = -Cos(angle,25);
  var laser = CreateObject(LASR,x,y,GetOwner());
  laser->SetClrModulation(RGB(0,255,0));
  laser->Set(angle,8,450,20,this());
  MuzzleFlash(250,this(),x,y,angle,RGBa(0,255,0,0));
  return(1);
}

public func LaserStrike(object pTarget)
{
  DoDmg(50, DMG_Energy, pTarget);
  return(0);
}

public func IsBulletTarget(id idBullet, object pBullet, object pShooter)
{
  if(idBullet == LASR)
  {
   if(GetOwner(pShooter) == GetOwner())
   {
    return(false);
   }
  }
  return(true);
}
local Touchable = 2;
local ActMap = {
Turn = {
Prototype = Action,
Name = "Turn",
Length = 90,
Delay = 0,
X = 0,
Y = 0,
Wdt = 60,
Hgt = 60,
NextAction = "Hold",
EnergyUsage = 100,
},  };
local Name = "$Name$";
