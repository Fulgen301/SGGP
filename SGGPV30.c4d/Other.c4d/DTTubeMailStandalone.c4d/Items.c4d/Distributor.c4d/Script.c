#strict 2
#include UT7I

func Floating()
{
	return GetProcedure() == "FLOAT";
}

func ControlDigDouble(object caller)
{
	if(DenyContainedDirectCom())
	{
		return false;
	}
	return SetAction("Idle");
}

func Activate(object caller)
{
	caller->Exit(this);
	SetAction("Float");
	return true;
}

func AcceptsObject(object obj, id id, object requester)
{
	return FindObject2(Find_Tube(), ExcludeOrigin(requester), Find_Func("CanSendObject", this, obj));
}

func RetrieveObject(object requester, id type, arriveCallback, object excludeOrigin, failCallback, object realTarget)
{
	var line = FindObject2(Find_Tube(), ExcludeOrigin(requester), ExcludeOrigin(excludeOrigin), Find_Func("CanRetrieveObject", this, type, false)) || FindObject2(Find_Tube(), ExcludeOrigin(requester), ExcludeOrigin(excludeOrigin), Find_Func("CanRetrieveObject", this, type, true), Sort_Func("FactoryLoad"));
	if(line)
	{
		return line->RetrieveObject(this, type, BindCallback(Callback("ForwardObject"), [0, 1, 2, Bind(requester), Bind(arriveCallback)]), 0, failCallback, realTarget || requester->GetLineEnd(this));
	}
}

func ForwardObject(object obj, object line, object receiver, object requester, arriveCallback)
{
	if(requester)
	{
		return requester->SendObject(this, obj, arriveCallback);
	}
}

func ExcludeOrigin(object originLine)
{
	var origin = originLine;
	if(!originLine)
	{
		return Find_And();
	}
	if(origin->~IsTube())
	{
		origin = origin->ObjectOrigin(this);
	}
	else
	{
		originLine = 0;
	}
	return Find_And(Find_Exclude(originLine), Find_Not(Find_Func("HasObjectOrigin", origin)));
}

func ReceiveObject(object obj, bool noReturn, array arriveCallback, object senderLine)
{
	if(arriveCallback)
	{
		if(CallA(arriveCallback, [obj, senderLine, this], true))
		{
			return TU7I_NoCallback;
		}
	}
	else
	{
		var line = FindObject2(Find_Tube(), ExcludeOrigin(senderLine), Find_Func("CanSendObject", this, obj));
		return line && line->SendObject(this, obj, noReturn);
	}
}

func HasObject(id type, bool allowProduction, object receiverLine, object excludeOrigin)
{
	return FindObject2(Find_Tube(), ExcludeOrigin(receiverLine), Find_Func("CanRetrieveObject", this, type, allowProduction), ExcludeOrigin(excludeOrigin));
}

func GetRetrievableObjects(object requester, bool produce)
{
	var lines = FindObjects(Find_Tube(), ExcludeOrigin(requester));
	var IDs = [], produceIDs = [], part;
	for(var line in lines)
	{
		part = line->~GetRetrievableObjects(this, produce) || [];
		for(var id in part)
		{
			if(GetIndexOf(id, IDs) == -1)
			{
				IDs[GetLength(IDs)] = id;
			}
		}
	}
	return IDs;
}

func RejectEntrance(object obj)
{
	return Floating();
}
