/*-- Wandnachricht --*/



local sText; // Text string

protected func Initialize()
  {
  SetAction("Walling");
  }

protected func ControlUp(object pPlayer)
  { [$CtrlRead$]
  return(Message("\"%s\"", pPlayer, sText));
  }

public func SetText(string sToText)
  {
  sText = sToText;
  return(true);
  }

global func AssignWScriptText(string sScriptName, string sToText)
  {
  var obj;
  while (obj = FindObject(_WSC, 0,0,0,0, 0, 0,0, 0, obj))
    if (obj->GetName() eq sScriptName)
      {
      obj->SetText(sToText);
      obj->SetName();
      return(true);
      }
  }
local Touchable = 1;
local ActMap = {
Walling = {
Prototype = Action,
Name = "Walling",
Procedure = DFA_FLOAT,
Length = 1,
Delay = 0,
FacetBase = 1,
},  };
local Name = "$Name$";
