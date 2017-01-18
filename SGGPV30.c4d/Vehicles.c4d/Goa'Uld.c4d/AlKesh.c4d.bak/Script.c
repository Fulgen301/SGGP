/*--- Dart ---*/

#strict 2
#include WEPN
#include CVHC

public func GetRace() { return SG1_Goauld; }

public func IsBulletTarget()
{
	return true;
}

public func Timer()
{
	_inherited();
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
	if (GetAction() != "Fly")
		return 1;
	SetComDir(COMD_Up); //comdir setzen
	return 1;
}

public func ContainedDown()//runter, das gleiche wie hoch nur andersrum
{
	[Runter|Image=GLEI]
	if (GetAction() == "Landed")
		return 0;
	if (GetAction() != "Fly")
		return 1;
	SetComDir(COMD_Down);
	return 1;
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