#strict
#include BAS3

local zpm1, zpm2, zpm3;
local User;
local info;
local iMode;

func Initialize()
{
  zpm1 = CreateObject(ZPM2);
  zpm2 = CreateObject(ZPM2);
  zpm3 = CreateObject(ZPM2);
  SetObjectOrder(zpm1,this());
  SetObjectOrder(zpm2,this());
  SetObjectOrder(zpm3,this());
  return(1);
}

func Damage()
{
  if(GetDamage() > 200)
  {
   Explode(EnrgA()+EnrgB()+EnrgC()+50);
  }
  return(1);
}

func Destruction()
{
  if(zpm1) zpm1->RemoveObject();
  if(zpm2) zpm2->RemoveObject();
  if(zpm3) zpm3->RemoveObject();
  return(1);
}

func ZpmA()
{
  if(zpm1->GetZpm() == 0)
  {
   return("1.ZPM:<c ff0000> Nicht vorhanden</c>");
  }

  if(GetAction(zpm1) eq "Depledet")
  {
   return("1.ZPM:<c 000000> Erschöpft</c>");
  }
  
  if(GetAction(zpm1) eq "Activen")
  {
   return("1.ZPM:<c 00ff00> Aktiv</c>");
  }
  
  if(GetAction(zpm1) eq "Inactive")
  {
   return("1.ZPM:<c 0000ff> Inaktiv</c>");
  }
  return(1);
}

func ZpmB()
{
  if(zpm2->GetZpm() == 0)
  {
   return("2.ZPM:<c ff0000> Nicht vorhanden</c>");
  }

  if(GetAction(zpm2) eq "Depledet")
  {
   return("2.ZPM:<c 000000> Erschöpft</c>");
  }
  
  if(GetAction(zpm2) eq "Activen")
  {
   return("2.ZPM:<c 00ff00> Aktiv</c>");
  }
  
  if(GetAction(zpm2) eq "Inactive")
  {
   return("2.ZPM:<c 0000ff> Inaktiv</c>");
  }
  return(1);
}

func ZpmC()
{
  if(zpm3->GetZpm() == 0)
  {
   return("3.ZPM:<c ff0000> Nicht vorhanden</c>");
  }

  if(GetAction(zpm3) eq "Depledet")
  {
   return("3.ZPM:<c 000000> Erschöpft</c>");
  }
  
  if(GetAction(zpm3) eq "Activen")
  {
   return("3.ZPM:<c 00ff00> Aktiv</c>");
  }
  
  if(GetAction(zpm3) eq "Inactive")
  {
   return("3.ZPM:<c 0000ff> Inaktiv</c>");
  }
  return(1);
}

func EnrgA()
{
  return(zpm1->Enrg());
}

func EnrgB()
{
  return(zpm2->Enrg());
}

func EnrgC()
{
  return(zpm3->Enrg());
}

func Check()
{
  if(GetCon() != 100)
  {
   return(1);
  }

  if(CheckEnergyNeedChain())
  {
   GiveEnerg();
  }
  if(zpm1)
  {
	zpm1->SetPosition(GetX()-13,GetY()-5);
	zpm1->SetYDir();
  }
  else
  {
	  zpm1 = CreateObject(ZPM2);
	  SetObjectOrder(zpm1,this);
  }
  if(zpm2)
  {
	  zpm2->SetPosition(GetX()+3,GetY()-5);
	  zpm2->SetYDir();
  }
  else
  {
	  zpm2 = CreateObject(ZPM2);
	  SetObjectOrder(zpm2,this);
  }
  if(zpm3)
  {
	  zpm3->SetPosition(GetX()+13,GetY()-5);
	  zpm3->SetYDir();
  }
  else
  {
	  zpm3 = CreateObject(ZPM2);
	  SetObjectOrder(zpm3,this);
  }
  if(info)
  {
   Message(Format("%v (%v%)|%v (%v%)|%v (%v%)",ZpmA(),EnrgA(),ZpmB(),EnrgB(),ZpmC(),EnrgC()),this());
  }
  else Message("");
  return(1);
}

func GiveEnerg()
{
  if(zpm1->GetZpm() != 0)
  {
   if(GetAction(zpm1) eq "Activen")
   {
    zpm1->Minus();
    DoEnergy(10000);
    return(1);
   }
  }
  
  if(zpm2->GetZpm() != 0)
  {
   if(GetAction(zpm2) eq "Activen")
   {
    zpm2->Minus();
    DoEnergy(10000);
    return(1);
   }
  }
  
  if(zpm3->GetZpm() != 0)
  {
   if(GetAction(zpm3) eq "Activen")
   {
    zpm3->Minus();
    DoEnergy(10000);
    return(1);
   }
  }
  return(0);
}

func Free()
{
  if(zpm1->GetZpm() == 0)
  {
   return(1);
  }
  if(zpm2->GetZpm() == 0)
  {
   return(1);
  }
  if(zpm3->GetZpm() == 0)
  {
   return(1);
  }
  return(0);
}

func HasZpm()
{
  if(zpm1->GetZpm() != 0)
  {
   return(1);
  }
  if(zpm2->GetZpm() != 0)
  {
   return(1);
  }
  if(zpm3->GetZpm() != 0)
  {
   return(1);
  }
  return(0);
}

func ControlDigDouble(pCaller)
{
  User = pCaller;
  CreateMenu(GetID(this()), User, 0,0, "ZPM Konsole", 0, 1);
  AddMenuItem("Info An/Aus", "Info",MEPU,User);
  if(FindContents(ZPM_,User))
  {
   if(Free())
   {
    AddMenuItem("ZPM hineinlegen","PutZpm",MEPU,User);
   }
  }
  if(HasZpm())
  {
   AddMenuItem("ZPM herausnehmen","GetZpm",MEPU,User);
  }
  
  
  if(ZpmA() eq "1.ZPM:<c 00ff00> Aktiv</c>")
  {
   AddMenuItem("1.ZPM Deaktivieren","SwtZpmA",MEPU,User);
  }
  if(ZpmA() eq "1.ZPM:<c 0000ff> Inaktiv</c>")
  {
   AddMenuItem("1.ZPM Aktivieren","SwtZpmA",MEPU,User);
  }
  
  if(ZpmB() eq "2.ZPM:<c 00ff00> Aktiv</c>")
  {
   AddMenuItem("2.ZPM Deaktivieren","SwtZpmB",MEPU,User);
  }
  if(ZpmB() eq "2.ZPM:<c 0000ff> Inaktiv</c>")
  {
   AddMenuItem("2.ZPM Aktivieren","SwtZpmB",MEPU,User);
  }
  
  if(ZpmC() eq "3.ZPM:<c 00ff00> Aktiv</c>")
  {
   AddMenuItem("3.ZPM Deaktivieren","SwtZpmC",MEPU,User);
  }
  if(ZpmC() eq "3.ZPM:<c 0000ff> Inaktiv</c>")
  {
   AddMenuItem("3.ZPM Aktivieren","SwtZpmC",MEPU,User);
  }
  return(1);
}

func SwtZpmA()
{
  if(GetAction(FindContents(ZPM_,zpm1)) eq "Activen")
  {
   FindContents(ZPM_,zpm1)->SetAction("Inactive");
  }
  else
  {
   FindContents(ZPM_,zpm1)->SetAction("Activen");
  }
  return(1);
}

func SwtZpmB()
{
  if(GetAction(FindContents(ZPM_,zpm2)) eq "Activen")
  {
   FindContents(ZPM_,zpm2)->SetAction("Inactive");
  }
  else
  {
   FindContents(ZPM_,zpm2)->SetAction("Activen");
  }
  return(1);
}

func SwtZpmC()
{
  if(GetAction(FindContents(ZPM_,zpm3)) eq "Activen")
  {
   FindContents(ZPM_,zpm3)->SetAction("Inactive");
  }
  else
  {
   FindContents(ZPM_,zpm3)->SetAction("Activen");
  }
  return(1);
}

func GetZpm()
{
  if(zpm1->GetZpm() != 0)
  {
   FindContents(ZPM_,zpm1)->Enter(User);
   return(1);
  }
  
  if(zpm2->GetZpm() != 0)
  {
   FindContents(ZPM_,zpm2)->Enter(User);
   return(1);
  }
  
  if(zpm3->GetZpm() != 0)
  {
   FindContents(ZPM_,zpm3)->Enter(User);
   return(1);
  }
  return(1);
}

func PutZpm()
{
  if(!FindContents(ZPM_,User))
  {
   return(1);
  }
  
  if(zpm1->GetZpm() == 0)
  {
   FindContents(ZPM_,User)->Enter(zpm1);
   return(1);
  }
  
  if(zpm2->GetZpm() == 0)
  {
   FindContents(ZPM_,User)->Enter(zpm2);
   return(1);
  }
  
  if(zpm3->GetZpm() == 0)
  {
   FindContents(ZPM_,User)->Enter(zpm3);
   return(1);
  }
  return(1);
}

func Info()
{
  if(info)
  {
   info = 0;
  }
  else
  {
   info = 1;
  }
  Sound("Connect");
  return(1);
}
func IsAntiker()
{
	return(1);
}

public func Set(int value)
{
	if(value == 1) return ChangeEnergyMode();
}

protected func ChangeEnergyMode()
{
	if(!iMode)
	{
		iMode = 1;
		return AddEffect("IntEnergy",this,1,1,this);
	}
	else
	{
		iMode = 0;
		return RemoveEffect("IntEnergy",this);
	}
}

/*
0: target-Variable des Sternenantrieb-Kontrollers
1: Objekte, die mit dem Sternenantrieb bewegt werden -> Zugehörigkeit zu Atlantis
*/
protected func FxIntEnergyStart(object pTarget, int iEffect)
{
	if(!FindObject2(Find_ID(ALSK),Find_Owner(GetOwner()))) return -1;
	FindObjects(Find_ID(PWRL),Find_ActionTarget(this),Find_Func("RemoveObject"));
	EffectVar(0,pTarget,iEffect) = LocalN("targets",FindObject2(Find_ID(ALSK),Find_Owner(pTarget->GetOwner())));
	return true;
}

protected func FxIntEnergyTimer(object pTarget, int iEffect)
{
	EffectVar(1, pTarget,iEffect) = CreateArray();
	for(drive in EffectVar(0, pTarget, iEffect))
	{
		for(obj in drive->FindObjects(Find_InRect(-40,AbsY(0),80,GetY()+20),Find_Or(Find_Owner(pTarget->GetOwner()),Find_Owner(-1))))
		{
			if(GetDefCoreVal("LineConnect","DefCore",obj->GetID()) & C4D_PowerConsumer)
			{
				GiveEnerg();
				var energy = GetEnergy(pTarget) / 3;
				var limit = 100 - GetEnergy(pTarget);
				energy = Min(Min(energy, limit), 20);
				DoEnergy(-energy, pTarget);
				DoEnergy(energy, obj);
			}
		}
	}
}