#strict
func Activate(int iPlayer)
{
	MessageWindow("Es gibt kein Fog of war! Freie sicht f�r freie Spieler. ����h",iPlayer);
}

func Timer()
{
	var i;
	while(i < GetPlayerCount())
	{
		if(GetPlayerName(i))
		{
			SetFoW(0,i);
		}
		i++;
	}
}
	