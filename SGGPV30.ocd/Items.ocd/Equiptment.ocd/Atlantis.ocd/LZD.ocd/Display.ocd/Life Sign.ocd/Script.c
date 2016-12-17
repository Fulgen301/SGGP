/* Marke */



local time;

func Initialize()
{
  this.Visibility = VIS_Owner;
  return(1);
}

func Disappear()
{
  time ++;

  if (time >= 15)
  {
    RemoveObject();
    return;
  }
  return(1);
}
local Name = "$Name$";
