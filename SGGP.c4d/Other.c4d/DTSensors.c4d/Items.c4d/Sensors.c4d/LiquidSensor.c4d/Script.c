#strict 2
#include SN7I

local triggered;

func Init()
{
	AddTimer("Check", 1);
}

func Attach(object caller, object contained)
{
	if(GetID() == LS7I && contained)
	{
		return SetPosition(GetX(), GetY() + 9);
	}
}

func Triggers() { return [["$LiquidTrigger$"], ["$NoLiquidTrigger$"]]; }

func SensorCallbacks() { return [["$Retrigger$", "Retrigger"]]; }

func Check(bool retrigger)
{
	ClearParticles("PSpark", this);
	if(GBackLiquid())
	{
		CreateParticle("PSpark", 0, -1, 0, 0, 50, RGB(0, 192, 0), this);
		if(!triggered || retrigger)
		{
			triggered = true;
			return Trigger(0);
		}
	}
	else if(triggered || retrigger)
	{
		triggered = false;
		return Trigger(1);
	}
}

func Retrigger()
{
	return Check(true);
}
