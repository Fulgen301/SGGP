#strict
#appendto MEDI
func FxMedipackHealStart(object pTarget, int iEffectNumber, int iTemp, int iHealAmount, int iHealRate) {
  if(iTemp)
    return();

  EffectVar(0,pTarget,iEffectNumber) = iHealAmount; //Heilung Insgesamt
  EffectVar(30,pTarget,iEffectNumber) = iHealRate; //1 Punkt Heilung alle iHealRate-Frames
}