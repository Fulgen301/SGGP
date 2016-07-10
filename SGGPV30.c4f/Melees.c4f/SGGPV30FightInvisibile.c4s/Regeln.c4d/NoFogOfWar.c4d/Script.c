#strict
func Activate(int iPlayer)
{
	MessageWindow("Es gibt kein Fog of war! Freie sicht für freie Spieler. Äהההh",iPlayer);
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
	