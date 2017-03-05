#strict 2
#include BAS3

local zpms;
local User;
local info;
local iMode;

protected func Construction()
{
	_inherited(...);
	zpms = CreateArray(3);
	AddTimer("Check", 4);
}

protected func Damage()
{
  if(GetDamage() > 200)
  {
	  var size = 50;
	  for(var zpm in zpms)
	  {
		  if(zpm) size += zpm->Enrg();
	  }
   Explode(size);
  }
}

protected func Destruction()
{
  RemoveObjects(zpms);
  return _inherited();
}

protected func Check()
{
  if(GetCon() != 100) return;

  if(CheckEnergyNeedChain()) GiveEnerg();
  
  for(var i = 0; GetIndexOf(0, zpms) != -1; i = GetIndexOf(0, zpms))
  {
	  zpms[i] = CreateObject(ZPM2, 0, 0, GetOwner());
	  zpms[i]->Set(this, 256*4 + 4 + i);
	  zpms[i]->SetAction("None", this);
  }
}

public func GiveEnerg()
{
	for(var zpm in zpms)
	{
		if(zpm && zpm->GetAction() == "Activen")
		{
			zpm->Minus();
			DoEnergy(10000);
			return;
		}
	}
}

public func Free()
{
	for(var zpm in zpms)
	{
		if(zpm && !zpm->FindContents(ZPM_)) return true;
	}
}

public func HasZPM(bool active)
{
	var i;
	for(var zpm in zpms)
	{
		if(zpm && zpm->GetAction() != "None") i++;
	}
  return i;
}

public func GetActiveZPMCount()
{
	var i;
	for(var zpm in zpms)
	{
		if(zpm && zpm->GetAction() == "Activen") i++;
	}
	
	return i;
}

public func & GetAllZPMs()
{
	return zpms;
}

protected func ControlDigDouble(pCaller)
{
  User = pCaller;
  CreateMenu(GetID(), User, 0,0, GetName(), 0, C4MN_Style_Dialog);
  
  AddMenuItem("Status", 0, NONE, User);
  for(var i = 0; i < GetLength(zpms); i++)
  {
	if(zpms[i])
	{
		var string;
		var act = zpms[i]->GetAction();
		if(act == "Activen") string = "$Activen$";
		else if(act == "Inactive") string = "$Inactive$";
		else if(act == "Depledet") string = "$Depledet";
		else if(act == "None") string = "$None$";
		
	  AddMenuItem(FormatN("$ZPMFormat$", ["i", "a", "e"], [i + 1, string, zpms[i]->Enrg()]), 0, NONE, User);
	}
  }
  
  AddMenuItem(" ", 0, NONE, User);
  
  if(FindContents(ZPM_,User) && Free())
  {
    AddMenuItem("$PutZPM$","PutZPM",MEPU,User);
  }
  
  if(HasZPM())
  {
   AddMenuItem("$GetZPM$","GetZPM",MEPU,User);
  }
  
  for(var i = 0; i < GetLength(zpms); i++)
  {
	  var txt;
	  var active = 0;
	  
	  if(zpms[i])
	  {
		  if(zpms[i]->GetAction() == "Activen")
		  {
			  txt = "$DeactivateZPM$";
			  active = 1;
		  }
		  else if(zpms[i]->GetAction() == "Inactive") txt = "$ActivateZPM$";
		  else continue;
		  
		  AddMenuItem(Format(txt, i + 1), Format("SwitchZPM(%d, %d)", i, active), MEPU, User);
	  }
  }
  return(1);
}

protected func SwitchZPM(int i, int active)
{
	if(!zpms[i]) return;
	if(active) zpms[i]->SetAction("Inactive");
	else zpms[i]->SetAction("Activen");
}

public func GetZPM()
{
  for(var zpm in zpms)
  {
	  if(zpm && zpm->FindContents(ZPM_) && User)
	  {
		  zpm->FindContents(ZPM_)->Enter(User);
		  return true;
	  }
  }
}

public func PutZPM()
{
  for(var zpm in zpms)
  {
	  if(zpm && !zpm->RejectCollect() && User)
	  {
		  User->FindContents(ZPM_)->Enter(zpm);
		  return true;
	  }
  }
}

func IsAntiker()
{
	return(1);
}

public func AtlantisOSFunc()
{
	var i = 0;
	for(var zpm in GetAllZPMs())
	{
		if(zpm && zpm->GetAction() == "Activen")
		{
			i += zpm->Enrg();
		}
	}
	if(i < 10) return ATLANTISOS_ZPMLOW;
	return ATLANTISOS_OK;
}

public func GetRace() { return SG1_Ancient; }