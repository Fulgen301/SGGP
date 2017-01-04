/*--- 
###############
###############
### Tel'tak ###
###############
###############
 ---*/

#strict 2
#include CVHC

//################
//### SONSTIGE ###
//################
local iMaxDamage, iAmmoCount, iExtra;  //Steuerung des Schiffes
local cloaked;                           //Tarnung
local chosen,chosen_timer;                           //Aktueller User


//#######################
//### RINGTRANSPORTER ###
//#######################
local ring1; //Innenbordringtransporter
//local ring2; //Außenbordringtransporter
local ringc; //RingtansporterBedinung

//################
//### HECKLUKE ###
//################
local luke1; //Heckluke
local lukec; //Hecklukensteuerung

//##############
//### ANDERE ###
//##############
local gen,gentime,genstate;   //Hyperraumgenerator
local pod;   //Fluchtkapsel
local selv;  //Selbstzerstörung
local entr;  //Eingangsbereich
local crate; //Transportkiste
local help, radius, on, time;   //Schild
local energy, mess,tangtime;  //Energie

public func HasGate()
{
	if(ring1->~IsStargate())
	{
		return(1);
	}
	return(0);
}

//#######################
//### Arrayerstellung ###
//#######################
local aInventory;

public func Initialize() 
{
	_inherited(...);
	energy = 100;
	on = 0;
	mess = 0;
	radius = 170;
  SetAction("Stand");  //Das Tel'tak Steht am anfang am Boden

//Damit das Tel'tak nicht feststeckt
  if(GetX() < 160)
  {
   SetPosition(160,GetY());
  }
  if(GetX() > (LandscapeWidth()-160))
  {
   SetPosition(LandscapeWidth()-160,GetY());
  }

//Heraussetzen aus Gebäuden
  if(Contained())
  {
   Exit();
  }
  Choose();
  return(1);
}

private func InitializeInventory()
{
	//#######################
//### RINGTRANSPORTER ###
//#######################
  ring1 = CreateObject(RIG1);  //Ringtransporter
  if(ring1->LocalN("ring2")) ring1->LocalN("ring2")->LocalN("target") = this;
  //ring2 = ring1->LocalN("ring2");  //Außenbordringtransporter
  ringc = CreateObject(RIG2);  //Ringtransportersteuerung
  LocalN("nobase",ringc) = 1;
  SetCategory(C4D_Vehicle,ringc);
  LocalN("nobase",ring1) = 1;

//################
//### HECKLUKE ###
//################
  luke1 = CreateObject(TEL3);  //Heckluke
  lukec = CreateObject(TEL2);  //Hecklukensteuerung

//##############
//### ANDERE ###
//##############
  gen   = CreateObject(TEL4);  //Hyperraumgenerator
  pod   = CreateObject(TEL5);  //Fluchtkapsel
  selv  = CreateObject(TELS);  //Selbstzerstörung
  entr  = CreateObject(TELZ);  //Eingangsbereich
  crate = CreateObject(TELK);  //Frachtkiste

//#######################
//### Arrayerstellung ###
//#######################
  return [ring1, ringc, luke1, lukec, gen, pod, selv, entr, crate];
}

func Choose()
{
	var own = GetCursor(GetOwner());
  CreateMenu(TEL_, own, 0, 0, "$Choose$", 0, 1);
	AddMenuItem(GetName(0,RIG1), "Ring", RIG1, own);
	AddMenuItem(GetName(0,STRG), "Gate", STGT, own);
	return(1);
}

func Ring()
{
	chosen=1;
	return(1);
}

func Gate()
{
	chosen=1;
	if(ring1) RemoveObject(ring1);
	//if(ring2) RemoveObject(ring2);
	if(ringc) RemoveObject(ringc);
	ring1=CreateObject(STGT);
	ring1->SetTeltak(this());
	ringc=CreateObject(DHD_);
	SetCategory(C4D_Vehicle,ring1);
	SetCategory(C4D_Vehicle,ringc);
	aInventory[0]=ring1;
	aInventory[1]=ringc;
	return(1);
}

//##########################
//### SCHADENSSTEUERUNG  ###
//##########################
public func Damage()
{
  if(GetDamage() > MaxDamage())
  {
   Call("Destroy");
  }
  return(1);
}


//Gibt TRUE zurück, wenn ein Teil fehlt!
public func CheckParts()
{
	if(ring1)
	{
	if(ringc)
	{
  if(luke1)
  {
  if(lukec)
  {
  if(gen)
  {
  if(pod)
  {
  if(selv)
  {
  if(entr)
  {
  if(crate)
  {
  return(0);
  }
  }
  }
  }
  }
  }
  }
  }
  }
  return(1);
}
        
public func Destroy()
{
  if(ring1)
  ring1-> RemoveObject();
  /*if(ring2)
  ring2-> RemoveObject();*/
  if(ringc)
  ringc->RemoveObject();
  if(luke1)
  luke1->RemoveObject();
  if(lukec)
  lukec->RemoveObject();
  if(gen)
  gen->RemoveObject();
  if(pod)
  pod->RemoveObject();
  if(selv)
  selv->Explode(20);
  if(entr)
  entr->RemoveObject();
  if(crate)
  crate->RemoveObject();
  if(shield) shield->RemoveObject();
  Explode(75);
  return(1);
}


public func Check()
{
if(GetCon() < 100) return;

//Wenn ein Teil fehlt: SELBSTZERSTÖRUNG!
  if(CheckParts() == 1)
  {
   if(GetCon() == 100)
   {
    Destroy();
    return(1);
   }
  }
  
  if(!chosen)
  {
  	chosen_timer+=1;
  	if(chosen_timer==100)
  	{
  		chosen_timer=0;
  		Choose();
  	}
  }
  
//Keine Positionsveränderung wärnd man getarnt ist
  if(cloaked)
  {
   if(GetAction() == "Fly")
   {
    SetXDir();
    SetYDir();
   }
  }

//##########################################
//### Positionierung der inneren Objekte ###
//##########################################
  //Seite: 1 (rechts)
  if(GetDir() == 1)
  {
   //Ringtransporter / Stargate
   if(GetID(ring1)==RIG1)
   {
   ring1 -> SetPosition(GetX()-20,GetY()+23);
   ringc -> SetPosition(GetX()+25,GetY()+25);
   }
   else
   {
   	ring1 -> SetPosition(GetX()-92,GetY()-17);
   	ringc->SetPosition(GetX()+25,GetY()+30);
   }
   
   //Heckluke
   luke1 -> SetPosition(GetX()-145,GetY()+25);
   luke1 -> Dir1();
   lukec -> SetPosition(GetX()-58,GetY()+25);
   
   //Andere
   gen ->   SetPosition(GetX()-100,GetY()+18);
   pod ->   SetPosition(GetX()+45,GetY()+25);
   selv ->  SetPosition(GetX()+70,GetY()+27);
   entr ->  SetPosition(GetX()+110,GetY()+27);
   crate -> SetPosition(GetX()-80,GetY()+30);
  }
  
  //Seite: 2 (links)
  if(GetDir() == 0)
  {
   //Ringtransporter
   if(GetID(ring1)==RIG1)
   {
   	ring1 -> SetPosition(GetX()+20,GetY()+23);
   	ringc -> SetPosition(GetX()-25,GetY()+25);
   }
   else
   {
   	ring1 -> SetPosition(GetX()-58,GetY()-17);
   	ringc->SetPosition(GetX()-25,GetY()+30);
   }

   //Heckluke
   luke1 -> SetPosition(GetX()+124,GetY()+25);
   luke1 -> Dir0();
   lukec -> SetPosition(GetX()+58,GetY()+25);
   
   //Andere
   gen ->   SetPosition(GetX()+100,GetY()+18);
   pod ->   SetPosition(GetX()-45,GetY()+25);
   selv ->  SetPosition(GetX()-70,GetY()+27);
   entr ->  SetPosition(GetX()-110,GetY()+27);
   crate -> SetPosition(GetX()+80,GetY()+30);
  }
  
  var x;
  for(x in aInventory)
  {
   x -> SetXDir();
   x -> SetYDir();
  }
//
  if ((GetAction(gen) == "Deactive")||(energy<10))
  {
	  SetPhysical("Float", 200, 3);
/*	  if (!cloaked)
	  {
		  /SetClrModulation(RGBa(0, 0, 0, 0));
		  var y;
		  for (y in aInventory)
		  {
			  y->SetClrModulation(RGBa(0, 0, 0, 0));
		  }
	  }*/
  }
  
  if (GetAction(gen) == "Active")
  {
	  genstate = 1;
	  SetPhysical("Float", 1100);
/*	  SetClrModulation(RGBa(0, 0, 255, 233));
	  for (y in aInventory)
	  {
		  y->SetClrModulation(RGBa(0, 0, 255, 233));
	  }
	  gentime += 1;
	  if (gentime == 50)
	  {
		  if (energy > 20)
		  {
			  energy -= 10;
			  gentime = 0;
		  }
	  }*/
  }
//###########################
//### SOLIDMASK-STEUERUNG ###
//###########################
/*  if(GetDir() == 0)
  {
   SetSolidMask(0,150,300,150);
  }

  if(GetDir() == 1)
  {
   SetSolidMask(300,150,300,150);
  }
*/
//###########################
//#### ENERGIE-STEUERUNG ####
//###########################
  if (crate->FindContents(TANG))
  {
	  tangtime+=1;
	  if (tangtime == 50)
	  {
		  energy += 3;
		  tangtime = 0;
	  }
  }
  if (energy < 0)
  {
	  energy = 0;
  }
  if (energy > 100)
  {
	  energy = 100;
  }
//###########################
//##### SCHILD-STEUERUNG ####
//###########################
  if(shield)
  {
	if(energy <= 15)
	{
		shield->RemoveObject();
	}
	else
		time++;
	    if(time % 50 == 0)
		{
			energy--;
			time = 0;
		}
  }

//#############################
//# ENERGIEANZEIGEN-STEUERUNG #
//#############################
  if (mess)
  {
	  Message("%v Energie", this(), energy);
  }
  
  for(obj in FindObjects(Find_Category(C4D_Vehicle),Find_Container(this)))
  {
	  if(obj) Exit(obj);
  }
}


//In der Luft stehenbleiben
public func ContainedUpDouble()
{
  SetComDir(COMD_Stop);
  SetXDir(0);
  SetYDir(0);
  return(1);
}

//Menüaufruf
public func MakeMenu(pCaller)
{
	_inherited(pCaller, ...);
  if(HasGate())
  {
  	AddMenuItem("$Iris$", "Iris", STGT, pPilot);
  }
  if(FindObject2(Find_ID(FLAG),Find_ActionTarget(this)))
  {
	  AddMenuItem("$Buy$","BuyMenu",SPIP,pPilot,0,pPilot);
	  AddMenuItem("$Sell$","SellMenu",DPIP,pPilot,0,pPilot);
  }
  return(1);
}

protected func BuyMenu()
{
	if(pPilot) SetCommand(pPilot,"Buy");
	return true;
}

protected func SellMenu()
{
	if(pPilot) SetCommand(pPilot,"Sell");
}

protected func ActivateMenu()
{
	if(pPilot) SetCommand(pPilot,"Activate",this);
}

public func EMPShock()
{
  EMPShockEffect(200);
  DoDamage(20);
  if(GetAction() == "Fly")
  {
   SetAction("StartStand");
  }
  return(1);
}

func ToggleEnergy()
{
	if (!mess)
	{
		mess = 1;
		return(1);
	}
	if (mess)
	{
		mess = 0;
		return(1);
	}
}

func BuildIris()
{
  if(GetID(ring1)==RIG1)
  {
   Sound("Error");
   return(1);
  }
  if(ring1->HasIris())
  {
   ring1->HasIris()->Update();
   Sound("Error");
   return(1);
  }
  ring1->InstallIris();
 	ring1->HasIris()->~SetCategory(C4D_Vehicle);
  return(1);
}

func Iris()
{
  if(GetID(ring1)==RIG1)
  {
   Sound("Error");
   return(1);
  }
  if(!ring1->HasIris())
  {
   BuildIris();
  }
  LocalN("iris", ring1)->Switch();
  return(1);
}

public func Hatch()
{
  if(GetAction(luke1) == "Open")
  {
   ObjectSetAction(luke1, "Close");
   Sound("ring_button2");
   return(1);
  }

  if(GetAction(luke1) == "Close")
  {
   ObjectSetAction(luke1, "Open");
   Sound("ring_button1");
   return(1);
  }
  return(1);
}




func Cloak()
{
  if(GetDamage() >= 500)
  {
   if(!cloaked)
   {
    Sound("start");
    return(1);
   }
  }
  Cloaking();
  return(1);
}


func Cloaking()
{
  if(cloaked)
  {
   cloaked = 0;
   SetAction("Tarnaus");
   Sound("sodan_cloak_off");
   return(1);
  }
  
  if(!cloaked)
  {
   cloaked = 1;
   SetAction("Tarnan");
   Sound("sodan_cloak_on");
   return(1);
  }
  return(1);
}

public func Visible()
{
  var x;
  for(x in aInventory)
  {
   x->SetOwner(GetOwner(pPilot));
   x->SetVisibility(VIS_All);
   x->SetClrModulation(0);
  }
  
  SetOwner(GetOwner(pPilot));
  SetVisibility(VIS_All);
  SetClrModulation(0);
  var flag;
  if(flag = FindObject2(Find_ID(FLAG), Find_Action("FlyBase"), Find_ActionTarget(this)))
  {
	  flag->SetVisibility(VIS_All);
	  flag->SetClrModulation(0);
  }
  return(1);
}

public func Invisible()
{
  var x;
  for(x in aInventory)
  {
   x->SetOwner(GetOwner(pPilot));
   x->SetVisibility(VIS_Owner);
   x->SetClrModulation(RGBa(0,0,100,100));
  }

  SetOwner(GetOwner(pPilot));
  SetVisibility(VIS_Owner);
  SetClrModulation(RGBa(0,0,100,100));
  var flag;
  if(flag = FindObject2(Find_ID(FLAG), Find_Action("FlyBase"), Find_ActionTarget(this)))
  {
	  flag->SetVisibility(VIS_Owner);
	  flag->SetClrModulation(RGBa(0,0,100,100));
  }
  return(1);
}


public func ExitPilot()
{
  pPilot->Exit();
  
  if(GetDir() == 0)
  {
   pPilot->SetPosition(GetX()-100,GetY()+27);
   return(1);
  }
  
  pPilot->SetAction("Walk");
  pPilot->SetPosition(GetX()+100,GetY()+27);
  return(1);
}

protected func ContainedThrow()
{
  if(GetAction() == "Fly")
  {
   SetAction("StartStand");
   return(1);
  }

  if(GetAction() == "Stand")
  {
   SetAction("Standend");
   return(1);
  }

  return(1);
}


func SDir()
{
  SetAction("Wenden");
  return(true);
}  

protected func ContainedUp()
{
  if(GetAction() == "Stand")
  {
   SetAction("Standend");
   return(1);
  }

  if(GetComDir() == COMD_UpLeft || GetComDir() == COMD_UpRight) SetComDir(COMD_Up);
  if(GetComDir() == COMD_Down) SetComDir(COMD_Up);
  if(GetComDir() == COMD_Left) SetComDir(COMD_UpLeft);
  if(GetComDir() == COMD_DownLeft) SetComDir(COMD_Left); 
  if(GetComDir() == COMD_DownRight) SetComDir(COMD_Right);
  if(GetComDir() == COMD_Right) SetComDir(COMD_UpRight);
  if(GetComDir() == COMD_Stop) SetComDir(COMD_Up);
  return(true);
}

protected func ContainedDown()
{
//  if(GetAction() == "Fly") 
//   {

  if(GetAction() == "Stand")
  {
   SetAction("Standend");
   return(1);
  }

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
//  SetAction("Stand",GetActionTarget(0),GetActionTarget(1));
//  if(GetAction() == "Stand") SetEntrance(1);
  return(true);
}

protected func ContainedRight()
{

  if(GetAction() == "Stand")
  {
   SetAction("Standend");
   return(1);
  }

  if(iExtra) return(0);
  if(GetAction() == "Turn") return(0);
  SetCommand(this,"None");
  SetComDir(COMD_Right);
   if(GetDir() == DIR_Left)
    {
    SetAction("Turn");
    iExtra++;
    }
  return(true);
}

protected func ContainedLeft()
{

  if(GetAction() == "Stand")
  {
   SetAction("Standend");
   return(1);
  }

  if(iExtra) return;
  if(GetAction() =="Turn") return;
  SetCommand(this(),"None");
  SetComDir(COMD_Left);  
   if(GetDir() == DIR_Right)
    {
   SetAction("Turn");
   iExtra++;
   }
  return(true);
}

func Turned()
{
//Neusetzung der Crew und allem
  var obj;
  for(obj in FindObjects(Find_InRect(-150,-75,300,150),Find_OCF(OCF_Alive)))
  {
   obj->SetPosition(GetX()-(GetX(obj)-GetX()),GetY(obj));
  }

//###############################
//### Die Vertices neu setzen ###
//###############################
  if(GetDir() == 1)
  {
   SetVertexXY(1,-146,24);
   SetVertexXY(2,-100,0);
   SetVertexXY(3,-86,-15);
   SetVertexXY(4,-58,-25);
   SetVertexXY(5,-30,-43);
   SetVertexXY(6,7,-62);
   SetVertexXY(7,27,-75);
   SetVertexXY(8,55,-60);
   SetVertexXY(9,78,-41);
   SetVertexXY(10,96,-26);
   SetVertexXY(11,117,-5);
   SetVertexXY(12,-117,41);
   SetVertexXY(13,128,49);
   SetVertexXY(14,144,43);
   SetVertexXY(15,151,29);
   SetVertexXY(16,-126,10);
   SetVertexXY(17,133,11);
   SetVertexXY(18,-81,45);
   SetVertexXY(19,105,54);
   SetSolidMask(0,150,300,150);
  }
  
  if(GetDir() == 0)
  {
   SetVertexXY(1,146,24);
   SetVertexXY(2,100,0);
   SetVertexXY(3,86,-15);
   SetVertexXY(4,58,-25);
   SetVertexXY(5,30,-43);
   SetVertexXY(6,-7,-62);
   SetVertexXY(7,-27,-75);
   SetVertexXY(8,-55,-60);
   SetVertexXY(9,-78,-41);
   SetVertexXY(10,-96,-26);
   SetVertexXY(11,-117,-5);
   SetVertexXY(12,117,41);
   SetVertexXY(13,-128,49);
   SetVertexXY(14,-144,43);
   SetVertexXY(15,-151,29);
   SetVertexXY(16,126,10);
   SetVertexXY(17,-133,11);
   SetVertexXY(18,81,45);
   SetVertexXY(19,-105,54);
   SetSolidMask(300,150,300,150);
  }

//Der rest:
  if(GetDir() == DIR_Left) SetDir(DIR_Right);
  else SetDir(DIR_Left);
  iExtra = 0;
  return(true);
}   

public func Stop() 
{
  SetComDir(COMD_Stop);
  SetYDir(0);
  SetXDir(0);
  return(true);
}

protected func ContainedRightDouble()
{

  if(GetAction() == "Stand")
  {
   SetAction("Standend");
   return(1);
  }

  if(GetDir() == DIR_Right)
  {
   SetComDir(COMD_Stop);
   SetYDir(0);
   SetComDir(COMD_Right);
  }
  else
  {
   SetAction("Wenden");
  }
  return(1);
}

protected func ContainedLeftDouble()
{
  if(GetAction() == "Stand")
  {
   SetAction("Standend");
   return(1);
  }

  if(GetDir() == DIR_Left)
  {
   SetComDir(COMD_Stop);
   SetYDir(0);
   SetComDir(COMD_Left);
  }
  else
  {
   SetAction("Wenden");
  }
  return(true);
}

public func Starting()
{
  SetAction("Fly",GetActionTarget(0),GetActionTarget(1));
  if(GetDir() == DIR_Left) SetComDir(COMD_UpLeft);
  if(GetDir() == DIR_Right) SetComDir(COMD_UpRight);
  return(true);
}

public func ContactLeft()
{
  return(SDir());
}

public func ContactRight()
{
  return(SDir());
}

public func ContactBottom()
{
  if(GetAction() == "Fly")
  {
   SetAction("StartStand",GetActionTarget(0),GetActionTarget(1));
   return(1);
  }
  return(1);
}

func Wenden()
{
  SetComDir(COMD_Stop);
  return(true);
}

private func ToggleShield()
{
	_inherited(...);
	if(shield) shield->SetActionData(256+20);
}

func Shield()
{
	if (on)
	{
		//Depledetbearbeitung
		if (energy <= 10)
		{
			on = 0;
			return(1);
		}

		//Effektbearbeitung
		help += 10;
		var pX;
		var pY;
		pX = Cos(help, radius);
		pY = Sin(help, radius);
		CreateParticle("PSpark", pX, pY, RandomX(-10, 10), RandomX(-10, -20), RandomX(40, 60));
		pX = Cos(help + 180, radius);
		pY = Sin(help + 180, radius);
		CreateParticle("PSpark", pX, pY, RandomX(-10, 10), RandomX(-10, -20), RandomX(40, 60));
		time += 1;
		if (time == 50)
		{
			energy -= 1;
			time = 0;
		}

   //ABSTOSSVERHALTEN
   for(target in FindObjects(Find_Distance(radius-10),Find_OCF(OCF_HitSpeed4)))
   {
    //Jumperdrohne
	   if (GetID(target) == PUDD)
	   {
		   target->~Hit();
		   energy -= 5;
		   if (!target)
		   {
			   return(1);
		   }
	   }
    
    //Meteorid
    if(GetID(target) == METO)
    {
     target->~Hit();
     return(1);
    }
   }
  
   //Trefferbearbeitung 2
   for(target in FindObjects(Find_Distance(radius),Find_Not(Find_Distance(radius - radius/8))))
   {
    //Objekt wird nicht abgestoßen, wenn es sich nicht bewegt!
    if((GetXDir(target) + GetYDir(target)) == 0)
    {
     return(1);
    }
    
    if (GetCategory(target) & C4D_Structure)
    {
    	return(1);
    }
    
    //Normale Kugel
    if(target->~IsBullet() == 1)
    {
     target->RemoveObject();
//     energy -= 2;
     return(1);
    }
    
    //KULL Ignorieren
    if(GetID(target) == KULL)
    {
     if(target->~HasGear())
     {
      return(1);
     }
    }
    
    //Jumperdrohne
    if(GetID(target) == PUDD)
    {
     target->~EMPShock();
     //energy -= 5;
     if(!target)
     {
      return(1);
     }
    }
    
    //Meteorid
    if(GetID(target) == METO)
    {
     target->~Hit();
	 energy -= 5;
     return(1);
    }

	if (GetID(target) == REDR)
	{
		target->~Hit();
		energy -= 5;
		return(1);
	}
    
    //Rakete
    if(GetID(target) == MISS)
    {
     target->~Hit();
     energy -= 10;
     if(!target)
     {
      return(1);
     }
    }
    
    //Lenkrakete
    if(GetID(target) == HMIS)
    {
     target->~Hit();
     energy -= 13;
     if(!target)
     {
      return(1);
     }
    }

    /*if(GetOCF(target) & OCF_Construct())
    {
     return(1);
    }*/

    target->~SetAction("Walk");
    target->SetXDir((GetX(target)-RandomX(GetX()+2,GetX()-2)) / 5);
    target->SetYDir((GetY(target)-GetY()) / 5);
   }
  }
  
  return(1);
}

protected func UpdateTransferZone()
{
	if(shield) shield->SetActionData(256+20);
}

public func ExitingHyperspace(object pHyperspace)
{
	if(!HasStargate() && !ring1) return;
	if(ring1->HasIris()) SetObjectOrder(ring1, ring1->HasIris());
}

public func IsBulletTarget(id idBullet, object pBullet, object pShooter)
{
	if(pBullet && pBullet->GetOwner() != GetOwner() && Hostile(pBullet->GetOwner(), GetOwner()))
		return true;
	
	return false;
}
public func IsMachine() 		{ return(1); }
public func Teltak()			{ return true; }
public func HasHyperdrive()		{ return GetDamage() < 500 && energy >= 70; }
public func HasShield()			{ return energy > 15; }
public func CanCloak()			{ return true; }
public func MaxDamage() 		{ return 1000; }