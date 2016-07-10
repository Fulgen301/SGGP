/*-- Virus --*/

#strict 2

local fly;
local time;
local iDamg;

protected func Initialize()
{
  SetAction("Stand");
  time = 1080;
//  AddEffect("Target", this, 1, 1, this);
  return(1);
}

protected func Damage()
{
  if(GetDamage() > 10)
  {
   if(fly != 0)
   {
    Explode(10);
    return(1);
   }
   Sound("Glass");
   Stufe4();
   RemoveObject();
   return(1);
  }
  return(1);
}

protected func BuildUp()
{
  SetCon(1);
}


protected func EMPShock()
{
  DoDamage(200);
}

protected func Damage(int iDam)
{
  iDamg += iDam;
  if(iDamg > 1200)
  {
    Sound("Glass");
    CastParticles("SplinterGlass", 15, 35, RandomX(-5,5), -5, 20, 20, RGBa(0,255,0,0), RGBa(0,255,0,0));
    CastParticles("SplinterGlass", 10, 30, RandomX(-5,5), -5, 20, 20, RGBa(100,100,100,0), RGBa(100,100,100,0));
    return(RemoveObject());
  }
}

protected func IsBulletTarget()
{
  return(true);
}

protected func IsRepli()
{
  return(true);
}

protected func Check()
{
  if(GetCon() < 100)
  {
	DoCon(1);
	return;
  }
  if(GetAction() == "Buildet")
  {
   /*if(time == 1080)
   {
    Sound("chargelift");
   }
   if(time == 36)
   {
    Explode(40);
    return(1);
   }
   Message("%v",this,time/36);
   time --;*/
   if(RandomX(-10,10) == 0)
   {
    CreateParticle("Fire",1,-9,0,0,60,RGBa(0,255,0,128));
   }
   return(1);
  }

  if(fly != 0)
  {
   CreateParticle("Fire",RandomX(-2,2),5,0,RandomX(-6,-12),RandomX(70,90),RGBa(10,RandomX(10,20),255,128));
   CreateParticle("Fire2",RandomX(-2,2),5,0,RandomX(-8,-14),RandomX(70,90),RGBa(255,255,255,64));
  }

  if(fly == 1)
  {
   if(GetY() < -50)
   {
    var obj;
    var i;
    if(GetPlayerCount()) while(i != GetOwner()) i = Random(GetPlayerCount());
    obj = FindBase(i);
    if(!obj) obj = GetCursor(i);
    if(!obj) obj = FindObject2(Find_Owner(i));
    SetPosition(RandomX(GetX(obj)-100,GetX(obj)+100),GetY());
    Stufe2();
   }
  
   if(GetYDir() == 0)
   {
    CastParticles("Smoke",40,1000,0,10,1, 350, RGBa(2,2,2,50), RGBa(20,20,20,100));
    CastParticles("Smoke",50,700,0,10,1, 200, RGBa(2,2,2,50), RGBa(20,20,20,100));
    SetYDir(-10);
   }
   SetXDir(0);
   
   if(GetYDir() < 20)
   {
    SetYDir(GetYDir() - 3);
   }
  }
  
  if(fly == 2)
  {
   if(GBackSolid(0,5))
   {
    fly = 0;
    ScheduleCall(0,"Stufe3",100);
    return(1);
   }
   if(GetYDir() > 30)
   {
    SetYDir(GetYDir() - 2);
   }
  }
  return(1);
}

protected func Start()
{
  if(GetAction() == "Stand")
  {
   SetAction("ClipIn");
   ScheduleCall(0,"Stufe1",75);
   return(1);
  }
  return(1);
}

protected func Stufe1()
{
  fly = 1;
  return(1);
}

protected func Stufe2()
{
  SetYDir(0);
  SetXDir(0);
  fly = 2;
  return(1);
}

protected func Stufe3()
{
  SetAction("Drill");
  ScheduleCall(0,"Stufe4",100);
  return(1);
}

protected func Stufe4()
{
  SetAction("Erb");
  Sound("Glass");
  CastParticles("SplinterGlass", 15, 35, RandomX(-5,5), -5, 20, 20, RGBa(0,255,0,0), RGBa(0,255,0,0));
  CastParticles("SplinterGlass", 10, 30, RandomX(-5,5), -5, 20, 20, RGBa(100,100,100,0), RGBa(100,100,100,0));
  return(1);
}

public func IsBulletTarget() { return(true); }