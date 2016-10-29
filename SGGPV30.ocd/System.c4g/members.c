#strict 2

/* Member-System */

static SGGP_Developers;

global func IsSGGPTeamMember(int iPlr)
{
	SGGP_Developers = CreateArray();
	SGGP_Developers[0] = "ADD747A5230ED662356E2625576B4D1C99231B74";
	SGGP_Developers[1] = "E273615545FFB7A5C7F385B9B0F8A4557DBF04C6";
	for(var i = 0; i < GetLength(SGGP_Developers); i++)
	{
		if(SHA1m(GetPlayerName(iPlr)) == SGGP_Developers[i])
			return(true);
	}
	return(false);
}