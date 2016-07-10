/*-- Zero Point Modul --*/

#strict

local iEnergie;

func Initialize() 
{
  SetAction("Inactive");
  iEnergie = 1000;
  return(1);
}

func Minus()
{
  iEnergie --;
  return(1);
}

func Plus()
{
  iEnergie ++;
  return(1);
}

func CalcValue()
{
  return(iEnergie);
}

func Energ()
{
  return(iEnergie/10);
}

func Piccheck()
{
  if(FindObject(ZPMU))
  {
   iEnergie = 1000;
  }

  if(GetDamage(this()) >= 100)
  {
   Call("Destr");
  }

  if(iEnergie <= 0)
  {
   SetAction("Depledet");
  }

  if(iEnergie >= 1000)
  {
   iEnergie = 1000;
  }


  if(GetAction() eq "Inactive")
  {
   SetPicture(72,0,70,70);
   return(1);
  }
  
  if(GetAction() eq "Activen")
  {
   SetPicture(13,0,70,70);
   return(1);
  }

  if(GetAction() eq "Depledet")
  {
   SetPicture(148,0,70,70);
   return(1);
  }
}

func Destr()
{
  Sound("Glass");
  CastParticles("SplinterGlass", 15, 35, RandomX(-20,20), -5, 20, 20, RGBa(216,146,0,0), RGBa(216,146,0,0));
  RemoveObject(this());
  return(1);
}


func Activaten()
{
  if(GetAction() eq "Activen")
  {
   SetAction("Inactive");
   Sound("Connect");
   Message("ZPM ist Inaktiv!",this());
   return(1);
  }

  if(GetAction() eq "Inactive")
  {
   SetAction("Activen");
   Sound("Connect");
   Message("ZPM ist Aktiv!",this());
   return(1);
  }

  if(GetAction(this()) eq "Depledet")
  {
   Message("Das ZPM ist erschöpft!",this());
   return(1);
  }

  SetAction("Activen");
  Sound("Connect");
  Message("ZPM ist Aktiv!",this());
  return(1);
}

func Inactive()
{
  if(GetAction() eq "Inactive") 
  return(1);
}

func Activen()
{
  if(GetAction() eq "Activen") 
  return(1);
}

func Depledet()
{
  if(GetAction(this()) eq "Depledet") 
  return(1);
}


public func IsAnvilProduct() { return(1); }
