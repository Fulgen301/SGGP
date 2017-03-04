/*-- Particle Cannon --*/

#strict 2
#include FLAK

private func CalculateRifle(&oX, &oY)
{
	var angle = Crosshair->GetAngle() + GetR();

	// Korrektur für Mitte (speziell für diese Grafik)
	var correction = CenterFix();
	
	var x = +Sin(angle, 25-(correction/5));
	var y = -Cos(angle, 15+correction/20);
	
	// circle x,y
	// min->max breite: 0->4
	// min->max höhe: 1->2
	var cx, cy;
	cx = correction/25;
	cy = 2 - correction/90;
	
	x += Sin(30+180*Rifle, cx);
	y += Cos(60+180*Rifle, cy);
	
	if(++Rifle > 1)
		Rifle = 0;
	
	oX = x;
	oY = y-3;
}

/** Waffenzeugs **/

public func FMData1(int data)
{
	if(data == FM_Name)			return("$Auto$");
	if(data == FM_AmmoID)		return(ENAM);

	if(data == FM_AmmoLoad)		return(40);
	if(data == FM_AmmoRate)		return(1);
	if(data == FM_AmmoUsage)	return(10);

	if(data == FM_Reload)		return(100);
	if(data == FM_Recharge)		return(80);

	if(data == FM_Damage)		return(80);
	if(data == FM_Auto)			return(false);

	return(Default(data));
}

public func Fire1()    // Projektilschuss
{ 
  var user = GetUser();
  var angle = Crosshair->GetAngle() + GetR();
  var x,y; CalculateRifle(x, y);
  var ammo = CreateObject(STBS,x,y,GetController(user));
  ammo->Launch(angle,250,600,5,300,GetFMData(FM_Damage, 1));

  // Effekte
  MuzzleFlash(40,user,x,y,angle);
  var dir = GetDir(user)*2-1;
  BulletCasing(dir*6,3,-dir*5,-20,5);

  // Sound
  Sound("LaunchSW",0,ammo);
  Reload();
}


public func ControlLeft()
{
    [$TxtLeft$|Image=TAN2:1]
	_inherited(...);
}

public func ControlRight()
{
    [$TxtRight$|Image=TAN2:2]
	_inherited(...);
}

public func ControlThrow()
{
    [$TxtFire$|Image=TAN2:0]
	_inherited(...);
}

public func GetRace() { return SG1_Goauld; }