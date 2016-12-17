/*-- Funkgerät --*/



local chnl;
local User;
local status;

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


func Activate()
{
  User = Contained();
  CreateMenu(GetID(),User,0,nil,0,0,1);
  User->AddMenuItem("Fragen","Ask",User->GetID());
  User->AddMenuItem("Antworten","Info",User->GetID());
  User->AddMenuItem("Selbst Formulieren","Output",User->GetID());
  User->AddMenuItem("Kanal","Chnll",GetID());
  return(1);
}

func Output()
{
  var form;
  form = CallMessageBoard(this, false, "Ausgeben", User->GetOwner());
}

func InputCallback(string form)
{
  var obj;
  while(obj = FindObject(GetID(),0,0,0,0,0,0,0,0,obj))
  {
   status = Format("%v",form);
   obj->Funkout(chnl,status);
  }
  return(1);
}


func Info()
{
  CreateMenu(GetID(),User,0,nil,0,0,1);
  User->AddMenuItem("Ja","Yes",GetID());
  User->AddMenuItem("Nein","No",GetID());
  User->AddMenuItem("Verstärkung","Help",GetID());
  User->AddMenuItem("Position","Pos",GetID());
  User->AddMenuItem("Personaldaten","Perso",User->GetID());
  User->AddMenuItem("Wiederholen bitte","Ret",User->GetID());
  User->Sound("Funk");
  return(1);
}

func Ask()
{
  CreateMenu(GetID(),User,0,nil,0,0,1);
  AddMenuItem("Wo bist du?","Where",GetID());
  AddMenuItem("Wer bist du?","Who",GetID());
  Sound("Funk");
  return(1);
}

func Chnll()
{
  CreateMenu(GetID(),User,0,"Kanal einstellen",0,1,1);
  User->AddMenuItem("1","SetChnl",Icon_MenuPoint,0,1);
  User->AddMenuItem("2","SetChnl",Icon_MenuPoint,0,2);
  User->AddMenuItem("3","SetChnl",Icon_MenuPoint,0,3);
  User->AddMenuItem("4","SetChnl",Icon_MenuPoint,0,4);
  User->AddMenuItem("5","SetChnl",Icon_MenuPoint,0,5);
  this->Message("Kanal: %d",chnl);
  return(1);
}

func SetChnl(trash,chnlsetted)
{
  chnl = chnlsetted;
  this->Message("Kanal: %d",chnl);
  Sound("Ding");
  return(1);
}

/* Hier wird nur der ganze Müll 
   mit den Fragen und Antworten
   Geschrieben. Hier gibts nix 
   Interessantes zu Lesen!   */

func Ret()
{
 
  Sound("Funk");
  return(1);
}

func Who()
{
 for(var obj in FindObjects(Find_ID(GetID()))
  {
   status = "Wer bist du?";
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}

func Where()
{
 for(var obj in FindObjects(Find_ID(GetID()))
  {
   status = "Wo bist du?";
   obj->Funkout(chnl,status);
  }
  Sound("Funk");
  return(1);
}

func Yes()
{
 for(var obj in FindObjects(Find_ID(GetID())))
  {
   status = "Aye-aye, Sir!";
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
