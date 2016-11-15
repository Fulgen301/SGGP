/*-- Neues Objekt --*/


local Enabled;
func Initialize() 
{
	Place(LandscapeWidth() / 2);
	Enable();
	return(1);
}

func Place(int iX)
{
	SetPosition(iX,0);
}

func Activate(int iPlayer)
{
	MessageWindow("Erzeugt eine Sperre in der Mitte der landschaft, um zu verhindern, das sich die Gegner vor der Zeit einen Besuch abstatten",iPlayer);
}

func Enable()
{
	Enabled = 1;
	Message("<c ffcc00> Gebietssperre aktiv! </c>");
}

func Timer()
{
	if(!Enabled) return();
	DrawParticleLine("MSpark", -10, 0, -10,LandscapeHeight(), 10, 100, RGBa(255,50,50,50), RGBa(255,255,50,100), -10);
	DrawParticleLine("MSpark", 10, 0, 10,LandscapeHeight(), 10, 100, RGBa(255,50,50,50), RGBa(255,255,50,100), -10);
	var pObj;
	for(pObj in FindObjects(Find_InRect(-10,-500,20,LandscapeHeight() + 1000)))
	{
		SetXDir(GetXDir(pObj) * -2,pObj);
		SetYDir(GetYDir(pObj) * -2,pObj);
	}
}

func Disable()
{
	Enabled = 0;
	Message("<c ff0000> Gebietssperre nicht aktiv! </c>");
}
local Name = "$Name$";
