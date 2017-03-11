//*-- Der Ringtransporter --*//
//*--      NORMAL     --*//

#strict 2

local ring;
local name;
local put;
local ring2;
local target;

static RIG1_Number;

//Automatische Namenssetzung des Transporters

protected func Construction()
{
	ring2 = CreateObject(RIG3,0,0,GetOwner());
	ring2->LocalN("target") = this;
}
public func Initialize()
{
	name = Format("Transporter %d", ++RIG1_Number);
}

protected func Destruction()
{
	if(ring2) ring2->RemoveObject();
}

public func IsFindable()
{
	return GetAction() == "Idle" && name != "Off";
}

public func Teltak() { return true; }

//Steuert die Treffbarkeit
public func IsBulletTarget()
{
	return !ActIdle();
}

//Schadenssteuerung
public func Damage()
{
	if(!put)
	{
		if(GetDamage(this()) >= 250)
		{
			put = 1;
			CreateObject(ROCK,-30,-20)->Explode(20);
			CreateObject(ROCK,10,5)->Explode(25);
			CreateObject(ROCK,0,20)->Explode(30);
			Explode(40);
		}
	}
	return(1);
}

//Manuelle Namnessetzung des Transporters
public func SetName(lName)
{
	name = lName;
	Message("<c ff0000> Neuer Name: </c>|<c 0000ff>%v</c>",this,name);
}

//Überprüft die gültigkeit des Transporters
public func IsValid(target)
{
	if(!target)
	{
		return true;
	}

	if((GetID(target) != GetID(this)) && (GetID(target) != RIG3))
	{
		return true;
	}
	return false;
}

//Start mit Auswahl
public func Activate(chooser)
{
	if(!ActIdle())
	{
		Sound("rt_error");
		return;
	}

	if(IsValid(chooser))
	{
		Sound("rt_error");
		return;
	}

	ring = chooser;
	ring -> Fake();
	Sound("rt_small",0,0,50);
	SetAction("Up");
}

//Quickstart
public func Quick(choose)
{
	if(!ActIdle())
	{
		Sound("rt_error");
		return;
	}

	if(choose)
	{
		Activate(choose);
		return;
	}

	ring = FindObject(GetID(this),0,0,-1,-1);
	ring -> Fake();
	Sound("rt_small",0,0,50);
	SetAction("Up");
}

func FindTransportObjects(object ring)
{
	return FindObjects(ring->Find_InRect(-25, -25, 50, 51), Find_Not(Find_Or(Find_Category(C4D_Structure), Find_Category(C4D_StaticBack), Find_Category(C4D_Parallax), Find_Func("IsTree"), Find_Func("RejectTransport", ring))), ...);
}

public func Beam()
{
	for(var transport in [[this, ring, FindTransportObjects(ring)], [ring, this, FindTransportObjects(this)]])
	{
		for(var obj in transport[2])
		{
			SetPosition(GetX(obj) - GetX(transport[1]) + GetX(transport[0]), GetY(obj) - GetY(transport[1]) + GetY(transport[0]), obj);
		}
	}
}

public func SizeCheck(pObj)
{
	if(GetDefCoreVal("Width",0,GetID(pObj)) > GetDefCoreVal("Height",0,GetID(pObj)))
	{
		if(GetDefCoreVal("Width",0,GetID(pObj)) > 75)
		{
			return true;
		}
	}

	if(GetDefCoreVal("Height",0,GetID(pObj)) > GetDefCoreVal("Width",0,GetID(pObj)))
	{
		if(GetDefCoreVal("Height",0,GetID(pObj)) > 75)
		{
			return true;
		}
	}
	return false;
}


public func Fake()
{
	Sound("rt_small",0,0,50);
	SetAction("Fake");
}

public func SolidUp()
{
	var phas;
	phas = GetPhase();
	SetSolidMask(phas*100,171,100,57,-25);
}

public func SolidLight()
{
	SetSolidMask(0,228,100,57,-25);
}

public func SolidDown()
{
	var phas;
	var help;
	phas = GetPhase();
	help = 1500 - (phas*100);
	SetSolidMask(help,171,100,57,-25);
}

public func GetRace() { return SG1_Ancient | SG1_Goauld; }
