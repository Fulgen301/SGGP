/*-- Große Luftschläuse --*/

#strict

local Lock1;
local Lock2;
local empty;
local open1;
local open2;
local co1;
local co2;

func Initialize() 
{
  open1 = 1;
  open2 = 1;

  Lock1 = CreateObject(HNG2);
  Lock2 = CreateObject(HNG2);
  Lock1 -> Open();
  Lock2 -> Open();
  
  //co1 = CreateObject(CNS2);
  //co1 -> SetPosition(GetX()-80,GetY()+20);
  //co1 -> Set(this());
  
  //co2 = CreateObject(CNS2);
  //co2 -> SetPosition(GetX()+80,GetY()+20);
  //co2 -> Set(this());
  return(1);
}

func Damage()
{
  if(GetDamage() > 500)
  {
   Explode(30);
   if(Lock1)
   {
    Lock1->Explode(10);
   }
   if(Lock2)
   {
    Lock2->Explode(10);
   }
   if(co1)
   {
    co1->Explode(10);
   }
   if(co2)
   {
    co2->Explode(10);
   }
  }
  return(1);
}

func Check()
{
  if(GetCon() != 100)
  {
   return(1);
  }

  Lock1 -> SetPosition(GetX()-60,GetY());
  Lock1 -> SetXDir();
  Lock1 -> SetYDir();
  
  Lock2 -> SetPosition(GetX()+60,GetY());
  Lock2 -> SetXDir();
  Lock2 -> SetYDir();
  
  if(empty)
  {
   if(open1)
   {
    empty = 0;
   }
   
   if(open2)
   {
    empty = 0;
   }
   
   if(GBackLiquid(0,29))
   {
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    InsertMaterial(ExtractLiquid(0,29),0,-36);
    Sound("Fusing");
    return(1);
   }
   empty = 0;
  }
  return(1);
}

func Left()
{
  Sound("Connect");
  if(open1)
  {
   Lock1->Close();
   open1 = 0;
   return(1);
  }
  Lock1->Open();
  open1 = 1;
  return(1);
}

func Right()
{
  Sound("Connect");
  if(open2)
  {
   Lock2->Close();
   open2 = 0;
   return(1);
  }
  Lock2->Open();
  open2 = 1;
  return(1);
}

func Empty()
{
  empty = 1;
  Sound("Connect");
  return(1);
}

public func ConsoleControl(int i)
{
  if(i == 1) return("Links");
  if(i == 2) return("Rechts");
  if(i == 3) return("Abpumpen");
}

public func ConsoleControlled(int i)
{
  if(i == 1)
  {
   Left();
   return(1);
  }
  
  if(i == 2)
  {
   Right();
   return(1);
  }
  
  if(i == 3)
  {
   Empty();
   return(1);
  }
}

public func IsConsoleTarget()
{
	return(1);
}
