/*-- Gefundener Schlüssel --*/



local iKeyIndex, fPerma;

/* Initialisierung */

protected func Initialize()
  {
  SetAction("Float");
  return(true);
  }
  
public func InitAsKey(int iIndex)
  {
  SetAction("Float");
  SetDir(iKeyIndex = iIndex);
  CreateParticle("MaterialSpark", 0,0, 0,0, 100, RGBa(255,255,0,0));
  Sound("KeyArrival", true);
  return(true);
  }
  
public func InitAsFireball()
  {
  SetAction("Fireball");
  Incinerate();
  SetObjectLayer(this());
  CreateContents(METO);
  return(true);
  }
  
public func SetPermanentFire() { fPerma=true; }

public func InitAsFire(bool fPermanent)
  {
  fPerma = fPermanent;
  SetAction("Fire");
  Incinerate();
  SetObjectLayer(this());
  CreateContents(METO);
  }
  
  
/* Aktivität */

protected func Floating() // StartCall: Float
  {
  if (!Random(20)) Sparkle(0, 0, 255,255,0, true);
  }
  
protected func Glowing() // TimerCall
  {
  var iPhase = 0; // FrameCounter()*4+iKeyIndex*180/KEY_MAXKEYS;
  SetClrModulation(RGBa(255, 255, 255, Sin(iPhase, 127)+128));
  }
  
protected func Fireballing()
  {
  CreateObject(GetID(), 0,10,GetOwner())->InitAsFire(fPerma);
  }
  
protected func Firing()
  {
  if (!fPerma) DoCon(-8);
  }
  
  
/* Hilfsfunktionen */
  
private func Sparkle(int x, int y, int r, int g, int b, bool allow_big_sparkles) {
  // Entweder einen kleinen, starken Blitzer...
  if(Random(3) || !allow_big_sparkles)
    CreateParticle("MaterialSpark", x,y, 0,0, 5*5+Random(5*5), RGBa(r,g,b,0)); 
  // ...oder ein größeres, schwaches Leuchten
  else
    CreateParticle("MaterialSpark", x,y, 0,0, 10*5+Random(40*5), RGBa(r,g,b,192+Random(64)));
  return(1);
}
local ActMap = {
Float = {
Prototype = Action,
Name = "Float",
Procedure = DFA_FLOAT,
Directions = 7,
Length = 1,
Delay = 10,
X = 0,
Y = 0,
Wdt = 20,
Hgt = 20,
NextAction = "Float",
StartCall = "Floating",
},
Fireball = {
Prototype = Action,
Name = "Fireball",
Procedure = DFA_FLOAT,
Directions = 1,
Length = 1,
Delay = 10,
X = 0,
Y = 0,
Wdt = 1,
Hgt = 1,
NextAction = "Fireball",
StartCall = "Fireballing",
},
Fire = {
Prototype = Action,
Name = "Fire",
Procedure = DFA_FLOAT,
Directions = 1,
Length = 1,
Delay = 10,
X = 0,
Y = 0,
Wdt = 1,
Hgt = 1,
NextAction = "Fire",
StartCall = "Firing",
},  };
local Name = "FlyingKey";
