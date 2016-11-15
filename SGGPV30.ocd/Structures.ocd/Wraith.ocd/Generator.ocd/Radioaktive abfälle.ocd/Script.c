/*--- Radioactive Waste ---*/



local size;
local strange;

func Initialize()
{
  size = 50;
  strange = 1;
  return(1);
}

func Hit () 
{
  CastParticles("SlimeGrav", 10, 25, 0, 0, 20, 40, RGBa(0, 240, 0, 10), RGBa(20, 255, 20, 75));
  Sound("RockHit*");
  return(1);
}

public func Check()
{
  if(GetID(Contained()) == ATOB)
  {
   if(LocalN("closed",Contained()) == 1)
   {
    return(1);
   }
  }

  CastParticles("SlimeGrav", 5, 20, 0, 0, 15, 25, RGBa(0, 240, 0, 10), RGBa(20, 255, 20, 75));

//Das Strahlungsverhalten:
  size = ( ObjectCount(RADW,-100,-100,200,200) +1) * 10;

  var x;
  for(x in FindObjects(Find_Distance(size),Find_OCF(OCF_Alive())))
  {
   if(RandomX(-10,10) == 0)
   {
    x->DoDamage(strange);
    x->DoEnergy(-strange);
    x->CastParticles("SlimeGrav", 5, 20, 0, 0, 15, 25, RGBa(0, 240, 0, 10), RGBa(20, 255, 20, 75));
   }
  }
  return(1);
}

func Damage(int Change)
{
  CastParticles("SlimeGrav", Change, 25, 0, 0, 20, 40, RGBa(0, 240, 0, 10), RGBa(20, 255, 20, 75));
  return(1);
}
local Name = "$Name$";
local Collectible = 1;
