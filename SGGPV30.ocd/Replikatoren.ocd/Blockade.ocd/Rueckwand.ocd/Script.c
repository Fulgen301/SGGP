#strict
func Initialize()
{
	if(GetAction() eq "2")FreeRect(GetX()-45,GetY()-15,330,30);
	if(GetAction() eq "1")FreeRect(GetX()-15,GetY()-15,270,30);
}

func CheckBlock()
{
	if(!FindObject2(Find_ID(REBO),Find_InRect(-45,-15,330,30))) RemoveObject();
}

func IsRepli()
{
	return(true);
}
local ActMap = {

1 = {

Prototype = Action,

Name = "1",

Length = 1,

Delay = 1,

X = 0,

Y = 32,

Wdt = 330,

Hgt = 30,

NextAction = "Hold",

StartCall = "Initialize",

},

2 = {

Prototype = Action,

Name = "2",

Length = 1,

Delay = 1,

X = 0,

Y = 0,

Wdt = 330,

Hgt = 30,

NextAction = "Hold",

StartCall = "Initialize",

},  };
local Name = "$Name$";
