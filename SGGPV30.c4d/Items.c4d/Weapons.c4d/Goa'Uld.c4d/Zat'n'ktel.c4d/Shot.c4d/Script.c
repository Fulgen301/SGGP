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