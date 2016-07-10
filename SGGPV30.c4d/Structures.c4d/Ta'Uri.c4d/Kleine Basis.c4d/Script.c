/*-- Basis --*/

#strict

#include DOOR
#include BAS8

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

func Damage()
{
  if(GetDamage() >= 100)
  {
   Explode(50);
  }
  return(1);
}