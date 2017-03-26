/*-- Basis --*/

#strict

#include DOOR
//#include BA15

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

func Damage()
{
  if(GetDamage() >= 250)
  {
   Explode(80);
  }
  return(1);
}

public func GetRace() { return SGA_Wraith; }