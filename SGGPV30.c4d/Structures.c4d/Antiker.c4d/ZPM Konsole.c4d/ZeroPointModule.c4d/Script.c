/*-- Zero Point Modul --*/

#strict 2

local timer, target, actiondata;

protected func Set(object pTarget, int iActionData)
{
	if(pTarget)
	{
		target = pTarget;
		actiondata = iActionData;
		SetAction("None", pTarget);
		SetActionData(iActionData);
	}
	return this;
}

func Minus()
{
  if(timer > 0)
  {
   timer--;
   return(1);
  }
  if(FindContents(ZPM_) && FindContents(ZPM_)->GetAction() != "Depledet")
  {
   FindContents(ZPM_)->Minus();
   timer = 50;
  }
  return(1);
}

func Enrg()
{
  if(FindContents(ZPM_))
  {
   return(FindContents(ZPM_)->Energ());
  }
  return(0);
}

func GetZpm()
{
  return(FindContents(ZPM_));
}

protected func Collection2(object pZPM)
{
	if(!pZPM) return;
	if(pZPM && (pZPM->GetID() != ZPM_ || ContentsCount() > 2)) return pZPM->Exit();
	SetAction(pZPM->GetAction());
	Visible();
}

protected func RejectCollect()
{
	return !!Contents();
}

protected func Ejection(object pZPM)
{
	if(!pZPM || pZPM->GetID() != ZPM_) return;
	SetAction("None");
	Invisible();
}

public func SetAction(string szAction, object pTarget)
{
	if(!pTarget && target) pTarget = target;
	if(Contents()) Contents()->SetAction(szAction);
	var ret = _inherited(szAction, pTarget, ...);
	SetActionData(actiondata);
	return ret;
}

private func Visible()		{ SetVisibility(VIS_All); }
private func Invisible()	{ SetVisibility(VIS_None); }