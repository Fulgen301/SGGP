#strict
local X,TimeAlive,NoMore;
func SetTo(int iX)
{
	X = iX;
	return(1);
}

func IsRepli()
{
	return(true);
}
func Timer()
{
	if(NoMore) return();
	TimeAlive++;
	if(TimeAlive < 100) return(0);
	if(ObjectCount2(Find_ID(REWU),Find_Distance(30)) >= RepliHunger)
	{
		var i;
		while(i < RepliHunger -1)
		{
			RemoveObject(FindObject2(Find_ID(REWU),Find_Distance(70)),Find_Exclude(this()));
			i++;
		}
		if(ObjectCount(REPL) <= RepliLimit || !RepliLimit) CreateObject(REPL);
		RemoveObject();
	}
	
	if(Distance(GetX(),0,X,0) < 5)
	{
		X = 0;
		return(1);
	}
	if(GetX() < X && X) SetXDir(12);
	if(GetX() > X && X) SetXDir(-12);
	SetYDir(-5);
}

func ARW()
{
}

func KilledByARW()
{
	NoMore=1;
	FadeOut(this(),300);
}

func IsMachine() 
{ 
	return(true); 
}
local Name = "$Name$";
