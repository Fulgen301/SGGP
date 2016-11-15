 
local HasZPM,Activ,Info,User,En,Damg;
func Initialize()
{
	HasZPM = "No";
	SetAction("Stand");
}

func Damage(int iDamage)
{
	Damg += iDamage;
	if(Damg > 200)
	{
		Exit(FindContents(ZPM_));
		Explode(50);
	}
}
func ControlDigDouble(object pUser)
{
	if(GetAction() ne Format("StandOpen%s",HasZPM)) 
	User = pUser;
	CreateMenu(ZPST, User, 0, 0, "ZPM-Schnittstelle",0,1);
	if(HasZPM ne "No") AddMenuItem("ZPM herausnehmen", "Take",  MEPU,User);
	if(HasZPM eq "No" && FindContents(ZPM_,pUser)) AddMenuItem("ZPM hineinlegen", "Give",  MEPU,User);
	if(!Activ && HasZPM eq "ZPM") AddMenuItem("Aktivieren", "Active",  MEPU,User);
	if(Activ) AddMenuItem("Deaktivieren", "Deactive",  MEPU,User);
	if(!Info) AddMenuItem("Info an", "InfoOn",  MEPU,User);
	if(Info) AddMenuItem("Info aus", "InfoOff",  MEPU,User);
	if(GetAction() eq "Stand" || GetAction() eq Format("Close%s",HasZPM)) AddMenuItem("Ausfahren", "FahrAus",  MEPU,User);
	if(GetAction() eq Format("StandOpen%s",HasZPM) || GetAction() eq Format("Open%s",HasZPM)) AddMenuItem("Einfahren", "Fahr",  MEPU,User);
}

func ControlThrow(object pUser)
{
	ControlDigDouble(pUser);
}

func Timer()
{
	var ZPM;
	ZPM = FindContents(ZPM_);
	if(ZPM) if(ZPM-> Depledet()) HasZPM = "ZPMEmpty";
	if(Info)
	{
		if(HasZPM eq "ZPM") 
		{
			if(Activ) Message("<c %x>%d%</c>|<c 00ff00>Aktiv</c>",this(),RGB(200-ZPM -> Energ() * 2,ZPM -> Energ() * 2,0),ZPM-> Energ());
			if(!Activ) Message("<c %x>%d%</c>|<c ff0000>Inaktiv</c>",this(),RGB(200-ZPM -> Energ() * 2,ZPM -> Energ() * 2,0),ZPM-> Energ());
		}
		if(HasZPM eq "No") Message("<c 000000>Kein ZPM</c>",this());
		if(HasZPM eq "ZPMEmpty") Message("<c 000000>ZPM verbraucht</c>",this());
	}
	if(HasZPM ne "ZPM") return(0);
	if(!Activ) return(0);
	if(CheckEnergyNeedChain() || GetEnergy() < 50)
	{
		En++;
		while(En > 40)
		{
			En-= 40;
			ZPM->Minus();
		}
		DoEnergy(+1500);
	}
}

func InfoOff()
{
	Info = 0;
	ControlDigDouble(User);
}

func InfoOn()
{
	Info = 1;
	ControlDigDouble(User);
}

func Deactive()
{
	Activ = 0;
	ControlDigDouble(User);
}

func Active()
{
	Activ = 1;
	ControlDigDouble(User);
}

func Give()
{
	var ZPM;
	ZPM = FindContents(ZPM_,User); 
	Exit(ZPM);
	this->Enter(ZPM);
	HasZPM = "ZPM";
	if(ZPM -> Depledet()) HasZPM = "ZPMEmpty";
	SetAction(Format("StandOpen%s",HasZPM));
	ControlDigDouble(User);
}

func Fahr()
{
	Sound("ZPMFahr");
	SetAction(Format("Close%s",HasZPM));
	ControlDigDouble(User);
}

func FahrM()
{
	Sound("ZPMFahr");
	if(GetAction() eq Format("StandOpen%s",HasZPM)) SetAction(Format("Close%s",HasZPM));
}

func FahrAus()
{
	Sound("ZPMFahr");
	SetAction(Format("Open%s",HasZPM));
	ControlDigDouble(User);
}
	
func Take()
{
	HasZPM = "No";
	SetAction(Format("StandOpen%s",HasZPM));
	Exit(FindContents(ZPM_));
	ControlDigDouble(User);
}

func MenuQueryCancel()
{
	ClearScheduleCall(this(),"Fahr");
	ScheduleCall(this(),"FahrM",100);
}

func IsAntiker()
{
	return(1);
}
local Touchable = 2;
local ActMap = {
Stand = {
Prototype = Action,
Name = "Stand",
Length = 1,
Delay = 5,
X = 48,
Y = 0,
Wdt = 16,
Hgt = 23,
NextAction = "Stand",
},
OpenZPM = {
Prototype = Action,
Name = "OpenZPM",
Length = 4,
Delay = 1,
Reverse = 1,
X = 0,
Y = 23,
Wdt = 16,
Hgt = 23,
NextAction = "StandOpenZPM",
},
CloseZPM = {
Prototype = Action,
Name = "CloseZPM",
Length = 4,
Delay = 1,
X = 0,
Y = 23,
Wdt = 16,
Hgt = 23,
NextAction = "Stand",
},
StandOpenZPM = {
Prototype = Action,
Name = "StandOpenZPM",
Length = 1,
Delay = 1,
X = 0,
Y = 23,
Wdt = 16,
Hgt = 23,
NextAction = "StandOpenZPM",
},
OpenZPMEmpty = {
Prototype = Action,
Name = "OpenZPMEmpty",
Length = 4,
Delay = 1,
Reverse = 1,
X = 0,
Y = 46,
Wdt = 16,
Hgt = 23,
NextAction = "StandOpenZPMEmpty",
},
CloseZPMEmpty = {
Prototype = Action,
Name = "CloseZPMEmpty",
Length = 4,
Delay = 1,
X = 0,
Y = 46,
Wdt = 16,
Hgt = 23,
NextAction = "Stand",
},
StandOpenZPMEmpty = {
Prototype = Action,
Name = "StandOpenZPMEmpty",
Length = 1,
Delay = 1,
X = 0,
Y = 46,
Wdt = 16,
Hgt = 23,
NextAction = "StandOpenZPMEmpty",
},
OpenNo = {
Prototype = Action,
Name = "OpenNo",
Length = 4,
Reverse = 1,
Delay = 1,
X = 0,
Y = 0,
Wdt = 16,
Hgt = 23,
NextAction = "StandOpenNo",
},
CloseNo = {
Prototype = Action,
Name = "CloseNo",
Length = 4,
Delay = 1,
X = 0,
Y = 0,
Wdt = 16,
Hgt = 23,
NextAction = "Stand",
},
StandOpenNo = {
Prototype = Action,
Name = "StandOpenNo",
Length = 1,
Delay = 1,
X = 0,
Y = 0,
Wdt = 16,
Hgt = 23,
NextAction = "StandOpenNo",
},  };
local Name = "$Name$";
