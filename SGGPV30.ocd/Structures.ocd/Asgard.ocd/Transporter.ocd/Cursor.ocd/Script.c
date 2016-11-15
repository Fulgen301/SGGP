
local pBeamer,pBef,Frame;
func Initialize()
{
	SetAction("1");
}

func ControlLeft()
{
	SetXDir(-30);
}

func ControlRight()
{
	SetXDir(30);
}

func ControlUp()
{
	SetYDir(-30);
}

func ControlDown()
{
	SetYDir(30);
}

func ControlLeftDouble()
{
	SetXDir(-80);
	SetYDir();
}
func ControlRightDouble()
{
	SetXDir(80);
	SetYDir();
}

func ControlUpDouble()
{
	SetYDir(-80);
	SetXDir();
}

func ControlDownDouble()
{
	SetYDir(80);
	SetXDir();
}

func ControlThrow()
{
	pBeamer -> Okay(GetX(),GetY());
	SetCursor(GetOwner(),pBef);
	RemoveObject();
} 

func ControlDig()
{
	SetXDir();
	SetYDir();
}

func SetBeamer(object pBeam,int iOwner,object pBefo)
{
	SetPlrViewRange(200);
	pBeamer = pBeam;
	pBef = pBefo;
	SetOwner(iOwner);
	SetCursor(iOwner,this());
	SetVisibility(VIS_None | VIS_Owner);
}

func Timer()
{
	if(pBeamer && GetCursor(GetOwner()) != this()) RemoveObject();
	Frame++;
	if(Frame > 10)
	{
		Frame = 0;
		if(GetAction() eq "1")
		{
			SetAction("2");
		}
		else
		{
			SetAction("1");
		}
	}
	/*if(GetR() < 360)
	{
		SetR(GetR() + 1);
	}
	else
	{
		SetR(0);
	}*/
	if(ObjectDistance(pBeamer) > LandscapeWidth() / 2 && !FindObject(ENRG)) 
	{
		if(GetX() > GetX(pBeamer))
		{
			SetXDir(-30);
		}
		else
		{
			SetXDir(30);
		}
		if(GetY() > GetY(pBeamer))
		{
			SetYDir(-30);
		}
		else
		{
			SetYDir(30);
		}
	}
	SetRDir(3);
}	

local ActMap = {
1 = {
Prototype = Action,
Name = "1",
NextAction = "1",
Procedure = DFA_FLOAT,
Delay = 1,
Length = 1,
X = 0,
Y = 0,
Wdt = 25,
Hgt = 25,
PhaseCall = "Timer",
},
2 = {
Prototype = Action,
Name = "2",
NextAction = "2",
Procedure = DFA_FLOAT,
Delay = 1,
Length = 1,
X = 25,
Y = 0,
Wdt = 25,
Hgt = 25,
PhaseCall = "Timer",
},  };
