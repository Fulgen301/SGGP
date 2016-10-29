/*-- Zero Point Modul --*/

#strict

local timer;

func Initialize() 
{
  SetAction("Inactive");
  SetVisibility(VIS_None());
  return(1);
}

func Minus()
{
  if(timer > 0)
  {
   timer--;
   return(1);
  }
  if(FindContents(ZPM_))
  {
   FindContents(ZPM_)->Minus();
   timer = 50;
  }
  return(1);
}

func Enrg()
{
  if(FindContents(ZPM_))
  {
   return(FindContents(ZPM_)->Energ());
  }
  return(0);
}

func GetZpm()
{
  return(FindContents(ZPM_));
}

func Piccheck()
{
  if(FindContents(ZPM_))
  {
   SetVisibility(VIS_All());
   SetAction(GetAction(FindContents(ZPM_)));
  }
  else
  {
   SetAction("Inactive");
   SetVisibility(VIS_None());
  }
  return(1);
}