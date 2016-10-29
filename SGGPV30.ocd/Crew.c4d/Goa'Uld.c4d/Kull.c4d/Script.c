/*---- Kull ----*/

#strict
#include JAFA

static const HZCK_LADDERSPEED = 7;

func Initialize()
{
  if(GetName() eq "Nr.")
  {
   SetName("Nr. 1");
  }
  CreateContents(GOKW);
  CreateContents(GOKR);
  return(_inherited());
}

func RejectCollect(pObj)
{
  if(pObj != GOKR)
  {
   if(pObj != GOKW)
   {
    if(pObj != ENAP)
    {
     return(1);
    }
   }
  }
  return();
}

func UpdateCharge()
{
  if(RandomX(0,2000) == 1)
  {
   DoEnergy(-1);
  }
  return(_inherited());
}

public func GetRace()	{ return SG1_Goauld; }