/*-- Stargate-Funktionen --*/

/** Creates a gate at the specific location.
@par ramp The ID of the ramp.
@par type The ID of the gate.
@par x The x coordinate of the location.
@par y The y coordinate of the location.
@par owner The owner of the gate. Shall be -1.
@par name The name of the gate
 */

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
