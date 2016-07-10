/*-- Wraith Granate --*/

#strict

local Active;

public func Activate()
{
  if(GetAction(Contained()) eq "Lie")
  {
   return(1);
  }

  if(Active == 1)
  {
   Contained()->SetAction("Throw");
   Exit(this(), GetDir(Contained())*12-6, 0, 0, GetDir(Contained())*6-3, -3, GetDir(Contained())*60-30);
   return(1);
  }

  CreateMenu(GetID(),Par(),0,0,"Zünder einstellen",0,1);
  AddMenuItem("Sekunde","One",SNB1,Par(),0,0);
  AddMenuItem("Sekunden","Two",SNB2,Par(),0,0);
  AddMenuItem("Sekunden","Three",SNB3,Par(),0,0);
  AddMenuItem("Sekunden","Four",SNB4,Par(),0,0);
  AddMenuItem("Sekunden","Five",SNB5,Par(),0,0);
  return(1);
}

protected func One()
{
  SetAction("One");
  Sound("WRReady");
  Active = 1;
  SetPicture(61,0,55,60);
  return(1);
}

protected func Two()
{
  SetAction("Two");
  Sound("WRReady");
  Active = 1;
  SetPicture(61,0,55,60);
  return(1);
}
  

protected func Three()
{
  SetAction("Three");
  Sound("WRReady");
  Active = 1;
  SetPicture(61,0,55,60);
  return(1);
}

protected func Four()
{
  SetAction("Four");
  Sound("WRReady");
  Active = 1;
  SetPicture(61,0,55,60);
  return(1);
}

protected func Five()
{
  SetAction("Five");
  Sound("WRReady");
  Active = 1;
  SetPicture(61,0,55,60);
  return(1);
}

protected func Exploden()
{
  Explode(50);
  Explode(50);
  return(1);
}

protected func Hit()
{
  Sound("GRHit*");
  return(1);
}

func IsGrenade() { return(0); }
public func IsReloading() {return(0);}
