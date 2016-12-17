/*-- SGGP --*/
#strict 2

static const SGGP_Version = 301;
static iSystemTime;
static SGGP_SystemTimeStrings;

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
	
	if(!GetEffect("IntTeamDisplay"))
	{
		AddEffect("IntTeamDisplay",0,1,5);
	}
	return(1);
}

protected func OnGameOver()
{
	for(var i = 0; i < GetPlayerCount(C4PT_User); i++)
	{
		SaveTime(GetPlayerByIndex(i));
	}
}

global func FxIntTeamDisplayTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
  var i, j, iPlr, iCount, szText, szPortrait, pClonk;
  var aIndex, aMessages;
  iCount = GetPlayerCount();
  aIndex = aMessages = [];
  for(i = 0; i < iCount; i++) {
    aIndex[ i] = GetPlayerByIndex(i);
    CustomMessage("",0,aIndex[ i],0,0,0,0,0,MSG_Top|MSG_Left);
  }
  
  if(FindObject(MS4K) || FindObject(EI4K)) return;
  
  for(i = 0; i < iCount; i++) {
    iPlr = aIndex[ i];
    pClonk = GetCursor(iPlr);
    szText = Format("@<c e000ff00>%s</c>|<c e0ff0000> %3d/%d Energy</c>|<c e00080ff> %3d Points</c>",
        GetPlayerName(iPlr),
		GetEnergy(pClonk),GetPhysical("Energy",0,pClonk)/1000,
		BoundBy(GetPlrExtraData(iPlr, "SGGP_Points"), 0, 0x7FFFFFFF));
    szPortrait = Format("Portrait:%i::%x::%s",GetPortrait(pClonk,true),GetColorDw(pClonk),GetPortrait(pClonk,false));
    for(j = 0; j < iCount; j++) {
      if(Hostile(iPlr,aIndex[j]))
        continue;
      CustomMessage(szText,0,aIndex[j],25+240*(aMessages[j]++),125,0,0,szPortrait,MSG_Top|MSG_Left|MSG_Multiple);
    }
  }
  return true;
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