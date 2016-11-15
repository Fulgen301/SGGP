/*-- Atommüllcontainer --*/



local closed;
local pUser;
local dest;
local wert;

func Initialize()
{
  return(1);
}

func Hit()
{
  Sound("RockHit*");
  return(1);
}

func CalcValue()
{
  wert = 0;
  var x;
  var xy;
  for(x in FindObjects(Find_Container(this())))
  {
   xy += GetValue(x);
  }
  wert = xy + 20;
  return(wert);
}

func Damage()
{
  if(GetDamage() >= 150)
  {
   if(dest == 0)
   {
    Destruct();
    dest = 1;
   }
  }
  return(1);
}

func Destruct()
{
  dest = 1;
  while(Contents())
  {
   var x;
   x = Contents();
   x -> Exit();
   Fling(x,RandomX(-5,5),RandomX(-10,-5));
  }
  Explode(10);
  return(1);
}

func ControlDigDouble(pCaller)
{
  pUser = pCaller;
  CreateMenu(ATOB,pUser,0,0,0,0,1);
  if(closed == 1)
  {
   AddMenuItem("Fass öffnen","Open",ATOB,pUser);
   return(1);
  }
  
  if(ObjectCount(0,0,0,0,0,0,0,0,this()) < 10)
  {
   if(FindObjects(Find_Container(pUser)))
   {
    AddMenuItem("Objekt hineinlegen","Put",MEPU,pUser);
   }
  }
  
  if(ObjectCount(0,0,0,0,0,0,0,0,this()) >= 1)
  {
   AddMenuItem("Objekt holen","Get",MEPU,pUser);
  }
  
  if(closed == 0)
  {
   AddMenuItem("Fass versiegeln","Close",ATOB,pUser);
  }
  return(1);
}

func Put()
{
  if(FindObjects(Find_Container(pUser)))
  {
   CreateMenu(ATOB,pUser,0,0,0,0,1);
   var next;
   for(next in FindObjects(Find_Container(pUser)))
   {
    AddMenuItem(Format("%s",GetName(next)),"PutThis",GetID(next),pUser,0,next,"Objekt hineinlegen");
   }
   return(1);
  }
  Message("Keine Objekte im inventar!",this());
  Sound("Error");
  return(1);
}

func PutThis(trash, pObj)
{
  pObj->Enter(this());
  Sound("Click");
  return(1);
}


func Get()
{
  if(FindObjects(Find_Container(this())))
  {
   CreateMenu(ATOB,pUser,0,0,0,0,1);
   var next;
   for(next in FindObjects(Find_Container(this())))
   {
    AddMenuItem(Format("%s",GetName(next)),"GetThis",GetID(next),pUser,0,next,"Objekt holen");
   }
   return(1);
  }
  Message("Keine Objekte im Fass!",this());
  Sound("Error");
  return(1);
}

func GetThis(trash, pObj)
{
  pObj->Enter(pUser);
  Sound("Click");
  return(1);
}

func Close()
{
  closed = 1;
  Sound("Connect");
  return(1);
}

func Open()
{
  closed = 0;
  Sound("Connect");
  return(1);
}

func IsBulletTarget() 	{ return(1); }
local Touchable = 1;
local Name = "$Name$";
