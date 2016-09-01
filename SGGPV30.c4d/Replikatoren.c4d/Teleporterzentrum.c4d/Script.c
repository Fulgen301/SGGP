#strict
local ARWd,Teles,iDamg,Empi,pQueen,Disabled,Bop,Counter,X;
func Initialize()
{
	SetAction("NoARW");
	Teles = -500;
	SetPosition(GetX(),GetY()+2);
}

func IsRepli()
{
	return(true);
}

func Timer()
{
	if(X) SetPosition(X,GetY());
	if(GetCon() < 100 || !ARWd || Empi || Disabled) return(0);
	var pOther;
	pOther = FindObject2(Find_ID(RETE),Find_Distance(RepliView),Find_Action("ARW"),Find_Exclude(this()));
	Bop++;
	if(Bop > 5)
	{
		var pBeam;
		pBeam = FindObject2(Find_OCF(OCF_Collectible),Find_NoContainer(),Find_Not(Find_ID(REWU),Find_Func("IsEquipment")),Find_Not(Find_And(Find_ID(FLAG),Find_Action("FlyBase"))),Find_Distance(RepliView*3),Find_Not(Find_Distance(300)));
		if(!pBeam) return(0);
		Beam(pBeam,this());
		Bop = 0;
	}
	if(pOther)
	{
		var Y;
	   	var X;
	   	X = GetX(pOther)-GetX();
	   	Y = GetY(pOther)-GetY();
		Teles+=2;
		if(Teles > 0)
		{
			if(Teles < 360)
			{
				Teles+=8;
				Y = GetY(pQueen) - 50 -GetY();
			   	var Radius;
			   	Radius = 40;
			   	X = GetX(pQueen) - GetX();
				var e;
			   	DrawParticleLine("PSpark", 0,0,X + Sin(Teles,Radius),Y-Cos(Teles,Radius), 4,20, RGB(128,0,255), RGB(0,0,255));
				DrawParticleLine("PSpark",GetX(pOther)-GetX(),GetY(pOther)-GetY(),X + Sin(Teles,Radius),Y-Cos(Teles,Radius), 4,20, RGB(128,0,255), RGB(0,0,255));
			   	pOther -> Disable();
			   	Disabled = 0;
				//CastParticles("PSpark", 10,60, 0,0, 20, 200, RGB(255,0,0), RGB(255,0,0));
				//pOther -> CastParticles("PSpark", 10,60, 0,0, 20, 200, RGB(255,0,0), RGB(255,0,0));
				//CastParticles("PSpark", 50,30, GetX(pQueen)-GetX(),GetY(pQueen) -50-GetY(), 100, 200, RGB(10,10,255), RGB(10,10,255));
			   	//if(Teles < 360) DrawParticleLine("PSpark", GetX(pQueen)-GetX(),GetY(pQueen) -50-GetY(),X + Sin(Teles,Radius),Y-Cos(Teles,Radius), 2, 20, RGB(0,0,255), RGB(0,0,255));
			   	while(e <= Teles) 
				{
			   		e+=4;
			   		CreateParticle("PSpark",X + Sin(e,Radius),Y-Cos(e,Radius),0,0, 20,RGB(0,0,255));
			  	}
		  	}
		  	else
		  	{
		  			Teles=360;
					Counter++;
			  		if(Counter > 10) 
			  		{
		  				Teles = -500;
			  			Counter = 0;
			  			return(0);
			  		}
					Y = GetY(pQueen) - 50 -GetY();
				   	X = GetX(pQueen) - GetX();
			  		var RandX;
			  		var RandY;
			  		RandX=RandomX(-20,20);
			  		RandY=RandomX(-10,10);
			  		var aArray;
			  		aArray = CreateArray(8);
			  		aArray = [METL,ROCK,GOLD,CRYS,WOOD,SPHR,COAL,LOAM];
			  		DrawParticleLine("PSpark", X,Y+50,X+RandX,Y+RandY , 4,20, RGB(128,0,255), RGB(0,0,255));
		  			CreateObject(aArray[Random(8)],X+RandX,Y+RandY,GetOwner(pQueen));
		  	}
		  	return();
		 }
		 return();
	}
	else
	{
		Counter = 0;
		Teles = -500;
	}
}

func Disable(int Disabl)
{
	Disabled = 1;
}

func SetQueen(object Queen,iXPos)
{
	X = GetX(pQueen) + iXPos;
	pQueen = Queen;
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

func OnDmg(iLevel)
{
	return(Damage(iLevel));
}

func Damage(int iLevel)
{
	iDamg = GetDamage();
	if(iDamg > 100) 
	{
		if(GetCon() == 100) CastReplis(20);
		SetCon(1);
	}
	iDamg += iLevel;
}

func EMPShock()
{
	Empi=1;
	EMPShockEffect(200);
}

func EMPShockEnd() 
{
	Empi=0;
	SetAction("Stand");
}

func KilledByARW()
{
	CastReplis(20,1);
	if(pQueen) pQueen -> Damage();
	SetCon(1);
}

func IsMachine() 
{ 
	return(true); 
}

func IsThreat() 
{ 
	return(true); 
}

func IgnoreFriendlyFire() 
{ 
	return(true); 
}

func IsBulletTarget() 
{ 
	return(true); 
}

