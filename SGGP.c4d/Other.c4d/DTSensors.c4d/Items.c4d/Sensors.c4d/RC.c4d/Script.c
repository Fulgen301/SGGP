#strict 2
#include SN7I

local viewTarget;
local user;
local controlTimer;
local realAttachPos;

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

func GetControlName(int ctrl)
{
	return ["$Left$" ,
					"$LeftSingle$" ,
					"$LeftDouble$" ,
					"$LeftReleased$" ,
					"$Right$" ,
					"$RightSingle$" ,
					"$RightDouble$" ,
					"$RightReleased$" ,
					"$Up$" ,
					"$UpSingle$" ,
					"$UpDouble$" ,
					"$UpReleased$" ,
					"$Down$" ,
					"$DownSingle$" ,
					"$DownDouble$" ,
					"$DownReleased$" ,
					"$Throw$" ,
					"$ThrowSingle$" ,
					"$ThrowDouble$" ,
					"$ThrowReleased$" ,
					"$Dig$" ,
					"$DigSingle$" ,
					"$DigDouble$" ,
					"$DigReleased$" ,
					"$Special$" ,
					"$SpecialSingle$" ,
					"$SpecialDouble$" ,
					"$SpecialReleased$" ,
					"$Special2$" ,
					"$Special2Single$" ,
					"$Special2Double$" ,
					"$Special2Released$" ,
					"$Update$" 
 				][ctrl];
}

func Triggers()
{
	return [["$Left$" ],
					["$LeftSingle$" ],
					["$LeftDouble$" ],
					["$LeftReleased$" ],
					["$Right$" ],
					["$RightSingle$" ],
					["$RightDouble$" ],
					["$RightReleased$" ],
					["$Up$" ],
					["$UpSingle$" ],
					["$UpDouble$" ],
					["$UpReleased$" ],
					["$Down$" ],
					["$DownSingle$" ],
					["$DownDouble$" ],
					["$DownReleased$" ],
					["$Throw$" ],
					["$ThrowSingle$" ],
					["$ThrowDouble$" ],
					["$ThrowReleased$" ],
					["$Dig$" ],
					["$DigSingle$" ],
					["$DigDouble$" ],
					["$DigReleased$" ],
					["$Special$" ],
					["$SpecialSingle$" ],
					["$SpecialDouble$" ],
					["$SpecialReleased$" ],
					["$Special2$" ],
					["$Special2Single$" ],
					["$Special2Double$" ],
					["$Special2Released$" ],
					["$Update$" ]];
}

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
				[RC7I_Control_L, "ControlLeft" ],
				[RC7I_Control_LS, "ControlLeftSingle" ],
				[RC7I_Control_LD, "ControlLeftDouble" ],
				[RC7I_Control_LR, "ControlLeftReleased" ],
				[RC7I_Control_R, "ControlRight" ],
				[RC7I_Control_RS, "ControlRightSingle" ],
				[RC7I_Control_RD, "ControlRightDouble" ],
				[RC7I_Control_RR, "ControlRightReleased" ],
				[RC7I_Control_U, "ControlUp" ],
				[RC7I_Control_US, "ControlUpSingle" ],
				[RC7I_Control_UD, "ControlUpDouble" ],
				[RC7I_Control_UR, "ControlUpReleased" ],
				[RC7I_Control_D, "ControlDown" ],
				[RC7I_Control_DS, "ControlDownSingle" ],
				[RC7I_Control_DD, "ControlDownDouble" ],
				[RC7I_Control_DR, "ControlDownReleased" ],
				[RC7I_Control_T, "ControlThrow" ],
				[RC7I_Control_TS, "ControlThrowSingle" ],
				[RC7I_Control_TD, "ControlThrowDouble" ],
				[RC7I_Control_TR, "ControlThrowReleased" ],
				[RC7I_Control_Q, "ControlDig" ],
				[RC7I_Control_QS, "ControlDigSingle" ],
				[RC7I_Control_QD, "ControlDigDouble" ],
				[RC7I_Control_QR, "ControlDigReleased" ],
				[RC7I_Control_S, "ControlSpecial" ],
				[RC7I_Control_SS, "ControlSpecialSingle" ],
				[RC7I_Control_SD, "ControlSpecialDouble" ],
				[RC7I_Control_SR, "ControlSpecialReleased" ],
				[RC7I_Control_Z, "ControlSpecial2" ],
				[RC7I_Control_ZS, "ControlSpecial2Single" ],
				[RC7I_Control_ZD, "ControlSpecial2Double" ],
				[RC7I_Control_ZR, "ControlSpecial2Released" ],
				[RC7I_Control_V, "ControlUpdate" ],
				[RC7I_Control_L, BindCallback(RC7I->Callback("UpdateTargetDir"), [Bind(this), Bind(DIR_Left)]), "$ChangeDirLeft$"],
				[RC7I_Control_R, BindCallback(RC7I->Callback("UpdateTargetDir"), [Bind(this), Bind(DIR_Right)]), "$ChangeDirRight$"],
				[RC7I_Control_S, BindCallback(RC7I->Callback("ShiftTargetContents"), [Bind(this)]), "$ShiftContents$"],
				[RC7I_Control_SD, BindCallback(RC7I->Callback("ShiftTargetContents"), [Bind(this)]), "$ShiftContents$"]
			];
		}
		else if(GetOCF() & OCF_Entrance)
		{
			return
			[
				[RC7I_Control_L, "ContainedLeft" ],
				[RC7I_Control_LS, "ContainedLeftSingle" ],
				[RC7I_Control_LD, "ContainedLeftDouble" ],
				[RC7I_Control_LR, "ContainedLeftReleased" ],
				[RC7I_Control_R, "ContainedRight" ],
				[RC7I_Control_RS, "ContainedRightSingle" ],
				[RC7I_Control_RD, "ContainedRightDouble" ],
				[RC7I_Control_RR, "ContainedRightReleased" ],
				[RC7I_Control_U, "ContainedUp" ],
				[RC7I_Control_US, "ContainedUpSingle" ],
				[RC7I_Control_UD, "ContainedUpDouble" ],
				[RC7I_Control_UR, "ContainedUpReleased" ],
				[RC7I_Control_D, "ContainedDown" ],
				[RC7I_Control_DS, "ContainedDownSingle" ],
				[RC7I_Control_DD, "ContainedDownDouble" ],
				[RC7I_Control_DR, "ContainedDownReleased" ],
				[RC7I_Control_T, "ContainedThrow" ],
				[RC7I_Control_TS, "ContainedThrowSingle" ],
				[RC7I_Control_TD, "ContainedThrowDouble" ],
				[RC7I_Control_TR, "ContainedThrowReleased" ],
				[RC7I_Control_Q, "ContainedDig" ],
				[RC7I_Control_QS, "ContainedDigSingle" ],
				[RC7I_Control_QD, "ContainedDigDouble" ],
				[RC7I_Control_QR, "ContainedDigReleased" ],
				[RC7I_Control_V, "ContainedUpdate" ],
				[RC7I_Control_S, BindCallback(RC7I->Callback("ShiftTargetContents"), [Bind(this)]), "$ShiftContents$"],
				[RC7I_Control_SD, BindCallback(RC7I->Callback("ShiftTargetContents"), [Bind(this)]), "$ShiftContents$"]
			];
		}
	}
}


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

func ControlLeft(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_L, caller || user, ...);
	}
}

func ControlLeftSingle(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_LS, caller || user, ...);
	}
}

func ControlLeftDouble(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_LD, caller || user, ...);
	}
}

func ControlLeftReleased(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_LR, caller || user, ...);
	}
}

func ControlRight(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_R, caller || user, ...);
	}
}

func ControlRightSingle(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_RS, caller || user, ...);
	}
}

func ControlRightDouble(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_RD, caller || user, ...);
	}
}

func ControlRightReleased(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_RR, caller || user, ...);
	}
}

func ControlUp(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_U, caller || user, ...);
	}
}

func ControlUpSingle(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_US, caller || user, ...);
	}
}

func ControlUpDouble(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_UD, caller || user, ...);
	}
}

func ControlUpReleased(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_UR, caller || user, ...);
	}
}

func ControlDown(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_D, caller || user, ...);
	}
}

func ControlDownSingle(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_DS, caller || user, ...);
	}
}

func ControlDownDouble(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_DD, caller || user, ...);
	}
}

func ControlDownReleased(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_DR, caller || user, ...);
	}
}

func ControlThrow(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_T, caller || user, ...);
	}
}

func ControlThrowSingle(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_TS, caller || user, ...);
	}
}

func ControlThrowDouble(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_TD, caller || user, ...);
	}
}

func ControlThrowReleased(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_TR, caller || user, ...);
	}
}

func ControlDig(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_Q, caller || user, ...);
	}
}

func ControlDigSingle(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_QS, caller || user, ...);
	}
}

func ControlDigReleased(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_QD, caller || user, ...);
	}
}

func ControlSpecial(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_S, caller || user, ...);
	}
}

func ControlSpecialSingle(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_SS, caller || user, ...);
	}
}

func ControlSpecialDouble(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_SD, caller || user, ...);
	}
}

func ControlSpecialReleased(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_SR, caller || user, ...);
	}
}

func ControlSpecial2(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_Z, caller || user, ...);
	}
}

func ControlSpecial2Single(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_ZS, caller || user, ...);
	}
}

func ControlSpecial2Double(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_ZD, caller || user, ...);
	}
}

func ControlSpecial2Released(object caller)
{
	if((caller && Contained() != caller) || user)
	{
		return Trigger(RC7I_Control_ZR, caller || user, ...);
	}
}


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
