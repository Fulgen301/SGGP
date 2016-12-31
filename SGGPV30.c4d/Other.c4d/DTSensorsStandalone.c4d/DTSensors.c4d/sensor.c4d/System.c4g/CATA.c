/*-- Pumpe --*/

#strict
#appendto CATA

public func GetTriggerName(a)
{
	if(a==1)
	{
		return("TURN_UP");
	}
	if(a==2)
	{
		return("TURN_DOWN");
	}
	if(a==3)
	{
		return("LEFT");
	}
	if(a==4)
	{
		return("RIGHT");
	}
	if(a==5)
	{
		return("SHOOT");
	}
	if(a==6)
	{
		return("AUTO_SHOOT");
	}
  return(1);
}

public func Trigger(a,pSensor,pSpecial)
{
	if(a==1)
	{
		return(AimUp(pSensor, 1, "ControlConf"));
	}
	if(a==2)
	{
		return(AimDown(pSensor, 1, "ControlConf"));
	}
	if(a==3)
	{
		return(SetDir (DIR_Left));
	}
	if(a==4)
	{
		return(SetDir (DIR_Right));
	}
	if(a==5)
	{
		return(Fire());
	}
	if(a==6)
	{
          if(pSpecial)
            if(Distance(GetX(),GetY(),GetX(pSpecial),GetY(pSpecial))>50)
              return(FireAt(GetX(pSpecial),GetY(pSpecial)));
	}
        return(1);	
}
