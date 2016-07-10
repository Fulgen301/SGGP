#strict
local Nummer,Has,Count,NextR,NextL,Expanded,Dir,Queen,Damg;

func Initialize()
{
	Nummer = 200;
	Dir=-2;
	SetAction("Close");
}

func IsRepli()
{
	return(true);
}
func SetQueen(object pQueen)
{
	Queen = pQueen;
	Nummer = 0;
}

func SetNummer(int iN,int iC,object pBefore,int iDir,object pQueen)
{	
	Dir = iDir;
	Queen = pQueen;
	if(iC < 0) NextR = pBefore;
	if(iC > 0) NextL = pBefore;
	Count = iC;
	Nummer = iN;
	if(Nummer == 14) if(FindObject(REQU)) FindObject(REQU) -> BuiRdy();
	if(Nummer == -4) Dir = -4;
	if(Nummer == 4) Dir = 4;
	if(Nummer == -9) Dir = -3;
	if(Nummer == 9) Dir = 3;
}

func ExpandNext()
{
	if(Expanded)
	{
		if(Count == -1)
		{
			if(NextL) NextL -> ExpandNext();
		}
		if(Count == 1)
		{
			if(NextR) NextR -> ExpandNext();
		}
		if(Count == 0)
		{
			if(NextR) NextR -> ExpandNext();
			if(NextL) NextL -> ExpandNext();
		}
	}
	else
	{
		Expand();
		if(Nummer == 14) if(FindObject(REQU)) FindObject(REQU) -> ExpRdy();
	}
}
func Opened()
{
	SetSolidMask(270,0,30,30);
}

func Closed()
{
	SetSolidMask(0,0,30,30);
}

func Build()
{
	if(Count == -1 && NextL)
	{
		NextL -> Build();
		return();
	}
	if(Count == 1 && NextR)
	{
		NextR -> Build();
		return();
	}
	if(!Count && NextR && NextL)
	{
		NextR -> Build();
		NextL -> Build();
		return();
	}
	if(Nummer == 0)
	{
		NextL = CreateObject(REBO,-30,15);
		NextL -> SetNummer(Nummer-1,-1,this(),-2,Queen);
		NextR = CreateObject(REBO,30,15);
		NextR -> SetNummer(Nummer+1,1,this(),-2,Queen);
		return();
	}
	if(Nummer > -4 && Count == -1)
	{
		if(Nummer == -3)CreateObject(REWA,-30,15) -> SetAction("1");
		NextL = CreateObject(REBO,-30,15);
		NextL -> SetNummer(Nummer-1,-1,this(),-2,Queen);
		return();
	}
	if(Nummer < 4 && Count == 1)
	{
		NextR = CreateObject(REBO,30,15);
		NextR -> SetNummer(Nummer+1,1,this(),-2,Queen);
		return();
	}
	if(Nummer > -9 && Count == -1)
	{
		CreateObject(REWA,0,-15) -> SetAction("1");
		NextL = CreateObject(REBO,0,-15);
		NextL -> SetNummer(Nummer-1,-1,this(),-1,Queen);
		return();
	}
	if(Nummer < 9 && Count == 1)
	{
		NextR = CreateObject(REBO,0,-15);
		NextR -> SetNummer(Nummer+1,1,this(),1,Queen);
		return();
	}
	if(Nummer > -13 && Count == -1)
	{
		NextL = CreateObject(REBO,30,15);
		NextL -> SetNummer(Nummer-1,-1,this(),2,Queen);
		return();
	}
	if(Nummer < 14 && Count == 1)
	{
		NextR = CreateObject(REBO,-30,15);
		NextR -> SetNummer(Nummer+1,1,this(),2,Queen);
		return();
	}
}

func Expand()
{
	if(Dir == -2) Expanded = CreateObject(REBO,0,45);
	if(Dir == 2) Expanded = CreateObject(REBO,0,-15);
	if(Dir == -1) 
	{
		Expanded = CreateObject(REBO,-30,15);
		if(Nummer== 5 || Nummer == -5) Expanded -> SetNummer(211);
	}
	if(Dir == 1) 
	{
		Expanded = CreateObject(REBO,30,15);
		if(Nummer== 5 || Nummer == -5) Expanded -> SetNummer(211);
	}
	if(Dir == -3)
	{
		Expanded = CreateObject(REBO,-30,15);
		CreateObject(REBO,0,-15);
		CreateObject(REBO,-30,-15);
	}
	if(Dir == -4)
	{
		Expanded = CreateObject(REBO,-30,45);
		CreateObject(REBO,0,45);
		CreateObject(REBO,-30,15);
	}
	if(Dir == 3)
	{
		Expanded = CreateObject(REBO,30,15);
		CreateObject(REBO,0,-15);
		CreateObject(REBO,30,-15);
	}
	if(Dir == 4)
	{
		Expanded = CreateObject(REBO,30,45);
		CreateObject(REBO,0,45);
		CreateObject(REBO,30,15);
	}
	var Wand;
	if(Wand = FindObject2(Find_ID(REWA),Find_Distance(5),Sort_Distance()))
	{
		Wand -> SetAction("2");
	}
			
}
/*
-2=Unten
2=Oben
-1=Links
1=Rechts
-3=ObenLinks
-4=UntenLinks
3=ObenRechts
4=UntenRechts
*/

func IsBulletTarget()
{
	if(GetAction() eq "StandClose") return(1);
}

func UpdateSolidOpen()
{
	SetSolidMask(GetPhase() * 30, 0, 30, 30);
}

func UpdateSolidClose()
{
	SetSolidMask(300 - GetPhase() * 30, 0, 30,30);
}

func Check()
{
	var pStuck;
	if(GetAction() eq "StandClose")
	{
		for(pStuck in FindObjects(Find_InRect(-16,-16,32,32),Find_Or(Find_Category(C4D_Living),Find_Category(C4D_Object)),Find_Exclude(this()),Find_Not(Find_Or(Find_ID(REWA),Find_ID(REBO)))))
		{
			if(pStuck) 
			{
				pStuck -> SetPosition(GetX(pStuck),GetY(pStuck) - 35,pStuck);
				if(GetID(pStuck) == WOOD)
				{
					RemoveObject(pStuck);
				}
			}
			
		}
		for(pStuck in FindObjects(Find_ID(WOOD),Find_InRect(-20,-15,40,35),Find_Or(Find_Category(C4D_Living),Find_Category(C4D_Object)),Find_Exclude(this()),Find_Not(Find_Or(Find_ID(REWA),Find_ID(REBO)))))
		{
			if(pStuck) 
			{
				pStuck -> RemoveObject();
			}
			
		}

	}
	if(Nummer == -5 || Nummer == 5 || Nummer == 211)
	{
		if(FindObject2(Find_Or(Find_ID(REPL),Find_ID(RELE)),Find_InRect(-200,-15,400,30),Find_Not(Find_Or(Find_Action("Scale"),Find_Action("ScaleDown")))))
		{
			if(GetAction() eq "StandClose") SetAction("Open");
		}
		else
		{
			if(GetAction() eq "StandOpen") SetAction("Close");
		}
	}
}

func Damage(iLevel)
{
	Damg += iLevel;
	if(Damg > 300)
	{
		if(Nummer != 0 || !Queen)
		{
			if(Queen) Queen -> BuiDam();
			RemoveObject();
		}
	}
}