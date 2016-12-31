#strict 2
#appendto TREE

static TREE_AutoChop;

global func NoAutoTreeChop() { return !TREE_AutoChop; }

func Construction()
{
	if(!NoAutoTreeChop() && FindObject2(Find_AtPoint(), Find_OCF(OCF_Exclusive)))
	{
		return RemoveObject();
	}
	AddEffect("CheckStructure", this, 100, 10, this);
	return _inherited(...);
}

func FxCheckStructureTimer()
{
	if(IsStanding())
	{
		if(!(GetOCF() & OCF_Chop) && !NoAutoTreeChop())
		{
			ChopDown();
		}
	}
	else
	{
		return FX_Execute_Kill;
	}
}
