/*-- Hyperspace --*/



global func TravelInHyperspace(object pObj, int x, int y, int delay)
{
	if(!pObj) if(!(pObj = this)) return;
	if(!delay) delay = 50;
	
	var hyperspace = CreateObject(HPRS);
	SetObjectLayer(hyperspace, pObj);
	Schedule(nil, Format("Object(%d)->SetPosition(%d,%d)",pObj->ObjectNumber(), x, y,delay));
	Schedule(nil, Format("SetObjectLayer(0,Object(%d))",pObj->ObjectNumber()),delay);
	RemoveObject(hyperspace);
	return pObj;
}
