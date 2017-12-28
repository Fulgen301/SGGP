/*-- Pistole --*/

#strict 2

#include WEPN
#include WPN2

// Anzeige in der Hand
public func HandSize() { return(800); }
public func HandX()    { return(5500); }
public func HandY()    { return(-1000); }
public func BarrelYOffset() { return(-2700); }
public func GetRace()	{ return SGA_Travellers;}

public func Selection()
{
  Sound("dexgun_engage");
  return(1);
}

public func _FMData1(int data)
{
  if(data == FM_Name)      return "$Standard$";
  if(data == FM_AmmoID)    return ENAM;
  if(data == FM_AmmoLoad)  return 15;
  if(data == FM_AmmoUsage) return 15;

  if(data == FM_Reload)    return 50;
  if(data == FM_Recharge)  return 50;
  if(data == FM_Damage)    return 70;

  return Default(data);
}

public func FMData1(int data)
{
  if (FindDefinition(WPN2)) return _FMData1(data);
  return FMData1T1(data);
}

public func FMData1T1(int data)
{
  if (FindDefinition(WPN2))
  {
    if (data == FT_Name) return "$Kill$";
  }
  else
  {
    if (data == FM_Name) return Format("%s - $Kill$", _FMData1(FM_Name));
  }
  return _FMData1(data);
}

public func FMData1T2(int data)
{
  if (FindDefinition(WPN2))
  {
    if (data == FT_Name) return "$Beteuben$";
  }
  else
  {
    if (data == FM_Name) return Format("%s - $Beteuben$", _FMData1(FM_Name));
  }
  
  if(data == FM_Damage)    return 0;

  return _FMData1(data);
}

public func FMData2(int data)
{
  if (FindDefinition(WPN2)) return;
  return FMData1T2(data);
}

public func Fire1()
{
  return Fire1T1();
}

public func Fire1T1()
{ 
  var user = GetUser();
  var angle = user->AimAngle(20) + RandomX(-1,+1);
  var x,y; user->WeaponEnd(x,y);
  var ammo = CreateObject(SH7X,x,y,GetController(user));
  ammo->Launch(angle,250,600,10,100,GetFMData(FM_Damage, 1),5);

  // Effekte
  MuzzleFlash(40,user,x,y,angle);
  var dir = GetDir(user)*2-1;
  BulletCasing(dir*6,3,-dir*5,-20,5);

  // Sound
  Sound("ronongun",0,ammo);
}


public func Fire1T2()
{ 
  var user = GetUser();
  var angle = user->AimAngle(20) + RandomX(-1,+1);
  var x,y; user->WeaponEnd(x,y);
  var ammo = CreateObject(RONB,x,y,GetController(user));
  ammo->Launch(angle,250,600,5,300,GetFMData(FM_Damage, 1));

  // Effekte
  MuzzleFlash(40,user,x,y,angle);
  var dir = GetDir(user)*2-1;
  BulletCasing(dir*6,3,-dir*5,-20,5);

  // Sound
  Sound("ronongun",0,ammo);
}

public func Fire2()
{
  return Fire1T2();
}
