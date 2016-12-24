//*-- Der Ringtransporter --*//
  //*--   AUSSENBORD   --*//

#strict

local ring;
local put;
local target;
local pX;
local pY;
local down;

//Automatische Namenssetzung des Transporters
public func Initialize()
{
  target = FindObject2(Find_ID(RIG1),Find_Distance(20),Find_Owner(GetOwner()));
  return(1);
}

public func Check()
{
  SetXDir();
  if(down != 0 && target)
  {
   SetPosition(pX,pY);
  }
  
  if(down == 1)
  {
   SetYDir(50);
   return(1);
  }
  
  if(down == -1)
  {
   SetYDir(-200);
   return(1);
  }
  
  if(Teltak() && target)
  {

  if(GetDir(target) == 1)
  {
   SetPosition(GetX(target) -20,GetY(target)+65);
  }
  
  if(GetDir(target) == 0)
  {
   SetPosition(GetX(target) +20,GetY(target)+65);
  }
  }
  else if(target) SetPosition(target->GetX(), target->GetY() + 65);
  return(1);
}

public func Fake()
{
  Schedule("SetPosition(GetX(),GetY()+10)",5);
  Sound("rt_small",0,0,50);
  SetAction("Fake");
  return(1);
}

/*--
+++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++
+++++    Solidmasksteuerung    ++++++
+++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++
--*/

public func SolidUp()
{
  var phas;
  if(phas == 5)
  {
   SetPosition(GetX(),GetY()+10);
  }
  if(Teltak()&& target) target ->~ContainedUpDouble();
  down = 1;
  phas = GetPhase();
  SetSolidMask(phas*100,200,100,100);
  return(1);
}
  
public func SolidLight()
{
  if(Teltak()&& target) target ->~ContainedUpDouble();
  SetSolidMask(0,300,100,100);
  return(1);
}

public func SolidDown()
{
  if(Teltak()&& target) target ->~ContainedUpDouble();
  down = -1;
  var phas;
  var help;
  phas = GetPhase();
  help = 1500 - (phas*100);
  SetSolidMask(help,200,100,100);
  return(1);
}

public func Off()
{
  down = 0;
  return(1);
}

public func Vorb()
{
  if(Teltak()&& target) target -> ContainedUpDouble();
  pX = GetX(target);
  pY = GetY(target);
  return(1);
}

public func Teltak()
{
	if(target) target->~Teltak();
}