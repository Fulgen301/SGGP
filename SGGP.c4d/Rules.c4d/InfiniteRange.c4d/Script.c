#strict 2

protected func Construction()
{
    SetVisibility(VIS_None);
}

func Activate(int iPlayer)
{
	MessageWindow(GetDesc(),iPlayer);
	return(1);
}	
