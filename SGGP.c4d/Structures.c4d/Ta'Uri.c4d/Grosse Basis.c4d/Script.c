/*-- Basis --*/

#strict 2

#include DOOR
#include BA15

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

protected func ContainedLeft(pCursor)
{
  pCursor->Exit();
  pCursor->SetPosition(GetX(),GetY()+10);
  return(1);
}

protected func ContextAufstieg(object pClonk)
{
  [Tower betreten|Image=MEPU]
  pClonk->ContainedCall("ContainedLeft", this());
}

func Damage()
{
  if(GetDamage() >= 200)
  {
   Explode(90);
  }
  return(1);
}

public func GetRace() { return SG1_StargateCenter; }