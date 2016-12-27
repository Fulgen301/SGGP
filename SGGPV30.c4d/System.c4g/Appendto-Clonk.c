#strict 2

#appendto CLNK

func ContextRelease(pCaller) 
{
	[$HelpRule$|Image=HELP]
  	HelpContext(GetController());
  	return(1);
}

func IsBulletTarget()
{
	return(true);
}

func IsThreat()
{
	return(true);
}

func Zated()
{
	SetAction("Dead");
	Schedule("ReRise()",300);
   	EMPShockEffect(50);
}

func ReRise()
{
	SetAction("FlatUp", 0,0, true); 
}

protected func ControlDigDouble()
{
	if(Contents() || (GetAction() == "Push" && GetActionTarget()) || GetEffect("GainKnowledge", this)) return _inherited(...);

	for(var structure in FindObjects(Find_Distance(30)))
	{
		if(structure && !GetPlrKnowledge(GetOwner(), structure->GetID()) && (C4D_Structure | C4D_StaticBack | C4D_Object | C4D_Knowledge) & structure->GetCategory())
		{
			//Log("%v", structure);
			var value = BoundBy(GetValue(0, structure->GetID())/100, 1, 50);
			AddEffect("GainKnowledge", this, 1, value, this, 0, structure, value*100);
			break;
		}
	}
	
	return _inherited(...);
}

protected func FxGainKnowledgeStart(object pTarget, int iEffect, int iTemp, object pStructure, int iValue)
{
	if(iTemp) return;
	EffectVar(0, pTarget, iEffect) = pStructure;
	EffectVar(1, pTarget, iEffect) = iValue;
	EffectVar(2, pTarget, iEffect) = 0;
}

protected func FxGainKnowledgeTimer(object pTarget, int iEffect)
{
	if(GetPlrKnowledge(pTarget->GetOwner(), EffectVar(0, pTarget, iEffect)->GetID())) return -1;
	EffectVar(2, pTarget, iEffect)++;
	PlayerMessage(pTarget->GetOwner(), "@%d%%", pTarget, EffectVar(2, pTarget, iEffect));
	
	if(EffectVar(2, pTarget, iEffect) == 100)
	{
		SetPlrKnowledge(pTarget->GetOwner(), EffectVar(0, pTarget, iEffect)->GetID());
		return -1;
	}
}

protected func FxGainKnowledgeStop(object pTarget, int iEffect, int iReason, bool fTemp)
{
	if(fTemp) return;
	Schedule(Format("PlayerMessage(%d, \"@\", Object(%d))", pTarget->GetOwner(), pTarget->ObjectNumber()),30);
}

protected func FxGainKnowledgeDamage(object pTarget, int iEffect, int iDmg, int iCause)
{
	if((iCause & 32) || iDmg < 0) return iDmg;
	RemoveEffect("GainKnowledge", pTarget);
	return iDmg;
}