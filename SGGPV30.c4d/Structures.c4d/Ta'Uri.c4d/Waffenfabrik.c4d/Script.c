#strict
#include BAS5
local aWeapons,User,Weaponid,Zahl,Richtung;
func Initialize()
{
	aWeapons = CreateArray(46);
	//Hier einfach die definitionen ergänzen
	//TAURI:
	aWeapons = [TAFU,GDO_,TALP,NANO,TANG,ROGN,C4EP,C4ZU,TACM,HEGR,P90_]; 
	SetAction("Stand");
	Richtung = 1;
}

func ControlDigDouble(object pUser)
{
	if(FindObject(TAAL)) aWeapons = [BMR_,ARW_,C4EP,C4ZU,LZD_,TAFU,GDO_,TALP,NANO,ROGN,GOBE,STBW,ZATN,TACM,HEGR,P90_,WRST,WRGR,PGWP,PIWP,GGWP,MIWP,GLWP,FTWP,ENWP,MEZL,BZWP,KLAS,KSLM,KRFL,AIRS,MEDI,NLGT,NVDN,DRSU,LMIN,MINE,SMIN,AIRT,HARM,FLSH,JTPK,HSHD,STAB,ENAP,GRAP,GSAP,MIAP];
	User = pUser;
	SetOwner(GetOwner(User));
	var idDef;
	CreateMenu(MEPU, pUser, this(), 1);
	for(idDef in aWeapons)
	{
		if(idDef)
		{
			if(GetPlrKnowledge(GetOwner(),idDef))
			AddMenuItem("Herstellen: %s",Format("StartProd(%i)",idDef),idDef,pUser,0,pUser);
		}
	}
}

func Sm()
{
	Smoke(-14,-8,RandomX(10,20));
}

func Start(id idDef)
{ 
	Weaponid = idDef;
	CreateMenu(MEPU, User, 0, 0, 0,0,1);
	AddMenuItem("1",Format("StartProd(%i,%d)",idDef,1),idDef,User,0,User);
	AddMenuItem("2",Format("StartProd(%i,%d)",idDef,2),idDef,User,0,User);
	AddMenuItem("5",Format("StartProd(%i,%d)",idDef,5),idDef,User,0,User);
	AddMenuItem("10",Format("StartProd(%i,%d)",idDef,10),idDef,User,0,User);
	AddMenuItem("20",Format("StartProd(%i,%d)",idDef,20),idDef,User,0,User);
	AddMenuItem("50",Format("StartProd(%i,%d)",idDef,50),idDef,User,0,User);
}

func StartProd(id idDef)
{
	var i;
	var j;
	var idComp;
	Weaponid = idDef;
	while(idComp = GetComponent(0,i,0,idDef))
	{
		j = 0;
		while(j < GetComponent(idComp,0,0,idDef) - ContentsCount(idComp))
		{
		    AddCommand(User,"Put",this(),0,0,0, 0, idComp);
		    AddCommand(User,"Acquire",0,0,0,this(), 0, idComp, 5);
		    j++;
		}
		i++;
	}
}

func Check()
{
	if(!Weaponid) return();
	var i;
	var idComp;
	while(idComp = GetComponent(0,i,0,Weaponid))
	{
		if(ContentsCount(idComp) < GetComponent(idComp,0,0,Weaponid))
		return();
		i++;
	}
	SetAction("Produce");
}

func Ready()
{
	CreateObject(Weaponid,-14,-2,GetOwner());
	var i;
	var idComp;
	while(idComp = GetComponent(0,i,0,Weaponid))
	{
		var j = 0;
		while(j < GetComponent(idComp,0,0,Weaponid))
		{
			if(FindContents(idComp)) RemoveObject(FindContents(idComp));
			j++;
		}
		i++;
	}
	Weaponid = 0;
}

func Lauf()
{
	var aIn;
	aIn = CreateArray(7);
	aIn = [METL,CRYS,FLNT,SFLN,EFLN,ENAP,NAQU];
	var p;
	for(p in FindObjects(Find_Category(C4D_Object),Find_InRect(-15,-2,45,3)))
	{
		SetYDir(-2,p);
		if(GetIndexOf(GetID(p),aIn) != -1)
		{
			SetXDir(-2,p);
		}
		else
		{
			SetXDir(2 * Richtung,p);
		}
	}
}

func ControlLeft()
{
	Richtung = -1;
}

func ControlRight()
{
	Richtung = 1;
}

func ProduceObj(id idDef)
{
	Weaponid = idDef;
	SetAction("Produce");
}

func Collection()
{
	return(Sound("Clonk"));
}


func Damage()
{
  if(GetDamage() >= 100)
  {
   Explode(50);
  }
  return(1);
}

public func GetRace() { return SG1_StargateCenter; }