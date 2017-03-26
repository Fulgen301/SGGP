#strict
#include GEAR
local User,Transporter,aTrans,aNames;
func Initialize() 
{
	aTrans = CreateArray(1);
	aNames = CreateArray(1);
}
func ActivateMe(object pCaller)
{
	CreateMenu(ASTR, User, 0, 0, "Asgard Teleporter Transponder",0,1);
	if(FindObject2(Find_ID(ASTE),Find_Distance(30,GetX(User)-GetX(),GetY(User)-GetY()),Sort_Distance())) AddMenuItem("Zu Transporter zuordnen", "Choose",  MEPU,User);
	var pTr;
	var i;
	for(pTr in aTrans)
	{
		if(pTr) AddMenuItem(Format("Zu %s beamen",aNames[i]), Format("Start(%d)",i),  MEPU,User);
		if(pTr) AddMenuItem(Format("%s löschen",aNames[i]), Format("Delete(%d)",i),  MEPU,User);
		i++;
	}
}

func Choose()
{
	aTrans[GetLength(aTrans)] = FindObject2(Find_ID(ASTE),Find_Distance(100,GetX(User)-GetX(),GetY(User)-GetY()),Sort_Distance());
	CallMessageBoard(0,false,"Bitte geben Sie eine passende Beschreibung ein:",GetOwner(User));
}

func InputCallback(string szText)
{
	aNames[GetLength(aNames)] = szText;
	Message("<c 00ff00>Transporter zugeordnet!",User);
}

func Start(int i)
{
	aTrans[i] -> In(User);
}

func Delete(int i)
{
	aTrans[i] = 0;
	aNames[i] = 0;
	Message("<c 00ff00>Transporterzuordnung gelöscht!</c>",User);
}

func GetGearType()	
{ 
	return 512; 
}

func IsEquipment()	
{ 
	return(true); 
}

public func ConDesc() 
{
	return("Transponder bedienen");
}

public func ConUseable() 
{
    return(true);
}

public func ConUse(object pCaller)
{
	User = pCaller;
	ActivateMe(pCaller);
	Sound("Click");
}

public func GetRace() { return SG1_Asgard; }