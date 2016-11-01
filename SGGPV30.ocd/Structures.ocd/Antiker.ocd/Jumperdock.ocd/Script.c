/*-- Atlantis Door --*/

#strict

local jumper;

func Initialize() 
{
  SetAction("Wait");
  return(1);
}

func Ready()
{
  if(jumper)
  {
   return(0);
  }
  else
  {
   return(1);
  }
}

func Check()
{
  if(jumper)
  {
   if(GetDir() != GetDir(jumper))
   {
    jumper->SetAction("Turn");
    jumper->SetDir(GetDir());
   }
   jumper->SetXDir();
   jumper->SetYDir();
   
   if(GetDir())
   {
    if(GetX(jumper) > GetX()+32)
    {
     jumper->SetPosition(GetX(jumper)-1,GetY(jumper));
    }
    if(GetX(jumper) < GetX()+32)
    {
     jumper->SetPosition(GetX(jumper)+1,GetY(jumper));
    }
    
    if(GetY(jumper) > GetY())
    {
     jumper->SetPosition(GetX(jumper),GetY(jumper)-1);
    }
    if(GetY(jumper) < GetY())
    {
     jumper->SetPosition(GetX(jumper),GetY(jumper)+1);
    }
   }
   else
   {
    if(GetX(jumper) > GetX()-32)
    {
     jumper->SetPosition(GetX(jumper)-1,GetY(jumper));
    }
    if(GetX(jumper) < GetX()-32)
    {
     jumper->SetPosition(GetX(jumper)+1,GetY(jumper));
    }
    
    if(GetY(jumper) > GetY())
    {
     jumper->SetPosition(GetX(jumper),GetY(jumper)-1);
    }
    if(GetY(jumper) < GetY())
    {
     jumper->SetPosition(GetX(jumper),GetY(jumper)+1);
    }
   }
   jumper->SetYDir();
   jumper->SetAction("Stand");
   jumper->SetDir(GetDir());
   LocalN("open",jumper) = 1;
  }
  return(1);
}

func Dock(jmp)
{
  jumper = jmp;
  Sound("Connect");
  return(1);
}

func Undock()
{
  if(!jumper)
  {
   return(1);
  }
  LocalN("open",jumper) = 0;
  jumper->SetAction("Fly");
  jumper->SetPosition(GetX(jumper) - 1, GetY(jumper));
  jumper = 0;
  return(1);
}
local ActMap = {

Wait = {

Prototype = Action,

Name = "Wait",

Delay = 1,

X = 0,

Y = 0,

Wdt = 35,

Hgt = 35,

FlipDir = 1,

Directions = 2,

NextAction = "Wait",

},  };
local Name = "$Name$";
