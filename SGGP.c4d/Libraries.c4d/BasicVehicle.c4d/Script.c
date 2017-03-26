/*-- Grundfahrzeug --*/

#strict 2

local pPilot;
local shield;
local energy;
local chevrons;
local shType;
local help;

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

protected func Construction()
{
    _inherited(...);
    AddEffect("IntShieldCheck", this, 1, 50, this);
}

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
    if(shType == 0) return;
    
    else if(shType == 1)
    {
        if(GetEffect("HazardShield", this)) return RemoveEffect("HazardShield", this);
        AddEffect("HazardShield", this, 99, 3, 0, HSHD, ShieldRadius(shType));
    }
    
    
    else if(shType == 2)
    {
        if(GetEffect("BounceShield", this)) return RemoveEffect("BounceShield", this);
        AddEffect("BounceShield", this, 99, 1, this);
    }
	
    else if(shType == 3)
    {
        if(shield) return shield->RemoveObject();
        shield = this->CreateShield(ShieldRadius(shType), GetOwner());
    }
}

public func FxBounceShieldTimer()
{
		//Effektbearbeitung
		help += 10;
		var pX;
		var pY;
		pX = Cos(help, ShieldRadius(shType));
		pY = Sin(help, ShieldRadius(shType));
		CreateParticle("PSpark", pX, pY, RandomX(-10, 10), RandomX(-10, -20), RandomX(40, 60));
		pX = Cos(help + 180, ShieldRadius(shType));
		pY = Sin(help + 180, ShieldRadius(shType));
		CreateParticle("PSpark", pX, pY, RandomX(-10, 10), RandomX(-10, -20), RandomX(40, 60));

   //Trefferbearbeitung 2
   for(var target in FindObjects(Find_Distance(ShieldRadius(shType)),Find_Not(Find_Distance(ShieldRadius(shType) - ShieldRadius(shType)/8))))
   {
    //Objekt wird nicht abgestoßen, wenn es sich nicht bewegt!
    if((GetXDir(target) + GetYDir(target)) == 0)
    {
     return(1);
    }

    if (GetCategory(target) & C4D_Structure)
    {
    	return(1);
    }

    //Normale Kugel
    if(target->~IsBullet() == 1)
    {
     target->RemoveObject();
//     energy -= 2;
     return(1);
    }

    //KULL Ignorieren
    if(GetID(target) == KULL)
    {
     if(target->~HasGear())
     {
      return(1);
     }
    }
    
    if(GetID(target) == PUD_) return;


    //Meteorid
    if(GetID(target) == METO)
    {
     target->~Hit();
	 energy -= 5;
     return(1);
    }

	if (GetID(target) == REDR)
	{
		target->~Hit();
		energy -= 5;
		return(1);
	}

    //Rakete
    if(GetID(target) == MISS)
    {
     target->~Hit();
     energy -= 10;
     if(!target)
     {
      return(1);
     }
    }

    //Lenkrakete
    if(GetID(target) == HMIS)
    {
     target->~Hit();
     energy -= 13;
     if(!target)
     {
      return(1);
     }
    }

    /*if(GetOCF(target) & OCF_Construct())
    {
     return(1);
    }*/

    target->~SetAction("Walk");
    target->SetXDir((GetX(target)-RandomX(GetX()+2,GetX()-2)) / 5);
    target->SetYDir((GetY(target)-GetY()) / 5);
   }
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

protected func OnDmg(int iDmg, int iType)
{
    if(GetEffect("HazardShield", this))
    {
        if(iType == DMG_Energy) return 100;
        return 50;
    }
    return 0;
}

protected func Damage(int iDamage)
{
    if(GetEffect("HazardShield", this))
    {
        EffectCall(this, GetEffect("HazardShield", this), "BulletHit");
        energy -= BoundBy(iDamage / 10, 1, 50);;
    }
	if(GetDamage() >= MaxDamage())
	{
		return Destroy();
	}
}

public func IsUpgradeable(id idUpgrade)
{
    if(idUpgrade == HSHD && shType <= 3 && GetWealth(GetOwner(pPilot)) >= 50) return "$UpgradeShield$";
}

public func Upgrade(id idUpgrade)
{
    if(HasShield() && idUpgrade == HSHD && shType <= 3 && GetWealth(GetOwner(pPilot)) >= 50)
    {
        ToggleShield();
        DoWealth(GetOwner(pPilot), -50);
        shType++;
        ToggleShield();
        return true;
    }
}

protected func FxIntShieldCheckTimer()
{
    if(GetShield())
    {
        if(HasShield()) energy -= shType;
        else ToggleShield();
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

public func ShieldRadius(int shType)
{
    if(shType == 1) return 1700;
    if(shType == 2) return ShieldRadius(1)/10;
    if(shType == 3) return 200;
}

public func MaxDamage()		{ return 500;	}
public func HyperspaceSize() { return 50; }
public func GetShield()     { return shield || GetEffect("BounceShield", this) || GetEffect("HazardShield", this); }