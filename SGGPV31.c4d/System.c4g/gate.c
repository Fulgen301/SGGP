/*-- Stargate-Funktionen --*/

#strict 2

global func CreateGate(id ramp,id type,int x,int y,int owner, aChevrons) // array aChevrons
{
	var gate;
	if(ramp)
	{
		gate = CreateObject(ramp,x,y,owner);
		gate->PlaceGate(type);
	}
	else
	{
		gate = CreateObject(type, x, y, owner);
	}
	if(aChevrons && GetType(aChevrons) == C4V_Array)
	{
		if(gate->~IsStargate()) gate->GetChevrons() = aChevrons;
		else if(gate->~IsStargateRamp()) gate->LocalN("target")->GetChevrons() = aChevrons;
	}
	return(gate);
}
