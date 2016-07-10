#strict
static RepliLimit;
static RepliHunger;
static const RepliView = 1000;
local Counter,Fight,iDamg,Expanded,Builded,Mauer,MachAusrust;
func Initialize()
{
	CreateConstruction(RETE,-60,5,-1,1) -> SetQueen(this(),-60);
	CreateConstruction(RETE,60,5,-1,1) -> SetQueen(this(),60);
	if(!RepliLimit) RepliLimit = 50;
	if(!RepliHunger) RepliHunger = 1;
	Mauer = CreateObject(REBO,0,40);
	Mauer -> SetQueen(this());
	SetXDir();
	SetYDir();
	SetAction("Stand");
}


func Construction()
{
	CreateScriptPlayer("Replikatoren",RGB(255,255,255),0,CSPF_FixedAttributes|CSPF_NoScenarioInit|CSPF_NoEliminationCheck);
	var i;
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i) eq "Replikatoren")
		{
			SetOwner(i);
		}
		i++;
	}
}


func OnDmg(iLevel)
{
	return(Damage(iLevel));
}

func IsRepli()
{
	return(true);
}
func ExpRdy()
{
	Expanded = 1;
}

func BuiRdy()
{
	Builded = 1;
}

func HasBui()
{
	return(Builded);
}

func HasExp()
{
	return(Expanded);
}

func BuiDam()
{
	Builded = 0;
}

func ExpDam()
{
	Expanded = 0;
}

func Dummer()
{
	SetXDir();
	SetYDir();
}
func Damage(int iLevel,H,H)
{
	iDamg = GetDamage();
	while(GetPlayerName(GetOwner())) SetOwner(GetOwner() +1);
	if(iDamg >100 ) 
	{
		if(GetCon() == 100) CastReplis(20);
		RemoveObject();
	}
	iDamg += iLevel;
	if(FindObject(REAG)) return();
	if(!HasExp()) return();
	if(GetKiller() == GetOwner()) return();
	Fight = 1;
	var pCrew;
	var iReplis;
	iReplis = ObjectCount2(Find_ID(REPL),Find_Distance(RepliView),Sort_Distance());
	iReplis /= 5;
	var i;
	var i;
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			if(GetPlayerName(i) ne "Replikatoren")
			{
				GameCall("SetHostility(GetOwner(),i,1)");
				GameCall("SetHostility(i,GetOwner(),1)");
			}
		}
		i++;
	}
	for(pCrew in FindObjects(Find_ID(REPL),Find_Distance(RepliView),Sort_Distance()))
	{
		LocalN("Forced",pCrew) = 0;
		LocalN("Action",pCrew) = 3;
		if(i < iReplis && iReplis > 3)
		{
			LocalN("Action",pCrew) = 0;
			LocalN("Forced",pCrew) = 1;
		}	
		i++;
	}
}

func Timer()
{
	MachAusrust++;
	if(MachAusrust == 900) 
	{
		CreateObject(HARM);
		MachAusrust = 0;
	}
	if(Mauer) SetPosition(GetX(Mauer),GetY());
	if(GetOwner() != -1) SetOwner(-1);
	if(GetCon() < 100) return(0);
	var pCont;
	while(pCont = FindContents(REWU))
	{
		RemoveObject(pCont);
		Counter++;
	}
	if(Counter > RepliHunger)
	{
		if(ObjectCount2(Find_ID(REPL),Find_Distance(RepliView),Sort_Distance()) >= RepliLimit / 2 && !Builded)
		{
			BuildMauer();
			Counter = 0;
		}
		if(ObjectCount2(Find_ID(REPL),Find_Distance(RepliView),Sort_Distance()) >= RepliLimit && !Expanded && Builded)
		{
			ExpandMauer();
			Counter = 0;
		}
	}
	if(Counter > 0)
	{
		if(ObjectCount(REPL) <= RepliLimit || !RepliLimit) 
		if(Builded || ObjectCount2(Find_ID(REPL),Find_Distance(RepliView),Sort_Distance()) <= RepliLimit / 2) 
		if(Expanded || ObjectCount2(Find_ID(REPL),Find_Distance(RepliView),Sort_Distance()) <= RepliLimit)
		{
			CreateObject(REWU,0,0,-1);
			CreateObject(REWU,0,0,-1);
			Counter = 0;
		}
	}
}

func KilledByARW()
{
	Damage();
	CastReplis(20,1);
	RemoveObject();
}

func BuildMauer()
{
	Mauer -> Build();
}

func ExpandMauer()
{
	Mauer -> ExpandNext();
}

func EMPShock()
{
	SetAction("Idle");
	EMPShockEffect(200);
}

func EMPShockEnd() 
{
	SetAction("Stand");
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

global func HoldReplis(int Time)
{
	var pRepl;
	for(pRepl in FindObjects(Find_ID(REPL)))
	{
		pRepl -> SetAction("Idle");
		pRepl -> Schedule("SetAction(\"Idle\")",1,Time-1);
		pRepl -> FinishCommand();
		LocalN("Action",pRepl) = 0;
		if(Time) pRepl -> Schedule("SetAction(\"Walk\")",Time);
	}
}

global func StartReplis()
{
	var pRepl;
	for(pRepl in FindObjects(Find_ID(REPL)))
	{
		pRepl -> SetAction("Walk");
	}
}
