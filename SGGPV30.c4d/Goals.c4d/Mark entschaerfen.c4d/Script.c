#strict
#include GOAL   
func ZPMCheck()
{
if(FindObject(TAMA))
  {
   if(GetAction(FindObject(TAMA)) eq "Deactive")
   {
   		return(1);
   	}
  }
}
    
func IsFulfilled()
{
  return(ZPMCheck());
}
 
func Activate(int iPlayer)
{
	MessageWindow("Sie müssen die Mark entschärfen!",iPlayer);
}