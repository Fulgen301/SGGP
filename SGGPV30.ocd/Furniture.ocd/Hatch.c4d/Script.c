#strict

Initialize:
  PutSolidMask();
  return(1);

CheckArea:
  // Clonk unter der Klappe suchen
  SetVar(0,FindObject(0, -10,10,24,20, OCF_CrewMember()));
  // Automatisch �ffnen
  if (Var(0)) ControlUp();
  return(1);
  
// Schlie�t die Luke
ControlDownSingle:
  // Wenn Luke bereits zu, keine Aktion
  if ( SEqual( GetAction(),"Idle" ) ) return(0);
  // Sonst Luke schlie�en
  SetAction("CloseHatch");
  Sound("Airlock2");
  return(1);

// �ffnet die Luke
ControlUp:
  // Wenn Luke bereits offen, keine Aktion
  if ( SEqual( GetAction(),"HatchOpen" ) ) return(0);
  // Sonst Luke �ffnen
  SetAction("OpenHatch");
  Sound("Airlock1");
  return(1);

// Entfernt die SolidMask    
RemoveSolidMask:
  SetSolidMask();
  return(1);

// Stellt SolidMask wieder her
PutSolidMask:
  SetSolidMask(4,14,16,2,4,14);
  return(1);
        
  
local Touchable = 2;
local ActMap = {
OpenHatch = {
Prototype = Action,
Name = "OpenHatch",
Procedure = DFA_NONE,
Length = 5,
Delay = 5,
X = 0,
Y = 0,
Wdt = 27,
Hgt = 23,
FacetBase = 1,
NextAction = "HatchOpen",
StartCall = "RemoveSolidMask",
},
HatchOpen = {
Prototype = Action,
Name = "HatchOpen",
Procedure = DFA_NONE,
Delay = 50,
X = 135,
Y = 0,
Wdt = 27,
Hgt = 23,
FacetBase = 1,
NextAction = "HatchOpen",
},
CloseHatch = {
Prototype = Action,
Name = "CloseHatch",
Procedure = DFA_NONE,
Length = 1,
Delay = 2,
X = 96,
Y = 0,
Wdt = 24,
Hgt = 20,
OffX = 0,
OffY = 0,
NextAction = "HatchClosed",
},
HatchClosed = {
Prototype = Action,
Name = "HatchClosed",
Procedure = DFA_NONE,
Length = 5,
Reverse = 1,
Delay = 5,
X = 0,
Y = 0,
Wdt = 27,
Hgt = 23,
FacetBase = 1,
NextAction = "Idle",
EndCall = "PutSolidMask",
},  };
local Name = "$Name$";
