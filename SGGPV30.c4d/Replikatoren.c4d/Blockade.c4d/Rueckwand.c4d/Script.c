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