//*-- Der Ringtransporter --*//
  //*--      NORMAL     --*//

#strict

local ring;
local name;
local put;
local nobase;
local Array1;
local Array2;

//Automatische Namenssetzung des Transporters
public func Initialize()
{
  ScheduleCall(0,"Telset",5);
  name = Format("Transporter %v",ObjectCount(GetID(this())) + 1);
  return(1);
}

public func IsFindable()
{
  if(GetAction() ne "Idle")
  {
   return();
  }
  
  if(name == "Off")
  {
   return();
  }
  else
  {
   return(1);
  }
}

//Neue Namenssetzung im Tel'tak
public func Telset()
{
  if(nobase)
  {
   name = Format("Tel'tak %v",ObjectCount(GetID(this())) + 1);
   return(1);
  }
  return(1);
}

//Zum Bausatz machen
public func MakeCNKT()
{
  if(!nobase)
  {
   ChangeDef(CNKT);
   Sound("Connect");
  }
  return(1);
}

//Steuert die Treffbarkeit
public func IsBulletTarget()
{
  if(!ActIdle())
  {
   return(1);
  }
  return();
}

//Schadenssteuerung
public func Damage()
{
  if(!put)
  {
   if(GetDamage(this()) >= 250)
   {
    put = 1;
    CreateObject(ROCK,-30,-20)->Explode(20);
    CreateObject(ROCK,10,5)->Explode(25);
    CreateObject(ROCK,0,20)->Explode(30);
    Explode(40);
   }
  }
  return(1);
}

//Manuelle Namnessetzung des Transporters
public func SetName(lName)
{
  name = lName;
  Message("<c ff0000> Neuer Name: </c>|<c 0000ff>%v</c>",this(),name);
  return(1);
}

//Überprüft die gültigkeit des Transporters
public func IsValid(target)
{
  if(GetID(target) == RIG3)
  {
   return();
  }

  if(!target)
  {
   return(1);
  }
  
  if(GetID(target) != GetID(this()))
  {
   return(1);
  }
  return();
}

//Start mit Auswahl 
public func Activate(chooser)
{
  if(!ActIdle())
  {
   Sound("rt_error");
   return(1);
  }

  if(IsValid(chooser))
  {
   Sound("rt_error");
   return(1);
  }
  
  ring = chooser;
  ring -> Fake();
  Sound("rt_small",0,0,50);
  SetAction("Up");
  return(1);
}

//Quickstart
public func Quick(choose)
{
  if(!ActIdle())
  {
   Sound("rt_error");
   return(1);
  }

  if(choose)
  {
   Activate(choose);
   return(1);
  }
  
  ring = FindObject(GetID(this()),0,0,-1,-1);
  ring -> Fake();
  Sound("rt_small",0,0,50);
  SetAction("Up");
  return(1);
}

public func Beam()
{ 
  Array1 = FindObjects(Find_InRect(GetX(ring)-25-GetX(),GetY(ring)-15-GetY(),50,35),Find_Not(Find_Category(C4D_Structure()),Find_Category(C4D_StaticBack()),Find_Category(C4D_Parallax()),Find_Category(C4D_Parallax()),Find_Func("IsTree")));
  Array2 = FindObjects(Find_InRect(-25,-15,50,35),Find_Not(Find_Category(C4D_Structure()),Find_Category(C4D_StaticBack()),Find_Category(C4D_Parallax()),Find_Category(C4D_Parallax()),Find_Func("IsTree")));
  var obj;

  for(obj in Array1)
  {
   SetPosition(GetX(obj)+GetX(this())-GetX(ring),GetY(obj)+GetY(this())-GetY(ring),obj);
  }
  
  for(obj in Array2)
  {
   SetPosition(GetX(obj)+GetX(ring)-GetX(this()),GetY(obj)+GetY(ring)-GetY(this()),obj);
  }
  return(1);
}

public func SizeCheck(pObj)
{
  if(GetDefCoreVal("Width",0,GetID(pObj)) > GetDefCoreVal("Height",0,GetID(pObj)))
  {
   if(GetDefCoreVal("Width",0,GetID(pObj)) > 75)
   {
    return(1);
   }
  }
  
  if(GetDefCoreVal("Height",0,GetID(pObj)) > GetDefCoreVal("Width",0,GetID(pObj)))
  {
   if(GetDefCoreVal("Height",0,GetID(pObj)) > 75)
   {
    return(1);
   }
  }
  return(0);
}


public func Fake()
{
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
  phas = GetPhase();
  SetSolidMask(phas*100,200,100,100);
  return(1);
}
  
public func SolidLight()
{
  SetSolidMask(0,300,100,100);
  return(1);
}

public func SolidDown()
{
  var phas;
  var help;
  phas = GetPhase();
  help = 1500 - (phas*100);
  SetSolidMask(help,200,100,100);
  return(1);
}
local ActMap = {

Up = {

Prototype = Action,

Name = "Up",

Length = 16,

Delay = 3,

X = 0,

Y = 0,

Wdt = 100,

Hgt = 100,

NextAction = "Light1",

PhaseCall = "SolidUp",

},

Light1 = {

Prototype = Action,

Name = "Light1",

Length = 9,

Delay = 3,

X = 0,

Y = 100,

Wdt = 100,

Hgt = 100,

NextAction = "Light2",

EndCall = "Beam",

StartCall = "SolidLight",

},

Light2 = {

Prototype = Action,

Name = "Light2",

Length = 9,

Delay = 3,

X = 900,

Y = 100,

Wdt = 100,

Hgt = 100,

NextAction = "Down",

},

Down = {

Prototype = Action,

Name = "Down",

Length = 16,

Delay = 3,

Reverse = 1,

X = 0,

Y = 0,

Wdt = 100,

Hgt = 100,

PhaseCall = "SolidDown",

},

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

},  };
local Name = "$Name$";
