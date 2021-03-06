#strict 2
#appendto CPT2

func IsRemoteControllable() { return false; }

func FindGate(bool right) { return FindObject(0, 0, 0, 0, 0, 0, (right && "GateRight") || "GateLeft", this); }

func SensorCallbacks()
{
	var ret = [];
	for(var part in [[false, "$TWR2_LeftGate$", ["LeftGateOpen", "LeftGateClose", "ControlLeft"]], [true, "$TWR2_RightGate$", ["RightGateOpen", "RightGateClose", "ControlRight"]]])
	{
		if(FindGate(part[0]))
		{
			ret[GetLength(ret)] = [Format("$TWR2_GateOpen$", part[1]), part[2][0]];
			ret[GetLength(ret)] = [Format("$TWR2_GateClose$", part[1]), part[2][1]];
			ret[GetLength(ret)] = [Format("$TWR2_GateOpenClose$", part[1]), part[2][2]];
		}
	}
	
	if((GetID() == CPT3 || GetID() == CPT4) && this->FindDrawbridge())
	{
		ret[GetLength(ret)] = ["$TWR2_DrawBridgeUp$", "ControlUp"];
		ret[GetLength(ret)] = ["$TWR2_DrawBridgeDown$", "ControlDownSingle"];
		ret[GetLength(ret)] = ["$TWR2_DrawBridgeUpDown$", "ToggleDrawBridge"];
	}
	
	return ret;
}

func LeftGateOpen() { return GateOpen(false); }
func LeftGateClose() { return GateClose(false); }

func RightGateOpen() { return GateOpen(true); }
func RightGateClose() { return GateClose(true); }

func GateOpen(bool right) { return GateOpenClose(right, false); }
func GateClose(bool right) { return GateOpenClose(right, true); }

func GateOpenClose(bool right, bool close)
{
	var gate = FindGate(right);
	if(gate)
	{
		gate->Activate();
		
		if(close)
		{
			gate->Close();
		}
		else
		{
			gate->Open();
		}
	}
}

func ToggleDrawBridge()
{
	var bridge = this->FindDrawbridge();
	if(bridge)
	{
		if(bridge->IsUp())
		{
			return bridge->ControlDown();
		}
		else
		{
			return bridge->ControlUp();
		}
	}
}

