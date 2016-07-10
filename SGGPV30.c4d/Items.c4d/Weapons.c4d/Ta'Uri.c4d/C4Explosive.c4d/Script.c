#strict
local User,Collectible,Attatched,Time,Wand,Activ,x,y;

func Initialize()
{
	Wand = "";
	Collectible = 1;
	SetAction(Format("%sStand",Wand));
}

func IsActiv()
{
	return(Activ);
}

func TimeUp()
{
	Time--;
	if(Time < 0) Bumm(10);
}

func Activat()
{
	Sound("DetonatorCharge");
	Activ = 1;
	SetOwner(GetOwner(User));
}

func Deactivate()
{
	Sound("DetonatorCharge");
	if(GetOwner(User) == GetOwner())
	{	
		Activ = 0;
	}
	else
	{
		if(Mies()) Activ = 0;
	}
}

func Activate(object pCaller)
{
	SetPlrViewRange(10,this());
	User = pCaller;
	CreateMenu(C4EP, User, 0, 0, "C4", 0, 1);
		AddMenuItem("Verankerung", "Attatch",  C4EP,User);
		if(!Activ) AddMenuItem("Aktivieren", "Activat",  C4EP,User);
		if(Activ) AddMenuItem("Deaktivieren", "Deactivate",  C4EP,User);
		if(Time > 0) AddMenuItem("Entschärfen", "Disable",  C4EP,User);
}

func ControlDigDouble(object pCaller)
{
	Activate(pCaller);
}

func Attatch()
{
	Sound("C4Attach1");
	if(Attatched)
	{
		Wand = "";
		Attatched = 0;
 	   	Collectible = 1;
 	   	SetAction(Format("%sStand",Wand));
		if(Time > 0) SetAction(Format("%sTime1",Wand));
 	   	return();

	}
	else
	{		
    	if(Contained()) Exit(0,0,15);
    	Collectible = 0;
		Wand = "Wand";
		Attatched = 1;
		SetAction(Format("%sStand",Wand));
		if(Time > 0) SetAction(Format("%sTime1",Wand));
		x=GetX();
		y=GetY();
	}
}

func TimeBlast(int iTime)
{
	Time = iTime;
	SetAction(Format("%sTime1",Wand));
}

func Timer()
{
	/*if(!Collectible) Exit();
	if(Contained()) return();
	if(!Collectible) return();
	var pEnter;
	pEnter =  FindObject2(Find_Distance(10),Find_Func("IsClonk"));
	if(!pEnter) return();
	var i;
	while(Contents(i,pEnter))
	{
		if(Contents(i,pEnter)) i++;
	}
	var Collects;
	Collects = pEnter -> ObjectCollectionLimit();
	if(!Collects) Collects = pEnter -> MaxContentsCount();
	if(!Collects) Collects = GetDefCoreVal("CollectionLimit",0,GetID(pEnter));
	if(i < Collects) Enter(pEnter);*/
}

func Mies()
{
	if(RandomX(0,100) < 90)
	{
		Bumm(RandomX(30,60));
		return(0);
	}
	return(1);
}

func Disable()
{
	if(GetOwner(User) == GetOwner())
	{
		Sound("DetonatorCharge");
		SetAction(Format("%sStand",Wand));
		Time = 0;
	}
	else
	{
		if(Mies()) Time = 0;
		SetAction(Format("%sStand",Wand));
	}
}

func Bumm(int iStark)
{
	var C4s;
	C4s = ObjectCount2(Find_ID(C4EP),Find_Distance(iStark));
	var C4;
	for(C4 in FindObjects(Find_ID(C4EP),Find_Distance(iStark))) RemoveObject(C4);
	C4s = C4s *15;
	Explode(iStark + C4s);
	Explode(iStark / 2 + C4s);
}

func Entrance()
{
	if(Collectible) return();
	Exit(this());
	SetPosition(x,y);
	return(1);
}