/*-- Tretmine --*/

#strict

public func Activate()
{ 
  if(GetAction() eq "Start")
  {
   return(1);
  }
  
  if(GetAction() eq "Scharf")
  {
   return(1);
  }
  
  
  if(GetDir(Contained()) == 0)
  {
   Exit();
   SetPosition(GetX()+20,GetY());
  }
  
  if(Contained())
  {
  if(GetDir(Contained()) == 1)
  {
   Exit();
   SetPosition(GetX()-20,GetY());
  }
  }
  
  SetAction("Start");
  Sound("Connect");
  return(1);
}

protected func Invis()
{
  SetClrModulation(RGBa(0,0,0,200));
  return(1);
}

protected func Check()
{
  if(GetDamage(this()) >= 5)
  {
   Call("Exploden");
   return(1);
  }

  if(FindObject(0,-15,-15,30,30,OCF_Alive()))
  {
   Call("Exploden");
   return(1);
  }
  return(1);
}

protected func Exploden()
{
  Explode(10);
  Explode(20);
  Explode(30);
  return(1);
}

protected func Hit()
{
  Sound("GRHit*");
  return(1);
}

func IsGrenade() { return(true); }
public func GetRace()	{ return SG1_StargateCenter; }