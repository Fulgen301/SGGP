/*-- Defcon --*/

#strict 2

local light,controller;

func Construction()
{
	SetCategory(C4D_StaticBack);
	return(1);
}

func Initialize() {
if(!(controller = FindObject2(Find_ID(DEFK),Find_Owner(GetOwner()))))
{
	controller=CreateObject(DEFK,0,0,GetOwner());
}
  SetAction("Def1");
  light = AddLight(100,0,this);
  return(1);
}

func Check()
{
if(!(controller = FindObject2(Find_ID(DEFK),Find_Owner(GetOwner()))))
{
	controller=CreateObject(DEFK,0,0,GetOwner());
}

  if(controller && controller->GetAction() == "Def1")
  {
   SetAction("Def1");
   light->ChangeColor(RGB(0,0,255));
   return(1);
  }
  
  else if(controller && controller->GetAction() == "Def2")
  {
   SetAction("Def2");
   light->ChangeColor(RGB(0,255,0));
   return(1);
  }
  
  else if(controller && controller->GetAction() == "Def3")
  {
   SetAction("Def3");
   light->ChangeColor(RGB(255,255,0));
   return(1);
  }
  
  else if(controller && controller->GetAction() == "Def4")
  {
   SetAction("Def4");
   light->ChangeColor(RGB(255,0,0));
   return(1);
  }
  
  else if(controller && controller->GetAction() == "Def5")
  {
   SetAction("Def5");
   light->ChangeColor(RGB(0,0,0));
   return(1);
  }
  return(1);
}
