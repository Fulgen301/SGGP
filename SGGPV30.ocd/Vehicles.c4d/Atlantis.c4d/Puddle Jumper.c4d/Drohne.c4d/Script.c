#strict

local target;
local iX;
local iY;
local light;
local iSpeed;

public func Initialize()
{
  light = AddLight(100,RGB(255,255,0),this());
  SetAction("Dead");
  SetYDir(0);
  return(1);
}

public func FindTarget()
{
  if(GetAction() ne "Fliegen")
  {
   target = 0;
   return(1);
  }

  CastParticles("PxSpark", 5, 50, Random(5), Random(5), 40, 50, RGBa(255,100,0,0), RGBa(255,128,0,128));
  
  if(!target)
  {
   SetYDir(1);
   if(FindObject2(Find_Hostile(GetOwner(this())),Find_Distance(500),Find_OCF(OCF_Alive())))
   {
    target=FindObject2(Find_Hostile(GetOwner(this())),Find_Distance(500),Find_OCF(OCF_Alive()));
   }
  }
  
  if(target)
  {
   if(ObjectDistance(target,this()) <= 10)
   {
    Hit();
    return(1);
   }
  }
  
  if(!target)
  {
   if(FindObject2(Find_Hostile(GetOwner()),Find_Distance(500),Find_Category(C4D_Structure),Find_Not(Find_OCF(OCF_OnFire))))
   {
    target=FindObject2(Find_Hostile(GetOwner()),Find_Distance(500),Find_Category(C4D_Structure),Find_Not(Find_OCF(OCF_OnFire)));
   }
  }

  if(GetDamage(this()) != 0)
  {
   Call("Hit");
  }
  return(1);
}

public func EMPShock()
{
  SetAction("Over");
  EMPShockEffect(2000);
  return(1);
}

public func Over()
{
  SetClrModulation(RGB(20,20,20));
  return(1);
}

public func Start()
{
  return(1);
}
  
public func Fliegen()
{ 
  if(EMPShocked())
  {
   return(1);
  }
  
  if (target)
  {
   SetR(Angle(GetX(),GetY(),GetX(target),GetY(target)));
  }
  
  iX = BoundBy(Sum(iX,Sin(GetR(),50)),-100,100);
  iY = BoundBy(Sub(iY,Cos(GetR(),50)),-100,100);
  SetXDir(iX);
  SetYDir(iY);
  return(1);
}


public func Damage()
{
  if(EMPShocked())
  {
   return(1);
  }

  Call("Hit");
  return(1);
}

public func Hit()
{
  Explode(30);
  Explode(20);
  Explode(10);
  return(1);
}


func IsMachine() 		{ return(1); }
func IsBulletTarget()    { return(1); }

