/*-- Thron --*/

#strict 2

local energy;

public func & HasEnergy()
{
	return energy;
}

protected func Construction()
{
	SetClrModulation(RGB(300,255,255));
	AddEffect("Timer", this, 1, 1, this);
}

private func IsOccupied()
  {
  return FindObject2(Find_OCF(OCF_CrewMember), Find_Container(this));
  }

protected func ActivateEntrance(pObj)
  {
  // Eingangsanfrage (nur Clonks)
  if (!pObj->Contained())
    if (pObj->GetOCF() & OCF_CrewMember)
      return OnEntrance(pObj);
  // Ausgangsanfrage
  if (pObj->Contained() == this)
    return OnExit(pObj);
  return;
  }

private func OnEntrance(pObj)
  {
  // Schon besetzt
  if (IsOccupied()) return;
  // Betreten
  pObj->Enter(this);
  SetOwner(pObj->GetOwner());
  SetColorDw(pObj->GetColorDw());
  SetAction("Occupied");
  return(1);
  }

private func OnExit(pObj)
  {
  pObj->Exit(0, 0,+4); pObj->SetDir(GetDir());
  SetAction("Empty");
  return(1);
  }

protected func ContainedDigDouble(object pClonk)
{
	CreateMenu(GetID(), pClonk, 0,0, GetName(), 0, 1);
	for(var obj in FindObjects(Find_Or(Find_Func("IsAntiker"), Find_Func("IsAsgard")), Find_Or(Find_Distance(400), Find_ID(ALSK))))
	{
		AddMenuItem(obj->GetName(), Format("Control(Object(%d), Object(%d))", obj->ObjectNumber(), pClonk->ObjectNumber()), obj->GetID(), pClonk);
	}
	return true;
}

private func Control(object obj, object pClonk)
{
	return obj->~ControlDigDouble(pClonk);
}

protected func FxTimerTimer(object pTarget, int pEffect)
{
	if(EnergyCheck(100) && HasEnergy() < 10000)
	{
		if(FindContents(ENAP))
		{
			HasEnergy() += 2000;
		}
		else
		{
			HasEnergy() += 100;
		}
	}
}