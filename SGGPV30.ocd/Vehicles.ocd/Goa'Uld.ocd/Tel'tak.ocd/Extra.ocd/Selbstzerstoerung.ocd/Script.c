#strict

local target;

public func Initialize()
{
  target = FindObject(TEL_,0,0,-1,-1);
  SetAction("Deactive");
  CreateContents(GOCR);
  return(1);
}

public func ControlDigDouble()
{
  if(EMPShocked() == 1)
  {
   Sound("Error");
   return(1);
  }
  
  if(!FindContents(GOCR))
  {
   Sound("Error");
   Message("<c ff0000> Kein Kristall vorhanden!</c>",this());
   return(1);
  }

  CreateMenu(GetID(),Par(),0,0,"Selbstzerstörung");

  if(GetAction() eq "Deactive")
  {
   AddMenuItem("Langsam","Slow",MEPU,Par(),0,Par(0));
   AddMenuItem("Normal","Norm",MEPU,Par(),0,Par(0));
   AddMenuItem("Schnell","Fast",MEPU,Par(),0,Par(0));
  }
  else
  {
   if(FindContents(GOCR))
   {
    AddMenuItem("Selbstzerstörung abschalten","Stop",MEPU,Par(),0,Par(0));
   }
  }
  return(1);
}

public func Stop()
{
  SetAction("Deactive");
  Sound("ring_button2");
  return(1);
}

public func Slow()
{
  if(!(GetAction() eq "Deactive"))
  {
   Sound("Error");
   return(1);
  }

  if(GetAction() eq "Deactive")
  {
   SetAction("Active");
   Sound("ring_button1");
  }
  return(1);
}

public func Norm()
{
  if(!(GetAction() eq "Deactive"))
  {
   Sound("Error");
   return(1);
  }

  if(GetAction() eq "Deactive")
  {
   SetAction("Activen");
   Sound("ring_button1");
   return(1);
  }
}

public func Fast()
{
  if(!(GetAction() eq "Deactive"))
  {
   Sound("Error");
   return(1);
  }

  if(GetAction() eq "Deactive")
  {
   SetAction("Activef");
   Sound("ring_button1");
   return(1);
  }
}

public func Boom()
{
  target->Destroy();
  return(1);
}

public func EMPShock()
{
  EMPShockEffect(1000);
  if(GetAction() eq "Deactive")
  {
   if(Random(4) == 2)
   {
    SetAction("Activen");
    Sound("ring_button1");
   }
  }
  return(1);
}

public func IsMachine() 		{ return(1); }
public func IsBulletTarget()    { return(1); }
public func Teltak()
{
	return(1);
}
local Touchable = 2;
local ActMap = {
Active = {
Prototype = Action,
Name = "Active",
Length = 92,
Delay = 30,
X = 0,
Y = 0,
Wdt = 16,
Hgt = 6,
EndCall = "Boom",
NextAction = "Active",
},
Activen = {
Prototype = Action,
Name = "Activen",
Length = 92,
Delay = 20,
X = 0,
Y = 0,
Wdt = 16,
Hgt = 6,
EndCall = "Boom",
NextAction = "Activen",
},
Activef = {
Prototype = Action,
Name = "Activef",
Length = 92,
Delay = 10,
X = 0,
Y = 0,
Wdt = 16,
Hgt = 6,
EndCall = "Boom",
NextAction = "Activef",
},
Deactive = {
Prototype = Action,
Name = "Deactive",
Length = 1,
Delay = 1,
X = 0,
Y = 0,
Wdt = 16,
Hgt = 6,
NextAction = "Deactive",
},  };
local Name = "Selbstzerstörung";
