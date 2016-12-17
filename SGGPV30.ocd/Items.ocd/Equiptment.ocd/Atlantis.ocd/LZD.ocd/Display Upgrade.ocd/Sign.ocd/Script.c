/* Marke */



local time;
local name;

func Initialize()
{
  this.Visibility = VIS_Owner;
  time = 11;
  return(1);
}

func Disappear()
{
  this->Message("%v",,name->GetName());
  
  time --;
  if (time == 0)
  {
    RemoveObject();
    return();
  }
  return(1);
}
local Name = "$Name$";
