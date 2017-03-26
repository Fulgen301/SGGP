#strict 2
#include SN7I

local color, controllingCard;

func Init()
{
	SetColor(HSL(Random(255), 255, 127));
	var card = CreateContents(KC7I);
	card->AddReader(this);
	Collection2(card);
}

func SetColor(int newColor)
{
	color = newColor;
	SetColorDw(color);
}

func GetColor() { return color; }

func OnOwnerChanged()
{
	SetColorDw(color);
}

func Triggers() { return [["$RightCard$"], ["$WrongCard$"]];}

func ControlThrow(object caller)
{
	var card, success;
	if(card = FindCard(caller, success))
	{
		if(!controllingCard)
		{
			ShowSuccess(success);
			Trigger(!success, caller);
		}
		else
		{
			PlayerMessage(GetController(caller), "$CardLoaded$", this);
		}
	}
	else if(controllingCard)
	{
		GetCard(0, caller);
	}
	return ClearCom(caller);
}

func ControlThrowDouble() { return ControlThrow(...); }

func ShowSuccess(bool success)
{
	if(!success)
	{
		Sound("Error");
		CreateParticle("PSpark", -5, -1, 0, 0, 50, RGB(192, 0, 0));
	}
	else
	{
		CreateParticle("PSpark", -5, -1, 0, 0, 50, RGB(0, 192, 0));
	}
}

func Setup(object caller, int& menuIndex)
{
	if(controllingCard && Contained(controllingCard) == this)
	{
		AddMenuItem("$GetCard$", "GetCard", KC7I, caller, 0, caller, 0, C4MN_Add_ForceNoDesc | C4MN_Add_ImgObject, controllingCard);
		++menuIndex;
		var success, card = FindCard(caller, success);
		if(card && !card->HasReader(this))
		{
			selectCaller = caller;
			AddMenuItem("$AddReader$", "AddReader", KC7I, caller, 0, card, 0, C4MN_Add_ForceNoDesc | C4MN_Add_ImgObject, card);
			++menuIndex;
		}
		if(ObjectCount2(Find_ID(KC7I), Find_Func("HasReader", this), Find_Exclude(controllingCard)))
		{
			AddMenuItem("$RemoveReader$", "RemoveReader", KC7I, caller, 0, caller, 0, C4MN_Add_ForceNoDesc | C4MN_Add_ImgObject, controllingCard);
			++menuIndex;
		}
	}
	else
	{
		var success;
		FindCard(caller, success);
		if(success)
		{
			AddMenuItem("$LoadCard$", "LoadCard", KC7I, caller, 0, caller, 0, C4MN_Add_ForceNoDesc | C4MN_Add_ImgColor, RGB(255, 255, 255));
			++menuIndex;
		}
	}
	return true;
}

func GetCard(id id, object caller)
{
	if(controllingCard)
	{
		Exit(controllingCard);
		caller->Collect(controllingCard);
	}
}

func LoadCard(id id, object caller)
{
	var success;
	var card = FindCard(caller, success);
	if(success)
	{
		Enter(this, card);
	}
	_Setup(caller);
	SelectMenuItem(2, caller);
}

func AddReader(id id, object card)
{
	card->AddReader(this);
}

func RemoveReader(id id, object caller)
{
	if(controllingCard)
	{
		controllingCard->RemoveReader(this);
		GetCard(id, caller);
	}
}

func FindCard(object container, bool& success)
{
	var card;
	success = false;
	for(var i = 0; i < ContentsCount(0, container); ++i)
	{
		var content = Contents(i, container);
		if(GetID(content) == KC7I)
		{
			if(content->HasReader(this))
			{
				card = content;
				success = true;
				break;
			}
			else if(!card)
			{
				card = content;
			}
		}
	}
	return card;
}

func Collection2(object obj)
{
	if(!controllingCard && obj->GetID() == KC7I && obj->HasReader(this))
	{
		controllingCard = obj;
		SetGraphics("Card", this, GetID(), GFX_Overlay, GFXOV_MODE_Base);
		SetClrModulation(obj->GetColor(), this, GFX_Overlay);
	}
}

func ContentsDestruction(object obj) { return Ejection(obj); }

func Ejection(object obj)
{
	if(obj == controllingCard)
	{
		SetGraphics(0, this, 0, GFX_Overlay);
		controllingCard = 0;
	}
}

func SetupCondition(object caller)
{
	if(controllingCard)
	{
		return true;
	}
	
	var success;
	FindCard(caller, success);
	return success;
}

func CalcDefValue()
{
	return Value(GetID()) + GetValue(0, KC7I);
}
