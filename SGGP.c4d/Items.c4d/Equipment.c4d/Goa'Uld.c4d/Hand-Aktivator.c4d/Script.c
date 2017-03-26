/*-- Hand-Activator --*/

#strict 2

local transporter;
local pUser;

func FindTransporters(int distance)
{
	if(FindObject2(Find_ID(RIGU))) return FindObjects(Find_ID(RIG1), Find_OCF(OCF_Fullcon), Sort_Distance(), ...);
	else return FindObjects(Find_ID(RIG1), Find_OCF(OCF_Fullcon), Find_Distance(distance || 150), Sort_Distance(), ...);
}

func Activate(object pCaller)
{
	Sound("Connect");
	SetOwner(GetOwner(pCaller));
	pUser = pCaller;
	var transporters = FindTransporters();

	for(var i = 0; i < GetLength(transporters); ++i)
	{
		transporters[i] = [transporters[i], LocalN("name", transporters[i]), MEPU];
	}

	if(!pCaller || !pCaller->~CreateSelectionMenu("ChooseTransporter", transporters, GetID(), "$ChooseTransporter$", this))
	{
		if(GetLength(transporters) > 0)
		{
			ChooseTransporter(0, transporters[0][0]);
		}
	}

	return 1;
}

func ChooseTransporter(id dummy, object pTransporter, bool fSpecial)
{
	transporter = pTransporter;

	Sound("rt_button1");

	if(fSpecial)
	{
		if(!transporter || !transporter->LocalN("ring2"))
		{
			Message("$NoTargetTransporter$", this);
			Sound("Error");
		}
		else
		{
			transporter->Activate(transporter->LocalN("ring2"));
		}
		return;
	}



	if(transporter)
	{
		var transporters = FindTransporters(500, Find_Exclude(transporter), Find_Func("IsFindable"));

		if(GetLength(transporters) > 0)
		{
			for(var i = 0; i < GetLength(transporters); ++i)
			{
				transporters[i] = [transporters[i], LocalN("name", transporters[i]), MEPU];
			}

			if(!pUser || !pUser->~CreateSelectionMenu("Go", transporters, RIG1, "$Dial$", this))
			{
				Go(0, transporters[0][0]);
			}
		}
		else
		{
			Message("$NoTargetTransporter$", this);
			Sound("Error");
		}
	}
}

public func Go(trash, tar)
{
	transporter->Activate(tar);
}

public func ConDesc()
{
	return "$ChooseTransporter$";
}

protected func Hit()		{ Sound("ClonkHit*"); }
