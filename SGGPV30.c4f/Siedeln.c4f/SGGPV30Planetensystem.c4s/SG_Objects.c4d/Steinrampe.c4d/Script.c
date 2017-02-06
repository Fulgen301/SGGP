#strict 2
#include SGR1

func Holde()
{
  if(!target)  { return(1); }
  target -> SetPosition(GetX(this)-70,GetY(this)-76);
  SetCategory(130);
  return(1);
}