/*-- Funkgerät --*/



local chnl;
local User;
local status;
local spam;

func Initialize()
{
  chnl = 1;
  return(1);
}

func Hit()
{
  Sound("MetalHit*");
  return(1);
}

func Damage()
{
  if(GetDamage() >= 150)
  {
   Explode(5);
  }
  return(1);
}

func Check()
{
  if(spam >= 10)
  {
   Log("<c ff0000>%s hat sein Funkgerät geschrottet HAHA!</c>",GetPlayerName(GetOwner()));
   Explode(20);
  }
  spam--;
  return(1);
}

func Activate()
{
  spam++;
  User = Contained();
  CreateMenu(GetID(),User,0,0,0,0,1,0);
  AddMenuItem("Fragen","Ask",GetID(User),User);
  AddMenuItem("Antworten","Info",GetID(User),User);
  AddMenuItem("Selbst Formulieren","Output",GetID(),User);
  AddMenuItem("Kanal","Chnll",GetID(),User);
  return(1);
}

func Output()
{
  var form;
  form = CallMessageBoard(0, false, "Ausgeben", GetOwner(User));
}

func InputCallback(string form)
{
  var obj;
  var status;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = Format("%v",form);
   obj->Funkout(chnl,status);
  }
  return(1);
}


func Info()
{
  CreateMenu(GetID(),User,0,0,0,0,1,0);
  AddMenuItem("Ja","Yes",GetID(),User);
  AddMenuItem("Nein","No",GetID(),User);
  AddMenuItem("Verstärkung","Help",GetID(),User);
  AddMenuItem("Position","Pos",GetID(),User);
  AddMenuItem("Personaldaten","Perso",GetID(User),User);
  AddMenuItem("Wiederholen bitte","Ret",GetID(),User);
  Sound("Funk");
  return(1);
}

func Ask()
{
  CreateMenu(GetID(),User,0,0,0,0,1,0);
  AddMenuItem("Wo bist du?","Where",GetID(),User);
  AddMenuItem("Wer bist du?","Who",GetID(),User);
  Sound("Funk");
  return(1);
}


func Info()
{
  CreateMenu(GetID(),User,0,0,0,0,1,0);
  AddMenuItem("Verstärkung","Help",GetID(),User);
  AddMenuItem("Position","Pos",GetID(),User);
  AddMenuItem("Personaldaten","Perso",GetID(User),User);
  Sound("Funk");
  return(1);
}

func Chnll()
{
  CreateMenu(GetID(),User,0,0,"Kanal einstellen",0,1,1);
  AddMenuItem("Setzen","SetChnl",SNB1,Contained(),0,1);
  AddMenuItem("Setzen","SetChnl",SNB2,Contained(),0,2);
  AddMenuItem("Setzen","SetChnl",SNB3,Contained(),0,3);
  AddMenuItem("Setzen","SetChnl",SNB4,Contained(),0,4);
  AddMenuItem("Setzen","SetChnl",SNB5,Contained(),0,5);
  Message("Kanal: %d",this(),chnl);
  return(1);
}

func SetChnl(trash,chnlsetted)
{
  chnl = chnlsetted;
  Message("Kanal: %d",this(),chnl);
  Sound("Ding");
  return(1);
}

/* Hier wird nur der ganze Müll 
   mit den Fragen und Antworten
   Geschrieben. Hier gibts nix 
   Interessantes zu Lesen!   */

func Ret()
{
  var obj;
  var status;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = "Könntest du das wiederholen?";
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}

func Who()
{
  var obj;
  var status;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = "Wer bist du?";
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}

func Where()
{
  var obj;
  var status;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = "Wo bist du?";
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}

func Yes()
{
  var obj;
  var status;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = "Positiv";
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}

func No()
{
  var obj;
  var status;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = "Negativ";
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}


func Help()
{
  var obj;
  var status;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = "Brauche Verstärkung";
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}

func Pos()
{
  var obj;
  var status;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = Format("Hier ist meine Position:|X: %d   Y: %d",GetX(),GetY());
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}

func Perso()
{
  var obj;
  var status;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = Format("Ich bin %s|von %s",GetName(User),GetPlayerName(GetOwner(User)));
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}

/* Der Ganze Müll mit den Fragen
   und Antworten is endlich Aus.
   Jetz wirds interessant, jetz
   wird die Message ausgegeben! */


func Funkout(chnlout,status)
{
  if(chnlout == chnl)
  {
   Message("%v",this(),status);
   Sound("Funk");
  }
  return(1);
}
local Name = "Funkgerät";
local Collectible = 1;
