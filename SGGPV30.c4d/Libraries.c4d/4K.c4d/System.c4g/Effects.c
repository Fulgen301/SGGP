#strict

/* Unstuck-Effect */
/*Effekt der Objekte augenfreundlich aus Materialien herauszieht.*/
global func FxIntUnstuck4KStart(object pTarget, int iEffectNumber, int iTemp,iXDir,iYDir)
{
  if(!iXDir && !iYDir)
  {
    for(var j = 10;j < 60;j+=10)
    {
      for(var i = 0;i < 360;i+=45)//In 45° Schritten testen.
      {
        iXDir = Cos(i,j);
        iYDir = Sin(i,j);
        if(!GBackSolid(iXDir,iYDir))
        {
          Normalize4K(iXDir,iYDir);
          EffectVar (0,pTarget,iEffectNumber) = iXDir;
          EffectVar (1,pTarget,iEffectNumber) = iYDir;
          return(1);
        }
      }
    }
    return(-1);
  }
  EffectVar (0,pTarget,iEffectNumber) = iXDir;
  EffectVar (1,pTarget,iEffectNumber) = iYDir;
  return(1);
}

global func FxIntUnstuck4KTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
  if(!Stuck(pTarget))
    return(-1);

  if(iEffectTime > 10)
    return(-1);

  SetPosition(GetX(pTarget)  -  EffectVar (0,pTarget,iEffectNumber),
              GetY(pTarget)  -  EffectVar (1,pTarget,iEffectNumber));

  return(0);
}

global func AutoUnstuck(pTarget,iXDir,iYDir)
{
  AutoUnstuck4K(pTarget,iXDir,iYDir);
}

global func AutoUnstuck4K(pTarget,iXDir,iYDir)
{
  AddEffect ("IntUnstuck4K",pTarget,1,1,pTarget,0,iXDir,iYDir); 
}


/* Rauch-Effect */
/*Effekt der Wraks schön rauchen und brennen lässt.*/
global func FxIntWreckSmoke4KStart(object pTarget, int iEffectNumber, int iTemp,iP,iX,iY,bF)
{
  EffectVar (0,pTarget,iEffectNumber) = iP;
  EffectVar (1,pTarget,iEffectNumber) = iX;
  EffectVar (2,pTarget,iEffectNumber) = iY;
  EffectVar (3,pTarget,iEffectNumber) = bF;
  return(1);
}

global func FxIntWreckSmoke4KTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
  if(!pTarget)
    return(-1);

  var iP = EffectVar (0,pTarget,iEffectNumber);
  var iX = EffectVar (1,pTarget,iEffectNumber);
  var iY = EffectVar (2,pTarget,iEffectNumber);
  
  GetOffset4K(iX,iY);
  
  var vel = Abs(GetXDir(pTarget))+Abs(GetYDir(pTarget));
  var alpha = Max(0,30-vel);
  var black = 40 + Random(40);
  
  if(EffectVar(3,pTarget,iEffectNumber))
    CreateParticle("Thrust",iX,iY,GetXDir()/2,GetYDir()/2,iP + Random(iP/2) + vel/3 + 40,RGBa(255,200,200,60));
  
  CreateParticle("Smoke3",iX,iY,RandomX(-1,1),-Random(5),iP + Random(iP/2) + vel/3,RGBa(black,black,black,alpha)); 

  return(0);
}

global func AddSmokeEffect4K(iStrength,iX,iY,bBurning,pTarget)
{
  if(!pTarget) pTarget = this();
  if(!pTarget) return(0);
  AddEffect ("IntWreckSmoke4K",pTarget,10,2,pTarget,0,iStrength,iX,iY,bBurning);
  return(1);
}


/*SpeedSecure®-Effekt*/
//Das Objekt kann bei hohen Geschwindigkeiten nicht eingesammelt werden.

global func FxIntSpeedSecure4KStart(object pTarget, int iEffectNumber, int iTemp,max_speed)
{
  EffectVar (0,pTarget,iEffectNumber) = max_speed;
  return(1);
}

global func FxIntSpeedSecure4KTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
  if(Distance(GetXDir(pTarget),GetYDir(pTarget)) > EffectVar (0,pTarget,iEffectNumber))
    SetCategory(C4D_Vehicle,pTarget);
  else
    SetCategory(C4D_Object,pTarget);
  return(0);
}

global func FxIntSpeedSecure4KStop(object pTarget, int iEffectNumber, int iReason, bool fTemp)
{
  SetCategory(C4D_Object,pTarget);
  return(-1);
}

global func SetSpeedSecure(iMaxSpeed,pTarget)
{
  if(!pTarget) pTarget = this();
  if(!pTarget) return(false);
  
  if(!iMaxSpeed) iMaxSpeed = 20;
  
  AddEffect ("IntSpeedSecure4K",pTarget,200,5,pTarget,0,iMaxSpeed); 
}


/* CreateScriptPlayer-Effect */
/*Dieser Effekt hilft beim Erstellen von Scriptspielern.*/

/*
global func FxIntWreckSmoke4KStart(object pTarget, int iEffectNumber, int iTemp,szName)
{
  EffectVar (0,pTarget,iEffectNumber) = szName;
  return(1);
}

global func FxIntWreckSmoke4KTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
  if(!pTarget)
    return(-1);

  var iP = EffectVar (0,pTarget,iEffectNumber);
  var iX = EffectVar (1,pTarget,iEffectNumber);
  var iY = EffectVar (2,pTarget,iEffectNumber);
  
  GetOffset4K(iX,iY);
  
  var vel = Abs(GetXDir(pTarget))+Abs(GetYDir(pTarget));
  var alpha = Max(0,30-vel);
  var black = 40 + Random(40);
  
  if(EffectVar(3,pTarget,iEffectNumber))
    CreateParticle("Thrust",iX,iY,GetXDir()/2,GetYDir()/2,iP + Random(iP/2) + vel/3 + 40,RGBa(255,200,200,60));
  
  CreateParticle("Smoke3",iX,iY,RandomX(-1,1),-Random(5),iP + Random(iP/2) + vel/3,RGBa(black,black,black,alpha)); 

  return(0);
}

global func AddScriptPlayer4K(string szCallback, object pCallback, string szName, int dwRGB, int iTeam, int iExtra)
{
  if(!szCallback) szCallback = "ScriptPlayerJoined";
  if(!pCallback) pCallback = this();
  if(!pCallback) return(false);

  if(!szName) szName = "KI";
  if(!dwRGB) dwRGB = RGB(Random(255),Random(255),Random(255));
  
  /*for(var i=GetPlayerCount();i>=0;i--)//Einen einzigartigen Namen machen.
  {
    while(GetPlayerName(i) eq szName)
    {
      szName = Format("%s!",szName);//°,° Psst. WildCradMatch() *flüster*
    }
  }
  
  GetEffectCount (string szMask, object pTarget, int iMaxPriority); 
  
  CreateScriptPlayer (szName,dwRGB,1,CSPF_NoScenarioInit|CSPF_NoEliminationCheck,iExtra);
  AddEffect ("IntWreckSmoke4K",pTarget,10,2,pTarget,0,iStrength,iX,iY,bBurning);
  return(true);
}*/