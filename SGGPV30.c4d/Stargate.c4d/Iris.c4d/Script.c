/*-- Iris --*/

#strict 2

local target;
local temp;

func Initialize()
{
  temp = 0;
  SetAction("Open");
  return(1);
}

public func IsClose()
{
	return GetAction() != "Open";
}

func GDOControl(pwget)
{
  var cmp;
  if(cmp = FindObject2(Find_Distance(1000),Find_ID(STWA),Sort_Distance()))
  {
   if(cmp->LocalN("password") == pwget)
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

public func Switch()
{
	var phase = GetPhase();
	if(GetAction() == "Open" || GetAction() == "Opens")
	{
		SetAction("Closes");
		DoSound();
	}
	
	else if(GetAction() == "Close" || GetAction() == "Closes")
	{
		SetAction("Opens");
		DoSound();
	}
}

public func SetAction(string szAction)
{
	if((szAction == "Opens" && GetAction() == "Closes") || (szAction == "Closes" && GetAction() == "Opens"))
	{
		var phs = GetPhase();
		_inherited(szAction, ...);
		SetPhase(20 - phs);
	}
	else return _inherited(szAction, ...);
}

public func DoSound()
{
	Sound("luke1");
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
  
  if(temp > 200) Break();
  
  SetPosition(GetX(target)+55,GetY(target)+40);
  return(1);
}

func Break()
{
  Explode(24);
  return 1;
}
