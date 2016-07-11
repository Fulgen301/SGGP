/*---- Das DHD ----*/

#strict 2

local pUser,ready,rena,atlantis, forw, bState;

func Initialize() 
{
  ready = 1;
  return(1);
}

func ControlLeft(pCaller)
{
  pUser = pCaller;

  if(!ready)
  {
   Sound("start");
   return(1);
  }
  
  ChevronSound();
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate in Reichweite!</c>",this());
   return(1);
  }
  FindStargate()->Deactivate();
  return(1);
}

func ControlUpDouble(pCaller)
{
  pUser = pCaller;

  if(!ready)
  {
   Sound("start");
   return(1);
  }
  
  ChevronSound();
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate in Reichweite!</c>",this());
   return(1);
  }
  else
  {
   CallMessageBoard(0,false,"Geben sie hier den Namen des anzuwählenden Stargates ein:",GetOwner(pUser));
  }
  return(1);
}

func ControlDigDouble(pCaller)
{
  ControlRightDouble(pCaller);
  return(1);
}

func ControlRightDouble(pCaller)
{
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate in Reichweite!</c>",this());
   return(1);
  }
  ChevronSound();
  if(FindObject(UMBE))
  {
   if(FindObject(NOKR))
   {
    Message("Gatename:|<c 00ff00>%v</c>",this(),FindStargate()->GetName());
    return;
   }
  }

  if(!ready)
  {
   CrystChange();
   return(1);
  }

  pUser = pCaller;
  CreateMenu(DHD_,pUser, 0, 0, FindStargate()->GetName(), 0, 1);
  if(!FindObject(UMBE))
  {
   AddMenuItem("Gate umbenennen","Rename",MEPU,pUser);
  }
  
  if(!FindObject(NOKR))
  {
   AddMenuItem("DHD manipulieren","CrystChange",MEPU,pUser);
  }
  
  if(!LocalN("outgoing",FindStargate()))
  {
	  AddMenuItem("Ausgehende Wurmlöcher erlauben","ChangeOutgoingState",MEPU,pUser,0,true);
  }
  else AddMenuItem("Ausgehende Wurmlöcher verbieten","ChangeOutgoingState",MEPU,pUser,0,false);
  
  if(!LocalN("incoming",FindStargate()))
  {
	  AddMenuItem("Eingehende Wurmlöcher erlauben","ChangeIncomingState",MEPU,pUser,0,true);
  }
  else AddMenuItem("Eingehende Wurmlöcher verbieten","ChangeIncomingState",MEPU,pUser,0,false);
  
  if(!LocalN("forwarding",FindStargate()))
  {
	  AddMenuItem("Weiterleitung einrichten","ChangeForwardingState",MEPU,pUser,0,true);
  }
  else AddMenuItem("Weiterleitung entfernen","ChangeForwardingState",MEPU,pUser,0,false);
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
		CallMessageBoard(0,false,"Geben Sie den Namen des Stargates ein, zu dem eine Weiterleitung eingerichtet werden soll:",GetOwner(pUser));
	}
	else
	{
		LocalN("forwarding",FindStargate()) = false;
		LocalN("fGate",FindStargate()) = 0;
		bState = false;
		Message("<c 00ff00>Weiterleitung entfernt!",this);
	}
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
   Message("<c ff0000>Das Gate hat keine Iris!</c>",this());
   Sound("Error");
   return(1);
  }
  FindStargate()->ControlIris();
  return(1);
}

func Rename()
{
  rena = 1;
  CallMessageBoard(0, false, "Geben sie hier den neuen Namen ihres Stargates ein:", GetOwner(pUser));
  return(1);
}

func CrystChange()
{
  if(!ready)
  {
   if(FindContents(DHDK,pUser))
   {
    if(LocalN("Damaged",FindContents(DHDK,pUser)) == 1)
    {
     Message("<c ff0000>Der Kristall ist kaputt!</c>",this());
     Sound("Error");
     return(1);
    }
    
    FindContents(DHDK,pUser)->RemoveObject();
    ready = 1;
    ChevronSound();
    return(1);
   }
   else
   {
    Message("<c ff0000>Kein Kontrollkristall vorhanden!</c>",this());
    return(1);
   }
   Sound("start");
   return(1);
  }
  else
  {
   CreateContents(DHDK,pUser);
   ready = 0;
   return(1);
  }
  return(1);
}

func InputCallback(string pGate)
{
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate in Reichweite!</c>",this());
   return(1);
  }

  if(rena)
  {
   rena = 0;
   if(!FindStargate())
   {
    Message("<c ff0000>Kein Gate in Reichweite!</c>",this());
    Sound("Error");
    return(1);
   }
   FindStargate()->ReName(pGate);
   Message("<c 00ff00>Neuer Gatename:</c><c 0000ff>%v</c>",this(),pGate);
   return(1);
  }
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
			if (szName == pGate)
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
  if(!ready)
  {
   Sound("start");
   return(1);
  }
  else
  {
   FindStargate()->Dial(pGate);
   return(1);
  }
  return(1);
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

func IsMachine() {return(1);}
public func ChevronSound()
{
	Sound("DHDChevron");
	return(1);
}

protected func Check()
{
	if(atlantis) return;
	if(FindStargate() && ready)
	{
		FindStargate()->GiveEnergy(500);
//		FindStargate()->~ReName(Name);
	}
	return(1);
}

public func FindStargate()
{
	return(FindObject2(Find_Func("IsStargate"),Find_Func("IsMilkywayGate"),Find_Distance(1000),Sort_Distance()));
}

public func IsDHD()			{return true;}
public func IsMilkywayDHD()	{return true;}
public func IsPegasusDHD()	{return false;}
public func IsDestinyDHD()	{return false;}