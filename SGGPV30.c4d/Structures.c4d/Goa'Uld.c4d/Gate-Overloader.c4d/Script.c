/*-- Gate-Overloader --*/

#strict

#include BAS9

local on;
local time;
local target;
local pUser;
local info;
local eft;

func Initialize()
{
  return(1);
}

func Damage()
{
  if(GetDamage() > 50)
  {
   Explode(100);
  }
  return(1);
}

func ControlDigDouble(pCaller)
{
  pUser = pCaller;
  CreateMenu(GOGO, pUser, 0, 0, "Overloader-Kontrolle", 0, 1);
  AddMenuItem("Info An-/Ab-schalten","Info",MEPU,pUser);
  AddMenuItem("Stargate suchen","SearchGate",MEPU,pUser);
  if(on)
  {
   AddMenuItem("Abschalten","Off",MEPU,pUser);
  }
  else
  {
   if(target)
   {
    if(TargetGate())
    {
     if(GetAction(target) eq "Outgoing3")
     {
      AddMenuItem("Overload Starten","On",MEPU,pUser);
     }
     if(GetAction(target) eq "Outgoing4")
     {
      AddMenuItem("Overload Starten","On",MEPU,pUser);
     }
    }
   }
  }
  return(1);
}

func Off()
{
  on = 0;
  return(1);
}

func On()
{
  on = 1;
  return(1);
}

func Info()
{
  if(info)
  {
   info = 0;
   Message("Info ist:<c ff0000>AUS</c>",this());
  }
  else
  {
   info = 1;
   Message("Info ist:<c 00ff00>AN</c>",this());
  }
  Sound("Ding");
  return(1);
}

func SearchGate()
{
  if(target = FindObject2(Find_Func("IsStargate"),Find_InRect(-50,-100,750,200)))
  {
   Message("<c 00ff00>Gate gefunden:</c>|<c 0000ff>%v</c>",this(),LocalN("Name",target));
   Sound("BipBipBip");
  }
  else
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
  }
  return(1);
}


func Check()
{
  if(on)
  {
   if(target)
   {
    if(TargetGate())
    {
     GateEffekt();
     LocalN("time",TargetGate()) = 2;
     LocalN("time",target) = 2;
     if(CanOverloadFast())
     {
      LocalN("heat",TargetGate()) += 20;
     }
     else
     {
      LocalN("heat",TargetGate()) += 5;
     }
    }
    else
    {
     on = 0;
    }
   }
   else
   {
    on = 0;
   }
  }

  if(info)
  {
   if(target)
   {
    Message("Anvisiert:|<c 00ff00>%v</c>|---|Restzeit:|<c 00ff00>%v</c>|---|Zielgate:|<c 00ff00>%v</c>",this(),LocalN("Name",target),RestTime(),LocalN("Name",TargetGate()));
   }
   else
   {
    Message("Kein anvisiertes Gate!",this());
   }
  }
  return(1);
}  

func GateEffekt()
{
  var x = 10;
  var y = -23;
  eft ++;
  if(eft == 10)
  {
   DrawParticleLine("MSpark",x,y,(GetX(target)-GetX())+72,(GetY(target)-GetY())+9,10,50,RGBa(255,150,0,50), RGBa(255,150,0,100), -10);
  }
  if(eft == 20)
  {
   DrawParticleLine("MSpark",x,y,(GetX(target)-GetX())+92,(GetY(target)-GetY())+11,10,50,RGBa(255,150,0,50), RGBa(255,150,0,100), -10);
  }
  if(eft == 30)
  {
   DrawParticleLine("MSpark",x,y,(GetX(target)-GetX())+105,(GetY(target)-GetY())+34,10,50,RGBa(255,150,0,50), RGBa(255,150,0,100), -10);
  }
  if(eft == 40)
  {
   DrawParticleLine("MSpark",x,y,(GetX(target)-GetX())+100,(GetY(target)-GetY())+62,10,50,RGBa(255,150,0,50), RGBa(255,150,0,100), -10);
  }
  if(eft == 50)
  {
   DrawParticleLine("MSpark",x,y,(GetX(target)-GetX())+53,(GetY(target)-GetY())+57,10,50,RGBa(255,150,0,50), RGBa(255,150,0,100), -10);
  }
  if(eft == 60)
  {
   DrawParticleLine("MSpark",x,y,(GetX(target)-GetX())+50,(GetY(target)-GetY())+40,10,50,RGBa(255,150,0,50), RGBa(255,150,0,100), -10);
  }
  if(eft == 70)
  {
   DrawParticleLine("MSpark",x,y,(GetX(target)-GetX())+55,(GetY(target)-GetY())+20,10,50,RGBa(255,150,0,50), RGBa(255,150,0,100), -10);
  }
  
  if(eft == 70)
  {
   eft = 10;
  }
  return(1);
}

func RestTime()
{
  if(target)
  {
   return(255-((LocalN("heat",TargetGate()))/1000));
  }
  return(1);
}

func TargetGate()
{
  if(!target)
  {
   return(0);
  }
  return(LocalN("pTo",target));
}

func CanOverloadFast()
{
  if(target)
  {
   if(TargetGate())
   {
    if(TargetGate()->pToClose())
    {
     return(0);
    }
    else
    {
     return(1);
    }
   }
  }
  return();
}

func GateReady()
{
  if(!target)
  {
   return();
  }
  if(target->IsClose())
  {
   return();
  }
  if((target->GetState()) == 1)
  {
   return(1);
  }
  return();
}

func IsAntiker()
{
	return(1);
}
