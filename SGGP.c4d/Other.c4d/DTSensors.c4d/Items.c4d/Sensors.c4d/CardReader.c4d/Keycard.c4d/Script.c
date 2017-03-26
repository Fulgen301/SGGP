#strict 2

local readers;
local color;

func Initialize()
{
	readers = [];
	ResetColor();
}

func ResetColor()
{
	SetColor(RGB(255, 255, 255));
}

func OnOwnerChanged()
{
	SetColorDw(color);
}

func HasReader(object reader)
{
	return GetIndexOf(reader, readers) != -1;
}

func CleanRemovedReaders()
{
	ArrayEraseItem(readers, 0, true);
}

func AddReader(object reader)
{
	if(!HasReader(reader))
	{
		readers[GetLength(readers)] = reader;
		CleanRemovedReaders();
		if(GetLength(readers) == 1)
		{
			SetColor(reader->GetColor());
		}
	}
	return true;
}

func RemoveReader(object reader)
{
	ArrayEraseItem(readers, reader);
	CleanRemovedReaders();
	if(color == reader->GetColor())
	{
		if(GetLength(readers) > 0)
		{
			SetColor(readers[0]->GetColor());
		}
		else
		{
			ResetColor();
		}
	}
	return true;
}

func SetColor(int newColor)
{
	color = newColor;
	SetColorDw(newColor);
}

func Selection()
{
	if(GetLength(readers))
	{
		var first = true, descList = "";
		for(var reader in readers)
		{
			if(reader)
			{
				Contained()->CreateSelectMark()->MarkObject(reader, 35);
				var desc = reader->GetDescription() || "";
				if(!first)
				{
					descList = Format("%s, ", descList);
				}
				descList = Format("%s<c %x>·</c> %s", descList, reader->GetColor(), desc);
				first = false;
			}
		}
		if(descList != "")
		{
			PlayerMessage(GetOwner(Contained()), "%s: %s", Contained(), SN7I->TargetText(), descList);
		}
	}
}

func Entrance(object container)
{
	if(GetOCF(container) & OCF_CrewMember)
	{
		Selection();
	}
}

func GetColor()
{
	return color;
}

func IsAnvilProduct() { return true; }
