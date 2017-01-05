/*-- Basis --*/

#strict 2

#include DOOR
#include BA15

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

func Damage()
{
  if(GetDamage() >= 200)
  {
   Explode(70);
  }
  return(1);
}

public func GetRace() { return SG1_StargateCenter; }