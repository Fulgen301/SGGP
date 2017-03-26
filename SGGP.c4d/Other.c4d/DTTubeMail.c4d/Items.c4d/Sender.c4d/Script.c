#strict 2

func IsTubeTarget() { return true; }

func Collection2(object obj)
{
	var line = FindObject2(Find_Tube(), Find_Func("CanSendObject", this, obj));
	if(!line || !line->SendObject(this, obj))
	{
		Exit(obj);
	}
}

func RejectCollect(id id, object obj)
{
	return obj && !FindObject2(Find_Tube(), Find_Func("CanSendObject", this, obj));
}

func IsAnvilProduct() { return true; }
