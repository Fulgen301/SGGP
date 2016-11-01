/*-- Goa'Uld Waffenfabrik --*/

#strict

/* Nutzt die Grundfunktionalität der Werkstatt. */

#include WRKS
#include BAS9

/* Produkteigenschaften (überladen) */
public func ProductType () {return(C4D_Object());}


public func ProductCondition() 
{
  return("IsGoauldWeapon");
}

public func ProductCondition2() 
{
  return("IsAmmoPacket");
}

/* Produktion */

private func MenuProduction(pCaller) 
{
  // Menü erzeugen und mit Bauplänen des Spielers füllen
  CreateMenu(GetID(this()),pCaller,this(),1,"$TxtNoconstructionplans$");
  for(var i=0,idKnowledge; idKnowledge=GetPlrKnowledge(GetOwner(pCaller),0,i,ProductType ()); ++i)
    if (DefinitionCall (idKnowledge, ProductCondition ()))
      AddMenuItem("$TxtProductions$", "SelectProduction", idKnowledge, pCaller, 0, pCaller);
      
  for(var i=0,idKnowledge; idKnowledge=GetPlrKnowledge(GetOwner(pCaller),0,i,ProductType ()); ++i)
    if (DefinitionCall (idKnowledge, ProductCondition2 ()))
      AddMenuItem("$TxtProductions$", "SelectProduction", idKnowledge, pCaller, 0, pCaller);
  return(1);
}

/* Türsteuerung */

private func SoundOpenDoor()
{
  Sound("SteelGate2");
}
  
private func SoundCloseDoor()
{
  Sound("SteelGate2");
}

/* Aktivität */

private func Smoking()
{
  Smoke(+7, -27, 8);
  Smoke(-5, -28, 5 + Random(3));
}

/* Aufnahme */

/* Kontext */

public func ContextConstruction(pCaller) 
{
  [$Production$|Image=GetID(this())|Condition=IsBuilt]
  return(MenuProduction(pCaller));
}
local ActMap = {

OpenDoor = {

Prototype = Action,

Name = "OpenDoor",

Length = 11,

Delay = 2,

X = 0,

Y = 0,

Wdt = 80,

Hgt = 50,

NextAction = "DoorOpen",

StartCall = "SoundOpenDoor",

},

DoorOpen = {

Prototype = Action,

Name = "DoorOpen",

Delay = 20,

X = 800,

Y = 0,

Wdt = 80,

Hgt = 50,

NextAction = "CloseDoor",

StartCall = "OpenEntrance",

EndCall = "CloseEntrance",

},

CloseDoor = {

Prototype = Action,

Name = "CloseDoor",

Length = 11,

Delay = 1,

X = 0,

Y = 0,

Wdt = 80,

Hgt = 50,

NextAction = "Idle",

StartCall = "SoundCloseDoor",

EndCall = "DoorClosed",

Reverse = 1,

},

Build2 = {

Prototype = Action,

Name = "Build2",

Procedure = DFA_NONE,

Length = 21,

Delay = 3,

X = 0,

Y = 50,

Wdt = 80,

Hgt = 50,

PhaseCall = "Smoking",

Sound = "goauldproduce",

NextAction = "Build",

EnergyUsage = 2000,

ObjectDisabled = 1,

},

Build = {

Prototype = Action,

Name = "Build",

Procedure = DFA_BUILD,

Length = 1,

Delay = 10,

FacetBase = 1,

NextAction = "Build2",

},  };
local Name = "$Name$";
