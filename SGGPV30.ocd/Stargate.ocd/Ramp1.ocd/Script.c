/*--- Die Stargaterampe (SGC) ---*/

local Energie;
local target;
local type;

func Initialize() 
{
  var hlp;
  while(FindObject(0,-1*(GetDefCoreVal("Width", "DefCore")/2),-12,GetDefCoreVal("Width", "DefCore"),22))
  {
   var hlp = FindObject(0,-1*(GetDefCoreVal("Width", "DefCore")/2),-12,GetDefCoreVal("Width", "DefCore"),22);
   hlp->SetPosition(GetX(),GetY()-25);
  }
  var own;
  own = GetCursor(GetOwner());
  CreateMenu(GetID(),own,0,0,"Welches Gate?",0,1);
  for(var i = 0, Def; Def = GetDefinition(i); i++)
  {
	  if(Def->~IsStargate() && Def != Stargate)
	  {
		  AddMenuItem(Def->GetName(), "PlaceGate", Def, own);
	  }
  }
  /*AddMenuItem("Milchstra�en-Gate","PlaceGate",STGT,own);
  AddMenuItem("Pegasus-Gate","PlaceGate",SGAG,own);
  AddMenuItem("Destiny-Gate", "PlaceGate", SGDG, own);*/
  return(1);
}

func PlaceGate(id gate)
{
	target = CreateObject(gate,0,-25);
	target.ramp = this;
  return(1);
}

func Holde()
{
  if(!target)  { return(1); }
  target -> SetPosition(GetX()-50,GetY()-60);
  SetCategory(130);
  return(1);
}

func ReName(string szName)
{
	return(target->ReName(szName));
}

public func IsStargateRamp()
{
	return(1);
}
local Name = "$Name$";
