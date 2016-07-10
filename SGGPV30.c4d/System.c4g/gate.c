/*-- Stargate-Funktionen --*/

#strict 2

global func CreateGate(id ramp,id type,int x,int y,int owner,string name)
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
	if(name)
	{
		gate->ReName(name);
	}	
	return(gate);
}
