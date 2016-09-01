
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

func Initialize()
{
  password = "";
  return(1);
}

func ControlDigDouble(pCaller)
{
  user = pCaller;
  ask=1;
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

  if(dial)
  {
   dial = 0;
   if(!FindStargate())
   {
    Message("<c ff0000>Kein Gate gefunden!</c>",this());
    Sound("Error");
    return(1);
   }
   FindStargate()->Dial(pw);
   return(1);
  }
  
  if(npw)
  {
   npw = 0;
   password = pw;
   return(1);
  }
  
  if(rena)
  {
   rena = 0;
   if(!FindStargate())
   {
    Message("<c ff0000>Kein Gate gefunden!</c>",this());
    Sound("Error");
    return(1);
   }
   FindStargate()->ReName(pw);
   Message("<c 00ff00>Neuer Gatename:</c><c 0000ff>%v</c>",this(),pw);
   return(1);
  }
  return(1);
}

func MakeMenu()
{
  CreateMenu(STWA,user, 0, 0, "Wahlcomputer", 0, 1);
  if(FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Find_Func("IsBusy"),Sort_Distance()))
  AddMenuItem("Gate abschalten","Deactivate",MEPU,user);
  AddMenuItem("Gate anwählen","Dial",MEPU,user);
  AddMenuItem("Gatenamen abfragen","GetGateName",MEPU,user);
  if(!FindObject(UMBE))
  {
   AddMenuItem("Gate umbenennen","Rename",MEPU,user);
  }
  if(!FindObject(NOPW))
  {
   AddMenuItem("Passwort ändern","ChangePass",MEPU,user);
  }
  if(!FindObject(NOIR))
  {
   if(FindStargate())
   {
     AddMenuItem("Iris bedienen","Iris",MEPU,user);
   }
  }
  AddMenuItem("Energieanzeige des Gates","GateEnergy",MEPU,user);
  if(FindObject2(Find_ID(NOMA))) return(1);
  if(!LocalN("outgoing",FindStargate()))
  {
	  AddMenuItem("Ausgehende Wurmlöcher erlauben","ChangeOutgoingState",MEPU,user,0,true);
  }
  else AddMenuItem("Ausgehende Wurmlöcher verbieten","ChangeOutgoingState",MEPU,user,0,false);
  
  if(!LocalN("incoming",FindStargate()))
  {
	  AddMenuItem("Eingehende Wurmlöcher erlauben","ChangeIncomingState",MEPU,user,0,true);
  }
  else AddMenuItem("Eingehende Wurmlöcher verbieten","ChangeIncomingState",MEPU,user,0,false);
  
  if(!LocalN("forwarding",FindStargate()))
  {
	  AddMenuItem("Weiterleitung einrichten","ChangeForwardingState",MEPU,user,0,true);
  }
  else AddMenuItem("Weiterleitung entfernen","ChangeForwardingState",MEPU,user,0,false);
  return(1);
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

protected func ChangeForwardingState(id dummy, bool state)
{
	bState = state;
	if(state)
	{
		forw=1;
		CallMessageBoard(0,false,"Geben Sie den Namen des Stargates ein, zu dem eine Weiterleitung eingerichtet werden soll:",GetOwner(user));
	}
	else
	{
		LocalN("forwarding",FindStargate()) = false;
		LocalN("fGate",FindStargate()) = 0;
		Message("<c 00ff00>Weiterleitung entfernt!",this);
		bState = false;
	}
	
}

func GetGateName()
{
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
   return(1);
  }
  Message("<c 0000ff>Gatename:</c><c 00ff00>%v</c>",this(),LocalN("Name",FindStargate()));
  return(1);
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

func Rename()
{
  rena = 1;
  CallMessageBoard(0, false, "Geben sie hier den neuen Namen ihres Stargates ein:", GetOwner(user));
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
  dial = 1;
  CallMessageBoard(0, false, "Geben sie hier den Namen des anzuwählenden Gates ein:", GetOwner(user));
  return(1);
}

func GateEnergy()
{
	if(FindStargate())
	{
		Message("Energie: %v",this(),FindStargate()->~Energy());
	}
}

func EMPShock()
{
EMPShockEffect(20);
if(FindStargate())
{
var gate;
gate = FindStargate();
if(FindObject2(Find_Func("IsStargate"),Find_Exclude(gate)))
{
gate->Dial(FindObject2(Find_Func("IsStargate"),Find_Exclude(gate))->GetName());
}
}
}

func Check()
{
}

func Alert(int state)
{
	if(FindObjectOwner(DEFK,GetOwner()))
	{
		if(state)
		{
			defcon_action = FindObject(DEFK)->GetAction();
			FindObject(DEFK)->SetAction("Defcon4");
		}
		else
		{
			if(defcon_action)
			{
				FindObject(DEFK)->SetAction(defcon_action);
				defcon_action = "";
			}
		}
		return(1);
	}
	return(0);
}

public func FindStargate()
{
	return FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance());
}
		
public func IsMachine() {return true;}
public func IsDHD()		{return true;}
public func IsDialPC()	{return true;}