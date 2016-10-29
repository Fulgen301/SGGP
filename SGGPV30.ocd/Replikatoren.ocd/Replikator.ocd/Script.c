#strict
static const RepliView = 2000;
local pFind,Action,pEnemy,pQueen,iDamg,pBuilding,Forced,pTree,pBeam,pARW,pGate,pDrohne,Dummy;

/* 
Aktionsliste der Replikatoren: (Variable: "Action")
---------------------------------------------------
	0: Nix
	1: Objektsuche
	2: Objekt bringen
	3: Angreifen
	4: Gebäude schrotten
	5: Bäume fällen
	6: Objekt zum Teleporter bringen
	7: ARW holen
	8: ARW zum Teleporter bringen
	9: Gate manipulieren
	10: Drohnenrampe bauen
	11: Drohnenrampe beliefern
	12: Drohnenrampe aufmotzen
---------------------------------------------------
*/

func IsRepli()
{
	return(true);
}

func Initialize()
{
	SetAction("Walk");
  	AddEffect("DmgCheck",this(),1,0);
	var pRepl;
	for(pRepl in FindObjects(Find_ID(REPL),Find_Distance(RepliView),Sort_Distance()))
	{
		 if(LocalN("Action",pRepl) ==3) Action = 3;
	}
}

protected func Scaling()
{
	var szDesiredAction;
	if (GetYDir() > 0) szDesiredAction = "ScaleDown"; else szDesiredAction = "Scale";
	if (GetAction() ne szDesiredAction) SetAction(szDesiredAction);
	return(1);   
}

func MachAction(int i)
{
	Action = 1;
	return(i);
}

func Timer()
{
	if(GetXDir() != 0)
	{
		Sound("Repl*");
	}
	while(GBackSolid())
	{
		SetPosition(GetX(),GetY()-1);
	}
	if(!GetXDir()) if(Abs(GetYDir()) < 5) if(GBackSolid(0, 3)) DigFreeRect(GetX()-10,GetY()-5,20,10);
	if(GetOwner() != GetOwner(pQueen)) SetOwner(GetOwner(pQueen));
	if(GetPlayerName(GetOwner()) ne "Replikatoren") SetOwner(-1);
	if(!pQueen)
	{
		pQueen = FindObject2(Find_ID(REQU));
		if(!pQueen) 
		{
			if(!FindObject2(Find_Distance(150),Find_Category(C4D_Structure)) && GetX() > 200 && GetX() < LandscapeWidth() - 200)
			{
				pQueen = CreateConstruction(REQU,0,0,-1,1);
			}
			else
			{
				if(GetX() > LandscapeWidth() / 2) SetComDir(COMD_Left);
				if(GetX() < LandscapeWidth() / 2) SetComDir(COMD_Right);
			}
		}
		if(!pQueen) return(0);
	}
	while(FindContents(REWU)) Exit(FindContents(REWU));
	if(GetCon(pQueen) < 100)
	{
		var i;
		var pCont;
		if(ObjectCount2(Find_ID(REPL),Find_Distance(RepliView),Sort_Distance()) <5 && Action == 3) Action = 0;
		while(pCont = Contents(i,pQueen))
		{
			if(Contents(i,pQueen)) RemoveObject(Contents(i,pQueen));
			pQueen -> DoCon(5);
			i++;
		}
	}
	else
	{
		if(!pARW)
		{
			pARW= FindARW();
			if(pARW) 
			{
				SetCommand(this(),"Get",pARW);
				Action = 7;
			}
		}
	}
	if(Action == 1 && !pFind)
	{
		Action = 0;
	}
	if(Action && !pEnemy && !pFind && !Contents() && !pBuilding && !pTree && !pBeam && !pARW && !pGate && !pDrohne && !Dummy)
	{
		Action = 0;
	}
	if(Action == 0)
	{
		pARW= FindARW();
		if(pARW) SetCommand(this(),"Get",pARW);
		if(!pARW)
		{
			if(ObjectCount2(Find_ID(REDA),Find_Not(Find_Func("HasARW"))) < 3 && pQueen -> HasBui())
			{
				Action = 10;
				Dummy=1;
				return(1);
			}
				pGate= FindGate();
				if(pGate) SetCommand(this(),"MoveTo",pGate);
				if(!pGate)
				{	
					pFind= FindObj();
					if(pFind) SetCommand(this(),"Get",pFind);
					if(!pFind)
					{
						pBuilding = FindBuilding();
						if(pBuilding) SetCommand(this(),"MoveTo",pBuilding);
						if(!pBuilding)
						{
							pTree = FindTree();
							if(pTree) SetCommand(this(),"MoveTo",pTree);
							if(!pTree)
							{	
								 Action = 3;
								return();
							}
							Action = 5;
							return(1);
						}
						Action = 4;
						return(1);
					}
					Action = 1;
					return(1);
				}
				Action = 9;
				return(1);
		}
		Action = 7;
		return(1);
	}	
	if(Action == 1)
	{
		if(pFind) SetCommand(this(),"Get",pFind);
		if(Contained(pFind) && Contained(pFind) != this())
		{
			Action = 0;
		}
		if(!PathFree(GetX(),GetY(),GetX(pFind),GetY(pFind)))
		{
			Action = 0;
		}
		if(Contained(pFind) == this())
		{
			if(pFind -> ~IsWeapon())
			{
				var pDro;
				if(pDro = FindObject2(Find_ID(REDA),Find_Distance(RepliView),Find_Not(Find_Func("HasARW")),Find_OCF(OCF_Fullcon)))
				{
					pBeam = pDro;
					SetCommand(this(),"MoveTo",pBeam);
					Action = 12;
					return();
				}
			}	
			if(GetComponent(1,0,pFind)) Split2Components(pFind);
			var i;
			i = 1;
			var pCont;
			while(pCont = Contents(i))
			{
				pCont -> Exit();
			}
			var pBea;
			if(pQueen -> HasBui()) pBea = FindObject2(Find_ID(RETE),Find_Not(Find_OCF(OCF_Fullcon)),Find_Distance(RepliView),Find_Not(Find_Action("ARW")));
			if(!pBea)
			{
				pBea = FindObject2(Find_ID(REDA),Find_Not(Find_OCF(OCF_Fullcon)),Find_Distance(RepliView));
				if(pBea)
				{
					pBeam = pBea;
					SetCommand(this(),"MoveTo",pBeam);
					Action = 6;
				}
				else
				{
					if(pQueen -> HasExp() && ObjectCount2(Find_ID(REDA),Find_Distance(RepliView),Find_Func("NeedWurfel")))
					{
						pDrohne = FindObject2(Find_ID(REDA),Find_Distance(RepliView),Sort_Distance(),Find_Func("NeedWurfel"));
						SetCommand(this(),"MoveTo",pQueen);
						Action = 11;
					}
					else
					{
						SetCommand(this(),"MoveTo",pQueen);
						Action = 2;
					}
				}
			}
			else
			{
				pBeam = pBea;
				SetCommand(this(),"MoveTo",pBeam);
				Action = 6;
			}	
		}
	}
	if(Action == 2)
	{
		SetCommand(this(),"MoveTo",pQueen);
		if(ObjectDistance(pQueen) < 40)
		{
			pQueen -> CreateContents(REWU);
			if(Contents()) RemoveObject(Contents());
			Action = 0;
		}
	}
	if(Action == 3)
	{
		if(pEnemy) SetCommand(this(),"MoveTo",pEnemy);
		if(ObjectDistance(pEnemy) < 15)
		{
			Punch(pEnemy,5);
			Jump(0,5);
			SetCommand(this(),"MoveTo",pEnemy);
		}
		if(pEnemy)
		{
			if(GetAction(pEnemy) eq "Dead")
			{
				if(Random(50))
				{
					RemoveObject(pEnemy);
//					CreateObject(REHU) -> Set(pQueen);
					RemoveObject();
				}
			}
		}
		if(!pEnemy || GetAction(pEnemy) eq "Dead")
		{
			pEnemy = FindObject2(Find_Not(Find_ID(RELE)),Find_OCF(OCF_CrewMember),Find_Distance(RepliView),Sort_Distance());
			SetCommand(this(),"MoveTo",pEnemy);
			if(!pEnemy)
			{
				Action = 0;
				SetCommand(this(),"MoveTo",pQueen);
			}
		}
	}
	if(Action == 4)
	{
		if(!pBuilding) 
		{
			Action = 0;
			SetCommand(this(),"MoveTo",pQueen);
			return();
		}
		if(pBuilding) SetCommand(this(),"MoveTo",pBuilding);
		var iAway;
		iAway  = GetX(pBuilding) -GetX();
		if(iAway < 0) iAway *= -1;
		if(iAway < 50)
		{
			if(GetID(pBuilding) == GATL ||GetID(pBuilding) == GATR)
			{
				pBuilding -> DoDamage(1);
			}
			else
			{
				pBuilding -> DoDamage(2);
			}
			Sound("Build*");
			if(GetDamage(pBuilding) > 200)
			{
				Split2Components(pBuilding);
				Action = 0;
			}
		}
	}
	if(Action == 5)
	{
		if(!pTree) 
		{
			Action = 0;
			SetCommand(this(),"MoveTo",pQueen);
			return();
		}
		if(pTree) SetCommand(this(),"MoveTo",pTree);
		var iAway;
		iAway  = GetX(pTree) -GetX();
		if(iAway < 0) iAway *= -1;
		if(iAway < 50)
		{
			pTree -> DoDamage(2);
			Sound("Chop*");
			if(pTree -> TreeStrength() < GetDamage(pTree))
			{
				Split2Components(pTree);
				Action = 0;
			}
		}
	}
	if(Action == 6)
	{
		SetCommand(this(),"MoveTo",pBeam);
		if(ObjectDistance(pBeam) < 40)
		{
			pBeam -> DoCon(5);
			if(Contents()) RemoveObject(Contents());
			Action = 0;
		}
	}
	if(Action == 7)
	{
		if(pARW) SetCommand(this(),"Get",pARW);
		if(Contained(pARW) && Contained(pARW) != this()) 
		{
			Action = 0;
		}
		if(Contained(pARW) == this())
		{
			var pBea;
			pBea = FindObject2(Find_ID(REAT),Find_OCF(OCF_Fullcon),Find_Distance(RepliView),Find_Not(Find_Action("ARW")));
			if(!pBea) pBea = FindObject2(Find_ID(RETE),Find_OCF(OCF_Fullcon),Find_Distance(RepliView),Find_Not(Find_Action("ARW")));
			if(!pBea)
			{
				SetCommand(this(),"MoveTo",pQueen);
				Action = 8;
			}
			else
			{
				pBeam = pBea;
				SetCommand(this(),"MoveTo",pBeam);
				Action = 8;
			}	
		}
	
	}
	if(Action == 8)
	{
		if(pBeam)
		{
			SetCommand(this(),"MoveTo",pBeam);
			var iAway;
			iAway  = GetX(pBeam) -GetX();
			if(iAway < 0) iAway *= -1;
			if(iAway < 50)
			{
				pBeam -> ~MachARW();
				if(Contents()) RemoveObject(Contents());
				Action = 0;
			}
		}
		else
		{
			SetCommand(this(),"MoveTo",pBeam);
			var iAway;
			iAway  = GetX(pTree) -GetX();
			if(iAway < 0) iAway *= -1;
			if(iAway < 50)
			{
				if(Contents()) Exit(Contents());
				Action = 0;
			}
			
		}
	}
	if(Action == 9)
	{
		SetCommand(this(),"MoveTo",pGate);
		var iAway;
		iAway  = GetX(pGate) -GetX();
		if(iAway < 0) iAway *= -1;
		if(iAway < 50)
		{
			var pMani;
			pMani = pGate -> CreateConstruction(REAT,-5,75,GetOwner(),1);
			pMani -> SetGate(pGate);
			pGate=0;
			Action = 0;
		}
	}
	if(Action == 10)
	{
		var pNextDr;
		if(ObjectCount2(Find_ID(REDA),Find_Distance(RepliView)) >= 3) 
		{
			Action = 0;
			Dummy = 0;
		}
		pNextDr = FindObject2(Find_Not(Find_Func("Replikator")),Find_Func("IsRepli"),Find_Distance(100),Sort_Distance());
		if(!pNextDr)
		{
			CreateConstruction(REDA,0,0,-1,10);
			Dummy=0;
			Action=0;			
		}
		if(GetX(pNextDr) > GetX() && GetX() > 100)
		{
			SetComDir(COMD_Left);
		}
		else
		{
			if(GetX() < LandscapeWidth() -100)
			{
				SetComDir(COMD_Right);
			}
			else
			{
				SetComDir(COMD_Left);
			}
		}
	}
	if(Action == 11)
	{
		SetCommand(this(),"MoveTo",pDrohne);
		if(ObjectDistance(pDrohne) < 40)
		{
			pDrohne -> MachWurfel();
			if(Contents()) RemoveObject(Contents());
			Dummy=0;
			Action = 0;
		}
	}
	if(Action == 12)
	{
		SetCommand(this(),"MoveTo",pBeam);
		if(ObjectDistance(pBeam) < 40)
		{
			pBeam -> MachARW();
			if(Contents()) RemoveObject(Contents());
			Action = 0;
		}
	}
}

func Replikator()
{
	return(true);
}

func Damage(int iLevel)
{
    iDamg = GetDamage();
	if(iDamg > 10) 
	{
		CastReplis(RepliHunger);
		RemoveObject();
		return();
	}
	iDamg += iLevel;
	if(pQueen)
	{
		if(pQueen -> HasExp() == 0) return();
	}
	return(1);
	if(GetKiller() == GetOwner()) return();
	var pCrew;
	for(pCrew in FindObjects(Find_ID(REPL),Find_Distance(RepliView),Sort_Distance()))
	{
		if(pCrew) LocalN("Action",pCrew) = 3;
	}
	if(pQueen) pQueen -> Damage();
	 Action = 3;
	pEnemy = FindObject2(Find_OCF(OCF_CrewMember),Find_Distance(RepliView),Sort_Distance());
	if(pEnemy) SetCommand(this(),"MoveTo",pEnemy);
}

func EMPShock()
{
	Damage(0);
	SetAction("Idle");
	EMPShockEffect(200);
}

func EMPShockEnd() 
{
	SetAction("Walk");
}

global func CastReplis(int iCount,bool iDamaged)
{
	var i;
	var pRepl;
	while(i <iCount)
	{
		i++;
		pRepl = CreateObject(REWU,0,0,-1);
		Fling(pRepl,RandomX(-5,5),RandomX(-5,5));
		pRepl -> SetTo(GetX());
		if(iDamaged) pRepl -> KilledByARW();
	}
}


func KilledByARW()
{
	Damage();
	CastReplis(RepliHunger,1);
	RemoveObject();
}

func IsMachine() 
{ 
	return(true); 
}

func IsThreat() 
{ 
	return(true); 
}

func IsBulletTarget() 
{ 
	return(true); 
}

func FindTree()
{
	return(
	FindObject2(
		Find_Distance(RepliView),
		Sort_Distance(),
		Find_Func("IsTree"),
		Find_Not(
			Find_ID(REQU)),
		Find_PathFree())
	);
}

func FindBuilding()
{
	return(
	FindObject2(
		Find_Distance(RepliView),
		Sort_Distance(),
		//Find_Or(
			Find_Category(C4D_Structure),
		//),
		Find_Not(
			Find_Or(
				Find_Func("IsTree"),
				//Find_ID(GATR),
				//Find_ID(GATL),
				Find_ID(TWR2),
				Find_Func("IsStargate"),
				Find_Func("IsRepli"))),		
		Find_Not(
			Find_Or(
				Find_ID(RIG1),
				Find_ID(RIG2),
				Find_ID(RIG3),
				Find_ID(TEL2),
				Find_ID(TEL3),
				Find_ID(TEL4),
				Find_ID(TEL5),
				Find_ID(TELS),
				Find_ID(TELZ),
				Find_ID(TEL_))),	
		Find_Not(
			Find_Or(
				Find_ID(TELK))),
		Find_PathFree())
	);
}

func FindObj()
{
	return(
	FindObject2(
		Find_OCF(OCF_Collectible),
		Find_NoContainer(),
		Find_Not(
			Find_ID(REWU),
			Find_ID(ARW_),
			Find_Func("IsEquipment")),
		Find_Not(
			Find_And(
				Find_ID(FLAG),
				Find_Action("FlyBase"))),
		Find_Distance(RepliView),
		Sort_Distance(),
		Find_PathFree())
	);
}


func FindARW()
{
	return(
		FindObject2(
			Find_Func("IsHazardGear"),
			Find_NoContainer(),
			Find_Distance(RepliView),
			Sort_Distance(),
			Find_PathFree())
	);
}

func FindGate()
{
	if(FindObject(REAT)) return();
	var Gate;
	Gate = FindObject2(Find_Func("IsStargate"),Find_Distance(RepliView),Sort_Distance(),Find_PathFree());
	if(!Gate) return(0);
	if(FindObject2(Find_ID(REAT),Find_InRect(GetX(Gate)-GetX()-50,GetY(Gate)-GetY()-50,125,130))) return(0);
	return(Gate);
}

global func RepliAggro(bool fOn)
{
	if(fOn)
	{
		var aRepl;
		aRepl = FindObjects(Find_ID(REPL));
		var pRepl;
		for(pRepl in aRepl)
		{
			if(pRepl) pRepl -> MachAction(3);
		}
		FindObject(REQU) -> Damage();
	}
	else
	{
		var aRepl;
		aRepl = FindObjects(Find_ID(REPL));
		var pRepl;
		for(pRepl in aRepl)
		{
			if(pRepl) if(LocalN("Action",pRepl) == 3) pRepl -> MachAction(0);
		}
		if(FindObject(REQU))
		{
			FindObject(REQU) -> Damage();
		}
	}
}
		
