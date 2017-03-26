#strict 2
#include UT7I

local worker;
local produceQueue;

func ControlThrow(object caller)
{
	if(DenyContainedDirectCom())
	{
		return false;
	}
	SendObjectThroughTube();
	return ClearLastPlrCom(GetController(caller)) || true;
}

func ControlDigDouble(object caller)
{
	if(DenyContainedDirectCom())
	{
		return false;
	}
	return Detach();
}

func ControlUp(object caller, id selectID)
{
	if(DenyContainedDirectCom())
	{
		return false;
	}
	return SendMenu(caller);
}

func Activate(object caller)
{
	return AttachMenu(caller);
}

func ContextSetWorker(object caller)
{
	[$SetWorker$|Image=CXCN|Condition=Attached]
	if(CheckWorker() && caller == worker)
	{
		worker = 0;
		PlayerMessage(GetController(caller), "$WorkerUnset$", this);
	}
	else
	{
		worker = caller;
		PlayerMessage(GetController(caller), "$WorkerSet$", this, GetName(caller));
	}
	return true;
}

func HasObject(id type, bool allowProduction)
{
	var ret = FindSendableObject(type);
	if(!ret && allowProduction)
	{
		var attached = Attached();
		if(attached && GetDefCollectible(type))
		{
			if(attached->GetBase() != NO_OWNER)
			{
				var plr = attached->GetBase();
				return GetHomebaseMaterial(plr, type) && GetWealth(plr) >= GetValue(0, type, attached, plr);
			}
			else if(CheckWorker() && attached->~IsProducerOf(worker, type))
			{
				return true;
			}
		}
	}
	return ret;
}

func RetrieveSendObject(object line, id type)
{
	return SendObjectThroughTube(type, line, ...);
}

func RetrieveProduceObject(object line, id type)
{
	BuyOrProduceSendObject(type, line, ...);
	return true;
}

func BuyOrProduceSendObject(id type, object line, arriveCallback, object excludeOrigin, failCallback, object realTarget) // TODO: Sort factories by "load", use very high "load" for buy-only
{
	if(GetDefCollectible(type))
	{
		var attached = Attached();
		if(attached)
		{
			if(attached->GetBase() != NO_OWNER)
			{
				var plr = attached->GetBase();
				var obj = Buy(type, plr, plr, attached, true);
				if(obj)
				{
					line = line || FindObject2(Find_Tube(), Find_Func("CanSendObject", this, obj));
					return line && line->SendObject(this, obj, arriveCallback, false, realTarget, ...);
				}
			}
			else if(CheckWorker() && attached->~IsProducerOf(worker, type))
			{
				AddQueue([type, line, arriveCallback, failCallback, realTarget]);
				//SetWorkerCommands(worker, [type, line, arriveCallback, failCallback], true);
			}
		}
	}
}

func AddQueue(array args)
{
	if(!produceQueue)
	{
		produceQueue = [args];
	}
	else
	{
		produceQueue[GetLength(produceQueue)] = args;
	}
	
	if(GetLength(produceQueue) == 1 || !GetCommand(worker))
	{
		ContinueQueue();
	}
	ShowQueue();
}

func ContinueQueue()
{
	if(GetLength(produceQueue) > 0)
	{
		SetWorkerCommands(worker, produceQueue[0], true);
	}
}

func RemoveQueued()
{
	ArrayErase(produceQueue, 0);
	ContinueQueue();
	ShowQueue();
}

func ShowQueue()
{
	if(GetLength(produceQueue) > 0)
	{
		var msgStr = "", showCount = 0, cnt = 1, lastID = produceQueue[i][0];
		for(var i = 1; i <= GetLength(produceQueue); ++i)
		{
			var id = produceQueue[i] && produceQueue[i][0];
			
			if(lastID == id)
			{
				++cnt;
			}
			else
			{
				if(cnt > 1)
				{
					msgStr = Format("|{{%i}} x%d%s", lastID, cnt, msgStr);
				}
				else
				{
					msgStr = Format("|{{%i}}%s", lastID, msgStr);
				}
				if(++showCount >= 10)
				{
					break;
				}
				cnt = 0;
			}
			
			lastID = id;
		}
		if(i < GetLength(produceQueue))
		{
			msgStr = Format("...%s", msgStr);
		}
		Message("@%s", this, msgStr);
	}
	else
	{
		Message("", this);
	}
}

func FactoryLoad() // TODO: TEST and FIXME
{
	var attached = Attached();
	if(attached && attached->GetBase() != NO_OWNER)
	{
		return 10; // maybe adjust this
	}
	else
	{
		return produceQueue && GetLength(produceQueue);
	}
}

func SetWorkerCommands(object worker, array args, bool checkIdle)
{
	if(!checkIdle || !GetCommand(worker))
	{
		var attached = Attached();
		if(attached)
		{
			AddCommand(worker, "Call", this, args, 0, 0, 0, "ProductionFinished");
			AddCommand(worker, "Put", attached, 0, 0, 0, 0, args[0]);
			AddCommand(worker, "Acquire", this, 0, 0, 0, 0, args[0]); // don't Acquire through tubes this time
			attached->~HowToProduce(worker, args[0]);
		}
	}
	else
	{
		AppendCommand(worker, "Call", this, args, 0, 0, 0, "SetWorkerCommands");
	}
}

func ProductionFinishedFailed(object worker, array args)
{
	RemoveQueued();
	Call(args[3], worker);
}

func ProductionFinished(object worker, array args)
{
	RemoveQueued();
	return args[0] && SendObjectThroughTube(args[0], args[1], args[2], false, args[4]);
}

func GetRetrievableObjects(object line, bool production)
{
	return GetSendableIDs(production);
}

func ProductionTitle()
{
	var attached = Attached();
	if(attached)
	{
		if(attached->GetBase() != NO_OWNER)
		{
			return "$Buy$";
		}
	}
	return _inherited(...);
}

func GetProducableIDs()
{
	var ret = [];
	var attached = Attached();
	if(attached)
	{
		if(attached->GetBase() != NO_OWNER)
		{
			var plr = attached->GetBase();
			for(var i = 0, type; type = GetHomebaseMaterial(plr, 0, i, C4D_StaticBack | C4D_Structure | C4D_Vehicle | C4D_Living | C4D_Object); ++i)
			{
				if(GetDefCollectible(type) && GetHomebaseMaterial(plr, type) && GetWealth(plr) >= GetValue(0, type, attached, plr))
				{
					ret[GetLength(ret)] = type;
				}
			}
		}
		else if(CheckWorker())
		{
			for(var i = 0, type; type = GetDefinition(i); ++i)
			{
				if(GetDefCollectible(type))
				{
					if(attached->~IsProducerOf(worker, type))
					{
						ret[GetLength(ret)] = type;
					}
				}
			}
		}
	}
	return ret;
}

func AttachObjectCondition(object caller)
{
	return _inherited(caller, Find_GrabPutGet(C4D_GrabGet), ...);
}

func AttachContextSend(object caller)
{
	[$SendObject$|Image=EX7I]
	return SendMenu(caller);
}

func SensorCallbacks()
{
	var ret = [["$SendObject$", BindCallback("SendObjectThroughTube", [1, 2])]];
	var attached = Attached();
	if(attached)
	{
		for(var part in [GetSendableIDs(), GetSendableIDs(true)])
		{
			for(var id in part)
			{
				ret[GetLength(ret)] = [Format("$SendObjectType$", GetName(0, id)), BindCallback("SendObjectThroughTube", [Bind(id), 2]), id];
			}
		}
	}
	return ret;
}

func CheckWorker()
{
	if(worker && !worker->GetAlive())
	{
		worker = 0;
	}
	return worker;
}
