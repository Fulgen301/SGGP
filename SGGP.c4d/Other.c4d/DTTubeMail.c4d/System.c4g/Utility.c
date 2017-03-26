#strict 2

global func GetLineEnd(object otherEnd, bool second, object line)
{
	line = line || this;
	var ret = GetActionTarget(!!second, line);
	if(otherEnd && otherEnd == ret)
	{
		ret = GetActionTarget(!second, line);
	}
	return ret;
}

global func Find_Tube(object target)
{
	return Find_Line(TK7I_Tube, target);
}

global func Find_Line(id type, object target)
{
	target = target || this;
	return [C4FO_Func, "Find_LineCheck", type, target];
}

global func Find_LineCheck(id type, object target)
{
	return (!type || type == GetID(this)) && GetProcedure() == "CONNECT" && (GetActionTarget(0) == target || GetActionTarget(1) == target);
}

global func Put(object container, object obj)
{
	obj = obj || this;
	if(container->GetOCF() & OCF_Collection)
	{
		return container->Collect(obj);
	}
	else
	{
		return CanCollect(container, obj, GetID(obj)) && obj->Enter(container) && (container->~Collection(obj, !(GetOCF(container) & OCF_Entrance)) || true);
	}
}

global func CanCollect(object container, object obj, id id)
{
	id = id || GetID(obj);
	var collectionLimit = GetDefCoreVal("CollectionLimit", "DefCore", GetID(container), 0);
	if(!collectionLimit || container->ContentsCount() < collectionLimit)
	{
		return !container->~RejectCollect(id, obj) && (!obj || !obj->~RejectEntrance(container));
	}
	return false;
}

global func Find_GrabPutGet(int type)
{
	return [C4FO_Func, "Find_GrabPutGetCheck", type];
}

global func Find_GrabPutGetCheck(int type)
{
	return GetDefGrabPutGet(GetID()) & type;
}
