#strict
#include SGGP

func Initialize() 
{
	_inherited();
	CreateGate(SGR2, STGT, 4466, 610, NO_OWNER);
	CreateGate(SGR2, STGT, 1471, 460, NO_OWNER);
   	ScriptGo(1);
   	RemoveAll(MANC);
   	RemoveAll(REBO);
   	return(1);
}

func Script1()
{
	var i;
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			DoWealth(i,2);
		}
		i++;
	}
	Sound("UnCash");
}

func Script60()
{
	goto(1);
}

