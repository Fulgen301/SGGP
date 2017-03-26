/*-- Transportkern --*/

#strict

local target;
local signs;
local beam;
local obj;
local free;
local time;

func Initialize() 
{
  beam = CreateObject(WRDB);
  beam -> ChangeSizeXY(500,1280);
  beam -> ChangeR(180);
  SetVisibility(VIS_None());
  time = 370;
  return(1);
}

func SaveMe()
{
  free = 1;
  SetAction("Idle");
  SetVisibility(VIS_All());
  return(1);
}

func SetTarg(obj)
{
  target = obj;
  beam = LocalN("light",target);
  beam -> SetTarg(this());
  beam -> ChangeSizeXY(500,1280);
  beam -> ChangeR(180);
  SetVisibility(VIS_None());
  return(1);
}

func Check()
{
  if(free)
  {
   if(FindObject2(Find_OCF(OCF_Alive()),Find_OCF(OCF_InFree()),Find_Distance(30)))
   {
    if(time != 0)
    {
     Message("%v",this(),time/37);
     time --;
    }
    else
    {
     while(FindObject2(Find_Container(this()),Find_OCF(OCF_Alive())))
     {
      FindObject2(Find_Container(this()),Find_OCF(OCF_Alive()))->Exit();
     }
     Sound("JumperAttack");
     MuzzleFlash(100,this(),0,0,90);
     CastParticles("AlienPlasma", 30, 50, RandomX(-20,20), -5, 20, 20, RGBa(100,100,100,0), RGBa(100,100,100,0));
     CastParticles("SplinterGlass", 30, 50, RandomX(-20,20), -5, 20, 20, RGBa(100,100,100,0), RGBa(100,100,100,0));
     RemoveObject();
     return(1);
    }
   }
   else
   {
    time = 370;
   }
   return(1);
  }
    
  signs=ObjectCount2(Find_Container(this()),Find_OCF(OCF_Alive()));
  if(GetAction(target) eq "Turn")
  {
   if(GetDir(target) == 0)
   {
    SetPosition(GetX(target)+GetActTime(),GetY(target));
   }
   if(GetDir(target) == 1)
   {
    SetPosition(GetX(target)-GetActTime(),GetY(target));
   }
   return(1);
  }
  
  if(GetDir(target) == 0)
  {
   SetPosition(GetX(target)+40,GetY(target)+4);
  }
  if(GetDir(target) == 1)
  {
   SetPosition(GetX(target)-25,GetY(target)+4);
  }
  return(1);
}

public func Eject()
{
  if(FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))
  {
   obj = FindObject(0,0,0,0,0,OCF_Alive(),0,0,this());
  }

  if(!obj)
  {
   return(1);
  }

  MuzzleFlash(200,this(),0,0,180,RGB(0,255,0));
  obj->Exit();
  obj->SetAction("Tumble");
  obj->SetYDir(5000);
  obj->SetXDir(0);
  return(1);
}
