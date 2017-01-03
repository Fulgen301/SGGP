#strict 2

local aSuperUser, pHelper,aMoney,aBann,Temperature,NoMordet;
static ScriptOn;


/*-- Enginecallbacks --*/

func Initialize() 
{
	CreateObject(TIME);
	aBann = CreateArray(5);
	aMoney = CreateArray(GetPlayerCount(0));
	if(FindObject(HELP)) RemoveObject();
	pHelper = CreateObject(HEL2);
  	return(1);
}

func Activate(int iPlayer)
{
	var pCall;
	pCall = GetCursor(iPlayer);
	CreateMenu(HELP, pCall, 0, 0,"Infos und so", 0, 1,1);
	AddMenuItem("Info", Format("Info(%d)",iPlayer),MEPU, pCall);
	if(GetLeague()) return;
	if(iPlayer == 0 || IsSGGPTeamMember(iPlayer))
	{
		AddMenuItem("Einstellungen", Format("ChooseRules(%d)",iPlayer),MEPU, pCall);
		if(!NoMordet)AddMenuItem("Beitritt deaktivieren", Format("NoMore(0)"),MEPU, pCall);
		if(NoMordet)AddMenuItem("Beitritt aktivieren", Format("AnyMore(0)"),MEPU, pCall);
		AddMenuItem("Spiel beenden", Format("GameOver(0)"),MEPU, pCall);
		if(!ScriptOn) AddMenuItem("Scripten aktivieren", "On", MEPU, pCall);
		if(ScriptOn) AddMenuItem("Scripten deaktivieren", "Off", MEPU, pCall);
	}
}

protected func Activate(int iPlr)
{
	//return _inherited(iPlr, ...);
	
	var pUser = GetCursor(iPlr);
	if(!pUser) return;
	
	CreateMenu(HELP, pUser, 0, C4MN_Extra_None, GetName(), 0, C4MN_Style_Dialog);
	
	// Info
	AddMenuItem("$Info$", 0, NONE, pUser);
	AddMenuItem(Format("$PlayerNumber$", iPlr), 0, NONE, pUser);
	if(ScriptOn) AddMenuItem(Format("$ScriptIsActive$", "$Yes$"), 0, NONE, pUser);
	else AddMenuItem(Format("$ScriptIsActive$", "$No$"), 0, NONE, pUser);
	if(GetLeague() || (iPlr && !IsSGGPTeamMember(iPlr))) return;
	// Blankline
	AddMenuItem(" ", 0, NONE, pUser);
	
	// Settings
	if(ScriptOn) AddMenuItem("$DeactivateScript$", "Off", MEPU, pUser);
	else AddMenuItem("$ActivateScript$", "On", MEPU, pUser);
	
	AddMenuItem("$Rules$", Format("Regeln(%d)",iPlr), MEPU, pUser);
	AddMenuItem("$Environment$", Format("Umwelt(%d)", iPlr), MEPU, pUser);
}
/*-- Interne Funktionen --*/

private func On() 
{
	ScriptOn = 1;
  	AddMsgBoardCmd("s","Run(\"%s\")",0);
	Log("<c ffcc00>Das Scripten wurde aktiviert</c>");
  	return(1);
}

global func Run(string szString)
{
	Log("<c 838b8b>-> %s</c>",szString);
	if(!ScriptOn) 
	{
		Log("<c 838b8b>:: Scripten Deaktiviert!</c>");
		return(0);
	}
	var result;
	result = eval(szString);
	Log("<c 838b8b>:: %v</c>",result);
}

private func Off() 
{
	ScriptOn = 0;
  	Log("<c ff0000>Das Scripten wurde deaktiviert</c>");
  	return(1);
}

/*
#####################################################################################
#####################################################################################
########################                          ###################################
########################   Regelwahl-Funktionen   ###################################
########################                          ###################################
#####################################################################################
#####################################################################################
*/

func ChooseRules(int iPlayer)
{
	
	CloseMenu(pCaller);
	Sound("Connect");
	var pCaller;
	pCaller = GetCursor(iPlayer);
	CreateMenu(GetID(this(0)), pCaller, 0, 0,"Einstellungen", 0, 1,1);
	AddMenuItem("Regeln", Format("Regeln(%d)",GetOwner(pCaller)), MEPU, pCaller);
	AddMenuItem("Ziele", Format("Ziele(%d)",GetOwner(pCaller)), MEPU, pCaller);
	AddMenuItem("Umwelt", Format("Umwelt(%d)",GetOwner(pCaller)),MEPU, pCaller);
	AddMenuItem("Baupläne", Format("Bauplane(%d)",GetOwner(pCaller)), MEPU, pCaller);
	
	return(1);
}	

func Umwelt(pCall)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	
	CloseMenu(pCaller);
	CreateMenu(EGRS, pCaller, 0, 0,"Umweltobjekte", 0, 1,1,103);
	AddMenuItem("Regen", Format("Regen(%d)",GetOwner(pCaller),GetMenuSelection(pCaller)), MEPU, pCaller);
	AddMenuItem("Meteoriten", Format("Meteoriten(%d)",GetOwner(pCaller),GetMenuSelection(pCaller)), MEPU, pCaller);
	AddMenuItem("Objekte im Erdreich", Format("Objekte(%d)",GetOwner(pCaller),GetMenuSelection(pCaller)), MEPU, pCaller);
	AddMenuItem("Temperatur", Format("Temperatur(%d)",GetOwner(pCaller),GetMenuSelection(pCaller)), MEPU, pCaller);
	AddMenuItem("Fertig", Format("ChooseRules(%d)",GetOwner(pCaller)), MEPU, pCaller);
	
}

func Bauplane(pCall,iSelection)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	CreateMenu(HUT2, pCaller, 0, 0,"Baupläne", 0, 1,1,104);
	var i;
	var idObjekt;
	while(idObjekt = GetDefinition (i,128))
	{
		if(GetPlrKnowledge(0,idObjekt)) AddMenuItem(Format("<c ff0000>%s löschen</c>",GetName(0,idObjekt)), Format("Building(%i,%d)",idObjekt,GetOwner(pCaller),GetCursor(pCall) -> GetMenuSelection(0)), idObjekt, pCaller);
		if(!GetPlrKnowledge(0,idObjekt)) AddMenuItem(Format("<c 00ff00>%s hinzufügen</c>",GetName(0,idObjekt)), Format("Building(%i,%d)",idObjekt,GetOwner(pCaller),GetCursor(pCall) -> GetMenuSelection(pCaller)), idObjekt, pCaller);
		i++;
	}
	AddMenuItem("Fertig", Format("ChooseRules(%d)",GetOwner(pCaller)), GOLD, pCaller);
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
}

func Ziele(pCall)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	CreateMenu(MEL2, pCaller, 0, 0,"Ziele", 0, 1,1,101);
	var i;
	var idGoal;
	while(idGoal = GetDefinition (i, C4D_Goal))
	{
		if(FindObject(idGoal)) AddMenuItem(Format("<c ff0000>%s löschen</c>",GetName(0,idGoal)), Format("Goal(%i,%d)",idGoal,GetOwner(pCaller),GetMenuSelection(pCaller)), idGoal, pCaller);
		if(!FindObject(idGoal)) AddMenuItem(Format("<c 00ff00>%s hinzufügen</c>",GetName(0,idGoal)), Format("Goal(%i,%d)",idGoal,GetOwner(pCaller),GetMenuSelection(pCaller)), idGoal, pCaller);
		i++;
	}
	AddMenuItem("Fertig", Format("ChooseRules(%d)",GetOwner(pCaller)), GOLD, pCaller);
}

func Regeln(pCall)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	CreateMenu(ENRG, pCaller, 0, 0,"Spielregeln", 0, 1,1,102);
	var i;
	var idRule;
	while(idRule = GetDefinition (i, C4D_Rule))
	{
		if(FindObject(idRule)) AddMenuItem(Format("<c ff0000>%s löschen</c>",GetName(0,idRule)), Format("Rule(%i,%d)",idRule,GetOwner(pCaller),GetMenuSelection(pCaller)), idRule, pCaller);
		if(!FindObject(idRule)) AddMenuItem(Format("<c 00ff00>%s hinzufügen</c>",GetName(0,idRule)), Format("Rule(%i,%d)",idRule,GetOwner(pCaller),GetMenuSelection(pCaller)), idRule, pCaller);
		i++;
	}
	AddMenuItem("Fertig", Format("ChooseRules(%d)",GetOwner(pCaller)), MEPU, pCaller);
}
/*-- SubSubMenus --*/

func Objekte(pCall)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	
	CloseMenu(pCaller);
	CreateMenu(FLNT, pCaller, 0, 0,"Objekte im Erdreich", 0, 1,1,133);
	var i;
	var idObjekt;
	while(idObjekt = GetDefinition (i, 16384))
	{
		if(FindObject(idObjekt)) AddMenuItem(Format("<c ff0000>%s löschen</c>",GetName(0,idObjekt)), Format("Objegt(%i,%d)",idObjekt,GetOwner(pCaller),GetMenuSelection(pCaller)), idObjekt, pCaller);
		if(!FindObject(idObjekt)) AddMenuItem(Format("<c 00ff00>%s hinzufügen</c>",GetName(0,idObjekt)), Format("Objegt(%i,%d)",idObjekt,GetOwner(pCaller),GetMenuSelection(pCaller)), idObjekt, pCaller);
		i++;
	}
	AddMenuItem("Fertig", Format("Umwelt(%d)",GetOwner(pCaller)), MEPU, pCaller);
	
}
 
func Regen(pCall)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	
	CloseMenu(pCaller);
	CreateMenu(0, pCaller, 0, 0,Format("%d Regen",ObjectCount(FXP1)), 0, 1,1,131);
	AddMenuItem("Mehr", "RainUp", MEPU, pCaller);
	AddMenuItem("Weniger", "RainDown", MEPU, pCaller);
	AddMenuItem("Fertig", Format("Umwelt(%d)",GetOwner(pCaller)), MEPU, pCaller);
	
}

func Temperatur(pCall)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	
	CloseMenu(pCaller);
	CreateMenu(ICE1, pCaller, 0, 0,Format("%d Temperatur",Temperature), 0, 1,1,131);
	AddMenuItem("Mehr", "ClimUp", MEPU, pCaller);
	AddMenuItem("Weniger", "ClimDown", MEPU, pCaller);
	AddMenuItem("Fertig", Format("Umwelt(%d)",GetOwner(pCaller)), MEPU, pCaller);
	
}

func Meteoriten(pCall)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	
	CloseMenu(pCaller);
	CreateMenu(MTRG, pCaller, 0, 0,Format("%d Meteoriten",ObjectCount(METR)), 0, 1,1,132);
	AddMenuItem("Mehr", "MeteoUp", MEPU, pCaller);
	AddMenuItem("Weniger", "MeteoDown", MEPU, pCaller);
	AddMenuItem("Fertig", Format("Umwelt(%d)",GetOwner(pCaller)), MEPU, pCaller);
	
}

/*-- Befehle --*/
 
func Goal(id idGoal,pCall,iSelection)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	iSelection = GetMenuSelection(pCaller);
	
	CloseMenu(pCaller);
	if(FindObject(idGoal)) 
	{
		Message("{{%i}} <c ffcc00>%s Entfernt</c>",0,idGoal,GetName(0,idGoal));
		RemoveAll(idGoal);
		Ziele(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return(0);
	}
	else
	{
		Message("{{%i}} <c ffcc00>%s Hinzugefügt</c>",0,idGoal,GetName(0,idGoal));
		CreateObject(idGoal);
		Ziele(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return(0);
	}
}

func Rule(id idRule,pCall,iSelection)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	iSelection = GetMenuSelection(pCaller);
	
	CloseMenu(pCaller);
	if(FindObject(idRule)) 
	{
		Message("{{%i}} <c ffcc00>%s Entfernt</c>",0,idRule,GetName(0,idRule));
		RemoveAll(idRule);
		Regeln(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return(0);
	}
	else
	{
		Message("{{%i}} <c ffcc00>%s Hinzugefügt</c>",0,idRule,GetName(0,idRule));
		CreateObject(idRule);
		Regeln(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return(0);
	}
}

func Objegt(id idObject,pCall,iSelection)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	iSelection = GetMenuSelection(pCaller);
	
	CloseMenu(pCaller);
	
	if(FindObject(idObject)) 
	{
		Message("{{%i}} <c ffcc00>%s Entfernt</c>",0,idObject,GetName(0,idObject));
		RemoveAll(idObject);
		Objekte(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return(0);
	}
	else
	{
		Message("{{%i}} <c ffcc00>%s Hinzugefügt</c>",0,idObject,GetName(0,idObject));
		PlaceObjects(idObject,50,"GBackSemiSolid");
		Objekte(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return(0);
	}
}

func Building(id idObject,pCall,iSelection)
{
	
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	iSelection = GetMenuSelection(pCaller);
	
	CloseMenu(pCaller);
	
	var i;
	while(i < GetPlayerCount(0))
	{
		if(GetPlrKnowledge(i,idObject)) 
		{
			Message("{{%i}} <c ffcc00>%s Nicht Baubar</c>",0,idObject,GetName(0,idObject));
			SetPlrKnowledge(i,idObject,1);
			Bauplane(GetOwner(pCaller));
			GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		}
		else
		{
			Message("{{%i}} <c ffcc00>%s Baubar</c>",0,idObject,GetName(0,idObject));
			SetPlrKnowledge(i,idObject,0);
			Bauplane(GetOwner(pCaller),iSelection);
		}
		i++;
	}
}

func MeteoDown()
{
	Message("{{METR}} <c ffcc00>Weniger Meteoriten</c>");
	Sound("Connect");
	if(FindObject(METR)) RemoveObject(FindObject(METR));
}

func MeteoUp()
{
	Message("{{METR}} <c ffcc00>Mehr Meteoriten</c>");
	Sound("Connect");
	CreateObject(METR);
}

func RainUp()
{
	Message("{{FXP1}} <c ffcc00>Mehr Regen</c>");
	Sound("Connect");
	CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Water"),LandscapeWidth()-10,10000);
}

func RainDown()
{
	Sound("Connect");
	Message("{{FXP1}} <c ffcc00>Weniger Regen</c>");
	if(FindObject(FXP1))RemoveObject(FindObject(FXP1));
}

func ClimDown()
{
	Sound("Connect");
	Message("{{ICE1}} <c ffcc00>Kälter</c>");
	Temperature--;
}

func ClimUp()
{
	Sound("Connect");
	Message("{{ICE1}} <c ffcc00>Wärmer</c>");
	Temperature++;
}

/*
#####################################################################################
#####################################################################################
########################                               ##############################
########################   Relaunchsystem-Funktionen   ##############################
########################                               ##############################
#####################################################################################
#####################################################################################
*/

/*
#####################################################################################
#####################################################################################
########################                              ###############################
########################   Globale Hilfs-Funktionen   ###############################
########################                              ###############################
#####################################################################################
#####################################################################################
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

global func Xplode(iLevel,pTarget)
{
  if(!iLevel)
  {
   return(1);
  }

  if(!pTarget)
  {
   return(1);
  }
  var pNuce;
  pNuce = CreateObject(NUCE);
  ShakeViewPort(iLevel, 0, GetX(pTarget), GetY(pTarget));
  SetPosition(GetX(pTarget),GetY(pTarget),pNuce);
  pNuce -> BlastFree(0,0, iLevel*5);
  
  pNuce -> CastNuclearSmoke(iLevel);
  CreateParticle("NuclearBlast",0,0,0,0,iLevel * 50);
  var pDes;
  BlastObjects(GetX(pNuce),GetY(pNuce),iLevel * 500);
  for(pDes in FindObjects(Find_Distance(iLevel)))
  {
   if(GetOCF(pDes) & OCF_Alive)
   {
    pDes -> CreateObject(NUSK);
    Kill(pDes);
    if(pDes)
    {
     pDes -> RemoveObject();
    }
   }
   if(GetOCF(pDes) & OCF_Inflammable)
   {
    Incinerate(pDes);
   }
  }
  pTarget->RemoveObject();
  pNuce -> Rauch(iLevel);
  AddEffect("FlashPlayers", 0, 300, 10, 0,NUCE);
  Sound("Blast3");
  return(1);
}

global func AddToArray(What,array& Arr)
{
	SetLength(Arr,GetLength(Arr)+1);
	Arr[GetLength(Arr)] = What;
	return(GetLength(Arr));
}

global func RemoveFromArray(What,array& Arr)
{
	var i;
	i = 0;
	while(Arr[i] != What)
	{
		if(GetLength(Arr) == i) return(0);
		i++;
	}
	if(Arr[i] == What) Arr[i] = 0;
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
	var i=GetCrewCount(iPlayer); while (i--) Kill(GetCrew(iPlayer, i));
}

global func CheckHelp()
{
	if(!FindObject(HELP)) CreateObject(HELP);
}

global func MatVert(string szMaterial,int iX,int iWidth)
{
	DrawMaterialQuad(szMaterial,iX,0,iX+iWidth,0,iX+iWidth,LandscapeHeight(),iX,LandscapeHeight(),1);
	return(1);
}

global func MatHori(string szMaterial,int iY,int iWidth)
{
	DrawMaterialQuad(szMaterial,0,iY,LandscapeWidth(),iY,LandscapeWidth(),iY+iWidth,0,iY+iWidth);
	return(1);
}

global func MatQuad(string szMaterial,int iX,int iY,int iWidth,int iHeigth)
{
	DrawMaterialQuad(szMaterial,iX,iY,iX+iWidth,iY,iX+iWidth,iY+iHeigth,iX,iY+iHeigth,1);
	return(1);
}


global func HelpContext(int iPlayer)
{	
	if(FindObject(HELP))
	{
		FindObject(HELP) -> Activate(iPlayer);
	}
	else
	{
		CreateObject(HELP) -> Activate(iPlayer);
	}
}
/*
#####################################################################################
#####################################################################################
#########################                      ######################################
#########################   Timer-Funktionen   ######################################
#########################                      ######################################
#####################################################################################
#####################################################################################
*/


global func SetTime(int iMinutes,int iSecounds)
{
	CheckHelp(0);
	var pTimer;
	pTimer = FindObject(TIMR);
	if(!pTimer) pTimer = CreateObject(TIMR);
	LocalN("iMinute",pTimer) = iMinutes;
	LocalN("iSecound",pTimer) = iSecounds;
	return(1);
}

global func ChangeTimerCount(int iC)
{
	CheckHelp(0);
	var pTimer;
	pTimer = FindObject(TIMR);
	if(!pTimer) pTimer = CreateObject(TIMR);
	LocalN("Count",pTimer) = iC;
}

public func OnClonkDeath(object pClonk, int iKiller)
{
	var melee = GameCall("IsMelee");
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