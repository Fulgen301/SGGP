/*-- SG Welt --*/

#strict 2

static fowTools;
static xpositions;
static ypositions_ranges;

func Initialize()
{
  CreateGate(SGR3, SGDG, 515, 298, -1, [8, 13, 7, 3, 10, 2, 9]);
  CreateGate(SGR2, SGAG, 2007, 1570, -1, [3, 7, 13, 10, 9, 15, 11]);
  CreateGate(SGR3, SGDG, 2507, 3131, -1, [8, 9, 13, 14, 15, 12, 4]);
  CreateGate(SGR2, STGT, 347, 4151, -1, [9, 2, 6, 12, 15, 4, 8]);
  CreateGate(SGR2, SGAG, 2010, 5321, -1, [13, 10, 7, 6, 14, 8, 12]);
  CreateGate(SGR3, SGDG, 3504, 5983, -1, [9, 10, 15, 2, 3, 13, 12]);
  CreateGate(SGR4, STGT, 1600, 7005, -1, [14, 2, 8, 10, 3, 11, 9]);
  
  CreateObject(DHD_, 1514, 7000, -1);
  CreateObject(DHD_, 272, 4148, -1);
  CreateObject(DHDP, 1926, 5317, -1);
  CreateObject(DHDP, 1929, 1568, -1);
  CreateObject(DHDD, 428, 292, -1);
  CreateObject(DHDD, 3418, 5978, -1);
  CreateObject(DHDD, 2419, 3128, -1);
  Schedule("RemoveAll(TIME)", 20);
  
  
  
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
