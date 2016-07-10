#strict
local User,iUser,X,Y,Number,Incom,Next,nX,nY,ChangePW,Password,iWdt,Enr,Damg,Proz,Brauch,HasGot;
local Dis;
func Initialize() 
{
	var i;
	i = LandscapeWidth() + LandscapeHeight();
	i /= 2;
	i /= 100;
	Proz = i;
	if(LandscapeWidth() > LandscapeHeight())
	{
		iWdt = LandscapeWidth() * 2;
	}
	else
	{
		iWdt = LandscapeHeight() * 2;
	}
	var pObj;
	for(pObj in FindObjects(Find_InRect(0,9,150,15)))
	{
		SetPosition(GetX(pObj),GetY(),pObj);
	}
	SetAction("Stand");
	return(1);
}

func Damage(int iDamage)
{
	Damg += iDamage;
	if(Damg > 200)
	{
		Explode(200);
	}
}

func Energ()
{
	if(Brauch)
	{
		if(FindObject(ENRG))
		{
			if(EnergyCheck(10000) && Enr < Brauch)
			{
				DoEnergy(-1);
				Enr += 10000;
			}
		}
		else
		{
			if(Enr < Brauch)
			{
				Enr += 500;
			}
			else
			{
				Message("<c ff0000>Lade Energie</c>",this());
			}
		}
	}
	if(HasGot == 1 && Enr >= Brauch )
	{
		SetAction("Activate");
		var pObj;
		var XOff;
		var YOff;
		for(pObj in FindObjects(Find_InRect(-42,-25,79,34),Find_Not(Find_ID(CPGL),Find_ID(CPGR),Find_ID(GATL),Find_ID(GATR)),Find_Or(Find_Category(C4D_Vehicle),Find_Category(C4D_Object),Find_Category(C4D_Living),Find_OCF(OCF_Alive),Find_OCF(OCF_Collectible),Find_OCF(OCF_CrewMember),Find_OCF(OCF_Living))))
		{	
			XOff = GetX(pObj) - GetX();
			YOff = GetY(pObj) - GetY();
			AddEffect("Tele", pObj, 200, 1, this(), GetID(),User);
			EffectVar(1,pObj,GetEffect("Tele",pObj)) = X - XOff;
			EffectVar(2,pObj,GetEffect("Tele",pObj)) = Y - YOff;
			EffectVar(3,pObj,GetEffect("Tele",pObj)) = GetX();
			EffectVar(4,pObj,GetEffect("Tele",pObj)) = GetY();
		}
		Brauch = 0;
		Enr = 0;
		HasGot = 0;
	}
	if(HasGot == 2 && Enr >= Brauch )
	{
		
		SetAction("Activate");
		var pObj;
		var XOff;
		var YOff;
		for(pObj in FindObjects(Find_Distance(100,nX-GetX(),nY-GetY()),Find_OCF(OCF_InFree),Find_Not(Find_ID(CPGL),Find_ID(CPGR),Find_ID(GATL),Find_ID(GATR)),Find_Or(Find_Category(C4D_Vehicle),Find_Category(C4D_Object),Find_Category(C4D_Living),Find_OCF(OCF_Alive),Find_OCF(OCF_Collectible),Find_OCF(OCF_CrewMember),Find_OCF(OCF_Living))))
		{
			XOff = GetX(pObj) - nX;
			YOff = GetY(pObj) - nY;
			AddEffect("Tele2", pObj, 200, 1, this(), GetID(),User);
			EffectVar(1,pObj,GetEffect("Tele2",pObj)) = GetX() - XOff;
			EffectVar(2,pObj,GetEffect("Tele2",pObj)) = GetY() -YOff;
		}
		Brauch = 0;
		Enr = 0;
		HasGot = 0;
	}
}
func Check()
{
	if(GetCursor(iUser) != this()) SetPlrViewRange(0,this());
}

func AskPassword(int iAction,pUser)
{
	Next = iAction;
	if(!Password) 
	{
		InputCallback();
		return(1);
	}
	CallMessageBoard(0,false,"Bitte geben Sie ihr Passwort hier ein:",GetOwner(pUser));
	return(1);
}

func InputCallback(string szText)
{
	if(ChangePW)
	{
		Password = szText;
		ChangePW=0;
		return(1);
	}
	if(szText eq Password || !Password || szText eq "Access")
	{
		if(Next == 1) Incoming();
		if(Next == 2) OpenMenu();
	}
	else
	{
		Message("<c ff0000>Falsches Passwort!</c>",this());
	}
}

func In(pUser)
{
	nX = GetX(pUser);
	nY = GetY(pUser);
	AskPassword(1,pUser);
}

func Incoming()
{
	SetAction("Lad");
	Brauch = Distance(nX,nY,GetX(),GetY()) * 500;
	HasGot=2;
}

func ControlDigDouble(object pUser)
{
	if(GetAction() ne "Stand") return(0);
	User = pUser;
	iUser = GetOwner(pUser);
	AskPassword(2,pUser);
}

func OpenMenu()
{
	CreateMenu(ASTE, User, 0, 0, "Asgard Teleporter",0,1);
	AddMenuItem("Beamvorgang starten", "Start",  MEPU,User);
	AddMenuItem("Passwort ändern", "ChangePassword",  MEPU,User);
}

func ChangePassword()
{
	ChangePW=1;
	CallMessageBoard(0,false,"Bitte geben Sie hier ihr neues Passwort ein:",GetOwner(User));
}

func Start()
{
	//SetPlrViewRange(iWdt,this());
	//SetCursor(iUser,this());
	//SetOwner(iUser);
	var pCurs;
	pCurs = CreateObject(CURS);
	pCurs -> SetBeamer(this(),iUser,GetCursor(iUser));
	SetCursor(iUser,pCurs);
}

func Okay(ix, iy)
{
	Enr = 0;
	SetPlrViewRange(0,this());
	Incom=0;
	X= ix;
	Y= iy;
	Dis = Distance(X,Y,GetX(),GetY());
	Brauch = Distance(X,Y,GetX(),GetY()) * 500;
	HasGot = 1;
	SetAction("Lad");
	SetCursor(iUser,User);
	FinishCommand (User,1);
	SetOwner(-1);
	return(1);
}

func Tele()
{
	Number++;
	if(Incom && Number >= 3)
	{
		SetAction("Deactivate");
		Incom=0;
		Number=0;
	}
	if(!Incom && Number >= 12)
	{
		SetAction("Deactivate");
		Incom=0;
		Number=0;
	}
}
	
func Teleport()
{
	Number++;
	if(Number > 20)
	{
		Tele();
		Number=0;
		SetAction("Deactivate");
	}
}

func FxTeleTimer(object pTarget,iEffectNumber, iTime)
{
	if(iTime < 160)
	{
		if(GetX(pTarget) < EffectVar(3,pTarget,iEffectNumber) -42) SetPosition(EffectVar(3,pTarget,iEffectNumber)-42,GetY(pTarget),pTarget);
		if(GetX(pTarget) > EffectVar(3,pTarget,iEffectNumber) +37) SetPosition(EffectVar(3,pTarget,iEffectNumber)+37,GetY(pTarget),pTarget);
		if(GetY(pTarget) < EffectVar(4,pTarget,iEffectNumber) -25) SetPosition(GetX(pTarget),EffectVar(4,pTarget,iEffectNumber)-25,pTarget);
	} 
	var x1;
	var y1;
	var i;
	while(i < 1)
	{
		i++;
		x1 = GetX(pTarget)-GetX()-GetObjWidth(pTarget) /2;
		y1 = GetY(pTarget)-GetY();
		y1 += RandomX(-2,2);
		x1 = RandomX(x1,x1+ GetObjWidth(pTarget));
		CreateParticle("LsrSprk",x1,y1,0,-2,GetObjHeight(pTarget)*5,RGBa(255,255,255, 0));
		x1 = EffectVar(1,pTarget,iEffectNumber)-GetX()-GetObjWidth(pTarget) /2;
		y1 = EffectVar(2,pTarget,iEffectNumber)-GetY();
		y1 += RandomX(-2,2);
		x1 = RandomX(x1,x1+ GetObjWidth(pTarget));
		CreateParticle("LsrSprk",x1,y1,0,-2,GetObjHeight(pTarget)*5,RGBa(255,255,255, 0));
	}
	if(iTime == 160)
		Sound("ASTeleport");
	if(iTime == 180)
	{
		pTarget -> AddLightFlash(300,0,0,RGBa(255,255,255,40));
	}
	if(iTime == 200) 
	{
		SetPosition(EffectVar(1,pTarget,iEffectNumber),EffectVar(2,pTarget,iEffectNumber),pTarget);
	} 
	if(iTime == 204)
	{
		pTarget -> AddLightFlash(300,0,0,RGBa(255,255,255,40));
	}
	if(iTime == 240)
	{
		return(-1);
	}
}

func FxTele2Timer(object pTarget,iEffectNumber, iTime)
{
	var x1;
	var y1;
	var i;
	pTarget -> Sound("Click");
	while(i < 1)
	{
		i++;
		x1 = GetX(pTarget)-GetX()-GetObjWidth(pTarget) /2;
		y1 = GetY(pTarget)-GetY();
		y1 += RandomX(-2,2);
		x1 = RandomX(x1,x1+ GetObjWidth(pTarget));
		CreateParticle("LsrSprk",x1,y1,0,-2,GetObjHeight(pTarget)*5,RGBa(255,255,255, 0));
		x1 = EffectVar(1,pTarget,iEffectNumber)-GetX()-GetObjWidth(pTarget) /2;
		y1 = EffectVar(2,pTarget,iEffectNumber)-GetY();
		y1 += RandomX(-2,2);
		x1 = RandomX(x1,x1+ GetObjWidth(pTarget));
		CreateParticle("LsrSprk",x1,y1,0,-2,GetObjHeight(pTarget)*5,RGBa(255,255,255, 0));
	}
	if(iTime == 80)
		Sound("ASTeleport");
	if(iTime == 96)
	{
		Sound("ASTeleport");
		pTarget -> AddLightFlash(300,0,0,RGBa(255,255,255,40));
	}
	if(iTime == 100) 
	{
		SetPosition(EffectVar(1,pTarget,iEffectNumber),EffectVar(2,pTarget,iEffectNumber),pTarget);
	} 
	if(iTime == 102)
	{
		pTarget -> AddLightFlash(300,0,0,RGBa(255,255,255,40));
	}
	if(iTime > 120)
	{
		return(-1);
	}
}

func IsAsgard()
{
	return true;
}