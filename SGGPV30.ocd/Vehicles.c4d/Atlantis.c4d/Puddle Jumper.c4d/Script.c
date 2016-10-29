/*--- Puddle Jumper ---*/

#strict

local iExtra;
local Gate;
local iEnergy;
local iGet;
local iMess;
local iDrohne;
local pUser;
local cloaked;
local open;
local kindersicherung;
local lzd;
local naqu;
local arw;
local destroyed;

public func Initialize() 
{
  kindersicherung = 0;
  CreateContents(LZD_);
  ScheduleCall(0,"LZDSet",4);
  SetAction("Opens");
  iExtra = 0;
  iEnergy = 100;
  iGet = 10;
  AddDamageEffect(this);
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
  if(FindObject(LZD_,0,0,0,0,OCF_Collectible(),0,0,this()))
  {
   lzd=FindObject(LZD_,0,0,0,0,OCF_Collectible(),0,0,this());
  }
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

public func MaxDamage() { return (300); }

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

  if(!FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))
  {
   if(!open)
   {
    SetAction("Opens");
   }
  }
  
  if(GetDamage(this()) >= 500)
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
   if(iEnergy > 20)
   {
    if(iGet == 5)
    {
     if(!naqu)
     iEnergy -= 1;
    }
   }
   
   if(iEnergy <= 20)
   {
    Cloaking();
   }
  }

  if(kindersicherung)
  {
   if(!FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))
   {
    if(!open)
    {
     SetAction("Open");
    }
   }
  }

  if(iMess == 1)
  {
   Message("%v Energie",this(),iEnergy);
  }

  if(iEnergy >=100)
  {
   iEnergy = 100;
  }

  if(iEnergy < 100)
  {
  
   if(iGet == 5)
   {
    if(!cloaked)
    {
     iEnergy ++;
     if(naqu)
     {
      iEnergy += 2;
      return(1);
     }
    }
   }
   
  }


  if(!FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))
  {
   if(GetAction() eq "Fly")
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

  if(GetAction(this()) eq "Tarned")
  {
   SetEntrance(1);
   return(1);
  }

  if(GetAction(this()) eq "Stand")
  {
   SetEntrance(1);
   return(1);
  }

  SetEntrance(0);
  return(1);
}

public func ContactBottom()
{
  if(GetAction() eq "Fly")
  {
   SetAction("Stand");
   return(1);
  }
  return(1);
}

protected func ContainedUpDouble()
{
  if(GetAction() eq "Tarned") { return(0); }
  if(GetAction() eq "Turn") { return(0); }
  SetComDir(COMD_Stop());
  SetXDir(0);
  SetYDir(0);
  return(1);
}

protected func ContainedDig(pCaller)
{
  pUser = pCaller;
  SetOwner(GetOwner(pUser));
  var title;
  if(FindObject2(Find_Distance(800),Find_Func("IsStargate")) && GetDamage() < 200)
  {
	  title = FindObject2(Find_Distance(800),Find_Func("IsStargate"))->GetName();
  }
  else title = "Jumper";
  CreateMenu(PUD_, pUser, 0, 0, title, 0, 1);	

  AddMenuItem("Aussteigen","Exit",PUD1,pCaller);
  AddMenuItem("Tarnung","Cloak",PUD2,Par(0));
  AddMenuItem("Schadensabfrage","Schaden",PUD4,Par(0));
  AddMenuItem("Motor Aus","Enginestop",PUD5,Par(0));
  AddMenuItem("Energieanzeige","Energy",PUD6,Par(0));
  AddMenuItem("Heckluke","Luke",PUD7,Par(0));
  if(iEnergy >= 50 && EXTENDED_MODE)
  {
	  AddMenuItem("Hyperantrieb","Hyperspace", MEPU,pUser, 0, pUser);
  }
  if(FindObject2(Find_Distance(800),Find_Func("IsStargate")))
  {
   if(GetDamage() < 200)
   {
    AddMenuItem("Gate anwählen","DialGate",STGT,pUser);
   }
  }

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

protected func Hyperspace(id dummy, object pCaller)
{
	var cursor = CreateObject(CURS,0,0,pCaller->GetOwner());
	cursor->SetBeamer(this, pCaller->GetOwner(),pCaller);
	SetCursor(pCaller->GetOwner(), cursor);
}

public func Okay(int x, int y)
{
	Cloak();
	iEnergy -= 50;
	TravelInHyperspace(this, x, y, 30);
	Schedule("Cloak()",1);
}

func DialGate()
{
  CallMessageBoard(0,false,"Gatename:",GetOwner(pUser));
  return(1);
}

func InputCallback(string pGate)
{ 
  if(!FindObject2(Find_Func("IsStargate"),Find_Distance(800),Sort_Distance()))
  {
   Message("<c ff0000>Kein Gate in Reichweite!</c>",this());
   return(1);
  }
  else
  {
   FindObject2(Find_Func("IsStargate"),Find_Distance(800),Sort_Distance())->Dial(pGate);
   return(1);
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
  hlp->Dock(this());
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
  if(GetAction() eq "Turn")  return(0);
  if(cloaked) 				 return(0);

  if(!arw)
  {
   return(1);
  }
  if(iEnergy >=90)
  {
   var ammo = CreateObject(ARWW,0,20,GetOwner(pUser));
   ammo->Launch(180,20,300,10,100,0);
   MuzzleFlash(100,this(),0,20,180,RGBa(0,0,255,0));
   Sound("Waveshot");
   iEnergy -= 90;
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

func Luke()
{
  if(GetAction() eq "Stand")
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
  
  if(GetAction() eq "Open")
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
  if(GetAction() eq "Fly")
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
  iEnergy -= 50;
  DoDamage(5);
  return(1);
}

public func Schaden()
{
  Message("Schaden: %v|Verbleibend: %v" ,this() , GetDamage(this()) , 500-GetDamage(this()));
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
  if(iEnergy < 20)
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
   if(GetAction() eq "Fly")
   {
    cloaked = 0;
    SetAction("Tarnaus2");
    Sound("JumperUnCloak");
    return(1);
   }
   
   if(GetAction() eq "Stand")
   {
    cloaked = 0;
    SetAction("Tarnaus");
    Sound("JumperUnCloak");
    return(1);
   }
  }
  
  if(!cloaked)
  {
   if(GetAction() eq "Fly")
   {
    cloaked = 1;
    SetAction("Tarnan2");
    Sound("JumperCloak");
    return(1);
   }
   
   if(GetAction() eq "Stand")
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
  SetVisibility(VIS_All());
  SetClrModulation(0);  
  return(1);
}

public func Invisible()
{
  SetOwner(GetOwner(pUser));
  SetVisibility(VIS_Owner());
  SetClrModulation(RGBa(0,0,100,100));  
  return(1);
}

public func Exit(pCaller) 
{
  if(!open)
  {
   Luke();
   return(1);
  }

  pUser->Exit();
  pUser->SetAction("Walk");
  
  if(GetDir() == 0)
  {
   pUser->SetPosition(GetX(pUser)+30,GetY(pUser)+15);
   SetEntrance(1);
   return(1);
  }
  
  pUser->SetPosition(GetX(pUser)-30,GetY(pUser)+15);
  SetEntrance(1);
  return(1);
}

protected func ContainedThrow(pCaller)
{
  SetOwner(GetOwner(pCaller));
  if(GetAction() eq "Stand") return(0);
  if(GetAction() eq "Opens") return(0);
  if(GetAction() eq "Open")  return(0);
  if(GetAction() eq "Close") return(0);
  if(GetAction() eq "Turn")  return(1);
  if(cloaked) 				 return(1);

  if(iEnergy < 10)
  {
   Sound("start");
   return(1);
  }

  Sound("drone_shot");
  iEnergy -= 10;

  iDrohne = CreateObject(PUDD,0,15);
  SetOwner(GetOwner(this()),iDrohne);

  if(GetDir(this()) == 1)
  {
   iDrohne->SetXDir(100);
   FindObject(PUDD,-20,-20,40,40)->SetR(90);
  }

  if(GetDir(this()) == 0)
  {
   iDrohne->SetXDir(-100);
   FindObject(PUDD,-20,-20,40,40)->SetR(270);
  }
  return(1);
}

protected func ContainedUp()
{
  if(GetAction() eq "Turn") { return(0); }

  if(GetAction() S= "Fly")
   {
   if(GetComDir() == COMD_UpLeft() || GetComDir() == COMD_UpRight()) SetComDir(COMD_Up());
   if(GetComDir() == COMD_Down()) SetComDir(COMD_Up());
   if(GetComDir() == COMD_Left()) SetComDir(COMD_UpLeft());
   if(GetComDir() == COMD_DownLeft()) SetComDir(COMD_Left()); 
   if(GetComDir() == COMD_DownRight()) SetComDir(COMD_Right());
   if(GetComDir() == COMD_Right()) SetComDir(COMD_UpRight());
   if(GetComDir() == COMD_Stop()) SetComDir(COMD_Up());
   return(true);
   }
   
   if(GetAction() eq "Stand")
   {
    SetAction("Fly");
    return(1);
   }
  return(1);
}

protected func ContainedDown()
{
   if(!(GetAction() eq "Fly")) 
   { 
    return(0); 
   }

   if(GetComDir() == COMD_DownLeft() ||GetComDir() == COMD_DownRight())
   {
    SetComDir(COMD_Down());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Up())
   {
    SetComDir(COMD_Stop());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Left()) 
   {
    SetComDir(COMD_DownLeft());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_UpLeft())
   {
    SetComDir(COMD_Left());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Stop())
   {
    SetComDir(COMD_Down());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Right()) 
   {
    SetComDir(COMD_DownRight());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_UpRight())
   {
    SetComDir(COMD_Right());
    SetEntrance(0);
   }
  return(1);
}

protected func ContainedRight()
{
  if(GetAction() eq "Tarnan")  return(1);
  if(GetAction() eq "Tarnan2")  return(1);
  if(GetAction() eq "Tarnaus")  return(1);
  if(GetAction() eq "Tarnaus2")  return(1);
  if(GetAction() eq "opens")  return(1);
  if(GetAction() eq "open")  return(0);
  if(GetAction() eq "close")  return(1);
  if(GetAction() eq "Turn") return(1);
  if(open)					return(0);
  if(iExtra) return(0);
  SetCommand(this(),"None");
  SetComDir(COMD_Right());
  
  if(GetDir() == DIR_Left())
  {
   SetAction("Turn");
   iExtra++;
  }
  return(1);
}

protected func ContainedLeft()
{
  if(GetAction() eq "Tarnan")  return(1);
  if(GetAction() eq "Tarnan2")  return(1);
  if(GetAction() eq "Tarnaus")  return(1);
  if(GetAction() eq "Tarnaus2")  return(1);
  if(GetAction() eq "opens")  return(0);
  if(GetAction() eq "open")  return(0);
  if(GetAction() eq "close")  return(0);
  if(GetAction() eq "Turn") return(1);
  if(iExtra) return(0);
  if(open)					return(0);
  
  SetComDir(COMD_Left());  
  if(GetDir() == DIR_Right())
  {
   SetAction("Turn");
   iExtra++;
  }
  return(true);
}

func Turned()
{
  if(GetDir() == DIR_Left()) SetDir(DIR_Right());
  else SetDir(DIR_Left());
  iExtra = 0;
  return(true);
}   

public func Stop() 
{
  SetComDir(COMD_Stop());
  SetYDir(0);
  SetXDir(0);
  return(true);
}

protected func ContainedRightDouble()
{
  if(!(GetAction() eq "Fly")) { return(0); }

  if(GetDir() == DIR_Right())
   {
   SetComDir(COMD_Stop());
   SetYDir(0);
   SetComDir(COMD_Right());
   }
  else
   {
   SetAction("Wenden");
   }
  return(true);
}

protected func ContainedLeftDouble()
  {
   if(GetAction() eq "Tarned") { return(0); }
   if(!(GetAction() eq "Fly")) { return(0); }

  if(GetDir() == DIR_Left())
   {
   SetComDir(COMD_Stop());
   SetYDir(0);
   SetComDir(COMD_Left());
   }
  else
   {
   SetAction("Wenden");
   }
  return(true);
  }

public func Starting()
{
  if(GetAction() eq "Stand")
  SetAction("Fly",GetActionTarget(0),GetActionTarget(1));
  if(GetDir() == DIR_Left()) SetComDir(COMD_UpLeft());
  if(GetDir() == DIR_Right()) SetComDir(COMD_UpRight());
  return(true);
}



func IsMachine() 		{ return(1); }

func IsBulletTarget()    { return(1); }
