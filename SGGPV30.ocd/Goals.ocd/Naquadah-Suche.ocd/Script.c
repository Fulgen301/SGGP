#strict
#include GOAL   
func ZPMCheck()
{
if(FindObject(NAQU))
  {
   if(GetID(Contained(FindObject(NAQU))) == SGK_) return(1);
  }
}
    
func IsFulfilled()
{
  return(ZPMCheck());
}
 
func Activate(int iPlayer)
{
	MessageWindow("Sie müssen das Naquadah finden!",iPlayer);
}
local Name = "$Name$";
