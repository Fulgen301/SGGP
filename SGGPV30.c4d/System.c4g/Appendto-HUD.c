/*-- HUD spart sich die Beschreibung --*/

#strict 2
#appendto 1HUD

private func UpdateWeapon(object weapon)
{
	if(!weapon || !weapon->~IsWeapon())
	{
		SetVisibility(VIS_None);
		info->SetVisibility(VIS_None);
		Message("",this);
		Message("",info);
		charge = 0;
		recharge = 0;
		SetCurrentWeapon(0);
		
		// garkein Inventar
		if(!weapon)
		{
			itemInfoHUD->SetVisibility(VIS_None);
			Message("",itemInfoHUD);
		}
		// Inventar, aber keine Waffe
		/*else
		{
			itemInfoHUD->SetVisibility(VIS_Owner);
			CustomMessage(Format("@<c ffff00>%s</c>|%s",GetName(weapon),GetDesc(weapon)), itemInfoHUD, GetOwner());
		}//*/
	}
	// Waffe...
	else
	{
		if(weapon->IsRecharging())
			recharge = weapon->GetRecharge();
		else
			recharge = 0;
		
		charge = weapon->GetCharge();
		SetVisibility(VIS_Owner);
		info->SetVisibility(VIS_Owner);
		itemInfoHUD->SetVisibility(VIS_None);
		Message("",itemInfoHUD);
		
		var ammoid = weapon->GetFMData(FM_AmmoID);
		var ammoload = weapon->GetFMData(FM_AmmoLoad);
		var modusname = weapon->GetFMData(FM_Name);
		var ammocount = weapon->GetAmmo(ammoid);
		
		var ammodiff = 0;
		if(currentWeapon == weapon && currentAmmoId == ammoid)
		{
			ammodiff = ammocount - currentAmmoCount;
		}

		SetCurrentWeapon(weapon);

		currentAmmoCount = ammocount;		
		if(ammodiff)
			AddEffect("AmmoUpdateNotification", info, 300, 1, this, 0, ammodiff, 750);
		
		var color = "ffff00";
		if(!ammocount) color = "ff0000";
		CustomMessage(Format("@%s", modusname), this, GetOwner(), 0, 10);
		CustomMessage(Format("@<c %s>%d/%d</c>", color, ammocount, ammoload), info, GetOwner(), 118 + GetNumberCount(ammoload)*6, 31);
		
		if(!SetGraphics(Format("Row%i",ammoid), 0, GetID(), HUD_Layer_AmmoBase, GFXOV_MODE_Base))
		{
			SetGraphics("Row", 0, GetID(), HUD_Layer_AmmoBase, GFXOV_MODE_Base);
		}
		info->SetGraphics(0, 0, ammoid,1,GFXOV_MODE_IngamePicture);
	}
	
	UpdateCharge();
	UpdateRecharge();
}
