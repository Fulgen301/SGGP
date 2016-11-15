

local aSuperUser, pHelper,aMoney,aBann,ATC,Temperature,NoMordet;
static ScriptOn;


/*-- Enginecallbacks --*/

protected func Initialize() 
{
	if(FindObject(Find_ID(GetID()))) RemoveObject();
	pHelper = CreateObject(HEL2);
	ScriptOn = 0;
  	return true;
}

func Activate(int iPlayer)
{
	var pCall;
	pCall = GetCursor(iPlayer);
	CreateMenu(GetID(), pCall, 0, "Infos und so");
	pCall->AddMenuItem("Info", Format("Info(%d)",iPlayer),Icon_MenuPoint);
	if(GetLeague()) return;
	if(iPlayer == 0 || IsSGGPTeamMember(iPlayer))
	{
		pCall->AddMenuItem("Einstellungen", Format("ChooseRules(%d)",iPlayer),Icon_MenuPoint);
		pCall->AddMenuItem("Spiel beenden", Format("GameOver(0)"),Icon_MenuPoint);
		if(!ScriptOn) pCall->AddMenuItem("Scripten aktivieren", "On", Icon_MenuPoint);
		else pCall->AddMenuItem("Scripten deaktivieren", "Off", Icon_MenuPoint);
	}
}


/*-- Interne Funktionen --*/

private func On() 
{
	ScriptOn = 1;
  	AddMsgBoardCmd("s","Run(\"%s\")");
	Log("<c ffcc00>Das Scripten wurde aktiviert</c>");
  	return(1);
}

global func Run(string szString)
{
	if(!ScriptOn) return;
	DebugLog("<c 838b8b>-> %s</c>",szString);
	var result = eval(szString);
	DebugLog("<c 838b8b>:: %v</c>",result);
}

private func Off() 
{
	ScriptOn = 0;
  	Log("<c ff0000>Das Scripten wurde deaktiviert</c>");
  	return(1);
}


private func Info(int iPlayer)
{
	var szString = Format("Spielernummer: <c ffcc00>%d</c>|Landschaftshöhe: <c ffcc00>%d</c>|Landschaftsbreite: <c ffcc00>%d</c>|Scripten aktiv: <c ff0000>", iPlayer, LandscapeHeight(), LandscapeWidth());
	if(ScriptOn) szString = Format("%sJa</c>", szString);
	else szString = Format("%sNein</c>", szString);
	MessageWindow(szString, iPlayer, GetID());
}

/*
#####################################################################################
#####################################################################################
########################                              ###############################
########################   Globale Hilfs-Funktionen   ###############################
########################                              ###############################
#####################################################################################
#####################################################################################
*/

/**
Casts a nuclear smoke.
*/
global func CastNuclearSmoke(int iCount)
{
	var Bob;
	Bob = -5;
	while(Bob != 8)
	{
		Bob++;
		CreateObject(NUCR,iCount,Bob*-iCount/2) -> DoCon(iCount*10);
		CreateObject(NUCR,-iCount,Bob*-iCount/2) -> DoCon(iCount*10);
		CreateObject(NUCR,0,Bob*-iCount/10) -> DoCon(iCount*10);
	}
	while(Bob != 11)
	{
		Bob++;
		CreateObject(NUCR,-iCount*6,Bob*-iCount/2) -> DoCon(iCount*10);
		CreateObject(NUCR,-iCount*4,Bob*-iCount/2) -> DoCon(iCount*10);
		CreateObject(NUCR,-iCount*2,Bob*-iCount/2) -> DoCon(iCount*10);
		CreateObject(NUCR,-iCount,Bob*-iCount/2) -> DoCon(iCount*10);
		CreateObject(NUCR,0,Bob*-iCount/2) -> DoCon(iCount*10);
		CreateObject(NUCR,iCount,Bob*-iCount/10) -> DoCon(iCount*10);
		CreateObject(NUCR,iCount*2,Bob*-iCount/2) -> DoCon(iCount*10);
		CreateObject(NUCR,iCount*4,Bob*-iCount/2) -> DoCon(iCount*10);
		CreateObject(NUCR,iCount*6,Bob*-iCount/2) -> DoCon(iCount*10);
	}
}

/**
Makes a nuclear explosion
@par iLevel The level of the exposion.
@par pTarget The object which should explode. If nil, Xplode should be called from object context.
*/

global func Xplode(iLevel,pTarget)
{
  if(!iLevel || (!pTarget && !(pTarget = this)))
  {
  	FatalError("Xplode: No target!");
  	return;
  }
  
  var pNuce;
  pNuce = CreateObject(NUCE);
  ShakeViewport(iLevel, 0, pTarget->GetX(), pTarget->GetY());
  SetPosition(pTarget->GetX(),GetY(pTarget),pNuce);
  pNuce -> BlastFree(0,0, iLevel*5);
  
  pNuce -> CastNuclearSmoke(iLevel);
  CreateParticle("NuclearBlast",0,0,0,0,iLevel * 50);
  var pDes;
  BlastObjects(pNuce->GetX(),pNuce->GetY(),iLevel * 500);
  for(pDes in FindObjects(Find_Distance(iLevel)))
  {
   if(pDes->GetOCF() & OCF_Alive)
   {
    pDes -> CreateObject(NUSK);
    pDes->Kill();
    if(pDes)
    {
     pDes -> RemoveObject();
    }
   }
   if(pDes->GetOCF() & OCF_Inflammable)
   {
    Incinerate();
   }
  }
  pTarget->RemoveObject();
  pNuce -> Rauch(iLevel);
  AddEffect("FlashPlayers", nil, 300, 10, nil,NUCE);
  Sound("Blast3");
  return;
}



global func EliminateTeam(int iTeam)
{
	var i;
	while(i != GetPlayerCount(0))
	{
		if(GetPlayerName(i))
		{
			if(GetPlayerTeam(i) == iTeam) EliminatePlayer(i);
		}
		i++;
	}
}


global func KillCrew(int iPlayer)
{
	var i=GetCrewCount(iPlayer); while (i--) GetCrew(iPlayer, i)->Kill();
}

global func CheckHelp()
{
	if(!FindObject(Find_ID(Rule_Help))) CreateObject(Rule_Help);
}

global func HelpContext(int iPlayer)
{	
	if(FindObject(Find_ID(Rule_Help)))
	{
		FindObject(Find_ID(Rule_Help)) -> Activate(iPlayer);
	}
	else
	{
		CreateObject(Rule_Help) -> Activate(iPlayer);
	}
}

public func OnClonkDeath(object pClonk, int iKiller)
{
	if(pClonk->GetOwner() == iKiller)
	{
		if(!pClonk->~IsWraith())
		{
			DoPoints(iKiller, 30, SGGP_MinusPoints);
		}
	}
	else
	{
		if(Hostile(iKiller, pClonk->GetOwner()) || pClonk->IsZombie())
		{
			DoPoints(iKiller, 50, SGGP_KillPoints);
		}
		else
		{
			DoPoints(iKiller, 80, SGGP_MinusPoints);
		}
	}
	return true;
}
local Name = "$Name$";
