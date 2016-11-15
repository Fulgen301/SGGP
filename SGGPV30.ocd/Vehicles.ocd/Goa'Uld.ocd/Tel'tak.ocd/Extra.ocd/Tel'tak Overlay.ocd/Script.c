/*--- Tel'tak ---*/


local target;

public func Initialize()
{
  target = FindObject(TEL_,0,0,-1,-1);
  SetAction("Wait");
  return(1);
}

public func Time()
 {
  SetPosition(GetX(target),GetY(target));

  if(GetDir(target) == 0)
  {
   SetDir(DIR_Left());
  }

  if(GetDir(target) == 1)
  {
   SetDir(DIR_Right());
  }


if(FindObject(0,-150,-75,300,150,OCF_Alive()))
{
  if(GetX(GetCursor(0))-GetX(this()) < 150)
  {
   if(GetX(GetCursor(0))-GetX(this()) > -150)
   {
    if(GetY(GetCursor(0))-GetY(this()) < 75)
    {
     if(GetY(GetCursor(0))-GetY(this()) > -75)
     {
      SetVisibility(VIS_None());
      return(1);
     }
    }
   }
  }

  if(GetX(GetCursor(1))-GetX(this()) < 150)
  {
   if(GetX(GetCursor(1))-GetX(this()) > -150)
   {
    if(GetY(GetCursor(1))-GetY(this()) < 75)
    {
     if(GetY(GetCursor(1))-GetY(this()) > -75)
     {
      SetVisibility(VIS_None());
      return(1);
     }
    }
   }
  }

  if(GetX(GetCursor(2))-GetX(this()) < 150)
  {
   if(GetX(GetCursor(2))-GetX(this()) > -150)
   {
    if(GetY(GetCursor(2))-GetY(this()) < 75)
    {
     if(GetY(GetCursor(2))-GetY(this()) > -75)
     {
      SetVisibility(VIS_None());
      return(1);
     }
    }
   }
  }

  if(GetX(GetCursor(3))-GetX(this()) < 150)
  {
   if(GetX(GetCursor(3))-GetX(this()) > -150)
   {
    if(GetY(GetCursor(3))-GetY(this()) < 75)
    {
     if(GetY(GetCursor(3))-GetY(this()) > -75)
     {
      SetVisibility(VIS_None());
      return(1);
     }
    }
   }
  }

}
  SetVisibility(VIS_All());
  return(1);


 }
 
 public func Teltak()
{
	return(1);
}
local ActMap = {
Wait = {
Prototype = Action,
Name = "Wait",
Procedure = DFA_NONE,
Directions = 2,
Length = 1,
Delay = 1,
FlipDir = 1,
X = 0,
Y = 0,
Wdt = 150,
Hgt = 300,
FacetTopFace = 1,
NextAction = "Wait",
},  };
local Name = "$Name$";
