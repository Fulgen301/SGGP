/*-- Zero Point Modul --*/



local iEnergie;

func Initialize() 
{
local timer = new timer {
minus = 50,
plus = 50
};
  SetAction("Inactive");
  iEnergie = 1000;
  return(1);
}

func Minus(bool exact)
{
if(exact)
  iEnergie --;
else
{
	timer.minus--;
	if(timer.minus == 0)
	{
		timer.minus = 50;
		iEnergie--;
	}
}
  return(1);
}

func Plus(bool exact)
{
if(exact)
  iEnergie --;
else
{
	timer.plus--;
	if(timer.plus == 0)
	{
		timer.plus = 50;
		iEnergie--;
	}
}
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

  if(GetDamage() >= 100)
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


  if(GetAction() == "Inactive")
  {
   SetPicture(72,0,70,70);
   return(1);
  }
  
  if(GetAction() == "Activen")
  {
   SetPicture(13,0,70,70);
   return(1);
  }

  if(GetAction() == "Depledet")
  {
   SetPicture(148,0,70,70);
   return(1);
  }
}

func Destr()
{
  Sound("Glass");
  CastParticles("SplinterGlass", 15, 35, RandomX(-20,20), -5, 20, 20, RGBa(216,146,0,0), RGBa(216,146,0,0));
  RemoveObject();
  return(1);
}


func Activaten()
{
  if(GetAction() == "Activen")
  {
   SetAction("Inactive");
   Sound("Connect");
   this->Message("ZPM ist inaktiv!");
   return(1);
  }

  if(GetAction() == "Inactive")
  {
   SetAction("Activen");
   Sound("Connect");
   this->Message("ZPM ist aktiv!");
   return(1);
  }

  if(GetAction() == "Depledet")
  {
   this->Message("Das ZPM ist erschöpft!");
   return(1);
  }

  SetAction("Activen");
  Sound("Connect");
  this->Message("ZPM ist aktiv!");
  return(1);
}

func Inactive()
{
  if(GetAction() == "Inactive") 
  return(1);
}

func Activen()
{
  if(GetAction() == "Activen") 
  return(1);
}

func Depledet()
{
  if(GetAction() == "Depledet") 
  return(1);
}


public func IsAnvilProduct() { return(1); }
local Name = "$Name$";
local Collectible = 1;
local ActMap = {

Inactive = {

Prototype = Action,

Name = "Inactive",

Delay = 1,

Length = 1,

X = 0,

Y = 0,

Wdt = 4,

Hgt = 7,

PhaseCall = "Inactive",

NextAction = "Inactive",

},

Activen = {

Prototype = Action,

Name = "Activen",

Delay = 1,

Length = 1,

X = 4,

Y = 0,

Wdt = 4,

Hgt = 7,

PhaseCall = "Activen",

NextAction = "Activen",

EnergyUsage = -1000000,

},

Depledet = {

Prototype = Action,

Name = "Depledet",

Delay = 1,

Length = 1,

X = 8,

Y = 0,

Wdt = 4,

Hgt = 7,

PhaseCall = "Depledet",

NextAction = "Depledet",

},  };
