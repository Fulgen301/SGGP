#strict
#include SHT2


public func BulletStrike(object pObj) 
{
  if(pObj)
  {
   if(GetAction(pObj) eq "Lie")
   {
    Kill(pObj);
    pObj->SetAction("Dead");
    return(1);
   }
   
   if(GetAction(pObj) eq "Dead")
   {
    Kill(pObj);
    pObj->SetAction("Dead");
    return(1);
   }
   
   if(GetAction(pObj) eq "Zatfall")
   {
    Kill(pObj);
   }
   pObj->~Zated();
  }
  return(1);
}
local ActMap = {
Travel = {
Prototype = Action,
Name = "Travel",
Procedure = DFA_FLOAT,
NextAction = "Travel",
FacetBase = 1,
Length = 1,
Delay = 1,
StartCall = "Traveling",
},  };
local Name = "$Name$";
