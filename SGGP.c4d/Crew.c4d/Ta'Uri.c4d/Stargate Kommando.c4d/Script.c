/*---- Stargate Kommando ----*/

#strict 2
#include JAFA

local hegrend;

/* Kontextmenü */

protected func ContextGetGrenade()
{
  [$CtxGetGrenade$|Image=HEGR|Condition=GetGrenade]
  CreateContents(HEGR);
  hegrend--;
  Sound("Connect");
  return(1);
}

protected func ContextPutGrenade() 
{
  [$CtxPutGrenade$|Image=HEGR|Condition=PutGrenade]
  hegrend ++;
  FindObject(HEGR,0,0,0,0,0,0,0,this)->RemoveObject();
  Sound("Connect");
  return(1);
}

protected func GetGrenade()
{
  if(hegrend != 0)
  {
   return(1);
  }

  return(0);
}

protected func PutGrenade()
{
  if(FindObject(HEGR,0,0,0,0,0,0,0,this))
  {
   if(hegrend < 2)
   {
    return(1);
   }
  }

  return(0);
}

/* Gestorben */

protected func Death() 
{
  if(hegrend == 1)
  {
   CreateObject(HEGR);
   hegrend = 0;
  }

  if(hegrend == 2)
  {
   CreateObject(HEGR);
   CreateObject(HEGR);
   hegrend = 0;
  }
  return(_inherited());
}

public func GetRace()	{ return SG1_StargateCenter; }