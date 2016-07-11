/*-- Globale Funktionen --*/

#strict 2

global func CreateObjects(id ID, int x, int y, int owner, int amount)
{
	var i = 0;
	while(i < amount)
	{
		CreateObject(ID, x, y, owner);
		i++;
	}
	return(amount);
}

/*Experimentell*/

global func GetPlayerPoints(int iPlr)
{	
	var spoints = BoundBy(GetPlrExtraData(iPlr, "SGGP_Points"), 0, 0x7FFFFFFF);
	return(spoints);
}

global func SetPlayerPoints(int iPlr, int iValue)
{
	SetPlrExtraData(iPlr, "SGGP_Points", iValue);
	return(1);
}

/* Member-System */

static SGGP_Developers;

global func IsSGGPTeamMember(int iPlr)
{
	SGGP_Developers = CreateArray();
	SGGP_Developers[0] = "39A010A2D3738FF9E78699FDF50EC38D7BE9BD79";
//	SGGP_Developers[1] = "";
	for(var i = 0; i < GetLength(SGGP_Developers); i++)
	{
		if(SHA1m(GetPlayerName(iPlr)) == SGGP_Developers[i])
			return(true);
	}
	return(false);
}


/* Compute a hash of string (by Sven2) */

global func SHA1m(string s)
{
  var h0 = 0x67452301,
      h1 = 0xEFCDAB89,
      h2 = 0x98BADCFE,
      h3 = 0x10325476,
      h4 = 0xC3D2E1F0;

  var sal = ((GetLength(s)+8)/64+1)*16;
  var sa = CreateArray(sal), sat = CreateArray(80);

  var i,j,k,l=GetLength(s),a,b,c,d,e,f,g;

  for (i=0; i<l; ++i) sa[i/4] |= (GetChar(s,i) << (8*(3-i%4)));
  sa[i/4] |= (0x80 << (8*(3-i%4)));
  sa[sal-1]=l*8;

  i=0;
  while (i<sal)
  {
    for (j=0;j<16;++j) sat[j]=CastInt(sa[i+j]); //C4Script erfindet C4IDs...
    for (;j<80;++j)
    {
      k = sat[j-3]^sat[j-8]^sat[j-14]^sat[j-16];
      sat[j]=((k&0x7fffffff)<<1)|(k<0);
    }
    a=h0; b=h1; c=h2; d=h3; e=h4;
    for (j=0;j<80;++j)
    {
      if (j<20)
      {
        f = (b&c)|((~b)&d);
        k = 0x5A827999;
      }
      else if (j<40)
      {
        f = b^c^d;
        k = 0x6ED9EBA1;
      }
      else if (j<60)
      {
        f = (b&c)|(b&d)|(c&d);
        k = 0x8F1BBCDC;
      }
      else
      {
        f = b^c^d;
        k = 0xCA62C1D6;
      }
      g = ((a&0x7fffffff)<<5)|((a<0)*0x10)|((a&0x78000000)>>27);
      g += e+f+k+sat[j];
      e = d;
      d = c;
      c = ((b&0x7fffffff)<<30)|((b<0)*0x20000000)|((b&0x7ffffffc)>>2);
      b = a;
      a = g;
    }
    h0+=a; h1+=b; h2+=c; h3+=d; h4+=e;
    i+=16;
  }

  //return [h0, h1, h2, h3, h4];
  return Format("%08X%08X%08X%08X%08X",h0,h1,h2,h3,h4);
}

global func GetIDsByName(string name, int category) // WARNING: desyncs between clients with different languages
{
	var i, id, ret = [];
	while(id = GetDefinition(i++, category))
	{
		if(GetName(0, id) == name)
		{
			ret[GetLength(ret)] = id;
		}
	}
	return ret;
}
