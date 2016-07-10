/*-- Basis --*/

#strict

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