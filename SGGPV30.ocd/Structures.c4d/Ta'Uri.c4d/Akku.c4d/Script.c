#strict
#include BAS2
local EnergieStand,InfoOn;

func Initialize()
{
	SetAction("EnergyStand");
	EnergieStand = 1;
}

func Timer()
{
	if(InfoOn)
	{
		Message("<c %x>%d%</c>",this(),RGB(200-EnergieStand / 20,EnergieStand / 20,0),(EnergieStand / 200)*5);
	}
	var iNeed;
	iNeed = 50-GetEnergy();
	if(EnergieStand - iNeed >= 1)
	{
		EnergieStand -= iNeed;
		DoEnergy(+iNeed);
	}
	if(EnergieStand < 1) EnergieStand = 1;
	if(EnergieStand > 3990) EnergieStand = 3990;
	SetPhase(EnergieStand / 200);
}

func ControlDigDouble()
{
	if(InfoOn)
	{
		Message(" ",this());
		InfoOn = 0;
	}
	else
	{
		InfoOn = 1;
	}
}	