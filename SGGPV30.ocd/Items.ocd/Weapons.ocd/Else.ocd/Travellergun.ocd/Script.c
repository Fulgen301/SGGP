/*-- Pistole --*/



#include WEPN

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

public func OnReload(int i)
{
//  if(i == 1) Sound("PistolLoad");
//  if(i == 2) Sound("PistolLoad");
//  if(i == 3) Sound("GrenadeLoad");
//  if(i == 4) Sound("SlimeLoad");
}

public func FMData1(int data)
{
  if(data == FM_Name)      return("$Standard$");
  if(data == FM_AmmoID)    return(ENAM);
  if(data == FM_AmmoLoad)  return(15);
  if(data == FM_AmmoUsage) return(15);

  if(data == FM_Reload)    return(50);
  if(data == FM_Recharge)  return(50);
//  if(data == FM_Condition) return(!GetUpgrade(KLAS));

  if(data == FM_Damage)    return(70);

  return(Default(data));
}

public func FMData2(int data)
{
  if(data == FM_Name)      return("$Beteuben$");
  if(data == FM_AmmoID)    return(ENAM);
  if(data == FM_AmmoLoad)  return(1);

  if(data == FM_Reload)    return(50);
  if(data == FM_Recharge)  return(50);
//  if(data == FM_Condition) return(!GetUpgrade(KLAS));

  if(data == FM_Damage)    return(70);

  return(Default(data));
}

public func BotData1(int data)
{
  if(data == BOT_Range)    return(500);
  if(data == BOT_Power)    return(BOT_Power_1);

  return(Default(data));
}

public func BotData2(int data)
{
  if(data == BOT_Range)    return(300);
  if(data == BOT_DmgType)  return(DMG_Energy);
  if(data == BOT_Power)    return(BOT_Power_1);

  return(Default(data));
}

public func BotData3(int data)
{
  if(data == BOT_Range)    return(50);
  if(data == BOT_DmgType)  return(DMG_Explosion);
  if(data == BOT_Ballistic)  return(true);
  if(data == BOT_Power)    return(BOT_Power_1);

  return(Default(data));
}

public func BotData4(int data)
{
  if(data == BOT_Range)    return(50);
  if(data == BOT_DmgType)  return(DMG_Bio);
  if(data == BOT_Ballistic)  return(true);
  if(data == BOT_Power)    return(BOT_Power_1);

  return(Default(data));
}

public func Fire1()    // Projektilschuss
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
  Reload();
}


public func Fire2()    // Projektilschuss
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
  Reload();
}
local Name = "$Name$";
local Collectible = 1;
