/* Punkteanzeige */
#strict 2
#appendto 1HUD

local aSGGPIcons;

private func InitAmmoBagHUD()
{
	// remove ammobag display
	var def = 0;
	allAmmo = CreateArray();
	ammovalues = CreateArray();
	aSGGPIcons = CreateArray();
	
	var arrI = 0;
	// get all ammo
	for(var i=0; def = GetDefinition(i,C4D_StaticBack); ++i)
	{
		if(DefinitionCall(def,"IsAmmo"))
		{
			allAmmo[arrI] = def;
			ammovalues[arrI] = 0;
			arrI++;
		}
	}
	
	allAmmo[GetLength(allAmmo)] = aSGGPIcons[GetLength(aSGGPIcons)] = MEDI;
	allAmmo[GetLength(allAmmo)] = aSGGPIcons[GetLength(aSGGPIcons)] = SGGP;
	ammoobjs = CreateArray();
	
	// place all ammo objects
	for(var i=0; i < GetLength(allAmmo); ++i)
	{
		// ...now
		ammoobjs[i] = CreateObject(2HUD,0,0,GetOwner());
		ammoobjs[i]->SetPosition(50,160+i*28);
		ammoobjs[i]->SetGraphics(0, 0, allAmmo[i],1,GFXOV_MODE_IngamePicture);
		ammoobjs[i]->SetObjDrawTransform(750,0,0,0,750,0,0,1);
		ammoobjs[i]->SetVisibility(VIS_None);
	}
}

// Munitionsanzeige updaten
private func UpdateAmmoBag(object ammobag, object weapon)
{

	var ammoid = NONE;
	if(weapon)
		if(weapon->~IsWeapon())
			ammoid = weapon->GetFMData(FM_AmmoID);

	var clonk = GetCursor();
		
	for(var i=0; i < GetLength(ammoobjs); ++i)
	{
		var aobj = ammoobjs[i];
		var isSpecial = false;
		
		if(GetIndexOf(allAmmo[i], aSGGPIcons) != -1) isSpecial = true;
		// unsichtbar bei NoAmmo
		if((NoAmmo() || !ammobag) && !isSpecial) {
			aobj->SetVisibility(VIS_None);
			aobj->Message("",aobj);
			continue;
		}
		// ansonsten Munitionsstand anzeigen
		aobj->SetVisibility(VIS_Owner);
			
		var ammo = 0;
		if(ammobag && !isSpecial)
			ammo = ammobag->GetAmmo(allAmmo[i]);
		
		else if(ammobag)
		{
			if(allAmmo[i] == SGGP)
			{
				ammo = BoundBy(GetPlrExtraData(GetOwner(), "SGGP_Points"), 0, 0x7FFFFFFF);
			}
			else if(allAmmo[i] == MEDI)
			{
				ammo = GetEnergy(GetCursor(GetOwner()));
			}
		}
		
		var ammodiff = 0;
		if(clonk == currentClonk)
		{
			ammodiff = ammo - ammovalues[i];
		}
		ammovalues[i] = ammo;
		if(ammodiff)
			AddEffect("AmmoUpdateNotification", aobj, 300, 1, this, 0, ammodiff, 750);
		
		var color = "eeeeee";
		if(!ammo) color = "777777";
		if(allAmmo[i] == ammoid) {
			color = "ffff00";
			if(!ammo) color = "ff0000";
		}
		aobj->CustomMessage(Format("@  <c %s>%d</c>", color, ammo), aobj, GetOwner(), 25, 31);
	}
}