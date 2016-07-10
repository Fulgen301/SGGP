#strict
global func FindTargets(object pObj, int maxDist, int maxAngle, int angle, bool disregardLineOfSight) {

  if(!pObj)
    pObj = this;

  if(!maxAngle)
    maxAngle = 180;
	
  var pT;
  var targets = CreateArray();
  
  var x = GetX(pObj);
  var y = GetY(pObj);

  var preTargets = FindObjects(
		Find_Distance(maxDist, AbsX(x), AbsY(y)),
		Find_Exclude(pObj),
        Find_NoContainer(),
        Find_Or(
                Find_Func("IsBulletTarget",GetID(pObj),0,pObj),
                Find_OCF(OCF_Alive)),
		Sort_Distance()
		//Find_Hostile(GetOwner()),  // schon in CheckEnemy drin
        );
  
  for(pT in preTargets) {
		var ox = GetX(pT);
		var oy = GetY(pT);
	
		if(!CheckEnemy(pT,pObj, true)) {
			continue;
		}
	
		// Pfad frei
		if(!disregardLineOfSight)
			if(!PathFree(x,y,ox,oy))
				continue;
		
		// Im Suchkegel
		var diffAngle = Abs(Normalize(Angle(x,y,ox,oy)-angle,-180));
		if(diffAngle > maxAngle)
		    continue;
		// dann rein in Ergebnismenge...
		targets[GetLength(targets)] = pT;
	}
	
	return targets;
}