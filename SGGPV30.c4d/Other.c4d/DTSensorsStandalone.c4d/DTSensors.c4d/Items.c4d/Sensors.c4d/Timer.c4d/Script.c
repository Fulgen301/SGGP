#strict 2
#include SN7I

local interval, timer, setupUser, repeats, repeatCount;

func Init()
{
	interval = 35;
}

func ControlThrow(object caller)
{
	Toggle();
	return ClearCom(caller);
}

func ControlThrowDouble() { return ControlThrow(...); }

func Triggers() { return [["$Timeout$"]];}

func Setup(object caller, int &menuIndex)
{
	setupUser = caller;
	AddMenuItem(Format("$Interval$", interval), "SetTimerEntry", GetID(), caller, 0, menuIndex++, 0, C4MN_Add_ForceNoDesc);
	AddMenuItem(Format("$Repeats$", (repeats && Format("%d", repeats)) || "$InfRepeats$"), "SetRepeatsEntry", GetID(), caller, 0, menuIndex++, 0, C4MN_Add_ForceNoDesc);
	AddMenuItem((!timer && "$Start$") || "$Stop$", "ToggleActive", GetID(), caller, 0, menuIndex++, 0, C4MN_Add_ForceNoDesc);
	AddMenuItem("$Test$", "Timeout", GetID(), caller, 0, menuIndex++, 0, C4MN_Add_ForceNoDesc);
	return true;
}

func SetTimerEntry(id id, int menuIndex, bool right)
{
	interval = Max(1, interval - (right * 2 - 1));
	_Setup(setupUser);
	SelectMenuItem(menuIndex, setupUser);
	if(timer)
	{
		RemoveTimer(timer);
		timer = 0;
		timer = AddTimer("Timeout", interval);
	}
}

func SetRepeatsEntry(id id, int menuIndex, bool right)
{
	repeats = Max(0, repeats - (right * 2 - 1));
	_Setup(setupUser);
	SelectMenuItem(menuIndex, setupUser);
}

func ToggleActive(id id, int menuIndex, bool right)
{
	Toggle();
	_Setup(setupUser);
	SelectMenuItem(menuIndex, setupUser);
}

func Toggle()
{
	if(timer)
	{
		Stop();
	}
	else
	{
		Start();
	}
}

func Stop()
{
	if(timer)
	{
		RemoveTimer(timer);
		timer = 0;
		SetAction("Idle");
	}
}

func Start()
{
	if(!timer)
	{
		timer = AddTimer("Timeout", interval);
		SetAction("On");
		repeatCount = 0;
	}
}

func Timeout(sym, int menuIndex)
{
	Trigger(0, this);
	if(GetType(sym) == C4V_C4ID)
	{
		_Setup(setupUser);
		SelectMenuItem(menuIndex, setupUser);
	}
	else if(!sym && repeats && ++repeatCount >= repeats)
	{
		Stop();
	}
}

func SingleShot()
{
	ScheduleCall(this, "Timeout", interval);
}

func SensorCallbacks()
{
	return [["$SingleShot$", "SingleShot"], ["$Start$", "Start"], ["$Stop$", "Stop"]];
}
