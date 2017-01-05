/*-- Neues Objekt --*/

#strict 2
protected func Construction()
{
	AddEffect("IntCheck", this, 1, 1, this);
}
func Initialize() {
   var chair;
  if((chair = FindObject2(Find_ID(ANKS), Find_Owner(GetOwner())))) SetPosition(chair->GetX(), chair->GetY());
}

protected func FxIntCheckTimer(object pTarget, int iEffect, int time)
{
	if((EffectVar(0, pTarget, iEffect) = FindObject2(Find_ID(ANKS), Find_Owner(GetOwner())))) SetPosition(EffectVar(0, pTarget, iEffect)->GetX(), EffectVar(0, pTarget, iEffect)->GetY());
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

public func GetRace() { return SG1_StargateCenter | SG1_Ancient; }