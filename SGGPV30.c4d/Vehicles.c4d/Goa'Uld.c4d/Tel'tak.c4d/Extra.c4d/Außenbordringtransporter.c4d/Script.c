//*-- Der Ringtransporter --*//
  //*--   AUSSENBORD   --*//

#strict 2

local ring;
local put;
local target;
local pX;
local pY;
local down;

//Automatische Namenssetzung des Transporters
public func Initialize()
{
  target = FindObject(TEL_,0,0,-1,-1);
  return(1);
}

public func Check()
{
  SetXDir();
  if(down != 0)
  {
   SetPosition(pX,pY,target);
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

  if(target)
  {
   var offX = 0, offY = 0;
   target->~TransporterPosition(offX, offY, this);
   SetPosition(GetX(target) + offX, GetY(target) + 57 + offY);
  }
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
  target ->~ContainedUpDouble();
  down = 1;
  phas = GetPhase();
  SetSolidMask(phas*100,200,100,100,-25,-33);
  return(1);
}

public func SolidLight()
{
  target ->~ContainedUpDouble();
  SetSolidMask(0,300,100,100,-25,-33);
  return(1);
}

public func SolidDown()
{
  target ->~ContainedUpDouble();
  down = -1;
  var phas;
  var help;
  phas = GetPhase();
  help = 1500 - (phas*100);
  SetSolidMask(help,200,100,100,-25,-33);
  return(1);
}

public func Off()
{
  down = 0;
  SetCategory(C4D_StaticBack);
  return(1);
}

public func Vorb()
{
  target ->~ContainedUpDouble();
  pX = GetX(target);
  pY = GetY(target);
  SetCategory(C4D_Structure);
  return(1);
}
