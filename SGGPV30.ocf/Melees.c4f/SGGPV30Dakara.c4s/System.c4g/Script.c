#strict 2
#appendto RIG2

public func ControlDigDouble(pCaller)
{
  var von;
  if(FindObject(RIG1,-150,-150,300,300))
  {
   von = FindObject(RIG1,0,0,-1,-1);
  }
  else
  {
   Message("Kein Ringtransporter in der nähe!",this());
   Sound("Error");
   return(1);
  }

  if(!ActIdle())
  {
   Sound("rt_error");
   return(1);
  }

  Sound("rt_button1");

  pUser = pCaller;
  SetOwner(GetOwner(pUser));
  
  if(FindObject2(Find_ID(RIG1),Find_Exclude(von),Find_Func("IsFindable")))
  {
   CreateMenu(RIG1,pUser,0,0,0,0,1);
   var next;
   for(next in FindObjects(Find_ID(RIG1),Find_Exclude(von),Find_Func("IsFindable")))
   {
    AddMenuItem(Format("%s",LocalN("name",next)),"Go",MEPU,pUser,0,next,"Anwählen");
   }
   return(1);
  }
  else
  {
   Message("Kein anzuwählender Ringtransporter in der Nähe!",this());
   Sound("Error");
  }
  return(1);
}
