/*-- Naquadah Generator --*/

#strict

local produce;
local heat;
local modul;
local temp;
local key;
local info;

public func Initialize() 
{
  produce = 5;		//Soviel strom produziert der Generator (von 1 bis 10) ab 5 gibt es Hitzeentwicklung!
  heat = 0;			//Dashier ist die anfangshitze. Sie wird sowiso sofort neu gesetzt!
  modul = 0;		//Die angabe für den Kühler, der den Reaktor doppeltsoschnell kühlen soll!
  info = 1;			//Der Infotext soll am anfang sofort ausgegeben werden!
  key = 0;			//Das Modul, damit der Reaktor funzt!

  SetAction("Aus");	//Damit der Reaktor nicht gleich auf vollen turen läuft, wenn er erstellt wird!
  return(1);
}

public func SetProduce()//Damit wird die Produktivität vom Laptop aus gesetzt!
{
  produce = LocalN("gen",FindObject(TALP,-15,-15,30,30));
  Message("Produktionswert wurde auf %v gestellt!",this(),LocalN("gen",FindObject(TALP,-15,-15,30,30)));
  Sound("Connect");
  return(1);
}

public func InfoSwitch()	//Eine Funktion um den Hilfstext ein/aus zu blenden!
{
  Sound("Connect");
  if(info)
  {
   info = 0;
  }
  else
  {
   info = 1;
  }
  return(1);
}

public func Key()	//Die funktion zum ein bzw. ausbauen des Schlüsselteils!
{
  if(key == 1)
  {
   key = 0;
   Message("Schlüsselteil aktiviert!",this());
   Sound("Connect");
   return(1);
  }
  
  if(modul == 0)
  {
   key = 1;
   Message("Schlüsselteil deaktiviert!",this());
   Sound("Connect");
   return(1);
  }
  return(1);
}

public func Mudul()	//Die funktion zum ein bzw. ausbauen des Kühlagregates!
{
  if(modul == 1)
  {
   modul = 0;
   Message("Kühler wurde ausgebaut!",this());
   Sound("Connect");
   return(1);
  }
  
  if(modul == 0)
  {
   modul = 1;
   Message("Kühler wurde eingebaut!",this());
   Sound("Connect");
   return(1);
  }
  return(1);
}

public func DoAction()	//Wird benötigt, damit der Reaktor eingeschaltet werden kann!
{
  if(produce == 1)
  {
   SetAction("Offen1");
   return(1);
  }

  if(produce == 2)
  {
   SetAction("Offen2");
   return(1);
  }

  if(produce == 3)
  {
   SetAction("Offen3");
   return(1);
  }

  if(produce == 4)
  {
   SetAction("Offen4");
   return(1);
  }

  if(produce == 5)
  {
   SetAction("Offen5");
   return(1);
  }

  if(produce == 6)
  {
   SetAction("Offen6");
   return(1);
  }

  if(produce == 7)
  {
   SetAction("Offen7");
   return(1);
  }

  if(produce == 8)
  {
   SetAction("Offen8");
   return(1);
  }

  if(produce == 9)
  {
   SetAction("Offen9");
   return(1);
  }

  if(produce == 10)
  {
   SetAction("Offen10");
   return(1);
  }
}

public func Heat()	//Steuert die Hitzeentwicklung auf den verschiedenen betriebsstufen!
{
  if(produce == 6)
  {
   heat ++;
   return(1);
  }

  if(produce == 7)
  {
   heat ++;
   heat ++;
   return(1);
  }

  if(produce == 8)
  {
   heat ++;
   heat ++;
   heat ++;
   return(1);
  }

  if(produce == 9)
  {
   heat ++;
   heat ++;
   heat ++;
   heat ++;
   return(1);
  }

  if(produce == 10)
  {
   heat ++;
   heat ++;
   heat ++;
   heat ++;
   heat ++;
   return(1);
  }
  return(1);
}

public func Cool()	//Steuert sowohl die Kälte als auch die Überlastungsfunktion des Reaktors!
{
  if(GetDamage(this()) <= 99)
  {
   if(GetAction() eq "Kaputt")
   {
    SetAction("Aus");
   }
  }

  temp = heat/100 + GetClimate();

  if(temp >= 100)
  {
   if(GetMaterial(0,0) == Material("Oil"))
   {
    CreateObject(FLAM);
   }
  }

  if(temp >= 200)
  {
   Call("Abex");
  }

  if(heat >= 1)
  {
   if(GetMaterial(0,0) == Material("Water"))
   {
    heat --;
    heat --;
    heat --;
    heat --;
    heat --;
    heat --;
    heat --;
    heat --;
    heat --;
   }

   if(modul == 1)
   {
    heat --;
   }

   heat --;

   if(!Contained())
   {
    if(info)
    {
     Message("%v°C",this(),heat/100 +GetClimate() );
    }
   }
  }

  //	Bis hier geht die Hitzesteuerung!

  if(GetAction() eq "Zu")
  {
   return(1);
  }

  if(GetAction() eq "Aus")
  {
   return(1);
  }

  if(GetAction() eq "Kaputt")
  {
   EMPShockEffect(5);
   return(1);
  }

  Message("%v°C",this(),heat/100 +GetClimate() );
  return(1);
}



public func EMPShock()		//Jaja, der gute alte EMP Impuls kann schonmal den Reaktor zerstören!
{
  EMPShockEffect(100);
  DoDamage(10);
  return(1);
}

private func Damage()		//wir wollen doch informiert werden, wie stark der generator beschädigt ist!
{
  if(GetDamage(this()) >= 100)
  {
   SetAction("Kaputt");
  }

  if(GetDamage(this()) >= 200)
  {
   Explode(20);
  }
  return(1);
}

private func Abex()
{
  var helpr;
  helpr = CreateObject(ROCK);
  Xplode(40,helpr);
  RemoveObject();
  return(1);
}

private func Hit()		//N tolles geräusch, wenn der Reaktor auf dem Boden auftrifft!
{
  Sound("RockHit*");
  return(1);
}

public func ControlUpDouble()	//Der Reaktor ist einsammelbar ^^, aber nur wenn er abgeschaltet ist!
{

  if(GetAction(this()) eq "Zu")
  {
   Enter(Par(0));
   return(1);
  }

  if(GetAction(this()) eq "Aus")
  {
   Enter(Par(0));
   return(1);
  }

  if(GetAction(this()) eq "Kaputt")
  {
   Enter(Par(0));
   return(1);
  }

  Sound("Error",this());
  Message("Erst Generator abschalten!",this());
  return(1);
}

public func ControlDigDouble()	//Ein und Ausschalten des Reaktors wird hier gestäuert!
{
  if(key == 1)
  {
   Message("Der Generator ist blockiert!|Ich kann ihn nicht bedienen!",this());
   Sound("Error");
   return(1);
  }

  if(Contained())
  {
   Message("Ich sollte den Generator erst ablegen!",Contained());
   return(1);
  }

  if(GetAction(this()) eq "Kaputt")
  {
   Sound("Error",this());
   Message("Der Generator wurde zerstört, und muss repariert werden!",this());
   return(1);
  }

  if(GetAction(this()) eq "Auf")
  {
   SetAction("Zu");
   return(1);
  }

  if(GetAction(this()) eq "Aus")
  {
   SetAction("Auf");
   return(1);
  }

  if(GetAction(this()) eq "Zu")
  {
   SetAction("Auf");
   return(1);
  }

  SetAction("Zu");
  return(1);
}

func IsMachine()		{ return(1); }
func IsBulletTarget()		{ return(1); }
