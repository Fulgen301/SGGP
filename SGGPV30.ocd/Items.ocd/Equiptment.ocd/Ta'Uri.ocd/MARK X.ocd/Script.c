/*-- MARK --*/



local pUser;
local timer;
local force;
local Password;
local lock;
local AskingPW;

public func AskPassword(int iUser)
{
  AskingPW=1;
  CallMessageBoard(0,false,"Passwort?",iUser);
}

public func Initialize()
{
  AskingPW=0;
  SetAction("Deactive");
  timer = 60;
  force = 20;
}

public func ControlDigDouble(object pCaller)
{
  pUser = pCaller;
  if(!Password) Menu();
  if(Password) AskPassword(GetOwner(pCaller));
}

public func Menu()
{
  CreateMenu(TAMA,pUser,0,0,0,0,1);  
  if(lock == 1)
  {
   AddMenuItem("Countdown beenden","Stop",TAMA,pUser);
   return(1);
  }
  
  AddMenuItem("Timer setzen","SetTimer",TAMA,pUser);
  AddMenuItem("Stärke setzen","SetForcer",TAMA,pUser);
  AddMenuItem("Countdown starten","Start",TAMA,pUser);
  AddMenuItem("Passwort setzen","SetPass",TAMA,pUser);
  return(1);
}

public func Stop()
{
  CreateObject(TAMA);
  FindObject(TAMA)->SetPosition(GetX(),GetY());
  LocalN("Password",FindObject(TAMA)) = LocalN("Password");
  Message("Erfolgreich abgebrochen!");
  RemoveObject();
  return(1);
}

public func Start()
{
  ScheduleCall(0,"Bom",timer*36);
  SetAction("Active");
  lock = 1;
  Message("Erfolgreich gestartet!|Explosion in: %v Sekunde/n",this(),timer);
  return(1);
}

public func Bom()
{
  if(!lock)
  {
   return(1);
  }
  var helper;
  helper = CreateObject(ROCK);
  Xplode(force,helper);
  RemoveObject();
  return(1);
}

public func SetPass()
{
  CallMessageBoard(0,false,"Passwort?",GetOwner(pUser));
}

public func SetForcer()
{
  CreateMenu(TAMA,pUser,0,0,0,0,1);
  AddMenuItem("10 Megatonnen",Format("SetForce(%d)",1),SNB1,pUser,0);
  AddMenuItem("20 Megatonnen",Format("SetForce(%d)",2),SNB2,pUser,0);
  AddMenuItem("30 Megatonnen",Format("SetForce(%d)",3),SNB3,pUser,0);
  AddMenuItem("40 Megatonnen",Format("SetForce(%d)",4),SNB4,pUser,0);
  AddMenuItem("50 Megatonnen",Format("SetForce(%d)",5),SNB5,pUser,0);
  AddMenuItem("60 Megatonnen",Format("SetForce(%d)",6),SNB6,pUser,0);
  AddMenuItem("70 Megatonnen",Format("SetForce(%d)",7),SNB7,pUser,0);
  AddMenuItem("80 Megatonnen",Format("SetForce(%d)",8),SNB8,pUser,0);
  AddMenuItem("90 Megatonnen",Format("SetForce(%d)",9),SNB9,pUser,0);
  return(1);
}

public func SetForce(int iforce)
{
  force = iforce *10;
  Message("Explosion auf: %d Megatonnen gesetzt",this(),iforce*10);
  return(1);
}


public func SetTimer()
{
  CreateMenu(TAMA,pUser,0,0,0,0,1);
  AddMenuItem("Kein Timer","SetTime",SNB0,pUser,0,1);
  AddMenuItem("10 Sekunden","SetTime",SNB1,pUser,0,10);
  AddMenuItem("20 Sekunden","SetTime",SNB2,pUser,0,20);
  AddMenuItem("30 Sekunden","SetTime",SNB3,pUser,0,30);
  AddMenuItem("40 Sekunden","SetTime",SNB4,pUser,0,40);
  AddMenuItem("50 Sekunden","SetTime",SNB5,pUser,0,50);
  AddMenuItem("60 Sekunden","SetTime",SNB6,pUser,0,60);
  AddMenuItem("70 Sekunden","SetTime",SNB7,pUser,0,70);
  AddMenuItem("80 Sekunden","SetTime",SNB8,pUser,0,80);
  AddMenuItem("90 Sekunden","SetTime",SNB9,pUser,0,90);
  return(1);
}

public func SetTime()
{
  timer = Par(1);
  Message("Timer auf: %v Sekunden",this(),Par(1));
  return(1);
}

public func SetPass()
{
  CallMessageBoard(0,false,"Passwort?",GetOwner(pUser));
}

func InputCallback(string szPass)
{
  if(AskingPW)
  {
   AskingPW=0;
   if(Password eq szPass) Menu();
   return();
  }
  Password = szPass;
}

func IsMachine()			{ return(1); }
func IsBulletTarget()		{ return(1); }
local Touchable = 1;
local ActMap = {
Active = {
Prototype = Action,
Name = "Active",
Length = 2,
Delay = 18,
X = 0,
Y = 0,
Wdt = 27,
Hgt = 10,
NextAction = "Active",
},
Deactive = {
Prototype = Action,
Name = "Deactive",
Length = 0,
Delay = 1,
X = 0,
Y = 10,
Wdt = 27,
Hgt = 10,
NextAction = "Deactive",
},  };
local Name = "$Name$";
