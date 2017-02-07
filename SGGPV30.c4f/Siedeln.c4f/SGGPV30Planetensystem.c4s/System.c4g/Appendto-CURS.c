#strict 2
#appendto CURS

public func Timer()
{
	if(GetMaterial() == Material("Vehicle") && !FindObject2(this->Find_AtPoint(), Find_Exclude(this)))
	{
		SetXDir(-GetXDir());
		SetYDir(-GetYDir());
	}
	return _inherited(...);
}