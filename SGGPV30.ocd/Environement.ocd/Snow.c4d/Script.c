/*-- Schneien --*/

#strict

protected func Initialize() {
  if(!IsNewgfx()) RemoveObject();
  SetPosition(0,0);
}

protected func Snowing(){
  var dir = BoundBy(GetWind(),-1,1);
  PushParticles("Snow",dir*Random(4));
  for(var x; x < 10; x++)
   {
    var size = RandomX(10,60);
    var xdir = BoundBy(GetWind(),-25,25)+RandomX(-5,5),
        ydir = (size/2*GetGravity())/100;
    var offset = LandscapeHeight()*2/3;
    CreateParticle("Snow",Random(LandscapeWidth()+offset)-offset/2-offset/2*dir,0,xdir,ydir,size,0);
   }
  return(1);
}
local Name = "$Name$";
