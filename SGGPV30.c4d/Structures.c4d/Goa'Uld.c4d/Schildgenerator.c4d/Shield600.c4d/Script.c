/* Schutzschild */

#strict 2

protected func Construction()
{
	SetSolidMask(0,0,GetDefWidth(GetID()), GetDefHeight(GetID()));
}

protected func OnDmg(int iDmg, int iType)
{
	if(iType != DMG_Explosion)
	{
		return 100;
	}
	return 75;
}

protected func Damage(int iDamage)
{
	GetEnergy() -= Min(iDamage/10, 50);
}

public func & GetEnergy()
{
	if(GetActionTarget()) return GetActionTarget()->LocalN("energy");
}

protected func LightningStrike()
{
	GetEnergy() += 10;
}

public func IsShield() { return true; }
public func GetRace() { return SG_All; }