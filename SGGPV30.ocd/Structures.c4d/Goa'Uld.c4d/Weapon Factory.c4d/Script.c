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
