
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
	  var str = "";
  for(var cv in FindStargate()->GetChevrons())
  {
	  if(cv) str = Format("%s{{%s%02d}}  ", str, FindStargate()->ChevronPrefix(), cv);
  }
  CreateMenu(STWA,user, 0, 0, str, 0, 1, true);
  if(FindStargate() && FindStargate()->IsBusy())
	AddMenuItem("$ShutdownGate$","Deactivate",MEPU,user);
  AddMenuItem("$DialGate$","Dial",MEPU,user);
  AddMenuItem("Koordinaten anzeigen", "ShowCoordinates", MEPU, user);
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
  if(FindObject2(Find_ID(NOMA))) return(1);
  if(!LocalN("outgoing",FindStargate()))
  {
	  AddMenuItem("$EnableOutgoingWormholes$","ChangeOutgoingState",MEPU,user,0,true);
  }
  else AddMenuItem("$DisableOutgoingWormholes$","ChangeOutgoingState",MEPU,user,0,false);
  
  if(!LocalN("incoming",FindStargate()))
  {
	  AddMenuItem("Eingehende Wurmlöcher erlauben","ChangeIncomingState",MEPU,user,0,true);
  }
  else AddMenuItem("Eingehende Wurmlöcher verbieten","ChangeIncomingState",MEPU,user,0,false);
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
	MessageWindow(msg, GetOwner(user));
}

protected func ChangeOutgoingState(id dummy, bool state)
{
	if(FindStargate())
	{
		LocalN("outgoing",FindStargate()) = state;
		return true;
	}
}

protected func ChangeIncomingState(id dummy, bool state)
{
	if(FindStargate())
	{
		LocalN("incoming",FindStargate()) = state;
		return true;
	}
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
  OpenChevronMenu(user);
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
		OpenChevronMenu(user);
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
	OpenChevronMenu(user);
}

public func Finish()
{
	if(!FindStargate()) return Sound("start");
	FindStargate()->~Chevron();
	FindStargate()->Dial(chevrons);
	chevrons = [];
}

func GateEnergy()
{
	if(FindStargate())
	{
		Message("Energie: %v",this(),FindStargate()->~Energy());
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