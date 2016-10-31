/*-- Hoch Explosive Granate --*/

#strict

public func Activate()
{ 
  if(GetAction(Contained()) eq "Lie")
  {
   return(1);
  }

  if(GetAction() eq "Scharf")
  {
   Contained(this())->SetAction("Throw");
   Exit(this(), GetDir(Contained())*12-6, 0, 0, GetDir(Contained())*6-3, -3, GetDir(Contained())*60-30);
   return(1);
  }

  SetAction("Scharf");
  Sound("Pin");
  SetPicture(41,0,35,35);
  return(1);
}

protected func Exploden()
{
  Explode(50);
  Explode(50);
  Explode(30);
  Explode(20);
  if(FindObject(0,-10,-10,20,20,OCF_Alive()))
  {
   FindObject(0,-10,-10,20,20,OCF_Alive())->Kill();
  }
  return(1);
}

protected func Hit()
{
  Sound("GRHit*");
  return(1);
}

func IsGrenade() { return(true); }
public func IsReloading() {return(0);}
public func GetRace()	{ return SG1_StargateCenter; }
local Name = "$Name$";
local Collectible = 1;
