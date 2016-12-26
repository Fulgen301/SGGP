/*-- Grundfahrzeug --*/

#strict 2

local pPilot;
local shield;
local energy;

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
	CreateMenu(GetID(), pPilot, this, C4MN_Extra_None, Format("%04d-%02d-%02d %02d:%02d:%02d", GetSystemTime(), GetSystemTime(1), GetSystemTime(3),GetSystemTime(4), GetSystemTime(5), GetSystemTime(6)), 0, C4MN_Style_Dialog);
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
		var pGate = FindObject2(Find_Func("IsStargate"), Find_Distance(800));
		if(pGate) AddMenuItem(Format("$DialGate$", pGate->GetName()), "Dial", pGate->GetID(), pPilot);
	}
}

private func Hatch() {}

private func Dial()
{
  CallMessageBoard(0,false,"$GateName$",pPilot->GetOwner());
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

public func HasHyperdrive() { return false; }
public func CanCloak()		{ return false; }
public func HasShield()		{ return false; }
public func CanDialGate()	{ return false; }
public func ShieldRadius() 	{ return 200; 	}
public func MaxDamage()		{ return 500;	}
public func HyperspaceSize() { return 50; }