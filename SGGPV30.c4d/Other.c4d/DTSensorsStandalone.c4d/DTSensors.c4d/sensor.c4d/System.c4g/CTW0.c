/*-- Pumpe --*/

#strict
#appendto CTW0

public func GetTriggerName(a)
{
	if(a==1)
	{
		return("TURN_LEFT");
	}
	if(a==2)
	{
		return("TURN_RIGHT");
	}
	if(a==3)
	{
		return("STOP");
	}
	if(a==4)
	{
		return("SHOOT");
	}
  return(1);
}

public func Trigger(a,pSensor)
{
	if(a==1)
	{
		return(ContainedLeft(pSensor));
	}
	if(a==2)
	{
		return(ContainedRight(pSensor));
	}
	if(a==3)
	{
		return(ContainedUp(pSensor));
	}
	if(a==4)
	{
		return(ContainedDig(pSensor));
	}
        return(1);	
}
