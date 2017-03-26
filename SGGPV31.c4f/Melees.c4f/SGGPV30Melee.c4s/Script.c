/*-- Siedelmelee --*/

#strict

#include SGGP

static Downs;
func Initialize() 
{
	_inherited();
	SetTime(5,0);
	ChangeTimerCount(-1);
	CreateObject(NOAM);
	CreateObject(NOFO);
	CreateObject(AUBA);
	CreateObject(AUBA);
	CreateObject(SPER);
	CreateObject(RULL);
	CreateGate(SGR2,STGT,989,415,NO_OWNER);
	CreateObject(DHD_,906,410,NO_OWNER);
	CreateGate(SGR2,STGT,2222,414,NO_OWNER);
	CreateObject(DHD_,2365,431,NO_OWNER);
	Schedule("FindObjects(Find_Func(\"IsStargate\"),Find_Func(\"ControlIris\"))",1);
	return(1);
}

func InitializePlayer(int iPlayer)
{
	_inherited();
	if(GetPlayerName(iPlayer))
	{
		var i;
		var pCrew;
		var Flag;
		while(pCrew = GetCrew(iPlayer,i))
		{
			if(GetPlayerTeam(iPlayer) == 1) pCrew -> SetPosition(983,378);
			if(GetPlayerTeam(iPlayer) == 2) pCrew -> SetPosition(2036,374);
			pCrew -> CreateObject(CNKT,20,0,iPlayer);
			if(!Flag)
			{
				pCrew -> CreateObject(FLAG,20,0,iPlayer);
				Flag = 1;
			}
			i++;
		}
	}
}

func TimerDown()
{
	if(!Downs)
	{
		ExpandHomebaseStuff(P90_);
		ExpandHomebaseStuff(ZATN);
		ExpandHomebaseStuff(FLSH);
		ExpandHomebaseStuff(WRST);
		Downs = 1;
		Message("{{P90_}}{{ZATN}}{{FLSH}}{{WRST}} sind verfügbar!");
		Schedule("SetTime(5,0)",100);
		ChangeTimerCount(-1);
		return();
	}
	if(Downs == 1)
	{
		ExpandHomebaseStuff(HARM);
		ExpandHomebaseStuff(STBW);
		ExpandHomebaseStuff(JTPK);
		Message("{{HARM}}{{STBW}}{{JTPK}} sind verfügbar!|<c ff0000>Der Krieg hat begonnen!</c>");
		Downs = 2;
		RemoveAll(SPER);
		Schedule("SetTime(5,0)",100);
		ChangeTimerCount(-1);
		return();
	}
	if(Downs == 2)
	{
		ExpandHomebaseStuff(ROGN);
		ExpandHomebaseStuff(WRGR);
		ExpandKnowledgeStuff(WAHL);
		ExpandHomebaseStuff(GDO_);
		Downs = 3;
		Message("{{ROGN}}{{WAHL}}{{WRGR}}{{GDO_}} sind verfügbar!|{{STGT}} <c ffcc00>ist offen</c>");
		Schedule("SetTime(3,0)",100);
		ChangeTimerCount(-1);
		var pGate;
		for(pGate in FindObjects(Find_ID(STGT)))
		{
			pGate -> ChangeIrisState();
		}
		return();
	}
	if(Downs == 3)
	{
		ExpandHomebaseStuff(GOBE);
		ExpandHomebaseStuff(HEGR);
		ExpandHomebaseStuff(CANN);
		ExpandHomebaseStuff(GUNP);
		ExpandHomebaseStuff(GUNP);
		ExpandHomebaseStuff(GUNP);
		ExpandHomebaseStuff(GUNP);
		ExpandHomebaseStuff(FLNT);
		ExpandHomebaseStuff(SFLN);
		ExpandHomebaseStuff(TAMA);	
		Message("{{GOBE}}{{HEGR}}{{SFLN}}{{TAMA}}{{FLNT}}{{CANN}}{{GUNP}} sind verfügbar!");
		Downs = 4;
		Schedule("SetTime(3,0)",100);
		ChangeTimerCount(-1);
		return();
	}
	if(Downs == 4)
	{
		ExpandHomebaseStuff(LZD_);
		ExpandHomebaseStuff(PUD_);
		ExpandHomebaseStuff(NANO);
		ExpandHomebaseStuff(EFLN);
		ExpandHomebaseStuff(TFLN);
		Message("{{LZD_}}{{PUD_}}{{NANO}}{{EFLN}}{{TFLN}} sind verfügbar!");
		Downs = 5;
		Schedule("SetTime(3,0)",100);
		ChangeTimerCount(-1);
		return();
	}
	if(Downs == 5)
	{
		ExpandHomebaseStuff(BZWP);
		ExpandHomebaseStuff(KLAS);
		ExpandHomebaseStuff(MINE);
		ExpandHomebaseStuff(KRFL);
		ExpandHomebaseStuff(GLWP);
		CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Acid"),LandscapeWidth()-10,10000);
		Message("{{GLWP}}{{KRFL}}{{MINE}}{{KLAS}}{{BZWP}} sind verfügbar!|<c 00ff00> Es regnet Säure!</c>");
		Downs = 6;
		ChangeTimerCount(1);
		return();
	}
}
func ExpandHomebaseStuff(objectId)
{
	for (var i = 0; i < GetPlayerCount(); i++)
	{
		DoHomebaseMaterial(i, objectId, 3);
		DoHomebaseProduction(i, objectId, 5);
	}
}

func ExpandKnowledgeStuff(objectId)
{
	for (var i = 0; i < GetPlayerCount(); i++)
	{
		SetPlrKnowledge(i, objectId);
	}
}
