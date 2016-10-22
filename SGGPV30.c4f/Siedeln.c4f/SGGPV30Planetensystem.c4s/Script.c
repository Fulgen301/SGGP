/*-- SG Welt --*/

#strict 2

static fowTools;
static xpositions;
static ypositions_ranges;

func Initialize()
{
  CreateGate(SGR3, SGDG, 515, 298, -1, "Alienworld");
  CreateGate(SGR2, SGAG, 2007, 1570, -1, "Pandora");
  CreateGate(SGR3, SGDG, 2507, 3131, -1, "Dune");
  CreateGate(SGR2, STGT, 347, 4151, -1, "Deathstar");
  CreateGate(SGR2, SGAG, 2010, 5321, -1, "Thalus");
  CreateGate(SGR3, SGDG, 3504, 5983, -1, "Lavahöhlen");
  CreateGate(SGR1, STGT, 1596, 6987, -1, "Mond");
  
  CreateObject(DHD_, 1514, 7000, -1);
  CreateObject(DHD_, 272, 4148, -1);
  CreateObject(DHDP, 1926, 5317, -1);
  CreateObject(DHDP, 1929, 1568, -1);
  CreateObject(DHDD, 428, 292, -1);
  CreateObject(DHDD, 3418, 5978, -1);
  CreateObject(DHDD, 2419, 3128, -1);
  
  
  
  return(1);
}

func InitializePlayer(int plr, int x, int y, object base, int team)
{
  var spawnpoints = [[1950, 240], [3530, 1510], [1800, 2990], [2040, 4100], [1850, 5310], [3400, 5960], [1710, 6990]];
  var startMaterial = [[FLAG, 1], [CNKT, 1]];

  SetFoW(true, plr);

  for(var i = 0; i < GetCrewCount(plr); ++i)
    SetPosition(spawnpoints[team - 1][0], spawnpoints[team - 1][1], GetCrew(plr, i));

  for(var material in startMaterial)
  {
    if(GetLength(material) == 2)
    {
      CreateObject(material[0], spawnpoints[team - 1][0], spawnpoints[team - 1][1], plr);
    }
  }
}
