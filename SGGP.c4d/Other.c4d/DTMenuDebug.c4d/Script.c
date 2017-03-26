#strict 2

static const DT_Menu = MN7I;
static const DT_Menu_Combined = -1;

// Enums and bitfields

/*
static const DT_Menu_Settings_Symbol = 0;
static const DT_Menu_Settings_Object = 0 + 1;
static const DT_Menu_Settings_Extra = 0 + 1 + 1;
static const DT_Menu_Settings_Caption = 0 + 1 + 1 + 1;
static const DT_Menu_Settings_ExtraData = 0 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_Style = 0 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_KeepOpen = 0 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_Parent = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_Size = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_RefreshInterval = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_Selection = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_ConditionDisableMode = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_ConditionAllowSelection = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_Callbacks = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_Decoration = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_RequireAction = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Settings_KeepParentOnClose = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
*/

static const DT_Menu_Settings_Symbol = 0;
static const DT_Menu_Settings_Object = 1;
static const DT_Menu_Settings_Extra = 2;
static const DT_Menu_Settings_Caption = 3;
static const DT_Menu_Settings_ExtraData = 4;
static const DT_Menu_Settings_Style = 5;
static const DT_Menu_Settings_KeepOpen = 6;
static const DT_Menu_Settings_Parent = 7;
static const DT_Menu_Settings_Size = 8;
static const DT_Menu_Settings_RefreshInterval = 9;
static const DT_Menu_Settings_Selection = 10;
static const DT_Menu_Settings_ConditionDisableMode = 11;
static const DT_Menu_Settings_ConditionAllowSelection = 12;
static const DT_Menu_Settings_Callbacks = 13;
static const DT_Menu_Settings_Decoration = 14;
static const DT_Menu_Settings_RequireAction = 15;
static const DT_Menu_Settings_KeepParentOnClose = 16;

/*
static const DT_Menu_KeepOpen_Not = 0x0;
static const DT_Menu_KeepOpen_Keep = 0x1;
static const DT_Menu_KeepOpen_Force = 0x2;
static const DT_Menu_KeepOpen_Permanent = 0x2 << 1;
static const DT_Menu_KeepOpen_Refresh = 0x2 << 1 << 1;
static const DT_Menu_KeepOpen_RefreshContinously = 0x2 << 1 << 1 << 1;
static const DT_Menu_KeepOpen_Refresh_Mask = 24; // DT_Menu_KeepOpen_Refresh | DT_Menu_KeepOpen_RefreshContinously
*/

static const DT_Menu_KeepOpen_Not = 0;
static const DT_Menu_KeepOpen_Keep = 1;
static const DT_Menu_KeepOpen_Force = 2;
static const DT_Menu_KeepOpen_Permanent = 4;
static const DT_Menu_KeepOpen_Refresh = 8;
static const DT_Menu_KeepOpen_RefreshContinously = 16;
static const DT_Menu_KeepOpen_Refresh_Mask = 24; // DT_Menu_KeepOpen_Refresh | DT_Menu_KeepOpen_RefreshContinously

/*
static const DT_Menu_Type_Setting = 0;
static const DT_Menu_Type_Entry = 0 + 1;
static const DT_Menu_Type_Factory = 0 + 1 + 1;
*/

//static const DT_Menu_Type_Combined = -1;
static const DT_Menu_Type_Setting = 0;
static const DT_Menu_Type_Entry = 1;
static const DT_Menu_Type_Factory = 2;

/*
static const DT_Menu_Action_Normal = 0;
static const DT_Menu_Action_Special2 = 0 + 1;
static const DT_Menu_Action_Close = 0 + 1 + 1;
*/

static const DT_Menu_Action_Normal = 0;
static const DT_Menu_Action_Special2 = 1;
static const DT_Menu_Action_Close = 2;

/*
static const DT_Menu_Callback_MenuObject = -3;
static const DT_Menu_Callback_Global = -3 + 1;
static const DT_Menu_Callback_Scenario = -3 + 1 + 1;
*/

static const DT_Menu_Callback_MenuObject = -3;
static const DT_Menu_Callback_Scenario = -2;
static const DT_Menu_Callback_Global = -1;

/*
static const Menu_React_Menu_React_Override = -1;
static const Menu_React_None = -1 + 1;
static const Menu_React_Close = -1 + 1 + 1;
static const Menu_React_Refresh = -1 + 1 + 1 + 1;
static const Menu_React_KeepOpen = -1 + 1 + 1 + 1 + 1;
static const Menu_React_Back = -1 + 1 + 1 + 1 + 1 + 1;
static const Menu_React_SelectionOffset = -1 + 1 + 1 + 1 + 1 + 1 + 1;
static const Menu_React_SelectionChange = -1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const Menu_React_ShowSubmenu = -1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
*/

static const Menu_React_OverrideReaction = -1;
static const Menu_React_None = 0;
static const Menu_React_Close = 1;
static const Menu_React_Refresh = 2;
static const Menu_React_KeepOpen = 3;
static const Menu_React_Back= 4;
static const Menu_React_SelectionOffset = 5;
static const Menu_React_SelectionChange = 6;
static const Menu_React_ShowSubmenu = 7;
	static const Menu_React_Max = Menu_React_ShowSubmenu;

global func Menu_React_OffsetSelection(int offset) { return [Menu_React_SelectionOffset, offset]; }
global func Menu_React_OverrideSelection(int override) { return [Menu_React_SelectionChange, override]; }
global func Menu_React_Override(override) { return [Menu_React_OverrideReaction, override]; }

/*
static const Menu_ConditionReact_Default = 0;
static const Menu_ConditionReact_Show = 0 + 1;
static const Menu_ConditionReact_Hide = 0 + 1 + 1;
static const Menu_ConditionReact_GrayOut = 0 + 1 + 1 + 1;
static const Menu_ConditionReact_CustomFormat = 0 + 1 + 1 + 1 + 1;
*/

static const Menu_ConditionReact_Default = 0;
static const Menu_ConditionReact_Show = 1;
static const Menu_ConditionReact_Hide = 2;
static const Menu_ConditionReact_GrayOut = 3;
static const Menu_ConditionReact_CustomFormat = 4;
	static const Menu_ConditionReact_Max = Menu_ConditionReact_GrayOut;

global func Menu_ConditionReact_CustomColor(int color) { return [Menu_ConditionReact_CustomFormat, Format("<c %x>%%s</c>", color)]; }
global func Menu_ConditionReact_Format(string format) { return [Menu_ConditionReact_CustomFormat, format]; }

/*
static const Menu_Condition_Default = 0;
static const Menu_Condition_AllowSelection = 0 + 1;
static const Menu_Condition_DenySelection = 0 + 1 + 1;
*/

static const Menu_Condition_Default = 0;
static const Menu_Condition_AllowSelection = 1;
static const Menu_Condition_DenySelection = 2;
	static const Menu_Condition_Max = 2;

/*
static const DT_Menu_Entry_Caption = 0;
static const DT_Menu_Entry_Callbacks = 0 + 1;
static const DT_Menu_Entry_Symbol = 0 + 1 + 1;
static const DT_Menu_Entry_Count = 0 + 1 + 1 + 1;
static const DT_Menu_Entry_InfoCaption = 0 + 1 + 1 + 1 + 1;
static const DT_Menu_Entry_Extra = 0 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Entry_XPar1 = 0 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Entry_XPar2 = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Entry_Args = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Entry_Condition = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Entry_Placeholder = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
*/

static const DT_Menu_Entry_Caption = 0;
static const DT_Menu_Entry_Callbacks = 1;
static const DT_Menu_Entry_Symbol = 2;
static const DT_Menu_Entry_Count = 3;
static const DT_Menu_Entry_InfoCaption = 4;
static const DT_Menu_Entry_Extra = 5;
static const DT_Menu_Entry_XPar1 = 6;
static const DT_Menu_Entry_XPar2 = 7;
static const DT_Menu_Entry_Args = 8;
static const DT_Menu_Entry_Condition = 9;
static const DT_Menu_Entry_Placeholder = 10;

/*
 static const Menu_CallbackType_None = 0x0;
static const Menu_CallbackType_Special2 = 0x1;
static const Menu_CallbackType_Normal = 0x2;
static const Menu_CallbackType_Close = 0x2 << 1;
static const Menu_CallbackType_Selection = 0x2 << 1 << 1;
static const Menu_CallbackType_Deselection = 0x2 << 1 << 1 << 1;
static const Menu_CallbackType_ValueChanged = 0x2 << 1 << 1 << 1 << 1;
static const Menu_CallbackType_InputAborted = 0x2 << 1 << 1 << 1 << 1 << 1;
static const Menu_CallbackType_Defaults = 0x3; // Menu_CallbackType_Normal | Menu_CallbackType_Special2
static const Menu_CallbackType_All = 0x7f; // Menu_CallbackType_Normal | Menu_CallbackType_Special2 | Menu_CallbackType_Close | Menu_CallbackType_Selection | Menu_CallbackType_Deselection | Menu_CallbackType_ValueChanged | Menu_CallbackType_InputAborted
*/

static const Menu_CallbackType_None = 0x0;
static const Menu_CallbackType_Special2 = 0x1;
static const Menu_CallbackType_Normal = 0x2;
static const Menu_CallbackType_Close = 0x4;
static const Menu_CallbackType_Selection = 0x8;
static const Menu_CallbackType_Deselection = 0x10;
static const Menu_CallbackType_ValueChanged = 0x20;
static const Menu_CallbackType_InputAborted = 0x40;
static const Menu_CallbackType_Defaults = 0x3; // Menu_CallbackType_Normal | Menu_CallbackType_Special2
static const Menu_CallbackType_All = 0x7f; // Menu_CallbackType_Normal | Menu_CallbackType_Special2 | Menu_CallbackType_Close | Menu_CallbackType_Selection | Menu_CallbackType_Deselection | Menu_CallbackType_ValueChanged | Menu_CallbackType_InputAborted


/*
static const Menu_AdaptorType_Boolean = 0;
static const Menu_AdaptorType_Integer = 0 + 1;
static const Menu_AdaptorType_String = 0 + 1 + 1;
static const Menu_AdaptorType_ID = 0 + 1 + 1 + 1;
static const Menu_AdaptorType_Enum = 0 + 1 + 1 + 1 + 1;
static const Menu_AdaptorType_BitField = 0 + 1 + 1 + 1 + 1 + 1;
*/

static const Menu_AdaptorType_Boolean = 0;
static const Menu_AdaptorType_Integer = 1;
static const Menu_AdaptorType_String = 2;
static const Menu_AdaptorType_ID = 3;
static const Menu_AdaptorType_Enum = 4;
static const Menu_AdaptorType_BitField = 5;

/*
static const DT_Menu_Adaptor_Type = 0;
static const DT_Menu_Adaptor_Variable = 0 + 1;
static const DT_Menu_Adaptor_Callbacks = 0 + 1 + 1;
static const DT_Menu_Adaptor_MessageBoardText = 0 + 1 + 1 + 1;
static const DT_Menu_Adaptor_Limits = 0 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_StepSize = 0 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_LayoutVals = 0 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_NoEmptyString = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_EntryIndex = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_Bit = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_WrapAround = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_Args = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_EnumSubmenu = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_EnumSubmenuCaption = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
static const DT_Menu_Adaptor_EnumSubmenuSymbol = 0 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
*/

static const DT_Menu_Adaptor_Type = 0;
static const DT_Menu_Adaptor_Variable = 1;
static const DT_Menu_Adaptor_Callbacks = 2;
static const DT_Menu_Adaptor_MessageBoardText = 3;
static const DT_Menu_Adaptor_Limits = 4;
static const DT_Menu_Adaptor_StepSize = 5;
static const DT_Menu_Adaptor_LayoutVals = 6;
static const DT_Menu_Adaptor_NoEmptyString = 7;
static const DT_Menu_Adaptor_EntryIndex = 8;
static const DT_Menu_Adaptor_Bit = 9;
static const DT_Menu_Adaptor_WrapAround = 10;
static const DT_Menu_Adaptor_Args = 11;
static const DT_Menu_Adaptor_EnumSubmenu = 12;
static const DT_Menu_Adaptor_EnumSubmenuCaption = 13;
static const DT_Menu_Adaptor_EnumSubmenuSymbol = 14;


static const Menu_Layout_Symbol = 1;
static const Menu_Layout_InfoCaption = 2;

static const Menu_Layout__CaptionPos = 3;
static const Menu_Layout__ValuePos = 4;
// static const Menu_Layout__InputValuePos = 5; TODO

static const Menu_Layout_Caption = 4;
static const Menu_Layout_Value = 8;
// static const Menu_Layout_InputValue = 16; TODO
static const Menu_Layout__NoFlagMask = 3;

// ----------------------------------------------------------------------------


local settings;
local entries;
local createEntries;
local entryCount;
local currentSelection;
local suspended;
local closing;
local selectionOffset;
local selectionOverride;
local msgBoardMode;
local msgBoardEntry;
local noSelectionCallbacks;
local subMenu;

func Initialize()
{

}

func Destruction()
{
	Close();
}

func Create(array cSettings, array cEntries)
{
	settings = cSettings;
	entries = [];
	createEntries = cEntries;
	currentSelection = -1;
	settings[DT_Menu_Settings_ConditionDisableMode] = settings[DT_Menu_Settings_ConditionDisableMode] || Menu_ConditionReact_Hide;

	if(settings[DT_Menu_Settings_Parent]) settings[DT_Menu_Settings_Parent]->Suspend();

	if(!(settings[DT_Menu_Settings_Object])) { FatalError("Assertion failed: CreateNewMenu: menu object is missing; assertion code: settings[DT_Menu_Settings_Object]"); }
	CreateMenu(settings[DT_Menu_Settings_Symbol], settings[DT_Menu_Settings_Object], this, settings[DT_Menu_Settings_Extra], settings[DT_Menu_Settings_Caption], settings[DT_Menu_Settings_ExtraData], settings[DT_Menu_Settings_Style], true, MN7I);

	if(GetType(settings[DT_Menu_Settings_Size]) == C4V_Array) SetMenuSize(settings[DT_Menu_Settings_Size][0], settings[DT_Menu_Settings_Size][1], settings[DT_Menu_Settings_Object]);

	entryCount = 0;
	AddEntries(cEntries, entryCount);

	SelectEntry(settings[DT_Menu_Settings_Selection]);

	if(settings[DT_Menu_Settings_Decoration])
	{
		SetMenuDecoration(settings[DT_Menu_Settings_Decoration], settings[DT_Menu_Settings_Object]);
	}

	if(!GetEffect("Menu", this)) AddEffect("Menu", this, 1, 1, this, 0);
}

func SelectEntry(int selection)
{
	if(selection < 0) selection = entryCount + selection;
	if(!(selection >= 0 && selection < entryCount)) { FatalError("Assertion failed: SelectEntry: selection index out of range; assertion code: selection >= 0 && selection < entryCount"); }
	SelectMenuItem(selection, settings[DT_Menu_Settings_Object]);
}

func ActivateEntry(int index, int action)
{
	if(index < 0) index = entryCount + index;
	if(index >= entryCount || index < 0)
	{
	Log("WARNING: ActivateEntry: index out of range: %d", index);
		return;
	}

	SelectEntry(index);

	var entry = entries[index];
	if(entry[0] == DT_Menu_Type_Entry)
	{
		MenuItemCommand(entry[1][DT_Menu_Entry_Symbol], index, action);
	}
	else
	{
		Log("WARNING: ActivateEntry: entry on index is not of type DT_Menu_Type_Entry");
	}
}

/*func FxMenuStart(object target, int effectNumber, int temp)
{

}*/

func FxMenuTimer(object target, int effectNumber, int effectTime)
{
	if(!settings[DT_Menu_Settings_Object])
	{
		return Close();
	}
	else if(settings[DT_Menu_Settings_RequireAction])
	{
		var obj = settings[DT_Menu_Settings_Object];
		var requirement = settings[DT_Menu_Settings_RequireAction];
		if(GetAction(obj) != requirement[0] || (requirement[1] && GetActionTarget(0, obj) != requirement[1]))
		{
			return Close();
		}
	}

	if(suspended) return;

	if(msgBoardMode != 0 && !TestMessageBoard(GetOwner(settings[DT_Menu_Settings_Object]), true))
	{
		var entry = entries[msgBoardEntry];
		var args = entry[1][DT_Menu_Entry_Args];
		var reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], Menu_CallbackType_InputAborted, [Menu_CallbackType_InputAborted, entry[1][DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Args]]);
		if(reaction != Menu_React_None)
		{
			React(reaction, msgBoardEntry);
		}
		msgBoardMode = 0;
	}

	if(!GetMenu(settings[DT_Menu_Settings_Object]))
	{
		if(settings[DT_Menu_Settings_KeepOpen] & (DT_Menu_KeepOpen_Refresh_Mask | DT_Menu_KeepOpen_Force))
		{
			Refresh(currentSelection);
		}
		else
		{
			return FX_Execute_Kill;
		}
	}

	if(settings[DT_Menu_Settings_KeepOpen] & DT_Menu_KeepOpen_RefreshContinously && !(effectTime % settings[DT_Menu_Settings_RefreshInterval]))
	{
		Refresh(currentSelection);
	}
}

func FxMenuStop(object target, int effectNumber, int reason, bool temp)
{
	if(temp)
	{
		return;
	}
	CloseMenu(settings[DT_Menu_Settings_Object]);
	if(settings[DT_Menu_Settings_Parent]) settings[DT_Menu_Settings_Parent]->Suspend(true);
	RemoveObject(this);
}

func CallCallbacks(array callbacks, int type, args, defaultRet, bool noGlobalCallbacks)
{
	var ret = defaultRet;
	if(callbacks)
	{
		for(var callback in callbacks)
		{
			if(callback[1] & type)
			{
				ret = CallA(callback[0], args);
				break;
			}
		}
	}

	if(!(!ret || (GetType(ret) == C4V_Int && ret > 0 && ret <= Menu_React_Max) || (GetType(ret) == C4V_Array && ret[0] > 0 && ret[0] <= Menu_React_Max && (!ret[1] || GetType(ret[1]) == C4V_Int)))) { FatalError(Format("Assertion failed: CallCallbacks: invalid return value detected: %v; assertion code: !ret || (GetType(ret) == C4V_Int && ret > 0 && ret <= Menu_React_Max) || (GetType(ret) == C4V_Array && ret[0] > 0 && ret[0] <= Menu_React_Max && (!ret[1] || GetType(ret[1]) == C4V_Int))", ret)); }

	if(!noGlobalCallbacks)
	{
		var globalRet = CallCallbacks(settings[DT_Menu_Settings_Callbacks], type, [ret, args], defaultRet, true);
		if(GetType(globalRet) == C4V_Array && globalRet[0] == Menu_React_OverrideReaction)
		{
			ret = globalRet[1];
	if(!(!ret || (GetType(ret) == C4V_Int && ret > 0 && ret <= Menu_React_Max) || (GetType(ret) == C4V_Array && ret[0] > 0 && ret[0] <= Menu_React_Max && (!ret[1] || GetType(ret[1]) == C4V_Int)))) { FatalError(Format("Assertion failed: CallCallbacks: invalid return value detected: %v; assertion code: !ret || (GetType(ret) == C4V_Int && ret > 0 && ret <= Menu_React_Max) || (GetType(ret) == C4V_Array && ret[0] > 0 && ret[0] <= Menu_React_Max && (!ret[1] || GetType(ret[1]) == C4V_Int))", ret)); }
		}
	else if(globalRet)
		{
			Log("WARNING: CallCallbacks: ignoring non-zero return value of global callback because override is not specified: %v", globalRet);
		}
	}

	return ret;
}

func Close(bool closeParents)
{
	closing = true;
	if(subMenu)
	{
		subMenu->Close();
	}
	if(closeParents && settings[DT_Menu_Settings_Parent]) settings[DT_Menu_Settings_Parent]->Close(true);
	RemoveEffect("Menu", this);
}

func Suspend(bool cont)
{
	if(suspended == !cont) return;
	if(suspended = !cont)
	{
		CloseMenu(settings[DT_Menu_Settings_Object]);
	}
	else if(!closing)
	{
		Refresh(currentSelection);
	}
}

func AddEntries(array entries, &i)
{
	for(var entry in entries)
	{
		if(entry[0] == DT_Menu_Type_Entry)
		{
			var condition = entry[1][DT_Menu_Entry_Condition], conditionRet;
			var caption = entry[1][DT_Menu_Entry_Caption], noCommand = !entry[1][DT_Menu_Entry_Placeholder] || (entry[1][DT_Menu_Entry_Placeholder] != true && !entry[1][DT_Menu_Entry_Callbacks]);
			if(condition)
			{
				if(noCommand || condition[1] == Menu_Condition_DenySelection || (condition[1] == Menu_Condition_Default && !settings[DT_Menu_Settings_ConditionAllowSelection]))
				{
					noCommand = true;
				}

				conditionRet = CallA(condition[0], [entry[1][DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[1][DT_Menu_Entry_Args]]) || settings[DT_Menu_Settings_ConditionDisableMode];
				if(conditionRet == Menu_ConditionReact_Hide)
				{
					continue;
				}
				else if(conditionRet == Menu_ConditionReact_GrayOut)
				{
					caption = Format("<c 808080>%s</c>", caption);
				}
				else if(GetType(conditionRet) == C4V_Array && conditionRet[0] == Menu_ConditionReact_CustomFormat)
				{
					caption = Format(conditionRet[1], caption);
				}
				else
				{
					noCommand = false;
				}
			}

			var symbol = entry[1][DT_Menu_Entry_Symbol], symbolID = 0;
			if(GetType(symbol) == C4V_Array)
			{
				if(GetType(symbol[0]) == C4V_C4ID)
				{
					symbolID = symbol[0];
					if(symbol[1])
					{
						entry[1][DT_Menu_Entry_Extra] |= C4MN_Add_ImgIndexed;
						entry[1][DT_Menu_Entry_XPar1] = symbol[1];
					}
				}
				else if(GetType(symbol[0]) == C4V_C4Object)
				{
					entry[1][DT_Menu_Entry_Extra] |= C4MN_Add_ImgObject;
					entry[1][DT_Menu_Entry_XPar1] = symbol[0];
					symbolID = GetID(symbol[0]);
				}
			}
			else
			{
				symbolID = symbol;
			}
			entry[1][DT_Menu_Entry_Symbol] = symbolID;

			LocalN("entries")[i] = entry;
			AddMenuItem(caption, !noCommand && "MenuItemCommand", symbolID, settings[DT_Menu_Settings_Object], entry[1][DT_Menu_Entry_Count], i++, entry[1][DT_Menu_Entry_InfoCaption], entry[1][DT_Menu_Entry_Extra], entry[1][DT_Menu_Entry_XPar1], entry[1][DT_Menu_Entry_XPar2]);

			if(GetType(symbol) == C4V_Array && GetType(symbol[0]) == C4V_C4Object && symbol[1])
			{
				RemoveObject(symbol[0]);
			}
		}
		else if(entry[0] == DT_Menu_Type_Factory)
		{
			for(var callback in entry[1][0])
			{
				var factoryResult = CallA(callback, [entry[1][1], i]);
				if(GetType(factoryResult) == C4V_Array)
				{
					var newEntries = [];
					UncombineAndDistinguish(factoryResult, settings, newEntries);
					AddEntries(newEntries, i);
				}
				else if(factoryResult == Menu_React_Close)
				{
					return Close();
				}
	else
				{
					Log("WARNING: AddEntries: ignoring invalid return value of Factory: %v (%v)", factoryResult, callback);
				}
			}
		}
	}
}

func React(reaction, int itemNumber, int refreshDelayed)
{
	if(reaction == Menu_React_Close)
	{
		Close(!settings[DT_Menu_Settings_KeepParentOnClose]);
	}
	else if(reaction == Menu_React_Back)
	{
		Close();
	}
	else if(reaction == Menu_React_Refresh || (settings[DT_Menu_Settings_KeepOpen] & DT_Menu_KeepOpen_Refresh))
	{
		Refresh(itemNumber, refreshDelayed);
	}
	else if(reaction == Menu_React_KeepOpen && (settings[DT_Menu_Settings_KeepOpen] == DT_Menu_KeepOpen_Not || settings[DT_Menu_Settings_KeepOpen] == DT_Menu_KeepOpen_Permanent))
	{
// 		Refresh(itemNumber, refreshDelayed);
	}
	else if(GetType(reaction) == C4V_Array)
	{
		if(reaction[0] == Menu_React_SelectionOffset)
		{
			selectionOffset = reaction[1];
		}
		else if(reaction[0] == Menu_React_SelectionChange)
		{
			selectionOverride = reaction[1] + 1;
		}
	}
}

func CheckCondition(array entry)
{
	var condition = entry[DT_Menu_Entry_Condition];
	return !condition || (CallA(condition[0], [entry[DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Args]]) || settings[DT_Menu_Settings_ConditionDisableMode]) == Menu_ConditionReact_Show;
}

func MenuItemCommand(id ID, int itemNumber, int action)
{
	var entry = entries[itemNumber];
	var condition = entry[1][DT_Menu_Entry_Condition];
	action = action || Menu_CallbackType_Normal;
	var reaction;
	if(CheckCondition(entry[1]))
	{
		reaction = CallCallbacks(entry[1][DT_Menu_Entry_Callbacks], action, [action, ID, settings[DT_Menu_Settings_Object], entry[1][DT_Menu_Entry_Args]]);
	}
	else
	{
		if(condition[1] == Menu_Condition_AllowSelection)
		{
			reaction = Menu_React_KeepOpen;
		}
		else
		{
			reaction = Menu_React_Refresh;
		}
	}
	React(reaction, itemNumber);
}

func SubmenuItemCallback(int action, id ID, object menuObject, args)
{
	var reaction = CallCallbacks(args[0], action, CreateFilledArray(action, ID, menuObject, args[1], ...), Menu_React_None);

	if(((action & Menu_CallbackType_Defaults) && reaction == Menu_React_None) || reaction == Menu_React_ShowSubmenu)
	{
		subMenu = CreateNewMenu(args[2], settings, this);
		return Menu_React_None;
	}
	else
	{
		return reaction;
	}
}

func MenuQueryCancel(int selection, object menuObject)
{
	if(selection != -1)
	{
		var entry = entries[selection];
		var reaction;
		if(entry[0] == DT_Menu_Type_Entry)
		{
			if(CheckCondition(entry[1]))
			{
				reaction = CallCallbacks(entry[1][DT_Menu_Entry_Callbacks], Menu_CallbackType_Close, [Menu_CallbackType_Close, entry[1][DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[1][DT_Menu_Entry_Args]]);
			}
		}

		React(reaction, selection, true);
	}

	if(settings[DT_Menu_Settings_KeepOpen] != DT_Menu_KeepOpen_Not && settings[DT_Menu_Settings_KeepOpen] != DT_Menu_KeepOpen_Permanent)
	{
		return true;
	}
}

func OnMenuSelection(int selection, object menuObject)
{
	if(!(selection < GetLength(entries))) { FatalError("Assertion failed: OnMenuSelection: Menu selection out of range. Was the menu modified manually?; assertion code: selection < GetLength(entries)"); }
	if(selection != currentSelection)
	{
		var oldSelection = currentSelection;
		var entry = entries[currentSelection];
		if(!noSelectionCallbacks && entry[0] == DT_Menu_Type_Entry && CheckCondition(entry[1]) && currentSelection != -1)
		{
			CallCallbacks(entry[1][DT_Menu_Entry_Callbacks], Menu_CallbackType_Deselection, [Menu_CallbackType_Deselection, entry[1][DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[1][DT_Menu_Entry_Args], oldSelection, selection]);
		}
		entry = entries[currentSelection = selection];
		if(!noSelectionCallbacks && entry[0] == DT_Menu_Type_Entry && CheckCondition(entry[1]))
		{
			CallCallbacks(entry[1][DT_Menu_Entry_Callbacks], Menu_CallbackType_Selection, [Menu_CallbackType_Selection, entry[1][DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[1][DT_Menu_Entry_Args], selection, oldSelection]);
		}
	}
}

func Refresh(int selection, bool delayed)
{
	if(suspended)
	{
		return;
	}

	if(delayed)
	{
		ScheduleCall(this, "Refresh", 1, 0, selection);
	}
	else
	{
		var disabledCallbacks;
		if(!noSelectionCallbacks)
		{
			disabledCallbacks = noSelectionCallbacks = true;
		}

		CloseMenu(settings[DT_Menu_Settings_Object]);
		Create(settings, createEntries);
		var newSelection = selection;
		selectionOverride && (newSelection = selectionOverride-1);
		SelectEntry(BoundBy(newSelection + selectionOffset, 0, entryCount-1));
		selectionOffset = 0;
		selectionOverride = 0;

		if(disabledCallbacks)
		{
			noSelectionCallbacks = false;
		}
	}
}

// ----------------------------------------------------------------------------

global func Menu__Setting(array setting) { return [DT_Menu_Type_Setting, setting]; }

global func Menu_Symbol(id symbol) { return Menu__Setting([DT_Menu_Settings_Symbol, symbol]); }
global func Menu_Object(object obj) { return Menu__Setting([DT_Menu_Settings_Object, obj]); }
global func Menu__Extra(int extra, int data) { return Menu_Combined([Menu__Setting([DT_Menu_Settings_Extra, extra]), Menu_ExtraData(data)]); }
global func Menu_Size(int width, int height) { 	if(!(width >= 0 && height >= 0)) { FatalError("Assertion failed: Menu_Size: Negative Menu_Size doesn't make sense; assertion code: width >= 0 && height >= 0"); }return Menu__Setting([DT_Menu_Settings_Size, [width, height]]); }
global func Menu_ExtraData(int data) { return Menu__Setting([DT_Menu_Settings_ExtraData, data]); }
global func Menu_Caption(string caption) { return Menu__Setting([DT_Menu_Settings_Caption, caption]); }
global func Menu_RefreshInterval(int interval) { 	if(!(interval >= 0)) { FatalError("Assertion failed: Menu_RefreshInterval: Negative interval doesn't make sense; assertion code: interval >= 0"); }return Menu__Setting([DT_Menu_Settings_RefreshInterval, interval + !interval]); }
global func Menu_Selection(int selection) { return Menu__Setting([DT_Menu_Settings_Selection, selection]); }
global func Menu__Style(int style) { return Menu__Setting([DT_Menu_Settings_Style, style]); }
global func Menu__KeepOpen(int mode) { return Menu__Setting([DT_Menu_Settings_KeepOpen, mode]); }

global func Menu_Extra_None() { return Menu__Extra(C4MN_Extra_None); }
global func Menu_Extra_Components() { return Menu__Extra(C4MN_Extra_Components); }
global func Menu_Extra_Value() { return Menu__Extra(C4MN_Extra_Value); }
global func Menu_Extra_MagicValue(int compare) { return Menu__Extra(C4MN_Extra_MagicValue, compare); }
global func Menu_Extra_Info() { return Menu__Extra(C4MN_Extra_Info); }
global func Menu_Extra_ComponentsMagic() { return Menu__Extra(C4MN_Extra_ComponentsMagic); }

global func Menu_Style_Normal() { return Menu__Style(C4MN_Style_Normal); }
global func Menu_Style_Context() { return Menu__Style(C4MN_Style_Context); }
global func Menu_Style_Info() { return Menu__Style(C4MN_Style_Info); }
global func Menu_Style_Dialog() { return Menu__Style(C4MN_Style_Dialog); }
global func Menu_Style_EqualItemHeight() { return Menu__Style(C4MN_Style_EqualItemHeight); }

global func Menu_DontKeepOpen() { return Menu__KeepOpen(DT_Menu_KeepOpen_Not); }
global func Menu_KeepOpen() { return Menu__KeepOpen(DT_Menu_KeepOpen_Keep); }
global func Menu_ForceKeepOpen() { return Menu__KeepOpen(DT_Menu_KeepOpen_Force); }
global func Menu_Refresh() { return Menu__KeepOpen(DT_Menu_KeepOpen_Refresh); }
global func Menu_RefreshContinously(int interval) { return Menu_Combined([Menu__KeepOpen(DT_Menu_KeepOpen_RefreshContinously), Menu_RefreshInterval(interval)]); }
global func Menu_Permanent() { return Menu__KeepOpen(DT_Menu_KeepOpen_Permanent); }

global func Menu_ConditionAllowSelection() { return Menu__Setting([DT_Menu_Settings_ConditionAllowSelection, true]);}
global func Menu_ConditionDenySelection() { return Menu__Setting([DT_Menu_Settings_ConditionAllowSelection, false]);}

global func Menu_Callbacks(array callbacks) { 	MN7I->ValidateMenuCallbacks(callbacks); return Menu__Setting([DT_Menu_Settings_Callbacks, callbacks]); }
global func Menu_Decoration(id decoration) { 	MN7I->ValidateDeco(decoration); return Menu__Setting([DT_Menu_Settings_Decoration, decoration]); }
global func Menu_RequireAction(string action, object target) { 	if(!(action)) { FatalError("Assertion failed: Menu_RequireAction: action is mandatory; assertion code: action"); }return Menu__Setting([DT_Menu_Settings_RequireAction, [action, target]]); }
global func Menu_KeepParentOnClose(bool dontKeep) { return Menu__Setting([DT_Menu_Settings_KeepParentOnClose, !dontKeep]);  }
global func Menu_ConditionDisableMode(mode) { 	if(!(!mode || (GetType(mode) == C4V_Int && mode >= 0 && mode <= Menu_ConditionReact_Max) || (GetType(mode) == C4V_Array && mode[0] == Menu_ConditionReact_CustomFormat && GetType(mode[1]) == C4V_String))) { FatalError("Assertion failed: Menu_ConditionDisableMode: invalid mode; assertion code: !mode || (GetType(mode) == C4V_Int && mode >= 0 && mode <= Menu_ConditionReact_Max) || (GetType(mode) == C4V_Array && mode[0] == Menu_ConditionReact_CustomFormat && GetType(mode[1]) == C4V_String)"); }return Menu__Setting([DT_Menu_Settings_ConditionDisableMode, mode]);}

global func Menu_Callback(array callback, int types)
{
	MN7I->ValidateMenuCallback(callback);
	if(!((types & ~Menu_CallbackType_All) == 0)) { FatalError("Assertion failed: Menu_Callback: invalid callback type(s) used; assertion code: (types & ~Menu_CallbackType_All) == 0"); }
	return [callback, types || Menu_CallbackType_Defaults];
}

global func Menu_Entry_Caption(string Caption) { return [DT_Menu_Entry_Caption, Caption]; }
global func Menu_Entry_Callbacks(array Callbacks) { return [DT_Menu_Entry_Callbacks, Callbacks]; }
global func Menu_Entry_Count(int Count) { return [DT_Menu_Entry_Count, Count]; }
global func Menu_Entry_InfoCaption(string InfoCaption) { return [DT_Menu_Entry_InfoCaption, InfoCaption]; }
global func Menu_Entry_Extra(int Extra) { return [DT_Menu_Entry_Extra, Extra]; }
global func Menu_Entry_XPar1(XPar1) { return [DT_Menu_Entry_XPar1, XPar1]; }
global func Menu_Entry_XPar2(XPar2) { return [DT_Menu_Entry_XPar2, XPar2]; }
global func Menu_Entry_Args(Args) { return [DT_Menu_Entry_Args, Args]; }
global func Menu_Entry_Placeholder(bool Placeholder) { return [DT_Menu_Entry_Placeholder, Placeholder]; }
global func Menu_Entry_Symbol(symbol, extra)
{
	
	var checkSymbol, checkExtra;
	if(GetType(symbol) == C4V_Array)
	{
		checkSymbol = symbol[0];
		checkExtra = symbol[1];
	}
	else
	{
		checkSymbol = symbol;
		checkExtra = extra;
	}

		if(!(!checkSymbol || GetType(checkSymbol) == C4V_C4ID || GetType(checkSymbol) == C4V_C4Object)) { FatalError("Assertion failed: Menu_Entry_Symbol: Invalid symbol; assertion code: !checkSymbol || GetType(checkSymbol) == C4V_C4ID || GetType(checkSymbol) == C4V_C4Object"); }
	if(checkExtra)
	{
		if(GetType(checkSymbol) == C4V_C4ID)
		{
				if(!(GetType(checkExtra) == C4V_Int && checkExtra >= 0)) { FatalError("Assertion failed: Menu_Entry_Symbol: Only positive integers are allowed for symbol extra with symbol id; assertion code: GetType(checkExtra) == C4V_Int && checkExtra >= 0"); }
		}
		else
		{
				if(!(GetType(checkExtra) == C4V_Bool)) { FatalError("Assertion failed: Menu_Entry_Symbol: Only booleans are allowed for symbol extra with symbol object; assertion code: GetType(checkExtra) == C4V_Bool"); }
		}
	}

	if(GetType(symbol) == C4V_Array)
	{
		return [DT_Menu_Entry_Symbol, symbol];
	}
	else
	{
		return [DT_Menu_Entry_Symbol, [symbol, extra]];
	}
}
global func Menu_Entry_Condition(callback, int allowDisabledSelection) { 	MN7I->CheckCallback(callback); return [DT_Menu_Entry_Condition, [callback, allowDisabledSelection]]; }
global func Menu_Entry_VariableCondition(array scopedVar, compare, int disableMode, bool invert, int allowDisabledSelection)
{
	MN7I->CheckScopedVar(scopedVar);
	if(!(!disableMode || (GetType(disableMode) == C4V_Int && disableMode >= 0 && disableMode <= Menu_ConditionReact_Max) || (GetType(disableMode) == C4V_Array && disableMode[0] == Menu_ConditionReact_CustomFormat && GetType(disableMode[1]) == C4V_String))) { FatalError("Assertion failed: Menu_ConditionDisableMode: invalid disableMode; assertion code: !disableMode || (GetType(disableMode) == C4V_Int && disableMode >= 0 && disableMode <= Menu_ConditionReact_Max) || (GetType(disableMode) == C4V_Array && disableMode[0] == Menu_ConditionReact_CustomFormat && GetType(disableMode[1]) == C4V_String)"); }
	if(!(!allowDisabledSelection || (GetType(allowDisabledSelection) == C4V_Int && allowDisabledSelection >= 0 && allowDisabledSelection <= Menu_Condition_Max))) { FatalError("Assertion failed: Menu_ConditionAllowSelection: invalid allowDisabledSelection value; assertion code: !allowDisabledSelection || (GetType(allowDisabledSelection) == C4V_Int && allowDisabledSelection >= 0 && allowDisabledSelection <= Menu_Condition_Max)"); }
	return Menu_Entry_Condition(BindCallback(MN7I->MenuObjectCallback("VariableCondition"), [Bind(scopedVar), Bind(compare), Bind(disableMode), Bind(invert)]), allowDisabledSelection);
}
global func VariableCondition(array scopedVar, compare, int disableMode, bool invert)
{
	var disable = ScopedVar(scopedVar) != compare;
	if(invert)
	{
		disable = !disable;
	}
	if(disable)
	{
		return disableMode;
	}
	else

	{
		return Menu_ConditionReact_Show;
	}
}
global func Menu_Entry_Object(object obj)
{
	if(!(obj)) { FatalError("Assertion failed: Menu_Entry_Object: obj is mandatory; assertion code: obj"); }
	return Menu_Combined([Menu_Entry_Symbol(obj), Menu_Entry_Caption(GetName(obj)), Menu_Entry_InfoCaption(GetDesc(obj))]);
}

global func Menu_Entry(caption, array callback, id symbol, int count, string infoCaption, args, int extra, XPar1, XPar2)
{
	if(!caption)
	{
		caption = [Menu_Entry_Placeholder(false)];
	}
	if(GetType(caption) == C4V_Array) // then caption is an array of named args
	{
		var namedArgs = [];
		namedArgs[DT_Menu_Entry_Caption] = "";
		namedArgs[DT_Menu_Entry_Placeholder] = -1;
		MN7I->NamedArgs(caption, namedArgs);
		if(!namedArgs[DT_Menu_Entry_InfoCaption])
		{
			namedArgs[DT_Menu_Entry_Extra] |= C4MN_Add_ForceNoDesc;
		}
		return [DT_Menu_Type_Entry, namedArgs];
	}
	else // unnamed arguments for shorter code
	{
	Log("WARNING: Menu_Entry: Use of old notation is discouraged: %s", caption);
		var ret = [DT_Menu_Type_Entry, [caption || "", [Menu_Callback(callback)], symbol, count, infoCaption, extra, XPar1, XPar2, args]];
		ret[1][DT_Menu_Entry_Placeholder] = -1;
		if(!infoCaption)
		{
			ret[1][DT_Menu_Entry_Extra] |= C4MN_Add_ForceNoDesc;
		}
		return ret;
	}
}
global func Menu_AutoEntry(id_or_obj, array callbacks, int count)
{
	MN7I->ValidateMenuCallbacks(callbacks);
	var id, id_, obj;
	if(GetType(id_or_obj) == C4V_C4ID)
	{
		id_ = id = id_or_obj;
	}
	else if(GetType(id_or_obj) == C4V_C4Object)
	{
		obj = id_or_obj;
		id = GetID(obj);
	}
	else
	{
		FatalError("Menu_AutoEntry: No ID or object given.");
		return;
	}

	return [DT_Menu_Type_Entry, [GetName(obj, id_), callbacks, id, count, GetDesc(obj, id_)]];
}

global func Menu_SubMenu(array entrySettings, array menuEntry_Settings)
{
	if(!(entrySettings)) { FatalError("Assertion failed: Menu_SubMenu: Non-selectable placeholder as submenu entry doesn't make sense; assertion code: entrySettings"); }
	if(!(menuEntry_Settings && GetLength(menuEntry_Settings) > 0)) { FatalError("Assertion failed: Menu_SubMenu: Empty submenu doesn't make sense; assertion code: menuEntry_Settings && GetLength(menuEntry_Settings) > 0"); }
	var ret = Menu_Entry(entrySettings);
	ret[1][DT_Menu_Entry_Args] = [ret[1][DT_Menu_Entry_Callbacks], ret[1][DT_Menu_Entry_Args], menuEntry_Settings];
	ret[1][DT_Menu_Entry_Callbacks] = [Menu_Callback(MN7I->MenuObjectCallback("SubmenuItemCallback"), Menu_CallbackType_All)];
	return ret;
}

global func Menu_Factory(array callbacks, args)
{
	if(!(callbacks)) { FatalError("Assertion failed: Menu_Factory: callbacks are mandatory; assertion code: callbacks"); }
	return [DT_Menu_Type_Factory, [callbacks, args]];
}

global func Menu_Decline(array callbacks, string caption, string infoCaption, args)
{
	caption || (caption = "$Decline$");
	caption = Format("{{MN7I:2}} %s", caption);
	return Menu_Entry(caption, MN7I->MenuObjectCallback("DeclineAcceptCommand"), 0, 0, infoCaption, [callbacks, args]);
}

global func Menu_Accept(array callback, string caption, string infoCaption, args)
{
	caption || (caption = "$Accept$");
	caption = Format("{{MN7I:1}} %s", caption);
	return Menu_Entry(caption, MN7I->MenuObjectCallback("DeclineAcceptCommand"), 0, 0, infoCaption, [callback, args]);
}

global func Menu_Back(array callback, string caption, string infoCaption, args)
{
	caption || (caption = "$Back$");
	caption = Format("{{MN7I:5}} %s", caption);
	return Menu_Entry(caption, MN7I->MenuObjectCallback("BackCommand"), 0, 0, infoCaption, [callback, args]);
}

global func Menu_Adaptor_Type(int Type) { return [DT_Menu_Adaptor_Type, Type]; }
global func Menu_Adaptor_Variable(array Variable) { return [DT_Menu_Adaptor_Variable, Variable]; }
global func Menu_Adaptor_Callbacks(array Callbacks) { return [DT_Menu_Adaptor_Callbacks, Callbacks]; }
global func Menu_Adaptor_MessageBoardText(string MessageBoardText) { return [DT_Menu_Adaptor_MessageBoardText, MessageBoardText]; }
global func Menu_Adaptor_WrapAround(bool WrapAround) { return [DT_Menu_Adaptor_WrapAround, WrapAround]; }
global func Menu_Adaptor_EnumSubmenuSymbol(id EnumSubmenuSymbol) { return [DT_Menu_Adaptor_EnumSubmenuSymbol, EnumSubmenuSymbol]; }
global func Menu_Adaptor_EnumSubmenu(int callbackType) { 	if(!((callbackType & ~Menu_CallbackType_All) == 0)) { FatalError("Assertion failed: Menu_Adaptor_EnumSubmenu: invalid callback type(s) used; assertion code: (callbackType & ~Menu_CallbackType_All) == 0"); }return [DT_Menu_Adaptor_EnumSubmenu, callbackType]; }
global func Menu_Adaptor_Limits(int min, int max) { 	if(!(min <= max)) { FatalError("Assertion failed: Menu_Adaptor_Limits: max cannot be smaller than min; assertion code: min <= max"); }return [DT_Menu_Adaptor_Limits, [min, max]]; }
global func Menu_Adaptor_StepSize(int step, force) { 	if(!(step > 0)) { FatalError("Assertion failed: negative or zero step doesn't make sense; assertion code: step > 0"); }	if(!(force >= 0)) { FatalError("Assertion failed: negative force step doesn't make sense; assertion code: force >= 0"); }return [DT_Menu_Adaptor_StepSize, [step, force]]; }
global func Menu_Adaptor_Enum(array enumVals, array layout, bool valuesAsSeparateLists)
{
	MN7I->AdaptorLayout(layout, enumVals, valuesAsSeparateLists);
	return Menu_Combined([Menu_Adaptor_Type(Menu_AdaptorType_Enum), [DT_Menu_Adaptor_LayoutVals, [enumVals, layout]]]);
}
global func Menu_Adaptor_BitField(array fieldVals, array layout, bool valuesAsSeparateLists)
{
	MN7I->AdaptorLayout(layout, fieldVals, valuesAsSeparateLists);
	
	var valuePos = layout[Menu_Layout__ValuePos] - 1;
	for(var fieldPart in fieldVals)
	{
			if(!(fieldPart[valuePos] >= 0 && fieldPart[valuePos] < 32)) { FatalError("Assertion failed: Menu_Adaptor_Bitfield: Bit value out of range; assertion code: fieldPart[valuePos] >= 0 && fieldPart[valuePos] < 32"); }
	}

	return Menu_Combined([Menu_Adaptor_Type(Menu_AdaptorType_BitField), [DT_Menu_Adaptor_LayoutVals, [fieldVals, layout]]]);
}
global func Menu_Adaptor_NoEmptyString() { return [DT_Menu_Adaptor_NoEmptyString, true]; }
global func Menu_Adaptor_EnumSubmenuCaption(string menuCaption, string entryCaption)
{
	return [DT_Menu_Adaptor_EnumSubmenuCaption, [menuCaption, entryCaption]];
}
global func Menu_Adaptor_Boolean() { return Menu_Adaptor_Type(Menu_AdaptorType_Boolean); }
global func Menu_Adaptor_Integer() { return Menu_Adaptor_Type(Menu_AdaptorType_Integer); }
global func Menu_Adaptor_String() { return Menu_Adaptor_Type(Menu_AdaptorType_String); }
global func Menu_Adaptor_ID() { return Menu_Adaptor_Type(Menu_AdaptorType_ID); }

func AdaptorLayout(array& layout, array& vals, bool valuesAsSeparateLists)
{
	if(!(vals)) { FatalError("Assertion failed: AdaptorLayout: vals are mandatory; assertion code: vals"); }
	layout = layout || [Menu_Layout_Value | Menu_Layout_Caption];
	var layoutMap = [];
	var index = 1;
	for(var val in layout)
	{
		var noFlag = val & Menu_Layout__NoFlagMask;

		if(noFlag)
		{
			layoutMap[noFlag] = index;
		}

		if(val & Menu_Layout_Caption)
		{
			layoutMap[Menu_Layout__CaptionPos] = index;
		}

		if(val & Menu_Layout_Value)
		{
			layoutMap[Menu_Layout__ValuePos] = index;
		}

// 		if(val & Menu_Layout_InputValue) TODO
// 		{
// 			layoutMap[Menu_Layout__InputValuePos] = index;
// 		}

		++index;
	}
	if(!(layoutMap[Menu_Layout__ValuePos])) { FatalError("Assertion failed: AdaptorLayout: Menu_Layout_Value is mandatory; assertion code: layoutMap[Menu_Layout__ValuePos]"); }

	layout = layoutMap;

	if(valuesAsSeparateLists)
	{
		var tempVals = vals;
		var vals = [];

		for(var i = 0; i < GetLength(tempVals[0]); ++i)
		{
			vals[i] = [];

			for(var j = 0; j < GetLength(tempVals); ++j)
			{
				vals[i][j] = tempVals[j][i];
			}
		}
	}
	
	for(var fieldPart in vals)
	{
		if(layout[Menu_Layout_Symbol]) { Menu_Entry_Symbol(fieldPart[layout[Menu_Layout_Symbol] - 1]); }
	}

}

global func Menu_Adaptor(array entrySettings, array adaptorSettings)
{
	if(!(entrySettings)) { FatalError("Assertion failed: Menu_Adaptor: Non-selectable placeholder as adaptor entry doesn't make sense; assertion code: entrySettings"); }
	if(!(adaptorSettings && GetLength(adaptorSettings) > 0)) { FatalError("Assertion failed: Menu_Adaptor: Adaptor without settings doesn't make sense; assertion code: adaptorSettings && GetLength(adaptorSettings) > 0"); }
	var adaptorArgs = [];

	adaptorArgs[DT_Menu_Adaptor_WrapAround] = -1;
	adaptorArgs[DT_Menu_Adaptor_EnumSubmenu] = Menu_CallbackType_Special2;

	MN7I->NamedArgs(adaptorSettings, adaptorArgs);

	if(adaptorArgs[DT_Menu_Adaptor_WrapAround] == -1)
	{
				if(adaptorArgs[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Integer)
		{
			adaptorArgs[DT_Menu_Adaptor_WrapAround] = false;
		}
		else if(adaptorArgs[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Enum)
		{
			adaptorArgs[DT_Menu_Adaptor_WrapAround] = true;
		}
	}

	return Menu_Factory([MN7I->MenuObjectCallback("AdaptorFactory")], [Menu_Entry(entrySettings)[1], adaptorArgs, entrySettings]);
}

func EnumValPos(array enumVals, array layout, val)
{
	for(var i = 0; i < GetLength(enumVals); ++i)
	{
		if(enumVals[i][layout[Menu_Layout__ValuePos] - 1] == val)
		{
			return i;
		}
	}
	Log("WARNING: EnumValPos: Current value %v is not in enum: %v", val, enumVals);
	return -1;
}

func BooleanToggleCaption(bool val, string caption)
{
	val = !!val;
	return Format("{{MN7I:%d}} <c %x>%s</c>", [2, 1][val], [RGB(128, 128, 128), RGB(255, 255, 255)][val], caption);
}

func InlineSymbol(string& caption, symbol)
{
	caption = Format("{{%i:%d}} %s", symbol[0], symbol[1], caption);
}

func ExtraSymbol(string& caption, &symbol, extraSymbol)
{
	if(GetType(extraSymbol) == C4V_C4ID)
	{
		extraSymbol = [extraSymbol];
	}

	if(symbol && extraSymbol && GetType(extraSymbol[0]) == C4V_C4ID)
	{
		InlineSymbol(caption, extraSymbol);
	}
	else
	{
		symbol = extraSymbol;
	}
}

func EnumEntrySettings(string& caption, &symbol, string& infoCaption, int index, array args, array entry)
{
	var layoutVals = args[DT_Menu_Adaptor_LayoutVals];
	var layout = layoutVals[1];
	layoutVals = layoutVals[0];

	caption = entry[DT_Menu_Entry_Caption];
	if(layout[Menu_Layout__CaptionPos])
	{
		caption = Format(caption, layoutVals[index][layout[Menu_Layout__CaptionPos] - 1]);
	}

	if(layout[Menu_Layout_Symbol])
	{
		ExtraSymbol(caption, symbol, layoutVals[index][layout[Menu_Layout_Symbol] - 1]);
	}

	if(layout[Menu_Layout_InfoCaption])
	{
		infoCaption = Format(infoCaption, layoutVals[index][layout[Menu_Layout_InfoCaption] - 1]);
	}
}

func AdaptorFactory(args, int entryIndex)
{
	var entry = args[0];
	var entrySettings = args[2];
	args = args[1];
	var caption;
	var infoCaption = entry[DT_Menu_Entry_InfoCaption];
	var symbol = entry[DT_Menu_Entry_Symbol];
	var val = ScopedVar(args[DT_Menu_Adaptor_Variable]);
	var defaultMsgboardText = "$EnterValue$";

	var retSubmenu;

	args[DT_Menu_Adaptor_Args] = entry[DT_Menu_Entry_Args];
	args[DT_Menu_Adaptor_EntryIndex] = entryIndex;
	args[DT_Menu_Adaptor_Callbacks] = args[DT_Menu_Adaptor_Callbacks] || [];
	if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Boolean)
	{
		if(!(GetType(val) == C4V_Any || GetType(val) == C4V_Bool)) { FatalError("Assertion failed: AdaptorFactory: Value of Menu_Adaptor_Variable has wrong type; assertion code: GetType(val) == C4V_Any || GetType(val) == C4V_Bool"); }
		caption = BooleanToggleCaption(val, entry[DT_Menu_Entry_Caption]);
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_String)
	{
		if(!(GetType(val) == C4V_Any || GetType(val) == C4V_String)) { FatalError("Assertion failed: AdaptorFactory: Value of Menu_Adaptor_Variable has wrong type; assertion code: GetType(val) == C4V_Any || GetType(val) == C4V_String"); }
		caption = Format(entry[DT_Menu_Entry_Caption], val);
		defaultMsgboardText = "$EnterText$";
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Integer)
	{
		if(!(GetType(val) == C4V_Any || GetType(val) == C4V_Int)) { FatalError("Assertion failed: AdaptorFactory: Value of Menu_Adaptor_Variable has wrong type; assertion code: GetType(val) == C4V_Any || GetType(val) == C4V_Int"); }
		var limits = args[DT_Menu_Adaptor_Limits], max, min;
		var wrapAround = args[DT_Menu_Adaptor_WrapAround];
		if(limits && !wrapAround)
		{
			if(val >= limits[1])
			{
				max = true;
			}
			if(val <= limits[0])
			{
				min = true;
			}
		}
		caption = Format("%s %s %s", ["{{MN7I:3}}", "<c 808080>{{MN7I:3}}</c>"][max], Format(entry[DT_Menu_Entry_Caption], val), ["{{MN7I:4}}", "<c 808080>{{MN7I:4}}</c>"][min]);
		defaultMsgboardText = "$EnterNumber$";
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_ID)
	{
		if(!(GetType(val) == C4V_Any || GetType(val) == C4V_C4ID)) { FatalError("Assertion failed: AdaptorFactory: Value of Menu_Adaptor_Variable has wrong type; assertion code: GetType(val) == C4V_Any || GetType(val) == C4V_C4ID"); }
		var text = "";
		if(val)
		{
			text = Format("{{%i}} %s", val, GetName(0, val));
		}
		caption = Format(entry[DT_Menu_Entry_Caption], text);
		defaultMsgboardText = "$EnterIDOrName$";
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Enum)
	{
		var layoutVals = args[DT_Menu_Adaptor_LayoutVals];
		var layout = layoutVals[1];
		layoutVals = layoutVals[0];

		var index = EnumValPos(layoutVals, layout, val);

		if(index == -1)
		{
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = layoutVals[0][layout[Menu_Layout__ValuePos] - 1];
			index = 0;
		}

		var submenuSymbol = symbol;

		EnumEntrySettings(caption, symbol, infoCaption, index, args, entry);

		if(args[DT_Menu_Adaptor_EnumSubmenu] != Menu_CallbackType_None)
		{
			args[DT_Menu_Adaptor_MessageBoardText] = args[DT_Menu_Adaptor_MessageBoardText] || defaultMsgboardText;

			var submenuCaption = args[DT_Menu_Adaptor_EnumSubmenuCaption];

			if(submenuCaption && submenuCaption[0])
			{
				submenuCaption = submenuCaption[0];
			}
			else
			{
				submenuCaption = caption;
			}

			retSubmenu = [
				Menu_KeepParentOnClose(),
				Menu_Caption(submenuCaption),
				Menu_DontKeepOpen(),

				Menu_Factory([MenuObjectCallback("AdaptorEnumSubmenuFactory")], [args, entry])
			];

			if(args[DT_Menu_Adaptor_EnumSubmenuSymbol])
			{
				submenuSymbol = [args[DT_Menu_Adaptor_EnumSubmenuSymbol]];
			}
			else if(!submenuSymbol && symbol && GetType(symbol[0]) == C4V_C4ID)
			{
				submenuSymbol = symbol;
			}

			if(submenuSymbol && GetType(submenuSymbol[0]) == C4V_C4ID)
			{
				ArrayAppend(retSubmenu, Menu_Symbol(submenuSymbol[0]));
			}
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_BitField)
	{
		if(!(GetType(val) == C4V_Any || GetType(val) == C4V_Int)) { FatalError("Assertion failed: AdaptorFactory: Value of Menu_Adaptor_Variable has wrong type; assertion code: GetType(val) == C4V_Any || GetType(val) == C4V_Int"); }
		args[DT_Menu_Adaptor_MessageBoardText] = args[DT_Menu_Adaptor_MessageBoardText] || defaultMsgboardText;

		var layoutVals = args[DT_Menu_Adaptor_LayoutVals];
		var layout = layoutVals[1];
		layoutVals = layoutVals[0];

		var fieldValue = ScopedVar(args[DT_Menu_Adaptor_Variable]);
		var ret = [];

		for(var val in layoutVals)
		{
			caption = entry[DT_Menu_Entry_Caption] || "%s";
			if(layout[Menu_Layout__CaptionPos])
			{
				caption = Format(caption, val[layout[Menu_Layout__CaptionPos] - 1]);
			}
			caption = BooleanToggleCaption(fieldValue & (1 << val[layout[Menu_Layout__ValuePos] - 1]), caption);

			symbol = entry[DT_Menu_Entry_Symbol];
			if(layout[Menu_Layout_Symbol])
			{
				ExtraSymbol(caption, symbol, val[layout[Menu_Layout_Symbol] - 1]);
			}

			if(layout[Menu_Layout_InfoCaption])
			{
				infoCaption = Format(infoCaption, val[layout[Menu_Layout_InfoCaption] - 1]);
			}

			args[DT_Menu_Adaptor_Bit] = val[layout[Menu_Layout__ValuePos] - 1];

			ArrayAppend(ret, Menu_Entry([Menu_Combined(entrySettings), Menu_Entry_Caption(caption), Menu_Entry_Callbacks([Menu_Callback(MenuObjectCallback("AdaptorCommand"), Menu_CallbackType_All)]), Menu_Entry_Symbol(symbol), Menu_Entry_InfoCaption(infoCaption), Menu_Entry_Args(args)]));
		}

		return ret;
	}
	args[DT_Menu_Adaptor_MessageBoardText] = args[DT_Menu_Adaptor_MessageBoardText] || defaultMsgboardText;
	if(!retSubmenu)
	{
		return [Menu_Entry([Menu_Combined(entrySettings), Menu_Entry_Caption(caption), Menu_Entry_Callbacks([Menu_Callback(MenuObjectCallback("AdaptorCommand"), Menu_CallbackType_All)]), Menu_Entry_Symbol(symbol), Menu_Entry_InfoCaption(infoCaption), Menu_Entry_Args(args)])];
	}
	else
	{
		return [Menu_SubMenu([Menu_Combined(entrySettings), Menu_Entry_Caption(caption), Menu_Entry_Callbacks([Menu_Callback(MenuObjectCallback("AdaptorCommand"), Menu_CallbackType_All)]), Menu_Entry_Symbol(symbol), Menu_Entry_InfoCaption(infoCaption), Menu_Entry_Args(args)], retSubmenu)];
	}
}

func AdaptorEnumSubmenuFactory(array args)
{
	var entry = args[1];
	args = args[0];
	var layoutVals = args[DT_Menu_Adaptor_LayoutVals];
	var layout = layoutVals[1];
	layoutVals = layoutVals[0];

	var ret = [Menu_Selection(EnumValPos(layoutVals, layout, ScopedVar(args[DT_Menu_Adaptor_Variable])))];

	var caption, infoCaption, symbol;

	var submenuCaption = args[DT_Menu_Adaptor_EnumSubmenuCaption];
	if(submenuCaption && submenuCaption[1])
	{
		entry[DT_Menu_Entry_Caption] = submenuCaption[1];
	}

	for(var i = 0; i < GetLength(layoutVals); ++i)
	{
		symbol = 0;
		EnumEntrySettings(caption, symbol, infoCaption, i, args, entry);
		ArrayAppend(ret, Menu_Entry([Menu_Entry_Caption(caption), Menu_Entry_Symbol(symbol), Menu_Entry_InfoCaption(infoCaption), Menu_Entry_Callbacks([Menu_Callback(MenuObjectCallback("AdaptorEnumSubmenuItem"))]), Menu_Entry_Args([i, args])]));
	}

	return ret;
}

func AdaptorEnumSubmenuItem(int action, id ID, object obj, args)
{
	var index = args[0];
	args = args[1];

	var val = ScopedVar(args[DT_Menu_Adaptor_Variable]);
	var oldVal = val;

	var enumVals = args[DT_Menu_Adaptor_LayoutVals];
	var layout = enumVals[1];
	enumVals = enumVals[0];

	ScopedVar(args[DT_Menu_Adaptor_Variable]) = val = enumVals[index][layout[Menu_Layout__ValuePos] - 1];
	var reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], Menu_CallbackType_ValueChanged, [Menu_CallbackType_ValueChanged, ID, obj, args[DT_Menu_Adaptor_Args], val, oldVal, true]);
	if(reaction != Menu_React_None)
	{
		return reaction;
	}

	return Menu_React_Back;
}

func WrapOrBind(int val, array limits, bool wrap)
{
	if(!limits)
	{
		return val;
	}

	var min = limits[0];
	var max = limits[1];

	if(val < min)
	{
		if(wrap)
		{
			return max;
		}
		else
		{
			return min;
		}
	}
	else if(val > max)
	{
		if(wrap)
		{
			return min;
		}
		else
		{
			return max;
		}
	}
	else
	{
		return val;
	}
}

func AdaptorCommand(int action, id ID, object obj, args) // TODO: Callback bei CallMessageBoard?
{
	var callbackArgs = args[DT_Menu_Adaptor_Args];
	var val = ScopedVar(args[DT_Menu_Adaptor_Variable]);
	var oldVal = val;
	var reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], action, CreateFilledArray(action, ID, obj, callbackArgs, ...), Menu_React_Refresh, true);
	if(reaction != Menu_React_Refresh)
	{
		return reaction;
	}
	if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Boolean)
	{
		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = val = !val;
			reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], Menu_CallbackType_ValueChanged, [Menu_CallbackType_ValueChanged, ID, obj, callbackArgs, val, oldVal]);
			if(reaction != Menu_React_None)
			{
				return reaction;
			}
		}
		else
		{
			return Menu_React_KeepOpen;
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Integer)
	{
		var limits = args[DT_Menu_Adaptor_Limits];
		var wrapAround = args[DT_Menu_Adaptor_WrapAround];
		var step = args[DT_Menu_Adaptor_StepSize];
		var stepSize = 1;
		if(step)
		{
			stepSize = step[0];
		}
		if(action == Menu_CallbackType_Special2)
		{
			if(msgBoardMode == 0)
			{
				msgBoardMode = Menu_AdaptorType_Integer + 1;
				msgBoardEntry = args[DT_Menu_Adaptor_EntryIndex];
				CallMessageBoard(this, false, args[DT_Menu_Adaptor_MessageBoardText], GetOwner(obj));
			}
			return Menu_React_KeepOpen;
		}
		else if(action == Menu_CallbackType_Normal)
		{
			val += stepSize;
		}
		else if(action == Menu_CallbackType_Close)
		{
			val -= stepSize;
		}
		else
		{
			return Menu_React_KeepOpen;
		}

		val = WrapOrBind(val, limits, wrapAround);

		if(val != oldVal)
		{
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = val;
			reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], Menu_CallbackType_ValueChanged, [Menu_CallbackType_ValueChanged, ID, obj, callbackArgs, val, oldVal]);
			if(reaction != Menu_React_None)
			{
				return reaction;
			}
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_String)
	{
		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			if(msgBoardMode == 0)
			{
				msgBoardMode = Menu_AdaptorType_String + 1;
				msgBoardEntry = args[DT_Menu_Adaptor_EntryIndex];
				CallMessageBoard(this, false, args[DT_Menu_Adaptor_MessageBoardText], GetOwner(obj));
			}
		}
		if(action == Menu_CallbackType_Close)
		{
			return Menu_React_None;
		}
		else
		{
			return Menu_React_KeepOpen;
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_ID)
	{
		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			if(msgBoardMode == 0)
			{
				msgBoardMode = Menu_AdaptorType_ID + 1;
				msgBoardEntry = args[DT_Menu_Adaptor_EntryIndex];
				CallMessageBoard(this, false, args[DT_Menu_Adaptor_MessageBoardText], GetOwner(obj));
			}
		}
		return Menu_React_KeepOpen;
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Enum)
	{
		if(GetType(args[DT_Menu_Adaptor_EnumSubmenu]) == C4V_Bool)
		{
			if(action & Menu_CallbackType_Defaults)
			{
				return Menu_React_ShowSubmenu;
			}
			else
			{
				return Menu_React_None;
			}
		}

		if(args[DT_Menu_Adaptor_EnumSubmenu] & action)
		{
			return Menu_React_ShowSubmenu;
		}

		var enumVals = args[DT_Menu_Adaptor_LayoutVals];
		var layout = enumVals[1];
		enumVals = enumVals[0];

		var index = EnumValPos(enumVals, layout, val);
		var wrapAround = args[DT_Menu_Adaptor_WrapAround];

		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			++index;
		}
		else if(action == Menu_CallbackType_Close)
		{
			--index;
		}
		else
		{
			return Menu_React_None;
		}

		index = WrapOrBind(index, [0, GetLength(enumVals) - 1], wrapAround);

		ScopedVar(args[DT_Menu_Adaptor_Variable]) = val = enumVals[index][layout[Menu_Layout__ValuePos] - 1];
		reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], Menu_CallbackType_ValueChanged, [Menu_CallbackType_ValueChanged, ID, obj, callbackArgs, val, oldVal]);
		if(reaction != Menu_React_None)
		{
			return reaction;
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_BitField)
	{
		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = (val ^= (1 << args[DT_Menu_Adaptor_Bit]));
			reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], Menu_CallbackType_ValueChanged, [Menu_CallbackType_ValueChanged, ID, obj, callbackArgs, val, oldVal]);
			if(reaction != Menu_React_None)
			{
				return reaction;
			}
		}
		else
		{
			return Menu_React_KeepOpen;
		}
	}

	return Menu_React_Refresh;
}

func InputCallback(string input, int plr)
{
	var entry = entries[msgBoardEntry];
	var args = entry[1][DT_Menu_Entry_Args];
	var callbackArgs = args[DT_Menu_Adaptor_Args];
	var oldVal = ScopedVar(args[DT_Menu_Adaptor_Variable]);
	var val = input;
	if(msgBoardMode - 1 == Menu_AdaptorType_Integer)
	{
		var int = ParseInt(input);
		var limits = args[DT_Menu_Adaptor_Limits];
		var step = args[DT_Menu_Adaptor_StepSize];
		if(GetType(int) == C4V_Int || GetType(int) == C4V_Any)
		{
			if(step && step[1])
			{
				var s = step[0];
				if(GetType(step[1]) == C4V_Int)
				{
					s = step[1];
				}
				int = ((int + s / 2) / s) * s;
			}
			if(limits)
			{
				int = BoundBy(int, limits[0], limits[1]);
			}
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = val = int;
		}
		else
		{
			val = oldVal;
		}
	}
	else if(msgBoardMode - 1 == Menu_AdaptorType_String)
	{
		if(args[DT_Menu_Adaptor_NoEmptyString] && (!input || input == ""))
		{
			val = oldVal;
		}
		else
		{
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = input;
		}
	}
	else if(msgBoardMode - 1 == Menu_AdaptorType_ID)
	{
		val = GetIDByName(input); // WARNING: desyncs between clients with different languages
		if(!val && GetLength(input) == 4) val = C4Id(input);
		if(!GetName(0, val)) val = 0;
		ScopedVar(args[DT_Menu_Adaptor_Variable]) = val;
	}
	msgBoardMode = 0;
	if(val != oldVal)
	{
		var reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], Menu_CallbackType_ValueChanged, [Menu_CallbackType_ValueChanged, entry[1][DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], callbackArgs, val, oldVal]);
		if(reaction != Menu_React_None)
		{
			return React(reaction, msgBoardEntry);
		}
	}
	Refresh(msgBoardEntry);
}

global func Menu_Combined(array combined) { 	if(!(combined)) { FatalError("Assertion failed: Menu_Combined: combined is mandatory; assertion code: combined"); }return [DT_Menu_Combined, combined]; }

global func CreateNewMenu(array menu, inheritSettings, object parentMenu)
{
	var settings = inheritSettings;

	if(GetType(settings) != C4V_Array) settings = [];
	settings[DT_Menu_Settings_Style] &= ~C4MN_Style_EqualItemHeight; // EqualItemHeight can't be inherited
	settings[DT_Menu_Settings_Selection] = 0; // Selection can't be inherited
	settings[DT_Menu_Settings_Callbacks] = 0; // Global callbacks can't be inherited (maybe filter callbacks)

	settings[DT_Menu_Settings_Parent] = parentMenu;

	var entries = [];

	MN7I->UncombineAndDistinguish(menu, settings, entries);

	var menuObj = CreateObject(MN7I);

	menuObj->Create(settings, entries);

	return menuObj;
}

func NamedArg(array namedArg, array &args)
{
	args[namedArg[0]] = namedArg[1];
}

func UncombineAndDistinguish(array combined, array &settings, array &entries)
{
	var line = 0;
	for(var val in combined)
	{
	if(!(val)) { FatalError(Format("Assertion failed: UncombineAndDistinguish: entry/setting of value 0 found at entry/setting number %d; assertion code: val", line)); }
		if(val[0] == DT_Menu_Type_Setting)
		{
			if((val[1][0] == DT_Menu_Settings_Style && val[1][1] == C4MN_Style_EqualItemHeight) || settings[DT_Menu_Settings_Style] == C4MN_Style_EqualItemHeight)
			{
				settings[DT_Menu_Settings_Style] |= val[1][1];
			}
			else
			{
				NamedArg(val[1], settings);
			}
		}
		else if(val[0] == DT_Menu_Type_Entry || val[0] == DT_Menu_Type_Factory)
		{
			entries[GetLength(entries)] = val;
		}
		else if(val[0] == DT_Menu_Combined)
		{
			UncombineAndDistinguish(val[1], settings, entries);
		}
	else
		{
			Log("WARNING: UncombineAndDistinguish: Unknown entry/settings type %v with value %v", val[0], val[1]);
		}

		++line;
	}
}

func NamedArgs(array namedArgs, array& args)
{
	for(var arg in namedArgs)
	{
		if(arg[0] == DT_Menu_Combined)
		{
			NamedArgs(arg[1], args);
		}
		else
		{
			NamedArg(arg, args);
		}
	}
}

func DeclineAcceptCommand(int action, id ID, object obj, args)
{
	if(args[0])
	{
		var reaction = CallA(args[0], [action, ID, settings[DT_Menu_Settings_Object], args[1]]);
		if(reaction != Menu_React_None) return reaction;
	}
	return Menu_React_Close;
}

func BackCommand(int action, id ID, object obj, args)
{
	if(args[0])
	{
		var reaction = CallA(args[0], [action, ID, settings[DT_Menu_Settings_Object], args[1]]);
		if(reaction != Menu_React_None) return reaction;
	}
	return Menu_React_Back;
}

func MenuObjectCallback(string name)
{
	return [CallbackTarget_Scenario - 1, name];
}

func CallCustom(callback, args)
{
	if(GetType(callback) == C4V_Array && GetLength(callback) == 2 && callback[0] == CallbackTarget_Scenario - 1)
	{
		return CallA(ObjectCallback(callback[1], this), args, ...);
	}
	else
	{
		return _inherited(callback, args, ...);
	}
}

func Update()
{
	return Refresh(currentSelection);
}

func GetSelection()
{
	return currentSelection;
}

func GetObject()
{
	return settings[DT_Menu_Settings_Object];
}

func ValidateDeco(id deco)
{
	return !deco || (deco->~FrameDecorationBackClr() || deco->~FrameDecorationBorderTop() || deco->~FrameDecorationBorderLeft() || deco->~FrameDecorationBorderRight() || deco->~FrameDecorationBorderBottom());
}

func ValidateMenuCallbacks(array callbacks)
{
	if(!callbacks)
	{
		return false;
	}

	for(var callback in callbacks)
	{
		if(!ValidateMenuCallback(callback))
		{
			return false;
		}
	}

	return true;
}

func ValidateMenuCallback(array callback)
{
	if(!callback)
	{
		return false;
	}

	return GetLength(callback) == 2 && GetType(callback[1]) == C4V_Int && (callback[1] & ~Menu_CallbackType_All) == 0 && CheckCallback(callback[0]);
}

func CheckCallback(callback)
{
	var ret = _inherited(callback, ...);
	if(ret && GetType(callback) == C4V_String)
	{
		Log("WARNING: DT_Menu::CheckCallback: A string only callback will not work as expected (yet): \"%s\"", callback[0]);
	}
	return ret;
}

func CheckCustomCallback(callback)
{
	if(GetType(callback) == C4V_Array && GetLength(callback) == 2 && callback[0] == (CallbackTarget_Scenario - 1) && GetType(callback[1]) == C4V_String && callback[1] != "")
	{
		return true;
	}

	return _inherited(callback, ...);
}

// TODO: Erstellungskontext in CreateNewMenu speichern, damit Callbacks ohne explizite Kontextangabe im "Erzeuger" aufgerufen werden können
// TODO: RefreshDelayed noch im gleichen Frame im Effekttimer, wenn möglich (also kein Umhergehüpfe); noch relevant?
// TODO: Created-Callback, Refresh-Callback, u.ä., Menu_Entry (optional) mit "benannten" Argumenten und Menu_AutoEntry dadurch ersetzen, Adapter-Factories (inline oder als SubMenu (optional side by side)), (Objekt-Selector mit Find_*-Filter als Ausgangsbasis (??))
// TODO: Vordefiniertes Condition-Callback für Variablenvergleiche (mit ScopedVar() und Vergleichswert)
// TODO: SelectionMenu wie in ObjectsAppend mit SelectMark aber flexibler (vgl. SelectionMenu und Leitung trennen-Menü)
// TODO: Flexibles Side by Side Submenu wie bei Sensor base für Ziel hinzufügen
// TODO: Menüglobale (wird bei jeder Eintragsaktion aufgerufen; vor (wie ein Filter) oder nach Eintragcallback; optional nur wenn das Callback React_None zurückgibt; Callback-Reaction als Parameter) Callbacks (vorallem Close)
// TODO: List-Factory (wie Factory, nur dass ein Array mit Args übergeben werden _muss_, worüber im Menüsystem iteriert wird)(Erspart eine explizite Schleife)
