/*-- Wraith Stunner --*/

#strict 2
#include WEPN
#include WPN2

// Anzeige in der Hand
public func HandSize() { return(800); }
public func HandX()    { return(5500); }
public func HandY()    { return(-1000); }
public func BarrelYOffset() { return(-2700); }
public func GetRace()	{ return SGA_Wraith; }
public func IsPrimaryWeapon()	{ return true; }

public func FMData1(int data)
{
  if(data == FM_Name)      return GetName();
  if(data == FM_AmmoID)    return ENAM;
  if(data == FM_AmmoLoad)  return 10;
  if(data == FM_AmmoUsage) return 10;

  if(data == FM_Reload)    return 30;
  if(data == FM_Recharge)  return 30;

  if(data == FM_Damage)    return 0;

  return Default(data);
}

public func FMData1T1(int data)
{
	if (data == FT_Name)	return "$Stun$";
	return FMData1(data);
}

public func Fire1()
{
	return Fire1T1();
}

public func Fire1T1()    // Projektilschuss
{ 
  var user = GetUser();
  var angle = user->AimAngle(20) + RandomX(-5,+5);
  var x,y; user->WeaponEnd(x,y);
  var ammo = CreateObject(WRSF,x,y,GetController(user));
  ammo->Launch(angle,250,600,5,300,GetFMData(FM_Damage, 1));

  // Effekte
  MuzzleFlash(40,user,x,y,angle);
  var dir = GetDir(user)*2-1;
  BulletCasing(dir*6,3,-dir*5,-20,5);

  // Sound
  Sound("wr_pistolfire",0,ammo);
}
