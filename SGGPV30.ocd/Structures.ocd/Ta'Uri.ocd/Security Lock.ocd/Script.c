/*-- Sicherheits Luftschl‰use --*/



local Lock;
local secure;
local open;
local co1;
local co2;

func Initialize() 
{
  open = 1;

  Lock = CreateObject(HNG2);
  Lock -> Open();
 
//  CreateObject(CNS2);
//  co1 = FindObject(CNS2);
//  co1 -> SetPosition(GetX()-35,GetY()+20);
//  co1 -> Set(this());
  
//  CreateObject(CNS2);
//  co2 = FindObject(CNS2);
//  co2 -> SetPosition(GetX()+35,GetY()+20);
//  co2 -> Set(this());
  return(1);
}

func Damage()
{
  if(GetDamage() > 100)
  {
   Explode(30);
   if(co1)
   {
    co1 -> Explode(10);
   }
   if(co2)
   {
    co2 -> Explode(10);
   }
   if(Lock)
   {
    Lock -> Explode(10);
   }
  }
  return(1);
}

func IsOpend()
{
  if(open)
  {
   return(1);
  }
  return();
}

func Check()
{
  if(GetCon() != 100)
  {
   return(1);
  }

  if(secure)
  {
   if(GBackLiquid(0,29))
   {
    if(open)
    {
     Lock->Close();
     open = 0;
     var x;
     for(x in FindObjects(Find_ID(SSLS),Find_Owner(GetOwner())))
     {
      if(LocalN("open",x))
      {
       if(LocalN("secure",x))
       {
        x->Switch();
       }
      }
     }
    }
   }
  }

  Lock -> SetPosition(GetX(),GetY());
  Lock -> SetXDir();
  Lock -> SetYDir();
  return(1);
}

func Switch()
{
  Sound("Connect");
  if(open)
  {
   Lock->Close();
   open = 0;
   return(1);
  }
  Lock->Open();
  open = 1;
  return(1);
}

func Secure()
{
  Sound("Connect");
  if(secure == 0)
  {
   secure = 1;
   Message("<c 0000ff> Autoschluss: </c> <c 00ff00> An </c>",this());
   return(1);
  }
  secure = 0;
  Message("<c 0000ff> Autoschluss: </c> <c ff0000> Aus </c>",this());
  return(1);
}

public func ConsoleControl(int i)
{
  if(i == 1) return("÷ffnen/Schlieﬂen");
  if(i == 2) return("Autoschluss An/Aus");
}

public func ConsoleControlled(int i)
{
  if(i == 1)
  {
   Switch();
   return(1);
  }
  
  if(i == 2)
  {
   Secure();
   return(1);
  }
}

public func IsConsoleTarget()
{
	return(1);
}
local Name = "$Name$";
