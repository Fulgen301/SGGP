/*-- Grundfahrzeug --*/

#strict 2

local pPilot;
local shield;
local energy;
local chevrons;

// Weapons
local aWeapons;

// Inventory
local aInventory;

// Symbols
local Icon_MenuPoint;
local Icon_Hyperdrive;
local Icon_Exit;
local Icon_Shield;
local Icon_Cloak;
local Icon_Hatch;

protected func Initialize()
{
	aWeapons = InitializeWeapons();
	if(GetType(aWeapons) != C4V_Array) aWeapons = [];
	
	aInventory = InitializeInventory();
	if(GetType(aInventory) != C4V_Array) aInventory = [];
	
	Icon_MenuPoint = MEPU;
	Icon_Hyperdrive = TEL4;
	Icon_Hatch = TEM4;
	Icon_Shield = GOSG;
	Icon_Cloak = TEM1;
}

protected func ContainedDig(object pCaller)
{
	MakeMenu(pCaller);
	return true;
}

protected func MakeMenu(object pCaller)
{
	pPilot = pCaller;
	SetOwner(GetOwner(pPilot));
	CreateMenu(GetID(), pPilot, this, C4MN_Extra_None, FormatN("$DateTimeFormat$", ["Y", "M", "D", "h", "m", "s"], [GetSystemTime(0), GetSystemTime(1), GetSystemTime(3), GetSystemTime(4), GetSystemTime(5), GetSystemTime(6)]), 0, C4MN_Style_Dialog);
	AddMenuItem("$Status$", 0, NONE, pPilot);
	AddMenuItem(Format("$Damage$: %v/%v", GetDamage(), MaxDamage()), 0, MEPU, pPilot);
	AddMenuItem(Format("$Energy$: %v%%", energy), 0, MEPU, pPilot);
	AddMenuItem(" ", 0, NONE, pPilot, 0, 0, " ");
	
	AddMenuItem("$Exit$", "ExitPilot", pPilot->GetID(), pPilot);
	AddMenuItem("$Heck$", "Hatch", Icon_Hatch, pPilot);
	if(HasShield()) AddMenuItem("$Shield$", "ToggleShield", Icon_Shield, pPilot);
	if(CanCloak()) AddMenuItem("$Cloak$", "Cloak", Icon_Cloak, pPilot);
	if(HasHyperdrive()) AddMenuItem("$Hyperspace$", "Hyperspace", TEL4, pPilot);
	
	if(CanDialGate())
	{
		var pGate = FindStargate();
		if(pGate) AddMenuItem(Format("$DialGate$", pGate->GetName()), "Dial", pGate->GetID(), pPilot);
	}
}

private func Hatch() {}

protected func Dial()
{
	OpenChevronMenu(pPilot);
}

public func OpenChevronMenu(object pCaller)
{
	if(!FindStargate()) return;
	CreateMenu(GetID(), pCaller, 0, 0, GetName());
	
	if(GetType(chevrons) != C4V_Array) chevrons = [];
	if(GetLength(chevrons) == 7) return AddMenuItem("Fertig", "Finish", GetID(), pCaller);
	for(var cv in FindStargate()->GetAllChevrons())
	{
		var icon;
		if(GetIndexOf(cv, chevrons) == -1)
		{
			icon = C4Id(Format("%s%02d", FindStargate()->ChevronPrefix(), cv));
		}
		else
			icon = CXRL;
		AddMenuItem(GetName(), Format("ChevronSelection(%d)", cv), icon, pCaller);
	}
}

public func MenuQueryCancel()
{
	chevrons = [];
}

public func ChevronSelection(int cv)
{
	if(GetIndexOf(cv, chevrons) != -1)
	{
		Sound("start");
		OpenChevronMenu(pPilot);
		return;
	}
	Sound("Connect");
	chevrons[GetLength(chevrons)] = cv;
	if(FindStargate())
	{
		FindStargate()->~Chevron(GetLength(chevrons));
		if(GetLength(chevrons) == 7)
		{
			FindStargate()->~Dial(chevrons);
		}
	}
	OpenChevronMenu(pPilot);
}

public func Finish()
{
	if(!FindStargate()) return Sound("start");
	FindStargate()->~Chevron();
	FindStargate()->Dial(chevrons);
	chevrons = [];
}

public func InputCallback(string szName)
{
	var pGate = FindObject2(Find_Func("IsStargate"),Find_Distance(800),Sort_Distance());
	if(pGate) pGate->Dial(szName);
}

private func ExitPilot()	{ if(pPilot) pPilot->Exit();}

private func ToggleShield()
{
	if(shield) return shield->RemoveObject();
	shield = this->CreateShield(ShieldRadius(), GetOwner());
}

private func Hyperspace()
{
	var cursor = CreateObject(CURS);
	cursor->SetBeamer(this,pPilot->GetOwner(),pPilot);
	SetCursor(pPilot->GetOwner(), cursor);
}

public func Okay(int iX, int iY)
{
	if(GetDir() == DIR_Left) HyperdriveWindow(-100, 0, HyperspaceSize(), iX, iY, this);
	else HyperdriveWindow(100, 0, HyperspaceSize(), iX, iY, this);
	energy -= 50;
}

private func InitializeWeapons() { return []; }
private func InitializeInventory() { return []; }


public func FindStargate()	{ return FindObject2(Find_Func("IsStargate"), Find_Distance(800), Sort_Distance()); }
public func HasHyperdrive() { return false; }
public func CanCloak()		{ return false; }
public func HasShield()		{ return false; }
public func CanDialGate()	{ return false; }
public func ShieldRadius() 	{ return 200; 	}
public func MaxDamage()		{ return 500;	}
public func HyperspaceSize() { return 50; }