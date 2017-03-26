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