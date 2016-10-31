/*-- Defcon --*/

#strict

local light,controller;

func Construction()
{
	SetCategory(C4D_StaticBack);
	return(1);
}

func Initialize() {
if(!FindObject(DEFK))
{
	controller=CreateObject(DEFK);
}
else
{
	controller=FindObject(DEFK);
}
  SetAction("Def1");
  light = AddLight(100,0,this());
  return(1);
}

func Check()
{
  if(!FindObject(DEFK))
  {
	  CreateObject(DEFK);
   return(1);
  }

  if(GetAction(FindObject(DEFK)) eq "Def1")
  {
   SetAction("Def1");
   light->ChangeColor(RGB(0,0,255));
   return(1);
  }
  
  if(GetAction(FindObject(DEFK)) eq "Def2")
  {
   SetAction("Def2");
   light->ChangeColor(RGB(0,255,0));
   return(1);
  }
  
  if(GetAction(FindObject(DEFK)) eq "Def3")
  {
   SetAction("Def3");
   light->ChangeColor(RGB(255,255,0));
   return(1);
  }
  
  if(GetAction(FindObject(DEFK)) eq "Def4")
  {
   SetAction("Def4");
   light->ChangeColor(RGB(255,0,0));
   return(1);
  }
  
  if(GetAction(FindObject(DEFK)) eq "Def5")
  {
   SetAction("Def5");
   light->ChangeColor(RGB(0,0,0));
   return(1);
  }
  return(1);
}
local Name = "$Name$";
