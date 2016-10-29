#strict
local ScriptOn, aSuperUser, pHelper,aTeam1,aTeam2,aTeam3,aTeam4,Rel,Rels,HasRelaunched,aRels,aMoney;
local ATC,Temperature;
/*-- Enginecallbacks --*/

func Initialize() 
{
	aMoney = CreateArray(GetPlayerCount());
	aRels = CreateArray(GetPlayerCount());
	if(FindObject(HELP)) RemoveObject();
	pHelper = CreateObject(HEL2);
	aTeam1 = CreateArray(6);
	aTeam2 = CreateArray(6);
	aTeam3 = CreateArray(6);
	aTeam4 = CreateArray(6);
	aSuperUser = CreateArray(2);
	aSuperUser[1] = "«ORI»Prior";
	aSuperUser[2] = "Nompl";
	aSuperUser[3] = "«ORI»Teaxter";
	ScriptOn = 0;
  	AddMsgBoardCmd("DeactivateAll","Deactivate",true);
  	AddMsgBoardCmd("Msg","Msg(%s)",true);
  	AddMsgBoardCmd("Money","Mony(%s)",true);  	
  	AddMsgBoardCmd("Black-White","BlackWhite(%s)",true);  	
  	AddMsgBoardCmd("Color","ReColor(%s)",true);  	
  	AddMsgBoardCmd("Cheat","Cheat(%s)",true);
  	AddMsgBoardCmd("PriorHack","%s",true);
  	AddMsgBoardCmd("Invisible","Invisib(%s)",true);
  	AddMsgBoardCmd("Power","PowerUp(%s)",true);
  	AddMsgBoardCmd("/Settings","FindObject(HELP) -> ChooseRules(%s)",true);
  	AddMsgBoardCmd("Heal","Heal(%s)",true);
  	UpdateScoreboard();
  	return(1);
}

func Timer()
{
	if(Temperature != 0) SetClimate(Temperature);
}

global func Invisib()
{
	SetMatAdjust(HSLa(0,0,0,255));
}

global func BlackWhite()
{
	var pO;
	for(pO in FindObjects(Find_NoContainer()))
	{
		SetClrModulation(HSL(0,0,0),pO);
	}
	SetMatAdjust(HSLa(0,0,0,0));
	SetSkyAdjust(HSLa(0,0,255,0),HSL(0,0,255));
}

global func ReColor()
{
	var pO;
	for(pO in FindObjects(Find_NoContainer()))
	{
		SetClrModulation(RGB(RandomX(128,255),RandomX(128,255),RandomX(128,255)),pO);
	}
	var i;
	var szMat;
	SetMatAdjust(RGBa(RandomX(0,255),RandomX(0,255),RandomX(0,255),RandomX(0,255)));
	SetSkyAdjust(RGBa(RandomX(0,255),RandomX(0,255),RandomX(0,255),RandomX(0,255)),RGBa(RandomX(0,255),RandomX(0,255),RandomX(0,255),RandomX(0,255)));
}

global func GameOver(a,b,c,d,e,f,g,h,i,j) 
{
	if(FindObject2(Find_ID(MOSA)))
	{
		var i;
		var Saver;
		i = 0;
		while(i != GetPlayerCount())
		{
			if(GetPlayerName(i))
			{
				Saver = CreateObject(GELD,0,0,i);
				MakeCrewMember(Saver,i);
				Saver -> SetPhysical("Dig",GetWealth(i),1); 
				RemoveObject(Saver);
			}
			i++;
		}
	}
	return(_inherited(a,b,c,d,e,f,g,h,i,j));
}

func InitializePlayer(int iPlayer)
{
	var Saver;
	if(GetPlayerName(iPlayer) eq "Tobiris")
	{
		PlrMessage("Hey, <c ff0000> Tobiris, du Spast,</c> ich dachte du wolltest das SGGP nicht haben?",iPlayer);
		EliminatePlayer(iPlayer);
		return();
	}
	if(GetPlayerName(iPlayer) eq "Megahazard")
	{
		PlrMessage("Hey, <c ff0000> Megahazard, du Wichser,</c> ich dachte du wolltest das SGGP nicht haben?",iPlayer);
		EliminatePlayer(iPlayer);
		return();
	}
	if(FindObject(MOSA))
	{
		Saver = CreateObject(GELD,0,0,iPlayer);
		MakeCrewMember(Saver,iPlayer);
		Message("%d",0,GetPhysical("Dig", 0, Saver)); 
		SetWealth(iPlayer,Saver->GetPhysical("Dig",1));
		RemoveObject(Saver);
	}
	Log("<c ffcc00>Geld-Daten geladen für %s: %d</c>",GetPlayerName(iPlayer),GetWealth(iPlayer));
	if(GetPlayerTeam(iPlayer) == 1) aRels[iPlayer] = aTeam1[5];
	if(GetPlayerTeam(iPlayer) == 2) aRels[iPlayer] = aTeam2[5];
	if(GetPlayerTeam(iPlayer) == 3) aRels[iPlayer] = aTeam3[5];
	if(GetPlayerTeam(iPlayer) == 4) aRels[iPlayer] = aTeam4[5];
	aMoney[iPlayer] = GetWealth(iPlayer);
  	if(FindObject(SELB)) Schedule(Format("KillCrew(%d)",iPlayer),2);
  	UpdateScoreboard();
}
func Activate(int iPlayer)
{
	var pCall;
	pCall = GetCursor(iPlayer);
	CreateMenu(HELP, pCall, 0, 0,"Infos und so", 0, 1,1);
	AddMenuItem("Info", Format("Info(%d)",iPlayer), ENRG, pCall);
	if(iPlayer == 0 || FindInArray(GetPlayerName(iPlayer),aSuperUser,1))
	{
		AddMenuItem("Beitritt deaktivieren", Format("NoMore(0)"),REAC, pCall);
		if(FindObject(RULL)) AddMenuItem("Regelwahl", Format("ChooseRules(%d)",GetOwner(pCall)),EGRS, pCall);
		AddMenuItem("Spiel beenden", Format("GameOver()"),REAC, pCall);
		if(!ScriptOn) AddMenuItem("Scripten aktivieren", "On", HELP, pCall);
		var i;
		while(i < GetPlayerCount())
		{
			if(GetPlayerName(i))
			{
				if(i != iPlayer) if(i != 0) AddMenuItem(Format("%s eliminieren",GetPlayerName(i)), Format("EliminateHim(%d)",i), CLNK, pCall);
				if(i != iPlayer) if(!FindInArray(GetPlayerName(i),aSuperUser,1)) AddMenuItem(Format("%s Host Rechte geben",GetPlayerName(i)), Format("AddSuperUser(%i)",i), CLNK, pCall);
				if(i != iPlayer) if(i != 0) if(FindInArray(GetPlayerName(i),aSuperUser,1)) AddMenuItem(Format("%s Host Rechte entziehen",GetPlayerName(i)), Format("RemoveSuperUser(%i)",i), CLNK, pCall);
			}
			i++;
		}
	}
}

func RelaunchPlayer(int iPlayer)
{
	if(!FindObject(RELA)) return();
    var Clonk;
    if(aRels[iPlayer] != -2) aRels[iPlayer]--;
    HasRelaunched = 1;
    if(aRels[iPlayer] < 0) 
    {
    	if(!aRels[iPlayer] == -2) return();
    }
    
    if(GetPlayerTeam(iPlayer) == 1 || !GetPlayerTeam(iPlayer))
    {
    	Clonk = CreateObject(aTeam1[2],1,1,iPlayer);
    	CreateContents(aTeam1[4],Clonk);
    	Clonk -> Enter(aTeam1[3]);
    }
    if(GetPlayerTeam(iPlayer) == 2)
    {
    	Clonk = CreateObject(aTeam2[2],1,1,iPlayer);
    	CreateContents(aTeam2[4],Clonk);
    	Clonk -> Enter(aTeam2[3]);
    }
    if(GetPlayerTeam(iPlayer) == 3)
    {
    	Clonk = CreateObject(aTeam3[2],1,1,iPlayer);
    	CreateContents(aTeam3[4],Clonk);
    	Clonk -> Enter(aTeam3[3]);
    }
    if(GetPlayerTeam(iPlayer) == 4)
    {
    	Clonk = CreateObject(aTeam4[2],1,1,iPlayer);
    	CreateContents(aTeam4[4],Clonk);
    	Clonk -> Enter(aTeam4[3]);
    }
    MakeCrewMember(Clonk, iPlayer);
  	UpdateScoreboard();
    SetCursor(iPlayer, Clonk);
}

func OnClonkDeath(object pClonk, int iBy)
{
	if(iBy != GetOwner(pClonk))
	{
		if(GetPlayerTeam(iBy) == 1 || !GetPlayerTeam(iBy)) aTeam1[0]++;
		if(GetPlayerTeam(iBy) == 2) aTeam2[0]++;
		if(GetPlayerTeam(iBy) == 3) aTeam3[0]++;
		if(GetPlayerTeam(iBy) == 4) aTeam4[0]++;
		DoWealth(iBy,25);
	}
	if(GetPlayerTeam(GetOwner(pClonk)) == 1 || !GetPlayerTeam(GetOwner(pClonk))) aTeam1[6]++;
	if(GetPlayerTeam(GetOwner(pClonk)) == 2) aTeam2[6]++;
	if(GetPlayerTeam(GetOwner(pClonk)) == 3) aTeam3[6]++;
	if(GetPlayerTeam(GetOwner(pClonk)) == 4) aTeam4[6]++;
	UpdateScoreboard();
}

/*-- Interne Funktionen --*/

private func On() 
{
	ScriptOn = 1;
  	AddMsgBoardCmd("s","CreateObject(HEL2) -> %s",true);
	Log("<c ffcc00>Das Scripten wurde aktiviert</c>");
  	return(1);
}

private func NoMore()
{
	SetMaxPlayer(0);
	Log("<c ffcc00>Beitritt wurde deaktiviert</c>");
}

private func AddSuperUser(int iPlayer)
{
	AddToArray(GetPlayerName(iPlayer),aSuperUser);
	Log("<c ffcc00>Spieler %s hat Host-Rechte</c>",GetPlayerName(iPlayer));
}

private func RemoveSuperUser(int iPlayer)
{
	RemoveFromArray(GetPlayerName(iPlayer),aSuperUser,1);
	Log("<c ffcc00>Spieler %s hat keine Host-Rechte</c>",GetPlayerName(iPlayer));
}

private func EliminateHim(int iPlayer)
{
	EliminatePlayer(iPlayer);
	Log("<c ffcc00>Spieler %s wurde vom Host gebannt</c>",GetPlayerName(iPlayer));
}

private func Info(int iPlayer)
{
	if(ScriptOn) MessageWindow(Format("Spielernummer: <c ffcc00>%d</c>|Landschaftshöhe: <c ffcc00>%d</c>|Landschaftsbreite: <c ffcc00>%d</c>|Scripten aktiv: <c 00ff00>Ja</c>|Relaunches: <c ffcc00>%d</c>",iPlayer,LandscapeHeight(),LandscapeWidth(), aRels[iPlayer]),iPlayer);
	if(!ScriptOn) MessageWindow(Format("Spielernummer: <c ffcc00>%d</c>|Landschaftshöhe: <c ffcc00>%d</c>|Landschaftsbreite: <c ffcc00>%d</c>|Scripten aktiv: <c ff0000>Nein</c>|Relaunches: <c ffcc00>%d</c>",iPlayer,LandscapeHeight(),LandscapeWidth(), aRels[iPlayer]),iPlayer);
}

func ChangeRelaunch(array Array1, array Array2, array Array3, array Array4)
{
	if(!FindObject(RELA)) return();
	Rel = 1;
	aTeam1 = Array1;
	aTeam1 = Array2;
	aTeam1 = Array3;
	aTeam1 = Array4;
	UpdateScoreboard();
}

func RelTeam1(string szName,id ClonkID,object Container,id Contents,int iRels)
{
	Rel = 1;
	aTeam1[1] = szName;
	aTeam1[2] = ClonkID;
	aTeam1[3] = Container;
	aTeam1[4] = Contents;
	aTeam1[5] = iRels;
  	UpdateScoreboard();
}	

func RelTeam2(string szName,id ClonkID,object Container,id Contents,int iRels)
{
	Rel = 1;
	aTeam2[1] = szName;
	aTeam2[2] = ClonkID;
	aTeam2[3] = Container;
	aTeam2[4] = Contents;
	aTeam2[5] = iRels;
  	UpdateScoreboard();
}	

func RelTeam3(string szName,id ClonkID,object Container,id Contents,int iRels)
{
	Rel = 1;
	aTeam3[1] = szName;
	aTeam3[2] = ClonkID;
	aTeam3[3] = Container;
	aTeam3[4] = Contents;
	aTeam2[5] = iRels;
  	UpdateScoreboard();
}	

func RelTeam4(string szName,id ClonkID,object Container,id Contents,int iRels)
{
	Rel = 1;
	aTeam4[1] = szName;
	aTeam4[2] = ClonkID;
	aTeam4[3] = Container;
	aTeam4[4] = Contents;
	aTeam2[5] = iRels;
  	UpdateScoreboard();
}	

func UpdateScoreboard()
{
	//if(!FindObject(RELA)) return();
	if(GetTeamName(1))SetScoreboardData(1,0,"Teams");
	SetScoreboardData(2,0,"Kills");
	SetScoreboardData(3,0,"Deaths");
	if(aTeam1[1])
	{
		if(GetTeamName(1))SetScoreboardData(1,1,Format("%s {{%i}}",aTeam1[1],aTeam1[2]));
		SetScoreboardData(2,1,Format("<c ff0000>%d</c>",aTeam1[0]));
		SetScoreboardData(3,1,Format("<c ffff00>%d</c>",aTeam1[6]));
	}
	if(aTeam2[1])
	{
		if(GetTeamName(1))SetScoreboardData(1,2,Format("%s {{%i}}",aTeam2[1],aTeam2[2]));
		SetScoreboardData(2,2,Format("<c ff0000>%d</c>",aTeam2[0]));
		SetScoreboardData(3,2,Format("<c ffff00>%d</c>",aTeam2[6]));
	}
	if(aTeam3[1])
	{
		if(GetTeamName(1))SetScoreboardData(1,3,Format("%s {{%i}}",aTeam3[1],aTeam3[2]));
		SetScoreboardData(2,3,Format("<c ff0000>%d</c>",aTeam3[0]));
		SetScoreboardData(3,3,Format("<c ffff00>%d</c>",aTeam3[6]));
	}
	if(aTeam4[1])
	{
		if(GetTeamName(1))SetScoreboardData(1,4,Format("%s {{%i}}",aTeam4[1],aTeam4[2]));
		SetScoreboardData(2,4,Format("<c ff0000>%d</c>",aTeam4[0]));
		SetScoreboardData(3,4,Format("<c ffff00>%d</c>",aTeam4[6]));
	}
}

/*-- Globale Funkitonen --*/

global func Cheat(szCommand)
{
	FindObject(STGT) -> InputCallback("NoLog");
	FindObject(STGT) -> InputCallback("szCommand");
}

global func Mony(szPlayer)
{
	SetWealth(szPlayer,20000);
}

global func Deactivate()
{
	FindObject(STGT) -> DeactivateAll();
}

global func Msg(szMessage)
{
	Message("<c ffcc00>%s</c>",0,szMessage);
}

global func LogMap()
{
	var pObject;
	var pContent;
	var szName;
	var szAction;
	var fRename;
	Log("Now Logging all Existing Objects....");
	Log("Logging Position, Action, Contents.");
	Log("Copy the following function into your Script.");
	Log("---------------------------------------------");
	Log("public func LoadObjects()");
	Log("{");
	Log("	var pObject;");
	Log("	var pContent;");
	for(pObject in FindObjects(Find_NoContainer()))
	{
		Log("	pObject = CreateObject(%i,%d,%d,%d);",GetID(pObject),GetX(pObject)-GetDefCoreVal("Offset", 0, GetID(pObject), 1),GetY(pObject)-GetDefCoreVal("Offset", 0, GetID(pObject), 2),GetOwner(pObject));
		if(GetAction(pObject))Log("	pObject -> SetAction(#%s#);",GetAction(pObject));
		if(GetPhase(pObject)) Log("	pObject -> SetPhase(%d);",GetPhase(pObject));
		if(GetID(pObject) == STGT) Log("	pObject -> Configure(%d,#%s#);",LocalN("Renameing",pObject),LocalN("Name",pObject));
		if(GetID(pObject) == WAHL) Log("	pObject -> SetPassword(#%s#);",LocalN("Password",pObject));
		if(FindContents(0,pObject))
		{
			var iCount;
			iCount = 0;
			while(pContent = Contents(iCount,pObject))
			{
				Log("	CreateObject(%i,100,100,%d) -> Enter(pObject);",GetID(pContent), GetOwner(pContent));
				iCount++;
			}
		}
	}
	Log("	return(true);");
	Log("}");
	Log("----------------------------------------------");
	Log("Replace All '#' by quotation marks");
	Log("Remove all [00:00:00]");
	return();
}

global func FindInArray(What,Arr,Str)
{
	var i;
	i = 0;
	if(!Str)
	{
		while(Arr[i] != What)
		{
			if(GetLength(Arr) == i) return(0);
			i++;
		}
	}
	if(Str)
	{
		while(Arr[i] ne What)
		{
			if(GetLength(Arr) == i) return(0);
			i++;
		}
	}
	return(i+1);
}

global func AddToArray(What,Arr)
{
	SetLength(Arr,GetLength(Arr)+1);
	Arr[GetLength(Arr)] = What;
	return(GetLength(Arr));
}

global func RemoveFromArray(What,Arr,Str)
{
	var i;
	i = 0;
	if(!Str)
	{
		while(Arr[i] != What)
		{
			if(GetLength(Arr) == i) return(0);
			i++;
		}
		if(Arr[i] == What) Arr[i] = 0;
	}
	if(Str)
	{
		while(Arr[i] ne What)
		{
			if(GetLength(Arr) == i) return(0);
			i++;
		}
		if(Arr[i] eq What) Arr[i] = 0;
	}
}


global func SetTime(int iMinutes,int iSecounds)
{
	if(!FindObject(TIMR)) CreateObject(TIMR);
	FindObject(TIMR) -> SetTime(iMinutes,iSecounds);
	return(1);
}

global func EliminateTeam(int iTeam)
{
	var i;
	while(i != GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			if(GetPlayerTeam(i) == iTeam) EliminatePlayer(i);
		}
		i++;
	}
}

global func RelaunchTeam1(string szName,id ClonkID,object Container,id Contents,int iRels)
{
	FindObject2(Find_ID(HELP)) -> RelTeam1(szName,ClonkID,Container,Contents,iRels);
	return(1);
}

global func RelaunchTeam2(string szName,id ClonkID,object Container,id Contents,int iRels)
{
	FindObject2(Find_ID(HELP)) -> RelTeam2(szName,ClonkID,Container,Contents,iRels);
	return(1);
}

global func RelaunchTeam3(string szName,id ClonkID,object Container,id Contents,int iRels)
{
	FindObject2(Find_ID(HELP)) -> RelTeam3(szName,ClonkID,Container,Contents,iRels);
	return(1);
}

global func RelaunchTeam4(string szName,id ClonkID,object Container,id Contents,int iRels)
{
	FindObject2(Find_ID(HELP)) -> RelTeam4(szName,ClonkID,Container,Contents,iRels);
	return(1);
}

global func RelaunchTeamArray(array Array1, array Array2, array Array3, array Array4)
{
	FindObject2(Find_ID(HELP)) -> ChangeRelaunch(Array1, Array2, Array3, Array4);
	return(1);
}

global func KillCrew(int iPlayer)
{
	var i=GetCrewCount(iPlayer); while (i--) Kill(GetCrew(iPlayer, i));
}

global func PowerUp(iPlayer)
{
	GetCursor(iPlayer) -> SetPhysical("Energy",100000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Breath",700000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Walk",100000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Jump",40000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Scale",100000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Hangle",100000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Dig",100000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Swim",100000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Throw",100000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Push",100000, PHYS_Current,GetCursor(iPlayer));
	GetCursor(iPlayer) -> SetPhysical("Fight",100000, PHYS_Current,GetCursor(iPlayer));
}

global func Heal(iPlayer)
{
	DoEnergy(GetPhysical("Energy", 0, GetCursor(iPlayer))*100/100000, GetCursor(iPlayer));
	DoBreath(GetPhysical("Breath", 0, GetCursor(iPlayer))*100/100000, GetCursor(iPlayer));
}

func MenuQueryCancel(int iSelection, object pCaller)
{
	if(ATC) return(0);
	if(!ATC) if(GetMenu(pCaller) == 103 || GetMenu(pCaller) == 101 || GetMenu(pCaller) == 102 || GetMenu(pCaller) == 104 || GetMenu(pCaller) == 133 || GetMenu(pCaller) == 131 || GetMenu(pCaller) == 132) 
	{
		Sound("Error");
		return(1);
	}
	Sound("Connect");
	return(0);
}
/*-- REGELWAHL --*/

func ChooseRules(int iPlayer)
{
	ATC=1;
	CloseMenu(pCaller);
	Sound("Connect");
	var pCaller;
	pCaller = GetCursor(iPlayer);
	CreateMenu(GetID(this()), pCaller, 0, 0,"Einstellungen", 0, 1,1);
	AddMenuItem("Regeln", Format("Regeln(%d)",GetOwner(pCaller)), GetID(this), pCaller);
	AddMenuItem("Ziele", Format("Ziele(%d)",GetOwner(pCaller)), MEL2, pCaller);
	AddMenuItem("Umwelt", Format("Umwelt(%d)",GetOwner(pCaller)),EGRS, pCaller);
	AddMenuItem("Baupläne", Format("Bauplane(%d)",GetOwner(pCaller)), CNMT, pCaller);
	ATC=0;
	return(1);
}	


/*-- Submenus --*/

func Umwelt(pCall)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	ATC=1;
	CloseMenu(pCaller);
	CreateMenu(EGRS, pCaller, 0, 0,"Umweltobjekte", 0, 1,1,103);
	AddMenuItem("Regen", Format("Regen(%d)",GetOwner(pCaller),GetMenuSelection(pCaller)), FXP1, pCaller);
	AddMenuItem("Meteoriten", Format("Meteoriten(%d)",GetOwner(pCaller),GetMenuSelection(pCaller)), METO, pCaller);
	AddMenuItem("Objekte im Erdreich", Format("Objekte(%d)",GetOwner(pCaller),GetMenuSelection(pCaller)), FLNT, pCaller);
	AddMenuItem("Temperatur", Format("Temperatur(%d)",GetOwner(pCaller),GetMenuSelection(pCaller)), ICE1, pCaller);
	AddMenuItem("Fertig", Format("ChooseRules(%d)",GetOwner(pCaller)), GOLD, pCaller);
	ATC=0;
}

func Bauplane(pCall,iSelection)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	CreateMenu(HUT2, pCaller, 0, 0,"Baupläne", 0, 1,1,104);
	var i;
	var idObjekt;
	while(idObjekt = GetDefinition (i,128))
	{
		if(GetPlrKnowledge(0,idObjekt)) AddMenuItem(Format("<c ff0000>%s löschen</c>",GetName(0,idObjekt)), Format("Building(%i,%d)",idObjekt,GetOwner(pCaller),GetCursor(pCall) -> GetMenuSelection()), idObjekt, pCaller);
		if(!GetPlrKnowledge(0,idObjekt)) AddMenuItem(Format("<c 00ff00>%s hinzufügen</c>",GetName(0,idObjekt)), Format("Building(%i,%d)",idObjekt,GetOwner(pCaller),GetCursor(pCall) -> GetMenuSelection(pCaller)), idObjekt, pCaller);
		i++;
	}
	AddMenuItem("Fertig", Format("ChooseRules(%d)",GetOwner(pCaller)), GOLD, pCaller);
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
}

func Ziele(pCall)
{
	ATC=0;
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
	ATC=0;
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
	AddMenuItem("Fertig", Format("ChooseRules(%d)",GetOwner(pCaller)), GOLD, pCaller);
}
/*-- SubSubMenus --*/

func Objekte(pCall)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	ATC=1;
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
	AddMenuItem("Fertig", Format("Umwelt(%d)",GetOwner(pCaller)), GOLD, pCaller);
	ATC=0;
}
 
func Regen(pCall)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	ATC=1;
	CloseMenu(pCaller);
	CreateMenu(FXP1, pCaller, 0, 0,Format("%d Regen",ObjectCount(FXP1)), 0, 1,1,131);
	AddMenuItem("Mehr", "RainUp", GetID(this()), pCaller);
	AddMenuItem("Weniger", "RainDown", GetID(this()), pCaller);
	AddMenuItem("Fertig", Format("Umwelt(%d)",GetOwner(pCaller)), GOLD, pCaller);
	ATC=0;
}

func Temperatur(pCall)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	ATC=1;
	CloseMenu(pCaller);
	CreateMenu(ICE1, pCaller, 0, 0,Format("%d Temperatur",Temperature), 0, 1,1,131);
	AddMenuItem("Mehr", "ClimUp", GetID(this()), pCaller);
	AddMenuItem("Weniger", "ClimDown", GetID(this()), pCaller);
	AddMenuItem("Fertig", Format("Umwelt(%d)",GetOwner(pCaller)), GOLD, pCaller);
	ATC=0;
}

func Meteoriten(pCall)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	ATC=1;
	CloseMenu(pCaller);
	CreateMenu(MTRG, pCaller, 0, 0,Format("%d Meteoriten",ObjectCount(METR)), 0, 1,1,132);
	AddMenuItem("Mehr", "MeteoUp", GetID(this()), pCaller);
	AddMenuItem("Weniger", "MeteoDown", GetID(this()), pCaller);
	AddMenuItem("Fertig", Format("Umwelt(%d)",GetOwner(pCaller)), GOLD, pCaller);
	ATC=0;
}

/*-- Befehle --*/
 
func Goal(id idGoal,pCall,iSelection)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	iSelection = GetMenuSelection(pCaller);
	ATC=1;
	CloseMenu(pCaller);
	if(FindObject(idGoal)) 
	{
		Message("{{%i}} <c ffcc00>%s Entfernt</c>",0,idGoal,GetName(0,idGoal));
		RemoveAll(idGoal);
		Ziele(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return();
	}
	else
	{
		Message("{{%i}} <c ffcc00>%s Hinzugefügt</c>",0,idGoal,GetName(0,idGoal));
		CreateObject(idGoal);
		Ziele(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return();
	}
}

func Rule(id idRule,pCall,iSelection)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	iSelection = GetMenuSelection(pCaller);
	ATC=1;
	CloseMenu(pCaller);
	if(FindObject(idRule)) 
	{
		Message("{{%i}} <c ffcc00>%s Entfernt</c>",0,idRule,GetName(0,idRule));
		RemoveAll(idRule);
		Regeln(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return();
	}
	else
	{
		Message("{{%i}} <c ffcc00>%s Hinzugefügt</c>",0,idRule,GetName(0,idRule));
		CreateObject(idRule);
		Regeln(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return();
	}
}

func Objegt(id idObject,pCall,iSelection)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	iSelection = GetMenuSelection(pCaller);
	ATC=1;
	CloseMenu(pCaller);
	ATC=0;
	if(FindObject(idObject)) 
	{
		Message("{{%i}} <c ffcc00>%s Entfernt</c>",0,idObject,GetName(0,idObject));
		RemoveAll(idObject);
		Objekte(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return();
	}
	else
	{
		Message("{{%i}} <c ffcc00>%s Hinzugefügt</c>",0,idObject,GetName(0,idObject));
		PlaceObjects(idObject,50,"GBackSemiSolid");
		Objekte(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
		return();
	}
}

func Building(id idObject,pCall,iSelection)
{
	ATC=0;
	var pCaller;
	pCaller = GetCursor(pCall);
	Sound("Connect");
	iSelection = GetMenuSelection(pCaller);
	ATC=1;
	CloseMenu(pCaller);
	ATC=0;
	var i;
	while(i != GetPlayerCount())
	{
		if(GetPlrKnowledge(i,idObject)) 
		{
			Message("{{%i}} <c ffcc00>%s Nicht Baubar</c>",0,idObject,GetName(0,idObject));
			SetPlrKnowledge(i,idObject,1);
			Bauplane(GetOwner(pCaller));
		GetCursor(GetOwner(pCaller)) -> SelectMenuItem(iSelection);
			return();
		}
		else
		{
			Message("{{%i}} <c ffcc00>%s Baubar</c>",0,idObject,GetName(0,idObject));
			SetPlrKnowledge(i,idObject,0);
			Bauplane(GetOwner(pCaller),iSelection);
			return();
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