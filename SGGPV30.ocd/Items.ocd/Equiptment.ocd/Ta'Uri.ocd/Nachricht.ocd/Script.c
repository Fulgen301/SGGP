/*-- Nachricht --*/



local Nachricht;

public func Activate(Leser){
  MessageWindow(Nachricht, GetOwner(Leser));
  return(1);
}

func Set(brief){Nachricht = brief;return(1);}
local Name = "$Name$";
local Collectible = 1;
