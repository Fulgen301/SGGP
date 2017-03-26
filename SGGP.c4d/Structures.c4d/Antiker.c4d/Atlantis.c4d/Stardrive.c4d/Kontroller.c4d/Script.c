/*-- Sternenantrieb-Kontroller --*/

#strict 2

local buildings;
local targets;

protected func Initialize()
{
	SetPosition(AbsX(0),AbsY(0));
	for(obj in FindObjects(Find_ID(ALSK),Find_Distance(1000),Find_Exclude(this)))
	{
		if(obj)
			obj->RemoveObject();
	}
	return(1);
}


protected func Check()
{
	targets=FindObjects(Find_Owner(GetOwner()),Find_Func("Atlantis"),Find_ID(ALSD));
	return(1);
}

public func ControlDigDouble(pCaller)
{
	CreateMenu(ALSD,pCaller,0,0,"Sternenantrieb");
	AddMenuItem("Hinauf","Up",MEPU,pCaller,0,pCaller);
	AddMenuItem("Hinunter","Down",MEPU,pCaller,0,pCaller);
	AddMenuItem("Nach links","Left",MEPU,pCaller,0,pCaller);
	AddMenuItem("Nach rechts","Right",MEPU,pCaller,0,pCaller);
	AddMenuItem("Stopp","Stop",MEPU,pCaller,0,pCaller);
	return true;
}	

public func Up(id dummy, object pCaller)
{
	AddEffect("IntStardrive",this,1,1,this,GetID(),"Up",pCaller);
	for(target in targets)
	{
		if(target)
			target->ControlUp(pCaller);
	}
	return(1);
}

public func Down(id dummy, object pCaller)
{
	AddEffect("IntStardrive",this,1,1,this,GetID(),"Down", pCaller);
	for(target in targets)
	{
		if(target)
			target->ControlDown(pCaller);
	}
	return(1);
}

public func Left(id dummy, object pCaller)
{
	AddEffect("IntStardrive",this,1,1,this,GetID(),"Left", pCaller);
	for(target in targets)
	{
		if(target)
			target->ControlLeft(pCaller);
	}
	return(1);
}

public func Right(id dummy, object pCaller)
{
	AddEffect("IntStardrive",this,1,1,this,GetID(),"Right", pCaller);
	for(target in targets)
	{
		if(target)
			target->ControlRight(pCaller);
	}
	return true;
}

public func Stop(id dummy, object pCaller)
{
	while(GetEffect("IntStardrive",this)) RemoveEffect("IntStardrive",this);
	return true;
}

protected func FxIntStardriveStart(object pTarget, int iEffect, bool fTemp, string mode, object pCaller)
{
	if(fTemp) return;
	EffectVar(0, pTarget, iEffect) = mode;
	EffectVar(1, pTarget, iEffect) = pCaller;
	EffectVar(2, pTarget, iEffect) = FindObject2(Find_ID(ALZP), Find_Owner(pTarget->GetOwner()));
}

protected func FxIntStardriveTimer(object pTarget, int iEffect, int time)
{
	if(!EffectVar(1, pTarget, iEffect)) EffectVar(1, pTarget, iEffect) = GetCrew(pTarget->GetOwner());
	
	if(EffectVar(2, pTarget, iEffect))
	{
		var zpmGenerator = EffectVar(2, pTarget, iEffect)->GetZPMGenerator();
		if(zpmGenerator && zpmGenerator->GetActiveZPMCount() >= 2 && GetType(zpmGenerator->GetAllZPMs()) == C4V_Array)
		{
			for(var zpm in zpmGenerator->GetAllZPMs())
			{
				if(zpm && zpm->GetZpm() && zpm->GetZpm()->GetAction() != "Depledet")
				{
					for(var i = 0; i < 4; i++)	zpm->Minus();
					break;
				}
			}
		}
		else
		{
			return -1;
		}
	}
	else if(!(EffectVar(2, pTarget, iEffect) = FindObject2(Find_ID(ALZP), Find_Owner(pTarget->GetOwner()))))
	{
		return -1;
	}
	
	if(pTarget && GetType(pTarget->LocalN("targets")) == C4V_Array && EffectVar(0, pTarget, iEffect))
	{
		for(var obj in pTarget->LocalN("targets"))
		{
			if(obj) obj->Call(Format("Control%s",EffectVar(0, pTarget, iEffect)), EffectVar(1, pTarget, iEffect));
		}
	}
	
	return 1;
}

public func IsAntiker()
{
	return(1);
}
