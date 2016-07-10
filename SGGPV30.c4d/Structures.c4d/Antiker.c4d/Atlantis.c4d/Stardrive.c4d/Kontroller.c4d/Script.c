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
	CreateMenu(ALSD,pCaller,0,0,"Sternenantrieb",0,0,true);
	AddMenuItem("Hinauf","Up",MEPU,pCaller,0,pCaller);
	AddMenuItem("Hinunter","Down",MEPU,pCaller,0,pCaller);
	AddMenuItem("Nach links","Left",MEPU,pCaller,0,pCaller);
	AddMenuItem("Nach rechts","Right",MEPU,pCaller,0,pCaller);
	return(1);
}	

public func Up(id dummy, object pCaller)
{
	for(target in targets)
	{
		if(target)
			target->ControlUp(pCaller);
	}
	return(1);
}

public func Down(id dummy, object pCaller)
{
	for(target in targets)
	{
		if(target)
			target->ControlDown(pCaller);
	}
	return(1);
}

public func Left(id dummy, object pCaller)
{
	for(target in targets)
	{
		if(target)
			target->ControlLeft(pCaller);
	}
	return(1);
}

public func Right(id dummy, object pCaller)
{
	for(target in targets)
	{
		if(target)
			target->ControlRight(pCaller);
	}
	return(1);
}

public func IsAntiker()
{
	return(1);
}
