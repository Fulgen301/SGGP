/*-- Pumpe --*/

#strict
#appendto PUMP

public func GetTriggerName(a)
{
	if(a==1)
	{
		return("START");
	}
	if(a==2)
	{
		return("STOP");
	}
  return(1);
}

public func Trigger(a,pSensor)
{
	if(a==1)
	{
		return(SetAction("Pump"));
	}
	if(a==2)
	{
		return(SetAction("Wait"));
	}
        return(1);	
}
