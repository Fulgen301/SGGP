#strict 2
#include LS7I

local range;
static LV7I_MaxRange;
local rangeTarget;

func MaxRange()
{
	return LV7I_MaxRange || 200;
}

func SetMaxRange(int range)
{
	if(this)
	{
		DebugLog("WARNING: LV7I->SetMaxRange() sets the maximum available distance for all living sensors.");
		DebugLog("Use this function in definition context only (this also disables this warning).");
	}
	
	LV7I_MaxRange = range;
}

func Init()
{
	range = 50;
	return _inherited(...);
}

func Triggers() { return [["$AnimalTrigger$"], ["$NoAnimalTrigger$"], ["$AlliedTrigger$"], ["$NoAlliedTrigger$"], ["$HostileTrigger$"], ["$NoHostileTrigger$"]]; }

func SetupMenuID() { return LV7I; }

func Setup(object caller, int& menuIndex)
{
	selectCaller = caller;
	AddMenuItem(Format("$Range$", range), "ChangeRange", GetID(), caller, 0, menuIndex++, 0, C4MN_Add_ForceNoDesc);
	if(!GetEffect("IntShowRange", caller))
	{
		AddEffect("IntShowRange", caller, 1, 1, this);
		rangeTarget = caller;
	}
	return true;
}

func ChangeRange(id id, int index, bool right)
{
	range = BoundBy(range - (right * 2 - 1), 1, MaxRange());
	_Setup(selectCaller);
	SelectMenuItem(index, selectCaller);
}

func FxIntShowRangeTimer(object target, int effectNumber)
{
	ClearParticles("PSpark", this);
	if(Contained())
	{
		ClearParticles("PSpark", Contained());
	}
	if(!target || GetMenu(target) != SetupMenuID())
	{
		rangeTarget = 0;
		return FX_Execute_Kill;
	}
	
	var ret = 0;
	var step = BoundBy(500 * MaxRange() / range, 500, 2000);
	var size = 30; //BoundBy((range * 3) / 5, 20, 60);
	for(var r = 0; r < 36000 - step + 1; r += step)
	{
		ret += CreateParticle("PSpark", Cos(r, range, 100), Sin(r, range, 100), 0, 0, size, GetPlrColorDw(GetOwner()), Contained() || this);
	}
}

func AnimalCondition()
{
	return Find_Or(Find_Category(4096), Find_Func("IsAnimal")); // C4D_SelectAnimal is 4096 but is not available as constant
}

func Check(bool retrigger)
{
	if(!rangeTarget)
	{
		ClearParticles("PSpark", this);
	}
	for(var mode in [[0, Find_Or(AnimalCondition(), Find_Owner(NO_OWNER)), RGB(255, 255, 0)], [1, Find_And(Find_Not(Find_Hostile(GetOwner())), Find_Not(AnimalCondition())), RGB(0, 192, 0)], [2, Find_And(Find_Hostile(GetOwner()), Find_Not(AnimalCondition())), RGB(192, 0, 0)]])
	{
		var living = FindObject2(Find_Distance(range), Find_OCF(OCF_Alive), mode[1], Sort_Random());
		TestAndTrigger(mode[0], living, living, mode[2], retrigger);
	}
}

func TestAndTrigger(int type, bool present, object obj, int color, bool retrigger)
{
	present = !!present;
	if(present)
	{
		CreateParticle("PSpark", (type - 1) * 5, 1, 0, 0, 50, color, this);
	}
	if((!!(triggered & (1 << type))) != present || retrigger)
	{
		if(present)
		{
			triggered |= (1 << type);
		}
		else
		{
			triggered &= ~(1 << type);
		}
		return Trigger(2 * type + !present, obj);
	}
}
