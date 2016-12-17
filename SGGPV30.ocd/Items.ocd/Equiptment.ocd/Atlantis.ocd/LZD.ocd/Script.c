/*-- LZD --*/



local on;
local target;
local upgraded;
local starget;
local next;
local user;
local jumper;
local jumpermark;

func Initialize() 
{
  ScheduleCall(this,"JumperSet",2);
  on = 0;
  upgraded = 0;
  return(1);
}

func JumperSet()
{
  if(Contained() && Contained()->GetID() == PUD_)
  {
   jumper = Contained();
  }
  return(1);
}

func Entf()
{
  if(target)
  {
   target->RemoveObject();
  }
  return(1);
}

func Activate()
{
  SetOwner(GetOwner(Contained()));
  CreateMenu(GetID(),Contained(),0,nil,0,3);
  Contained()->AddMenuItem("An/Aus","Switch",LZDS);
  
  if(upgraded)
  {
   Contained()->AddMenuItem("Object Markieren","Select",Arrow);
  }
  
  if(starget)
  {
   Contained()->AddMenuItem("Markierung löschen","DeSelect",Arrow);
  }
  
  if(jumper)
  {
   if(jumper.kindersicherung)
   {
    Contained()->AddMenuItem("Jumper Tarnen","Cloak",PUD2);
   }
   Contained()->AddMenuItem("Jumperortung","JumperMark",LZD5);
   
   Contained()->AddMenuItem("Jumper Tarnen","Cloak2",PUD2);
 
   Contained()->AddMenuItem("Jumper Heckluke","Luke",PUD7);
  }
  return(1);
}

func JumperMark()
{
  if(jumpermark)
  {
   jumpermark = 0;
   Message("Jumperortung ist aus!",this());
   if(target)
   {
    target.jumper = nil;
   }
   return(1);
  }
  
  if(!jumpermark)
  {
   jumpermark = 1;
   this->Message("Jumperortung ist an!");
   if(target)
   {
    target.jumper = jumper;
   }
   return(1);
  }
  return(1);
}
  
func Luke()
{
  jumper->Luke();
  return(1);
}

func Cloak()
{
  if(jumper->GetAction() == "Open")
  {
   jumper->SetAction("Stand");
  }
  jumper->Cloak();
  jumper.pUser = Contained();
  jumper->SetOwner(GetOwner());
  ScheduleCall(this,"CloseJumper",21);
  return(1);
}

func Cloak2()
{
  if(jumper->GetAction() == "Open")
  {
   jumper->Luke();
   ScheduleCall(,"Cloak2",22);
   return(1);
  }
  jumper->Cloak();
  jumper.pUser = Contained();
  jumper->SetOwner(GetOwner());
  return(1);
}

func CloseJumper()
{
  jumper.open = 0;
  return(1);
}

func DeSelect()
{
  if(starget)
  {
   starget=0;
  }
  return(1);
}

func Select()
{
  CreateMenu(Arrow,Contained(),0,nil,0,3);
  for(next in FindObjects(Find_Or(Find_Category(C4D_Vehicle),Find_OCF(OCF_Collectible),Find_OCF(OCF_Alive)),Find_Exclude(Contained()),Find_Exclude(this()),Find_Distance(20)))
  {
   Contained()->AddMenuItem("%s auswählen","Mark",next->GetID(),0,next);
  }
  return(1);
}

func Mark(trash,ziel)
{
  starget = ziel;
  this->Message("Zielobjekt: %v",this,starget->GetName());
  return(1);
}

func Switch()
{
  SetOwner(Contained()->GetOwner());

  if(on == 0)
  {
   on = 1;
   
   if(upgraded == 1)
   {
    target=CreateObject(LZD1);
    target->SetOwner(GetOwner());
    target.jumper=jumper;
    
    if(!jumpermark)
    {
     target.jumper = nil;
    }
    return(1);
   }
   
   target=CreateObject(LZDS);
   target->SetOwner(GetOwner());
   target.jumper=jumper;
   
   if(!jumpermark)
   {
    target.jumper = nil;
   }
   return(1);
  }
  
  if(on == 1)
  {
   on = 0;
   target->RemoveObject();
   return(1);
  }
}

func Check()
{
  if(starget)
  {
   if(upgraded)
   {
    if(on)
    {
     target.starget = starget;
    }
   }
  }
  
  if(!Contained())
  {
   if(on == 1)
   {
    Switch();
   }
  }

  if(Contained() == GetCursor(GetOwner()))
  {
   return(1);
  }

  if(on == 1)
  {
   Switch();
   return(1);
  }
  return(1);
}

/* Upgrade */

local Name = "$Name$";
local Collectible = 1;
