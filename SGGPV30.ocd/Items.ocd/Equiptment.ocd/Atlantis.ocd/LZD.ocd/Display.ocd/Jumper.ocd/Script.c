/* Marke */

#strict

local time;

func Initialize()
{
  SetVisibility(VIS_Owner);
  return(1);
}

func Disappear()
{
  Message("Jumper",this());
  time ++;

  if (time >= 38)
  {
    RemoveObject();
    return;
  }
  return(1);
}
local Name = "$Name$";
