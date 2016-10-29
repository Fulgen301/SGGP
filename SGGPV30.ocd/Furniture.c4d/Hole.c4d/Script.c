#strict

protected func CastSparks() {
  // Ab und zu mal
  if (Random(8)) return(0);
  Sound("Electric");
  CastParticles("MSpark", 10, 10, 0, +3, 10, 50, RGB(RandomX(100, 150), RandomX(200, 255), 255), RGB(RandomX(100, 150), RandomX(200, 255), 255));
}