/*--- Dart ---*/

#strict 2
#include VHCL

local open;    //Ist momentan die Luke geöffnet?
local iExtra;  //Ne winzige Hilfsvariable für die Turn funktion
local fire;    //Sammelstrahl oder Blaster aktiv?
local timer;   //N kleiner Hilfstimer. Wenn du gut bist, findest du raus wofür xD
local core;    //Hier wird der Kern gespeichert, was gibts sonst noch zu sagen?
local light;   //Wo ist der Sammelstrahl???... DDAAA ist der Sammelstrahl!
local on;      //Ist der Sammelstrahl an?
local alflusy; //Alternatives Flug System
local Wdamage; //Soviel schaden kann man haben, bis das Vehikel nichtmehr feuert.
local Fdamage; //Soviel schaden kann man haben, bis das Vehikel nichtmehr fliegt.
local Gate;	   //Platzhaltervariable für das Gateanwählen.

//Wer erräts? In der Initialize werden erstmal die Standarts gesetzt
public func Initialize() 
{
	_inherited(...);
	chevrons = [];
  Wdamage = 300;				//Schaden für Waffen: 	Check
  Fdamage = 450;				//Schaden fürs Fliegen:	Check
  alflusy = 1;					//Alternatives Flugsystem anschalten
  SetAction("Open");			//Der Dart ist regulär offen geliefert
  energy = 100;				//Jawohl, volle Akkus bei lieferung
  AddDamageEffect(this);		//Juhu, der Dart ist Raucher
  core = CreateObject(WRDC);	//Jetzt noch der Wraithkern für Lebewesenspeicherung
  ScheduleCall(0,"LightSet",1);	//Und noch n kleier Timer um den Sammelstrahl zu setzen
  
  Icon_Hatch = WRD1;
  return(1);
}

//Na endlich... 1 Tick nach Initialize wird der Sammelstrahl und Kern gesetzt.
public func LightSet()
{
  light = CreateObject(WRDB);	//Erstmal Sammelstrahl erzeugen
  LocalN("on",light) = 0;		//Sammelstrahl ist AUUUUUS
  light->TurnOff();				//Ja, komplett aus
  light->SetTarg(core);			//Dem Sammelstrahl den Kern vorstellen...
  core -> SetTarg(this());		//...Dem Kern sagen, dass der Sammelstrahl was von ihm will
  return(1);
}

//Jaja, der Dart muss auch kaputt gehen können.
public func Destruction()
{
  if(FindObject2(Find_Container(core)))	//Is jemand im Kern?
  {
   core->SaveMe();						//Verdaaaamt, der Kern muss noch gerettet werden!
  }
  else
  {
   core->RemoveObject();				//Nimand drinne? Dann brauchen wir das Ding nichtmehr. POFF, weg...
  }
  light->RemoveObject();				//Der Sammelstrahl hat keinen Schleudersitz und muss den Kern verlassen
  return(1);
}

//Jetzt wird geöffnet:
public func Open()
{
  open=1;
  SetEntrance(1);				//Das war jetzt schwer. Puh
  return(1);
}

//Und wieder geschlossen:
public func Close()
{
  open=0;
  SetEntrance(0);				//Fast noch schwerer als zu öffnen...
  return(1);
}

//FEEEEUUUUEEEEERRRR!!! Ratatatatatat
public func ContainedThrow(pCaller)
{
  SetOwner(GetOwner(pCaller));	//Jetzt wird endlich der Eigentümer von dem Ding gesetzt

  if(GetDamage() > Wdamage)		//Haben wir zuviel Schaden um zu Schießen?....
  {
   Sound("Electric");			//...Na dann wird jetz auch nix aus Schießen und es gibt nen tollen Sound.
   return(1);
  }

  if(fire == 1)					//Haben wir den Sammelstrahl aktiv?
  {
   Harvest(pCaller);			//Surrrrr
   return(1);
  }
  if(fire == 0)					//Oder doch lieber der Blaster?
  {
   Blaster(pCaller);			//Blaster: AKTIVIEREN
   return(1);
  }
  return(1);
}

//Peng, Peng
public func Blaster(pCaller)
{
  pPilot = pCaller;				//Und nochmal den Owner Setzen!

  if(GetAction() == "Turn")  { return(1);}	//Ui, ich dreh mich!
  if(GetAction() != "Fly")   { return(0);}	//Juhuuuu, ich flieeeegeeeee...

  if(timer != 0)				//Schon wieder dieser Mysteriöse Timer grrrr
  {
   return(1);
  }
 
  else
  {
   if(GetDir() == 0)
   {
    var angle = 270;
   }
   if(GetDir() == 1)
   {
    var angle = 90;
   }
  }
  //Hmm, schade. Waren ja doch nicht sooo schwer. Nur n Paar FindObject2 Funktionen die sich ähneln.
  
  if(GetDir() == 0)				//Fliegen wir anch Rechts oder links?
  {
   var ammo = CreateObject(WRDS,-20,-2,GetOwner(pPilot));
   MuzzleFlash(40,pPilot,-20,-2,angle);
  }
  if(GetDir() == 1)				//Ohoh, nochmal != Richtungsabfrage
  {
   var ammo = CreateObject(WRDS,20,-2,GetOwner(pPilot));
   MuzzleFlash(40,pPilot,20,-2,angle);
  }
  
  ammo->Launch(angle + RandomX(-5,5),300,1500,10,500,200);	//BOOOOOOOM
  ammo->SetOwner(GetOwner(pPilot));							//Eigentümer des Projektils setzen
  Sound("DartBlast");										//Und der Wuuuunderbare Sound
  timer = 20;												//Mysteriöser Timer auf 20? Nagut!
  return(1);
}

//Surrr, der Harvester kommt. MUAHAHA
public func Harvest()
{
  if(GetAction() != "Fly")	//Nur wenn wir fliegen!
  {
   return(1);
  }

  if(!on)					//Ohgott, der Sammelstrahl ist aus
  {
   if(timer != 0)			//Wenn du mir nicht bald sagst, was der timer macht, dann kündige ich!
   {
    Sound("start");
    return(1);
   }
  }

  if(on)					//Gottseidank er läuft wieder
  {
   LocalN("outfade",light) = 1;
   on = 0;
   Sound("DartBlast");
   return(1);
  }

  if(!on)					//Schonwieder off?
  {
   LocalN("on",light) = 1;
   LocalN("stay",light) = 50;
   light->TurnOn();
   light->SetCon(10);
   on = 1;
   Sound("DartBlast");
   timer = 300;
   return(1);
  }
  return(1);
}
public func OnDmg(int iDmg, int iType) 
{
  //Das erklär ich jetz aber nicht alles. Das is nur die Entfindlichkeit.
  if(iType == DMG_Bio)			return(100);
  if(iType == DMG_Melee)		return(40);
  if(iType == DMG_Fire)			return(50);
  if(iType == DMG_Explosion)	return(0);
  return(30);
}

//Natoll, die Timerüberprüfung aus der Defcore. Da steht alles drinnen.
public func Aktiviti()
{
  if(open)					//Ist die Türe offen?
  {
   SetEntrance(1);			//Dann ist der Eingang auch auf
  }
  
  if(!open)					//Was? Türe zu?
  {
   SetEntrance(0);			//Dann auch der Eingang zu
  }
  
  if(GetAction() == "Fly")
  {
   SetEntrance(0);
  }
  
  
  if(GetDamage() > Fdamage || !FindObject2(Find_OCF(OCF_CrewMember), Find_Container(this)))	//Haben wir zuviel Schaden um zu Fliegen...
  {
   SetAction("Open");		//...dann Ist die Türe immer auf und wir können nichtmehr Starten,...
   open = 1;				//...Und man kann immer Betreten und verlassen!
   return(1);
  }


  if(alflusy)				//Alternatives Flugsystem: Check
  {
   if(GetAction() != "Turn")	//Juhuuu, ich drehe mich!
   {
    if(GetXDir() > 0)
    {
     if(GetDir() == 0)
     {
      SetComDir(COMD_Right);
      SetAction("Turn");
      iExtra ++;				//Und die Extradaten nicht vergessen
     }
    }
    if(GetXDir() < 0)
    {
     if(GetDir() == 1)
     {
      SetComDir(COMD_Left);
      SetAction("Turn");
      iExtra ++;				//Auch hier wird an Extradaten gedacht
     }
    }
   }
  }

  if(!FindObject2(Find_OCF(OCF_CrewMember), Find_Container(this)))	//Bremsen, wenn nimand im Cockpit sitzt!
  {
   if(GetXDir() > 0)
   {
    SetComDir(COMD_Left);							//Links: Check
   }
   if(GetXDir() < 0)
   {
    SetComDir(COMD_Right);						//Rechts: Check
   }
   if(GetYDir() > 0)
   {
    SetComDir(COMD_Up);							//Oben: Check
   }
   if(GetYDir() < 0)
   {
    SetComDir(COMD_Down);							//Unten: Check
   }
   if(GetXDir() == 0)
   {
    if(GetYDir() == 0)
    {
     SetXDir(0);									//Jaja, stehenbleiben muss auch sein!
     SetYDir(0);
     SetComDir(COMD_Stop);
    }
   }
   if(FindObject(0,-50,-5,100,140,OCF_CrewMember,"Jump"))				//Will hier einer Rein?
   {
    if(GetAction() == "Fly")											//Erstmal überprüfen ob wir fliegen
    {
     var clnok2 = FindObject(0,-50,-5,100,140,OCF_CrewMember,"Jump");	//Derhier will rein!
     clnok2 -> Enter(this);											//Rein mit dir!
     clnok2 -> SetAction("Walk");										//Und Aktion "Gehen" Setzen!
     clnok2 -> SetComDir(COMD_Stop);									//Und letztes Sprungkommando löschen
     light -> TurnOn();													//Und noch nen kurzen Lichteffekt
     light -> SetCon(100);
     LocalN("outfade",light) = 1;
     Sound("DartButton");												//Und den Sound nicht vergessen
    }
   }
  }

  if(on)											//Sind wir on?
  {
   if(GetAction() != "Fly")							//Fliegen wir?
   {
    if(GetAction() != "Turn")						//Drehen wir uns?
    {
     Harvest();										//Sammeln!
    }
   }
  }

  if(timer != 0)			//Jaja, der Mysteriöse timer ist wohl für die Sammelstrahl ladezeit
  {
   timer --;				//Und muss natürlich wieder zurück auf 0
  }
  return(1);
}


public func ContactBottom()		//Aua, wir haben den Boden berührt
{
  if(GetAction() == "Fly")
  {
   SetAction("Stand");
   return(1);
  }
  return(1);
}

protected func ContainedUpDouble()			//Stehenbleiben bei Doppelhoch!
{
  if(GetAction() == "Turn") { return(0); }	//Nur wenn wir uns nicht drehen!
  SetComDir(COMD_Stop);
  SetXDir(0);
  SetYDir(0);
  return(1);
}

protected func MakeMenu()
{
	_inherited(...);
	pPilot->AddStructMenuItems([
		StructMenu_MenuEntry(WRD3, "Motor Aus", "", "Enginestop"),
		StructMenu_ConditionalMenuEntry(WRD5, "Blaster", "", fire, "FireSwitch"),
		StructMenu_ConditionalMenuEntry(WRD6, "Harvester", "", !fire, "FireSwitch"),
		StructMenu_ConditionalMenuEntry(WRD7, "Freilassen", "", FindObject2(Find_Container(core)), "Exiting")
		]);
  return true;
}

func Exiting()
{
  light -> TurnOn();
  light -> SetCon(100);
  LocalN("outfade",light) = 1;
  Sound("DartButton");
  core->Eject();
  return(1);
}

func FireSwitch()
{
  timer = 0;
  LocalN("on",light) = 0;
  light->TurnOff();
  on = 0;
  
  if(fire == 0)
  {
   PlayerMessage(GetOwner(pPilot),"Harvester",this());
   fire = 1;
   Sound("DartButton");
   return(1);
  }
  if(fire == 1)
  {
   PlayerMessage(GetOwner(pPilot),"Blaster",this());
   fire = 0;
   Sound("DartButton");
   return(1);
  }
  return(1);
}

func Hatch()
{
  if(GetAction() == "Stand")
  {
   if(open)
   {
    SetAction("Closes");
    return(1);
   }
  
   if(!open)
   {
    SetAction("Opens");
    return(1);
   }
  }
  
  if(GetAction() == "Open")
  {
   if(open)
   {
    SetAction("Closes");
    return(1);
   }
  
   if(!open)
   {
    SetAction("Opens");
    return(1);
   }
  }
  return(1);
}

func Enginestop()
{
  if(GetAction() == "Fly")
  {
   SetAction("Stand");
  }
  return(1);
}

func EMPShock()
{
  EMPShockEffect(50);
  DoDamage(2);
  return(1);
}

public func Destroy()
{
  Explode(50);
  return(1);
}

public func ExitPilot() 
{
	if(GetAction() == "Stand") return;

  if(!open)
  {
   Hatch();
   return(1);
  }

  pPilot->Exit();
  pPilot->SetAction("Walk");
  
  if(GetDir() == 0)
  {
   pPilot->SetPosition(GetX(pPilot)+30,GetY(pPilot)+15);
   SetEntrance(1);
   return(1);
  }
  
  pPilot->SetPosition(GetX(pPilot)-30,GetY(pPilot)+15);
  SetEntrance(1);
  return(1);
}

protected func ContainedUp()
{
  if(GetAction() == "Turn") { return(0); }

  if(GetAction() == "Fly")
   {
   if(GetComDir() == COMD_UpLeft || GetComDir() == COMD_UpRight) SetComDir(COMD_Up);
   if(GetComDir() == COMD_Down) SetComDir(COMD_Up);
   if(GetComDir() == COMD_Left) SetComDir(COMD_UpLeft);
   if(GetComDir() == COMD_DownLeft) SetComDir(COMD_Left); 
   if(GetComDir() == COMD_DownRight) SetComDir(COMD_Right);
   if(GetComDir() == COMD_Right) SetComDir(COMD_UpRight);
   if(GetComDir() == COMD_Stop) SetComDir(COMD_Up);
   return(true);
   }
   
   if(GetAction() == "Stand")
   {
    SetAction("Fly");
    return(1);
   }
  return(1);
}

protected func ContainedDown()
{
   if(!(GetAction() == "Fly"))
   { 
    return(0); 
   }

   if(GetComDir() == COMD_DownLeft ||GetComDir() == COMD_DownRight)
   {
    SetComDir(COMD_Down);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Up)
   {
    SetComDir(COMD_Stop);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Left) 
   {
    SetComDir(COMD_DownLeft);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_UpLeft)
   {
    SetComDir(COMD_Left);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Stop)
   {
    SetComDir(COMD_Down);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Right) 
   {
    SetComDir(COMD_DownRight);
    SetEntrance(0);
   }
   if(GetComDir() == COMD_UpRight)
   {
    SetComDir(COMD_Right);
    SetEntrance(0);
   }
  return(1);
}

protected func ContainedRight()
{
  if(GetAction() == "opens")  return(1);
  if(GetAction() == "open")   return(0);
  if(GetAction() == "close")  return(1);
  if(GetAction() == "Turn")   return(1);
  if(GetAction() == "Stand")  return(0);
  if(open)					  return(0);
  if(iExtra) return(0);
  
  if(alflusy == 1)
  {
   if(GetXDir() < 0)
   {
    SetCommand(this,"None");
    SetComDir(COMD_Right);
    return(1);
   }
  }
  
  SetCommand(this,"None");
  SetComDir(COMD_Right);
  
  if(GetDir() == DIR_Left)
  {
   SetAction("Turn");
   iExtra++;
  }
  return(1);
}

protected func ContainedLeft()
{
  if(GetAction() == "opens")  return(1);
  if(GetAction() == "open")   return(0);
  if(GetAction() == "close")  return(1);
  if(GetAction() == "Turn")   return(1);
  if(GetAction() == "Stand")  return(1);
  if(open)					  return(1);
  if(iExtra) return(0);
  
  if(alflusy == 1)
  {
   if(GetXDir() > 0)
   {
    SetCommand(this,"None");
    SetComDir(COMD_Left);
    return(1);
   }
  }
  
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
   if(!(GetAction() == "Fly")) { return(0); }

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
  return(true);
}

protected func ContainedLeftDouble()
{
   if(GetAction() == "Tarned") { return(0); }
   if(!(GetAction() == "Fly")) { return(0); }

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
  if(GetAction() == "Stand")
  SetAction("Fly",GetActionTarget(0),GetActionTarget(1));
  if(GetDir() == DIR_Left) SetComDir(COMD_UpLeft);
  if(GetDir() == DIR_Right) SetComDir(COMD_UpRight);
  return(true);
}



func IsMachine() 		{ return(1); }

func IsBulletTarget()    { return(1); }
public func GetRace() { return SGA_Wraith; }
public func CanDialGate() { return GetDamage() < 300; }
public func MaxDamage() { return 500; }