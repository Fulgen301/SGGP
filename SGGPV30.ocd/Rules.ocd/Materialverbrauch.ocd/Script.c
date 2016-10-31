#strict
func Activate(int iPlayer)
{
	MessageWindow(Format("Es kann maximal <c ff0000>%d</c> Replikatoren geben! Tja...",RepliLimit),iPlayer);
	return(1);
}	

func Initialize()
{
	SetRepliMaterial(ObjectCount(REMA));
}

global func SetRepliMaterial(int iLimit)
{
	RepliHunger = iLimit;
}

local Name = "$Name$";
