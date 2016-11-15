//*-- Der Ringtransporter --*//
  //*--   AUSSENBORD   --*//



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

  if(GetDir(target) == 1)
  {
   SetPosition(GetX(target) -20,GetY(target)+65);
  }
  
  if(GetDir(target) == 0)
  {
   SetPosition(GetX(target) +20,GetY(target)+65);
  }
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
  target -> ContainedUpDouble();
  down = 1;
  phas = GetPhase();
  SetSolidMask(phas*100,200,100,100);
  return(1);
}
  
public func SolidLight()
{
  target -> ContainedUpDouble();
  SetSolidMask(0,300,100,100);
  return(1);
}

public func SolidDown()
{
  target -> ContainedUpDouble();
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
  target -> ContainedUpDouble();
  pX = GetX(target);
  pY = GetY(target);
  return(1);
}

public func Teltak()
{
	return(1);
}
local ActMap = {
Fake = {
Prototype = Action,
Name = "Fake",
Length = 16,
Delay = 3,
X = 0,
Y = 0,
Wdt = 100,
Hgt = 100,
NextAction = "Fake2",
PhaseCall = "SolidUp",
StartCall = "Vorb",
},
Fake2 = {
Prototype = Action,
Name = "Fake2",
Length = 18,
Delay = 3,
X = 0,
Y = 100,
Wdt = 100,
Hgt = 100,
NextAction = "Fake3",
StartCall = "SolidLight",
},
Fake3 = {
Prototype = Action,
Name = "Fake3",
Length = 16,
Delay = 3,
Reverse = 1,
X = 0,
Y = 0,
Wdt = 100,
Hgt = 100,
PhaseCall = "SolidDown",
EndCall = "Off",
},  };
local Name = "$Name$";
