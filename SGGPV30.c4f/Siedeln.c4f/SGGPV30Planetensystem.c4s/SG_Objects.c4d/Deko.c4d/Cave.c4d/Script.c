/*-- Stippelnest --*/

#strict 2

local fBroken;
local theEvil;

func Initialize() 
{
  EkeVerifyEvilOwner();
  if (!theEvil) theEvil = FindObject(TE5B);
  if (!theEvil) theEvil = CreateObject(TE5B);
  SetOwner(GetOwner(theEvil));
  SetAction("Open");
  AddEffect("StippelSpawn",this,100,40,this);
  return true;
}

func Damage() {return Death();}

func Death()
{
  SetAction("Close");
  SetCategory(C4D_StaticBack);
  GameCallEx("OnCaveRumble",this,GetKiller());
  return true;
}

func FxStippelSpawnTimer()
{
  var theEvilOwner = GetOwner(FindObject(TE5B));
    if (GetOwner() != theEvilOwner) SetOwner(theEvilOwner);
  
  if(!fBroken)
  {
    if(!Random(3)) CreateObject(ST5B,0,0,GetOwner());
    else if(!Random(10)) CreateObject(MI5B,0,10,GetOwner());
  }
  return true;
}

func CloseCheck()
{
  if(GetPhase() < 9) Sound("Earthquake");
  if(GetPhase() == 4)
  {
    fBroken = true;
    //Stippel darin sterben...
    for (var i = 0; i < 15; i++) 
    {
      CreateParticle("EkeStippelFlesh",RandomX(-7,7),5,RandomX(-20,20),-Random(20),10+Random(50));
      if(i < 5) Sound("ST_Die*");
    }
  }
  if(GetPhase() == 9) Sound("Discharge");
  return true;
}
