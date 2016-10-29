/*--- Dart ---*/

#strict

local iEnergy; //Sowas ist eigentlich recht unwichtig...
local pUser;   //Ey, wer fliegt mich?
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
local MaxDam;  //Soviel schaden kann man haben, bis man in die Luft fliegt.
local Gate;	   //Platzhaltervariable für das Gateanwählen.

//Wer erräts? In der Initialize werden erstmal die Standarts gesetzt
public func Initialize() 
{
  MaxDam = 500;					//Maximaler Schaden: 	Check
  Wdamage = 300;				//Schaden für Waffen: 	Check
  Fdamage = 450;				//Schaden fürs Fliegen:	Check
  alflusy = 1;					//Alternatives Flugsystem anschalten
  SetAction("Open");			//Der Dart ist regulär offen geliefert
  iEnergy = 100;				//Jawohl, volle Akkus bei lieferung
  AddDamageEffect(this);		//Juhu, der Dart ist Raucher
  core = CreateObject(WRDC);	//Jetzt noch der Wraithkern für Lebewesenspeicherung
  ScheduleCall(0,"LightSet",1);	//Und noch n kleier Timer um den Sammelstrahl zu setzen
  return(1);
}

//Aua, das tut weh
public func Hit2()
{
  DoDamage(1);
  return(1);
}

//Hier wirds aber langsam kritisch!
public func Hit3()
{
  DoDamage(2);
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

//Oh, toll ne Funktion, damit nur 1 Clonk drinnen sitzen kann. Geht nur leider nicht.
public func RejectCollect(id idObj, object pObj)
{
  if(GetOCF(pObj) & OCF_CrewMember())
  {
   if(FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this()))
   {
    return(1);
   }
  }
  return();
  //An alle Scripter unter euch, die das Lesen. Bitte meldet mir, wiso es nicht geht...
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
  pUser = pCaller;				//Und nochmal den Owner Setzen!

  if(GetAction() eq "Turn")  { return(1);}	//Ui, ich dreh mich!
  if(GetAction() ne "Fly")   { return(0);}	//Juhuuuu, ich flieeeegeeeee...

  if(timer != 0)				//Schon wieder dieser Mysteriöse Timer grrrr
  {
   return(1);
  }
  
  //Achtung, jetzt folgen sehr komplizierte Funktionen, wenn du die verstehst, bist du ich.
  if(FindObject2(Find_Distance(700),Find_OCF(OCF_InFree()),Find_Hostile(GetOwner(pUser)),Sort_Distance(),Find_Or(Find_OCF(OCF_Alive()),Find_Category(C4D_Structure()))))
  {
   var pTarget = FindObject2(Find_Distance(700),Find_OCF(OCF_InFree()),Find_Hostile(GetOwner(pUser)),Sort_Distance(),Find_Or(Find_OCF(OCF_Alive()),Find_Category(C4D_Structure())));
   var angle = Angle(Abs(GetX()),Abs(GetY()),Abs(GetX(pTarget)),Abs(GetY(pTarget)));
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
   var ammo = CreateObject(WRDS,-20,-2,GetOwner(pUser));
   MuzzleFlash(40,pUser,-20,-2,angle);
  }
  if(GetDir() == 1)				//Ohoh, nochmal ne Richtungsabfrage
  {
   var ammo = CreateObject(WRDS,20,-2,GetOwner(pUser));
   MuzzleFlash(40,pUser,20,-2,angle);
  }
  
  ammo->Launch(angle + RandomX(-5,5),300,1500,10,500,200);	//BOOOOOOOM
  ammo->SetOwner(GetOwner(pUser));							//Eigentümer des Projektils setzen
  Sound("DartBlast");										//Und der Wuuuunderbare Sound
  timer = 20;												//Mysteriöser Timer auf 20? Nagut!
  return(1);
}

//Surrr, der Harvester kommt. MUAHAHA
public func Harvest()
{
  if(GetAction() ne "Fly")	//Nur wenn wir fliegen!
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

public func MaxDamage() { return (MaxDam); }	//Maximaler Schaden ist 500

public func OnDmg(int iDmg, int iType) 
{
  //Das erklär ich jetz aber nicht alles. Das is nur die Entfindlichkeit.
  if(iType == DMG_Bio)			return(100);
  if(iType == DMG_Melee)		return(40);
  if(iType == DMG_Fire)			return(50);
  if(iType == DMG_Explosion)	return(0);
  return(30);
}

//Wird bei Schaden aufgerufen, noch fragen?
public func Damage()
{
  if(GetDamage(this()) >= MaxDam)					//KABOOOOM, wenn wir zuviel Schaden haben.
  {
   Call("Destroy");									//Und Destroy wird aufgerufen
   return(1);
  }
  return(1);
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
  
  if(GetAction() eq "Fly")
  {
   SetEntrance(0);
  }
  
  
  if(GetDamage() > Fdamage)	//Haben wir zuviel Schaden um zu Fliegen...
  {
   SetAction("Open");		//...dann Ist die Türe immer auf und wir können nichtmehr Starten,...
   open = 1;				//...Und man kann immer Betreten und verlassen!
   return(1);
  }


  if(alflusy)				//Alternatives Flugsystem: Check
  {
   if(GetAction() ne "Turn")	//Juhuuu, ich drehe mich!
   {
    if(GetXDir() > 0)
    {
     if(GetDir() == 0)
     {
      SetComDir(COMD_Right());
      SetAction("Turn");
      iExtra ++;				//Und die Extradaten nicht vergessen
     }
    }
    if(GetXDir() < 0)
    {
     if(GetDir() == 1)
     {
      SetComDir(COMD_Left());
      SetAction("Turn");
      iExtra ++;				//Auch hier wird an Extradaten gedacht
     }
    }
   }
  }

  if(!FindObject(0,0,0,0,0,OCF_Alive(),0,0,this()))	//Bremsen, wenn nimand im Cockpit sitzt!
  {
   if(GetXDir() > 0)
   {
    SetComDir(COMD_Left());							//Links: Check
   }
   if(GetXDir() < 0)
   {
    SetComDir(COMD_Right());						//Rechts: Check
   }
   if(GetYDir() > 0)
   {
    SetComDir(COMD_Up());							//Oben: Check
   }
   if(GetYDir() < 0)
   {
    SetComDir(COMD_Down());							//Unten: Check
   }
   if(GetXDir() == 0)
   {
    if(GetYDir() == 0)
    {
     SetXDir(0);									//Jaja, stehenbleiben muss auch sein!
     SetYDir(0);
     SetComDir(COMD_Stop());
    }
   }
   if(FindObject(0,-50,-5,100,140,OCF_CrewMember(),"Jump"))				//Will hier einer Rein?
   {
    if(GetAction() eq "Fly")											//Erstmal überprüfen ob wir fliegen
    {
     var clnok2 = FindObject(0,-50,-5,100,140,OCF_CrewMember(),"Jump");	//Derhier will rein!
     clnok2 -> Enter(this());											//Rein mit dir!
     clnok2 -> SetAction("Walk");										//Und Aktion "Gehen" Setzen!
     clnok2 -> SetComDir(COMD_Stop());									//Und letztes Sprungkommando löschen
     light -> TurnOn();													//Und noch nen kurzen Lichteffekt
     light -> SetCon(100);
     LocalN("outfade",light) = 1;
     Sound("DartButton");												//Und den Sound nicht vergessen
    }
   }
  }

  if(on)											//Sind wir on?
  {
   if(GetAction() ne "Fly")							//Fliegen wir?
   {
    if(GetAction() ne "Turn")						//Drehen wir uns?
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
  if(GetAction() eq "Fly")
  {
   SetAction("Stand");
   return(1);
  }
  return(1);
}

protected func ContainedUpDouble()			//Stehenbleiben bei Doppelhoch!
{
  if(GetAction() eq "Turn") { return(0); }	//Nur wenn wir uns nicht drehen!
  SetComDir(COMD_Stop());
  SetXDir(0);
  SetYDir(0);
  return(1);
}

protected func ContainedDig(pCaller)
{
  var title;
  if(FindObject2(Find_Distance(800),Find_Func("IsStargate")) && GetDamage() < 200)
  {
	  title = FindObject2(Find_Distance(800),Find_Func("IsStargate"))->GetName();
  }
  else title = "Dart";
  pUser = pCaller;
  SetOwner(GetOwner(pCaller));
  CreateMenu(WRDR, pUser, 0, 0, title, 0, 1);
  AddMenuItem("Aussteigen","Exite",WRD1,pCaller);
  AddMenuItem("Schadensabfrage","Schaden",WRD2,Par(0));
  AddMenuItem("Motor Aus","Enginestop",WRD3,Par(0));
  AddMenuItem("Luke","Luke",WRD4,Par(0));
  if(fire == 1)
  {
   AddMenuItem("Blaster","FireSwitch",WRD5,Par(0));
  }
  if(fire == 0)
  {
   AddMenuItem("Harvester","FireSwitch",WRD6,Par(0));
  }
  if(FindObject2(Find_Container(core)))
  {
   AddMenuItem("Freilassen","Exiting",WRD7,Par(0));
  }
  if(FindObject2(Find_Distance(800),Find_Func("IsStargate")))
  {
   if(GetDamage() < 200)
   {
    AddMenuItem("Gate anwählen","DialGate",WRD8,Par(0));
   }
  }
  return(1);
}

func DialGate()
{
  CallMessageBoard(0,false,"Gatename:",GetOwner(pUser));
  return(1);
}

func InputCallback(string pGate)
{ 
  if(!FindObject2(Find_Or(Find_ID(STGT),Find_ID(SGAG),Find_ID(SGDG)),Find_Distance(800),Sort_Distance()))
  {
   Message("<c ff0000>Kein Gate in Reichweite!</c>",this());
   return(1);
  }
  else
  {
   FindObject2(Find_Or(Find_ID(STGT),Find_ID(SGAG),Find_ID(SGDG)),Find_Distance(800),Sort_Distance())->Dial(pGate);
   return(1);
  }
  return(1);
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
   PlayerMessage(GetOwner(pUser),"Harvester",this());
   fire = 1;
   Sound("DartButton");
   return(1);
  }
  if(fire == 1)
  {
   PlayerMessage(GetOwner(pUser),"Blaster",this());
   fire = 0;
   Sound("DartButton");
   return(1);
  }
  return(1);
}

func Luke()
{
  if(GetAction() eq "Stand")
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
  
  if(GetAction() eq "Open")
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
  if(GetAction() eq "Fly")
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

public func Schaden()
{
  Message("Schaden: %v|Verbleibend: %v" ,this() , GetDamage(this()) , 500-GetDamage(this()));
  return(1);
}

public func Destroy()
{
  Explode(50);
  return(1);
}

public func Exite(pCaller) 
{
  if(GetAction() eq "Fly")
  {
   if(light)
   {
    light -> TurnOn();
    light -> SetCon(100);
   }
   LocalN("outfade",light) = 1;
   var clnok;
   clnok = pUser;
   SetAction("Stand");
   Sound("DartButton");
   SetEntrance(1);
   clnok -> Exit();
   SetEntrance(0);
   if(GetDir() == 0)
   {
    clnok -> SetPosition(GetX()+40,GetY());
   }
   else
   {
    clnok -> SetPosition(GetX()-40,GetY());
   }
   SetAction("Fly");
   clnok -> SetAction("Tumble");
   clnok -> SetYDir(10000);
   return(1);
  }

  if(!open)
  {
   Luke();
   return(1);
  }

  pUser->Exit();
  pUser->SetAction("Walk");
  
  if(GetDir() == 0)
  {
   pUser->SetPosition(GetX(pUser)+30,GetY(pUser)+15);
   SetEntrance(1);
   return(1);
  }
  
  pUser->SetPosition(GetX(pUser)-30,GetY(pUser)+15);
  SetEntrance(1);
  return(1);
}

protected func ContainedUp()
{
  if(GetAction() eq "Turn") { return(0); }

  if(GetAction() S= "Fly")
   {
   if(GetComDir() == COMD_UpLeft() || GetComDir() == COMD_UpRight()) SetComDir(COMD_Up());
   if(GetComDir() == COMD_Down()) SetComDir(COMD_Up());
   if(GetComDir() == COMD_Left()) SetComDir(COMD_UpLeft());
   if(GetComDir() == COMD_DownLeft()) SetComDir(COMD_Left()); 
   if(GetComDir() == COMD_DownRight()) SetComDir(COMD_Right());
   if(GetComDir() == COMD_Right()) SetComDir(COMD_UpRight());
   if(GetComDir() == COMD_Stop()) SetComDir(COMD_Up());
   return(true);
   }
   
   if(GetAction() eq "Stand")
   {
    SetAction("Fly");
    return(1);
   }
  return(1);
}

protected func ContainedDown()
{
   if(!(GetAction() eq "Fly"))
   { 
    return(0); 
   }

   if(GetComDir() == COMD_DownLeft() ||GetComDir() == COMD_DownRight())
   {
    SetComDir(COMD_Down());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Up())
   {
    SetComDir(COMD_Stop());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Left()) 
   {
    SetComDir(COMD_DownLeft());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_UpLeft())
   {
    SetComDir(COMD_Left());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Stop())
   {
    SetComDir(COMD_Down());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_Right()) 
   {
    SetComDir(COMD_DownRight());
    SetEntrance(0);
   }
   if(GetComDir() == COMD_UpRight())
   {
    SetComDir(COMD_Right());
    SetEntrance(0);
   }
  return(1);
}

protected func ContainedRight()
{
  if(GetAction() eq "opens")  return(1);
  if(GetAction() eq "open")   return(0);
  if(GetAction() eq "close")  return(1);
  if(GetAction() eq "Turn")   return(1);
  if(GetAction() eq "Stand")  return(0);
  if(open)					  return(0);
  if(iExtra) return(0);
  
  if(alflusy == 1)
  {
   if(GetXDir() < 0)
   {
    SetCommand(this(),"None");
    SetComDir(COMD_Right());
    return(1);
   }
  }
  
  SetCommand(this(),"None");
  SetComDir(COMD_Right());
  
  if(GetDir() == DIR_Left())
  {
   SetAction("Turn");
   iExtra++;
  }
  return(1);
}

protected func ContainedLeft()
{
  if(GetAction() eq "opens")  return(1);
  if(GetAction() eq "open")   return(0);
  if(GetAction() eq "close")  return(1);
  if(GetAction() eq "Turn")   return(1);
  if(GetAction() eq "Stand")  return(0);
  if(open)					  return(0);
  if(iExtra) return(0);
  
  if(alflusy == 1)
  {
   if(GetXDir() > 0)
   {
    SetCommand(this(),"None");
    SetComDir(COMD_Left());
    return(1);
   }
  }
  
  SetComDir(COMD_Left());  
  if(GetDir() == DIR_Right())
  {
   SetAction("Turn");
   iExtra++;
  }
  return(true);
}

func Turned()
{
  if(GetDir() == DIR_Left()) SetDir(DIR_Right());
  else SetDir(DIR_Left());
  iExtra = 0;
  return(true);
}   

public func Stop() 
{
  SetComDir(COMD_Stop());
  SetYDir(0);
  SetXDir(0);
  return(true);
}

protected func ContainedRightDouble()
{
   if(!(GetAction() eq "Fly")) { return(0); }

  if(GetDir() == DIR_Right())
   {
   SetComDir(COMD_Stop());
   SetYDir(0);
   SetComDir(COMD_Right());
   }
  else
   {
   SetAction("Wenden");
   }
  return(true);
}

protected func ContainedLeftDouble()
{
   if(GetAction() eq "Tarned") { return(0); }
   if(!(GetAction() eq "Fly")) { return(0); }

  if(GetDir() == DIR_Left())
   {
   SetComDir(COMD_Stop());
   SetYDir(0);
   SetComDir(COMD_Left());
   }
  else
   {
   SetAction("Wenden");
   }
  return(true);
}

public func Starting()
{
  if(GetAction() eq "Stand")
  SetAction("Fly",GetActionTarget(0),GetActionTarget(1));
  if(GetDir() == DIR_Left()) SetComDir(COMD_UpLeft());
  if(GetDir() == DIR_Right()) SetComDir(COMD_UpRight());
  return(true);
}



func IsMachine() 		{ return(1); }

func IsBulletTarget()    { return(1); }
