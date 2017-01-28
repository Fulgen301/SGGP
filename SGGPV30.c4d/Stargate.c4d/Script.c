/*--Das Stargate --*/

#strict 2

local Name;
local pTo;
local pFrom;
local time;
local iris;
local heat;
local teltak;
local destiny;
local energy;
local ramp;
local iX, iY;
local outgoing, incoming, forwarding;
local fGate;
local chevroncount;
local fake;
local aChevrons;

public func IsTeltakGate()
{
	if(teltak)
	{
		return(1);
	}
	return(0);
}

public func SetTeltak(object obj)
{
	if(obj)
	{
	if(GetID(obj)==TEL_)
	{
		teltak=obj;
		return(1);
	}
	return(0);
	}
	return(0);
}

public func SetDestiny(object obj)
{
	if(obj)
	{
		destiny=obj;
	}
	return(1);
}
//Namenssetzung des Gates:
func Initialize()
{
  heat = 0;
  SetAction("Idle");
  var i;
  i = 0;
  for(obj in FindObjects(Find_Func("IsStargate")))
  {
	  if(obj) i++;
  }
  iX = GetX();
  iY = GetY();
  outgoing = true;
  incoming = true;
  forwarding = false;
  
  aChevrons = [];
  
  InitChevrons();
  for(var i = 0; FindObject2(Find_Func("HasAddress", aChevrons), Find_Exclude(this)) && i < 100; i++) InitChevrons();
  return(1);
}

protected func InitChevrons()
{
	var all = GetAllChevrons();
	for(var i = 0; GetLength(aChevrons) < 7; i++)
	{
		var x = RandomX(1,GetLength(all));
		if(GetIndexOf(all[x], aChevrons) == -1 && all[x] != 0) aChevrons[GetLength(aChevrons)] = all[x];
	}
}

public func GetAllChevrons()
{
	var ret = [];
	for(var i = 1; GetName(0, C4Id(Format("%s%02d", ChevronPrefix(), i))); i++)
	{
		if(i > 15) return ret;
		ret[GetLength(ret)] = i;
	}
	return ret;
}

public func & GetChevrons()
{
	return aChevrons;
}

public func HasAddress(array aAddress)
{
	return aChevrons == aAddress;
}

//Hat das Gate eine Iris?
func HasIris()
{
  return(iris);
}

//Nein? Dann müssen wir eine Installieren:
func InstallIris()
{
  iris = CreateObject(SGIR);
  SetObjectOrder(this,iris);
  LocalN("target",iris) = this;
  return(1);
}

//Abfrage ob die Iris zu ist
func IsClose()
{
  if(!iris)
  {
   return(0);
  }
  return(iris->IsClose());
}

//Abfrage ob beim angewählten Gate die Iris geschlossen ist
func pToClose()
{
  if(!pTo)
  {
   return(0);
  }
  return(pTo->IsClose());
}

//Sound wenn was gegen die Iris kracht
func Dong()
{
  Sound("IrisHit");
  return(1);
}

//Kontrolle an die Iris weitergeben
func ControlIris()
{
  if(iris)
  {
   iris->Switch();
  }
  return(1);
}

func GDOControlIris(passw)
{
  if(iris)
  {
   iris->GDOControl(passw);
  }
  return(1);
}

//Tötung beim Kawoosh
func KawooshKill()
{
	if(GetPhase() > 66) return;
   var xobj;
   DigFree(GetX()+18,GetY()+46,12);
   DigFree(GetX()+41,GetY()+44,15);
   DigFree(GetX()+10,GetY()+46,11);
   DigFree(GetX()+63,GetY()+43,13);
   DigFree(GetX()+46,GetY()+42,27);
   for(xobj in FindObjects(Find_InRect(60,22,30,45),Find_Or(Find_OCF(OCF_Living),Find_OCF(OCF_Collectible))))
   {
    if(!IsTeltakGate())
   	{
   		if(xobj) xobj->RemoveObject();
   	}
	else
	{
		if(xobj && !Contained(xobj))
		{
			xobj->RemoveObject();
		}
	}
   }
   for(xobj in FindObjects(Find_InRect(60,22,30,45),Find_Category(C4D_Vehicle)))
   {
    if(IsTeltakGate())
   	{
		if(xobj && !xobj->~Teltak())
		{
			xobj->DoDamage(1000);
		}
   	}
	else
		if(xobj) xobj->DoDamage(1000);
   }
  return(1);
}

//Die Sounds beim anwählen
protected func DialSounds()
{
	if(GetEffect("HoldAction", this)) return;
  if(GetPhase() == 1)
  {
   RollSound();
  }
  
  if(GetPhase() == 8)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 15)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 22)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 29)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 36)
  {
   ChevronSound();
  }
  
  if(GetPhase() == 44)
  {
   ChevronSound();
  }

  if(GetPhase() == 49)
  {
	  if(fake)
	  {
		  fake = false;
		  FailSound();
		  Deactivate();
	  }
  }
  if(GetPhase() == 50)
  {
   ChevronSound();
  }
  return(1);
}

func OpenSound()
{
  Sound("StargateOpen");
  return(1);
}

public func Chevron(int i)
{
	chevroncount = i;
	if(GetAction() == "Idle") SetAction("Outgoing1");
}

public func HasName(string sz)
{
	return Name == sz;
}

//Gibt den aktuellen Status des Gates zurück:
func GetState()
{
  if(GetAction() == "Outgoing3" || GetAction() == "Outgoing4") 
  {
   return(1);
  }
  
  if(GetAction() == "Income3" || GetAction() == "Income4")
  {
   return(2);
  }
  
  if(GetAction() == "Idle") 
  {
   return(0);
  }
  return(3);
}

//Gibt nur den Namen zurück:
func GetName()
{
  var ret = "";
  for(var cv in aChevrons)
  {
	  ret = Format("%s{{%s%02d}}  ", ret, ChevronPrefix(), cv);
  }
  return ret;
}

//Setzt den neuen Namen
func ReName(newName)
{
  if(newName == 0)
  {
   Message("Es muss ein Name gesetzt werden!",this);
   Sound("Error");
   return(1);
  }
  Name = newName;
  return(1);
}

//Beschäftigt?!
func IsBusy()
{
  return !(GetAction() == "Idle");
}

public func Dial(array gate)
{
	if(!chevroncount)
	{
		if(pTo)
		{
			ContinueAction(this);
			ContinueAction(pTo);
			time = 20 - !!IsDestinyGate() * 13;
		}
		else
		{
			FailSound();
			Deactivate();
			return;
		}
	}
	var pGate = FindObject2(Find_Func("IsStargate"), Find_Exclude(this), Find_Func("HasAddress", gate), Find_Not(Find_Func("IsBusy")));
	if(!pGate)
	{
		return;
	}
	
	var enrg = BoundBy(Distance(GetX(),GetY(),pGate->GetX(),pGate->GetY())*100, 100000, 1000000);
	if(energy >= enrg)
	{
		energy -= enrg;
	}
	else
	{
		return;
	}
	
	pTo = pGate;
	pTo->LocalN("pFrom") = this;
	pTo->SetAction("Income1");
	pTo->RollSound();
	pTo->ChevronSound();
	pTo->SetPhase(pTo->ChevronPhase()[chevroncount]);
	HoldAction(pTo);
}

//Überprüft ob das Gate sich abschalten muss:
func Check()
{
  if(EnergyCheck(100) && energy <= 1000000)
  {
  	energy += 50;
  }
		
  if(IsSpaceGate() && !IsTeltakGate())	SetPosition(iX, iY);
  if(heat > 0)
  {
   if(iris)
   {
    LocalN("temp",iris) = heat/1000;
   }
   heat -= 2;
   if(IsClose())
   {
    heat -= 2;
   }
   SetClrModulation(RGB(255,255-(heat/1000),255-(heat/1000)));
  }
  if(heat < 0)
  {
   heat = 0;
  }
  if(heat > 255000)
  {
	  Destroy();
  }
  if(IsClose())
  {
   if(GetAction() == "Income2")
   {
    SetAction("Income3");
   }
   if(GetAction() == "Outgoing2")
   {
    SetAction("Outgoing3");
   }
  }
  if(forwarding && WildcardMatch(GetAction(),"Income*") && fGate && !fGate->IsBusy() && !IsForwarding())
  {
	  LocalN("pTo",pFrom) = fGate;
	  LocalN("pFrom",fGate) = pFrom;
	  pFrom = 0;
	  fGate->SetAction(GetAction());
	  fGate->SetPhase(GetPhase());
	  Deactivate();
  }
  
  if(GetAction() == "Outgoing1" && chevroncount)
  {
	  if(GetPhase() != ChevronPhase()[chevroncount])
	  {
		  ContinueAction(this);
	  }
	  else
	  {
		  HoldAction(this);
	  }
	  
	  return 1;
  }
  else if(GetAction() == "Off" || GetAction() == "Idle")
  {
   return(1);
  }

  if((!pFrom && !pTo) || (pFrom && pFrom->GetAction() == "Idle") || (pTo && pTo->GetAction() == "Idle"))
	  Deactivate();
  return(1);
}

//Abschaltzeit
func ShutDelay()
{
  time --;
  if(time <= 0)
  {
   Deactivate();
  }
  return(1);
}

public func Deactivate()
{
	if(pFrom && !WildcardMatch(GetAction(), "Outgoing*")) return;
	if(pTo)
	{
		pTo->LocalN("pFrom") = 0;
		pTo->LocalN("pTo") = 0;
		pTo->SetAction("Off");
	}
	if(pFrom)
	{
		pFrom->LocalN("pFrom") = 0;
		pFrom->LocalN("pTo") = 0;
		pFrom->SetAction("Off");
	}
	pFrom = 0;
	pTo = 0;
	
	if(WildcardMatch(GetAction(), "*1"))
	{
		FailSound();
		SetAction("Idle");
	}
	if(GetState()) SetAction("Off");
	return true;
}


//Überbringung des Ziels:
func Transport()
{
	if(!pTo) return;
  var obj;
  for(obj in FindObjects(Find_InRect(70,0,25,80)))
  {
  	if(GetID(obj) == TEL_)
  	{
  		if(IsTeltakGate())
  		{
  			return(1);
  		}
  	}
   if(GetXDir(obj) < 1)
   {
    return(1);
   }
   if(IsClose())
   {
    return(1);
   }
   if(pTo->IsClose())
   {
    obj->RemoveObject();
    pTo->Dong();
    Sound("teleport");
    return(1);
   }
   if(GetID(obj) == TAUV)
   {
    LocalN("dir",obj) = 180;
    obj->SetPosition(GetX(pTo),GetY(pTo));
    Sound("teleport");
    Sound("teleport",0,pTo);
    return(1);
   }
   Sound("teleport");
   Sound("teleport",0,pTo);
   var hX;
   var hY;
   hX = GetX(obj)-GetX();
   hY = GetY(obj)-GetY();
   obj->SetPosition(GetX(pTo)+hX,GetY(pTo)+hY);
   obj->SetDir(0);
   SetComDir(COMD_Left,obj);
   SetDir(DIR_Left,obj);
   obj->SetXDir(GetXDir(obj)*-1);
  }
  return(1);
}

protected func Destroy()
{
   if(ramp)
   {
     ramp->RemoveObject();
   }
   Explode(300);
   return(1);
}

protected func Damage()
{
	if(GetDamage() > 300)
	{
		Destroy();
	}
}

public func LightningStrike() 
{
	if (GetCon() < 100) return(0);
	energy += 25000;
	return(1);
}

public func SetFGate(object gate)
{
	fGate = gate;
	return fGate;
}
public func IsForwarding()
{
	if(forwarding && !IsBusy()) return true;
	else return false;
}

public func IsStargate()
{
	return true;
}

public func ChevronSound()
{
	return(1);
}

public func RollSound()
{
	return(1);
}

public func FailSound()
{
	return(1);
}

public func ChevronCount(object gate)
{
	return(7);
}

public func IsDestinyGate()
{
	return(0);
}

public func IsMilkywayGate()
{
	return(0);
}

public func IsPegasusGate()
{
	return(0);
}

public func ChevronPrefix() { return ""; }

public func GiveEnergy(int amount)
{
	DoEnergy(amount);
	return(1);
}

public func IsConsoleTarget()
{
	return true;
}

public func IsSpaceGate()
{
	return (!ramp && !IsTeltakGate());
}

public func Energy()
{
	return(energy);
}

public func IsBulletTarget(id Bullet)
{
	if(IsSpaceGate() || Bullet == SHT3) return true;
}

/* Console */

public func ConsoleControl(int i)
{
	if(i == 1) return "Position verändern";
}

public func ConsoleControlled(int i, int iObjectNumber)
{
	if(i == 1) return Position(iObjectNumber);
}

protected func Position(int iObjectNumber)
{
	if(ramp) ramp->RemoveObject();
	var pCursor = CreateObject(CURS);
	pCursor->SetBeamer(this, Object(iObjectNumber)->GetController(), Object(iObjectNumber));
	SetCursor(Object(iObjectNumber)->GetController(), pCursor);
	return true;
}

protected func Okay(int x, int y)
{
	iX = x;
	iY = y;
	SetPosition(x,y);
	return true;
}


public func ChevronPhase()
{
	return [1, 8, 15, 22, 29, 36, 44, 49];
}