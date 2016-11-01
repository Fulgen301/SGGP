#strict

local User, Keks, HasEnrg, InfoOn, menu, on;

func Initialize()
{
	menu = [];
  SetAction("Aus");
}

func Damage()
{
  if(GetDamage() > 200)
  {
   Explode(35);
  }
  return(1);
}

func ControlDigDouble(pUser)
{
	User = pUser;
  SetAction("An");
  CreateMenu(GetID(this()), pUser, 0,0, "Asgard Kern", 0, 1);
  AddMenuItem("Info An/Aus","Info",MEPU,pUser);
  var obj;	   	
  for(obj in FindObjects(Find_Or(Find_Func("IsAsgard"),Find_Func("IsAntiker")),Find_Distance(400),Find_Or(Find_Owner(GetOwner()),Find_Owner(-1))))
  {
	  AddMenuItem(Format("%s bedienen", GetName(obj)), "Control", GetID(obj), pUser, 0, obj);
  }
  
  if(FindObjectOwner(ALSK,GetOwner()))
  {
  	AddMenuItem("Sternenantrieb bedienen", "Control", ALSD, pUser, 0, FindObjectOwner(ALSK,GetOwner()));
  }

  if (!on)
  {
	  AddMenuItem("Notstromversorgung aktivieren", "ActivateEmergency", MEPU, pUser);
  }
  else
  {
	  AddMenuItem("Notstromversorgung deaktivieren", "DeactivateEmergency", MEPU, pUser);
  }
  
  return(1);
}

func MenuQueryCancel()
{
  SetAction("Aus");
}

func Control(Trash,Obj)
{
	SetAction("Aus");
	if(HasEnrg >= 1000) 
	{ 
		Keks = Obj;
		if(Obj) Obj -> ControlDigDouble(User,this());
		else
		Message("Verbindung wurde unterbrochen",this());
		HasEnrg -= 1000;
	}
	else
	{
		Message("<c ff0000>Nicht genügend Energie </c>",this());
	}
}

func Timer()
{
	if(FindObject(ENRG))
	{
		if(HasEnrg < 10000)
		{
			if(EnergyCheck(100))
			{
				HasEnrg += 100;
			}
		}
	}
	else
	{
		if(HasEnrg < 10000)
		{
			if(FindContents(ENAP))
			{
				HasEnrg += 2000;
			}
		}
	}
	var EnrgProz;
	EnrgProz = HasEnrg / 100;
	if(InfoOn) Message("<c %x>%d%</c>",this(),RGB(200 - EnrgProz *2,EnrgProz *2),EnrgProz);
	CallEmergencyObject();
}

func Info()
{
	if(InfoOn)
	{
		InfoOn = 0;
		Message(" ",this());
	}
	else
	{
		InfoOn = 1;
	}
}

func ControlThrow(pUser)
{
	if(!FindObject(ENRG)) if(FindContents(ENAP,pUser)) FindContents(ENAP,pUser) -> Enter(this());
}

func ActivateEmergency()
{
	on = 1;
	CallEmergencyObject();
}

func DeactivateEmergency()
{
	on = 0;
	return(1);
}

func CallEmergencyObject()
{
	if (on)
	{
		if (LocalN("energy", FindObject2(Find_ID(GOSG), Find_Distance(1000))) < 20)
		{
			for (obj in FindObjects(Find_ID(TANG), Find_Distance(1000), Find_Or(Find_Action("Zu"),Find_Action("Aus"))))
			{
				obj->~ControlDigDouble();
			}
			
			for (obj in FindObjects(Find_ID(WRNR), Find_Distance(1000), Find_Or(Find_Action("Closes"), Find_Action("Close"))))
			{
				obj->~ControlDigDouble();
			}
			return(1);
		}
	}
	return(1);
}
local Touchable = 2;
local ActMap = {
Aus = {
Prototype = Action,
Name = "Aus",
Length = 1,
Delay = 1,
X = 0,
Y = 0,
Wdt = 60,
Hgt = 50,
NextAction = "Hold",
},
An = {
Prototype = Action,
Name = "An",
Length = 1,
Delay = 1,
X = 60,
Y = 0,
Wdt = 60,
Hgt = 50,
NextAction = "Hold",
},  };
local Name = "$Name$";
