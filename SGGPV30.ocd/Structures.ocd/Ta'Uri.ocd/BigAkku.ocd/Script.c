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
   Message("<c %x>%d%</c>",this(),RGB(2000-EnergieStand / 200,EnergieStand / 200,0),(EnergieStand / 800)*2);
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
local Touchable = 1;
local ActMap = {

EnergyStand = {

Prototype = Action,

Name = "EnergyStand",

Length = 50,

Delay = 0,

X = 0,

Y = 0,

Wdt = 150,

Hgt = 80,

NextAction = "Hold",

},  };
local Name = "$Name$";
