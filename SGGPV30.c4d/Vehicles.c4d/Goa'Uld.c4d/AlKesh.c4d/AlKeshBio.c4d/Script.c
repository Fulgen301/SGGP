#strict 2
#include SHT1

local glow,iSX;

/* Schuss */

//Extern für Überladung
private func CreateTrail(int iSize, int iTrail)
{
	AddLight(30, RGB(0, 255, 0, ), this, GLOW);
}

private func Traveling()
{
	// effect
	DoR(4);
	if (glow)
		glow->ChangeColor(Color(GetActTime()));
	//CreateParticle("PSpark",0,0,-GetXDir()/4,-GetYDir()/4,RandomX(100,200)*GetCon()/100,
	//               RGBa(64,32,255,100+50*GetActTime()/iTime),this());
	return _inherited();
}

/* Treffer */

public func Timer()
{
	DoR(80);
}

private func Hit()
{

	for (var i = 8 + Random(7), glob; i; i--)
	{
		glob = CreateObject(SLST, 0, 0, GetOwner());
		glob->~Launch(RandomX(-60, 60), RandomX(-60, 60), 8);
	}
	CastParticles("SlimeGrav", 10, 25, 0, 0, 20, 40, RGBa(0, 240, 0, 10), RGBa(20, 255, 20, 75));
	CastParticles("FrSprk", 30, 5, 0, 0, 70, 130, RGBa(0, 240, 0, 10), RGBa(20, 255, 20, 75));
	Sound("SlimeHit");
	Sound("Poff");
	RemoveObject();
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
	// bewegt haben. Und sortieren sie nach Distanz (nähere zuerst)
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
	// Der Schuss wird erst "scharf gemacht", d.h. kann den Schützen selbst treffen, wenn
	// der Schuss einmal die Shape des Schützen verlassen hat.

	// OKOK, Ich hab sogar das Restzeug kommentiert. :P
	if (!EffectVar(5, target, effect))
	{
		if (!EffectVar(4, target, effect))
		{
			// ready gibt an, ob wir schon "scharf" sind. True = Scharf
			var ready = true;
			// Wir suchen alle Objekte mit der ID unseres Schützens an unserer momentanen Stelle
			for (var foo in FindObjects(Find_AtPoint(GetX(target), GetY(target)), Find_ID(EffectVar(3, target, effect)))) 
				if (foo == EffectVar(2, target, effect))
					ready = false;
			// wir haben den Schützen nicht gefunden
			if (ready)
				EffectVar(4, target, effect) = true;
		}
	}
}
public func TrailColor(int iATime)
{
	return Color(iATime);
}
