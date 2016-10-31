#strict
#include GOAL   
func ZPMCheck()
{
if(FindObject(ZPM_))
  {
   if(FindObject(ZPST))
   {
    if(FindContents(ZPM_,FindObject(ZPST)))
    { 
     Sound("Applause",1);
     return(1);
    }
   }
  }
}
    
func IsFulfilled()
{
  return(ZPMCheck());
}
 
func Activate(int iPlayer)
{
	MessageWindow("Sie müssen das ZPM unversehrt in die Konsole packen!",iPlayer);
}
local Name = "$Name$";
