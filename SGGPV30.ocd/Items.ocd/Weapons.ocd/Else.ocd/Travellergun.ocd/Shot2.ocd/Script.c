#strict
#include SH7X

public func BulletStrike(object pObj) 
{
  if(pObj)
  {
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
