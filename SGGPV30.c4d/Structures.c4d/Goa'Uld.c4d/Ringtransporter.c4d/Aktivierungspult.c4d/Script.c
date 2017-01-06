#strict 2

local pTo;
local transporter;

func Initialize()
{
	SetTransporter(0, FindTransporters()[0]);
}

public func IsBulletTarget()
{
	return !ActIdle();
}

public func Damage()
{
	if(GetDamage(this) >= 100)
	{
		Explode(30);
	}
}

func CheckTransporter(object pCaller)
{
	if(!transporter)
	{
		PlayerMessage(GetController(pCaller), "$NoTransporterAssigned$", this);
		Sound("Error");
		return false;
	}
	return true;
}

public func ControlDigDouble(pCaller)
{
	if(!CheckTransporter(pCaller))
	{
		return 1;
	}

	if(!ActIdle())
	{
		Sound("rt_error");
		return 1;
	}

	Sound("rt_button1");

	SetOwner(GetOwner(pCaller));

	var transporters = FindTransporters(500, Find_Exclude(transporter), Find_Func("IsFindable"));

	if(GetLength(transporters) > 0)
	{
		for(var i = 0; i < GetLength(transporters); ++i)
		{
			transporters[i] = [transporters[i], LocalN("name", transporters[i]), MEPU];
		}

		if(!pCaller || !pCaller->~CreateSelectionMenu("Go", transporters, RIG1, "$Dial$", this))
		{
			Go(0, transporters[0][0]);
		}
	}
	else
	{
		Message("$NoTargetTransporter$", this);
		Sound("Error");
	}
	return 1;
}

public func Go(trash, tar)
{
	pTo = tar;
	if(transporter)
	{
		SetAction("Fuse");
		Sound("rt_button2");
	}
	else
	{
		Sound("rt_error");
	}
}

public func Start()
{
	if(transporter)
	{
		transporter->Activate(pTo);
	}
	else
	{
		Sound("rt_error");
	}
}

public func ControlRightDouble(pCaller)
{
	if(CheckTransporter(pCaller))
	{
		CallMessageBoard(0, false, "$EnterName$", GetController(pCaller));
	}
	return 1;
}

public func ControlLeftDouble(pCaller)
{
	if(CheckTransporter(pCaller) && transporter->LocalN("ring2"))
	{
		pTo = transporter->LocalN("ring2");
		Sound("rt_button2");
		SetAction("Fuse");
	}
	else
	{
		Sound("rt_error");
	}
}

func ControlUpDouble(object pCaller)
{
	var transporters = FindTransporters();

	for(var i = 0; i < GetLength(transporters); ++i)
	{
		transporters[i] = [transporters[i], LocalN("name", transporters[i]), MEPU];
	}

	if(!pCaller || !pCaller->~CreateSelectionMenu("SetTransporter", transporters, GetID(), "$AssignTransporter$", this))
	{
		if(GetLength(transporters) > 0)
		{
			SetTransporter(0, transporters[0][0]);
		}
	}
}

func FindTransporters(int distance)
{
	return FindObjects(Find_ID(RIG1), Find_OCF(OCF_Fullcon), Find_Distance(distance || 150), Sort_Distance(), ...);
}

func SetTransporter(id dummy, object pTransporter)
{
	transporter = pTransporter;
}

func InputCallback(string szName)
{
	if(transporter && szName && szName != "")
	{
		transporter->SetName(szName);
	}
}

func Grabbed(object pByObject, bool fGrab)
{
	if(fGrab && transporter)
	{
		PlayerMessage(GetController(pByObject), "%s", this, transporter->LocalN("name"));
		pByObject->CreateSelectMark()->MarkObject(transporter, 35);
	}
}

public func GetRace() { return SG1_Ancient | SG1_Goauld; }
