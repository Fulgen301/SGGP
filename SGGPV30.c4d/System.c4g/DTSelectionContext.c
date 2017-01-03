#strict 2
#appendto HZCK
#appendto CLNK

global func SetAllCursorsCommand(int player)
{
	var ret;
	for(var i = 0, cursor; cursor = GetCursor(player, i); ++i)
	{
		ret = SetCommand(cursor, ...) || ret;
		ExecuteCommand(cursor);
	}
	return ret;
}

local selectionObjects, selectMark;

func FindTreeCriteria()
{
	return Find_And(Find_AtPoint(), Find_OCF(OCF_Chop), Find_Layer(GetObjectLayer()));
}

func CreateSelectionMenu(string callback, array objects, id symbol, string caption, object callbackObject)
{
	SetComDir(COMD_Stop);
	var ret = CreateMenu(symbol, this, callbackObject || this, C4MN_Extra_None, caption, 0, C4MN_Style_Context, 0, SELM);
	selectionObjects = objects;
	for(var obj in objects)
	{
		if(GetType(obj) == C4V_C4Object)
		{
			AddMenuItem(GetName(obj), callback, GetID(obj), this, 0, obj, 0, C4MN_Add_ForceNoDesc | C4MN_Add_ImgObject, obj);
		}
		else
		{
			AddMenuItem(obj[1] || GetName(obj[0]), callback, obj[2] || GetID(obj[0]), this, 0, obj[0], 0, C4MN_Add_ForceNoDesc | ((!obj[2]) && C4MN_Add_ImgObject), obj[0]);
		}
	}
	EffectCall(this, AddEffect("IntShowSelection", this, 100, 2, this), "Timer");
	return ret;
}

func FxIntShowSelectionTimer(object target, int effectNumber)
{
	if(GetMenu(target) != SELM)
	{
		if(selectMark)
		{
			RemoveObject(selectMark);
		}
		return FX_Execute_Kill;
	}
	else
	{
		var obj = selectionObjects[GetMenuSelection(target)];
		if(!obj || (GetType(obj) == C4V_Array && !obj[0]))
		{
			if(selectMark)
			{
				RemoveObject(selectMark);
			}
		}
		else
		{
			selectMark = selectMark || CreateSelectMark();
			if(GetType(obj) == C4V_Array)
			{
				selectMark->MarkObject(obj[0]);
			}
			else
			{
				selectMark->MarkObject(obj);
			}
		}
	}
}

func ContextChop()
{
	[$CtxChop$|Image=CXCP|Condition=AtTreeToChop]
	var objs = FindObjects(FindTreeCriteria());
	if(GetLength(objs) > 1)
	{
		CreateSelectionMenu("ChopObject", objs, CXCP, "$CtxChop$");
		return true;
	}
	else
	{
		return _inherited(...);
	}
}

func ChopObject(id id, object tree)
{
	if(tree) SetAllCursorsCommand(GetController(this), "Chop", tree);
}

func FindConstructionSiteCriteria()
{
	return Find_And(Find_AtRect(GetDefOffset(GetID(this)), GetDefOffset(GetID(this), 1), GetObjWidth(this), GetObjHeight(this) + 10), Find_OCF(OCF_Construct));
}

func AtConstructionSite() { return !Contained() && FindConstructionSite(); }

func ContextConstructionSite()
{
	[$CtxConstructionSite$|Image=CXCM|Condition=AtConstructionSite]
	var objs = FindObjects(FindConstructionSiteCriteria());
	if(GetLength(objs) > 1)
	{
		CreateSelectionMenu("ConstructionSiteMenu", objs, CXCM, "$CtxConstructionSite$");
	}
	else
	{
		ConstructionSiteMenu(0, FindConstructionSite());
	}
}

func ConstructionSiteMenu(id id, object site)
{
	if(ObjectCount(CNMT))
	{
		SetComDir(COMD_Stop);
		CreateMenu(GetID(site), this, this, C4MN_Extra_None, GetName(site), 0, C4MN_Style_Context, 0);
		AddMenuItem("$CtxConstructionMaterial$", "ConstructionSiteMat", CXCM, this, 0, site, 0, C4MN_Add_ForceNoDesc);
		AddMenuItem("$CtxConstructionContinue$", "ConstructionSiteContinue", CXCN, this, 0, site, 0, C4MN_Add_ForceNoDesc);
	}
	else
	{
		ConstructionSiteContinue(id, site);
	}
}

func ConstructionSiteMat(id id, object site)
{
	if(site) PlayerMessage(GetOwner(), site->GetNeededMatStr(), site);
}

func ConstructionSiteContinue(id id, object site)
{
	if(site) SetAllCursorsCommand(GetController(this), "Build", site);
}

func FindGrabbableObjectCriteria()
{
	return Find_And(Find_AtRect(GetDefOffset(GetID(this)), GetDefOffset(GetID(this), 1), GetObjWidth(this), GetObjHeight(this)), Find_OCF(OCF_Grab), Find_NoContainer());
}

func AtGrabbableObject() { return !Contained() && FindObject2(FindGrabbableObjectCriteria()); }

func ContextGrab()
{
	[$CtxGrab$|Image=CXIV|Condition=AtGrabbableObject]
	var objs = FindObjects(FindGrabbableObjectCriteria());
	if(GetLength(objs) > 1)
	{
		if(GetProcedure() == "PUSH")
		{
			for(var i = 0; i < GetLength(objs) ; ++i)
			{
				if(GetActionTarget() == objs[i])
				{
					objs[i] = [objs[i], "$Release$"];
				}
			}
		}
		CreateSelectionMenu("GrabObject", objs, CXIV, "$CtxGrab$");
	}
	else
	{
		GrabObject(0, objs[0]);
	}
}

func GrabObject(id id, object obj)
{
	if(obj)
	{
		if(GetProcedure() == "PUSH" && obj == GetActionTarget())
		{
			SetAllCursorsCommand(GetController(this), "UnGrab");
		}
		else
		{
			SetAllCursorsCommand(GetController(this), "Grab", obj);
		}
	}
}

func FindEnterableObjectCriteria()
{
	return Find_And(Find_AtRect(GetDefOffset(GetID(this)), GetDefOffset(GetID(this), 1), GetObjWidth(this), GetObjHeight(this)), Find_OCF(OCF_Entrance), Find_NoContainer(), Find_Not(Find_Func("HiddenEntrance")));
}

func AtEnterableObject() { return !Contained() && FindObject2(FindEnterableObjectCriteria()); }

func ContextEnter()
{
	[$CtxEnter$|Image=DOOR|Condition=AtEnterableObject]
	var objs = FindObjects(FindEnterableObjectCriteria());
	if(GetLength(objs) > 1)
	{
		CreateSelectionMenu("EnterObject", objs, DOOR, "$CtxEnter$");
	}
	else
	{
		EnterObject(0, objs[0]);
	}
}

func EnterObject(id id, object obj)
{
	if(obj)
	{
		if(GetProcedure() == "PUSH" && GetActionTarget() && !GetDefNoPushEnter(GetID(GetActionTarget())))
		{
			SetAllCursorsCommand(GetController(this), "PushTo", GetActionTarget(), 0, 0, obj);
		}
		else
		{
			SetAllCursorsCommand(GetController(this), "Enter", obj);
		}
	}
}

func AtObjectWithLines()
{
	return !Contained() && FindConnections(true);
}

global func HasLine(bool lineCheck, object target)
{
	if(lineCheck)
	{
		return GetProcedure() == "CONNECT" && (GetActionTarget(0) == target || GetActionTarget(1) == target);
	}
	else
	{
		return FindObject2(Find_Func("HasLine", true, this));
	}
}

func FindConnections(bool single)
{
	var targets = FindObjects(Find_AtPoint(), Find_Exclude(this), Find_Or(Find_OCF(OCF_LineConstruct), Find_Func("HasLine")));
	var connections = [];
	for(var target in targets)
	{
		var lines = FindObjects(Find_Action("Connect"), Find_Or(Find_ActionTarget(target), Find_ActionTarget2(target)));
		for(var line in lines)
		{
			var kit = line->~KitID() || LNKT;
			if(GetID(GetActionTarget(0, line)) == kit || GetID(GetActionTarget(1, line)) == kit) // not connected on the other side
			{
				continue;
			}
			var otherTarget = GetActionTarget(0, line);
			if(otherTarget == target)
			{
				otherTarget = GetActionTarget(1, line);
			}
			var connection = [target, line, otherTarget];
			if(single)
			{
				return connection;
			}
			else
			{
				connections[GetLength(connections)] = connection;
			}
		}
	}
	if(!single)
	{
		return connections;
	}
}

local lineConnectionSelections;

func ContextRemoveLine()
{
	[$TxtRemoveLine$|Image=LNKT|Condition=AtObjectWithLines]
	lineConnectionSelections = FindConnections();
	if(GetLength(lineConnectionSelections) > 1)
	{
		SetComDir(COMD_Stop);
		CreateMenu(LNKT, this, this, C4MN_Extra_None, "$TxtRemoveLine$", 0, C4MN_Style_Context, 0, SELM);
		var i = 0;
		for(var connection in lineConnectionSelections)
		{
			AddMenuItem(Format("%s: %s - %s", GetName(connection[1]), GetName(connection[0]), GetName(connection[2])), "RemoveLineEntry", GetID(connection[1]), this, 0, i++, 0, C4MN_Add_ForceNoDesc);
		}
		AddEffect("IntShowDoubleSelection", this, 100, 1, this);
	}
	else
	{
		return RemoveLineEntry(0, 0);
	}
	return 1;
}

local selectMark2;

func FxIntShowDoubleSelectionTimer(object target, int effectNumber)
{
	if(GetMenu(target) != SELM)
	{
		if(selectMark)
		{
			RemoveObject(selectMark);
		}
		if(selectMark2)
		{
			RemoveObject(selectMark2);
		}
		return FX_Execute_Kill;
	}
	else
	{
		var obj = lineConnectionSelections[GetMenuSelection(target)];
		if(!obj[0])
		{
			if(selectMark)
			{
				RemoveObject(selectMark);
			}
		}
		else
		{
			selectMark = selectMark || CreateSelectMark();
			selectMark->MarkObject(obj[0]);
		}
		if(!obj[2])
		{
			if(selectMark2)
			{
				RemoveObject(selectMark2);
			}
		}
		else
		{
			selectMark2 = selectMark2 || CreateSelectMark()->Secondary();
			selectMark2->MarkObject(obj[2]);
		}
	}
}

func RemoveLineEntry(id id, int pos)
{
	var connection = lineConnectionSelections[pos];
	if(!connection || !GetPhysical("CanConstruct"))
	{
		return;
	}
	if((GetActionTarget(0, connection[1]) != connection[0] && GetActionTarget(1, connection[1]) != connection[0]) || (GetActionTarget(0, connection[1]) != connection[2] && GetActionTarget(1, connection[1]) != connection[2]))
	{
		Message("$AlreadyDisconnected$", this);
		Sound("Error");
		return false;
	}

	var lnkt = CreateObject(connection[1]->~KitID() || LNKT, 0, 0, GetOwner());
	Collect(lnkt);
	Sound("Connect");
	if(GetActionTarget(0, connection[1]) == connection[0])
	{
		SetActionTargets(lnkt, connection[2], connection[1]);
	}
	else
	{
		SetActionTargets(connection[2], lnkt, connection[1]);
	}
	Message("$IDS_OBJ_DISCONNECT$", this, GetName(connection[1]), GetName(connection[0]));
	return true;
}

func ControlDigDouble(target, overloaded)
{
	var ret = _inherited(target, true, ...);
	if(!ret && !overloaded)
	{
		if(GetProcedure() == "WALK" || GetProcedure() == "DIG" || GetProcedure() == "SWIM")
		{
			if(Contents() && Contents()->~Activate(this))
			{
				return true;
			}
			else if(AtTreeToChop() && GetProcedure() != "SWIM")
			{
				SetAllCursorsCommand(GetController(this), "Chop", FindTree());
				return true;
			}
			else if(AtObjectWithLines())
			{
				if(ContextRemoveLine())
				{
					return true;
				}
			}
		}
	}
	return ret;
}
