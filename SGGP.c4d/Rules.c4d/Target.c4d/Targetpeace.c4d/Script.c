/* Zielscheibenteil */

#strict

local i;


protected func Initialize()
{
  SetRDir(RandomX(-50,50),this());
  SetAction("FadeOut");
  return(1);
}

private func FadeOut()
{
  DoCon(-1);
  i+=20;
  if(i>=240) RemoveObject();
  SetClrModulation(RGBa(255,255,255,i));
  if(GetActTime()>50) RemoveObject();
  return(1);
}

