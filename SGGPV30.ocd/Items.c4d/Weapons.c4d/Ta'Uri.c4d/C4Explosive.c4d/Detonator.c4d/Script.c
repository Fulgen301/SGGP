#strict
#include GEAR
local User,targets,Follow,pTarg;
func Initialize()
{
}

func ActivateMe(object pCaller)
{
	User = pCaller;
	SetOwner(GetOwner(User));
	CreateMenu(C4ZU, User, 0, 0, "C4",0,1);
	targets = FindObjects(Find_ID(C4EP),Find_Owner(GetOwner()),Find_Func("IsActiv"));
	Follow = 1;
	pTarg = 0;
	var targ;
	AddMenuItem("Alle bedienen", Format("Choosen(%d)",-1),  C4EP,User);
	for(targ in targets)
	{
		 AddMenuItem("C4", Format("Choosen(%d)",ObjectNumber(targ)),  C4EP,User);
	}
}


func Sight()
{
	if(GetCursor(GetOwner(User)) == User)
		if(Follow)
		{
			if(!targets) return();
				var Targ;
				if(!pTarg) 
				{
					Targ = targets[GetMenuSelection(User) - 1];
					if(!Targ) return();
				}
				else
				{
					Targ = pTarg;
				}
				SetPlrView(GetOwner(User),Targ);
				SetPlrViewRange(30,User);
				if(GetAction(Targ) ne "Time1" && GetAction(Targ) ne "Time2" && GetAction(Targ) ne "WandTime1" && GetAction(Targ) ne "WandTime2" ) Targ -> SetAction(Format("%sFlash",LocalN("Wand",Targ)));
		}
	return();
}

func MenuQueryCancel()
{
	Follow = 0;
	SetPlrViewRange(500,User);
}

func Choosen(int iC4)
{
	Sound("DetonatorCharge");
	var pC4;
	pC4 = Object(iC4);
	Follow = 1;
	pTarg = pC4;
	CreateMenu(C4ZU, User, 0, 0, "C4",0,1);
		if(LocalN("Time",pC4) > 0) AddMenuItem("Entschärfen", Format("Disable(%d)",ObjectNumber(pC4)),  C4EP,User);
		AddMenuItem("Zeitzünder", Format("Enable(%d)",iC4),  C4EP,User);
		AddMenuItem("Hochjagen", Format("Bumm(%d)",iC4),  C4EP,User);
}

func Disable(int iC4)
{
	Sound("DetonatorCharge");
	Follow = 0;
	SetPlrViewRange(500,User);
	if(iC4 == -1)
	{
		var targ;
		for(targ in targets)
		{
			targ -> Disable();
		}
		return();
	}	
	var pC4;
	pC4 = Object(iC4);	
	pC4 -> Disable();
}

func Bumm(int iC4)
{
	Sound("DetonatorCharge");
	Follow = 0;
	if(User)
	{
	 SetPlrViewRange(500,User);
	}
	if(iC4 == -1)
	{
		var targ;
		for(targ in targets)
		{
			if(targ)
				targ -> Bumm(10);
		}
		return();	
	}
	var pC4;
	pC4 = Object(iC4);
	pC4 -> Bumm(20);
}

func Enable(int iC4)
{
	var pC4;
	pC4 = Object(iC4);
	Follow = 1;
	pTarg = pC4;
	Sound("DetonatorCharge");
	CreateMenu(C4ZU, User, 0, 0, "C4",0,1);
		AddMenuItem("5 Sekunden", Format("Start(%d,%d)",iC4,5),C4EP,User);
		AddMenuItem("10 Sekunden", Format("Start(%d,%d)",iC4,10),C4EP,User);
		AddMenuItem("15 Sekunden", Format("Start(%d,%d)",iC4,15),C4EP,User);
		AddMenuItem("20 Sekunden", Format("Start(%d,%d)",iC4,20),C4EP,User);
		AddMenuItem("30 Sekunden", Format("Start(%d,%d)",iC4,30),C4EP,User);
		AddMenuItem("45 Sekunden", Format("Start(%d,%d)",iC4,45),C4EP,User);
		AddMenuItem("60 Sekunden", Format("Start(%d,%d)",iC4,60),C4EP,User);
		AddMenuItem("90 Sekunden", Format("Start(%d,%d)",iC4,90),C4EP,User);
}

func Start(int iC4,int iSec)
{
	Sound("DetonatorCharge");
	Follow = 0;
	SetPlrViewRange(500,User);
	if(iC4 == -1)
	{
		var targ;
		for(targ in targets)
		{
			targ -> TimeBlast(iSec);
		}
		return();
	}	
	var pC4;
	pC4 = Object(iC4);
	pC4 -> TimeBlast(iSec);
}
func GetGearType()	
{ 
	return(GEAR_Light); 
}

func IsEquipment()	
{ 
	return(true); 
}

public func ConDesc() 
{
	return("Zünder bedienen");
}

public func ConUseable() 
{
    return(true);
}

public func ConUse(object pCaller)
{
	ActivateMe(pCaller);
	Sound("Click");
}

public func GetRace()	{ return SG1_StargateCenter; }