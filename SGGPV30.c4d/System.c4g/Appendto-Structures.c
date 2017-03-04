/*-- Gebäude sind mit dem Punktesystem kompatibel --*/

#strict 2

#appendto *

protected func Completion()
{
	_inherited(...);
	if(this && (GetCategory(this) & C4D_Structure) && !this->~IsRepli() && GetID(this) != SGIR)
	{
		DoPoints(this->GetOwner(), 10, SGGP_SettlePoints);
		if(FindObject2(Find_Distance(200),Find_Func("IsPartOfAtlantis")) && GetALOS(GetOwner()))
		{
			GetALOS(GetOwner())->RegisterStructure(this);
		}
	}
	return true;
}