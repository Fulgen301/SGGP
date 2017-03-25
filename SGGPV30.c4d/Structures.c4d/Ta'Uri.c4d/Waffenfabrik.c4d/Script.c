#strict 2
#include WRKS
func Initialize()
{
	_inherited(...);
	SetAction("Stand");
}

func ControlDigDouble(object pUser)
{
	return MenuProduction(pUser);
}

private func MenuProduction(pCaller)
{
	CreateMenu(GetID(), pCaller, this, 1, "$TxtNoconstructionplans$");
	for(var i = 0, Def; Def = GetPlrKnowledge(GetOwner(pCaller), 0, i, C4D_Object); i++)
	{
		if(Def && ((Def->~GetRace() & SG1_StargateCenter) || (Def->~GetRace() & SG_All)))
		{
			AddMenuItem("$TxtProductions$", "SelectProduction", Def, pCaller, 0, pCaller);
		}
	}
}

func Damage()
{
  if(GetDamage() >= 100)
  {
   Explode(50);
  }
  return(1);
}

public func GetRace() { return SG1_StargateCenter; }