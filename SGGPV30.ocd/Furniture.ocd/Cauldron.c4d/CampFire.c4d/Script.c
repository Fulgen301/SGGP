/*-- Lagerfeuer --*/



protected func Initialize() {
  CreateContents(WOOD);
  BurnWood();
}

private func Smoking() {
  //if(!Random(2))
    Smoke(Random(3),Random(3),Random(8)+5);
}

protected func CheckContents() {
  if(GetActTime()>5000)
    SetAction("Idle");
  if(ActIdle())
    if(ContentsCount(WOOD))
      return(BurnWood());
}

private func BurnWood() {
  var pWood;
  if(pWood=FindContents(WOOD)) RemoveObject(pWood);
  Sound("Inflame");
  SetAction("Burn");
}

// auﬂer Holz nichts aufnehmen
protected func RejectCollect(idType,pObj) { if(idType!=WOOD) return(1); }
local Touchable = 2;
local ActMap = {
Burn = {
Prototype = Action,
Name = "Burn",
Procedure = DFA_NONE,
Length = 20,
Delay = 3,
X = 20,
Y = 0,
Wdt = 20,
Hgt = 25,
FacetBase = 0,
NextAction = "Burn",
PhaseCall = "Smoking",
},  };
local Name = "$Name$";
