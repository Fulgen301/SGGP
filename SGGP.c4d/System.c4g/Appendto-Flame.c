/*-- Flammen zünden Objekte an --*/

#strict 2

#appendto FFLM

protected func Flying()
{

  if(InLiquid()) {
    // Blubberblubber
    for(var i=0; i<5; ++i) Bubble(RandomX(-5,+5),RandomX(-5,5));
    RemoveObject();
	return;
  }

  if(GetActTime() > MaxLifeTime()-Random(5)) {
    RemoveObject();
    return;
  }
  
  if(!Random(4) && GetActTime() > MaxLifeTime()/4)
    SetYDir(GetYDir()+RandomX(-4,2));

  if(slimy)
  {
    CastSlimeEffects(GetActTime());
  }
  else
  {
    CastFireEffects(GetActTime());
    var target;
			for (target in FindObjects(Find_Distance(10),Find_OCF(OCF_Inflammable),Find_NoContainer()))
			{
				target->~Incinerate();
			}
  }
}

