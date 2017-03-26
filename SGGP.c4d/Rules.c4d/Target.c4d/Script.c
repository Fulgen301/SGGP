/* Zielscheibe */

#strict


protected func Initialize()
{
  SetEntrance(1);
  SetClrModulation(RGBa(255,255,255,150));
  SetAction("Exist");
  return(1);
}

protected func Damage(int iChange,int byPlr)
{
  DoWealth(byPlr,5);
  CastObjects(TGTP,4,15,0,0);
  CastParticles("Light",100,150,0,0,80,80,RGBa(20,20,20,0),RGBa(20,20,20,0));
  Sound("GlassBreak");
  RemoveObject();
  return(1);
}

protected func RejectCollect(Id, obj)
{
  if(GetOCF(obj)&OCF_HitSpeed2()) {ProtectedCall(obj,"ContactTop");ProtectedCall(obj,"Hit");}
  return(Damage());
}

protected func Check()
{
  var obj;
  if (obj = FindObject(0,1,0,0,0, OCF_CrewMember(),0,0,NoContainer()))
    return(Damage());
  return(1);
}