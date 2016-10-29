#strict
#appendto CLNK

func ContextWaffen(pCaller) 
{
	[Waffen|Image=ROGN]
  	Weapons(pCaller);
  	return(1);
}

func ContextRustung(pCaller) 
{
	[Ausrüstung|Image=HARM]
  	Rustung(pCaller);
  	return(1);
}

func ContextSonstige(pCaller) 
{
	[Sonstige|Image=HEGR]
  	Sonstige(pCaller);
  	return(1);
}

func Weapons(pCaller)
{
	var id;
	var aId;
	aId = CreateArray(14);
	aId = [ROGN,ZATN,WRST,P90_,STBW,BZWP,MEZL,ENWP,FTWP,GLWP,MPWP,GGWP,PIWP,PGWP];
	CreateMenu(ROGN,pCaller,pCaller,C4MN_Extra_Value,0,0,0,1); 
 	for(id in aId)
	{
		if(GetValue(0,id) <= GetWealth(GetOwner()) && id != 0) 
		AddMenuItem(Format("<c ffcc00>%3d$</c> %s",GetValue(0,id),GetName(0,id)),Format("Cont(%i,%d,%d)",id,GetValue(0,id),ObjectNumber(pCaller)),id,pCaller,0,0,GetDesc(0,id));
	}
}

func Rustung(pCaller)
{

	var id;
	var aId;
	aId = CreateArray(10);
	aId = [AIRT,HARM,FLSH,JTPK,HSHD,NANO,GDO_,TALP,TAFU,LZD_];
	CreateMenu(ROGN,pCaller,pCaller,C4MN_Extra_Value,0,0,0,1); 
 	for(id in aId)
	{
		if(GetValue(0,id) <= GetWealth(GetOwner()) && id != 0)
		AddMenuItem(Format("<c ffcc00>%3d$</c> %s",GetValue(0,id),GetName(0,id)),Format("Cont(%i,%d,%d)",id,GetValue(0,id),ObjectNumber(pCaller)),id,pCaller,0,0,GetDesc(0,id));
	}
}

func Sonstige(pCaller)
{

	var id;
	var aId;
	aId = CreateArray(10);
	aId = [PUD_,WRDR,GOBE,TACM,HEGR,WRGR,KRFL,KLAS,KSLM,MINE,LMIN,AIRS];
	CreateMenu(ROGN,pCaller,pCaller,C4MN_Extra_Value,0,0,0,1); 
 	for(id in aId)
	{
		if(GetValue(0,id) <= GetWealth(GetOwner()) && id != 0)
		AddMenuItem(Format("<c ffcc00>%3d$</c> %s",GetValue(0,id),GetName(0,id)),Format("Cont(%i,%d,%d)",id,GetValue(0,id),ObjectNumber(pCaller)),id,pCaller,0,0,GetDesc(0,id));
	}
}

func Cont(id idDef,int iValue,int pCaller)
{
	if(GetWealth(GetOwner()) >= GetValue(0,idDef))
	{ 
		CreateContents(idDef,Object(pCaller));
		DoWealth(GetOwner(Object(pCaller)),-iValue);
	}
}