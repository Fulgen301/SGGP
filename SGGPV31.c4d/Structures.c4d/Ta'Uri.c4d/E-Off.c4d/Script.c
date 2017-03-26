#strict
#include BAS9
#include DOOR
local VOn,EOn,pUser,Owner,Counter;
func Initialize()
{
}

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

func ContainedDigDouble(object User)
{
	pUser = User;
	var Enrg,Verk;
	if(VOn) Verk = "An";
	else
	Verk = "Aus";
	if(EOn) Enrg = "An";
	else
	Enrg = "Aus";
	CreateMenu(GetID(this()), pUser, 0,0, "E-Off", 0, 1,1);
	AddMenuItem(Format("Energiezellen: <c ffcc00>%s</c>",Enrg), "EnrgZell",MEPU,pUser);
	AddMenuItem(Format("Verkauf: <c ffcc00>%s</c>",Verk), "Verk",MEPU,pUser);
	AddMenuItem("Besitzer ändern", "Besitz",MEPU,pUser);
}

func Damage()
{
  if(GetDamage() >= 200)
  {
   Explode(50);
  }
  return(1);
}

public func ContextConstruction(pCaller) 
{
  [E-Off|Image=TAEO]
  return(ContainedDigDouble(pCaller));
}

func EnrgZell()
{
	if(EOn)
	{
		EOn = 0;
	}
	else
	{
		EOn = 1;
	}
	ContainedDigDouble(pUser);
}

func Verk()
{
	if(VOn)
	{
		VOn = 0;
	}
	else
	{
		VOn = 1;
	}
	ContainedDigDouble(pUser);
}

func Timer()
{
	if(EnergyCheck(100)) Counter++;
	if(VOn)
	{
		if(Counter >= 10)
		{
			Counter-=10;
			DoWealth(GetOwner(),1);
			CastParticles("PxSpark", 10,40, -50,-10, 100, 30, RGBa(128,128,255,0), RGBa(255,255,255,127));
		}
	}
	if(EOn)
	{
		if(Counter >= 90)
		{
			Counter-=90;
			CreateContents(ENAP);
			CastParticles("PxSpark", 10,40, -50,-10, 100, 30, RGBa(128,128,255,0), RGBa(255,255,255,127));
		}
	}
}

func Besitz()
{
	CreateMenu(GetID(this()), pUser, 0,0, "Besitzer", 0, 1,1);
	var i;
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			AddMenuItem(Format("Ändern zu: <c ffcc00>%s</c>",GetPlayerName(i)), Format("ChangeOwner(%d)",i),MEPU,pUser);
		}
		i++;
	}
}

func ChangeOwner(int iOwner)
{
	SetOwner(iOwner);
	Message("<c ffcc00>Besitzer zu %s geändert</c>",this(),GetPlayerName(iOwner));
	ContainedDigDouble(pUser);
}

public func GetRace() { return SG1_StargateCenter; }
			