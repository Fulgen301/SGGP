/*---- Jaffa ----*/

#strict 2
#include CLNK
#include HZCK
#include PCMK

public func Zated()
{
  if(GetAction() == "Lie")
  {
   SetAction("Lie");
   EMPShockEffect(50);
   return(1);
  }
  SetAction("Zatfall");
  EMPShockEffect(50);
  return(1);
}

public func GetRace()	{ return SG1_Goauld; }

protected func RejectCollect(id idObj, object pObj)
{
	if(ObjectCount(RACS))
	{
		if(idObj->~GetRace() == SG_All) return 0;
		else if(idObj->~GetRace() == GetRace()) return 0;
		else return 1;
	}
	return _inherited(idObj, pObj, ...);
}

/*protected func Grab(object pTarget, bool fGrab)
{
	if(fGrab)
	{
		var race = pTarget->~GetRace();
		if(race != GetRace()) return SetCommand(pTarget, "UnGrab");
		else if(race != SG_All) return SetCommand(pTarget, "UnGrab");
	}
	return _inherited(pTarget, fGrab,...);
}//*/
