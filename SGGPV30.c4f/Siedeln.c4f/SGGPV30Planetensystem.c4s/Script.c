/*-- Neues Szenario --*/

#strict
#include SGGP

func Initialize() 
{
	_inherited();
	RemoveAll();
	RemoveAll();
	CreateObject(TACC);
	CreateObject(TKNW);
	CreateObject(CNMT);
	CreateObject(ENRG);
	CreateObject(HELP);
	Forest(0,LandscapeHeight()/3,LandscapeWidth(),LandscapeHeight()/3);
	Volcanoe(0,LandscapeHeight()/3*2,LandscapeWidth(),LandscapeHeight()/3+20);
	Mountains(0,0,LandscapeWidth(),LandscapeHeight()/3);
	MatHori("Brick",LandscapeHeight() / 3 -25,50);
	MatHori("Brick",LandscapeHeight() / 3 *2  -25,50);
	CreateObject(FXP1,LandscapeWidth()/2)->Activate(Material("Snow"),LandscapeWidth()-10,10000);
	CreateObject(FXP1,LandscapeWidth()/2,LandscapeHeight() / 3 * 2 +20)->Activate(Material("Lava"),LandscapeWidth()-10,10000);
	
	CreateGate(SGR2,STGT,1464,1261,-1,"Stargate 1");
	CreateObject(DHD_,1380,1255,-1);
	CreateGate(SGR2,STGT,1450,300,-1,"Stargate 2");
	CreateObject(DHD_,1504,250,-1);
	CreateGate(SGR2,STGT,1133,2132,-1,"Stargate 3");
	CreateObject(DHD_,1034,2119,-1);
	//
	SetSkyParallax(1, 20,20, 20,0,0,0);
	return(1);
}

func Forest(X,Y,W,H)
{
	FreeRect(X,Y,W,H);
	DrawDefMap(X,Y,W,H,"Forest");
	PlaceObjects(LOAM,20,"Earth",X,Y,W,H);
	PlaceObjects(GOLD,40,"Earth",X,Y,W,H);
	PlaceObjects(FLNT,10,"Earth",X,Y,W,H);
	PlaceObjects(ROCK,30,"Earth",X,Y,W,H);
	PlaceObjects(NAQU,12,"Earth",X,Y,W,H);
	var i;
	while(i < 30)
	{
		PlaceVegetation (TRE1, X,Y,W,H, -1);
		PlaceVegetation (TRE2, X,Y,W,H, -1);
		PlaceVegetation (TRE3, X,Y,W,H, -1);
		i++;
	}

}

func Volcanoe(X,Y,W,H)
{
	FreeRect(X,Y,W,H);
	DrawDefMap(X,Y,W,H,"Volcanoe");
	PlaceObjects(FLNT,30,"Ashes",X,Y,W,H);
	PlaceObjects(NAQU,12,"Ashes",X,Y,W,H);
	PlaceVegetation (TRB1, X,Y,W,H, -1);
	PlaceVegetation (TRB2, X,Y,W,H, -1);
	PlaceVegetation (TRB3, X,Y,W,H, -1);
	PlaceVegetation (TRB4, X,Y,W,H, -1);
	PlaceVegetation (TRB1, X,Y,W,H, -1);
	PlaceVegetation (TRB2, X,Y,W,H, -1);
	PlaceVegetation (TRB3, X,Y,W,H, -1);
	PlaceVegetation (TRB4, X,Y,W,H, -1); 
}

func Mountains(X,Y,W,H)
{
	FreeRect(X,Y,W,H);
	DrawDefMap(X,Y,W,H,"Mountains");
	PlaceObjects(LOAM,20,"Earth",X,Y,W,H);
	PlaceObjects(GOLD,40,"Earth",X,Y,W,H);
	PlaceObjects(FLNT,10,"Earth",X,Y,W,H);
	PlaceObjects(ROCK,30,"Earth",X,Y,W,H);
	PlaceObjects(BONE,10,"Earth",X,Y,W,H);
	PlaceObjects(NAQU,12,"Earth",X,Y,W,H);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
	PlaceVegetation (TRE4, X,Y,W,H, -1);
}
