#strict

//#include BA15

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
   Message("<c %x>%d%</c>",this(),RGB(2000-EnergieStand / 200,EnergieStand / 200,0),EnergieStand / 400);
  }
  var iNeed;
  iNeed = 50-GetEnergy();
  if(EnergieStand - iNeed >= 1)
  {
   EnergieStand -= iNeed;
   DoEnergy(+iNeed);
  }
  if(EnergieStand < 1) EnergieStand = 1;
  if(EnergieStand > 40100) EnergieStand = 40100;
  SetPhase((EnergieStand / 800));
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

public func GetRace() { return SG1_StargateCenter; }