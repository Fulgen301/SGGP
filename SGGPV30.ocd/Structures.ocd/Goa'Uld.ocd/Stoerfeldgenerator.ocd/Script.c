
#include BAS3

local Damg,Dis,Aktiv,Enr,Config;
func Initialize()
{
	Dis = 100;
	Enr=100;
}

func Damage()
{
  if(GetDamage() >= 100)
  {
   Explode(50);
  }
  return(1);
}

func Timer()
{
	var pCursor;
	if(Aktiv)
	{
		if(Enr <= 0)
		{
			if(EnergyCheck(Dis / 10 ))
			{
				Enr = 600;
				DoEnergy(-Dis / 10);
			}
		}
		else
		{
			Enr-= Dis /10;
			for(pCursor in FindObjects(Find_Distance(Dis),Find_ID(CURS)))
			{
				if(GetX(pCursor) < GetX())
				{
					pCursor -> ControlLeftDouble();
				}
				else
				{
					pCursor -> ControlRightDouble();
				}
			}
			for(pCursor in FindObjects(Find_Distance(Dis-20),Find_ID(CURS)))
			{
				pCursor -> RemoveObject();
			}
		}
	}
}

func ControlLeft()
{
	if(Dis > 50)Dis-=10;
	var i;
	while(i <= 360) 
	{
   		i+=4;
   		CreateParticle("PSpark",Sin(i,Dis),Cos(i,Dis),0,0, 20,RGB(255,0,0));
  	}
	Message("Radius: <c ffcc00>%d</c>",this(),Dis);
}

func ControlRight()
{
	if(Dis < 500) Dis+=10;
	var i;
	while(i <= 360) 
	{
   		i+=4;
   		CreateParticle("PSpark",Sin(i,Dis),Cos(i,Dis),0,0, 20,RGB(255,0,0));
  	}
	Message("Radius: <c ffcc00>%d</c>",this(),Dis);
}

func ControlDigDouble()
{
	if(Aktiv)
	{
		Aktiv = 0;
		var i;
		while(i <= 360) 
		{
	   		i+=4;
	   		CreateParticle("PSpark",Sin(i,Dis),Cos(i,Dis),0,0, 20,RGB(255,0,0));
	  	}
		SetAction("Stand");
	}
	else
	{
		Aktiv = 1;
		var i;
		while(i <= 360) 
		{
	   		i+=4;
	   		CreateParticle("PSpark",Sin(i,Dis),Cos(i,Dis),0,0, 20,RGB(255,0,0));
	  	}
		SetAction("Activ");
	}
}

func IsAntiker()
{
	return(1);
}
local Touchable = 2;
local ActMap = {
Stand = {
Prototype = Action,
Name = "Stand",
NextAction = "Hold",
Delay = 1,
Length = 1,
X = 0,
Y = 0,
Wdt = 30,
Hgt = 20,
},
Activ = {
Prototype = Action,
Name = "Activ",
NextAction = "ActivRev",
Delay = 2,
Length = 5,
X = 0,
Y = 0,
Wdt = 30,
Hgt = 20,
PhaseCall = "Timer",
},
ActivRev = {
Prototype = Action,
Name = "ActivRev",
NextAction = "Activ",
Reverse = 1,
Delay = 2,
Length = 5,
X = 0,
Y = 0,
Wdt = 30,
Hgt = 20,
PhaseCall = "Timer",
},  };
local Name = "$Name$";
