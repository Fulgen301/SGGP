#strict
#include SHT1


public func BulletStrike(object pObj) 
{
  if(pObj)
  {   
   pObj->DoDamage(2);
   if(pObj)
   {
    pObj->DoEnergy(-2);
   }
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
