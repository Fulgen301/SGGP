/*-- SGGP --*/

#strict 2

static const SGGP_Version = 30;

protected func InitializePlayer(int iPlr)
{
  	var version = GetPlrExtraData(iPlr, "SGGP_Version");
	if(version != SGGP_Version)
	{
		SetPlrExtraData(iPlr, "SGGP_Version", SGGP_Version);
	}
	
	var points = BoundBy(GetPlrExtraData(iPlr, "SGGP_Points"), 0, 0x7FFFFFFF);
	if(!points)
	{
		SetPlrExtraData(iPlr, "SGGP_Points", 0);
	}
}

protected func Initialize()
{
	if(!FindObject(HELP))
		CreateObject(HELP);
	return(1);
}
