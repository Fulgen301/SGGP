#strict 2
#include SGIR

public func DoSound()
{
	Sound("iris_atlantis_loop", 0,0,50,0,1 - (GetAction() == "Opens") * 2);
	if(GetAction() == "Opens")
	{
		Sound("iris_atlantis_open");
		
	}
	else if(GetAction() == "Closes")
	{
		Sound("iris_atlantis_close");
	}
}

public func IsStargateShield()
{
	return true;
}