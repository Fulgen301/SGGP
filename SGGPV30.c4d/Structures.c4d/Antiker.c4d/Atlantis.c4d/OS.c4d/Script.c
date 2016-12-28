/*-- Atlantis-Betriebssystem --*/

#strict 2

protected func Construction()
{
	AddEffect("IntAtlantisOS",this,1,35,this,GetID(), []);
}

global func GetALOS(int iPlr)
{
	var obj;
	if(obj = FindObject2(Find_ID(ALOS), Find_Owner(iPlr))) return obj;
	else return CreateObject(ALOS,0,0,iPlr);
}
/* RegisterStructure */

public func RegisterStructure(object pStructure)
{
	if(pStructure)
	{
		var struct = [];
		EffectVar(0, this, GetEffect("IntAtlantisOS", this))[GetLength(EffectVar(0, this, GetEffect("IntAtlantisOS", this)))] = pStructure;
		return true;
	}
}

public func GetStructures(array& proplist, data)
{
	var ret = [];
	for(var i = 0; i < GetLength(proplist); i++)
	{
		if(!data && GetIndexOf(proplist[i], ret) == -1)
		{
			ret[GetLength(ret)] = proplist[i];
		}
		
		else if(GetType(data) == C4V_C4ID && GetType(proplist[i]) == C4V_C4Object && proplist[i]->GetID() == data && GetIndexOf(proplist[i], ret) == -1)
		{
			ret[GetLength(ret)] = proplist[i];
		}
		
		else if(GetType(data) == C4V_String && GetType(proplist[i]) == C4V_C4Object && eval(Format("Object(%d)->~%s()", proplist[i]->ObjectNumber(), data)) && GetIndexOf(proplist[i], ret) == -1)
		{
			ret[GetLength(ret)] = proplist[i];
		}
	}
	
	return ret;
}

/* The core system */

protected func FxIntAtlantisOSStart(object pTarget, int iEffect, int iTemp, array proplist)
{
	if(iTemp) return;
	EffectVar(0, pTarget, iEffect) = proplist;
	EffectVar(1, pTarget, iEffect) = [];
	EffectVar(1, pTarget, iEffect) = 0;
	EffectVar(2, pTarget, iEffect) = 35;
}

static const ATLANTISOS_OK				 = 0;
static const ATLANTISOS_NOENERGY		 = 2;
static const ATLANTISOS_ZPMLOW			 = 4;
static const ATLANTISOS_ENEMYAPPROACHING = 8;
static const ATLANTISOS_QUARANTINE		 = 16;

/* EffectVars
	0 - proplist with all registered structures
	1 - status
	2 - current effect interval
*/

protected func FxIntAtlantisOSTimer(object pTarget, int iEffect, int time)
{
	var values = [];
	var interval = EffectVar(2, pTarget, iEffect);
	var status = 0;
	
	// Executing the function in the structures
	for(var i = 0; i < GetLength(EffectVar(0, pTarget, iEffect)); i++)
	{
		if(EffectVar(0, pTarget, iEffect)[i]) values[i] = EffectVar(0, pTarget, iEffect)[i]->~AtlantisOSFunc();
		
		//Handle the return value
		
		/*if(values[i] == ATLANTISOS_OK)
		{
			// All ok, don't do anything.
		}
		
		else */
		if(values[i] & ATLANTISOS_NOENERGY)
		{
			 // Why do we this here? Because this is structure specific.
			 // With our current energy system, this gets a bit more complicated, but at least, we can set the defcon to a high level.
		}
		
		/*else if(values[i] == ATLANTISOS_ZPMLOW)
		{
		}*/
		
		status |= values[i];
	}
	
	//
	//
	//	Common checks
	//
	//
	
	if(status == ATLANTISOS_OK)
	{
		interval = 35;
		
		var defcon_active = false;
		
		for(var gate in pTarget->GetStructures(EffectVar(0, pTarget, iEffect), "IsStargate"))
		{
			if(gate && !gate->IsSpaceGate())
			{
				if(WildcardMatch(gate->GetAction(), "Income*"))
				{
					if(gate->GetAction() == "Income1" || gate->GetAction() == "Income2")
					{
						if(!(gate->IsClose()))
						{
							if(!(gate->HasIris())) gate->InstallIris();
							gate->~ControlIris();
						}
					}
					else if(gate->IsClose() && gate->GetState() != 2)
					{
						gate->ControlIris();
					}
				}
				
				if(gate->IsBusy())
				{
					if(!defcon_active) defcon_active = true;
				}
				else if(gate->IsClose()) gate->ControlIris();
			}
		}
	
		if(pTarget->GetStructures(EffectVar(0, pTarget, iEffect), DEFK) == [] && FindObject2(Find_ID(DEFK), Find_Owner(pTarget->GetOwner()))) GetALOS(pTarget->GetOwner())->RegisterStructure(FindObject2(Find_ID(DEFK), Find_Owner(pTarget->GetOwner())));
		for(var defcontr in pTarget->GetStructures(EffectVar(0, pTarget, iEffect), DEFK))	
		{
			if(defcontr)
			{
				defcontr->~ConsoleControlled((defcon_active * 3) + 1);
			}
		}
	}
	
	if(status & ATLANTISOS_ZPMLOW)
	{
		for(var defc in pTarget->GetStructures(EffectVar(0, pTarget, iEffect), DEFK))
		{
			if(defc) defc->ConsoleControlled(5);
		}
		// Check if there is a defcon controller; if yes, set it to the highest level;
		// if submerged and the shield is online, trying to raise the city; 
		// if we do not have enough power for that,
		// lower the shield and raise the city
			
		// if the ZPM count is not enough,
		// dial the next gate, close all doors which do not lead to the stargate.
		
		/*var struct = [];
		
		if(struct = pTarget->GetStructures(EffectVar(0, pTarget, iEffect), ALZP))
		{
			var zpmGenerator = struct[0]->~GetZPMGenerator();
			var zpm;
			if(zpmGenerator && zpmGenerator->~GetActiveZPMCount() < 2)
			{
				for(var obj in zpmGenerator->~GetAllZPMs())
				{
					if(obj)
					{	
						if(obj->GetAction() == "Depledet")
						{
							continue;
						}
						
						else
						{
							zpm = obj;
						}
					}
				}
				
				/*if(struct = GetStructure(EffectVar(0, pTarget, iEffect), DEFK))
				{
					GetProplistData(struct, "object")->~ConsoleControlled(5);
				}
			}
		}*/
	}
	
	if(status & ATLANTISOS_QUARANTINE)
	{
		for(var defcontr in pTarget->GetStructures(EffectVar(0, pTarget, iEffect), DEFK))	
		{
			if(defcontr)
			{
				defcontr->~ConsoleControlled(5);
			}
		}
		
		for(var gate in pTarget->GetStructures(EffectVar(0, pTarget, iEffect), "IsStargate"))
		{
			if(gate && !(gate->IsClose()))
			{
				gate->~ControlIris();
				if(WildcardMatch(gate->GetAction(), "Outgoing*"))
				{
					gate->Deactivate();
				}
			}
		}
		
		interval = 10;
	}
	
	EffectVar(1, pTarget, iEffect) = status;
	if(interval != EffectVar(2, pTarget, iEffect))
	{
		EffectVar(2, pTarget, iEffect) = interval;
		ChangeEffect("IntAtlantisOS", pTarget, 0, "IntAtlantisOS", interval);
	}
}

protected func FxIntAtlantisOSRaise(object pTarget, int iEffect)
{
	//TODO: Raise the city	
}

protected func FxIntAtlantisOSStatus(object pTarget, int iEffect, object pChair)
{
	var msg = "";
	PlayerMessage(pTarget->GetOwner(), msg, pChair);
}
public func Atlantis()
{
	return true;
}
