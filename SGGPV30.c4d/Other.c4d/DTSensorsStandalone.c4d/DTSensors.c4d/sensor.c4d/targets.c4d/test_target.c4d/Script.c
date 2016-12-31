/*-- Statue --*/

#strict
#include IDOL


/*
  Die verschiedenen Aktionen des Sensor-Ziels.
*/
public func GetTriggerName(int a)
{
	if(a==1)//Pink f�rben.
	{
		return("PINK");
	}
  
	if(a==2)//Entf�rben.
	{
		return("NORMAL");
	}
  
  return(true);//Muss immer TRUE zur�ckgeben!
}

/*
  Hier werden die Aktionen ausgel�st.
*/
public func Trigger(a)
{
	if(a==1)//Pink f�rben.
	{
		SetClrModulation (RGBa(255,0,128,0),this());
	}
  
	if(a==2)//Entf�rben.
	{
		SetClrModulation (RGBa(0,0,0,0),this());
	}
  
  return(true);	
}