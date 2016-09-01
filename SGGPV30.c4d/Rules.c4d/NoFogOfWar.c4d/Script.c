#strict 2


protected func Activate(int iPlayer)
{
	MessageWindow(GetDesc(),iPlayer);
}

protected func Timer()
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

public func IsChooseable() {return true;}