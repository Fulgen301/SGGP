#strict 2
#include UT7I

func ControlDigDouble(object caller)
{
	if(DenyContainedDirectCom())
	{
		return false;
	}
	return Detach();
}

func ControlThrow(object caller)
{
	if(DenyContainedDirectCom())
	{
		return false;
	}
	if(!Contents(0, caller))
	{
		RetrieveObjectThroughTube();
		return ClearLastPlrCom(GetController(caller)) || true;
	}
	return false;
}

func ControlUp(object caller)
{
	if(DenyContainedDirectCom())
	{
		return false;
	}
	return RetrieveMenu(caller);
}

func AttachObjectCondition(object caller)
{
	return _inherited(caller, Find_GrabPutGet(C4D_GrabPut), ...);
}

func Activate(object caller)
{
	return AttachMenu(caller, true);
}

func AcceptsObject(object obj, id id)
{
	var attached = Attached() || Contained();
	return !attached || CanCollect(attached, obj, id);
}

func RejectCollect(id id, object obj)
{
	return !AcceptsObject(obj, id);
}

func Collection2(object obj)
{
	return TryPut(obj) || Exit(obj);
}

func SensorCallbacks()
{
	var ret = [["$RetrieveObject$", BindCallback("RetrieveObjectThroughTube", [1, 2])]];
	for(var id in GetRetrievableIDs())
	{
		ret[GetLength(ret)] = [Format("$RetrieveObjectType$", GetName(0, id)), BindCallback("RetrieveObjectThroughTube", [Bind(id), 2]), id];
	}
	for(var part in GetRetrievableIDs(true))
	{
		for(var id in part[1])
		{
			ret[GetLength(ret)] = [Format("$RetrieveObjectType$", GetName(0, id)), BindCallback("RetrieveObjectThroughTube", [Bind(id), 2]), id];
		}
	}
	return ret;
}

func AttachContextRetrieve(object caller)
{
	[$RetrieveObject$|Image=FI7I]
	return RetrieveMenu(caller);
}

func IsProducerOf(object caller, id def)
{
	return CanRetrieveObject(def);
}

func HowToProduce(object caller, id def, object excludeOrigin)
{
	return SetRetrieveCommands(def, caller, true, excludeOrigin) || true;
}

func IsRetriever() { return true; }
