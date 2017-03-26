#strict

local User, Keks, HasEnrg, InfoOn, menu, on;

protected func Construction()
{
	AddEffect("IntTimer", this, 1, 1, this);
}
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
  for(obj in FindObjects(/*Find_Or(*/Find_Func("IsAsgard")/*,Find_Func("IsAntiker"))*/,Find_Distance(400),Find_Or(Find_Owner(GetOwner()),Find_Owner(-1))))
  {
	  AddMenuItem(Format("%s bedienen", GetName(obj)), "Control", GetID(obj), pUser, 0, obj);
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

func FxIntTimerTimer()
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

public func GetRace() { return SG1_Asgard; }
