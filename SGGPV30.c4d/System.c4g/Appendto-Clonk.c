#strict

#appendto CLNK

func ContextRelease(pCaller) 
{
	[$HelpRule$|Image=HELP]
  	HelpContext(GetController());
  	return(1);
}

func IsBulletTarget()
{
	return(true);
}

func IsThreat()
{
	return(true);
}

func Zated()
{
	SetAction("Dead",this());
	Schedule("ReRise()",300);
   	EMPShockEffect(50);
}

func ReRise()
{
	ObjectSetAction(this(),"FlatUp", 0,0, true); 
}