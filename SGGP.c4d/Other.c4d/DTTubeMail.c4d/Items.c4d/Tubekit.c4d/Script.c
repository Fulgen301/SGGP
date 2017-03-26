#strict 2

static const TK7I_Tube = TU7I;

func Find_TubeTarget()
{
	return [C4FO_Func, "IsTubeTarget"];
}

func Activate(object caller)
{
	var line = FindObject2(Find_Tube(this)), lineEnd;
	if(line)
	{
		lineEnd = line->GetLineEnd(this);
	}
	var targets = FindObjects(Find_AtRect(0, -9, 1, 18), Find_TubeTarget());
	if(GetLength(targets) > 1)
	{
		caller->~CreateSelectionMenu("ConnectTarget", targets, GetID(), "$SelectTarget$", this);
	}
	else if(GetLength(targets) == 1)
	{
		ConnectTarget(0, targets[0]);
	}
	else
	{
		PlayerMessage(GetController(caller), "$TxtNoNewLine$", this);
	}
	return true;
}

func ConnectTarget(id id, object target)
{
	var line = FindObject2(Find_Line(TK7I_Tube, this)), lineEnd;
	if(line)
	{
		lineEnd = line->GetLineEnd(this);
		if(lineEnd == target)
		{
			PlayerMessage(GetController(Contained()), "$TxtLineRemoval$", Contained(), GetName(line));
			RemoveObject(line);
			return true;
		}
	}
	else
	{
		line = CreateObject(TK7I_Tube);
		CreateObject(TK7I_Tube)->Complement(line);
	}
	
	if(line->GetActionTarget(0) == lineEnd)
	{
		line->SetActionTargets(lineEnd || this, target);
	}
	else
	{
		line->SetActionTargets(target, lineEnd || this);
	}
	
	PlayerMessage(GetController(Contained()), "$TxtConnect$", Contained(), GetName(line), GetName(target));
	if(lineEnd)
	{
		RemoveObject();
	}
	return true;
}

func AcceptsObject(object obj)
{
	return true;
}

func ReceiveObject(object obj, bool noReturn)
{
	obj->Enter(this);
	Exit(obj);
	if(Contained())
	{
		Put(Contained(), obj);
	}
	return true;
}

func IsAnvilProduct() { return true; }
