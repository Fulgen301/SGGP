
/*---- Das Wahlcomputer ----*/



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
/*
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
				FindStargate().forwarding = bState;
				FindStargate().fGate = Gate;
				this->Message("<c 00ff00>Weiterleitung eingerichtet zu:</c><c 0000ff>%v</c>",Gate->GetName());
				bState = 0;
				return(1);
			}
		}
      }
	  bState = 0;
	  Message("<c ff0000>Weiterleitung fehlgeschlagen!</c>",this);
	  return(1);
  }
  */
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
    this->Message("<c ff0000>Kein Gate gefunden!</c>",);
    Sound("Error");
    return(1);
   }
   FindStargate()->ReName(pw);
   this->Message("<c 00ff00>Neuer Gatename:</c><c 0000ff>%v</c>",pw);
   return(1);
  }
  return(1);
}

func MakeMenu()
{
  CreateMenu(GetID(),user, 0, "Wahlcomputer", 0, 1);
  if(!FindObject(Find_Func("IsStargate"),Find_Distance(1000),Find_Func("IsBusy"),Sort_Distance())) return;
  user->AddMenuItem("Gate abschalten","Deactivate",Icon_MenuPoint);
  user->AddMenuItem("Gate anwählen","Dial",Icon_MenuPoint);
  user->AddMenuItem("Gatenamen abfragen","GetGateName",Icon_MenuPoint);
  if(!FindObject(UMBE))
  {
   user->AddMenuItem("Gate umbenennen","Rename",Icon_MenuPoint);
  }
  if(!FindObject(NOPW))
  {
   user->AddMenuItem("Passwort ändern","ChangePass",Icon_MenuPoint);
  }
  if(!FindObject(NOIR))
  {
   if(FindStargate())
   {
     user->AddMenuItem("Iris bedienen","Iris",Icon_MenuPoint);
   }
  }
  user->AddMenuItem("Energieanzeige des Gates","GateEnergy",Icon_MenuPoint);
  /*
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
  else AddMenuItem("Weiterleitung entfernen","ChangeForwardingState",MEPU,user,0,false);*/
  return(1);
}

protected func ChangeOutgoingState(id dummy, bool state)
{
	if(FindStargate())
	{
		FindStargate().outgoing = state;
		return true;
	}
}

protected func ChangeIncomingState(id dummy, bool state)
{
	if(FindStargate())
	{
		FindStargate().incoming = state;
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
		FindStargate().forwarding = false;
		FindStargate().fGate = nil;
		this->Message("<c 00ff00>Weiterleitung entfernt!");
		bState = false;
	}
	
}

func GetGateName()
{
  if(!FindStargate())
  {
   this->Message("<c ff0000>Kein Gate gefunden!</c>");
   Sound("Error");
   return(1);
  }
  this->Message("<c 0000ff>Gatename:</c><c 00ff00>%v</c>",FindStargate()->GetName());
  return(1);
}

func BuildIris()
{
  if(!FindStargate())
  {
   this->Message("<c ff0000>Kein Gate gefunden!</c>");
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
  FindStargate().iris->Switch();
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
		this->Message("Energie: %v",FindStargate()->~Energy());
	}
}

func Check()
{
}

func Alert(int state)
{
	if(FindObject(Find_ID(DEFK),Find_Owner(GetOwner())))
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
	return FindObject(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance());
}
		
public func IsMachine() {return true;}
public func IsDHD()		{return true;}
public func IsDialPC()	{return true;}
local Touchable = 2;
local Name = "$Name$";
