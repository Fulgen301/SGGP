/*---- Das DHD ----*/

#strict 2

local pUser,ready;
local chevrons;

func Initialize() 
{
  ready = 1;
  return(1);
}

func ControlLeft(pCaller)
{
	[$ShutdownGate$]
  pUser = pCaller;

  if(!ready)
  {
   Sound("start");
   return(1);
  }
  
  ChevronSound();
  if(!FindStargate())
  {
   Message("$NoGate$",this);
   return(1);
  }
  FindStargate()->Deactivate();
  return(1);
}

func ControlUpDouble(pCaller)
{
	[$DialGate$]
  pUser = pCaller;

  if(!ready)
  {
   Sound("start");
   return(1);
  }
  if(!FindStargate())
  {
   Message("$NoGate", this);
   return(1);
  }
  else
  {
   FindStargate()->OpenChevronMenu(pCaller, this);
  }
  return(1);
}


protected func ControlDigDouble(pCaller)
{
	[$ManipulateDHD$|Image=DHDK|Condition=CanManipulate]
	CrystChange();
	return true;
}

public func CanManipulate()
{
	return !FindObject2(Find_ID(NOKR));
}

protected func Grabbed(object pBy, bool fGrab)
{
	pUser = pBy;
	if(fGrab)
	{
		if(FindStargate()) Message("@%s", this, FindStargate()->GetName());
		pUser->CreateSelectMark()->MarkObject(FindStargate(), 35);
	}
	else Message("",this);
}

func CrystChange()
{
  if(!ready)
  {
   if(FindContents(DHDK,pUser))
   {
    if(LocalN("Damaged",FindContents(DHDK,pUser)) == 1)
    {
     Message("$CrystDamaged$",this);
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
    Message("$NoCryst$",this);
    return(1);
   }
   Sound("start");
   return(1);
  }
  else if(CanManipulate())
  {
   CreateContents(DHDK,pUser);
   ready = 0;
   return(1);
  }
  return(1);
}

public func ChevronSound()
{
	Sound("DHDChevron");
	return(1);
}

protected func Check()
{
	if(FindStargate() && ready)
	{
		FindStargate()->GiveEnergy(500);
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