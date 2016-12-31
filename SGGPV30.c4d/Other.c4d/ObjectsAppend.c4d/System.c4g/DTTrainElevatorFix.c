#strict 2
#appendto ELEC

func SetActionTargets(target1, target2, obj)
{
	if(GetID(obj) == STMG)
	{
		return 0;
	}
	return _inherited(target1, target2, obj, ...);
}
