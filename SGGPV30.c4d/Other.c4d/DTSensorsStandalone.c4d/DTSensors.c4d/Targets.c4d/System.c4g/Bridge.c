#strict 2
#appendto BRDG

func RemoteControlMap()
{
	return [
		[RC7I_Control_T, "LockSafe", "$BRDG_Lock$"],
		[RC7I_Control_U, "ReleaseSafe", "$BRDG_Release$"],
		[RC7I_Control_Q, "ControlDigDouble", "$BRDG_Toggle$"]
	];
}

func LockSafe() { return !IsLocked() && Lock(); }
func ReleaseSafe() { return IsLocked() && Release(); }
