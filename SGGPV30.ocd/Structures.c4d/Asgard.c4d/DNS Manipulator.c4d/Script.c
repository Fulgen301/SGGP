#strict
local pClonk,User,Kern;
func Initialize()
{	
	SetAction("Stand");
	SetSolidMask(0,40,30,40);
	SetPosition(GetX(this()),GetY(this())+10);
}

func IsAsgard()
{
	return true;
}

func SolidMaskClose()
{
	SetSolidMask(40+40*GetPhase(),80,30,40);
}

func SolidMaskOpen()
{
	SetSolidMask(640-(40*GetPhase()),80,30,40);
}

func ControlDigDouble(object pUser,pKern)
{	
	User = pUser;
	Kern = pKern;
	CreateMenu(GetID(this()), pUser, 0,0, "Asgard Materie Konverter", 0, 1);
	if(GetAction() eq "Closed") AddMenuItem("Öffnen", "Open",MEPU,pUser);
	if(GetAction() eq "Stand")AddMenuItem("Schliessen", "Close",MEPU,pUser);
	if(GetAction() eq "Stand")AddMenuItem("Aktivieren", "Activate",MEPU,pUser);
	if(GetAction() eq "Started")AddMenuItem("Herunterfahren", "Deactivate",MEPU,pUser);
	if(GetAction() eq "Started")AddMenuItem("Innere Organe manipulieren", "ManipulateLives",MEPU,pUser,0,0,"Manipuliert:|Atem und Lebensenergie");
	if(GetAction() eq "Started")AddMenuItem("Muskulatur manipulieren", "ManipulateWalks",MEPU,pUser,0,0,"Manipuliert:|Laufen, klettern und hangeln");
	if(GetAction() eq "Started")AddMenuItem("Koordination manipulieren", "ManipulateHands",MEPU,pUser,0,0,"Manipuliert:|Werfen, kämpfen und stossen");
	if(GetAction() eq "Started")AddMenuItem("Beweglichkeit manipulieren", "ManipulateBody",MEPU,pUser,0,0,"Manipuliert:|Springen, graben und schwimmen");
	if(GetAction() eq "Started")AddMenuItem("Ursprüngliche DNS wiederherstellen", "Normalize",MEPU,pUser);
}

func MenuQueryCancel()
{
	Kern -> ControlDigDouble(User);
}

func Open()
{
	SetSolidMask(0,40,30,40);
	SetAction("Open");
}

func Timer()
{
	if(GetAction() eq "Stand")
	if(!pClonk)
	{
		pClonk = FindObject2(Find_OCF(OCF_Alive),Find_InRect(-13,-10,26,20));
	}
}

func Normalize()
{
	pClonk -> SetPhysical("Breath",GetPhysical("Breath", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	pClonk -> SetPhysical("Walk",GetPhysical("Walk", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	pClonk -> SetPhysical("Jump",GetPhysical("Jump", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	pClonk -> SetPhysical("Scale",GetPhysical("Scale", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	pClonk -> SetPhysical("Hangle",GetPhysical("Hangle", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	pClonk -> SetPhysical("Dig",GetPhysical("Dig", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	pClonk -> SetPhysical("Swim",GetPhysical("Swim", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	pClonk -> SetPhysical("Throw",GetPhysical("Throw", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	pClonk -> SetPhysical("Push",GetPhysical("Push", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	pClonk -> SetPhysical("Fight",GetPhysical("Fight", PHYS_Current,0,GetID(pClonk))-EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)), PHYS_Current,pClonk);
	ControlDigDouble(User);
	if(GetEffect("DNSManipulate",pClonk)) RemoveEffect("DNSManipulate",pClonk);
	if(GetEffect("DNSManipulateLive",pClonk)) RemoveEffect("DNSManipulateLive",pClonk);
}

func Close()
{
	SetAction("Close");
}


func Activate()
{
	SetAction("Start");
	SetSolidMask(30,40,30,40);
}

func Deactivate()
{
	SetAction("End");
}

func Opened()
{
	SetSolidMask(0,40,30,40);
}

func Ended()
{
	SetSolidMask(0,40,30,40);
}
	
func ManipulateLives()
{
	pClonk -> SetPhysical("Energy",100000, PHYS_Current,pClonk);
	pClonk -> SetPhysical("Breath",700000, PHYS_Current,pClonk);
   	AddEffect("DNSManipulate",pClonk, 3,30, pClonk);
   	AddEffect("DNSManipulateLive",pClonk, 3,610, pClonk);
   	if(!GetEffect("StoreManipulates",pClonk))
   	{
   		AddEffect("StoreManipulates",pClonk, 3,0, pClonk);
   	}
   	EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)) += 5000;
   	pClonk = 0;
	ControlDigDouble(User);
}

func ManipulateWalks()
{
	pClonk -> SetPhysical("Walk",100000, PHYS_Current,pClonk);
	pClonk -> SetPhysical("Scale",100000, PHYS_Current,pClonk);
	pClonk -> SetPhysical("Hangle",100000, PHYS_Current,pClonk);
   	AddEffect("DNSManipulate",pClonk, 3,30, pClonk);
   	AddEffect("DNSManipulateLive",pClonk, 3,610, pClonk);
   	if(!GetEffect("StoreManipulates",pClonk))
   	{
   		AddEffect("StoreManipulates",pClonk, 3,0, pClonk);
   	}
   	EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)) += 5000;
	ControlDigDouble(User);
}

func ManipulateHands()
{
	pClonk -> SetPhysical("Throw",100000, PHYS_Current,pClonk);
	pClonk -> SetPhysical("Push",100000, PHYS_Current,pClonk);
	pClonk -> SetPhysical("Fight",100000, PHYS_Current,pClonk);
   	AddEffect("DNSManipulate",pClonk, 3,30, pClonk);
   	AddEffect("DNSManipulateLive",pClonk, 3,610, pClonk);
   	if(!GetEffect("StoreManipulates",pClonk))
   	{
   		AddEffect("StoreManipulates",pClonk, 3,0, pClonk);
   	}
   	EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)) += 5000;
	ControlDigDouble(User);
}

func ManipulateBody()
{
	pClonk -> SetPhysical("Jump",40000, PHYS_Current,pClonk);
	pClonk -> SetPhysical("Dig",100000, PHYS_Current,pClonk);
	pClonk -> SetPhysical("Swim",100000, PHYS_Current,pClonk);
   	AddEffect("DNSManipulate",pClonk, 3,30, pClonk);
   	AddEffect("DNSManipulateLive",pClonk, 3,610, pClonk);
   	if(!GetEffect("StoreManipulates",pClonk))
   	{
   		AddEffect("StoreManipulates",pClonk, 3,0, pClonk);
   	}
   	EffectVar(4,pClonk,GetEffect("StoreManipulates",pClonk)) += 3000;
	ControlDigDouble(User);
}

global func FxDNSManipulateTimer(object pTarget)
{
	if(GetPhysical("Breath", PHYS_Current,pTarget) > 10) pTarget -> SetPhysical("Breath",GetPhysical("Breath", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	if(GetPhysical("Walk", PHYS_Current,pTarget) > 1000) pTarget -> SetPhysical("Walk",GetPhysical("Walk", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	if(GetPhysical("Jump", PHYS_Current,pTarget) > 10) pTarget -> SetPhysical("Jump",GetPhysical("Jump", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	if(GetPhysical("Scale", PHYS_Current,pTarget) > 100) pTarget -> SetPhysical("Scale",GetPhysical("Scale", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	if(GetPhysical("Hangle", PHYS_Current,pTarget) > 100) pTarget -> SetPhysical("Hangle",GetPhysical("Hangle", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	if(GetPhysical("Dig", PHYS_Current,pTarget) > 10) pTarget -> SetPhysical("Dig",GetPhysical("Dig", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	if(GetPhysical("Swim", PHYS_Current,pTarget) > 50) pTarget -> SetPhysical("Swim",GetPhysical("Swim", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	if(GetPhysical("Throw", PHYS_Current,pTarget) > 10) pTarget -> SetPhysical("Throw",GetPhysical("Throw", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	if(GetPhysical("Push", PHYS_Current,pTarget) > 10) pTarget -> SetPhysical("Push",GetPhysical("Push", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	if(GetPhysical("Fight", PHYS_Current,pTarget) > 10) pTarget -> SetPhysical("Fight",GetPhysical("Fight", PHYS_Current,pTarget)-10, PHYS_Current,pTarget);
	return(1);
}

global func FxDNSManipulateLiveTimer(object pTarget)
{
	DoEnergy(-1,pTarget);
	return(1);
}
