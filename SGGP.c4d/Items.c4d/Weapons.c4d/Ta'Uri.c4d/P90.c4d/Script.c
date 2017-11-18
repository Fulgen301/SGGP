/*-- P90 --*/

#strict 2
#include WEPN
#include WPN2
// Anzeige in der Hand
public func HandSize() { return(900); }
public func HandX()    { return(5000); }
public func HandY()    { return(0); }
public func BarrelYOffset() { return(-1000); }
public func GetRace()	{ return SG1_StargateCenter; }
public func IsPrimaryWeapon()	{ return true; }

public func FMData1(int data)
{
  if(data == FM_Name)      return "$Bullets$";
  if(data == FM_AmmoID)    return STAM;
  if(data == FM_AmmoLoad)  return 50;

  if(data == FM_Reload)    return 80;
  if(data == FM_Damage)    return 8;
  
  return Default(data);
}

public func FMData1T1(int data)
{
	if(data == FT_Name)      return "$Standard$";
	if(data == FM_Recharge)  return 3;
	if(data == FM_Auto)      return 1;
	return FMData1(data);
}


public func FMData1T2(int data)
{
  if(data == FM_Name)      return "$Singleshot$";
  if(data == FM_Recharge)  return 10;
  if(data == FM_Damage)    return 10;

  return FMData1(data);
}

public func Fire1()
{
	return Fire1T1();
}

public func Fire1T1()    // Projektilschuss
{ 
  var user = GetUser();
  var angle = user->AimAngle(20) + RandomX(-4,+4);
  var x,y; user->WeaponEnd(x,y);
  var ammo = CreateObject(SHT1,x,y,GetController(user));
  ammo->Launch(angle,250,500,5,300,GetFMData(FM_Damage, 1));

  // Effekte
  MuzzleFlash(40,user,x,y,angle);
  var dir = GetDir(user)*2-1;
  BulletCasing(dir*6,3,-dir*5,-20,5);

  // Sound
  Sound("MPShot",0,ammo);
}

public func Fire1T2()    // Projektilschuss
{ 
  var user = GetUser();
  var angle = user->AimAngle(20) + RandomX(-1,+1);
  
  var x,y; user->WeaponEnd(x,y);
  var ammo = CreateObject(SHT1,x,y,GetController(user));
  ammo->Launch(angle,250,500,5,300,GetFMData(FM_Damage, 1));
  // Effekte
  MuzzleFlash(40,user,x,y,angle);
  var dir = GetDir(user)*2-1;
  BulletCasing(dir*6,3,-dir*5,-20,5);

  // Sound
  Sound("MPShot",0,ammo);
}
