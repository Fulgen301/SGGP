/*-- Kull-Disruptor --*/

#strict 2
#include WEPN
#include WPN2

// Anzeige in der Hand
public func HandX() { return(5000); }
public func HandY() { return(500); }
public func GetRace()	{ return SG1_StargateCenter; }
public func IsSecondaryWeapon()	{ return true; }

public func FMData1(int data)
{
  if(data == FM_Name)      return GetName();
  if(data == FM_AmmoID)    return ENAM;
  if(data == FM_AmmoLoad)  return 200;
  if(data == FM_AmmoUsage) return 200;

  if(data == FM_Reload)    return 100;
  if(data == FM_Recharge)  return 100;
  if(data == FM_Aim)       return 1;

  if(data == FM_Damage)    return 0;

  return Default(data);
}

public func FMData1T1(int data)
{
	if (data == FT_Name) return "$Shockwave$";
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
  var ammo = CreateObject(AKWW,x,y,GetController(user));
  ammo->Launch(angle,50,150,3,100,GetFMData(FM_Damage, 1));

  MuzzleFlash(50,user,x,y,angle,RGBa(40,40,255,0));
  Sound("KullDis");
  Reload();
}

public func OnReload()
{
  Sound("EMPLoad");
}

