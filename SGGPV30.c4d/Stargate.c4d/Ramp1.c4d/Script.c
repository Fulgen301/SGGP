/*--- Die Stargaterampe (SGC) ---*/

#strict

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
  CreateMenu(SGR1,own,0,0,"Welches Gate?",0,1);
  AddMenuItem("Milchstraßen-Gate","PlaceGate",STGT,own);
  AddMenuItem("Pegasus-Gate","PlaceGate",SGAG,own);
  AddMenuItem("Destiny-Gate", "PlaceGate", SGDG, own);
  return(1);
}

func PlaceGate(id gate)
{
	target = CreateObject(gate,0,-25);
	LocalN("ramp",target) = this;
  return(1);
}

func Holde()
{
  if(!target)  { return(1); }
  target -> SetPosition(GetX(this)-50,GetY(this)-60);
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
