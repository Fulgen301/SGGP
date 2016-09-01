/*--- Die Stargaterampe (SGU) ---*/

#strict
#include SGR1

func Holde()
{
  if(! target)  { return(1); }
  target -> SetPosition(GetX(this())-73,GetY(this())-71);
  SetCategory(130);
  return(1);
}

func ReName(string szName)
{
	return(target->ReName(szName));
}

public func IsStargateRamp()
{
	return(1);
}
