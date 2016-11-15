/*---- Das DHD ----*/

local pUser,ready,rena,atlantis, forw, bState;

protected func Construction()
{
	AddEffect("Check", this, 1, 1, this);
}

protected func Initialize() 
{
  ready = 1;
  return true;
}

protected func ControlLeft(pCaller)
{
  pUser = pCaller;

  if(!ready)
  {
   Sound("start");
   return;
  }
  
  ChevronSound();
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate in Reichweite!</c>",this);
   return;
  }
  FindStargate()->Deactivate();
  return true;
}

protected func ControlUpDouble(pCaller)
{
  pUser = pCaller;

  if(!ready)
  {
   Sound("start");
   return;
  }
  
  ChevronSound();
  if(!FindStargate())
  {
   this->Message("<c ff0000>Kein Gate in Reichweite!</c>");
   return;
  }
  else
  {
   CallMessageBoard(this,false,"Geben sie hier den Namen des anzuwÃ¤hlenden Stargates ein:",pUser->GetOwner());
  }
  return true;
}

protected func ControlDigDouble(pCaller)
{
  ControlRightDouble(pCaller);
  return true;
}

protected func ControlRightDouble(pCaller)
{
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate in Reichweite!</c>",this);
   return;
  }
  ChevronSound();
  if(FindObject(UMBE))
  {
   if(FindObject(NOKR))
   {
    Message("Gatename:|<c 00ff00>%v</c>",this,FindStargate()->GetName());
    return;
   }
  }

  if(!ready)
  {
   CrystChange();
   return;
  }

  pUser = pCaller;
  CreateMenu(GetID(),pUser, 0, FindStargate()->GetName(), 0, 1);
  if(!FindObject(UMBE))
  {
   pUser->AddMenuItem("Gate umbenennen","Rename",Icon_MenuPoint);
  }
  
  if(!FindObject(NOKR))
  {
   pUser->AddMenuItem("DHD manipulieren","CrystChange",Icon_MenuPoint);
  }
/*  if(FindStargate().outgoing)
  {
	  AddMenuItem("Ausgehende Wurmlöcher erlauben","ChangeOutgoingState",Icon_MenuPoint,pUser,0,true);
  }
  else AddMenuItem("Ausgehende Wurmlöcher verbieten","ChangeOutgoingState",Icon_MenuPoint,pUser,0,false);
  
  if(FindStargate().incoming)
  {
	  AddMenuItem("Eingehende Wurmlöcher erlauben","ChangeIncomingState",Icon_MenuPoint,pUser,0,true);
  }
  else AddMenuItem("Eingehende Wurmlï¿½cher verbieten","ChangeIncomingState",Icon_MenuPoint,pUser,0,false);
  
  if(FindStargate().forwarding)
  {
	  AddMenuItem("Weiterleitung einrichten","ChangeForwardingState",Icon_MenuPoint,pUser,0,true);
  }
  else AddMenuItem("Weiterleitung entfernen","ChangeForwardingState",Icon_MenuPoint,pUser,0,false);*/
  return true;
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
		CallMessageBoard(this,false,"Geben Sie den Namen des Stargates ein, zu dem eine Weiterleitung eingerichtet werden soll:",pUser->GetOwner());
	}
	else
	{
		FindStargate().forwarding = false;
		FindStargate().fGate = nil;
		bState = false;
		this->Message("<c 00ff00>Weiterleitung entfernt!");
	}
}

protected func Rename()
{
  rena = 1;
  CallMessageBoard(nil, false, "Geben sie hier den neuen Namen ihres Stargates ein:", pUser->GetOwner());
  return;
}

protected func CrystChange()
{
  if(!ready)
  {
   if(pUser->FindContents(DHD_Crystal))
   {
    if(pUser->FindContents(DHD_Crystal).Damaged = 1)
    {
     Message("<c ff0000>Der Kristall ist kaputt!</c>",this);
     Sound("Error");
     return;
    }
    
    pUser->FindContents(DHD_Crystal)->RemoveObject();
    ready = 1;
    ChevronSound();
    return;
   }
   else
   {
    Message("<c ff0000>Kein Kontrollkristall vorhanden!</c>",this);
    return;
   }
  }
  else
  {
   pUser->CreateContents(DHD_Crystal);
   ready = 0;
   return true;
  }
}

protected func InputCallback(string pGate)
{
  if(!FindStargate())
  {
   Message("<c ff0000>Kein Gate in Reichweite!</c>",this);
   return;
  }

  if(rena)
  {
   rena = 0;
   if(!FindStargate())
   {
    Message("<c ff0000>Kein Gate in Reichweite!</c>",this);
    Sound("Error");
    return;
   }
   FindStargate()->ReName(pGate);
   Message("<c 00ff00>Neuer Gatename:</c><c 0000ff>%v</c>",this,pGate);
   return(1);
  }
  if(forw)
  {
	  forw = 0;
	  if(!FindStargate())
	  {
		Message("<c ff0000>Kein Gate in Reichweite!</c>",this);
		Sound("Error");
		return(1);
	  }
	  var Gate;
	  for(Gate in FindObjects([C4FO_Func, "IsStargate"]))
	  {
		if(Gate != FindStargate())
		{
			var szName;
			szName = Gate ->GetName();
			if (szName == pGate)
			{
				FindStargate().forwarding = bState;
				FindStargate().fGate = Gate;
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

private func ChevronSound() {Sound("DHDChevron");}

public func FindStargate()
{
	return FindObject([C4FO_Func, "IsStargate"],[C4FO_Func, "IsMilkywayGate"],[C4FO_Distance, 1000, GetX(), GetY()],[C4SO_Distance, GetX(), GetY()]);
}

public func IsDHD()			{return true;}
public func IsMilkywayDHD()	{return true;}
public func IsPegasusDHD()	{return false;}
public func IsDestinyDHD()	{return false;}
local Touchable = 2;
local Name = "$Name$";
