protected func Initialize()
{
	if(GetActionTarget())	SetOwner(GetActionTarget()->GetOwner());	
}

/*public func & GetEnergy()
{
	if(GetActionTarget())	return GetActionTarget()->LocalN("energy");
}*/

public func OnDmg(int iDmg, int iType)
{
	if(iType == DMG_Explosion) return 30;
	return 100;
}

protected func Damage(int iChange)
{
}

protected func CatchBlow(int iLevel, object pBy)
{
	var ID = pBy->GetID();
	
	if(ID == PUDD || ID == METO || ID == REDR)
		GetActionTarget().energy -= 5;
	
	else if(pBy->~MaxTime() && pBy->~Acceleration() && pBy->~IsMachine() && pBy->~IsBulletTarget())
		GetActionTarget().energy -= 10;
}
local ActMap = {
Field = {
Prototype = Action,
Name = "Field",
Procedure = DFA_ATTACH,
FacetBase = 1,
},  };
local Name = "$Name$";
