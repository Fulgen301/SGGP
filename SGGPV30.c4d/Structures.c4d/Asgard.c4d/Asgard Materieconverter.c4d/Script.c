#strict
local pId,idDef,HasEnrg,InfoOn,X,Y,User,Wait;
func Initialize()
{
	SetAction("Stand");
}

func Damage()
{
  if(GetDamage() > 200)
  {
   Explode(35);
  }
  return(1);
}

func ControlDigDouble(object pUser)
{
	User = pUser;
	CreateMenu(GetID(this()), pUser, 0,0, "Asgard Materie Konverter", 0, 1);
	if(!pId) if(HasEnrg >= 100000) AddMenuItem("Objekt erzeugen", Format("Create(%d)",pUser),MEPU,pUser);
	if(pId) AddMenuItem("Antigravitationsfeld abschalten", "Off",MEPU,pUser);
	AddMenuItem("Info An/Aus", "Info",MEPU,pUser);
}

func Create()
{
	CallMessageBoard(0,false,"Welches Objekt möchten sie erschaffen:",GetOwner(User));
}

func InputCallback(string szString)
{
	var category = C4D_Object;
	var id = C4Id(szString);
	if(!id || !FindDefinition(id))
	{
		var ids = GetIDsByName(szString, category);
		if(GetLength(ids) > 0)
		{
			var first = true;
			var text = Format("%s: ", szString);
			for(var id in ids)
			{
				if(!first)
				{
					text = Format("%s, ", text);
				}
				else
				{
					first = false;
				}
				
				text = Format("%s{{%i}} %i", text, id, id);
			}
			Message(text, this);
			Wait = 200;
			return;
		}
	}
	else
	{
		if(GetCategory(0, id) & category)
		{
			idDef = id;
			HasEnrg = 0;
			SetAction("Start");
			return;
		}
	}
	Message("<c ff0000>Objekt nicht in Datenbank!</c>",this);
	Wait = 200;
}

func Off()
{
	SetAction("Stand");
	pId = 0;
	X = 0;
	Y = 0;
}

func IsAsgard()
{
	return true;
}

func SoundAS()
{
	Sound("ASTeleport");
}

func CreateIt()
{
	pId = CreateObject(idDef, 0, 7, GetOwner(User));
	X = GetX(pId);
	Y = GetY(pId);
}

func Timer()
{
	if(Wait > 0) Wait--;
	if(FindObject(ENRG))
	{
		if(HasEnrg < 100000) if(EnergyCheck(100)) 
		{
			HasEnrg += 100;
		}
	}
	else
	{
		if(HasEnrg < 100000)
		{
			HasEnrg += 1;
		}
	}
	if(Contained(pId))
	{
		pId = 0;
		SetAction("Stand");
	}
	if(!pId)
	{
	 if(GetAction() eq "Wait")
	 {
		SetAction("Stand");
	 }
	 
	 if(GetAction() eq "WaitRev")
	 {
		SetAction("Stand");
	 }
	}
	if(pId)
	{ 
		SetYDir(-2,pId);
		SetXDir(0,pId);
		SetPosition(X,Y,pId);
	}
	var EnrgProz;
	EnrgProz = HasEnrg / 1000;
	if(!Wait) if(InfoOn) Message("<c %x> %d%</c>",this(),RGB(200 - EnrgProz * 2,EnrgProz*2),EnrgProz);
}

func Info()
{
	if(InfoOn)
	{
		InfoOn = 0;
		Message(" ",this());
	}
	else
	{
		InfoOn = 1;
	}
}
