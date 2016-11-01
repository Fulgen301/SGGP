/*-- Lichtkegel --*/

#strict
#include LIGH

// Variablen

local iSizeX, iSizeY, iOffX, iOffY, iR, bDir;
local target;
local on;
local outfade;
local stay;

/*
  iSizeX - X-Größe
  iSizeY - Y-Größe
  iOffX  - Verschiebung der Grafik in X-Richtung
  iOffY  - Verschiebung der Grafik in Y-Richtung
  //Alle Werte in 1000/Pixel
  iR     - Rotation
  bDir   - Wenn true wird ist das X-Offset mit der Dir gespiegelt
*/

// Licht updaten... verändert keine Werte sondern
// passt die Anzeige nur an

func SetTarg(obj)
{
  target = obj;
  SetAction("Attach",obj);
  return(1);
}

public func Update() 
{
  ChangeSizeXY(iSizeX, iSizeY);
  ChangeColor(iColor);
}

public func Check()
{
  if(on)
  {
   stay--;
   if(stay == 0)
   {
    outfade = 1;
    on = 0;
    Sound("DartBlast");
    LocalN("on",LocalN("target",target)) = 0;
   }
  }
  
  if(outfade)
  {
   if(GetCon() == 10)
   {
    outfade = 0;
    TurnOff();
    on = 0;
    return(1);
   }
   
   if(GetCon() != 10)
   {
    DoCon(-10);
    return(1);
   }
  }


  if(GetCon() != 100)
  {
   DoCon(10);
   return(1);
  }
  
  if(!on)
  {
   return(1);
  }
  
  if(FindObject2(Find_InRect(-20,0,40,128),Find_OCF(OCF_Alive()),Find_OCF(OCF_InFree())))
  {
   var hecl;
   hecl = FindObject2(Find_InRect(-20,-0,40,128),Find_OCF(OCF_Alive()),Find_OCF(OCF_InFree()));
   if(PathFree(GetX(target),GetY(target),GetX(hecl),GetY(hecl)))
   {
    hecl -> Enter(target);
    Sound("DartButton");
   }
  }
  return(1);
}

public func ChangeSize(int iNewSize) { 
  ChangeSizeXY(iNewSize,iNewSize);
}

public func ChangeSizeXY(int iNewSizeX, int iNewSizeY) {

  iSizeX = iNewSizeX;
  iSizeY = iNewSizeY;

  Draw();
}

public func ChangeOffset(int iNewOffX, int iNewOffY, bool bNewDir) {
  iOffX = iNewOffX;
  iOffY = iNewOffY;
  bDir = bNewDir;
  Draw();
}

public func ChangeR(int iNewR) {
  iR = -iNewR;
  Draw();
}

public func Draw() {
  var dir;
  if(!bDir) dir = 1;
  else      dir = 1-GetDir(GetActionTarget())*2;
  
  var alphamod, sizemod;
  CalcLight(alphamod, sizemod);
  
  var fsin, fcos, xoff, yoff;
  fsin = Sin(iR, 1000);
  fcos = Cos(iR, 1000);
  xoff = 0;
  yoff = +64;
  
  var width = iSizeX*sizemod/100, height = iSizeY*sizemod/100;
  
  SetObjDrawTransform(
    +fcos*width/1000, +fsin*height/1000, (((1000-fcos)*xoff - fsin*yoff)*height)/1000+iOffX*1000*dir,
    -fsin*width/1000, +fcos*height/1000, (((1000-fcos)*yoff + fsin*xoff - 64000)*height)/1000+iOffY*1000
  );
}
local ActMap = {

Attach = {

Prototype = Action,

Name = "Attach",

Procedure = DFA_ATTACH,

NextAction = "Attach",

Length = 5,

Delay = 1,

X = 0,

Y = 0,

Wdt = 128,

Hgt = 128,

},  };
local Name = "$Name$";
