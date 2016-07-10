/*---- Das DHD ----*/

#strict

local pUser,ready,rena,atlantis;
local Name;

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

  if(FindObject(UMBE))
  {
   if(FindObject(NOKR))
   {
    Message("Gatename:|<c 00ff00>%v</c>",this(),Name);
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

public func GetName()		{return Name;}
public func IsDHD()			{return true;}
public func IsMilkywayDHD()	{return true;}
public func IsPegasusDHD()	{return false;}
public func IsDestinyDHD()	{return false;}