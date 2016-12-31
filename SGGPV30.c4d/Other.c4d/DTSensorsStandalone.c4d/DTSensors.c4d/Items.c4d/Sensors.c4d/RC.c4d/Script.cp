#strict 2
#include SN7I

local viewTarget;
local user;
local controlTimer;
local realAttachPos;

#pp_include enum
#pp_include bitfield
#pp_include utility
#define _
// _enum(RC7I_Control_, L, LS, LD, LR, R, RS, RD, RR, U, US, UD, UR, D, DS, DD, DR, T, TS, TD, TR, Q, QS, QD, QR, S, SS, SD, SR, Z, ZS, ZD, ZR, V)
static const RC7I_Control_L = 0;
static const RC7I_Control_LS = 1;
static const RC7I_Control_LD = 2;
static const RC7I_Control_LR = 3;
static const RC7I_Control_R = 4;
static const RC7I_Control_RS = 5;
static const RC7I_Control_RD = 6;
static const RC7I_Control_RR = 7;
static const RC7I_Control_U = 8;
static const RC7I_Control_US = 9;
static const RC7I_Control_UD = 10;
static const RC7I_Control_UR = 11;
static const RC7I_Control_D = 12;
static const RC7I_Control_DS = 13;
static const RC7I_Control_DD = 14;
static const RC7I_Control_DR = 15;
static const RC7I_Control_T = 16;
static const RC7I_Control_TS = 17;
static const RC7I_Control_TD = 18;
static const RC7I_Control_TR = 19;
static const RC7I_Control_Q = 20;
static const RC7I_Control_QS = 21;
static const RC7I_Control_QD = 22;
static const RC7I_Control_QR = 23;
static const RC7I_Control_S = 24;
static const RC7I_Control_SS = 25;
static const RC7I_Control_SD = 26;
static const RC7I_Control_SR = 27;
static const RC7I_Control_Z = 28;
static const RC7I_Control_ZS = 29;
static const RC7I_Control_ZD = 30;
static const RC7I_Control_ZR = 31;
static const RC7I_Control_V = 32;

#define INDENT _			
#define SEP ,
#define ELSE
#define ControlPrefix Control
#define Ctrl(name, short) [RC7I_Control_##short, STRINGIFY(ControlPrefix##name)]
#define CtrlMultiPart(name, short) Ctrl(name##Single, short##S)##SEP\
INDENT	Ctrl(name##Double, short##D)##SEP\
INDENT	Ctrl(name##Released, short##R)
#define CtrlMulti(name, short) Ctrl(name, short)##SEP\
INDENT	CtrlMultiPart(name, short)
#define Ctrl(name) STRINGIFY($name$)
func GetControlName(int ctrl)
{
#define INDENT INDENT	
	return [CtrlMulti(Left, L),
					CtrlMulti(Right, R),
					CtrlMulti(Up, U),
					CtrlMulti(Down, D),
					CtrlMulti(Throw, T),
					CtrlMulti(Dig, Q),
					CtrlMulti(Special, S),
					CtrlMulti(Special2, Z),
					Ctrl(Update, V)
 				][ctrl];
}
#pop Ctrl

#define Ctrl(name, short) [STRINGIFY($name$)]
func Triggers()
{
	return [CtrlMulti(Left, L),
					CtrlMulti(Right, R),
					CtrlMulti(Up, U),
					CtrlMulti(Down, D),
					CtrlMulti(Throw, T),
					CtrlMulti(Dig, Q),
					CtrlMulti(Special, S),
					CtrlMulti(Special2, Z),
					Ctrl(Update, V)];
}
#pop Ctrl
#pop INDENT

global func IsRemoteControllable(object controller)
{
	return GetOCF() & OCF_Grab;
}

global func RemoteControlMap(object controller)
{
	if(this->~IsRemoteControllable(controller))
	{
		if(GetOCF() & OCF_Grab)
		{
			return
			[
				CtrlMulti(Left, L),
				CtrlMulti(Right, R),
				CtrlMulti(Up, U),
				CtrlMulti(Down, D),
				CtrlMulti(Throw, T),
				CtrlMulti(Dig, Q),
				CtrlMulti(Special, S),
				CtrlMulti(Special2, Z),
				Ctrl(Update, V),
				[RC7I_Control_L, BindCallback(RC7I->Callback("UpdateTargetDir"), [Bind(this), Bind(DIR_Left)]), "$ChangeDirLeft$"],
				[RC7I_Control_R, BindCallback(RC7I->Callback("UpdateTargetDir"), [Bind(this), Bind(DIR_Right)]), "$ChangeDirRight$"],
				[RC7I_Control_S, BindCallback(RC7I->Callback("ShiftTargetContents"), [Bind(this)]), "$ShiftContents$"],
				[RC7I_Control_SD, BindCallback(RC7I->Callback("ShiftTargetContents"), [Bind(this)]), "$ShiftContents$"]
			];
		}
		else if(GetOCF() & OCF_Entrance)
		{
#define ControlPrefix Contained
			return
			[
				CtrlMulti(Left, L),
				CtrlMulti(Right, R),
				CtrlMulti(Up, U),
				CtrlMulti(Down, D),
				CtrlMulti(Throw, T),
				CtrlMulti(Dig, Q),
				Ctrl(Update, V),
				[RC7I_Control_S, BindCallback(RC7I->Callback("ShiftTargetContents"), [Bind(this)]), "$ShiftContents$"],
				[RC7I_Control_SD, BindCallback(RC7I->Callback("ShiftTargetContents"), [Bind(this)]), "$ShiftContents$"]
			];
		}
	}
}

#undef ControlPrefix
#undef CtrlMulti
#undef CtrlMultiPart
#undef Ctrl

func Setup(object caller, int &menuIndex)
{
	AddMenuItem("$AddControlTarget$", "AutoTarget", GetID(), caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
	++menuIndex;
	AddMenuItem("$SetViewObject$", "SelectViewObject", GetID(), caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
	++menuIndex;
	return true;
}

func GetPossibleTargets(object caller)
{
	return FindObjects((caller || this)->Find_AtPoint(), Find_Not(Find_Hostile(GetOwner(this))), Find_Func("IsRemoteControllable", this), Find_NoContainer(), Find_Exclude(this));
}

func AutoTarget(id id, object caller)
{
	var objs = GetPossibleTargets(caller);
	var ret = caller->~CreateSelectionMenu("AddTarget", objs, GetID(), SelectTargetText(), this);
	return ret;
}

func SelectViewObject(id id, object caller)
{
	var objs = GetPossibleTargets(caller);
	var ret = caller->~CreateSelectionMenu("SetViewObject", objs, GetID(), SelectTargetText(), this);
	if(ret && viewTarget)
	{
		AddMenuItem(RemoveTargetText(), "SetViewObject", GetID(), caller, 0, 0, 0, C4MN_Add_ForceNoDesc);
	}
	return ret;
}

func SetViewObject(id id, object obj)
{
	viewTarget = obj;
}

func Activate(object caller)
{
	if(!triggerCallbacks || !GetLength(triggerCallbacks))
	{
		_Setup(caller);
		return true;
	}
	else if(caller)
	{
		user = caller;
		caller->Exit(this);
		realAttachPos = attachPos;
		RemoteControlTimer(true);
		controlTimer = AddTimer("RemoteControlTimer", 1);
		SetCursor(GetController(caller), this);
		if(viewTarget)
		{
			SetViewCursor(GetController(caller), viewTarget);
			caller->CreateSelectMark()->MarkObject(viewTarget, 35);
		}
		SetCommand(caller, "Grab", this);
		ExecuteCommand(caller);
		SetAction("Active");
		return true;
	}
	else if(!Attached())
	{
		return ControlDigDouble(caller, ...);
	}
}

func ControlDigDouble(object caller)
{
	if(user || (caller && (GetProcedure(caller) != "PUSH" || GetActionTarget(0, caller) != this) && Contained() != caller))
	{
		Trigger(RC7I_Control_QD, caller || user, ...);
		return true;
	}
	else if(Attached())
	{
		return Activate(caller, ...);
	}
}

func RemoteControlTimer(bool first)
{
	if(!first && (GetProcedure(user) != "PUSH" || GetActionTarget(0, user) != this || !user))
	{
		SetCursor(GetOwner(user), user);
	}
	else
	{
		if(!GetPlrView(GetController(user)) && viewTarget && (first || !GetPlayerVal("MouseControl", "Player", GetController(user))))
		{
			SetPlrView(GetController(user), viewTarget);
		}
		SetSpeed();
		if(viewTarget)
		{
			user->SetDir(GetX(viewTarget) > GetX(user));
		}
		SetR((2 * GetDir(user) - 1) * 30);
		attachPos = [GetX(user) + (2 * GetDir(user) - 1) * 5, GetY(user)];
		if(!Attached())
		{
			SetPosition(attachPos[0], attachPos[1]);
		}
	}
}

func AllowEntrance() { return !user; }

func ControlUpdate(object caller)
{
	if(user || (caller && Contained() != caller))
	{
		return Trigger(RC7I_Control_V, user || caller, ...);
	}
}

#define MapControl(name) func Control##name(object caller)\
{\
	if(user && target)\
	{\
		return target->~Control##name(caller || user, ##...);\
	}\
}\

#define MapControl(name, short) func Control##name(object caller)\
{\
	if((caller && Contained() != caller) || user)\
	{\
		return Trigger(RC7I_Control_##short, caller || user, ##...);\
	}\
}\

_
#define MapMultiPartControl(name, short) MapControl(name##Single, short##S)\
MapControl(name##Double, short##D)\
MapControl(name##Released, short##R)
_
#define MapMultiControl(name, short) MapControl(name, short)\
MapMultiPartControl(name, short)
_
#define foreach ctrl in (Left, Right) MapMultiPartControl(ctrl)\

_
#define foreach ctrl in (Up, Down, Throw, Special2) MapMultiControl(ctrl)\

_
#define foreach ctrl in (Dig, DigSingle, DigReleased, SpecialSingle, SpecialReleased) MapControl(ctrl)\

_
MapMultiControl(Left, L)
MapMultiControl(Right, R)
MapMultiControl(Up, U)
MapMultiControl(Down, D)
MapMultiControl(Throw, T)
MapControl(Dig, Q)
MapControl(DigSingle, QS)
MapControl(DigReleased, QD)
MapMultiControl(Special, S)
MapMultiControl(Special2, Z)
#undef MapMultiControl
#undef MapMultiPartControl
#undef MapControl
_

func UpdateTargetDir(object target, int dir)
{
	if(GetXDir(target) == 0)
	{
		SetDir(dir, target);
	}
}

func ShiftTargetContents(object target)
{
	ShiftContents(target, false, 0, true);
}

func AddTarget(id id, object obj)
{
	if(!triggerCallbacks && !viewTarget)
	{
		SetViewObject(id, obj);
	}
	for(var mapping in obj->RemoteControlMap(this))
	{
		AddTargetAction(mapping[0], obj, [mapping[2] || GetControlName(mapping[0]), mapping[1]]);
	}
}

func CrewSelection(bool deselect)
{
	if(deselect)
	{
		if(user)
		{
			SetViewCursor(GetController(user), 0);
		}
		SetCursor(GetController(user), user);
		if(!Attached())
		{
			SetCommand(user, "UnGrab");
		}
		user = 0;
		SetCategory(GetCategory(0, GetID()));
		if(!Attached())
		{
			SetAction("Idle");
			SetR(0);
		}
		if(controlTimer)
		{
			RemoveTimer(controlTimer);
			attachPos = realAttachPos;
		}
	}
}

func Selection()
{
	if(viewTarget)
	{
		PlayerMessage(GetOwner(Contained()), "%s: {{%i}} %s%s", Contained(), TargetText(), GetID(viewTarget), GetName(viewTarget), ((!desc || !descVisible) && "") || "|");
		Contained()->CreateSelectMark()->MarkObject(viewTarget, 35);
	}
}

func Entrance(object container)
{
	if(GetOCF(container) & OCF_CrewMember)
	{
		Selection();
	}
}

global func FxIntJnRAimTimer(object target, int number, int time)
{
	// Controller weg?
	var controller = EffectVar(2, target, number);
	if(!controller) return(-1);
	
	// Controller muss Fahrzeug anfassen
	if(target)
		if(target->GetCategory() & C4D_Vehicle)
			if(controller->GetProcedure() != "PUSH" || (controller->GetActionTarget() != target && GetID(controller->GetActionTarget()) != RC7I))
				return FX_Execute_Kill;
			
			if(target)
				target->AimConf(EffectVar(0, target, number), EffectVar(1, target, number), EffectVar(2, target, number));
			else if(EffectVar(3, target, number))
				AimConf(EffectVar(0, target, number), EffectVar(1, target, number), EffectVar(2, target, number), EffectVar(3, target, number));
			else
				// Global call via eval()?
				;
}

func Attach(object caller)
{
	if(!user)
	{
		SetAction("Active");
		var dir;
		if(viewTarget)
		{
			dir = GetX(viewTarget) > GetX();
		}
		else
		{
			dir = Random(2);
		}
		SetR((dir * 2 - 1) * 30);
	}
	SetPosition(GetX(caller) + (2 * GetDir(caller) - 1) * 5, GetY(caller));
}

func Detach()
{
	if(!user)
	{
		SetAction("Idle");
		SetR(0);
	}
}

func AttachCondition() { return !user; }

func DetachCondition() { return !user; }

func IsRemoteControllable() { return true; }


global func CreateMenu(sym, object menuObject)
{
	var mObj = menuObject || this;
	var actionTarget = GetActionTarget(0, menuObject);
	if(menuObject && menuObject->GetProcedure() == "PUSH" && GetID(actionTarget) == RC7I && LocalN("user", actionTarget) == menuObject)
	{
		menuObject = actionTarget;
	}
	return _inherited(sym, menuObject, ...);
}

global func AddMenuItem(caption, command, sym, object menuObject)
{
	var mObj = menuObject || this;
	var actionTarget = GetActionTarget(0, menuObject);
	if(menuObject && menuObject->GetProcedure() == "PUSH" && GetID(actionTarget) == RC7I && LocalN("user", actionTarget) == menuObject)
	{
		menuObject = actionTarget;
	}
	return _inherited(caption, command, sym, menuObject, ...);

}
