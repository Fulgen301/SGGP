/*-- Atlantis-Betriebssystem --*/

#strict 2

protected func Construction()
{
	AddEffect("IntAtlantisOS",this,1,35,this,GetID(), []);
}

global func GetALOS(int iPlr)
{
	if(!GetPlayerName(iPlr)) return;
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
	EffectVar(2, pTarget, iEffect) = 0;
    EffectVar(8, pTarget, iEffect) = CreateHash();
}

static const ATLANTISOS_OK				 = 0;
static const ATLANTISOS_NOENERGY		 = 2;
static const ATLANTISOS_ZPMLOW			 = 4;
static const ATLANTISOS_ENEMYAPPROACHING = 8;
static const ATLANTISOS_QUARANTINE		 = 16;

/* EffectVars
	0 - proplist with all registered structures
	1 - status
	2 - counter
	3 - Stargate
	4 - Shield generator
	5 - ZPM console
	6 - DefCon controller
	7 - Stardrive controller
    8 - common hashtable
    9 - Dial PC
*/

protected func FxIntAtlantisOSTimer(object pTarget, int iEffect, int time)
{
	var values = [];
	var status = 0;
	var i;
	
	// Executing the function in the structures
	for(var obj in EffectVar(0, pTarget, iEffect))
	{
		if(obj) values[i] = obj->~AtlantisOSFunc();
		
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
		i++;
		
		if(obj)
		{
			if(!EffectVar(3, pTarget, iEffect) && obj->~IsStargate()) EffectVar(3, pTarget, iEffect) = obj; // Stargate
			else if(!EffectVar(4, pTarget, iEffect) && obj->~IsShieldGenerator()) EffectVar(4, pTarget, iEffect) = obj; // Shield generator
			else if(!EffectVar(5, pTarget, iEffect) && obj->~GetID() == ZPMG) EffectVar(5, pTarget, iEffect) = obj; // ZPM console
			else if(!EffectVar(6, pTarget, iEffect) && obj->~GetID() == DEFK) EffectVar(6, pTarget, iEffect) = obj; // DefCon controller
			else if(!EffectVar(7, pTarget, iEffect) && obj->~GetID() == ALSK) EffectVar(7, pTarget, iEffect) = obj; // Stardrive controller
            else if(!EffectVar(9, pTarget, iEffect) && obj->~IsDialPC()) EffectVar(9, pTarget, iEffect) = obj; // Dial pc
		}
	}
	
	//
	//
	//	Common checks
	//
	//
	
	var gate = EffectVar(3, pTarget, iEffect);
	
	if(status == ATLANTISOS_OK)
	{
		
        var obj = EffectVar(9, pTarget, iEffect);
        var addresses;
        if(obj && EffectVar(8, pTarget, iEffect) && (addresses = obj->LocalN("addresses")))
        {
            var list = [];
            for(var a in addresses)
            {
                var hash = CreateHash();
                HashPut(hash, "chevrons", HashGet(a, "chevrons"));
                HashPut(hash, "invalid", 0);
                list[GetLength(list)] = hash;
            }
            
            HashPut(EffectVar(8, pTarget, iEffect), "addresses", list);
        }
        
		var defcon_active = false;
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
            else if(EffectVar(2, pTarget, iEffect) % 300 == 0)
            {
                EffectCall(pTarget, iEffect, "StargateDial");
            }
			else if(gate->IsClose()) gate->ControlIris();
		}
	
		if(!EffectVar(6, pTarget, iEffect) && FindObject2(Find_ID(DEFK), Find_Owner(pTarget->GetOwner()))) GetALOS(pTarget->GetOwner())->RegisterStructure(FindObject2(Find_ID(DEFK), Find_Owner(pTarget->GetOwner())));
		else if(EffectVar(6, pTarget, iEffect))
		{
			EffectVar(6, pTarget, iEffect)->~ConsoleControlled((defcon_active * 3) + 1);
		}
        
	}
	
	if(status & ATLANTISOS_ZPMLOW)
	{
		if(EffectVar(6, pTarget, iEffect)) EffectVar(6, pTarget, iEffect)->ConsoleControlled(5);
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
		if(EffectVar(6, pTarget, iEffect)) EffectVar(6, pTarget, iEffect)->ConsoleControlled(5);
		
		if(gate) gate->Deactivate();
	}
	
	EffectVar(1, pTarget, iEffect) = status;
    EffectVar(2, pTarget, iEffect)++;
}

protected func FxIntAtlantisOSRaise(object pTarget, int iEffect)
{
	//TODO: Raise the city	
}

protected func FxIntAtlantisOSStatus(object pTarget, int iEffect, object pChair)
{
}

protected func FxIntAtlantisOSStargateDial(object pTarget, int iEffect)
{
    var gate;
    if(!(gate = EffectVar(3, pTarget, iEffect))) return;
    
	var addresses = HashGet(EffectVar(8, pTarget, iEffect), "addresses");
    addresses = addresses || [CreateHash()];
    
    var counter = HashGet(EffectVar(8, pTarget, iEffect), "counter");
    
    var adr = addresses[counter];
    
    var pGate = FindObject2(Find_Func("IsStargate"), Find_Exclude(gate), Find_Func("HasAddress", HashGet(adr, "chevrons")), Find_Not(Find_Func("IsBusy")));
	if(pGate)
    {
        var enrg = BoundBy(Distance(gate->GetX(),gate->GetY(),pGate->GetX(),pGate->GetY())*100, 100000, 1000000);
        if(gate->LocalN("energy") >= enrg)
        {
            gate->Dial2(HashGet(adr, "chevrons"));
        }
    }
    
    if(gate->GetAction() == "Idle")
    {
        HashPut(adr, "invalid", HashGet(adr, "invalid") + 1);
    }
    else HashPut(adr, "invalid", 0);
    
    if(counter >= GetLength(addresses)) counter = 0;
    
    HashPut(EffectVar(8, pTarget, iEffect), "addresses", addresses);
    HashPut(EffectVar(8, pTarget, iEffect), "counter", counter);
    ScheduleCall(gate, "Deactivate", 600);
}

public func GetRace() { return SG1_Ancient; }
