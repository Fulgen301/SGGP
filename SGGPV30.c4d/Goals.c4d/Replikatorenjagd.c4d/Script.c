#strict 2
#include GOAL   
//#include TEAM

local finished;
static count;

public func GoalExtraValue() {return count;}
public func IsFulfilled()
{
	if(!finished) return(0);
	return ReplCheck();
}

protected func Initialize()
{
	_inherited();
	AddEffect("ReplCheck", this, 1, 1, this);
}
 
protected func Activate(int iPlayer)
{
//	MessageWindow(Format("{{REPL}} Replikatoren: <c ffcc00>%d</c>|{{REQU}} Königinnen: <c ffcc00>%d</c>|{{REWU}} Würfel: <c ffcc00>%d</c>|{{RETE}} Teleporter: <c ffcc00>%d</c>|{{REAT}} GateAttatchs: <c ffcc00>%d</c>|{{REDA}} Drohnenrampen: <c ffcc00>%d</c>",ObjectCount2(Find_OCF(OCF_Fullcon),Find_ID(REPL)),ObjectCount2(Find_OCF(OCF_Fullcon),Find_ID(REQU)),ObjectCount2(Find_OCF(OCF_Fullcon),Find_ID(REWU)),ObjectCount2(Find_OCF(OCF_Fullcon),Find_ID(RETE)),ObjectCount2(Find_OCF(OCF_Fullcon),Find_ID(REAT)),ObjectCount2(Find_OCF(OCF_Fullcon),Find_ID(REDA))),iPlayer);
}

protected func FxReplCheckTimer()
{
	count = ObjectCount2(Find_OCF(OCF_Fullcon),Find_Func("IsRepli"),Find_Not(Find_ID(REBO),Find_ID(REWA)));
}

protected func ReplCheck()
{
	if(FindObject2(Find_OCF(OCF_Fullcon),Find_Func("IsRepli"),Find_Not(Find_ID(REBO),Find_ID(REWA)))) 
	{
		return(0);
	}
	else
	{
		//GameOver();
		return(1);
	}
}

/* CMC */

public func ChooserFinished()
{
	for (var i = 0; i < 5; i++)
	{
		var x = Random(LandscapeWidth());
		var y = Random(LandscapeHeight());
		if(GBackSolid(x,y))
		{
			i--;
			continue;
		}
		else
		{
			CreateObject(REPL, Random(LandscapeWidth()), Random(LandscapeHeight()), -1);
		}
	}
	finished=1;
	return(1);
}

public func UpdateScoreboard()
{
  SetScoreboardData(SBRD_Caption, SBRD_Caption, GetName());
  SetScoreboardData(SBRD_Caption, 0, Format("{{%i}}", GetID()));
  SetScoreboardData(SBRD_Caption, 1, Format("$Count$"));
  SetScoreboardData(SBRD_Caption, 2, Format("%i", count));
}

public func InitScoreboard()
{
	UpdateScoreboard();
}


