/*-- Hand-Activator --*/

#strict

local pUser;
local next;
local pTo;

func Activate(pCall)
{
  Sound("Connect");
  pUser = pCall;
  var von;
  if(FindObject(RIG1,-150,-150,300,300))
  {
   von = FindObject(RIG1,0,0,-1,-1);
  }
  else
  {
   Message("Kein Ringtransporter in der Nähe!",pUser);
   Sound("Error");
   return(1);
  }
  Sound("rt_button1");
  SetOwner(GetOwner(pUser));
  if(FindObject2(Find_ID(RIG1),Find_Distance(500),Find_Exclude(von),Find_Func("IsFindable")))
  {
   CreateMenu(RIG1,pUser,0,0,0,0,1);
   var next;
   for(next in FindObjects(Find_ID(RIG1),Find_Distance(500),Find_Exclude(von),Find_Func("IsFindable")))
   {
    AddMenuItem(Format("%s",LocalN("name",next)),"Go",MEPU,pUser,0,next,"Anwählen");
   }
   return(1);
  }
  else
  {
   Message("Kein anzuwählender Ringtransporter in der Nähe!",pUser);
   Sound("Error");
  }
  return(1);
}

public func Go(trash, tar)
{
  pTo = tar;
  if(FindObject(RIG1,-150,-150,300,300))
  {
   FindObject(RIG1,-150,-150,300,300) -> Activate(pTo);
   return(1);
  }
  Sound("rt_error");
  return(1);
}

public func ConDesc() 
{
  return("Ringtransporter auswählen");
}

protected func Hit()		{ Sound("ClonkHit*"); }
local Name = "$Name$";
local Collectible = 1;
