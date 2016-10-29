/*-- Gebäude sind mit dem Punktesystem kompatibel --*/

#strict 2

#appendto *

protected func Completion()
{
	_inherited(...);
	if((GetCategory(this) & C4D_Structure) && !this->~IsRepli())
	{
		DoPoints(this->GetOwner(), 10, SGGP_SettlePoints);
	}
	return true;
}