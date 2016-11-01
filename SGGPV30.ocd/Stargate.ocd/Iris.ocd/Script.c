/*-- Iris --*/

#strict

local open;
local target;
local update;
local temp;

func Initialize()
{
  temp = 0;
  SetAction("Open");
  open = 1;
  return(1);
}

func Update(object gate)
{
	if(target && target->~IsPegasusGate())
	{
		SetGraphics("Atlantis");
		update = 1;
	}
	return 1;
}

func GDOControl(pwget)
{
  var cmp;
  if(cmp = FindObject2(Find_Distance(1000),Find_ID(STWA),Sort_Distance()))
  {
   if(LocalN("password",cmp) eq pwget)
   {
    Switch();
    return(1);
   }
   else
   {
    Message("Falsches Passwort zur öffnung entfangen:|<c 00ff00>%v</c>",target,pwget);
    Sound("Error");
    return(1);
   }
  }
  return(1);
}

func Switch()
{
    var phase = GetPhase();
  if(open)
  {
   if(GetAction() eq "Open")
   {
    open = 0;
    SetAction("Closes");
    if(update)
    {
     SoundStart();
     Sound("iris_atlantis_close");
    }
	else Sound("luke1");
   }
   if(GetAction() eq "Opens")
   {
    open = 0;
    SetAction("Closes");
    if(update)
    {
     SoundStart();
     Sound("iris_atlantis_close");
    }
	else Sound("luke1");
    SetPhase(20-phase);
   }
   if(GetAction() eq "Closes")
   {
    return(1);
   }
   if(GetAction() eq "Close")
   {
    return(1);
   }
  }
  else
  {
   if(GetAction() eq "Open")
   {
    return(1);
   }
   if(GetAction() eq "Opens")
   {
    return(1);
   }
   if(GetAction() eq "Closes")
   {
    open = 1;
    SetAction("Opens");
    if(update)
    {
     SoundStop();
     Sound("iris_atlantis_open");
    }
	else Sound("luke1");
    SetPhase(20 - phase);
   }
   if(GetAction() eq "Close")
   {
    open = 1;
    SetAction("Opens");
    if(update)
    {
     SoundStop();
     Sound("iris_atlantis_open");
    }
	else Sound("luke1");
   }
  }
  return(1);
}
 
func SoundStart()
{
  Sound("iris_atlantis_loop",0,0,50,0,1);
  return(1);
}

func SoundStop()
{
  Sound("iris_atlantis_loop",0,0,50,0,-1);
  return(1);
}

func Check()
{
	if(!target) return RemoveObject();
  if(!update)
  {
   if(temp > 100)
   {
    Break();
   }
  }
  else
  {
   if(temp > 200)
   {
    Break();
   }
  }
  SetPosition(GetX(target)+55,GetY(target)+40);
  if(target->~IsPegasusGate() && !update)
  {
  	Update();
  }
  return(1);
}

func IsClose()
{
  if(open)
  {
   return(0);
  }
  else
  {
   return(1);
  }
}

func Break()
{
  Explode(24);
  return 1;
}
local ActMap = {

Opens = {

Prototype = Action,

Name = "Opens",

Length = 20,

Delay = 2,

Reverse = 1,

X = 0,

Y = 0,

Wdt = 110,

Hgt = 80,

NextAction = "Open",

},

Open = {

Prototype = Action,

Name = "Open",

Length = 1,

Delay = 1,

X = 0,

Y = 0,

Wdt = 110,

Hgt = 80,

NextAction = "Open",

},

Closes = {

Prototype = Action,

Name = "Closes",

Length = 20,

Delay = 2,

X = 0,

Y = 0,

Wdt = 110,

Hgt = 80,

NextAction = "Close",

},

Close = {

Prototype = Action,

Name = "Close",

Length = 1,

Delay = 1,

X = 2090,

Y = 0,

Wdt = 110,

Hgt = 80,

NextAction = "Close",

},  };
local Name = "$Name$";
