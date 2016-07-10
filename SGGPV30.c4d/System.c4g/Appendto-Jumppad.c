/*-- Jumppads lassen Replikatoren in Frieden --*/

#strict 2
#appendto JPTP

private func CheckBounce() // Timer um Clonks wegzustoßen
{
  if(EMPShocked())
  	return;
  for(var pClonk in FindObjects(Find_InRect(-8, -8, 16, 16), Find_Or(Find_OCF(OCF_Alive),Find_Func("IsBouncy")), Find_Not(Find_Func("IsRepli")), Find_NoContainer()))
    Bounce(pClonk);
}