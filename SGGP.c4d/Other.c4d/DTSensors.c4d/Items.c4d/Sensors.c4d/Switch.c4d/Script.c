#strict 2
#include BS7I

local state;

func Triggers() { return [["$On$"], ["$Off$"]]; }

func ControlThrow(object caller)
{
	state = !state;
	SetAction(["Idle", "On"][state]);
	Sound("Grab");
	TriggerState(caller);
}

func TriggerState(object caller)
{
	Trigger(!state, caller);
}

func SensorCallbacks() { return [["$Switch$", "ControlThrow"], ["$Retrigger$", "TriggerState"]]; }
