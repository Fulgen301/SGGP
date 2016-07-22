/*-- Hyperspace --*/

#strict 2

global func EnterHyperspace(object pObj, int x, int y)
{
	if(!pObj) if(!(pObj = this)) return;
	var hyperspace = CreateObject(HPRS, x, y, pObj->GetOwner());
	pObj->Enter(hyperspace);
	return hyperspace;
}

global func LeaveHyperspace(object pObj, int x, int y)
{
	if(!pObj) if(!(pObj = this)) return;
	Log("TravelInHyperspace::X = %d, TravelInHyperspace::Y = %d", x, y);
	
	var hyperspace = pObj->Contained();
	if(hyperspace->GetID() != HPRS) return;
	assert(Format("%d > 0", x));
	assert(Format("%d > 0", y));
	assert(Format("hyperspace->GetX() == %d", x));
	Exit(pObj);
	return pObj;
}

global func TravelInHyperspace(object pObj, int x, int y, int delay)
{
	Log("TravelInHyperspace::X = %d, TravelInHyperspace::Y = %d", x, y);
	if(!pObj) if(!(pObj = this)) return;
	if(!delay) delay = 50;
	var hyperspace = pObj->EnterHyperspace(0, x, y);
	assert(Format("%d > 0", x));
	assert(Format("%d > 0", y));
	Schedule(Format("LeaveHyperspace(Object(%d), %d, %d)",ObjectNumber(pObj), x, y),delay);
	return pObj;
}