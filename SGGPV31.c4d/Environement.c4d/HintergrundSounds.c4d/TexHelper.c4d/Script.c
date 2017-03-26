/*-- Infoding --*/

#strict

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
