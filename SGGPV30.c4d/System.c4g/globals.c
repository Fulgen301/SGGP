/*-- Globale Funktionen --*/

#strict 2

static EXTENDED_MODE;

global func CreateObjects(id ID, int x, int y, int owner, int amount)
{
	var array = CreateArray(amount);
	for(var i = 0; i < amount; i++)
	{
		array[i] = CreateObject(ID, x, y, owner);
	}
	return array;
}

global func RemoveObjects(array aObjects, bool fContents)
{
	if(!aObjects || GetType(aObjects) != C4V_Array) return false;
	for(obj in aObjects)
	{
		if(obj) RemoveObject(obj, fContents);
	}
	return true;
}


/* Compute a hash of string (by Sven2) */
/** SHA1m
	
*/

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

/** GetIDsByName
	@par name The name.
	@par category The category of the ids.
	@author DerTod
*/

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

global func GivePlrAllKnowledge(int iPlr)
{
	var i, j, Def;
	while(Def = GetDefinition(i++,C4D_Magic))
	{
		SetPlrMagic(iPlr, Def);
	}
	
	while(Def = GetDefinition(j++,C4D_Structure))
	{
		if(GetDefCoreVal("Construction","DefCore",Def))
		{
			SetPlrKnowledge(iPlr, Def);
		}
	}
		
	return i + j;
}

/** ParseInt
	@author DerTod
*/

global func ParseInt(string int)
{
	if(GetLength(int) == 0)
	{
		return "";
	}
	var ret = 0, neg = false;
	for(var i = 0; i < GetLength(int); ++i)
	{
		var c = GetChar(int, i);
		if(i == 0)
		{
			if(c == 45) // "-"
			{
				neg = true;
				continue;
			}
			else if(c == 43) // "+"
			{
				continue;
			}
		}
		c -= 48; // "0" == 48
		if(c < 0 || c > 9)
		{
			return "";
		}
		ret *= 10;
		ret += c;
	}
	return ret * (1 - (2 * neg));
}

/** Assert
*/

global func assert(string sz)
{
	var result = eval(sz);
	if(!result)
	{
		return FatalError(Format("AssertionError: %s", sz));
	}
}

/** GetIndexOf2
	@author DerTod
	@par val value to search in arr (by value not by pointer as in GetIndexOf)
	@par arr array where to search in
*/

global func GetIndexOf2(val, array arr) // Because GetIndexOf doesn't find Format("%c", GetChar("a", 0)) in ["a"]
{
	var i = 0;
	for(var value in arr)
	{
		if(val == value) return i;
		++i;
	}
	return -1;
}

/** FormatN
	@author DerTod
	@par format format specification
	@par placeholders Either the order of supplied items' placeholders' names or pairs of name and item
	@par items 0 or list of items to be substituted for the placeholders in the same order as placeholders
*/

global func FormatN(string format, array placeholders, array items)
{
	if(!items && GetType(placeholders[0]) == C4V_Array)
	{
		items = CreateArray(GetLength(placeholders));
		for(var i = 0; i < GetLength(placeholders); ++i)
		{
			items[i] = placeholders[i][1];
			placeholders[i] = placeholders[i][0];
		}
	}

	var ret = "";

	var inPlaceholder = 0;
	var placeholderType = "";
	var placeholderPart = "";

	for(var i = 0; i < GetLength(format); ++i)
	{
		var c = GetChar(format, i);
		if(c == 37) // %
		{
			if(inPlaceholder == 0)
			{
				inPlaceholder = 1;
			}
			else if(inPlaceholder == 1)
			{
				if(c == 37 && GetLength(placeholderType) == 0) // %
				{
					ret = Format("%s%%", ret);
					inPlaceholder = 0;
				}
				else
				{
					inPlaceholder = 2;
				}
			}
			else if(inPlaceholder == 2)
			{
				var index = GetIndexOf2(placeholderPart, placeholders);
				if(index == -1)
				{
					FatalError(Format("FormatN: Unkown placeholder \"%s\"", placeholderPart));
					return 0;
				}

				ret = Format(Format("%%s%%%s", placeholderType), ret, items[index]);

				inPlaceholder = 0;
				placeholderType = "";
				placeholderPart = "";
			}
		}
		else
		{
			if(inPlaceholder == 0)
			{
				ret = Format("%s%c", ret, c);
			}
			else if(inPlaceholder == 1)
			{
				placeholderType = Format("%s%c", placeholderType, c);
			}
			else if(inPlaceholder == 2)
			{
				placeholderPart = Format("%s%c", placeholderPart, c);
			}
		}
	}

	if(inPlaceholder == 1)
	{
		FatalError(Format("FormatN: Placeholder not finished at end of format-string: \"%%%s\"", placeholderType));
		return 0;
	}
	else if(inPlaceholder == 2)
	{
		FatalError(Format("FormatN: Placeholder not finished at end of format-string: \"%%%s%%%s\"", placeholderType, placeholderPart));
		return 0;
	}

	return ret;
}
