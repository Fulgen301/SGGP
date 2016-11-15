/*-- DHD Kristall --*/



local Damaged;

func Initialize() 
{   
  return(1);
}

func Hit()
{
  Sound("Crystal*");
  Damaged = 1;
  SetGraphics("Damaged");
  return(1);
}

func Activate(object pUser)
{
  Sound("CommadFailure1");
  if (Damaged == 1) pUser->Message("<c ff0000>$Damaged$</c>");
  if (Damaged == 0) pUser->Message("<c 00ff00>$NotDamaged$</c>");
  return(1);
}

func Damage()
{
  return(Damaged);
}
local Name = "$Name$";
local Collectible = 1;
