/*-- Sarkophag --*/

#strict

#include DOOR

local countr;
local counte;
local heal;

protected func SoundOpenDoor()  	{ return(1); }
protected func SoundCloseDoor() 	{ return(1); }
protected func IsBulletTarget() 	{ return(1); }
protected func IsMachine() 			{ return(1); }

protected func Damage()
{
  if(GetDamage(this()) >= 500)
  {
   Explode(100);
   return(1);
  }
  SetEntrance(0);
  return(1);
}


protected func ActivateEntrance(object by)
{
  if((by->GetOCF() & OCF_CrewMember) && !Contents())
  {
   if(by == Contents()) 
   { 
    Exit(by); 
   }
   else if(!ContentsCount()) 
   {
    if(GetAction() eq "Auf")
    {
     return(1);
    }
    
    if(GetAction() eq "DoorOpen")
    {
     Enter(this(),by);
     return(1);
    }
    
    if(GetAction() eq "OpenDoor")
    {
     Enter(this(),by);
     return(1);
    }
    
    SetAction("Auf");
   }
   FinishCommand(by, true);
  }
  
  else 
  {
   FinishCommand(by, false); 
  }
}

protected func Check()
{
  if(GetAction() ne "DoorOpen")
  {
   SetEntrance(0);
  }
  else
  {
   SetEntrance(1);
  }
  
  if(GetAction() ne "OpenDoor")
  {
   SetEntrance(0);
  }
  else
  {
   SetEntrance(1);
  }

  countr ++;
  counte ++;
  heal=ObjectCount(TANG,-200,-200,400,400,OCF_InFree(),"Offen9");

  if(FindObject(TANG,-200,-200,400,400,OCF_InFree(),"Offen9"))
  {
   if(FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))
   {
    if(GetAction() eq "Idle")
    {
     FindObject(0,0,0,0,0,OCF_Alive(),0,0,this())->DoEnergy(heal);
    }
   }
  }

  if(countr == 10)
  {
   if(GetAction() eq "Idle")
   {
    if(FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))
    {
     FindObject(0,0,0,0,0,OCF_Alive(),0,0,this())->DoEnergy(1);
    }
   }
   countr=0;
  }
  
  
  if(counte == 100)
  {
   if(GetAction() eq "Idle")
   {
    if(FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))
    {
     FindObject(0,0,0,0,0,OCF_Alive(),0,0,this())->TrainPhysical("Energy",5,500000);
    }
   }
   counte=0;
  }
  
  if(FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))
  {
   if(GetAction(this()) eq "OpenDoor")
   {
    SetAction("Idle");
   }
  }
  
  if(FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))
  {
   SetEntrance(0);
   return(1);
  }
  return(1);
}

protected func ContainedDown()
{
  Call("ContainedUp");
  return(1);
}

protected func ContainedUp()
{
  if(GetAction(this()) eq "Exit")
  {
   return(1);
  }
  
  if(GetAction(this()) eq "DoorOpen")
  {
   return(1);
  }
  
  if(GetAction(this()) eq "CloseDoor")
  {
   return(1);
  }
  
  SetAction("Exit");
  return(1);
}

protected func Out()
{
  FindObject(0,0,0,0,0,OCF_Alive(),0,0,this())->Exit();
  return(1);
}