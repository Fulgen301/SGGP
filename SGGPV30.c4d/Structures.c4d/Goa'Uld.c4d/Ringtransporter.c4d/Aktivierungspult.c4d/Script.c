#strict

local pX, pY;
local pUser;
local next;
local pTo;
local nobase;

public func Initialize()
{
  pX = GetX();
  pY = GetY();
  nobase = 1;
  return(1);
}

public func Check()
{
  return(1);
}

public func IsBulletTarget()
{
  if(!ActIdle())
  {
   return(1);
  }
  return();
}

public func Damage()
{
  if(GetDamage(this()) >= 100)
  {
   Explode(30);
   return(1);
  }
  return(1);
}

public func ControlDigDouble(pCaller)
{
  var von;
  if(FindObject(RIG1,-150,-150,300,300))
  {
   von = FindObject(RIG1,0,0,-1,-1);
  }
  else
  {
   Message("Kein Ringtransporter in der Nähe!",this());
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
   Message("Kein anzuwählender Ringtransporter in der Nähe!",this());
   Sound("Error");
  }
  return(1);
}

public func Go(trash, tar)
{
  pTo = tar;
  if(FindObject(RIG1,-150,-150,300,300))
  {
   SetAction("Fuse");
   Sound("rt_button2");
   return(1);
  }
  Sound("rt_error");
  return(1);
}

public func Start()
{
  if(FindObject(RIG1,-150,-150,300,300))
  {
   FindObject(RIG1,-150,-150,300,300) -> Activate(pTo);
   return(1);
  }
  Sound("rt_error");
  return(1);
}

public func ControlRightDouble(pCaller)
{
  pUser = pCaller;
  CallMessageBoard(0,false,"Geben sie hier den neuen Namen ihres Ringtransporters ein:",GetOwner(pUser));
  return(1);
}

public func ControlLeftDouble(pCaller)
{
  pUser = pCaller;
  if(nobase)
  {
   Sound("rt_button2");
   SetAction("Fuse2");
   return(1);
  }
  return();
}

public func FuseEnd2()
{
  if(nobase)
  {
   if(FindObject(RIG1,-150,-150,300,300)) FindObject(RIG1,-150,-150,300,300) -> Activate(FindObject(RIG1,-150,-150,300,300)->LocalN("ring2"));
   return(1);
  }
  return(1);
}

func InputCallback(string szName)
{
  if(FindObject(RIG1,-150,-150,300,300))
  {
   FindObject(RIG1,-150,-150,300,300)->SetName(szName);
   return(1);
  }
  Message("Kein Ringtransporter in der Nähe!",this());
  return(1);
}

public func GetRace() { return SG1_Ancient | SG1_Goauld; }