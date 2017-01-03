#strict 2
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
	CreateMenu(GetID(this), pUser, 0,0, "Asgard Materie Konverter", 0, 1);
	if(!pId) if(HasEnrg >= 100) AddMenuItem("Objekt erzeugen", Format("Create(%d)",pUser),MEPU,pUser);
	if(pId) AddMenuItem("Antigravitationsfeld abschalten", "Off",MEPU,pUser);
	AddMenuItem("Info An/Aus", "Info",MEPU,pUser);
}

func Create()
{
	CallMessageBoard(0,false,"Welches Objekt möchten sie erschaffen:",GetOwner(User));
}

func InputCallback(string szString)
{
	if(HasEnrg < 100) return;
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
			Wait = 20;
			return;
		}
	}
	else
	{
		if(GetCategory(0, id) & category && !id->~IsNotConvertable())
		{
			Off();
			idDef = id;
			HasEnrg = 0;
			SetAction("Start");
			return;
		}
	}
	Message("<c ff0000>Objekt nicht in Datenbank!</c>",this);
	Wait = 20;
}

func Off()
{
	if(pId)
	{
		RemoveEffect("HoldObject", pId);
	}
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
	AddEffect("HoldObject", pId, 1, 1, this);
}

func Timer()
{
	if(Wait > 0) Wait--;
	if(FindObject(ENRG))
	{
		if(HasEnrg < 100) if(EnergyCheck(1000))
		{
			++HasEnrg;
		}
	}
	else
	{
		if(HasEnrg < 100)
		{
			HasEnrg += 1;
		}
	}
	if(!Wait && InfoOn)
	{
		Message("<c %x> %d%</c>",this,RGB(200 - HasEnrg * 2,HasEnrg*2),HasEnrg);
	}
}

func FxHoldObjectStart(object pTarget, int iEffectNumber, int iTemp)
{
	if(!iTemp)
	{
		SetAction("Wait");
	}
}

func FxHoldObjectTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
	if(Contained(pTarget))
	{
		return FX_Execute_Kill;
	}

	SetYDir(-2,pId);
	SetXDir(0,pId);
	SetPosition(X,Y,pId);
}

func FxHoldObjectStop(object pTarget, int iEffectNumber, int iReason, bool fTemp)
{
	if(!fTemp)
	{
		pId = 0;
		SetAction("Stand");
	}
}

func Info()
{
	if(InfoOn)
	{
		InfoOn = 0;
		Message(" ",this);
	}
	else
	{
		InfoOn = 1;
	}
}

public func SensorCallbacks(object pSensor)
{
	return [["Objekt erzeugen", BindCallback("SensorControl", [Bind(pSensor)])]];
}

public func SensorControl(object pSensor)
{
	if(!pSensor) return;
	return InputCallback(LocalN("desc", pSensor));

}
