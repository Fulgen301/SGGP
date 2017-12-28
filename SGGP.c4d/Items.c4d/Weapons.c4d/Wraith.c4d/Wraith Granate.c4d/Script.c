/*-- Wraith Granate --*/

#strict 2

local Active;

public func Activate(object obj)
{
  if(GetAction(obj) == "Lie")
  {
   return(1);
  }

  if(Active == 1)
  {
   obj->SetAction("Throw");
   Exit(this, GetDir(obj)*12-6, 0, 0, GetDir(obj)*6-3, -3, GetDir(obj)*60-30);
   return(1);
  }

  CreateMenu(GetID(),obj,0,0,"Zünder einstellen",0,1);
  AddMenuItem("Sekunde","One",SNB1,obj,0,0);
  AddMenuItem("Sekunden","Two",SNB2,obj,0,0);
  AddMenuItem("Sekunden","Three",SNB3,obj,0,0);
  AddMenuItem("Sekunden","Four",SNB4,obj,0,0);
  AddMenuItem("Sekunden","Five",SNB5,obj,0,0);
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

public func GetRace()	{ return SGA_Wraith; }
