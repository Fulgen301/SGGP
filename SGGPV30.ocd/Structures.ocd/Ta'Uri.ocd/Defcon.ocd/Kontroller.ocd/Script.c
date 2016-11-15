/*-- Neues Objekt --*/



func Initialize() {
   
  return(1);
}

func IsConsoleTarget() {return(1);}

public func ConsoleControl(int i)
{
  if(i == 1) return("Defcon1");
  if(i == 2) return("Defcon2");
  if(i == 3) return("Defcon3");
  if(i == 4) return("Defcon4");
  if(i == 5) return("Defcon5");
}


public func ConsoleControlled(int i)
{
  if(i == 1)
  {
   SetAction("Def1");
//   Sound("defcon");
   return(1);
  }
   if(i == 2)
  {
   SetAction("Def2");
//   Sound("defcon");
   return(1);
  }
   if(i == 3)
  {
   SetAction("Def3");
//   Sound("defcon");
   return(1);
  }
   if(i == 4)
  {
   SetAction("Def4");
//   Sound("defcon");
   return(1);
  }
   if(i == 5)
  {
   SetAction("Def5");
//   Sound("defcon");
   return(1);
  }
}
local Name = "$Name$";
