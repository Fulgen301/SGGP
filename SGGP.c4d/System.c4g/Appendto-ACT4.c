/*-- ZPMs --*/

#strict 2
#appendto ACT4

local timer;

protected func Construction()
{
    _inherited(...);
    timer = CreateHash();
}

public func ComEnter(object pObj)
{
    _inherited(pObj, ...);
    timer = timer || CreateHash();
    if(GetID(pObj) == ZPM_)
    {
        HashPut(timer, pObj, 50);
        Enter(this, pObj);
    }
}

public func ComFire(object pClonk)
{
  // SetRDir(0)
  SetRDir(0);
  SetAction("Attaching",GetActionTarget());
  
  // Pruefen, ob genug Kristalle zur Verfuegung stehen
  var power;
  var i = 0, obj;
  
  while(obj = Contents(i ++) )
  {
    if(GetID(obj) == CRYS)
    {
      power += (GetCon(obj) - 50);
      if(power >= 50)
        break;
    }
    else if(GetID(obj) == ZPM_)
    {
        power += 300;
        if(power >= 50) break;
    }
  }
  if(power < 50) return(Sound("Error") );
  
  // Kristalle verbrauchen. Beim Pruefen konnten die Kristalle
  // nicht gleichzeitig verbraucht werden, da, wenn die Energie
  // nicht ausreicht, eventuell bereits Kristalle geloescht worden waeren.
  power = 0;
  // Von oben nach unten zaehlen, da Objekte geloescht werden.
  i = ContentsCount();
  while(obj = Contents(-- i) )
  {
    if(GetID(obj) == CRYS)
    {
      // Kraft des Kristalls zur Gesamtkraft hinzufeugen
      power += (GetCon(obj) - 50);
      // Mehr als noetig?
      if(power > 50)
      {
        // Nur das was noetig ist dem Kristall abziehen
        var con = (GetCon(obj) ) - power;
        DoCon(-con, obj);
      }
      else
        // Reicht noch nicht? Kristall ganz verbrauchen.
        RemoveObject(obj);
        
      // Genug power? Ok.
      if(power >= 50)
        break;
    }
    
    else if(GetID(obj) == ZPM_ && GetAction(obj) != "Depledet")
    {
        power += 300;
        HashPut(timer, obj, HashGet(timer, obj) - 1);
        if(HashGet(timer, obj) <= 0)
        {
            obj->~Minus();
            HashPut(timer, obj, 50);
        }
    }
  }

  Sound("LightningCannon");
  
  var lgt1=CreateObject(ADM4, 0, 0, -1);
  lgt1->SetController(pClonk->GetController());
  lgt1->ADM4::Activate(GetX(), GetY(), Sin(GetR(), 18), 4, -Cos(GetR(), 18), 4);
  var lgt2=CreateObject(ADM4, 0, 0, -1);
  lgt2->SetController(pClonk->GetController());
  lgt2->ADM4::Activate(GetX() + Sin(GetR() + 90, 5), GetY() + Cos(GetR() + 90, 5), Sin(GetR(), 18), 4, -Cos(GetR(), 18), 4);
  
  CastParticles("Spark", Random(8) + 4, Random(35), Sin(GetR(), 18), -Cos(GetR(), 18) );
}

