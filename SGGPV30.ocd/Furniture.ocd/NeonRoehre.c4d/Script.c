#strict

func Initialize()
{
  An();
  return(1);
}

func Damage()
{
  if(SEqual(GetAction(),"An")) if(LessThan(50,GetDamage()))
  {
    SetAction("FlackerAn");
    if(!Local(0)) ObjectSetAction(Local(0)=CreateObject(LJ3V,-20,16),"Neon");
  }
  return(1);
}
func Flacker()
{
  if(Not(Random(15))) And(CastObjects(SU3V,Sum(1,Random(1)),Sum(5,Random(15)),Sum(-14,Random(28)),Sum(1,Random(2))),Sound("Spark*"));
  if(Not(Random(2))) return(0);
  if(Random(6)) return(ObjectSetAction(Local(0),"Neon")&&SetAction("FlackerAn"));
  if(Random(6)) return(ObjectSetAction(Local(0),"Aus")&&SetAction("FlackerAus"));
  return(1);
}

func An()
{
  if(Local(0)) return(1);
  SetAction("An");
  ObjectSetAction(Local(0)=CreateObject(LJ3V,-20,16),"Neon");
  return(1);
}
func Aus()
{
  SetAction("Aus");
  if(Local(0)) RemoveObject(Local(0));
  return(1);
}
local ActMap = {
An = {
Prototype = Action,
Name = "An",
Delay = 500,
Length = 1,
X = 0,
Y = 0,
Wdt = 28,
Hgt = 4,
NextAction = "An",
},
FlackerAn = {
Prototype = Action,
Name = "FlackerAn",
Delay = 5,
Length = 1,
X = 0,
Y = 0,
Wdt = 28,
Hgt = 4,
EndCall = "Flacker",
NextAction = "FlackerAn",
},
Aus = {
Prototype = Action,
Name = "Aus",
Delay = 500,
Length = 1,
X = 28,
Y = 0,
Wdt = 28,
Hgt = 4,
NextAction = "Aus",
},
FlackerAus = {
Prototype = Action,
Name = "FlackerAus",
Delay = 5,
Length = 1,
X = 28,
Y = 0,
Wdt = 28,
Hgt = 4,
EndCall = "Flacker",
NextAction = "FlackerAus",
},  };
local Name = "Neonröhre";
