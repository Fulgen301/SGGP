/*-- Naniten Spritze --*/



local target;
local targetname;
local next;

func Initialize() 
{   
  return(1);
}

func Activate()
{
  SetComDir(COMD_Stop(),Contained());
  CreateMenu(NANO,Contained(),0,0,0,0,1);
  AddMenuItem("Selbst Injekzieren","Inject",GetID(Contained()),Contained());
  
  if(FindObject2(Find_Distance(15),Find_Exclude(Contained()),Find_OCF(OCF_Alive())))
  {
   for(next in FindObjects(Find_Distance(15),Find_Exclude(Contained()),Find_OCF(OCF_Alive())))
   {
    AddMenuItem(Format("%s von %s Injekzieren",GetName(next),GetPlayerName(GetOwner(next))),"OtherInject",GetID(next),Contained(),0,next,"Naniten Injekzieren");
   }
   return(1);
  }
  return(1);
}

func OtherInject(trash, target)
{
  if(!GetEffect("Nanite",target)) 
  {
   AddEffect("Nanite",target, 3,30, target);
   AddEffect("Renanite",target, 3,1, target);
   Sound("inject");
   Message("Naniten wurden %v injekziert",Contained(),GetName(target));
   RemoveObject();
   return(1);
  }
  
  if(GetEffect("Nanite",target))
  {
   Message("Er hat schon Naniten!",Contained());
   return(1);
  }
  
  return(1);
}

func Inject()
{
  if(!GetEffect("Nanite",Contained())) 
  {
   AddEffect("Nanite",Contained(), 3,30, Contained());
   AddEffect("Renanite",Contained(), 3,1, Contained());
   Sound("inject");
   RemoveObject();
   return(1);
  }

  if(GetEffect("Nanite",Contained()))
  {
   Message("Ich hab schon Naniten!",Contained());
   return(1);
  }

  return(1);
}

global func FxNaniteTimer(object pTarget)
{
  if(GetEffect("Genuced",pTarget))
  {
   RemoveEffect("Genuced",pTarget);
   SetClrModulation(0,pTarget);
  }
  
  if(GetAction(pTarget) eq "Lie")
  {
   RemoveEffect("Nanite",pTarget);
   RemoveEffect("Renanite",pTarget);
   ResetPhysical(pTarget);
   return(-1);
  }

  pTarget -> DoEnergy(1);
  SetPhysical("Energy", 300000, PHYS_StackTemporary, pTarget);
  return(1);
}


global func FxRenaniteTimer(object pTarget)
{
  if(GetEffect("Genuced",pTarget))
  {
   RemoveEffect("Genuced",pTarget);
   SetClrModulation(0,pTarget);
  }
  return(1);
}
local Name = "$Name$";
local Collectible = 1;
