#strict
#include SHT1

local glow;

/* Schuss */

//Extern f�r �berladung
private func CreateTrail(int iSize, int iTrail) {
  //glow = AddLight(100,RGB(255,20,20),this(),GLOW);
  
  pTrail = CreateObject(TRAI,0,0,-1);
  if(pTrail) {
    pTrail->Set(iSize+2,iTrail,this());
    pTrail->SetAction("Travel2");
    SetObjectBlitMode(GetObjectBlitMode(),pTrail);
  }
}

private func Traveling()
{
  // effect
  if(glow)
    glow->ChangeColor(Color(GetActTime()));
  //CreateParticle("PSpark",0,0,-GetXDir()/4,-GetYDir()/4,RandomX(100,200)*GetCon()/100,
  //               RGBa(64,32,255,100+50*GetActTime()/iTime),this());
  return(_inherited());
}

public func Hit()
{
  Explode(8);
  return(1);
}

/* Treffer */

private func HitObject(object pObject) {
  if(BulletStrike(pObject)) {
    LaserLight(RandomX(30,50), Color(GetActTime()),0,0,10);
    Remove();
  }
}

public func BulletStrike(object pObj) {
  if(pObj)
  {
	  if(pObj->~GetOCF() & OCF_Living)
	  {
		  DoDmg(RandomX(145,160),DMG_Energy, pObj, iPrec);
		  return 1;
	  }
	else DoDmg(iDamage, DMG_Energy, pObj, iPrec);
  }
  return(1);
}

private func Color(int iATime) {
  var iPrg = 100*iATime/iTime;
  return(RGBa(255,204,0,iPrg*2));
}

private func GlowColor(int iATime) {
  var iPrg = 100*iATime/iTime;
  return(RGBa(255,204,0,130));
}

public func TrailColor(int iATime) { return(Color(iATime)); }
