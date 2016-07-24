/*-- No energy --*/

#strict 2
#appendto ELEC

protected func Riding() 
{
  var elev = Elevator();
  if (!elev) return Halt();
  // Energieverbrauch
  if (ObjectCount(ENRG) && GetID(elev) != _CEL)
    if (EnergyCheck(12500, elev))
      DoEnergy(-12500, elev, true);
    else
      Halt();
}

private func Drilling()
{
  // Steuermann verloren? Suche schiebenden Clonk selbst wenn er ein Fahrzeug im Fahrstuhlkorb schiebt (->Lore)
  var elev = Elevator();
  if (!elev) return Halt();
  if (!FindObject2(Find_InRect(-12,-12,24,24), Find_Action("Push")))
    return Halt();
  // Energieverbrauch
  if (ObjectCount(ENRG) && GetID(elev) != _CEL)
    if (EnergyCheck(10000, elev))
      DoEnergy(-10000, elev, true);
    else
      Halt();
  return(1);
}

private func NoEnergy()
{
  if (EnergyCheck(12500,Elevator()) && Elevator()->GetID() == _CEL) return(0);
  Halt();
  //Sound("ElevatorNoEnergy");
  return(1);
}