/*-- Knopf --*/

#strict
#include SN4K

local last_user;

func Initialize()
{
  _inherited();
  AddState("$PRESSED$");
}

private func Timer()
{
	TriggerActions();
}

func Reset()
{
	SetState(state,0,2);//Nicht Gedr�ckt!
}

public func ControlThrow(pClonk)
{
  Trigger(pClonk);
}

public func ActivateEntrance(pObj)
{
  FinishCommand (pObj,true,0); 
  ControlThrow(pObj);
  return(1);
}

public func Trigger(pByObj)
{
	last_user = pByObj;
	SetState(state,0,1);//Knopf wurde gedr�ckt!
	Sound("Grab");
	SetGraphics("Down");
        ScheduleCall(0,"ResetGraphics",20);
	TriggerActions();
	Reset();
}

public func GetAdditionalInfo()
{
	return(last_user);
}

private func ResetGraphics()
{
  SetGraphics();
}
