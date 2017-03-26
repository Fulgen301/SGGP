#strict 2
#appendto CLNK

func ControlCommandAcquire(object target, Tx, int Ty, object target2, id def)
{ // TODO: decide based on distance to AvailableObject/Homebase and Retriever which one to use
	if(!target) // TODO: avoid "stealing"
	{
		var retriever = FindObject2(Find_InRect(-500, -250, 1000, 500), Find_Func("IsRetriever"), Find_Func("CanRetrieveObject", def, false, target2), Find_Exclude(target), Sort_Distance());
		if(retriever)
		{
			FinishCommand(this, true);
			if(retriever->~HowToProduce(this, def, target2))
			{
				return true;
			}
		}
		if(!GetAvailableObject (def, target2))
		{
			var produceRetriever = FindObject2(Find_InRect(-500, -250, 1000, 500), Find_Func("IsRetriever"), Find_Func("CanRetrieveObject", def, true, target2), Find_Exclude(target), Sort_Distance());
			if(produceRetriever)
			{
				FinishCommand(this, true);
				if(produceRetriever->~HowToProduce(this, def, target2))
				{
					return true;
				}
			}
		}
	}
	return _inherited(target, Tx, Ty, target2, def);
}
