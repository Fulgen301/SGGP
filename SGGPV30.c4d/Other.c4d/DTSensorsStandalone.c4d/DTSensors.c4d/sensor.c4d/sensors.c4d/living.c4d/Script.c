/*-- Living-Sensor --*/

#strict
#include SN4K

local living;
local distance;

func Initialize()
{
  _inherited();
  
  /*
    Die einzelnen Stadien.
    Alle Stadien können gleichzeitig aktiv sein und sind immer 0 oder 1!
  */
  AddState("$ENEMYS$"); //0 <- Kennnummer.
  AddState("$ALLIED$"); //1
  AddState("$ANIMALS$");//2
  living = 0;
  distance = 50;
}

func Timer()
{
	Reset();
	living = FindObject2(Find_Distance (distance),Find_OCF (OCF_Alive));
	if(living)
	{
		if(GetOwner(living)==-1)
    {
      /*
        Status setzen.
        SetState(state,<Kennnummer>,<Wert>); (Wert kann nur 1 oder 0 sein.)
      */
			SetState(state,2,1);//Aha! Ein Tier(zumindest ein besitzerloses Wesen)!
    }
		else
		{
			if(Hostile (GetOwner(this()),GetOwner(living)))	
				SetState(state,0,1);//Der Feind naht!
			else
				SetState(state,1,1);//Aber ein Freund!
		}
	}
  
  /*
    Aktionen auslösen.
  */
	TriggerActions();
}

func Reset()//Hilfsfunktion für den Timer.
{
	SetState(state,0,2);//Kein Feind!
	SetState(state,1,2);//Kein Freund!
	SetState(state,2,2);//Kein Tier!
}

public func GetAdditionalInfo()//Spezialinformationen für Sensor-Ziele.
{
	return(living);
}
