	/*--Das Stargate --*/

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
local position;
local state;
local fGate;
local chevroncount;
local fake;

public func IsTeltakGate()
{
    return teltak;
}

public func HasDestiny()
{
    return destiny;
}

public func SetTeltak(object obj)
{
	if(obj && obj->~Teltak())
	{
		teltak = obj;
	}
	
	return this;
}

public func SetDestiny(object obj)
{
	if(obj && obj->~IsDestiny())
	{
		destiny = obj;
	}
	
	return this;
}

protected func Construction()
{
	AddEffect("IntCheck", this, 1, 1, this);
}

//Namenssetzung des Gates:
protected func Initialize()
{
  heat = 0;
  SetAction("Idle");
  var i;
  i = 0;
  for(var obj in FindObjects(Find_Func("IsStargate")))
  {
	  if(obj) i++;
  }
  Name = Format("Stargate %v",i);
  position = new position {
      x = GetX(),
      y = GetY()
  };
  state = new state {
      outgoing = true,
      incoming = true,
      forwarding = false
  };
  return true;
}

//Hat das Gate eine Iris?
func HasIris()
{
  return(iris);
}

//Nein? Dann müssen wir eine Installieren:
func InstallIris()
{
  iris = CreateObject(Stargate_Iris);
  iris.target = this;
  return(1);
}

//Abfrage ob die Iris zu ist
public func IsClose()
{
  if(!iris)
  {
   return nil;
  }
  return iris->IsClose();
}

//Abfrage ob beim angewählten Gate die Iris geschlossen ist
public func pToClose()
{
  if(!pTo)
  {
   return nil;
  }
  return pTo->IsClose();
}

//Sound wenn was gegen die Iris kracht
private func Dong()
{
  Sound("IrisHit");
  return true;
}

//Kontrolle an die Iris weitergeben
protected func ControlIris()
{
  if(iris)
  {
   iris->Switch();
  }
  return true;
}

public func GDOControlIris(passw)
{
  if(iris)
  {
   iris->GDOControl(passw);
  }
  return true;
}

//Tötung beim Kawoosh
protected func KawooshKill()
{
   var xobj;
   FreeRect(GetX() - GetID()->GetDefOffset(0), GetY() - GetID()->GetDefOffset(1), GetID()->GetDefWidth(), GetID()->GetDefHeight());
   for(xobj in FindObjects(Find_InRect(60,22,30,45),Find_Or(Find_OCF(OCF_Living),Find_OCF(OCF_Collectible), Find_Category(C4D_Vehicle))))
   {
    if(!IsTeltakGate())
   	{
   		if(xobj) xobj->RemoveObject();
   	}
	else
	{
		if(xobj && !xobj->Contained(xobj) && !xobj->Teltak())
		{
			xobj->RemoveObject();
		}
	}
   }
  return true;
}

//Die Sounds beim anwählen
protected func DialSounds()
{
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
		  FailSound();
		  Deactivate();
	  }
  }
  if(GetPhase() == 50)
  {
   ChevronSound();
  }
  return true;
}

private func OpenSound()
{
  return Sound("StargateOpen");
}

//Gibt den aktuellen Status des Gates zurück:
public func GetState()
{
  if(GetAction() == "Outgoing3" || GetAction() == "Outgoing4") 
  {
   return 1;
  }
  
  if(GetAction() == "Income3" || GetAction() == "Income4")
  {
   return 2;
  }
  
  if(GetAction() == "Idle" || GetAction() == "Off") 
  {
   return 0;
  }
  return 3;
}

//Gibt nur den Namen zurück:
public func GetName()
{
  return Name;
}

public func GiveName()
{
	return GetName();
}

//Setzt den neuen Namen
public func ReName(newName)
{
  if(!newName)
  {
   Message("Es muss ein Name gesetzt werden!",this);
   Sound("Error");
   return false;
  }
  Name = newName;
  return true;
}

//START: Anwählen

public func Dial(string gate)
{
	var szName;
	var pGate;
	for(var obj in FindObjects(Find_Func("IsStargate"), Find_Exclude(this), Find_Not(Find_Func("IsBusy"))))
	{
		if((szName = obj->GetName()) == gate)
		{
			pGate = obj;
			break;
		}
	}
	
	//Energy
	
	var cc = ChevronCount(this);
	if(cc == 7 && energy >= 100000)
	{
		energy -= 100000;
	}
	else if(cc == 8 && energy >= 500000)
	{
		energy -= 500000;
	}
	else if(cc == 9 && energy >= 1000000)
	{
		energy -= 1000000;
	}
	else
	{
		fake = true;
		SetAction("Outgoing1");
		return true;
	}
	
	pTo = pGate;
	pTo.pFrom = this;
	
	SetAction("Outgoing1");
	pTo->SetAction("Income1");
	return true;
}

//ENDE: Anwählen

protected func FxIntCheckTimer(object pTarget, proplist pEffect, int time)
{
  if(energy <= 1000000)
  {
  	energy += 50;
  }
		
  if(IsSpaceGate() && !IsTeltakGate())	SetPosition(position.x, position.y);
  if(heat > 0)
  {
   if(iris)
   {
    iris.temp = heat/1000;
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
	  if(GetAction() == "Outgoing2") SetAction("Outgoing3");
	  else if(GetAction() == "Income2") SetAction("Income3");
  }
  if(!GetState())
  {
	  if(!pFrom)
	  {
		if(!pTo && !fake)
		{
			Deactivate();
		}
	  }
	  else if(pFrom && pFrom->GetAction() == "Idle")
	  {
			Deactivate();
	  }
	  if(pTo && !fake)
	  {
		if(pTo->GetAction() == "Idle")
		{
			Deactivate();
		}
	  }
  }
  return true;
}

//Abschaltzeit
private func ShutDelay()
{
  time --;
  if(time <= 0)
  {
   Deactivate();
  }
  return true;
}

public func Deactivate()
{
	if(pTo)
	{
		pTo.pFrom = nil;
		pTo.pTo = nil;
	}
	if(pFrom)
	{
		pFrom.pFrom = nil;
		pFrom.pTo = nil;
	}
	pFrom = nil;
	pTo = nil;
	
	if(WildcardMatch(GetAction(), "*1"))
	{
		FailSound();
		SetAction("Idle");
	}
	if(GetState()) SetAction("Off");
	return true;
}

//Überbringung des Ziels:
protected func Transport()
{
  var obj;
  for(obj in FindObjects(Find_InRect(70,0,25,80)))
  {
  	if(IsTeltakGate() && obj->~Teltak())
  	{
		continue;
  	}
   if(obj->GetXDir() < 1)
   {
    continue;
   }
   if(IsClose())
   {
    return true;
   }
   if(pTo->IsClose())
   {
    obj->RemoveObject();
    pTo->Dong();
    Sound("teleport");
    return true;
   }
   if(obj->GetID() == TAUV)
   {
    obj.dir= 180;
    obj->SetPosition(pTo->GetX(),pTo->GetY());
    Sound("teleport");
    pTo->Sound("teleport");
    continue;
   }
   Sound("teleport");
   pTo->Sound("teleport");
   var hX;
   var hY;
   hX = obj->GetX()-GetX();
   hY = obj->GetY()-GetY();
   obj->SetPosition(pTo->GetX()+hX,pTo->GetY()+hY);
   obj->SetDir(0);
   obj->SetComDir(COMD_Left);
   obj->SetDir(DIR_Left);
   obj->SetXDir(-(obj->GetXDir()));
  }
  return true;
}
protected func Destroy()
{
   if(ramp) ramp->RemoveObject();
   Explode(300);
   return true;
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
	if (GetCon() < 100) return;
	energy += 25000;
	return true;
}

public func SetFGate(object gate)
{
	fGate = gate;
	return this;
}

//###############
//###Callbacks###
//###############

public func IsBulletTarget(id Bullet)  { return IsSpaceGate(); }

//Stargate
public func IsStargate()				{ return true; }
public func IsDestinyGate()				{ return false; }
public func IsMilkywayGate()			{ return false; }
public func IsPegasusGate()				{ return false; }
public func IsSpaceGate()				{ return !ramp; }
public func IsForwarding()				{ return (state.forwarding && !IsBusy()); }
public func ChevronCount(object gate)	{ return 7; }
public func IsBusy()					{ return !(GetAction() == "Idle"); }

//Energy
public func GetEnergy()					{ return energy; }

//Sound
private func ChevronSound()				{ return; }
private func RollSound()				{ return; }
private func FailSound()				{ return; }

//Console
public func IsConsoleTarget()			{ return true; }
local ActMap = {

Outgoing1 = {

Prototype = Action,

Name = "Outgoing1",

Length = 51,

Delay = 4,

FlipDir = 1,

X = 0,

Y = 0,

Wdt = 110,

Hgt = 80,

NextAction = "Outgoing2",

PhaseCall = "DialSounds",

},

Outgoing2 = {

Prototype = Action,

Name = "Outgoing2",

Length = 66,

Delay = 2,

FlipDir = 1,

X = 0,

Y = 80,

Wdt = 110,

Hgt = 80,

NextAction = "Outgoing3",

StartCall = "OpenSound",

PhaseCall = "KawooshKill",

},

Outgoing3 = {

Prototype = Action,

Name = "Outgoing3",

Length = 51,

Delay = 1,

FlipDir = 1,

X = 0,

Y = 160,

Wdt = 110,

Hgt = 80,

NextAction = "Outgoing4",

EndCall = "ShutDelay",

Sound = "Opened",

PhaseCall = "Transport",

},

Outgoing4 = {

Prototype = Action,

Name = "Outgoing4",

Length = 51,

Delay = 1,

FlipDir = 1,

Reverse = 1,

X = 0,

Y = 160,

Wdt = 110,

Hgt = 80,

NextAction = "Outgoing3",

Sound = "Opened",

PhaseCall = "Transport",

},

Income1 = {

Prototype = Action,

Name = "Income1",

Length = 51,

Delay = 4,

FlipDir = 1,

X = 0,

Y = 0,

Wdt = 110,

Hgt = 80,

NextAction = "Income2",

PhaseCall = "DialSounds",

},

Income2 = {

Prototype = Action,

Name = "Income2",

Length = 66,

Delay = 2,

FlipDir = 1,

X = 0,

Y = 80,

Wdt = 110,

Hgt = 80,

NextAction = "Income3",

StartCall = "OpenSound",

PhaseCall = "KawooshKill",

},

Income3 = {

Prototype = Action,

Name = "Income3",

Length = 51,

Delay = 1,

FlipDir = 1,

X = 0,

Y = 160,

Wdt = 110,

Hgt = 80,

NextAction = "Income4",

Sound = "Opened",

},

Income4 = {

Prototype = Action,

Name = "Income4",

Length = 51,

Delay = 1,

FlipDir = 1,

Reverse = 1,

X = 0,

Y = 160,

Wdt = 110,

Hgt = 80,

NextAction = "Income3",

Sound = "Opened",

},

Off = {

Prototype = Action,

Name = "Off",

Length = 63,

Delay = 1,

FlipDir = 1,

X = 0,

Y = 240,

Wdt = 110,

Hgt = 80,

Sound = "StargateClose",

NextAction = "Idle",

},  };
