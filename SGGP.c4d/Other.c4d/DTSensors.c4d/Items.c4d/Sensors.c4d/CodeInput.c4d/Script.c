#strict 2
#include SN7I

local inputMode, code, authedPlayers;

func Init()
{
	inputMode = [];
	authedPlayers = [];
}

func Triggers() { return [["$RightCode$"], ["$WrongCode$"]];}

func ControlThrow(object caller)
{
	if(!code)
	{
		PlayerMessage(GetController(caller), "$NoCodeSet$", this);
	}
	else
	{
		QueryCode(caller, 0);
	}
	return ClearCom(caller);
}

func ControlThrowDouble() { return ControlThrow(...); }

func QueryCode(object caller, int mode)
{
	var plr = GetController(caller);
	inputMode[plr] = [mode, caller];
	CallMessageBoard(this, false, ["$EnterCode$", "$EnterCurrentCode$", "$EnterNewCode$", "$EnterCode$"][mode], plr);
}

func InputCallback(string answer, int plr)
{
	if(!inputMode[plr])
	{
		return _inherited(answer, plr, ...);
	}
	else if(answer != "")
	{
		var mode = inputMode[plr][0];
		var caller = inputMode[plr][1];
		inputMode[plr] = 0;
		if(mode == 0 || mode == 3)
		{
			authedPlayers[GetPlayerID(plr)] = answer == code;
			if(mode == 0)
			{
				Trigger(answer != code, caller);
			}
			else if(mode == 3)
			{
				if(answer == code)
				{
					_Setup(caller);
				}
				else
				{
					Trigger(1, caller);
				}
			}
			ShowSuccess(answer == code, caller);
			if(answer != code)
			{
				ScheduleCall(this, "QueryCode", 1, 0, caller, mode);
			}
		}
		else if(mode == 1)
		{
			ShowSuccess(answer == code, caller);
			ScheduleCall(this, "QueryCode", 1, 0, caller, 1 + (answer == code));
			if(answer != code)
			{
				Trigger(1, caller);
			}
		}
		else if(mode == 2)
		{
			code = answer;
			authedPlayers = [];
			authedPlayers[GetPlayerID(plr)] = true;
			PlayerMessage(plr, "$CodeChanged$", this);
		}
	}
}

func ShowSuccess(bool success, object caller)
{
	if(!success)
	{
		Sound("Error");
		PlayerMessage(GetController(caller), "$TxtWrongCode$", this);
		CreateParticle("PSpark", -2, -3, 0, 0, 50, RGB(192, 0, 0));
	}
	else
	{
		CreateParticle("PSpark", -2, -3, 0, 0, 50, RGB(0, 192, 0));
	}
}

func _Setup(object caller)
{
	if(code && !authedPlayers[GetPlayerID(GetController(caller))])
	{
		QueryCode(caller, 3);
	}
	else
	{
		return _inherited(caller, ...);
	}
}

func Setup(object caller, int& menuIndex)
{
	if(GetController(caller) == GetOwner())
	{
		AddMenuItem("$ChangeCode$", "ChangeCode", GetID(), caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
		++menuIndex;
	}
	return true;
}

func ChangeCode(id id, object caller)
{
	_Setup(caller);
	SelectMenuItem(2, caller);
	
	QueryCode(caller, 1 + !code);
}

func ChangeDesc(id id, object caller, bool right)
{
	inputMode[GetController(caller)] = 0;
	return _inherited(id, caller, right, ...);
}
