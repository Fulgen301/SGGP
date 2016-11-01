/*--- Die Stargaterampe (SGC) ---*/
local Energie;
local target;
local type;

protected func Initialize() 
{
  for(var obj in FindObjects(Find_InRect(-1*(GetDefCoreVal("Width", "DefCore")/2),-12,GetDefCoreVal("Width", "DefCore"),22)))
  {
   obj->SetPosition(GetX(), GetY()-25)
  }
  var own;
  own = GetCursor(GetOwner());
  CreateMenu(GetID(),own,0,0,"Welches Gate?",0,1);
  for(var i = 0, Def; Def = GetDefinition(i); i++)
  {
	  if(Def->~IsStargate() && Def != Stargate)
	  {
		  AddMenuItem(GetName(0, Def), "PlaceGate", Def, own);
	  }
  }
  return true;
}

public func PlaceGate(id gate)
{
	target = CreateObject(gate,0,-25);
	target.ramp = this;
  return true;
}

private func Holde()
{
  if(!target)  { return; }
  target -> SetPosition(GetX()-50,GetY()-60);
  SetCategory(130);
  return true;
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
