/*-- Nachrichtenzeiger --*/

#strict

local text,icon,color,alpha;

func Initialize()
{
  return(1);
}

func GetText()
{
  return(text);
}

func GetIcon()
{
  return(icon);
}

func SetVisPlayer(iPlr)
{
  SetOwner(iPlr);
  SetVisibility (VIS_Owner);
}

func SetVisTeam(iPlr)
{
  SetOwner(iPlr);
  SetVisibility (VIS_Allies);
}

func SetVisAll()
{
  SetVisibility (VIS_All);
}

func Attach(pObj)
{
  if(pObj)
    SetAction("Attach",pObj);
  else
    SetAction("ActIdle",pObj);
}

func FloatFade(szText,dwColor,bNoSound)
{
  if(!dwColor)
    dwColor = RGB(255,255,255);
    
  if(!bNoSound)
    PlaySound();

  text = szText;
  icon = 0;
  color = dwColor;
  alpha = 255;

  FloatFadeInit();
  FadeOut_Float();
}

func Float(szText,dwColor,bNoSound)
{
  if(!dwColor)
    dwColor = RGB(255,255,255);
    
  if(!bNoSound)
    PlaySound();

  text = szText;
  icon = 0;
  color = dwColor;
  alpha = 255;
  
  FloatInit();
}

func Event(szText,idIcon,dwColor,bNoSound)
{
  if(!dwColor)
    dwColor = RGB(255,255,255);
    
  if(!bNoSound)
    PlaySound();

  text = szText;
  icon = idIcon;
  color = dwColor;
  alpha = 255;
  
  EventInit();
  FadeOut();
}

func Exercise(szText,idIcon,dwColor,bNoSound)
{
  if(!dwColor)
    dwColor = RGB(255,255,255);
    
  if(!bNoSound)
    PlaySound();
    
  text = szText;
  icon = idIcon;
  color = dwColor;
  alpha = 255;
  
  ExerciseInit();
}

func SetParallax(bParallax)
{
  if(bParallax)
  {
    Local(0) = 0;
    Local(1) = 0;
  }
  else
  {
    Local(0) = 100;
    Local(1) = 100;
  }
}

/* FloatFade-Funktionen */

protected func FloatFadeInit()
{
  if(GetOwner() == NO_OWNER)
    SetVisAll();
  else
    SetVisibility(VIS_Owner());

  SetParallax(false);

  SetAction("Fade");
  return(1);
}

/* Float-Funktionen */

protected func FloatInit()
{
  if(GetOwner() == NO_OWNER)
    SetVisAll();
  else
    SetVisibility(VIS_Owner());

  SetParallax(false);

  SetAction("ActIdle");

  Message ("@<c %x>%s</c>",this(),SetRGBaValue(color,alpha),text);

  return(1);
}

/* Exercise-Funktionen */

protected func ExerciseInit()
{
  SetVisibility(VIS_Owner());
  SetParallax(true);

  SetAction("Exercise");

  SortByPos();

  Message ("@<c %x>%s</c> <c %x>{{%i}}</c>",this(),SetRGBaValue(color,alpha),text,RGBa(255,255,255,alpha),icon);

  return(1);
}

protected func SortByPos()
{
  var aSymbols = FindObjects (Find_Owner(GetOwner()),Find_Action ("Exercise"),Find_ID (GetID()));

  for(var i = 0;i < GetLength(aSymbols);i++)
  {
    SetPosition(-IconSize(),80+i*IconSize(),aSymbols[i]);

    if(i > MaxInfos())
      aSymbols[i]->Remove();
  }
}

/* Event-Funktionen */

protected func EventInit()
{
  SetVisibility(VIS_Owner());
  SetParallax(true);

  SetAction("Event");
  SortByActTime();
  return(1);
}

private func PlaySound()
{
  Sound("new_message",1,0,100,GetOwner()+1);
  return(1);
}

private func SortByActTime()
{
  var aSymbols = FindObjects (Find_Owner(GetOwner()),Find_Action ("Event"),Find_ID (GetID()));
  var temp;

  while(!Sorted(aSymbols))
  {
    for(var i = 0;i < GetLength(aSymbols);i++)
    {
      if(i == 0)
        continue;

      if(GetActTime(aSymbols[i]) < GetActTime(aSymbols[i-1]))
      {
        temp = aSymbols[i];
        aSymbols[i] = aSymbols[i-1];
        aSymbols[i-1] = temp;
      }
    }
  }

  for(var i = 0;i < GetLength(aSymbols);i++)
  {
    //Log("%d",GetActTime(aSymbols[i]))//Debug

    SetPosition(IconSize(),80+i*IconSize(),aSymbols[i]);

    if(i > MaxInfos())
      aSymbols[i]->Remove();
  }

}

private func Sorted(&aSymbols)
{
  if(GetLength(aSymbols) == 1)
    return(true);

  for(var i = 0;i < GetLength(aSymbols);i++)
  {
    if(i == 0)
      continue;

    if(GetActTime(aSymbols[i]) < GetActTime(aSymbols[i-1]))
    {
      return(false);
    }
  }
  return(true);
}

public func Remove()
{
  Message ("",this());//zur Sicherheit
  return(RemoveObject());
}

private func Destruction()//*hack*
{
  var tmp = CreateObject(ROCK,0,AbsY(-10));
  Schedule (Format("UpdateMessage4K(%d)",GetOwner()),2,0,tmp);
  Schedule ("RemoveObject()",4,0,tmp);
}

public func Update()
{
  if(GetAction() eq "Event")
  {
    return(SortByActTime());
  }

  if(GetAction() eq "Exercise")
  {
    return(SortByPos());
  }
}

/* Action-Call */

private func FadeOut()
{
  // ausblenden
  alpha = 255-(GetActTime()/5);

  // zum Schluss löschen
  if (alpha <= 0)
    return(Remove());

  Message ("@<c %x>{{%i}}</c> <c %x>%s</c>",this(),RGBa(255,255,255,alpha),icon,SetRGBaValue(color,alpha),text);
  //CustomMessage(string szText, pObj, GetOwner(this()), 0, 0, 0);
  return(1);
}

private func FadeOut_Float()
{
  // ausblenden
  alpha = 255-(GetActTime()/5);

  // zum Schluss löschen
  if (alpha <= 0)
    return(Remove());

  Message ("@<c %x>%s</c>",this(),SetRGBaValue(color,alpha),text);

  return(1);
}

/* Interne Konstanten */

public func MaxInfos(){return(12);}
public func IconSize(){return(35);}//a*a ... also wird angenommen das das Icon quadratisch ist

/* Erkennungsmerkmal */

public func IsEventInfo(){return(1);}//für eventuelle andere Dinge :O
public func IsHUD(){return(1);}



/* Globale Funktionen */

global func EventInfo4K(iPlayer,szText,idIcon,dwColor,bNoSound)
{
  if(iPlayer == NO_OWNER)
  {
    var aMessages = CreateArray();
    for(var i = GetPlayerCount();i > 0;i--)
    {
      aMessages[i-1] = CreateObject(MS4K,0,0,i-1);
      aMessages[i-1]->Event(szText,idIcon,dwColor,bNoSound);
    }
    return(aMessages);
  }
  var message = CreateObject(MS4K,0,0,iPlayer);
  message->Event(szText,idIcon,dwColor,bNoSound);
  return(message);
}

global func Exercise4K(iPlayer,szText,idIcon,dwColor,bNoSound)
{
  if(iPlayer == NO_OWNER)
  {
    var aMessages = CreateArray();
    for(var i = GetPlayerCount();i > 0;i--)
    {
      aMessages[i-1] = CreateObject(MS4K,0,0,i-1);
      aMessages[i-1]->Exercise(szText,idIcon,dwColor,bNoSound);
    }
    return(aMessages);
  }
  
  var message = CreateObject(MS4K,0,0,iPlayer);
  message->Exercise(szText,idIcon,dwColor,bNoSound);
  return(message);
}

global func FreeMessage4K(iPlayer,szText,dwColor,iX,iY,bFade,bNoSound)
{
  var message = CreateObject(MS4K,iX,iY,iPlayer);
  if(bFade)
    message->FloatFade(szText,dwColor,bNoSound);
  else
    message->Float(szText,dwColor,bNoSound);
  return(message);
}

global func GetEventInfo4K(iPlr,idIcon,szText)
{
  var a = FindObjects(Find_Owner(iPlr),Find_ID(MS4K),Find_Action("Event"));
  for(var obj in a)
  {
    if((obj->GetIcon() == idIcon)||(obj->GetText() eq szText))
      return(obj);
  }
  return(0);
}

global func GetExercise4K(iPlr,idIcon,szText,bNoSound)
{
  var a = FindObjects(Find_Owner(iPlr),Find_ID(MS4K),Find_Action("Exercise"));
  for(var obj in a)
  {
    if((obj->GetIcon() == idIcon)||(obj->GetText() eq szText))
      return(obj);
  }
  return(0);
}

global func UpdateMessage4K(iPlr)
{
  for(var obj in FindObjects(Find_Owner(iPlr),Find_ID(MS4K)))
  {
    obj->Update();
  } 
}