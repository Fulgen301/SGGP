/*-- Stargate-Funktionen --*/

#strict 2

global func CreateGate(id ramp,id type,int x,int y,int owner, array aChevrons)
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
	if(aChevrons)
	{
		gate->GetChevrons() = aChevrons;
	}	
	return(gate);
}
