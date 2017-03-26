/*-- StructMenu --*/

#strict 2

static const C4SM_TextEntry = 0;
static const C4SM_MenuEntry = 1;

global func CreateStructMenu(id idSymbol, string szTitle, object pCommandObject, array aEntries)
{
	CreateMenu(idSymbol, this, pCommandObject, C4MN_Extra_None, szTitle, 0, C4MN_Style_Dialog);
	this->AddStructMenuItems(aEntries);
	return true;
}

global func AddStructMenuItem(array item)
{
	return AddStructMenuItems([item]);
}

global func AddStructMenuItems(array aEntries)
{
	for(var entry in aEntries)
	{
		if(GetType(entry) == C4V_Array && entry[4])
		{
			if(entry[0] == C4SM_TextEntry || entry[0] == C4SM_MenuEntry)
			{
				if(entry[0] == C4SM_MenuEntry && GetType(entry[6]) == C4V_Array)
				{
					entry[5] = Format("%s(", entry[5]);
					for(var i in entry[6])
					{
						entry[5] = Format(Format("%%s%s,", GetFormatString(i)), entry[5], i);
					}
					entry[5] = Format("%s)", entry[5]);
				}
				AddMenuItem(entry[2], entry[5], entry[1], this, 0, 0, entry[3]);
			}
		}
	}
	return true;
}

global func StructMenu_BlankLine()
{
	return [C4SM_MenuEntry, NONE, " ", " ", " "];
}

global func StructMenu_ConditionalTextEntry(id symbol, string data, string caption, bool condition)
{
	return [C4SM_TextEntry, symbol, data, caption, condition];
}

global func StructMenu_TextEntry(id symbol, string data, string caption)
{
	return [C4SM_TextEntry, symbol, data, caption, true];
}

global func StructMenu_ConditionalMenuEntry(id symbol, string data, string caption, bool condition, string szCommand, array aParameters)
{
	return [C4SM_MenuEntry, symbol, data, caption, condition, szCommand, aParameters];
}

global func StructMenu_MenuEntry(id symbol, string data, string caption, string szCommand, array aParameters)
{
	return [C4SM_MenuEntry, symbol, data, caption, true, szCommand, aParameters];
}

global func GetFormatString(v)
{
	if(GetType(v) == C4V_String) return "%s";
	if(GetType(v) == C4V_Int)	 return "%d";
	if(GetType(v) == C4V_C4ID)   return "%i";
	return "%v";
}