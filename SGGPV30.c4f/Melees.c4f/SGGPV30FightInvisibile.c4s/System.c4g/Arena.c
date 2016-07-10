#strict
#appendto NODR
protected func Timer()
{
	var pObj;
	for(pObj in FindObjects(Find_NoContainer(),Find_Category(C4D_Object))) AddEffect("Arena_Remove", pObj, 1, 500, this());
}

func FxRemoveInvOnDeathStop(target, no, reason) 
{
	if(reason == 4)
    {
    	for(var i = 0 ; Contents(i, target) ; i++)
      	if(Contents(i, target)) Schedule("RemoveObject();", 1, 0, Contents(i, target));
    	for(var pGear in LocalN("aGear", target))
      	if(pGear)
      		{
        		pGear->GearUnbuckle(target);
        		pGear->RemoveObject();
      		}
    }
}
