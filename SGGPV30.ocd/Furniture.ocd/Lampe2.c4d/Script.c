#strict
local licht;

protected Blinken:
  if(Not(Global(1001)==2))return(1);
  ++licht;
  if(licht==30)CreateParticle("Lichtlein",-13,-40,0,0,80,RGBa(255,0,0,0));
  if(licht==32)CreateParticle("Lichtlein",-13,-32,0,0,80,RGBa(255,0,0,0));
  if(licht==34)CreateParticle("Lichtlein",-4,-19,0,0,80,RGBa(0,255,0,0));
  if(licht==36)licht=0;
  return(1);
local Name = "Lampe2";
