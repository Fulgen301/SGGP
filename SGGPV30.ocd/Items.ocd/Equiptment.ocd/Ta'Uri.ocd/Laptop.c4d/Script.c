/*-- Naquadah Generator --*/

#strict

local active;
local user;
local gen;
local instgen;
local instgenpatch;
local insthack;
local instdial;

public func Initialize() 
{
  SetPicture(100,10,100,100);
  active = 0;			//Der Laptop wird Ausgeschaltet geliefert!
  instgen = 1;			//Die Software: Generatorkalibrierung, ist von hausaus drauf!
  instgenpatch = 1;		//Ein patch zum Ausschalten der Bedienung des Reaktors!
  insthack = 1;			//Ein patch um Passwörter zu hacken!
  instdial = 1;			//Ein patch um ein Stargate anwählen zu können!
  return(1);
}


public func EMPShock()
{
  if(active)
  {
   DoDamage(100);
   return(1);
  }

  EMPShockEffect(100);
  return(1);
}

private func Damage()
{
  if(GetDamage(this()) >= 50)
  {
   Explode(10);
  }
  return(1);
}

private func Hit()
{
  DoDamage(5);
  Sound("RockHit*");
  return(1);
}

public func Activate()
{
  user = Par(0);

  CreateMenu(GetID(this()),user,0,0,0,0,1);
  if(active == 1)
  {
   AddMenuItem("Laptop ausschalten","Off",TALP,user,0,Par(0));
  }

  if(active == 0)
  {
   AddMenuItem("Laptop einschalten","On",TALP,user,0,Par(0));
  }


  if(active == 1)
  {
   if(instgen == 1)
   {
    if(FindObject(TANG,-20,-20,40,40))
    {
     AddMenuItem("Naquadah Generator","Gen",TANG,user,0,Par(0));
    }
   }
   
   if(insthack)
   {
    if(FindObject(STWA,-15,-15,30,30))
    {
     AddMenuItem("Passwort zurücksetzen","Hack",STWA,user,0,Par(0));
    }
   }
   
   if(instdial)
   {
    if(FindObject2(Find_Func("IsStargate"),Find_Distance(200),Sort_Distance()))
    {
     AddMenuItem("Gate anwählen","Dial",STWA,user,0,Par(0));
    }
   }
   return(1);
  }
  return(1);
}

public func Dial()
{
  CallMessageBoard(0, false, "Namen des anzuwählenden Gates hier eingeben:", GetOwner(Contained()));
  Sound("BipBipBip");
  return(1);
}

func InputCallback(string gatename)
{
  if(!FindObject2(Find_Func("IsStargate"),Find_Distance(200),Sort_Distance()))
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
   return(1);
  }
  FindObject2(Find_Func("IsStargate"),Find_Distance(200),Sort_Distance())->Dial(gatename);
  return(1);
}

public func Hack()
{
  if(!FindObject(STWA,-15,-15,30,30))
  {
   Message("Kein Wahlcomputer in der nähe!",this());
  }
  if(RandomX(-10,10) != 0)
  {
   Message("Hack war erfolglos!|Probieren Sie es erneut!",this());
   return(1);
  }
  LocalN("password",FindObject(STWA,-15,-15,30,30)) = 0;
  Message("Das Passwort des Wahlcomputers wurde zurückgesetzt!",this());
  Sound("Ding");
  return(1);
}

public func On()
{
  SetPicture(0,10,100,100);
  active = 1;
  Sound("Ding");
  return(1);
}

public func Off()
{
  SetPicture(100,10,100,100);
  active = 0;
  Sound("Ding");
  return(1);
}

public func Gen()
{
  if(!FindObject(TANG,-20,-20,40,40))
  {
   Message("Kein Generator in der nähe!",this());
   return(1);
  }

  if(FindObject(TANG,-20,-20,40,40))
  {
   CreateMenu(TANG,user,0,0,0,0,1);
   AddMenuItem("Energieausstoß","GenE",TANG,user,0,Par(1));
   AddMenuItem("Anzeigetext","GenI",TANG,user,0,Par(1));

   if(instgenpatch == 1)
   {
    AddMenuItem("Generator sperren/entsperren","GenA",TANG,user,0,Par(1));
   }
   return(1);
  }
}

public func GenI()
{
  if(!FindObject(TANG,-20,-20,40,40))
  {
   Message("Kein Generator in der nähe!",this());
   return(1);
  }

  FindObject(TANG,-20,-20,40,40)->InfoSwitch();
  return(1);
}

public func GenA()
{
  if(!FindObject(TANG,-20,-20,40,40))
  {
   Message("Kein Generator in der nähe!",this());
   return(1);
  }

  FindObject(TANG,-15,-15,30,30)->Call("Key");
  return(1);
}


public func GenE()
{
  if(!FindObject(TANG,-15,-15,30,30))
  {
   Message("Kein Generator in der nähe!",this());
   return(1);
  }

  if(FindObject(TANG,-15,-15,30,30))
  {
   CreateMenu(TANG,user,0,0,0,0,1);
   AddMenuItem("Setzen","GenES",SNB1,Par(1),0,1);
   AddMenuItem("Setzen","GenES",SNB2,Par(1),0,2);
   AddMenuItem("Setzen","GenES",SNB3,Par(1),0,3);
   AddMenuItem("Setzen","GenES",SNB4,Par(1),0,4);
   AddMenuItem("Setzen","GenES",SNB5,Par(1),0,5);
   AddMenuItem("Setzen","GenES",SNB6,Par(1),0,6);
   AddMenuItem("Setzen","GenES",SNB7,Par(1),0,7);
   AddMenuItem("Setzen","GenES",SNB8,Par(1),0,8);
   AddMenuItem("Setzen","GenES",SNB9,Par(1),0,9);
   return(1);
  }
}

public func GenES()
{
  if(!FindObject(TANG,-15,-15,30,30))
  {
   Message("Kein Generator in der nähe!",this());
   return(1);
  }
  gen = Par(1);
  ObjectCall(FindObject(TANG,-15,-15,30,30),"SetProduce");
  return(1);
}

func IsMachine()		{ return(1); }	
func IsBulletTarget()		{ return(1); }	
