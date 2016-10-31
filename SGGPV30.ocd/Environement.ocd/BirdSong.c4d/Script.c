/*-- Vogelgezwitscher --*/

#strict

protected func Initialize()
{
  SetAction("Sing");
  return(1);
}

private func Singing()
{
  // Bei Tag singen sie
    Sound("BirdSong1",1);
}  
local ActMap = {
Sing = {
Prototype = Action,
Name = "Sing",
Length = 1,
Delay = 25,
NextAction = "Sing",
StartCall = "Singing",
},  };
local Name = "$Name$";
