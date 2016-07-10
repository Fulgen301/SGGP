/*-- Garage Door opener (GDO) --*/

#strict

local target;

func Initialize()
{
  SetPicture(10,0,120,90);
  return(1);
}

public func ContextMenu(object pCaller)
{
  [$Menu$|Image=GDO_]
  ControlDigDouble(pCaller);
}

func Check()
{
  if(target = FindObject2(Find_Distance(500),Find_Func("IsStargate"),Find_Or(Find_Action("Outgoing3"),Find_Action("Outgoing4"))))
  {
   if(target->pToClose())
   {
    SetPicture(250,0,120,90);
   }
   else
   {
    SetPicture(130,0,120,90);
   }
  }
  else
  {
   SetPicture(10,0,120,90);
  }
  return(1);
}

func ControlDigDouble()
{
  if(target = FindObject2(Find_Distance(500),Find_Func("IsStargate"),Find_Or(Find_Action("Outgoing3"),Find_Action("Outgoing4"))))
  {
   Sound("BipBipBip");
   CallMessageBoard(0, false, "Passwort:", GetOwner(Contained()));
  }
  else
  {
   Message("Kein Gate in Reichweite!",Contained());
  }
  return(1);
}

func InputCallback(pw)
{
  if(target = FindObject2(Find_Distance(500),Find_Func("IsStargate"),Find_Or(Find_Action("Outgoing3"),Find_Action("Outgoing4"))))
  {
   Sound("BipBipBip");
   LocalN("pTo",target)->GDOControlIris(pw);
  }
  else
  {
   Message("Kein Gate in Reichweite!",Contained());
  }
  return(1);
}
