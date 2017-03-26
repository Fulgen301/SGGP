#strict 2
#include LS7I

local detectIDs, exceptIDs, denyIDs, detectCats, denyCats, hostility;

func Init()
{
	detectCats = C4D_Living | C4D_Object | C4D_Vehicle;
	denyCats = 0;
	detectIDs = [C4FO_Or];
	exceptIDs = [C4FO_Or];
	denyIDs = [C4FO_Or];
	return _inherited(...);
}

func ControlUp(object caller)
{
	if(!Attached() && caller)
	{
		caller->Collect(this);
	}
}

func Attach(object caller, object contained)
{
	if(contained && GetProcedure(contained) == "WALK")
	{
		return SetPosition(GetX(), GetY() + 10);
	}
}

func Triggers() { return [["$ObjectTrigger$"], ["$NoObjectTrigger$"], ["$DeniedObjectTrigger$"]]; }

func Setup(object caller, int &menuIndex)
{
	selectCaller = caller;
	AddMenuItem("$SetupDetection$", "SetupDetection", RSR1, caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
	++menuIndex;
	return true;
}

func SetupDetection(id id, object caller, int selection)
{
	if(CreateMenu(RSR1, caller, this, C4MN_Extra_None, "$SetupDetection$", 0, C4MN_Style_Context, 0))
	{
		var menuIndex = 0;
		AddMenuItem("$AddType$", "AddType", GetID(), caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
		++menuIndex;
		AddMenuItem(Format("$TargetOwner$", ["$All$", "$Allied$", "$Hostile$", 0, "$DenyHostile$", "$DenyAllied$"][hostility]), "ChangeHostility", GetID(), caller, 0, caller, 0, C4MN_Add_ForceNoDesc);
		++menuIndex;
		
		for(var part in [["$DetectDef$", detectCats], ["$DetectDenial$", denyCats]])
		{
			for(var cat in [[C4D_Vehicle, "$Vehicle$", LORY], [C4D_Living, "$Living$", WIPF], [C4D_Object, "$Object$", ROCK]])
			{
				if(part[1] & cat[0])
				{
					AddMenuItem(Format(part[0], cat[1]), "RemoveCat", cat[2], caller, 0, cat[0], 0, C4MN_Add_ForceNoDesc);
					++menuIndex;
				}
			}
		}
		
		for(var part in [["$DetectDef$", detectIDs], ["$DetectException$", exceptIDs], ["$DetectDenial$", denyIDs]])
		{
			for(var i = 1; i < GetLength(part[1]); ++i)
			{
				AddMenuItem(Format(part[0], GetName(0, part[1][i][1])), "RemoveDef", part[1][i][1], caller, 0, ++menuIndex, 0, C4MN_Add_ForceNoDesc);
			}
		}
		SelectMenuItem(selection - 1, caller);
		SelectMenuItem(selection, caller);
	}
}

func RemoveCat(id id, int cat, bool right)
{
	var denial = detectCats & cat;
	detectCats &= ~cat;
	denyCats &= ~cat;
	if(right)
	{
		if(denial)
		{
			denyCats |= cat;
		}
		else
		{
			detectCats |= cat;
		}
	}
	SetupDetection(0, selectCaller, 3);
}

func RemoveDef(id id, int indexPO, bool right)
{
	var part = [C4FO_ID, id], exception, denial;
	if(right)
	{
		exception = GetIndexOf2(part, detectIDs) == -1;
		denial = GetIndexOf2(part, denyIDs) == -1;
	}
	ArrayEraseItem(detectIDs, part);
	ArrayEraseItem(exceptIDs, part);
	ArrayEraseItem(denyIDs, part);
	if(right)
	{
		if(exception)
		{
			if(denial)
			{
				denyIDs[GetLength(denyIDs)] = part;
			}
			else
			{
				detectIDs[GetLength(detectIDs)] = part;
			}
		}
		else
		{
			exceptIDs[GetLength(exceptIDs)] = part;
		}
	}
	SetupDetection(0, selectCaller, indexPO - 1);
}

func AddType(id id, object caller, int selection)
{
	var menuIndex = 0;
	if(CreateMenu(RSR1, caller, this, C4MN_Extra_None, "$AddType$", 0, C4MN_Style_Context, 0))
	{
		for(var cat in [[C4D_Vehicle, "$Vehicle$", LORY], [C4D_Living, "$Living$", WIPF], [C4D_Object, "$Object$", ROCK]])
		{
			if(!(detectCats & cat[0]))
			{
				AddMenuItem(cat[1], "AddCat", cat[2], caller, 0, cat[0], 0, C4MN_Add_ForceNoDesc);
				++menuIndex;
			}
		}
		var defs = [];
		for(var obj in FindObjects(Find_Exclude(this), (caller || this)->Find_AtPoint(), IgnoreSensorIgnored(), Find_Category(C4D_Living | C4D_Object | C4D_Vehicle)))
		{
			var def = GetID(obj);
			if(GetIndexOf(def, defs) == -1 && GetIndexOf2([C4FO_ID, def], detectIDs) == -1 && GetIndexOf2([C4FO_ID, def], exceptIDs) == -1)
			{
				defs[GetLength(defs)] = def;
			}
		}
		
		for(def in defs)
		{
			AddMenuItem(GetName(0, def), "AddDef", def, caller, 0, ++menuIndex, 0, C4MN_Add_ForceNoDesc);
		}
		
		SelectMenuItem(selection - 1, caller);
		SelectMenuItem(selection, caller);
	}
}

func AddCat(id id, int cat, bool right)
{
	if(right)
	{
		denyCats |= cat;
	}
	else
	{
		detectCats |= cat;
	}
	AddType(0, selectCaller, 1);
}

func AddDef(id id, int indexPO, bool right)
{
	if(right)
	{
		exceptIDs[GetLength(exceptIDs)] = [C4FO_ID, id];
	}
	else
	{
		detectIDs[GetLength(detectIDs)] = [C4FO_ID, id];
	}
	AddType(0, selectCaller, indexPO - 1);
}

func ChangeHostility(id id, object caller, bool right)
{
	if(right)
	{
		if(hostility)
		{
			if(hostility > 2)
			{
				hostility -= 3;
			}
			else
			{
				hostility += 3;
			}
		}
		else
		{
			hostility = 4;
		}
	}
	else
	{
		var denyOther = (hostility > 2) * 4;
		++hostility;
		if((!denyOther && hostility > 2) || (denyOther && hostility > 5))
		{
			hostility = denyOther;
		}
	}

	SetupDetection(0, caller, 1);
}

func Check(bool retrigger)
{
	var posCond;
	if(Attached() && !GBackSemiSolid(0, 2))
	{
		SetCategory(C4D_Structure);
		SetAction("Wall");
		SetSolidMask();
		posCond = Find_AtRect(-3, 0, 8, 8);
	}
	else
	{
		SetCategory(C4D_Object);
		SetAction("Idle");
		posCond = Find_AtPoint(0, -3);
		if(!Contained() && GetSpeed() < 5)
		{
			SetSolidMask(0, 0, 10, 1);
		}
		else
		{
			SetSolidMask();
		}
	}
	var obj;
	var additionalConds = [C4FO_And];
	var hostilityCond = [0, Find_Not(Find_Hostile(GetOwner(this))), Find_Hostile(GetOwner(this))][hostility % 3];
	var hostilityDenyCond = [0, Find_Hostile(GetOwner(this)), Find_Not(Find_Hostile(GetOwner(this)))][hostility - 3];
	if(GetLength(exceptIDs) > 1)
	{
		additionalConds[GetLength(additionalConds)] = Find_Not(exceptIDs);
	}
	if(hostilityCond)
	{
		additionalConds[GetLength(additionalConds)] = hostilityCond;
	}
	var additionalDenyConds = [C4FO_Or];
	if(denyIDs)
	{
		additionalDenyConds[GetLength(additionalDenyConds)] = denyIDs;
	}
	if(denyCats)
	{
		additionalDenyConds[GetLength(additionalDenyConds)] = Find_Category(denyCats);
	}
	if(hostilityDenyCond)
	{
		additionalDenyConds[GetLength(additionalDenyConds)] = Find_And(Find_Or(detectIDs, detectCats && Find_Category(detectCats)), hostilityDenyCond);
	}
	ClearParticles("PSpark", this);
	if(GetLength(additionalDenyConds) > 1 && (obj = FindObject2(Find_Exclude(this), posCond, Find_NoContainer(), Find_Category(C4D_Living | C4D_Object | C4D_Vehicle), IgnoreSensorIgnored(), additionalDenyConds)))
	{
		CreateParticle("PSpark", 0, 0, 0, 0, 50, RGB(192, 0, 0), this);
		if(triggered != 2 || retrigger)
		{
			triggered = 2;
			return Trigger(2, obj);
		}
	}
	else if(obj = FindObject2(Find_Exclude(this), posCond, Find_NoContainer(), IgnoreSensorIgnored(), Find_Or(detectIDs, detectCats && Find_Category(detectCats)), additionalConds))
	{
		CreateParticle("PSpark", 0, 0, 0, 0, 50, RGB(0, 192, 0), this);
		if(!triggered || retrigger)
		{
			triggered = true;
			return Trigger(0, obj);
		}
	}
	else if(triggered || retrigger)
	{
		triggered = false;
		return Trigger(1);
	}
}
