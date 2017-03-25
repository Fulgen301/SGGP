/*-- Goa'Uld Waffenfabrik --*/

#strict 2

/* Nutzt die Grundfunktionalität der Werkstatt. */

#include WRKS
#include BAS9

private func MenuProduction(pCaller)
{
	CreateMenu(GetID(), pCaller, this, 1, "$TxtNoconstructionplans$");
	for(var i = 0, Def; Def = GetPlrKnowledge(GetOwner(pCaller), 0, i, C4D_Object); i++)
	{
		if(Def && ((Def->~GetRace() & SG1_Goauld) || (Def->~GetRace() & SG_All)))
		{
			AddMenuItem("$TxtProductions$", "SelectProduction", Def, pCaller, 0, pCaller);
		}
	}
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

public func GetRace() { return SG1_Goauld; }