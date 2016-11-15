/*-- Infoding --*/



local pAttacher;

protected func Initialize()
{
  SetVisibility(VIS_God);
}

protected func GetTarget(object pAttach){
    pAttacher = pAttach;
    SetAction("Attach",pAttacher);
    SetOwner(GetOwner(pAttach));
  return(1);
  }
  
protected func Timer(){
  if(!pAttacher) RemoveObject();
  return(1);
  }  
local ActMap = {
Attach = {
Prototype = Action,
Name = "Attach",
Procedure = DFA_ATTACH,
Delay = 1,
FacetBase = 1,
NextAction = "Attach",
PhaseCall = "Timer",
},  };
local Name = "$Name$";
