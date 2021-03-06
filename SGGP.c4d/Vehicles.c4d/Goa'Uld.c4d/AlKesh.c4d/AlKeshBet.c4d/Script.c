#strict 2
#include SHT1
local iLevel,iY;
local glow,iSX;

/* Schuss */

//Extern f�r �berladung
private func CreateTrail(int iSize, int iTrail)
{
	AddLight(30, RGB(0, 255, 0, ), this, GLOW);
}

private func Traveling()
{
	// effect
	if (glow)
		glow->ChangeColor(Color(GetActTime()));
	//CreateParticle("PSpark",0,0,-GetXDir()/4,-GetYDir()/4,RandomX(100,200)*GetCon()/100,
	//               RGBa(64,32,255,100+50*GetActTime()/iTime),this());
	return _inherited();
}

public func Timer()
{
	DoR(60);
}
/* Treffer */

private func Hit()
{

	if (iY)
		return;
	iY = 1;
	ScheduleCall(this, "DidIt", 50, 0);
	ScheduleCall(this, "Do", 1, 50);
	Sound("Gobe");
}


public func DidIt()
{
	var pObj;
	for (pObj in FindObjects(Find_Distance((iLevel * 10) / 2), Find_OCF(OCF_Alive))) 
		if(pObj) pObj->~Zated();
	RemoveObject();
}

public func Do()
{
	iLevel++;
	CreateParticle("Flash", 0, 0, 0, 0, iLevel * 50, RGBa(255, 255, 255, Random(120)));
}

public func BulletStrike(object pObj)
{

	if(pObj) pObj->~Zated();
	return 1;
}

private func Color(int iATime)
{
	var iPrg = 100 * iATime / iTime;
	return RGBa(0, 0, 255, iPrg * 2);
}

private func GlowColor(int iATime)
{
	var iPrg = 100 * iATime / iTime;
	return RGBa(0, 0, 255, 130);
}

public func FxHitCheckTimer(object target, int effect, int time)
{
	var obj;
	// Oh man. :O
	var oldx = EffectVar(0, target, effect);
	var oldy = EffectVar(1, target, effect);
	var newx = GetX(target);
	var newy = GetY(target);
	var dist = Distance(oldx, oldy, newx, newy);
	EffectVar(0, target, effect) = GetX(target);
	EffectVar(1, target, effect) = GetY(target);

	// Schuss schon Scharf?
	var exclude = EffectVar(2, target, effect);
	// Ja, wir treffen nur uns selbst nicht (ja, Workaround .)
	if (EffectVar(4, target, effect))
		exclude = target;

	//DrawParticleLine("NoGravSpark", newx - oldx, newy - oldy, 0, 0, 1, 25, RGB(255, 0, 0), RGB(0, 0, 255));
	// Wir suchen nach Objekten entlang der Linie die wir uns seit dem letzten Check
	// bewegt haben. Und sortieren sie nach Distanz (n�here zuerst)
	for (obj in FindObjects(Find_OnLine(oldx, oldy, newx, newy), Find_NoContainer(), Sort_Distance(oldx, oldy))) 
	{
		// Excludes
		if (obj == target)
			continue;
		if (obj == exclude)
			continue;
		// CheckEnemy
		if (!CheckEnemy(obj, target))
			continue;
		// IsBulletTarget oder Alive
		if (obj->~IsBulletTarget(GetID(target), target, EffectVar(2, target, effect)) || GetOCF(obj) & OCF_Alive)
			if (GetAction(obj) != "Dead")
			{
				DebugLog("%s IsBulletTarget: %i, %s, %s", "HitCheck", GetName(obj), GetID(target), GetName(target), GetName(EffectVar(2, target, effect)));
				return target->~HitObject(obj);
			}
	}

	EffectVar(0, target, effect) = GetX(target);
	EffectVar(1, target, effect) = GetY(target);

	//verdammt, kommentier doch mal... Also:
	// Der Schuss wird erst "scharf gemacht", d.h. kann den Sch�tzen selbst treffen, wenn
	// der Schuss einmal die Shape des Sch�tzen verlassen hat.

	// OKOK, Ich hab sogar das Restzeug kommentiert. :P
	if (!EffectVar(5, target, effect))
	{
		if (!EffectVar(4, target, effect))
		{
			// ready gibt an, ob wir schon "scharf" sind. True = Scharf
			var ready = true;
			// Wir suchen alle Objekte mit der ID unseres Sch�tzens an unserer momentanen Stelle
			for (var foo in FindObjects(Find_AtPoint(GetX(target), GetY(target)), Find_ID(EffectVar(3, target, effect)))) 
				if (foo == EffectVar(2, target, effect))
					ready = false;
			// wir haben den Sch�tzen nicht gefunden
			if (ready)
				EffectVar(4, target, effect) = true;
		}
	}
}
public func TrailColor(int iATime)
{
	return Color(iATime);
}
