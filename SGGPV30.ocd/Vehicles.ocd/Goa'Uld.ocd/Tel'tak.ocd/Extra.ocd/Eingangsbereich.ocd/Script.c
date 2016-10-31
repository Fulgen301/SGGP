#strict

local target;

public func Initialize()
{
  target = FindObject(TEL_,0,0,-1,-1);
  SetEntrance(1);
  return(1);
}

public func Time()
{
  if(!target)
  {
   RemoveObject();
   return(1);
  }
  if(FindObject2(Find_Container(this()),Find_OCF(OCF_Alive())))
  {
   FindObject2(Find_Container(this()),Find_OCF(OCF_Alive()))->Enter(target);
  }
  
  if(FindObject(0,0,0,0,0,0,0,0,this()))
  {
   FindObject(0,0,0,0,0,0,0,0,this())->Exit();
  }
  return(1);
}

public func Teltak()
{
	return(1);
}
local Name = "Eingangsbereich";
