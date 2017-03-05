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
	_inherited(...);
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
	
	var menu = [
		StructMenu_TextEntry(NONE, "$Status$"),
		StructMenu_TextEntry(MEPU, Format("$Damage$: %v/%v", GetDamage(), MaxDamage())),
		StructMenu_TextEntry(MEPU, Format("$Energy$: %v%%", energy)),
		StructMenu_BlankLine(),
		StructMenu_MenuEntry(pPilot->GetID(), "$Exit$", 0, "ExitPilot"),
		StructMenu_MenuEntry(Icon_Hatch, "$Heck$", 0, "Hatch"),
		StructMenu_ConditionalMenuEntry(Icon_Shield, "$Shield$", 0, HasShield(), "ToggleShield"),
		StructMenu_ConditionalMenuEntry(Icon_Cloak, "$Cloak$", 0, CanCloak(), "Cloak"),
		StructMenu_ConditionalMenuEntry(TEL4, "$Hyperspace$", 0, HasHyperdrive(), "Hyperspace")
		];
	
	var pGate;
	if(CanDialGate() && (pGate = FindStargate()))
	{
		menu[GetLength(menu)] = StructMenu_MenuEntry(pGate->GetID(), Format("$DialGate$", pGate->GetName()), 0, "Dial");
	}
	
	pPilot->CreateStructMenu(
	GetID(),
	FormatN("$DateTimeFormat$", ["Y", "M", "D", "h", "m", "s"], [GetSystemTime(0), GetSystemTime(1), GetSystemTime(3), GetSystemTime(4), GetSystemTime(5), GetSystemTime(6)]),
	this,
	menu);
}

private func Hatch() {}

protected func Dial()
{
	if(FindStargate()) FindStargate()->OpenChevronMenu(pPilot, this);
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

protected func Damage()
{
	if(GetDamage() >= MaxDamage())
	{
		return Destroy();
	}
}
private func InitializeWeapons() 	{ return []; }
private func InitializeInventory() 	{ return []; }
private func Destroy()				{ return Explode(50); }


public func FindStargate()	{ return FindObject2(Find_Func("IsStargate"), Find_Distance(800), Sort_Distance()); }
public func HasHyperdrive() { return false; }
public func CanCloak()		{ return false; }
public func HasShield()		{ return false; }
public func CanDialGate()	{ return false; }
public func ShieldRadius() 	{ return 200; 	}
public func MaxDamage()		{ return 500;	}
public func HyperspaceSize() { return 50; }