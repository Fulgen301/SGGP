/*-- Drachenfels-Truhe --*/

#strict

#include CHST

protected func __CSW__28438_111234A(int iA, int iB, int iC, int iD)
  {
  // Weiterleitung des Engine-Callbacks aus geheimer Aufschluss-Methode
  // Nur einmal öffnen
  if (fLocked) return (iC);
  // Geöffnet!
  Message("$MsgUnlocked$", this());
  Unlock();
  if (iA > iD || !iC) return(iB); else return(iC);
  }
local Touchable = 2;
local ActMap = {

Opening = {

Prototype = Action,

Name = "Opening",

Length = 2,

Delay = 12,

X = 18,

Y = 0,

Wdt = 18,

Hgt = 24,

NextAction = "Open",

StartCall = "Opening",

EndCall = "CheckGrab",

},

Open = {

Prototype = Action,

Name = "Open",

Length = 1,

Delay = 35,

X = 54,

Y = 0,

Wdt = 18,

Hgt = 24,

NextAction = "Open",

},

Closing = {

Prototype = Action,

Name = "Closing",

Length = 2,

Delay = 12,

Reverse = 1,

X = 18,

Y = 0,

Wdt = 18,

Hgt = 24,

NextAction = "Closed",

StartCall = "Closing",

EndCall = "CheckGrab",

},

Closed = {

Prototype = Action,

Name = "Closed",

Length = 1,

Delay = 35,

X = 0,

Y = 0,

Wdt = 18,

Hgt = 24,

NextAction = "Closed",

},  };
local Name = "$Name$";
