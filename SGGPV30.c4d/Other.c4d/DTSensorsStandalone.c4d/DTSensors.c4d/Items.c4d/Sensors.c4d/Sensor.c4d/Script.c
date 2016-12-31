#strict 2 // TODO: catch ChangeDef and Fire (because of BurnTo. ignore BuildTo because connecting construction sites is nonsense, isnt it?)

local attached;
local selectCaller, selectTrigger, selectCallbacks, selectTarget, selectTargets, selectTargetsMax;
local triggerCallbacks;
local desc, descVisible;
local attachPos;
local entrance;

static const SN7I_Setup_NoDesc = -1;

func Initialize()
{
	Init();
}

func ContextSetup()
{
	[$CtxSetup$|Image=RSR1|Condition=_SetupCondition]
	return _Setup(...);
}

func ContextAttach()
{
	[$Attach$|Image=CXCN|Condition=_AttachCondition]
	return _Attach(...);
}

func ContextDetach()
{
	[$Detach$|Image=CXCN|Condition=_DetachCondition]
	return _Detach(...);
}

func Attached() { return !!attached; }

func RejectContents() { return true; }
func RejectEntrance() { return attached || !AllowEntrance(); }
func AllowEntrance() { return true; }
func Setup() { return true; }
func Attach() {  }
func Detach() {  }
func SetupMenuID() {  }
func Triggers() { return []; }

func AttachCondition() { return true; }
func DetachCondition() { return true; }
func SetupCondition() { return true; }

func SelectTargetText() { return "$SelectTarget$"; }
func RemoveTargetText() { return "$RemoveTarget$"; }
func TargetText() { return "$Target$"; }

func EntranceCallback() {  }

func Init() {  }

func AttachFixPosition() { return true; }

func Activate(object caller)
{
	return SetupCondition(caller) && _Setup(caller, ...);
}

func ControlDigDouble()
{
	return Attached() && Activate(...);
}

func DenyHostility(object caller)
{
	return !Hostile(GetOwner(), GetOwner(caller));
}

func _SetupCondition(object caller)
{
	return DenyHostility(caller);
}

func _Setup(object caller, bool selectDescChange, bool selectDescToggle)
{
	if(!DenyHostility(caller))
	{
		return 0;
	}
	if(CreateMenu(RSR1, caller, this, C4MN_Extra_None, Format("$Setup$", GetName()), 0, C4MN_Style_Context, 0, SetupMenuID()))
	{
		var i = 0;
		selectTrigger = 0;
		AddMenuItem("$AddTarget$", "AddSensorTarget", GetID(), caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
		++i;
		if(triggerCallbacks && GetLength(triggerCallbacks))
		{
			AddMenuItem("$RemoveTarget$", "RemoveSensorTarget", GetID(), caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
			++i;
		}
		var ret = Setup(caller, i, ...);
		if(ret != SN7I_Setup_NoDesc)
		{
			AddMenuItem(Format("$ChangeDesc$", desc || ""), "ChangeDesc", GetID(), caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
			if(selectDescChange)
			{
				SelectMenuItem(i, caller);
			}
			++i;
			AddMenuItem((!descVisible && "$ShowDesc$") || "$HideDesc$", "ToggleDesc", GetID(), caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
			if(selectDescToggle)
			{
				SelectMenuItem(i, caller);
			}
			++i;
		}
		return ret;
	}
}

func ChangeDesc(id id, object caller, bool right)
{
	if(right)
	{
		descVisible = false;
		desc = 0;
		ToggleDesc(0, 0, 0, true);
	}

	if(caller)
	{
		_Setup(caller, true);
		selectCaller = caller;
	}

	if(!right)
	{
		CallMessageBoard(this, false, "$EnterDesc$", GetController(caller));
	}
}

func InputCallback(string input, int plr)
{
	if(!desc)
	{
		descVisible = true;
	}
	if(input != "")
	{
		desc = input;
		ToggleDesc(0, 0, 0, true);
	}
	_Setup(selectCaller, true);
}

func ToggleDesc(id id, object caller, bool right, bool update)
{
	if(!update)
	{
		descVisible = !descVisible;
	}
	if(!descVisible)
	{
		Message("", this);
	}
	else if(desc)
	{
		Message("@%s", this, desc);
	}
	if(caller && !update)
	{
		_Setup(caller, false, true);
	}
}

func AddSensorTarget(id id, object caller, bool right, int selection)
{
	var itemCommand = (right && "SelectSensorTarget2") || "SelectSensorTarget";
	selectCaller = caller;
	if(CreateMenu(GetID(), selectCaller, this, C4MN_Extra_None, "$SelectTrigger$", 0, C4MN_Style_Context, 0))
	{
		var i = 0;
		for(var trigger in Triggers())
		{
			var caption = trigger[0];
			if(GetType(selectTrigger) == C4V_Array)
			{
				if(GetIndexOf(i, selectTrigger) != -1)
				{
					caption = Format("× %s", caption);
				}
				else
				{
					caption = Format("   %s", caption);
				}
			}
			AddMenuItem(caption, itemCommand, trigger[1] || GetID(), selectCaller, 0, i++, 0, C4MN_Add_ForceNoDesc);
		}
		if(GetType(selectTrigger) == C4V_Array)
		{
			AddMenuItem("$Continue$", itemCommand, GetID(), selectCaller, 0, -1, 0, C4MN_Add_ForceNoDesc);
		}
		SelectMenuItem(selection, caller);
		return true;
	}
}

local triggerTargetList;
func RemoveSensorTarget(id id, object caller)
{
	if(CreateMenu(GetID(), caller, this, C4MN_Extra_None, SelectTargetText(), 0, C4MN_Style_Context, 0, SELM))
	{
		triggerTargetList = [];
		var j = 0, cnt = 0;
		for(var trigger in triggerCallbacks)
		{
			if(trigger)
			{
				var triggerInfo = Triggers()[j], i = 0;
				for(var callback in trigger)
				{
					if(GetType(callback) == C4V_Array)
					{
						if(CheckTarget(j, i))
						{
							AddMenuItem(Format("%s: {{%i}} %s -> %s", triggerInfo[0], GetID(callback[0]), GetName(callback[0]), callback[1][0]), Format("RemoveSensorTargetIndex(%d, %d, Object(%d), %d)", j, i - 1, ObjectNumber(caller), cnt++), callback[1][2] || GetID(), caller, 0, 0, 0, C4MN_Add_ForceNoDesc);
							triggerTargetList[GetLength(triggerTargetList)] = callback[0];
						}
					}
				}
			}
			++j;
		}
		EffectCall(caller, AddEffect("IntShowSelection", caller, 1, 1, this), "Timer");
		return true;
	}
}

func RemoveSensorTargetIndex(int trigger, int index, object menuObject, int selection)
{
	if(triggerCallbacks && triggerCallbacks[trigger])
	{
		ArrayErase(triggerCallbacks[trigger], index);
		if(!GetLength(triggerCallbacks[trigger]))
		{
			triggerCallbacks[trigger] = 0;
		}
		var empty = true;
		for(var callbacks in triggerCallbacks)
		{
			if(callbacks)
			{
				empty = false;
				break;
			}
		}
		if(!empty && menuObject)
		{
			RemoveSensorTarget(0, menuObject);
			SelectMenuItem(selection && (selection - 1), menuObject); // fallback to previous if next is not existent
			SelectMenuItem(selection, menuObject);
		}
		else
		{
			triggerCallbacks = 0;
		}
	}
}

local selectMark;
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
		var obj = triggerTargetList[GetMenuSelection(target)];
		if(!obj)
		{
			if(selectMark)
			{
				RemoveObject(selectMark);
			}
		}
		else
		{
			selectMark = selectMark || CreateSelectMark();
			selectMark->MarkObject(obj);
		}
	}
}

func _Attach(object caller)
{
	var contained;
	if(contained = Contained())
	{
		contained->Exit(this);
		SetPosition(GetX(), GetY() + 3);
	}
	var ret = Attach(caller, contained, ...);
	if(AttachFixPosition())
	{
		attachPos = [GetX(), GetY()];
		attached = AddTimer("AttachTimer", 1);
	}
	else
	{
		attached = true;
	}
	if(EntranceCallback())
	{
		entrance = CreateObject(SE7I)->Attach(this);
	}
	return ret;
}

func _Detach(object caller)
{
	if(Attached())
	{
		if(AttachFixPosition())
		{
			RemoveTimer(attached);
		}
		attached = 0;
		Collect(this, caller);
	}
	if(entrance)
	{
		RemoveObject(entrance);
	}
	return Detach(...);
}

func _AttachCondition(object caller)
{
	return DenyHostility(caller) && !Attached() && AttachCondition(caller, ...);
}

func _DetachCondition(object caller)
{
	return DenyHostility(caller) && Attached() && DetachCondition(caller, ...);
}

func AttachTimer()
{
	SetPosition(attachPos[0], attachPos[1]);
	SetSpeed();
}

global func GetSensorCallbacks(object sensor)
{
	var ret = [];
	// Remote control callbacks

	var customCallbacks = this->~SensorCallbacks(sensor);
	if(customCallbacks)
	{
		ArrayAppendArray(ret, customCallbacks);
	}

	// Legacy sensor pack (and hazard) support
	for(var i = 1, name; ; ++i)
	{
		if(GetType(name = this->~GetTriggerName(i)) == C4V_String)
		{
			ret[GetLength(ret)] = [name, BindCallback("Trigger", [Bind(i), Bind(sensor), 0])]; // 0 = user, rest = other args passed to trigger
			// WARNING: update mapping when necessary
		}
		else if(name = this->~ConsoleControl(i))
		{
			ret[GetLength(ret)] = [name, BindCallback(SN7I->Callback("HazardCallback"), [Bind(i), Bind(this), Bind(ObjectNumber(sensor)), 0])]; // 0 = user, rest = other args passed to trigger
			// WARNING: update mapping when necessary
		}
		else
		{
			break;
		}
	}

	if(this->~IsRemoteControllable(sensor))
	{
		for(var mapping in this->~RemoteControlMap(sensor))
		{
			ret[GetLength(ret)] = [mapping[2] || Format("$Control$", RC7I->GetControlName(mapping[0])), mapping[1]];
		}
	}
	if(GetLength(ret) > 0)
	{
		return ret;
	}
	else
	{
		return false;
	}
}

func HazardCallback(int trigger, object target, int sensor, object user)
{
	return target->~ConsoleControlled(trigger, ObjectNumber(user), sensor);
}

func SelectSensorTarget(id id, int index, bool right)
{
	if(index != -1 && (right || GetType(selectTrigger) == C4V_Array))
	{
		if(GetType(selectTrigger) == C4V_Array)
		{
			var idx;
			if((idx = GetIndexOf(index, selectTrigger)) != -1)
			{
				ArrayErase(selectTrigger, idx);
			}
			else
			{
				selectTrigger[GetLength(selectTrigger)] = index;
			}
		}
		else
		{
			selectTrigger = [index];
		}
		AddSensorTarget(0, selectCaller, 0, index);
	}
	else
	{
		if(index != -1)
		{
			selectTrigger = index;
		}
		if(GetType(selectTrigger) != C4V_Array)
		{
			selectTrigger = [selectTrigger];
		}
		var targets = FindObjects(selectCaller->Find_AtPoint(), Find_Not(Find_Hostile(GetOwner(this))), Find_Func("GetSensorCallbacks", this), Find_Exclude(this));
		if(GetLength(targets) > 0)
		{
			return selectCaller->~CreateSelectionMenu("SelectTargetAction", targets, GetID(), SelectTargetText(), this);
		}
		else
		{
			PlayerMessage(GetOwner(selectCaller), "$NoTargets$", this);
		}
	}
}

func SelectSensorTarget2(id id, int index, bool right)
{
	if(index != -1 && (right || GetType(selectTrigger) == C4V_Array))
	{
		if(GetType(selectTrigger) == C4V_Array)
		{
			var idx;
			if((idx = GetIndexOf(index, selectTrigger)) != -1)
			{
				ArrayErase(selectTrigger, idx);
			}
			else
			{
				selectTrigger[GetLength(selectTrigger)] = index;
			}
		}
		else
		{
			selectTrigger = [index];
		}
		AddSensorTarget(0, selectCaller, true, index);
	}
	else
	{
		if(index != -1)
		{
			selectTrigger = index;
		}
		if(GetType(selectTrigger) != C4V_Array)
		{
			selectTrigger = [selectTrigger];
		}
		var targets = FindObjects(selectCaller->Find_AtPoint(), Find_Not(Find_Hostile(GetOwner(this))), Find_Func("GetSensorCallbacks", this), Find_Exclude(this));
		if(GetLength(targets) > 0)
		{
			selectTargets = CreateArray(GetLength(targets));
			selectTargetsMax = 0;
			for(var i = 0; i < GetLength(targets); ++i)
			{
				var target = targets[i];
				selectTargets[i] = [target, target->GetSensorCallbacks(this), 0];
				selectTargetsMax = Max(selectTargetsMax, GetLength(selectTargets[i][1]));
			}
			SelectTargetActionsSideBySide();
		}
		else
		{
			PlayerMessage(GetOwner(selectCaller), "$NoTargets$", this);
		}
	}
}

func SelectTargetActionsSideBySide(int mainSelection, int subSelection)
{
	SetComDir(COMD_Stop, selectCaller);
	if(CreateMenu(GetID(), selectCaller, this, C4MN_Extra_None, SelectTargetText(), 0, C4MN_Style_Context, 0, SEN2))
	{
		SetMenuSize(2, 0, selectCaller);
		var i, cnt = Max(GetLength(selectTargets) + 1, GetLength(selectTargets[mainSelection][1]));
		for(i = 0; i < cnt; ++i)
		{
			if(i < GetLength(selectTargets))
			{
				var obj = selectTargets[i][0];
				var caption = Format((selectTargets[i][2] && "·  %s") || "   %s", GetName(obj));
				if(i != mainSelection)
				{
					caption = Format("<c 808080>%s</c>", caption);
				}
				AddMenuItem(caption, "SelectTargetActionObject", GetID(obj), selectCaller, 0, i, 0, C4MN_Add_ForceNoDesc | C4MN_Add_ImgObject, obj);
			}
			else if(i == GetLength(selectTargets))
			{
				AddMenuItem("$Finish$", "SelectTargetAction2", GetID(), selectCaller, 0, -1, 0, C4MN_Add_ForceNoDesc);
			}
			else
			{
				AddMenuItem(0, " ", 0, selectCaller);
			}
			if(i < GetLength(selectTargets[mainSelection][1]))
			{
				var callback = selectTargets[mainSelection][1][i];
				var caption = Format((callback[10] && "× %s") || "   %s", callback[0]);
				AddMenuItem(caption, "SelectTargetAction2", callback[2] || GetID(selectTargets[mainSelection][0]), selectCaller, 0, i, 0, C4MN_Add_ForceNoDesc);
			}
			else
			{
				AddMenuItem(0, " ", 0, selectCaller);
			}
		}
		for(; i < selectTargetsMax; ++i)
		{
			AddMenuItem(0, " ", 0, selectCaller);
			AddMenuItem(0, " ", 0, selectCaller);
		}
		if(subSelection)
		{
			SelectMenuItem(subSelection * 2 - 1, selectCaller);
		}
		else
		{
			SelectMenuItem(mainSelection * 2, selectCaller);
		}
		lastMainRow = mainSelection;
		if(!GetEffect("IntShowSelection", this))
		{
			EffectCall(this, AddEffect("IntShowSelection", this, 100, 2, this), "Timer");
		}
	}
}

func FxIntShowSelectionTimer(object target, int effectNumber)
{
	var marker = EffectVar(0, target, effectNumber);
	if(!selectCaller || GetMenu(selectCaller) != SEN2)
	{
		if(marker)
		{
			RemoveObject(marker);
		}
		return FX_Execute_Kill;
	}

	if(GetMenuSelection(selectCaller) == GetLength(selectTargets) * 2 || !selectTargets[lastMainRow][0])
	{
		if(marker)
		{
			RemoveObject(marker);
		}
	}
	else
	{
		if(!marker)
		{
			marker = selectCaller->CreateSelectMark();
		}
		marker->MarkObject(selectTargets[lastMainRow][0]);
	}
	EffectVar(0, target, effectNumber) = marker;
}

func SelectTargetActionObject(id id, int index)
{
	for(var i = 0; i < GetLength(selectTargets[index][1]); ++i)
	{
		selectTargets[index][1][i][10] = false;
	}
	selectTargets[index][2] = 0;
	SelectTargetActionsSideBySide(lastMainRow);
}

func SelectTargetAction2(id id, int index)
{
	if(index != -1)
	{
		selectTargets[lastMainRow][2] += ((selectTargets[lastMainRow][1][index][10] = !selectTargets[lastMainRow][1][index][10]) * 2) - 1;
		SelectTargetActionsSideBySide(lastMainRow, index + 1);
	}
	else
	{
		for(var target in selectTargets)
		{
			if(target[2] > 0)
			{
				for(var trigger in selectTrigger)
				{
					for(var callback in target[1])
					{
						if(callback[10])
						{
							AddTargetAction(trigger, target[0], callback);
						}
					}
				}
			}
		}
		selectTargets = 0;
		selectTargetsMax = 0;
	}
}

local byMenuSelection, lastMainRow, lastSelectedCol;
func SelectMenuItem(int selection, object menuObject, bool redraw)
{
	if(!redraw)
	{
		byMenuSelection = true;
		var ret = _inherited(selection, menuObject);
		byMenuSelection = false;
		return ret;
	}
	else
	{
		return _inherited(selection, menuObject);
	}
}

func OnMenuSelection(int selection, object menuObject)
{
	if(!byMenuSelection)
	{
		if(GetMenu(menuObject) == SEN2)
		{
			if(!(selection % 2))
			{
				if(lastSelectedCol == 0)
				{
					if(selection/2 < GetLength(selectTargets))
					{
						CloseMenu(menuObject);
						SelectTargetActionsSideBySide(selection/2);
					}
					else if(selection/2 == GetLength(selectTargets) + 1)
					{
						SelectMenuItem(0, menuObject, true);
					}
					else if(selection/2 != GetLength(selectTargets))
					{
						SelectMenuItem((GetLength(selectTargets) - 1) * 2, menuObject, lastMainRow != (GetLength(selectTargets) - 1));
					}
				}
				else
				{
					SelectMenuItem(2 * lastMainRow, menuObject);
				}
				lastSelectedCol = 0;
			}
			else
			{
				if(lastSelectedCol == 0)
				{
					SelectMenuItem(1, menuObject);
				}
				else
				{
					if(selection/2 == GetLength(selectTargets[lastMainRow][1]))
					{
						SelectMenuItem(1, menuObject);
					}
					else if(selection/2 > GetLength(selectTargets[lastMainRow][1]))
					{
						SelectMenuItem(2 * GetLength(selectTargets[lastMainRow][1]) - 1, menuObject);
					}
				}
				lastSelectedCol = 1;
			}
		}
	}
}

func SelectTargetAction(id id, object target)
{
	if(CreateMenu(GetID(), selectCaller, this, C4MN_Extra_None, "$SelectAction$", 0, C4MN_Style_Context, 0))
	{
		var i = 0;
		selectTarget = target;
		selectCallbacks =  target->GetSensorCallbacks(this);
		for(var callback in selectCallbacks)
		{
			AddMenuItem(callback[0], "SetTargetAction", callback[2] || GetID(target), selectCaller, 0, i++, 0, C4MN_Add_ForceNoDesc);
		}
	}
}

func SetTargetAction(id id, int index)
{
	for(var trigger in selectTrigger)
	{
		AddTargetAction(trigger, selectTarget, selectCallbacks[index]);
	}
	selectTrigger = 0;
}

func AddTargetAction(int trigger, object target, callback)
{
	triggerCallbacks = triggerCallbacks || [];
	triggerCallbacks[trigger] = triggerCallbacks[trigger] || [];
	triggerCallbacks[trigger][GetLength(triggerCallbacks[trigger])] = [target, callback];
}

func Trigger(int index, object user)
{
	if(triggerCallbacks && GetType(triggerCallbacks[index]) == C4V_Array)
	{
		var ret = false, i = 0;
		for(var callback in triggerCallbacks[index])
		{
			if(GetType(callback) == C4V_Array)
			{
				if(CheckTarget(index, i))
				{
					ret = callback[0]->CallA(callback[1][1], CreateFilledArray(user, ...), true) || ret;
				}
			}
		}
		return ret;
	}
}

func CheckTarget(int trigger, int& index)
{
	if(!triggerCallbacks || !triggerCallbacks[trigger] || !triggerCallbacks[trigger][index] || !triggerCallbacks[trigger][index][0])
	{
		RemoveSensorTargetIndex(trigger, index);
		return false;
	}
	else
	{
		++index;
		return true;
	}
}

func ClearTrigger(int index)
{
	triggerCallbacks[index] = 0;
}

func UpdateTransferZone()
{
	ToggleDesc(0, 0, 0, true);
}

func IsAnvilProduct() { return GetID() != SN7I; }

func IsRemoteControllable() { return false; }

func IgnoreSensorIgnored() { return Find_Not(Find_Func("SensorIgnored")); }

func ClearCom(object caller)
{
	if(caller)
	{
		ClearLastPlrCom(GetController(caller));
	}
	return true;
}

func GetDescription()
{
	return desc;
}
