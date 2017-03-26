#strict 2
#appendto CURS

public func Timer()
{
	if(this->LocalN("pBeamer") && this->LocalN("pBeamer")->GetID() == ASTE && GetMaterial() == Material("Vehicle") && !FindObject2(this->Find_AtPoint(), Find_Exclude(this)))
	{
		SetXDir(-GetXDir());
		SetYDir(-GetYDir());
	}
	return _inherited(...);
}