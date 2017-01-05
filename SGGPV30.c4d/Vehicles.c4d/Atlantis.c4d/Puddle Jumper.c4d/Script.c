/*--- Puddle Jumper ---*/

#strict 2
#include CVHC

local iExtra;
local Gate;
local iGet;
local iMess;
local iDrohne;
local cloaked;
local open;
local kindersicherung;
local lzd;
local naqu;
local arw;
local destroyed;

public func Initialize() 
{
	_inherited(...);
  kindersicherung = 0;
  CreateContents(LZD_);
  ScheduleCall(0,"LZDSet",4);
  SetAction("Opens");
  iExtra = 0;
  energy = 100;
  iGet = 10;
  AddDamageEffect(this);
	Icon_Hatch = PUD7;
	Icon_Shield = GOSG;
	Icon_Cloak = PUD2;
  return(1);
}

func CalcValue()
{
  return(150);
}

func Sounder()
{
  if(cloaked)  { return(1); }
  Sound("engine");
  return(1);
}

func LZDSet()
{
	if(FindObject2(Find_ID(LZD_), Find_Container(this))) lzd = FindObject2(Find_ID(LZD_), Find_Container(this));
  return(1);
}

public func Open()
{
  open=1;
  SetEntrance(1);
  return(1);
}

public func Close()
{
  open=0;
  SetEntrance(0);
  return(1);
}

public func MaxDamage() { return (500); }

public func OnDmg(int iDmg, int iType) 
{
	if(iType == DMG_Bio)		return(100);
	if(iType == DMG_Melee)		return(80);
	if(iType == DMG_Fire)		return(80);
	if(iType == DMG_Explosion)	return(0);

	return(30);
}

public func Damage()
{
  if(GetDamage() >= 300)
  {
   if(cloaked)
   {
    Cloak();
    Sound("Blast2");
   }
  }

  if(!FindObject(0,0,0,0,0,OCF_Alive,0,0,this))
  {
   if(!open)
   {
    SetAction("Opens");
   }
  }
  
  if(GetDamage(this) >= 500)
  {
   Call("Destroy");
   return(1);
  }
  return(1);
}

public func Aktiviti()
{
  if(iGet == 0)
  {
   iGet = 20;
  }
  
  iGet--;

  if(cloaked)
  {
   if(energy > 20)
   {
    if(iGet == 5)
    {
     if(!naqu)
     energy -= 1;
    }
   }
   
   if(energy <= 20)
   {
    Cloaking();
   }
  }

  if(kindersicherung)
  {
   if(!FindObject(0,0,0,0,0,OCF_Alive,0,0,this))
   {
    if(!open)
    {
     SetAction("Open");
    }
   }
  }

  if(iMess == 1)
  {
   Message("%v Energie",this,energy);
  }

  if(energy >=100)
  {
   energy = 100;
  }

  if(energy < 100)
  {
  
   if(iGet == 5)
   {
    if(!cloaked)
    {
     energy ++;
     if(naqu)
     {
      energy += 2;
      return(1);
     }
    }
   }
   
  }


  if(!FindObject(0,0,0,0,0,OCF_Alive,0,0,this))
  {
   if(GetAction() == "Fly")
   {
    SetAction("Stand");
   }
  }

  if(open)
  {
   SetEntrance(1);
   return(1);
  }
  
  if(!open)
  {
   SetEntrance(0);
   return(1);
  }

  if(GetAction(this) == "Tarned")
  {
   SetEntrance(1);
   return(1);
  }

  if(GetAction(this) == "Stand")
  {
   SetEntrance(1);
   return(1);
  }

  SetEntrance(0);
  return(1);
}

public func ContactBottom()
{
  if(GetAction() == "Fly")
  {
   SetAction("Stand");
   return(1);
  }
  return(1);
}

protected func ContainedUpDouble()
{
  if(GetAction() == "Tarned") { return(0); }
  if(GetAction() == "Turn") { return(0); }
  SetComDir(COMD_Stop);
  SetXDir(0);
  SetYDir(0);
  return(1);
}

protected func MakeMenu(object pCaller)
{
  _inherited(pCaller, ...);
  AddMenuItem("Motor Aus","Enginestop",PUD5,Par(0));

  if(FindObject2(Find_Distance(300),Find_PathFree(),Find_ID(JUDO),Find_Func("Ready")))
  {
   AddMenuItem("Andocken","Docking",JUDO,Par(0));
  }
  else
  {
   if(FindObject2(Find_Distance(300),Find_PathFree(),Find_ID(JUDO)))
   {
    AddMenuItem("Abdocken","AbDocking",JUDO,Par(0));
   }
  }
  
  if(FindContents(TANG))
  {
   if(!naqu)
   {
    AddMenuItem("Reaktor einbauen","NaEiBa",TANG,Par(0));
   }
  }
  if(naqu)
  {
   AddMenuItem("Reaktor ausbauen","NaAuBa",TANG,Par(0));
  }
  
  if(FindContents(ARW_))
  {
   if(!arw)
   {
    AddMenuItem("Disruptor einbauen","ArwEiBa",ARW_,Par(0));
   }
  }
  if(arw)
  {
   AddMenuItem("EM-Welle abfeuern","ArwFire",ARW_,Par(0));
   AddMenuItem("Disruptor ausbauen", "ArwAuBa", ARW_, Par(0));
  }
  return(1);
}


func Docking()
{
  var hlp;
  if(FindObject2(Find_Distance(300),Find_PathFree(),Find_ID(JUDO),Find_Func("Ready")))
  {
   hlp = FindObject2(Find_Distance(300),Find_PathFree(),Find_ID(JUDO),Find_Func("Ready"));
  }
  else
  {
   return(1);
  }
  hlp->Dock(this);
  return(1);
}

func AbDocking()
{
  var hlp;
  if(FindObject2(Find_Distance(300),Find_PathFree(),Find_ID(JUDO)))
  {
   hlp = FindObject2(Find_Distance(300),Find_PathFree(),Find_ID(JUDO));
  }
  else
  {
   return(1);
  }
  hlp->Undock();
  return(1);
}

func ArwFire()
{
  if(GetAction() == "Turn")  return(0);
  if(cloaked) 				 return(0);

  if(!arw)
  {
   return(1);
  }
  if(energy >=90)
  {
   var ammo = CreateObject(ARWW,0,20,GetOwner(pPilot));
   ammo->Launch(180,20,300,10,100,0);
   MuzzleFlash(100,this,0,20,180,RGBa(0,0,255,0));
   Sound("Waveshot");
   energy -= 90;
   return(1);
  }
  Sound("start");
  return(1);
} 
  
func ArwEiBa()
{
  if(FindContents(ARW_))
  {
   if(!arw)
   {
    FindContents(ARW_)->RemoveObject();
    Sound("Connect");
    arw=1;
   }
  }
  return(1);
}

func ArwAuBa()
{
	if(arw)
	{
		CreateContents(ARW_);
		Sound("Connect");
		arw = 0;
	}
}
func NaEiBa()
{
  if(FindContents(TANG))
  {
   if(!naqu)
   {
    FindContents(TANG)->RemoveObject();
    Sound("Connect");
    naqu=1;
   }
  }
  return(1);
}

func NaAuBa()
{
  if(naqu)
  {
   CreateContents(TANG);
   Sound("Connect");
   naqu=0;
  }
  return(1);
}

func Hatch()
{
  if(GetAction() == "Stand")
  {
   if(open)
   {
    SetAction("Close");
    return(1);
   }
  
   if(!open)
   {
    SetAction("Opens");
    return(1);
   }
  }
  
  if(GetAction() == "Open")
  {
   if(open)
   {
    SetAction("Close");
    return(1);
   }
  
   if(!open)
   {
    SetAction("Opens");
    return(1);
   }
  }
  return(1);
}

func Energy()
{
  if(iMess == 1)
  {
   iMess --;
   return(1);
  }

  if(iMess == 0)
  {
   iMess ++;
   return(1);
  }
}

func Enginestop()
{
  if(GetAction() == "Fly")
  {
   SetAction("Stand");
  }
  return(1);
}


func EMPShock()
{
  if(cloaked)
  {
   Cloak();
  }

  EMPShockEffect(50);
  energy -= 50;
  DoDamage(5);
  return(1);
}

public func Schaden()
{
  Message("Schaden: %v|Verbleibend: %v" ,this , GetDamage(this) , 500-GetDamage(this));
  return(1);
}

public func Destroy()
{
  if(destroyed) return;
  else destroyed = true;
  if(lzd)
  {
   lzd->Entf();
  }
  Explode(50);
  return(1);
}

func Cloak()
{
  if(energy < 20)
  {
   Sound("start");
   return(1);
  }

  if(GetDamage() >= 300)
  {
   if(!cloaked)
   {
    Sound("start");
    return(1);
   }
  }
  Cloaking();
  return(1);
}


func Cloaking()
{
  if(cloaked)
  {
   if(GetAction() == "Fly")
   {
    cloaked = 0;
    SetAction("Tarnaus2");
    Sound("JumperUnCloak");
    return(1);
   }
   
   if(GetAction() == "Stand")
   {
    cloaked = 0;
    SetAction("Tarnaus");
    Sound("JumperUnCloak");
    return(1);
   }
  }
  
  if(!cloaked)
  {
   if(GetAction() == "Fly")
   {
    cloaked = 1;
    SetAction("Tarnan2");
    Sound("JumperCloak");
    return(1);
   }
   
   if(GetAction() == "Stand")
   {
    cloaked = 1;
    SetAction("Tarnan");
    Sound("JumperCloak");
    return(1);
   }
  }
  return(1);
}

public func Visible()
{
  SetVisibility(VIS_All);
  SetClrModulation(0);  
  return(1);
}

public func Invisible()
{
  SetOwner(GetOwner(pPilot));
  SetVisibility(VIS_Owner);
  SetClrModulation(RGBa(0,0,100,100));  
  return(1);
}

public func ExitPilot(pCaller) 
{
  if(!open)
  {
   Hatch();
   return(1);
  }

  pPilot->Exit();
  pPilot->SetAction("Walk");
  
  if(GetDir() == 0)
  {
   pPilot->SetPosition(GetX(pPilot)+30,GetY(pPilot)+15);
   SetEntrance(1);
   return(1);
  }
  
  pPilot->SetPosition(GetX(pPilot)-30,GetY(pPilot)+15);
  SetEntrance(1);
  return(1);
}

protected func ContainedThrow(pCaller)
{
  SetOwner(GetOwner(pCaller));
  if(GetAction() == "Stand") return(0);
  if(GetAction() == "Opens") return(0);
  if(GetAction() == "Open")  return(0);
  if(GetAction() == "Close") return(0);
  if(GetAction() == "Turn")  return(1);
  if(cloaked) 				 return(1);

  if(energy < 10)
  {
   Sound("start");
   return(1);
  }

  Sound("drone_shot");
  energy -= 10;

  iDrohne = CreateObject(PUDD,0,15);
  SetOwner(GetOwner(this),iDrohne);

  if(GetDir(this) == 1)
  {
   iDrohne->SetXDir(100);
   FindObject(PUDD,-20,-20,40,40)->SetR(90);
  }

  if(GetDir(this) == 0)
  {
   iDrohne->SetXDir(-100);
   FindObject(PUDD,-20,-20,40,40)->SetR(270);
  }
  return(1);
}

protected func ContainedUp()
{
  if(GetAction() == "Turn") { return(0); }

  if(GetAction() == "Fly")
   {
   if(GetComDir() == COMD_UpLeft || GetComDir() == COMD_UpRight) SetComDir(COMD_Up);
   if(GetComDir() == COMD_Down) SetComDir(COMD_Up);
   if(GetComDir() == COMD_Left) SetComDir(COMD_UpLeft);
   if(GetComDir() == COMD_DownLeft) SetComDir(COMD_Left); 
   if(GetComDir() == COMD_DownRight) SetComDir(COMD_Right);
   if(GetComDir() == COMD_Right) SetComDir(COMD_UpRight);
   if(GetComDir() == COMD_Stop) SetComDir(COMD_Up);
   return(true);
   }
   
   if(GetAction() == "Stand")
   {
    SetAction("Fly");
    return(1);
   }
  return(1);
}

protected func ContainedDown()
{
   if(!(GetAction() == "Fly")) 
   { 
    return(0); 
   }

   if(GetComDir() == COMD_DownLeft ||GetComDir() == COMD_DownRight)
   {
    SetComDir(COMD_Down);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Up)
   {
    SetComDir(COMD_Stop);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Left) 
   {
    SetComDir(COMD_DownLeft);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_UpLeft)
   {
    SetComDir(COMD_Left);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Stop)
   {
    SetComDir(COMD_Down);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Right) 
   {
    SetComDir(COMD_DownRight);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_UpRight)
   {
    SetComDir(COMD_Right);
    SetEntrance(0);
   }
  return(1);
}

protected func ContainedRight()
{
  if(GetAction() == "Tarnan")  return(1);
  if(GetAction() == "Tarnan2")  return(1);
  if(GetAction() == "Tarnaus")  return(1);
  if(GetAction() == "Tarnaus2")  return(1);
  if(GetAction() == "opens")  return(1);
  if(GetAction() == "open")  return(0);
  if(GetAction() == "close")  return(1);
  if(GetAction() == "Turn") return(1);
  if(open)					return(0);
  if(iExtra) return(0);
  SetCommand(this,"None");
  SetComDir(COMD_Right);
  
  if(GetDir() == DIR_Left)
  {
   SetAction("Turn");
   iExtra++;
  }
  return(1);
}

protected func ContainedLeft()
{
  if(GetAction() == "Tarnan")  return(1);
  if(GetAction() == "Tarnan2")  return(1);
  if(GetAction() == "Tarnaus")  return(1);
  if(GetAction() == "Tarnaus2")  return(1);
  if(GetAction() == "opens")  return(0);
  if(GetAction() == "open")  return(0);
  if(GetAction() == "close")  return(0);
  if(GetAction() == "Turn") return(1);
  if(iExtra) return(0);
  if(open)					return(0);
  
  SetComDir(COMD_Left);  
  if(GetDir() == DIR_Right)
  {
   SetAction("Turn");
   iExtra++;
  }
  return(true);
}

func Turned()
{
  if(GetDir() == DIR_Left) SetDir(DIR_Right);
  else SetDir(DIR_Left);
  iExtra = 0;
  return(true);
}   

public func Stop() 
{
  SetComDir(COMD_Stop);
  SetYDir(0);
  SetXDir(0);
  return(true);
}

protected func ContainedRightDouble()
{
  if(GetAction() != "Fly") { return(0); }

  if(GetDir() == DIR_Right)
   {
   SetComDir(COMD_Stop);
   SetYDir(0);
   SetComDir(COMD_Right);
   }
  else
   {
   SetAction("Wenden");
   }
  return(true);
}

protected func ContainedLeftDouble()
  {
   if(GetAction() == "Tarned") { return(0); }
   if(!(GetAction() == "Fly")) { return(0); }

  if(GetDir() == DIR_Left)
   {
   SetComDir(COMD_Stop);
   SetYDir(0);
   SetComDir(COMD_Left);
   }
  else
   {
   SetAction("Wenden");
   }
  return(true);
  }

public func Starting()
{
  if(GetAction() == "Stand")
  SetAction("Fly",GetActionTarget(0),GetActionTarget(1));
  if(GetDir() == DIR_Left) SetComDir(COMD_UpLeft);
  if(GetDir() == DIR_Right) SetComDir(COMD_UpRight);
  return(true);
}



func IsMachine() 		{ return(1); }

func IsBulletTarget()    { return(1); }

public func CanDialGate() { return GetDamage() < 300; }
public func CanCloak()	  { return true; }
public func GetRace() { return SG1_Ancient; }