
#include Library_Structure
#include Library_Ownable
#include Library_PowerProducer
#include Library_Flag

local DefaultFlagRadius = 200;
static const ZPMConsole_produced_power = 120;

protected func Initialize()
{
	AddTimer("Check", 1);
	return _inherited(...);
}

public func IsHammerBuildable() { return true; }

public func IsContainer() { return true; }

protected func RejectCollect(id idObj, object pObj)
{
	return pObj->GetID() != ZPM && ContentsCount(ZPM) < 3;
}

protected func Check()
{
	if(IsWorking()) return;
	var zpm;
	if(zpm = GetFirstActiveZPM())
	{
		RegisterPowerProduction(ZPMConsole_produced_power);
	}
	else UnregisterPowerProduction();
}

public func GetFirstActiveZPM()
{
	for(var i = 0; Contents(i); i++)
	{
		if(Contents(i) && Contents(i)->GetAction() != "Depledet")
		{
			return Contents(i);
		}
	}
}

// Produces power on demand, so not steady.
public func IsSteadyPowerProducer() { return false; }

// Low priority so that other sources of power are drained before burning fuel.
public func GetProducerPriority() { return 0; }

public func OnPowerProductionStart(int amount)
{
	if(!IsWorking())
		CreateEffect(IntZPM, 1, 200);
	
	return true;
}

public func OnPowerProductionStop()
{
	RemoveEffect("IntZPM", this);
	return true;
}

public func IsWorking() 	{ return !!GetEffect("IntZPM", this); }

local Name = "$Name$";
local IntZPM = new Effect {
	Timer = func(int time) {
		this.zpm = this.Target->GetFirstActiveZPM();
		if(!this.zpm)
		{
			return -1;
		}
		this.zpm->SetAction("Activen");
		this.zpm->Minus();
	},
	
	Stop = func(int iReason, bool fTemp) {
		if(fTemp) return;
		
		if(this.Target) this.Target->UnregisterPowerProduction();
		if(this.zpm) this.zpm->SetAction("Inactive");
	}
};
