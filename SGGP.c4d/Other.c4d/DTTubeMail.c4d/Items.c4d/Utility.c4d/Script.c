#strict 2

func AttachVertex() { return 3; }

func Detach()
{
	if(Attached() || Floating())
	{
		SetAction("Idle");
		return true;
	}
	return false;
}

func AttachObjectCondition(object caller)
{
	return Find_And(Find_Or(Find_OCF(OCF_Entrance | OCF_Collection), ...), Find_Not(Find_Category(C4D_Living)));
}

func AttachMenu(object caller, bool allowFloating)
{
	var targets = FindObjects(Find_AtPoint(), Find_Exclude(caller), Find_Exclude(this), AttachObjectCondition(caller));
	if(allowFloating)
	{
		targets[GetLength(targets)] = [0, "$AttachWall$", GetID()];
	}
	return caller->~CreateSelectionMenu("AttachEntry", targets, GetID(), "$SelectTarget$", this);
}

func AttachEntry(id id, object target)
{
	if(target)
	{
		return Attach(target);
	}
	else
	{
		if(Contained())
		{
			Contained()->Exit(this); // TODO: maybe use scripted Float instead
		}
		return SetAction("Float");
	}
}

func Attach(object target) // TODO: maybe use scripted Attach instead; check if target shape is still at own position; At best implement FilterObject(s) using Find_*-Filter at first und use that
{ // WARNING: needs an action with the name "Attach", the Procedure "ATTACH" and an AbortCall of "Detached"
	SetVertex(AttachVertex(), VTX_X, GetX(target) - GetX() + GetVertex(0, VTX_X, target), this, VTX_SetPermanentUpd);
	SetVertex(AttachVertex(), VTX_Y, GetY(target) - GetY() + 5 + GetVertex(0, VTX_Y, target), this, VTX_SetPermanentUpd);
	
	SetAction("Attach", target);
	SetActionData(AttachVertex() << 8);
}

func UpdateTransferZone()
{
	if(Attached())
	{
		SetActionData(AttachVertex() << 8);
	}
}

func IsTubeTarget() { return true; }

func IsAnvilProduct() { return true; }

func Attached(bool containerFallback) { return (GetAction() == "Attach" && GetActionTarget()) || (containerFallback && Contained()); }

func Floating() { return GetAction() == "Float"; }

func Detached()
{
	SetVertex(AttachVertex(), VTX_X, 0, this, VTX_SetPermanentUpd);
	SetVertex(AttachVertex(), VTX_Y, 0, this, VTX_SetPermanentUpd);
}

func RejectEntrance(object container) { return Attached() && Contained(Attached()) != container || Floating(); }

func CanRetrieveObject(id type, bool allowProduction, object excludeOrigin)
{
	return FindObject2(Find_Tube(), Find_Func("CanRetrieveObject", this, type, allowProduction, excludeOrigin), excludeOrigin && Find_Not(Find_Func("HasOrigin", excludeOrigin)));
}

func RetrieveObject() { return this->~RetrieveSendObject(...) || this->~RetrieveProduceObject(...); }

func GetRetrievableIDs(bool produce)
{
	var lines = FindObjects(Find_Tube()), IDs = [], produceIDs = [];
	for(var line in lines)
	{
		var lineIDs = line->GetRetrievableObjects(this);
		if(lineIDs)
		{
			for(var id in lineIDs)
			{
				if(GetIndexOf(id, IDs) == -1)
				{
					IDs[GetLength(IDs)] = id;
				}
			}
		}
		
		if(produce)
		{
			produceIDs[GetLength(produceIDs)] = [line->GetLineEnd(this), line->GetRetrievableObjects(this, true)];
		}
	}
	if(produce)
	{
		if(GetLength(produceIDs) == 0)
		{
			return [];
		}
		var ret = [], parts = [], part;
		for(var i = 0; i < GetLength(produceIDs); ++i)
		{
			part = [];
			if(produceIDs[i][1])
			{
				for(var id in produceIDs[i][1])
				{
					if(GetIndexOf(id, parts) == -1 && GetIndexOf(id, IDs) == -1)
					{
						part[GetLength(part)] = id;
						parts[GetLength(parts)] = id;
					}
				}
				if(GetLength(part) > 0)
				{
					ret[GetLength(ret)] = [produceIDs[i][0], part];
				}
			}
		}
		return ret;
	}
	return IDs;
}

func ProductionTitle() { return "$Production$"; }
func ProductionSymbol() { return GetID(Attached() || this); }

func RetrieveMenu(object caller, id selectID)
{
	var IDs = GetRetrievableIDs();
	if(caller && CreateMenu(GetID(), caller, this, C4MN_Extra_None, "$SelectRetrieveType$", 0, C4MN_Style_Context))
	{
		if(!selectID)
		{
			SetCommand(caller, "None");
		}
		var i = 0;
		for(var id in IDs)
		{
			AddMenuItem(GetName(0, id), "RetrieveMenuEntry", id, caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
			if(id == selectID)
			{
				SelectMenuItem(i, caller);
			}
			++i;
		}
		IDs = GetRetrievableIDs(true);
		if(GetLength(IDs) > 0)
		{
			for(var producer in IDs)
			{
				AddMenuItem(producer[0]->ProductionTitle(), 0, producer[0]->ProductionSymbol(), caller);
				++i;
				for(var id in producer[1])
				{
					AddMenuItem(Format("    %s", GetName(0, id)), "RetrieveMenuEntry", id, caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
					if(id == selectID)
					{
						SelectMenuItem(i, caller);
					}
					++i;
				}
			}
		}
		return true;
	}
}

func RetrieveMenuEntry(id type, object caller)
{
	SetRetrieveCommands(type, caller, false);
	RetrieveMenu(caller, type);
}

func SetRetrieveCommands(id type, object caller, bool indirect, object excludeOrigin)
{
	if((!indirect && ((!Attached() && !Floating()) || (GetProcedure(caller) == "PUSH" && GetActionTarget(0, caller) == this))) || !CommandRequireContainerOrPush(caller, Attached() || (Floating() && this), BindCallback((indirect && "RetrieveObjectForProduction") || "RetrieveMenuEntry", [Bind(type), 0, Bind(excludeOrigin)]), 0, indirect))
	{
		RetrieveObjectThroughTube(type);
	}
}

func RetrieveObjectForProduction(id type, object caller, object excludeOrigin)
{
	RetrieveObjectThroughTube(type, BindCallback("ObjectReceived", [Bind(caller), 0]), excludeOrigin, BindCallback("ObjectReceivingFailed", [Bind(caller)]));
	AddCommand(caller, "Wait", 0, 0, 0, 0, 0, -1);
}

func ObjectReceivingFailed(object caller)
{
	FinishCommand(caller, false);
}

func ObjectReceived(object caller, object obj)
{
	FinishCommand(caller, true);
	FinishCommand(caller, true);
	FinishCommand(caller, true);
	AddCommand(caller, "Get", obj);
}

func RetrieveObjectThroughTube(id type, arriveCallback, object excludeOrigin, failCallback)
{
	var line = FindObject2(Find_Tube(), Find_Func("CanRetrieveObject", this, type, false, excludeOrigin)) || FindObject2(Find_Tube(), Find_Func("CanRetrieveObject", this, type, true, excludeOrigin), Sort_Func("FactoryLoad", this));
	return line && line->RetrieveObject(this, type, arriveCallback, excludeOrigin, failCallback);
}

func SendableObjectConditions(object container)
{
	return Find_And(Find_OCF(OCF_Collectible), Find_OCF(OCF_Fullcon), ...);
}

func SendableConditions(object container)
{
	container = container || Attached();
	if(container)
	{
		return Find_And(Find_Container(container), SendableObjectConditions(container));
	}
	else
	{
		return Find_Or();
	}
}

func GetSendableIDs(bool production)
{
	var IDs = [];
	var attached = Attached();
	if(attached)
	{
		for(var obj in FindObjects(SendableConditions(attached)))
		{
			if(GetIndexOf(GetID(obj), IDs) == -1)
			{
				IDs[GetLength(IDs)] = GetID(obj);
			}
		}
	}
	if(production)
	{
		var produceIDs = this->~GetProducableIDs();
		var ret = [];
		if(produceIDs)
		{
			for(var id in produceIDs)
			{
				if(GetIndexOf(id, IDs) == -1)
				{
					ret[GetLength(ret)] = id;
				}
			}
		}
		return ret;
	}
	return IDs;
}

func FindSendableObject(id type)
{
	return FindObject2(SendableConditions(), type && Find_ID(type));
}

func SendMenu(object caller, id selectID)
{
	if(caller && CreateMenu(GetID(), caller, this, C4MN_Extra_None, "$SelectSendType$", 0, C4MN_Style_Context))
	{
		if(!selectID)
		{
			SetCommand(caller, "None");
		}
		var i = 0;
		for(var id in GetSendableIDs())
		{
			AddMenuItem(GetName(0, id), "SendMenuEntry", id, caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
			if(id == selectID)
			{
				SelectMenuItem(i, caller);
			}
			++i;
		}
		var IDs = GetSendableIDs(true);
		if(GetLength(IDs) > 0)
		{
			AddMenuItem(ProductionTitle(), 0, ProductionSymbol(), caller);
			++i;
			for(var id in IDs)
			{
				AddMenuItem(Format("    %s", GetName(0, id)), "SendMenuEntry", id, caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
				if(id == selectID)
				{
					SelectMenuItem(i, caller);
				}
				++i;
			}
		}
		return true;
	}
}

func SendMenuEntry(id type, object caller)
{
	if(!Attached() || (GetProcedure(caller) == "PUSH" && GetActionTarget(0, caller) == this) || !CommandRequireContainerOrPush(caller, Attached(), BindCallback("SendMenuEntry", [Bind(type), 0])))
	{
		SendObjectThroughTube(type);
	}
	SendMenu(caller, type);
}

func SendObjectThroughTube(id type, object line, arriveCallback, object excludeOrigin, failCallback, object realTarget)
{
	var attached = Attached();
	if(attached)
	{
		var objs = FindObjects(SendableConditions(attached), type && Find_ID(type));
		if(GetLength(objs) > 0)
		{
			for(var obj in objs)
			{
				line =  line || FindObject2(Find_Tube(), Find_Func("CanSendObject", this, obj));
				if(line)
				{
					line->SendObject(this, obj, arriveCallback, false, realTarget);
					break;
				}
			}
			return true;
		}
		else if(type)
		{
			this->~RetrieveProduceObject(line, type, arriveCallback, excludeOrigin, failCallback, realTarget);
			return true;
		}
	}
}

func DenyContainedDirectCom()
{
	return Contained();
}

func TryPut(object obj, object container)
{
	var attached = container || Attached() || Contained();
	if(attached)
	{
		return Put(attached, obj);
	}
	else
	{
		return false;
	}
}

func ReceiveObject(object obj, bool noReturn)
{
	Exit(obj);
	SetPosition(GetX(), GetY(), obj);
	return TryPut(obj) || (!Attached() && !Contained());
}

func IsRemoteControllable() { return false; }

func CommandRequireContainerOrPush(object cmdTarget, object target, callback, object callbackTarget, bool add)
{
	if(add || (Contained(cmdTarget) != target && (GetProcedure(cmdTarget) != "PUSH" || GetActionTarget(0, cmdTarget) != target)))
	{
		if(add)
		{
			AddCommand(cmdTarget, "Call", this, callback, 0, callbackTarget || this, 0, "ClonkEnteredCallback");
			AddCommand(cmdTarget, "Call", this, target, 0, 0, 0, "EnterOrGrabIfNotAlready");
		}
		else
		{
			AppendCommand(cmdTarget, "Call", this, target, 0, 0, 0, "EnterOrGrabIfNotAlready");
			AppendCommand(cmdTarget, "Call", this, callback, 0, callbackTarget || this, 0, "ClonkEnteredCallback");
		}
		return true;
	}
	return false;
}

func EnterOrGrabIfNotAlready(object cmdTarget, object target)
{
	if(target && Contained(cmdTarget) != target && (GetProcedure(cmdTarget) != "PUSH" || GetActionTarget(0, cmdTarget) != target))
	{
		if(GetDefGrab(GetID(target)))
		{
			AddCommand(cmdTarget, "Grab", target);
		}
		else
		{
			AddCommand(cmdTarget, "Enter", target);
		}
		return true;
	}
}

func ClonkEnteredCallback(object cmdTarget, callback, null, object callbackTarget)
{
	return callbackTarget && callbackTarget->Call(callback, cmdTarget);
}

func ObjectOrigin()
{
	return Attached(true) || this;
}
