/*-- DHD Kristall --*/

#strict

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
  if (Damaged == 1) Message("<c ff0000>$Damaged$</c>",pUser);
  if (Damaged == 0) Message("<c 00ff00>$NotDamaged$</c>",pUser);
  return(1);
}

func Damage()
{
  return(Damaged);
}
local Name = "$Name$";
local Collectible = 1;
