/*--- Naquadah ---*/

#strict 2

func Hit () {
  Sound("RockHit*");
}

protected func Damage()
{
  // Explodiert nicht, wenn er von einem Clonk getragen wird (Sonderregel gegen T-Flint-Superjumps)
  if (Contained() && Contained()->~IsClonk())
  {
      Extinguish();
      return 0;
  }
  // Explosion - verz�gert, um Endlosrekursion zu verhindern
  Schedule("Explode(40)", 1);
  return 1;
}

// Entz�ndet sich bei Explosionstreffer
public func OnShockwaveHit(level, x, y)
{
 Incinerate();
}

func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(200); }