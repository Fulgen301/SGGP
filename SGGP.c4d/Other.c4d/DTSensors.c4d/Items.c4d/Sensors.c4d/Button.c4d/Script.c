#strict 2
#include SN7I

func Triggers() { return [["$Press$"]];}

func ControlThrow(object caller)
{
	SetAction("Pressed");
	Sound("Grab");
	Trigger(0, caller);
	return ClearCom(caller);
}
func ControlThrowDouble() { return ControlThrow(...); }

func EntranceCallback() { return "ControlThrow"; }

func SensorCallbacks() { return [["$Press$", "ControlThrow"]]; }
