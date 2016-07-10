
/*---- Das Wahlcomputer ----*/

#strict

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

func Initialize()
{
  password = 0;
  return(1);
}

func ControlDigDouble(pCaller)
{
  user = pCaller;
  ask=1;
  if(password eq "") 
  {
   InputCallback("");
   return(0);
  }
  CallMessageBoard(0, false, "Geben sie hier ihr Passwort ein:", GetOwner(user));
  return(1);
}

func InputCallback(string pw)
{			
  if(ask)
  {
   ask=0;
   if(pw ne password)
   {
    Sound("Error");
    Message("<c ff0000>Falsches Passwort!</c>",this());
    return();
   }
   MakeMenu();
   return(5);
  }

  if(dial)
  {
   dial = 0;
   if(!FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))
   {
    Message("<c ff0000>Kein Gate gefunden!</c>",this());
    Sound("Error");
    return(1);
   }
   FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance())->Dial(pw);
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
   if(!FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))
   {
    Message("<c ff0000>Kein Gate gefunden!</c>",this());
    Sound("Error");
    return(1);
   }
   FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance())->ReName(pw);
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
   if(FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))
   {
     AddMenuItem("Iris bedienen","Iris",MEPU,user);
   }
  }
  AddMenuItem("Energieanzeige des Gates","GateEnergy",MEPU,user);
  return(1);
}

func GetGateName()
{
  if(!FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
   return(1);
  }
  Message("<c 0000ff>Gatename:</c><c 00ff00>%v</c>",this(),LocalN("Name",FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance())));
  return(1);
}

func BuildIris()
{
  if(!FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
   return(1);
  }
  if(FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance())->HasIris())
  {
   FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance())->HasIris()->Update();
   Sound("Error");
   return(1);
  }
  FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance())->InstallIris();
  return(1);
}

func Iris()
{
  if(!FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
   return(1);
  }
  if(!FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance())->HasIris())
  {
   BuildIris();
  }
  LocalN("iris", FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))->Switch();
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
  if(!FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))
  {
   Message("<c ff0000>Kein Gate gefunden!</c>",this());
   Sound("Error");
   return(1);
  }
  FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance())->Deactivate();
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
	if(FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))
	{
		Message("Energie: %v",this(),FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance())->~Energy());
	}
}

func EMPShock()
{
EMPShockEffect(20);
if(FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance()))
{
var gate;
gate = FindObject2(Find_Func("IsStargate"),Find_Distance(1000),Sort_Distance());
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
		
public func IsMachine() {return true;}
public func IsDHD()		{return true;}
public func IsDialPC()	{return true;}