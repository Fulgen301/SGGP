/*-- Stabwaffe --*/

#strict 2
#include WEPN
#include WPN2

// Anzeige in der Hand
public func HandSize() { return(800); }
public func HandX()    { return(7000); }
public func HandY()    { return(-5000); }
public func BarrelYOffset() { return(-2700); }
public func GetRace()	{ return SG1_Goauld; }
public func IsPrimaryWeapon()	{ return true; }

public func OnAimStart()
{
  Sound("lancearme");
  return(1);
}

public func FMData1(int data)
{
  if(data == FM_Name)      return GetName();
  if(data == FM_AmmoID)    return ENAM;
  if(data == FM_AmmoLoad)  return 20;
  if(data == FM_AmmoUsage) return 20;

  if(data == FM_Reload)    return 50;
  if(data == FM_Recharge)  return 1;
  if(data == FM_Aim) 	   return 1;

  if(data == FM_Damage)    return 30;

  return Default(data);
}

public func FMData1T1(int data)
{
	if (data == FT_Name) return "$Standard$";
	return FMData1(data);
}

public func Fire1()
{
	return Fire1T1();
}

public func Fire1T1()    // Projektilschuss
{ 
  var user = GetUser();
  var angle = user->AimAngle(20) + RandomX(-1,+1);
  var x,y; user->WeaponEnd(x,y);
  var ammo = CreateObject(STBS,x,y,GetController(user));
  ammo->Launch(angle,250,600,5,300,GetFMData(FM_Damage, 1));

  // Effekte
  MuzzleFlash(40,user,x,y,angle);
  var dir = GetDir(user)*2-1;
  BulletCasing(dir*6,3,-dir*5,-20,5);

  // Sound
  Sound("LaunchSW",0,ammo);
}

func IsGoauldWeapon() { return(true); }
func AlchemProcessTime() { return(800); }
