#strict
#include CLNK

local life;

func Initialize()
{
	SetAction("Walk");
  	life = 128;
  	return(1);
}

func ControlDigDouble()
{
	var User;
	CreateMenu(0,this(),this()); 
	var i; 
	var id; 
	if(FindObject(ONSG))
	{
  		while (id = GetDefinition(i++))
  		{
  			if(id != FCLK) if(id !=  GetID(this())) 
  			if(GetValue(0,id) > 0) 
  			if(GetWealth(GetOwner()) >= GetValue(0,id) - GetValue()) 
  			if(GetDefCoreVal("CrewMember", "DefCore", id)) 
  			AddMenuItem("%s",Format("ChangeTo(%i,%d)",id,GetValue(0,id) - GetValue()),id,this(),GetValue(0,id) - GetValue());	
  		}
	}
	else
	{
  		if(GetWealth(GetOwner()) >= GetValue(0,SGK_) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",SGK_,GetValue(0,SGK_) - GetValue()),SGK_,this(),GetValue(0,SGK_) - GetValue());
  		if(GetWealth(GetOwner()) >= GetValue(0,CLNK) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",CLNK,GetValue(0,CLNK) - GetValue()),CLNK,this(),GetValue(0,CLNK) - GetValue());
  		if(GetWealth(GetOwner()) >= GetValue(0,JAFA) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",JAFA,GetValue(0,JAFA) - GetValue()),JAFA,this(),GetValue(0,JAFA) - GetValue());
  		if(GetWealth(GetOwner()) >= GetValue(0,KULL) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",KULL,GetValue(0,KULL) - GetValue()),KULL,this(),GetValue(0,KULL) - GetValue());
  		if(GetWealth(GetOwner()) >= GetValue(0,WRAT) - GetValue()) AddMenuItem("%s",Format("ChangeTo(%i,%d)",WRAT,GetValue(0,WRAT) - GetValue()),WRAT,this(),GetValue(0,WRAT) - GetValue());
	}
	return(true);
}

func ChangeTo(id IdTyp,int iValue)
{
	DoWealth(GetOwner(),-iValue);
	var Clk;
	Clk = CreateObject(IdTyp,0,10,GetOwner());
	Clk->CastParticles("FSpark", 10,100, 0,0, 100, 200, RGBa(255,0,0,0),RGBa(255,128,0,128));
	MakeCrewMember(Clk,GetOwner());
	SetCursor(GetOwner(),Clk);
	RemoveObject();
}

func Checks()
{
	life --;
	Message("Wähle per <c 000000>Doppelgraben</c> einen Clonktyp!|<c %x>%d</c>",this(),RGB(255-life*2,life*2,0),life);
	if(life == 0)
	{
		ChangeTo(CLNK,0);
	}
	return(1);
}

func MaxContentsCount() { return(0); }