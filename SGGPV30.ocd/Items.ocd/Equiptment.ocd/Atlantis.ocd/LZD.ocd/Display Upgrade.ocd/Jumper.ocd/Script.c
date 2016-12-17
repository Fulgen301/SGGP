/* Marke */



local time;

func Initialize()
{
  SetVisibility(VIS_Owner);
  return(1);
}

func Disappear()
{
 this->Message("Jumper");
  time ++;

  if (time >= 11)
  {
    RemoveObject();
    return;
  }
  return(1);
}
local Name = "$Name$";
