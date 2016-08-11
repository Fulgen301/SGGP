/*-- Kull Handgelekswaffe --*/

#strict

#include WEPN

// Anzeige in der Hand
public func HandSize() { return(800); }
public func HandX()    { return(5500); }
public func HandY()    { return(-1000); }
public func BarrelYOffset() { return(-2700); }
public func GetRace()	{ return SG1_Goauld; }

public func FMData1(int data)
{
  if(data == FM_Name)      return("$Standard$");
  if(data == FM_AmmoID)    return(ENAM);
  if(data == FM_AmmoLoad)  return(200);

  if(data == FM_Reload)    return(50);
  if(data == FM_Recharge)  return(5);

  if(data == FM_Damage)    return(10);
  if(data == FM_Auto)      return(1);

  return(Default(data));
}

public func Fire1()    // Projektilschuss
{
  var user = GetUser();
  var angle = user->AimAngle(20) + RandomX(-4,+4);
  var x,y; user->WeaponEnd(x,y);
  var ammo = CreateObject(TACS,x,y,GetController(user));
  ammo->Launch(angle,250,600,5,300,GetFMData(FM_Damage, 1));

  // Effekte
  MuzzleFlash(40,user,x,y,angle);
  var dir = GetDir(user)*2-1;
  BulletCasing(dir*6,3,-dir*5,-20,5);

  // Sound
  Sound("staff_weapon",0,ammo);
  return(1);
}

func IsGoauldWeapon() { return(true); }
func AlchemProcessTime() { return(800); }