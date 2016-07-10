/*-- P90 --*/

#strict

#include WEPN

local rifleupgrade;

// Anzeige in der Hand
public func HandSize() { return(900); }
public func HandX()    { return(5000); }
public func HandY()    { return(0); }
public func BarrelYOffset() { return(-1000); }

public func OnReload(int i)
{
  Sound("PistolLoad");
}

public func FMData1(int data)
{
  if(data == FM_Name)      return("$Standard$");
  if(data == FM_AmmoID)    return(STAM);
  if(data == FM_AmmoLoad)  return(50);
  if(data == FM_Condition) return(!rifleupgrade);

  if(data == FM_Reload)    return(80);
  if(data == FM_Recharge)  return(3);
  if(data == FM_Auto) 	   return(1);

  if(data == FM_Damage)    return(8);

  return(Default(data));
}


public func FMData2(int data)
{
  if(data == FM_Name)      return("$Singleshot$");
  if(data == FM_AmmoID)    return(STAM);
  if(data == FM_AmmoLoad)  return(50);
//  if(data == FM_Condition) return(rifleupgrade);

  if(data == FM_Reload)    return(80);
  if(data == FM_Recharge)  return(10);
  if(data == FM_Auto) 	   return(0);

  if(data == FM_Damage)    return(10);

  return(Default(data));
}


public func FMData3(int data)
{
  if(data == FM_Name)      return("$Antikull$");
  if(data == FM_AmmoID)    return(ENAM);
  if(data == FM_AmmoLoad)  return(1);
  if(data == FM_Condition) return(GetUpgrade(ANTK));

  if(data == FM_Reload)    return(200);
  if(data == FM_Recharge)  return(10);
  if(data == FM_Auto) 	   return(0);

//  if(data == FM_Damage)    return(20);

  return(Default(data));
}



public func BOTData1(int data)
{
  if(data == BOT_Range)    return(480);

  return(Default(data));
}

public func Fire1()    // Projektilschuss
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

public func Fire2()    // Projektilschuss
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



public func Fire3()    // Antikullschuss
{ 
  var user = GetUser();
  var angle = user->AimAngle(20) + RandomX(-3,+3);
  
  var x,y; user->WeaponEnd(x,y);
  var ammo = CreateObject(ANKB,x,y,GetController(user));
  ammo->Launch(angle,250,500,5,300,GetFMData(FM_Damage, 1));
  // Effekte
  MuzzleFlash(40,user,x,y,angle);
  var dir = GetDir(user)*2-1;
  BulletCasing(dir*6,3,-dir*5,-20,5);

  // Sound
  Sound("MPShot",0,ammo);
}



/* Upgrade */

public func IsUpgradeable(id uid) {
  if(GetUpgrade(uid))
    return(false);
  
  if(uid == ANTK) return("$ANTKUpgradeDesc$");
}

public func OnUpgrade(id uid) {
  if(uid == ANTK) {
//    SetFireMode(2);
    var own = GetOwner(Contained());
    if(Contained()) HelpMessage(own,"$ANTKUpgraded$",Contained());
    return(true);
  }
}

public func OnDowngrade(id uid) {
  if(uid == ANTK) {
//    SetFireMode(1);
    return(true);
  }
}

