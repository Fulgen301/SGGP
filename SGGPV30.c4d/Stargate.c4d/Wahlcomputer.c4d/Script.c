
/*---- Das Wahlcomputer ----*/

#strict 2

local password;
local user;
local ask;
local dial;
local npw;
local rena;
local gate;
local myGate;
local iris;
local defcon_action;
local Name;
local forw;
local bState;
local chevrons;

func Initialize()
{
  password = "";
  chevrons = [];
  return(1);
}

func ControlDigDouble(pCaller)
{
  user = pCaller;
  ask=1;
  if(password == 0) password = "";
  if(password == "") 
  {
   InputCallback("");
   return(0);
  }
  CallMessageBoard(0, false, "Geben sie hier ihr Passwort ein:", GetOwner(user));
  return(1);
}

func InputCallback(string pw)
{
  if(forw)
  {
	  forw = 0;
	  if(!FindStargate())
	  {
		Message("<c ff0000>Kein Gate in Reichweite!</c>",this());
		Sound("Error");
		return(1);
	  }
	  var Gate;
	  for(Gate in FindObjects(Find_Func("IsStargate")))
	  {
		if (Gate != FindStargate())
		{
			var szName;
			szName = Gate ->GetName();
			if (szName == pw)
			{
				LocalN("forwarding",FindStargate()) = bState;
				LocalN("fGate",FindStargate()) = Gate;
				Message("<c 00ff00>Weiterleitung eingerichtet zu:</c><c 0000ff>%v</c>",this,Gate->GetName());
				bState = 0;
				return(1);
			}
		}
      }
	  bState = 0;
	  Message("<c ff0000>Weiterleitung fehlgeschlagen!</c>",this);
	  return(1);
  }
  if(ask)
  {
   ask=0;
   if(pw != password)
   {
    Sound("Error");
    Message("<c ff0000>Falsches Passwort!</c>",this());
    return;
   }
   MakeMenu();
   return(5);
  }
  
  if(npw)
  {
   npw = 0;
   password = pw;
   return(1);
  }
}

func MakeMenu()
{
	if(!FindStargate()) return;
	user->CreateSelectMark()->MarkObject(FindStargate(), 35);
  CreateMenu(STWA,user, 0, 0, FindStargate()->GetName(), 0, 1, true);
  if(FindStargate() && FindStargate()->IsBusy())
	AddMenuItem("$ShutdownGate$","Deactivate",MEPU,user);
  AddMenuItem("$DialGate$","Dial",MEPU,user);
  AddMenuItem("$ShowCoordinates$", "ShowCoordinates", MEPU, user);
  if(!FindObject(NOPW))
  {
   AddMenuItem("$ChangePassword$","ChangePass",MEPU,user);
  }
  if(!FindObject(NOIR))
  {
   if(FindStargate())
   {
     AddMenuItem("$ToggleIris$","Iris",MEPU,user);
   }
  }
  AddMenuItem("$GateEnergy$","GateEnergy",MEPU,user);
  return(1);
}

protected func ShowCoordinates()
{
	if(!FindStargate()) return;
	var prefixes = [];
	for(var i = 0, def; def = GetDefinition(i, 2); i++)
	{
		if(def && def->~IsStargate())
		{
			prefixes[GetLength(prefixes)] = def->~ChevronPrefix();
		}
	}
	
	var msg = "";
	for(var prefix in prefixes)
	{
		for(var cv in FindStargate()->GetChevrons())
		{
			msg = Format("%s  {{%s%02d}}", msg, prefix, cv);
		}
		msg = Format("%s|", msg);
	}
	for(var cv in FindStargate()->GetChevrons())
	{
		msg = Format("%s %d", msg, cv);
	}
	MessageWindow(msg, GetOwner(user));
}

func BuildIris()
{
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
   return(1);
  }
  if(FindStargate()->HasIris())
  {
   FindStargate()->HasIris()->Update();
   Sound("Error");
   return(1);
  }
  FindStargate()->InstallIris();
  return(1);
}

func Iris()
{
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
   return(1);
  }
  if(!FindStargate()->HasIris())
  {
   BuildIris();
  }
  LocalN("iris", FindStargate())->Switch();
  return(1);
}

func Deactivate()
{
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
   return(1);
  }
  FindStargate()->Deactivate();
  return(1);
}

func ChangePass()
{
  npw = 1;
  CallMessageBoard(0, false, "Geben sie hier ihr neues Passwort ein:", GetOwner(user));
  return(1);
}

func Dial()
{
  if(FindStargate()) FindStargate()->OpenChevronMenu(user, this);
}

func GateEnergy()
{
	if(FindStargate())
	{
		Message("Energie: %v",this,FindStargate()->~Energy());
	}
}

public func FindStargate()
{
	return FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance());
}

protected func Damage()
{
	if(GetDamage() > 100)
	{
		Incinerate();
		SetClrModulation(RGB(100,100,100));
	}
}
		
public func IsMachine() {return true;}
public func IsDHD()		{return true;}
public func IsDialPC()	{return true;}