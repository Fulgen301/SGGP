
local isOn,Dir,Speed,pOther,pOtherRight;
func Initialize()
{
	Adjust();
	Speed = 25;
	Dir = -1;
	SetAction("Stand");
	isOn = 0;
}

func Timer()
{
	if(isOn)
	{
		if(HasEnrg())
		{
			if(Dir == -1) if(GetAction() ne "MoveLeft") SetAction("MoveLeft");
			if(Dir == 1) if(GetAction() ne "MoveRight") SetAction("MoveRight");
			var pObj;
			for(pObj in FindObjects(Find_InRect(-44,-15,87,6),Find_Category(C4D_Object)))
			{
				if(GetYDir(pObj) > 3) 
				{
					SetYDir(3,pObj);
					SetXDir(0,pObj);
				}
			}
			for(pObj in FindObjects(Find_InRect(-44,-10,87,5),Find_Category(C4D_Object)))
			{
				SetYDir(-2,pObj);
				SetXDir(Speed * Dir,pObj);
			}
		}
		else
		{
			isOn = 0;
			SetAction("Stand");
		}
	}
	if(!HasEnrg())
	{
		isOn = 0;
		SetAction("Stand");
	}
}

func ControlDigDouble(object pUser)
{
	Info();
	CreateMenu(GetID(this()), pUser, 0,0, "Förderband", 0, 1,1);
	AddMenuItem("Schneller", "SpeedUp",MEPU,pUser);
	AddMenuItem("Langsamer", "SpeedDown",MEPU,pUser);
	AddMenuItem("Links", "ControlLeft",MEPU,pUser);
	AddMenuItem("Rechts", "ControlRight",MEPU,pUser);
	AddMenuItem("An/Aus", "OnOff",MEPU,pUser);
	AddMenuItem("Ausrichten", "Adjust",MEPU,pUser);
	AddMenuItem("Zusammenbauen", "BuildDown",MEPU,pUser);
}

func ControlLeft()
{
	Dir = -1;
	SetAction("MoveLeft");
	Info();
}

func ControlRight()
{
	Dir = 1;
	SetAction("MoveRight");
	Info();
}

func ControlThrow()
{
	OnOff();
}

func BuildDown()
{
	CreateObject(CNKT);
	RemoveObject();
}

func SpeedUp()
{
	Speed += 2;
	if(Speed > 50)
	{
		Speed = 50;
	}
	Info();
}

func SpeedDown()
{
	Speed -= 2;
	if(Speed < 2)
	{
		Speed = 2;
	}
	Info();
}

func OnOff()
{
	if(HasEnrg())
	{
		if(isOn)
		{
			isOn = 0;
		} 
		else
		{
			isOn = 1;
		}
	}
	else
	{
		isOn = 0;
	}
	Info();
}

func Adjust()
{
	pOther = FindObject2(Sort_Distance(),Find_ID(TALA),Find_InRect(-135,-7,135,14),Find_Exclude(this()));
	pOtherRight = FindObject2(Sort_Distance(),Find_ID(TALA),Find_InRect(0,-7,135,14),Find_Exclude(this()));
	if(pOther)
	{
		SetPosition(GetX(pOther)+87,GetY(pOther));
		var pLine;
		pLine = CreateObject(LNKT);
		pLine -> Activate();
		SetPosition(GetX(pOther),GetY(pOther),pLine);
		pLine -> Activate();
	}
	else
	{
		if(pOtherRight)
		{
			SetPosition(GetX(pOtherRight)-87,GetY(pOtherRight));
			var pLine;
			pLine = CreateObject(LNKT);
			pLine -> Activate();
			SetPosition(GetX(pOtherRight),GetY(pOtherRight),pLine);
			pLine -> Activate();
		}
	}
}

func HasEnrg(object pExclude)
{
	
	if(EnergyCheck(Speed*2))
	{
		return(1);
	}
	return(0);
}


func Info()
{
	var Direc;
	var Stat;
	if(Dir == -1) Direc = "Links";
	if(Dir == 1) Direc = "Rechts";
	if(isOn) Stat = "<c 00ff00>An</c>";
	if(!isOn) Stat = "<c ff0000>Aus</c>";
	Message("Geschwindigkeit:<c %x>%d%</c>|Richtung: <c ffcc00>%s</c>|Status:%s",this(),RGB(200-Speed*4,Speed*4,0),Speed*2,Direc,Stat);
}
	
local Touchable = 2;
local ActMap = {
MoveLeft = {
Prototype = Action,
Name = "MoveLeft",
Delay = 1,
Length = 11,
X = 0,
Y = 0,
Wdt = 100,
Hgt = 15,
NextAction = "MoveLeft",
},
Stand = {
Prototype = Action,
Name = "Stand",
Delay = 1,
Length = 1,
X = 0,
Y = 0,
Wdt = 100,
Hgt = 15,
NextAction = "Hold",
},
MoveRight = {
Prototype = Action,
Name = "MoveRight",
Delay = 1,
Length = 11,
Reverse = 1,
X = 0,
Y = 0,
Wdt = 100,
Hgt = 15,
NextAction = "MoveRight",
},  };
local Name = "$Name$";
