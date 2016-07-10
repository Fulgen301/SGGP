#strict

public func Initialize()
{
  SetEntrance(1);
  SetAction("Full");
  return(1);
}

public func Time()
{
  if(FindObject(EPOD,-10,-10,10,10))
  {
   RemoveObject(FindObject(EPOD,-10,-10,10,10));
   SetAction("Full");
   Sound("Connect");
  }
  return(1);
}

public func ControlDigDouble()
{
 if(GetAction() eq "Empty")
 {
  if(GetWealth(GetOwner()) < 25 )
  {
   Message("Nicht genug geld!|Dir fehlen noch %v $",this(),50-GetWealth(GetOwner(this())));
   Sound("Error");
   return(1);
  }

  if(GetWealth(GetOwner()) >= 25 )
  {
   SetAction("Full");
   SetWealth(GetOwner(),GetWealth(GetOwner())-25);
   Sound("Cash");
   return(1);
  }
 }
 return(1);
}

public func ContainedDig()
{
  SetAction("Eject");
  return(1);
}

public func ControlRightDouble()
{
  SetAction("Eject");
  return(1);
}

public func Ejected()
{
  CreateObject(EPOD,0,50)->SetAction("Flight");
  while(FindObject(0,0,0,0,0,0,0,0,this()))
  {
   FindObject(0,0,0,0,0,0,0,0,this())->Enter(FindObject(EPOD));
   return(1);
  }
  return(1);
}

public func Empty()
{
  SetEntrance(0);
  return(1);
}

public func Full()
{
  SetEntrance(1);
  return(1);
}

public func Teltak()
{
	return(1);
}
