#strict
local HasDr,Wurfel,iDamg,IsARWd,Time;
static Repl_Drohnen;
func Initialize()
{
	SetAction("NoDr");
	MatQuad("Granite",GetX()-20,GetY()+15,40,5);
	var p;
	for(p in FindObjects(Find_InRect(-20,15,40,5),Find_Exclude(this())))
	{
		SetPosition(GetX(p),GetY(p)-10,p);
	}
	
}


func OnDmg(iLevel)
{
	return(Damage(iLevel));
}

func HasARW()
{
	return(IsARWd);
}

func Timer()
{
	if(GetCon() < 100) return();
	if(IsARWd)
	{
		Time--;
		if(Time <= 0)
		{
			var pEnemy;
			pEnemy = FindObject2(Find_Not(Find_ID(RELE)),Find_OCF(OCF_CrewMember),Find_Distance(RepliView/3),Sort_Distance());
			if(pEnemy)
			{
				if(!FindObject(REAG))
				{
					if(PathFree(GetX(), GetY(), GetX(pEnemy), GetY(pEnemy)))
					{
						var angle;
						var laser;
						laser = CreateObject(LASR,0,-5);
						angle = Angle(Abs(GetX()),Abs(GetY()),Abs(GetX(pEnemy)+RandomX(-10,10)),Abs(GetY(pEnemy)+RandomX(-10,10)));
						laser -> SetClrModulation(RGB(0,0,255));
						laser -> Set(angle,10,ObjectDistance(pEnemy)+100,15,this());
						Sound("LaserShot");
						Time = 10;
					}
				}
			}
		}
	}
	else
	{
		if(Wurfel >= 2 && !HasDr)
		{
			SetAction("HasDr");
			Wurfel = 0;
			HasDr ++;
			Repl_Drohnen++;
		}
		if(!FindObject(REAG))
		if(HasDr && FindObject2(Find_Not(Find_ID(RELE)),Find_OCF(OCF_CrewMember),Find_Distance(RepliView/3),Sort_Distance()))
		{
			Fling(CreateObject(REDR),0,-10);
			HasDr=0;
			SetAction("NoDr");
			Repl_Drohnen--;
		}
	}
}

func LaserStrike(object pEnemy)
{
	DoEnergy(-20,pEnemy);
}

func MachARW()
{
	Repl_Drohnen -= HasDr;
	HasDr = 0;
	IsARWd = 1;
	SetAction("HasARW");
}

func NeedWurfel()
{
	if(Wurfel < 2 && !HasDr) return(1);
	return(0);
}

func MachWurfel()
{
	Wurfel++;
	return(Wurfel);
}

func Damage(int iLevel)
{
	if(iDamg > 100) 
	{
		if(GetCon() == 100) CastReplis(20);
		SetCon(1);
	}
	iDamg += iLevel;
}

func KilledByARW()
{
	CastReplis(20,1);
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


func IsRepli()
{
	return(true);
}