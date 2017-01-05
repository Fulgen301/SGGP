/*-- Generator --*/

#strict

local trash;

func Initialize()
{
  SetAction("Close");
  return(1);
}

func Damage()
{
  if(GetDamage() >= 150)
  {
   Explode(100);
  }
  return(1);
}

func Check()
{
  if(GetDamage() > 100)
  {
   SetGraphics("Red");
   return(1);
  }
  
  if(GetDamage() > 50)
  {
   SetGraphics("Orange");
   return(1);
  }
  SetGraphics();
  return(1);
}

func ControlDigDouble()
{
  if(GetAction() eq "Open")
  {
   SetAction("Closes");
   return(1);
  }
  
  if(GetAction() eq "Close")
  {
   SetAction("Opens");
   return(1);
  }
  return(1);
}

func Produce()
{
  if(trash)
  {
   var laser = CreateObject(LASR);
   laser->SetClrModulation(RGB(0,255,0));
   laser->Set(0,5,25,3,this());
   trash->SetXDir();
   trash->SetYDir();
   trash->SetRDir(15);
   trash->SetPosition(GetX(),GetY()-10);
   if(Contained(trash))
   {
    trash = 0;
   }
  }
  
  if(RandomX(-1100,1100) == 1)
  {
   if(CheckEnergyNeedChain())
   {
    trash = CreateObject(RADW);
   }
   if(!FindObject(ENRG))
   {
    trash = CreateObject(RADW);
   }
  }
  
  var rand;
  var x;
  var angle;
  rand = RandomX(1,4);
  if(rand == 1)
  {
   x = -15;
  }
  if(rand == 2)
  {
   x = -28;
  }
  if(rand == 3)
  {
   x = 15;
  }
  if(rand == 4)
  {
   x = 28;
  }
  
  angle = Angle(Abs(GetX())+x,Abs(GetY())-15 ,Abs(GetX()),Abs(GetY()));
  
  if(RandomX(-30,30) == 1)
  {
   var laser = CreateObject(LASR,x,-12);
   laser->SetClrModulation(RGB(0,255,0));
   laser->Set(angle,5,20,15,this());
  }
  return(1);
}

func EMPShock()
{
  EMPShockEffect(50);
  if(GetAction() eq "Open")
  {
   SetAction("Closes");
  }
  DoDamage(10);
  return(1);
}

func IsMachine() 		{ return(1); }
public func GetRace() { return SGA_Wraith; }