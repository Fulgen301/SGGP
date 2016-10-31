#strict
local Gate,ARWd,iDamg,pOther,iDelay;
func Initialize()
{
	SetAction("NoARW");
}

func SetGate(object pGate)
{
	Gate = pGate;
}	

func KilledByARW()
{
	CastReplis(20,1);
	RemoveObject();
}

func IsRepli()
{
	return(true);
}
func Timer()
{
	if(!Gate) RemoveObject();
	if(FindObject2(Find_ID(REAT),Find_OCF(OCF_Fullcon),Find_Exclude(this()))) RemoveObject();
	if(GetCon() < 100) 
	{
		DoCon(1);
		return(0);
	}
	SetPosition(GetX(Gate)+39,GetY(Gate)+2);
	if(!ARWd) return();
	if(Gate->GetState() == 3) return(0);
	if(Gate->GetState() == 2 || Gate->GetState() == 1)
	{
		var pBeam;
		pBeam =FindObject2(Find_OCF(OCF_Collectible),Find_NoContainer(),Find_Not(Find_ID(REWU),Find_ID(ARW_),Find_Func("IsEquipment")),Find_Not(Find_And(Find_ID(FLAG),Find_Action("FlyBase"))),Find_Distance(RepliView/3,GetX(LocalN("pTo",Gate))-GetX(),GetY(LocalN("pTo",Gate))-GetY()),Sort_Distance());
		//if(!pBeam) Gate -> DeactivateCall();
		if(pBeam) DrawParticleLine("PSpark",GetX(pBeam)-GetX(),GetY(pBeam)-GetY(),GetX(pOther)-GetX()+37,GetY(pOther)-GetY()+40, 4,20, RGB(128,0,255), RGB(0,0,255));
		if(pBeam) 
		{
			SetPosition(GetX()+37,GetY()+40,pBeam);
			Fling(pBeam,-5,-5);
		}
		return(0);
	}
	iDelay++;
	if(iDelay > 1500)
	{
		iDelay = 0;
		var pTo;
		for(pTo in FindObjects(Find_Func("IsStargate"),Find_Not(Find_Func("Testi")),Find_Func("GetName"),Find_Exclude(Gate)))
		{
			var szName;
			szName = pTo -> GetName(pTo);
			if(ObjectCount2(Find_OCF(OCF_Collectible),Find_NoContainer(),Find_Not(Find_ID(REWU),Find_ID(ARW_),Find_Func("IsEquipment")),Find_Not(Find_And(Find_ID(FLAG),Find_Action("FlyBase"))),Find_Distance(RepliView,GetX(pTo)-GetX(),GetY(pTo)-GetY())))
			{
				Gate->Dial(szName);
				pOther = pTo;
			}
		}
	}
}

func HasARW()
{
	if(ARWd) return(true);
	if(!ARWd) return(false);
}

func MachARW()
{
	SetAction("ARW");
	ARWd=1;
}

func Damage(int iLevel)
{
	if(iDamg > 100) 
	{
		if(GetCon() == 100) CastReplis(20);
		RemoveObject();
	}
	iDamg += iLevel;
}

func KilledByARW()
{
	CastReplis(20,1);
	RemoveObject();
}

func IsBulletTarget() 
{ 
	return(true); 
}

func FindObj()
{
	return();
}
local ActMap = {
NoARW = {
Prototype = Action,
Name = "NoARW",
Length = 1,
Delay = 1,
X = 0,
Y = 0,
Wdt = 75,
Hgt = 80,
NextAction = "Hold",
},
ARW = {
Prototype = Action,
Name = "ARW",
Length = 1,
Delay = 1,
X = 75,
Y = 0,
Wdt = 75,
Hgt = 80,
NextAction = "Hold",
},  };
local Name = "$Name$";
