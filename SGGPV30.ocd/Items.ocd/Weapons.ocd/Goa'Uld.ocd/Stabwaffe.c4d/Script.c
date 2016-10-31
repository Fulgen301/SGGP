/*-- Pistole --*/

#strict

#include WEPN

// Anzeige in der Hand
public func HandSize() { return(800); }
public func HandX()    { return(5000); }
public func HandY()    { return(-1000); }
public func BarrelYOffset() { return(-2700); }
public func GetRace()	{ return SG1_Goauld; }

public func Initialize()
{
  CreateContents(GONZ);
  return _inherited();
}

public func Selection()
{
  Sound("staff_engage");
  return(1);
}
public func OnReload(int i)
{
//  if(i == 1) Sound("PistolLoad");
//  if(i == 2) Sound("PistolLoad");
}

public func FMData1(int data)
{
  if(data == FM_Name)      return("$Standard$");
  if(data == FM_AmmoID)    return(ENAM);
  if(data == FM_AmmoLoad)  return(1);
  if(data == FM_AmmoUsage) return(1);

  if(data == FM_Reload)    return(30);
  if(data == FM_Recharge)  return(1);
//  if(data == FM_Condition) return(!GetUpgrade(KLAS));

  if(data == FM_Damage)    return(30);

  return(Default(data));
}

public func Fire1()    // Projektilschuss
{ 
  if(!FindContents(GONZ))
  {
   return 0;
  }
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
  Sound("staff_weapon",0,ammo);
  Reload();
}

public func ContextMenu(object pCaller)
{
  [$Menu$|Image=STBW]
  Menu(pCaller);
}

public func HasCell()
{
  if(FindContents(GONZ))
  {
   return 1;
  }
  else
  {
   return 0;
  }
}

public func Reload()
{
  if(!FindContents(GONZ))
  {
   return 0;
  }
  return _inherited();
}

public func Menu(object pCaller)
{
  CreateMenu(STBW,pCaller,this(),0,"Stabwaffe",0,1);
  if(FindContents(GONZ))
  {
   AddMenuItem("Zelle ausbauen","PutTake",GONZ,pCaller);
  }
  else
  {
   AddMenuItem("Zelle einbauen","PutTake",GONZ,pCaller);
  }
  return 1;
}

public func PutTake()
{
  Sound("Connect");
  if(FindContents(GONZ))
  {
   FindContents(GONZ)->Enter(Contained());
   if(IsReloading()) RemoveEffect("Reload", this());
   if(IsRecharging()) RemoveEffect("Recharge", this());
   var ammoid = GetFMData(FM_AmmoID);
   var ammoamount = GetAmmo(ammoid, this());
   DoAmmo(ammoid, -ammoamount, this());
  }
  else
  {
   if(!FindContents(GONZ,Contained()))
   {
    Message("Keine Zelle für den Einbau vorhanden!",this());
    return 1;
   }
   else
   {
    FindContents(GONZ,Contained())->Enter(this());
   }
  }
  return 1;
}

func IsGoauldWeapon() { return(true); }
func AlchemProcessTime() { return(800); }
local Name = "$Name$";
local Collectible = 1;
