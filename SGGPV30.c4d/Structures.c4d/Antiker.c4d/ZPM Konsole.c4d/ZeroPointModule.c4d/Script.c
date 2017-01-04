/*-- Zero Point Modul --*/

#strict 2

local timer;

func Initialize() 
{
  ObjectSetAction(this, "None");
}

func Minus()
{
  if(timer > 0)
  {
   timer--;
   return(1);
  }
  if(FindContents(ZPM_))
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
}

protected func Ejection(object pZPM)
{
	if(!pZPM || pZPM->GetID() != ZPM_) return;
	ObjectSetAction(this, "Idle");
}

public func SetAction(string szAction)
{
	Log(szAction);
	if(Contents()) Contents()->SetAction(szAction, ...);
	return _inherited(szAction, ...);
}

private func Visible()		{ SetVisibility(VIS_All); }
private func Invisible()	{ SetVisibility(VIS_None); }