/*--- Dart ---*/

#strict 2
#include WEPN
#include VHCL

public func Initialize()
{
	_inherited(...);
	SetAction("Landed");
}

public func GetRace() { return SG1_Goauld; }

public func IsBulletTarget()
{
	return true;
}

public func Timer()
{
	return _inherited(...);
}

public func MotorAus()
{
	//Sound("Stop");
	SetAction("Off");
}

public func MotorAn()
{
	//Sound("Start");
	SetAction("On");
}

public func ContainedUp()//Hocfliegen
{
	[Hoch|Image=GLEI]
	if(GetAction() == "Landed")
		return MotorAn();
	if (GetAction() != "Fly")
		return 1;
  if(GetComDir() == COMD_UpLeft || GetComDir() == COMD_UpRight) SetComDir(COMD_Up);
  if(GetComDir() == COMD_Down) SetComDir(COMD_Up);
  if(GetComDir() == COMD_Left) SetComDir(COMD_UpLeft);
  if(GetComDir() == COMD_DownLeft) SetComDir(COMD_Left);
  if(GetComDir() == COMD_DownRight) SetComDir(COMD_Right);
  if(GetComDir() == COMD_Right) SetComDir(COMD_UpRight);
  if(GetComDir() == COMD_Stop) SetComDir(COMD_Up);return 1;
}

public func ContainedUpDouble()
{
	SetComDir(COMD_Stop);
	SetXDir();
	SetYDir();
	return 1;
}

public func ContainedDown()//runter, das gleiche wie hoch nur andersrum
{
	[Runter|Image=GLEI]
	if (GetAction() == "Landed")
		return 0;
	if (GetAction() != "Fly")
		return 1;
	if(GetComDir() == COMD_DownLeft ||GetComDir() == COMD_DownRight)
    {
    SetComDir(COMD_Down);
    }
   if(GetComDir() == COMD_Up)
    {
    SetComDir(COMD_Stop);
    }
   if(GetComDir() == COMD_Left)
    {
    SetComDir(COMD_DownLeft);
    }
   if(GetComDir() == COMD_UpLeft)
    {
    SetComDir(COMD_Left);
    }
   if(GetComDir() == COMD_Stop)
    {
    SetComDir(COMD_Down);
    }
   if(GetComDir() == COMD_Right)
    {
    SetComDir(COMD_DownRight);
    }
   if(GetComDir() == COMD_UpRight)
    {
    SetComDir(COMD_Right);
//    }
   }
   return 1;
}

public func ContainedLeft()
{
	[Links|Image=GLEI]
	if(GetAction() == "Landed")
		return 0;
	else if(GetAction() != "Fly")
		return 1;
	SetComDir(COMD_Left);
	SetDir(DIR_Left);
	return 1;
}

public func ContainedRight()
{
	[Rechts|Image=GLEI]
	if(GetAction() == "Landed")
		return 0;
	else if(GetAction() != "Fly")
		return 1;
	
	SetComDir(COMD_Right);
	SetDir(DIR_Right);
	return 1;
}

public func Turned2()
{
	
}

public func Turned1()
{
	
}

public func ContainedThrow(object pClonk)
{
	if(GetAction() == "Fly") return ControlThrow(pClonk);
}

public func IsMachine() { return true; }
public func ReadyToFire()	{ return GetAction() == "Fly"; }

public func UpdateCharge(object driver) {
	
	var hud = driver->GetHUD();
	if(hud) hud->Update(this(), driver->AmmoStoring(),driver);
	return true;
}

public func MakeMenu(object pCaller)
{
	_inherited(pCaller, ...);
	AddMenuItem("Feuermodus wechseln", "ChangeFire", MEPU, pCaller);
}

public func ChangeFire()
{
	if(pPilot) ControlDigDouble(pPilot);
}

public func FMData1(int data)
{
	if (data == FM_Name)
		return "Explosion";
	if (data == FM_AmmoID)
		return ENAM;
	if (data == FM_AmmoLoad)
		return 160;
	if (data == FM_Reload)
		return 80;
	if (data == FM_Recharge)
		return 80;
	if (data == FM_AmmoUsage)
		return 160;
	if (data == FM_AmmoRate)
		return 1;
	if (data == FM_Auto)
		return true;
	if (data == FM_Damage)
		return 40;
	return Default(data);
}

public func Fire1()
{
	Fling(CreateObject(ALBU, 0, 90), 0, 4);
}

public func FMData2(int data)
{
	if (data == FM_Name)
		return "Bio";
	if (data == FM_AmmoID)
		return GSAM;
	if (data == FM_AmmoLoad)
		return 40;
	if (data == FM_Reload)
		return 120;
	if (data == FM_Recharge)
		return 40;
	if (data == FM_AmmoUsage)
		return 40;
	if (data == FM_AmmoRate)
		return 1;
	if (data == FM_Auto)
		return true;
	if (data == FM_Damage)
		return 40;
	return Default(data);
}

public func Fire2()
{
	Fling(CreateObject(ALBI, 0, 90), 0, 4);
}

public func FMData3(int data)
{
	if (data == FM_Name)
		return "Betäubung";
	if (data == FM_AmmoID)
		return ENAM;
	if (data == FM_AmmoLoad)
		return 80;
	if (data == FM_Reload)
		return 80;
	if (data == FM_Recharge)
		return 80;
	if (data == FM_AmmoUsage)
		return 80;
	if (data == FM_AmmoRate)
		return 1;
	if (data == FM_Auto)
		return true;
	if (data == FM_Damage)
		return 40;
	return Default(data);
}

public func Fire3()
{
	Fling(CreateObject(ALBE, 0, 90), 0, 4);
}

global func DoR(int iR, object pObj)
{
	if(!pObj && !(pObj = this)) return;
	return pObj->SetR(pObj->GetR() + iR);
}