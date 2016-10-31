/*--- Die Stargaterampe (Stein) ---*/

#strict
#include SGR1

func Holde()
{
  Effect();
  if(! target)  { return(1); }
  target -> SetPosition(GetX(this())-78,GetY(this())-71);
  SetCategory(130);
  return(1);
}

func Effect()
{
  if(target)
  {
   if(!target->IsBusy())
   {
    return(1);
   }
  }
  if(GetMaterial(0,-20) == Material("Water"))
  {
   return(1);
  }
  if(GetCon() != 100)
  {
   return(1);
  }
//  if (type == 0)
//  {
	  CreateParticle("Fire", RandomX(-2, 2) - 34, -13, 0, RandomX(-6, -12), RandomX(40, 60), RGBa(255, RandomX(224, 255), 0, 128));
	  CreateParticle("Fire2", RandomX(-2, 2) - 34, -13, 0, RandomX(-8, -14), RandomX(40, 60), RGBa(255, 255, 255, 64));

	  CreateParticle("Fire", RandomX(-2, 2) + 10, -13, 0, RandomX(-6, -12), RandomX(40, 60), RGBa(255, RandomX(224, 255), 0, 128));
	  CreateParticle("Fire2", RandomX(-2, 2) + 10, -13, 0, RandomX(-8, -14), RandomX(40, 60), RGBa(255, 255, 255, 64));
	  return(1);
//  }
//  if (type == 1)
//  {
//	  CreateParticle("Fire", RandomX(-2, 2) - 34, -13, 0, RandomX(-6, -12), RandomX(40, 60), RGBa(0, RandomX(224, 255), 255, 128));
//	  CreateParticle("Fire2", RandomX(-2, 2) - 34, -13, 0, RandomX(-8, -14), RandomX(40, 60), RGBa(255, 255, 255, 64));
//
//	  CreateParticle("Fire", RandomX(-2, 2) + 10, -13, 0, RandomX(-6, -12), RandomX(40, 60), RGBa(0, RandomX(224, 255), 255, 128));
//	  CreateParticle("Fire2", RandomX(-2, 2) + 10, -13, 0, RandomX(-8, -14), RandomX(40, 60), RGBa(255, 255, 255, 64));
//	  return(1);
//  }
}

public func IsStargateRamp()
{
	return(1);
}
local Name = "$Name$";
