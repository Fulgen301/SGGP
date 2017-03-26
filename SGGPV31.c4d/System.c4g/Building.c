/* Building */

#strict 2

global func AddBuildEffect(object pObj)
{
	if(!pObj) if(!(pObj = this)) return;
	if(pObj->~RejectBuild() || FindObject2(Find_ID(AUBA))) return;
	AddEffect("Build", pObj, 1, 60);
}

global func FxBuildStart(object pTarget, int iEffect, bool fTemp)
{
	if(fTemp) return;
	
	EffectVar(0, pTarget, iEffect) = BoundBy(GetMass(0, pTarget->GetID())/100, 1, 7);
}

global func FxBuildEffect(string szNewEffectName, object pTarget)
{
	if(szNewEffectName == "Build") return -1;
}

global func FxBuildTimer(object pTarget, int iEffect)
{
	if(pTarget->GetCon() >= 100) return -1;
	
	if(GetWealth(pTarget->GetOwner()) >= EffectVar(0, pTarget, iEffect))
	{
		DoWealth(pTarget->GetOwner(), -EffectVar(0, pTarget, iEffect));
		pTarget->DoCon(1);
	}
	
	Message("@%d%%", pTarget, pTarget->GetCon());
}

global func FxBuildStop(object pTarget, int iEffect, int iReason, bool fTemp)
{
	if(fTemp || !pTarget) return;
	Message("@", pTarget);
}