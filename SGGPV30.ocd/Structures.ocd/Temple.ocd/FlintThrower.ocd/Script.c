/*-- Flintwerfer --*/

#strict

local idProjectile;
local iOutSpeed;
local iInterval, iShots;

protected func Initialize() {
  SetAction("Off");
  idProjectile = FLNT;
  iOutSpeed = 10;
  return(1);
}

public func SetDir(a,b,c,d,e,f,g,h,i,j)
  {
  inherited(a,b,c,d,e,f,g,h,i,j);
  UpdateTransferZone();
  }

protected func UpdateTransferZone()
  {
  SetSolidMask(GetDir()*32, 64, 32, 64);
  }

protected func OffCheck()
  {
  var o, iDirA;
  if (GetDir()) iDirA = 180;
  if (o=FindObject(0, iOutSpeed*-30,iOutSpeed*-30,iOutSpeed*60,iOutSpeed*60, OCF_Alive, 0,0, NoContainer()))
    if (Inside((Angle(GetX(o), GetY(o), GetX(), GetY()) + 360 - GetR()) % 360 , iDirA + 30, iDirA + 150))
      if (idProjectile)
        {
        iShots = 0;
        SetAction("On");
        Sound("FlintThrowerOn");
        }
  }
  
protected func OnCheck()
  {
  var o, iDirA = GetDir()*180;
  if (!(o=FindObject(0, iOutSpeed*-40,iOutSpeed*-40,iOutSpeed*80,iOutSpeed*80, OCF_Alive, 0,0, NoContainer()))) return(SetAction("Off"));
  if (!Inside((Angle(GetX(o), GetY(o), GetX(), GetY()) + 360 - GetR()) % 360 , iDirA+10, iDirA+170)) return(SetAction("Off"));
  ++iShots;
  if (!iInterval || !(iShots++%iInterval)) Shoot();
  }
  
public func Shoot()
  {
  var r, iDir, iDirMul;
  iDirMul = (iDir=GetDir())*2-1;
  Sound("FlintThrowerThrow");
  Exit(r=CreateContents(idProjectile), GetVertex(iDir, 0), GetVertex(iDir, 1)+GetDefHeight(idProjectile)/2, GetR()*iDirMul, Cos(GetR(), iOutSpeed)*iDirMul, Sin(GetR(), iOutSpeed)*iDirMul);
  return(r);
  }
local ActMap = {
Off = {
Prototype = Action,
Name = "Off",
Procedure = DFA_FLOAT,
X = 0,
Y = 0,
Wdt = 32,
Hgt = 64,
FacetBase = 0,
Length = 1,
Directions = 2,
Delay = 50,
FlipDir = 1,
NextAction = "Off",
StartCall = "OffCheck",
},
On = {
Prototype = Action,
Name = "On",
Procedure = DFA_FLOAT,
X = 32,
Y = 0,
Wdt = 32,
Hgt = 64,
FacetBase = 0,
Length = 1,
Directions = 2,
FlipDir = 1,
Delay = 50,
NextAction = "On",
EndCall = "OnCheck",
},  };
local Name = "FlintThrower";
