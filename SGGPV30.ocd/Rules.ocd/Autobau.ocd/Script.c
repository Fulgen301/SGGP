/*-- Autobau --*/

#strict

local obj;


func Initialize() {
   
  return(1);
}

func Timer()
{
  for(obj in FindObjects(Find_OCF(OCF_Construct())))
  {
   obj -> DoCon(1);
  }
  return(1);
}

func Activate(int iPlayer)
{
	MessageWindow("Sorgt für den automatischen Aufbau von Objekten!",iPlayer);
}
local Name = "$Name$";
