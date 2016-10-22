/*--- Mondstaubklumpen ---*/

#strict

protected func Hit()
{
  CastPXS("Mondstaub", 100, 20);
  RemoveObject();
  return(1);
}
