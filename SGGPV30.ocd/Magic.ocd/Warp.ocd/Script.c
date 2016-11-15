/* Warp */



public func Activate(caster) {
  // Zaubernden Clonk finden
  var clonk = caster;
    
  if (Contained(clonk))
    if (Contained(clonk)->~IsGolem())
      clonk = clonk->Contained();

  // Und warpen.
  return(Warp(clonk));
}

private func Warp(clonk)
{ 
  // Warpposition finden
  var ox, oy;
  var pos = GetWarpPosition();
  ox = pos[0];
  oy = pos[1];
  
  // Keine passende Warpposition
  if(ox == -1 && oy == -1) return clonk->Message("$TxtNoPlace$");

  // Objekt wird vorsichtshalber nach draußen versetzt
//  Exit(clonk);
  
  // Die akustische Kulisse darf nicht fehlen
  Sound("Magic1");
  
  // Richtungsfaktor ermitteln
  var dir = GetDir(clonk);
  if(dir == DIR_Left ) dir = -1;
  
  // Warplöcher erzeugen
  var startwarp = CreateObject(Warp, BoundBy(65 * dir, -GetX(), LandscapeWidth() - GetX()), 10, -1);
  var helper = CreateObject(Rock,AbsX(ox), AbsY(oy), -1);
  helper.Visibility = VIS_None;
  
  var stargate = helper->FindObject(Find_Func("IsStargate"), Find_Not(Find_Func("IsBusy")), helper->Find_Distance(200));
  if(stargate)
  {
	  startwarp->Connect(stargate);
  }
  else
  {
	var endwarp = CreateObject(Warp, AbsX(ox), AbsY(oy), -1);
  
	// Warplöcher verbinden
	startwarp->Connect(endwarp);
  }
  if(helper) helper->RemoveObject();
 
  // Fertisch
  RemoveObject();
  return(1);
}

private func GetWarpPosition()
{
  var x, y;
  var i;
  while(1)
  {
    var obj = PlaceAnimal(Wipf);
    if(!obj)
      x = y = -1;
    else
      { x = obj->GetX(); y = obj->GetY(); }
    var n = (ObjectDistance(obj) < 100) && ((i++) < 100);
    obj->RemoveObject();
    if(!n) break;
  }
  
  return [x, y];
}

public func GetSpellClass(object pMage) { return; }
public func GetSpellCombo(pMage) { return ("144"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
local Name = "$Name$";
