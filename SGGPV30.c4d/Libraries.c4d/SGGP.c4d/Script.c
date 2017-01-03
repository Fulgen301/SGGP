/*-- SGGP --*/
#strict 2

static const SGGP_Version = 301;
static iSystemTime;
static SGGP_SystemTimeStrings;
static SGGP_Developers;

protected func InitializePlayer(int iPlr)
{
	if(GetPlrExtraData(iPlr,"SGGP_Banned"))
	{
		EliminatePlayer(iPlr);
		Log("%s is banned.", GetPlayerName(iPlr));
		return;
	}
	
  	var version = GetPlrExtraData(iPlr, "SGGP_Version");
	if(version <= SGGP_Version)
	{
		SetPlrExtraData(iPlr, "SGGP_Version", SGGP_Version);
	}
	
	SaveTime(iPlr);
}

global func SaveTime(int iPlr)
{
	//Time hack
	if(IsSGGPTeamMember(iPlr) || iPlr == 0)
	{
		if(!IsNetwork())
		{
			for(var i = 0; i < GetLength(SGGP_SystemTimeStrings); i++)
			{
				SetPlrExtraData(iPlr,Format("SGGP_%s", SGGP_SystemTimeStrings[i]), GetSystemTime(i));
			}
		}

		for(var i = 0; i < GetLength(SGGP_SystemTimeStrings); i++)
		{
			iSystemTime[i] = GetPlrExtraData(iPlr, Format("SGGP_%s", SGGP_SystemTimeStrings[i]));
		}
	}
}

global func GetSystemTime(int iWhat)
{
	if(!IsNetwork()) return _inherited(iWhat, ...);
	
	if(GetType(iSystemTime) != C4V_Array) iSystemTime = [];
	return iSystemTime[iWhat];
}

protected func Initialize()
{
	iSystemTime = [];
	SGGP_SystemTimeStrings = ["Year", "Month", "WeekDay", "Day", "Hour", "Minute", "Second", "Millisecond"];	
	if(!FindObject(HELP))
		CreateObject(HELP);
	
	SGGP_Developers = CreateArray();
	SGGP_Developers[0] = "NDRBQjg1QTI1MkFEQjdBREU4Q0EzNkZFQzQxNTdBODYyQzFGNzI1RnwwfC0x";
	SGGP_Developers[1] = "MTc1RUM0NTlBRjQyMzEwNjQ2N0FGQkNEMUM1ODZEMjZGNTcyRkUwQXwwfC0x";
	SGGP_Developers[2] = "";
	
	AddMsgBoardCmd("identify", "Identify(%player%, \"%s\")", C4MSGCMDR_Escaped);
	return(1);
}

protected func OnGameOver()
{
	for(var i = 0; i < GetPlayerCount(C4PT_User); i++)
	{
		SaveTime(GetPlayerByIndex(i));
	}
}


/*Points*/
static const SGGP_KillPoints = 1;
static const SGGP_SettlePoints = 2;
static const SGGP_MinusPoints = 3;

global func DoPoints(int iPlr, int iAmount, int iType)
{
	if(iPlr == NO_OWNER) return;
	var points = BoundBy(GetPlrExtraData(iPlr, "SGGP_Points"), 0, 0x7FFFFFFF);
	if(iType == SGGP_MinusPoints)
	{
		if(points > iAmount)
		{
			points -= iAmount;
		}
		else
		{
			points = 0;
		}
		if(GetCursor(iPlr))
		{
			//CustomMessage(Format("{{MEPU:2}} -%d", points), GetCursor(iPlr), 10, 0, RGB(255, 0, 0));
			Message("{{MEPU:2}} <c ff0000>-%d</c>", GetCursor(iPlr), iAmount);
		}
	}
	else
	{
		points += iAmount;
		//CustomMessage(Format("{{MEPU:1}} +%d", points), GetCursor(iPlr), 10, 0, RGB(0, 150, 0));
		Message("{{MEPU:1}} <c 009600>%d</c>",GetCursor(iPlr), iAmount);
	}
	SetPlrExtraData(iPlr, "SGGP_Points", points);
	return points;
}

global func Identify(int iPlr, string szPassword)
{
	for(var i = 0; i < GetLength(SGGP_Developers); i++)
	{
		if(SHA1m(szPassword) == SplitStringAT(League64Dec(SGGP_Developers[i]), "|")[0])
		{
			SGGP_Developers[i] = League64Enc(JoinString([SplitStringAT(League64Dec(SGGP_Developers[i]), "|")[0], 1, iPlr], "|"));
			return true;
		}
	}
}

global func IsSGGPTeamMember(int iPlr)
{
	
	for(var i = 0; i < GetLength(SGGP_Developers); i++)
	{
		if(ParseInt(SplitStringAT(League64Dec(SGGP_Developers[i]), "|")[1]) && ParseInt(SplitStringAT(League64Dec(SGGP_Developers[i]), "|")[2]) == iPlr)
		{
			return true;
		}
	}
	return false;
}