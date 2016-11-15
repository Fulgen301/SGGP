/*--- Die Stargaterampe (SGC) ---*/

local Energie;
local target;
local type;

func Initialize() 
{
  var own;
  own = GetCursor(GetOwner());
  CreateMenu(GetID(),own,0,"Welches Gate?",0,1);
  for(var i = 0, Def; Def = GetDefinition(i); i++)
  {
	  if(Def->~IsStargate() && Def != Stargate)
	  {
		  own->AddMenuItem(Def->GetName(), "PlaceGate", Def);
	  }
  }
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
