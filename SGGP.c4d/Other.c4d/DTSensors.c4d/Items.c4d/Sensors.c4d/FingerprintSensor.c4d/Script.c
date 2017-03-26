#strict 2
#include SN7I

local masterFinger, fingers;

func Init()
{
	fingers = [];
}

func CleanupFingers()
{
	ArrayEraseItem(fingers, 0, true);
}

func Triggers() { return [["$RightFinger$"], ["$WrongFinger$"]];}

func ControlThrow(object caller)
{
	if(GetLength(fingers) > 0)
	{
		var success = IsKnownFinger(caller);
		ShowSuccess(success);
		Trigger(!success, caller);
	}
	return ClearCom(caller);
}

func ShowSuccess(bool success, object caller)
{
	if(!success)
	{
		Sound("Error");
		CreateParticle("PSpark", -2, -2, 0, 0, 50, RGB(192, 0, 0));
	}
	else
	{
		CreateParticle("PSpark", -2, -2, 0, 0, 50, RGB(0, 192, 0));
	}
}

func ControlThrowDouble() { return ControlThrow(...); }

func EntranceCallback() { return "ControlThrow"; }

func SetupCondition(object caller)
{
	return GetLength(fingers) == 0 || IsKnownFinger(caller);
}

func IsKnownFinger(object finger)
{
	return GetIndexOf(finger, fingers) != -1;
}

func Setup(object caller, int& menuIndex)
{
	if(!CheckMasterFinger())
	{
		AddMenuItem("$SetMasterFinger$", "SetMasterFinger", RSR1, caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
		++menuIndex;
	}
	if(caller == masterFinger)
	{
		if(FindObject2(AddFingerCondition()))
		{
			AddMenuItem("$AddFinger$", "AddFingers", RSR1, caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
			++menuIndex;
		}
		if(GetLength(fingers) > 0)
		{
			AddMenuItem("$ChangeFingers$", "ChangeFingers", RSR1, caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
			++menuIndex;
		}
	}
	return true;
}

func SetMasterFinger(id id, object caller)
{
	if(!CheckMasterFinger())
	{
		masterFinger = caller;
		if(!IsKnownFinger(caller))
		{
			fingers[GetLength(fingers)] = caller;
		}
	}
}

func AddFingerCondition()
{
	return Find_And(Find_OCF(OCF_CrewMember), Find_ActionTarget(this), Find_Procedure("PUSH"), Find_Not(Find_Func("FP7I_IsKnownFinger", this)));
}

func GetFingerList(array fingers, bool showMaster)
{
	var ret = CreateArray(GetLength(fingers));
	for(var i = 0; i < GetLength(fingers); ++i)
	{
		var obj = fingers[i];
		ret[i] = [obj, Format("%s (%s)", GetName(obj), GetPlayerName(GetOwner(obj)))];
		if(showMaster && obj == masterFinger)
		{
			ret[i][1] = Format("$MasterFinger$", ret[i][1]);
		}
	}
	return ret;
}

func AddFingers(id id, object caller)
{
	return caller->~CreateSelectionMenu("AddFinger", GetFingerList(FindObjects(AddFingerCondition())), GetID(), "$AddFinger$", this);
}

func AddFinger(id id, object finger, bool right)
{
	if(!IsKnownFinger(finger))
	{
		fingers[GetLength(fingers)] = finger;
	}
	if(right)
	{
		masterFinger = finger;
	}
}

func ChangeFingers(id id, object caller)
{
	selectCaller = caller;
	return caller->~CreateSelectionMenu("ChangeFinger", GetFingerList(fingers, true), GetID(), "$ChangeFingers$", this);
}

func ChangeFinger(id id, object finger, bool right)
{
	if(right)
	{
		masterFinger = finger;
	}
	else
	{
		var i = GetIndexOf(finger, fingers);
		if(i != -1)
		{
			ArrayErase(fingers, i);
			if(finger != masterFinger)
			{
				ChangeFingers(0, selectCaller);
				SelectMenuItem(i - 1, selectCaller);
				SelectMenuItem(i, selectCaller);
			}
			else
			{
				masterFinger = 0;
			}
		}
	}
}

global func FP7I_IsKnownFinger(object sensor)
{
	return sensor && sensor->IsKnownFinger(this);
}

func CheckMasterFinger()
{
	if(masterFinger && !GetAlive(masterFinger))
	{
		masterFinger = 0;
	}
	return !!masterFinger;
}
