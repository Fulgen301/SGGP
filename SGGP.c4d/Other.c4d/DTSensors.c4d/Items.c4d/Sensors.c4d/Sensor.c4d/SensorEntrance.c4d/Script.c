#strict 2

local target;

func Initialize()
{
	SetVisibility(VIS_None);
}

func Attach(object obj)
{
	target = obj;
	SetAction("Attach", target);
	AddEffect("AttachCheck", target, 1, 0, this);
	SetName(GetName(obj));
	SetGraphics(0, this, GetID(target), GFX_Overlay, GFXOV_MODE_Picture);
	return this;
}

func FxAttachCheckStop()
{
	return RemoveObject();
}

func ActivateEntrance(object caller)
{
	FinishCommand(caller, true);
	target->Call(target->EntranceCallback(), caller, ...);
	return 1;
}

func HiddenEntrance() { return true; }
func SensorIgnored() { return true; }
