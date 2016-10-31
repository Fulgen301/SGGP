#strict
func Activate(int iPlayer)
{
	MessageWindow(Format("Es kann maximal <c ff0000>%d</c> Replikatoren geben! Tja...",RepliLimit),iPlayer);
	return(1);
}	

func Initialize()
{
	SetRepliLimit(ObjectCount(RERE) * 10 +10);
}

global func SetRepliLimit(int iLimit)
{
	RepliLimit = iLimit;
}

local Name = "$Name$";
