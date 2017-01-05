//*-- Der Ringtransporter --*//
  //*--    BAUOBJEKT   --*//
  
#strict

public func Initialize()
{
  CreateObject(RIG1,0,34);
  RemoveObject();
  return(1);
}

public func GetRace() { return SG1_Ancient | SG1_Goauld; }