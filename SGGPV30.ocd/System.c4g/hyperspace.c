/*-- Hyperspace --*/

#strict 2

global func TravelInHyperspace(object pObj, int x, int y, int delay)
{
	if(!pObj) if(!(pObj = this)) return;
	if(!delay) delay = 50;
	
	var hyperspace = CreateObject(HPRS);
	SetObjectLayer(hyperspace, pObj);
	Schedule(Format("Object(%d)->SetPosition(%d,%d)",ObjectNumber(pObj), x, y),delay);
	Schedule(Format("SetObjectLayer(0,Object(%d))",ObjectNumber(pObj)),delay);
	RemoveObject(hyperspace);
	return pObj;
}