/*-- Kull-Disruptor --*/



#include WEPN

local laser; //der Laserstrahl

// Anzeige in der Hand
public func HandX() { return(5000); }
public func HandY() { return(500); }
public func GetRace()	{ return SG1_StargateCenter; }

public func FMData1(int data)
{
  if(data == FM_Name)      return("$Shockwave$");
  if(data == FM_AmmoID)    return(ENAM);
  if(data == FM_AmmoLoad)  return(30);
  if(data == FM_AmmoUsage) return(30);

  if(data == FM_Reload)    return(70);
  if(data == FM_Recharge)  return(70);
//  if(data == FM_Condition) return(!GetUpgrade(KLAS));

  if(data == FM_Damage)    return(50);

  return(Default(data));
}

public func Fire1()    // Projektilschuss
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

public func OnDeselect() 
{
  if(laser) {
    RemoveObject(laser);
  }
}
local Name = "$Name$";
local Collectible = 1;
