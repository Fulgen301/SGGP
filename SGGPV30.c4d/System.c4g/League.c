/*-- League script --*/

#strict 2

// Base64 codec, using a modified charset for CR League compatibility

// What we do here is split an arbitrary 8-bit string into what is essentially
// a 6-bit string, and vice versa. The Base64 charset chosen here is the full
// charset that the Clonk Rage league allows to store. Most importantly, this
// is not Base64 as defined by RFC 4648, because it does not use any padding,
// as well as using a slightly modified alphabet. This means you cannot use a
// standard Base64 encoder to generate strings accepted by this implementation
// unless you afterwards transform its output to conform to the alphabet used
// here, and remove all padding characters and line breaks.

static const __L64ENC_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_ ";
// Can't use hex escapes here, nor NUL bytes. Ugh. Since I only need values
// between 0 and 63, I've added 0x40 to all values. 0x20 (" ") means the input
// is not part of our alphabet and will get rejected.
static const __L64DEC_table = "                                               tuvwxyz{|}       @ABCDEFGHIJKLMNOPQRSTUVWXY    ~ Z[\\]^_`abcdefghijklmnopqrs     ";
// I wish I could pre-allocate the output string, but it probably doesn't
// matter too much because the data we get is hopefully small. (In fact, we
// know it will be small because CR will error out on strings larger than
// 1024 bytes).
global func League64Enc(string data)
{
	var buffer_data = 0;
	var buffer_bits = 0;
	var output = "";
	var c = 0;
	for (var i = 0; c = GetChar(data, i); ++i)
	{
		// Shift a character into the buffer
		buffer_data = (buffer_data << 8) | c;
		buffer_bits += 8;

		// Consume all 6-bit groups we have
		while (buffer_bits >= 6)
		{
			c = (buffer_data >> (buffer_bits - 6)) & 0x3f;
			output = Format("%s%c", output, GetChar(__L64ENC_table, c));
			buffer_bits -= 6;
		}
	}
	// Drain remainder of buffer. Always 2 or 4 bits because we're shifting it
	// in in 8 bit chunks, so it can't ever be an odd number of bits.
	if (buffer_bits == 2)
	{
		c = (buffer_data & 3) << 4;
		output = Format("%s%c", output, GetChar(__L64ENC_table, c));
	}
	else if (buffer_bits == 4)
	{
		c = (buffer_data & 15) << 2;
		output = Format("%s%c", output, GetChar(__L64ENC_table, c));
	}
	// We're not appending any padding because the league will kill it anyway.
	return output;
}

global func League64Dec(string data)
{
	var buffer_data = 0;
	var buffer_bits = 0;
	var output = "";
	for (var i = 0, cin; cin = GetChar(data, i); ++i)
	{
		// Fetch correct value from decoder table
		cin = GetChar(__L64DEC_table, cin);
		if (cin == 0x20)
		{
			// RFC 4648 demands that all inputs containing non-alphabet
			// characters be rejected.
			return 0;
		}
		// Else subtract the shift value of 0x40 used in constructing the table
		cin -= 0x40;

		// Shift value into buffer
		buffer_data = (buffer_data << 6) | cin;
		buffer_bits += 6;

		// Consume 8-bit group, if we have one
		if (buffer_bits >= 8)
		{
			buffer_bits -= 8;
			var c = (buffer_data >> buffer_bits) & 0xff;
			output = Format("%s%c", output, c);
			// Mask out consumed data
			buffer_data = buffer_data & ((1 << buffer_bits) - 1);
		}
	}
	// We may have some non-zero value left in the buffer, but all significant
	// data has been output, so we can just discard it.
	return output;
}

/** FindString
Sucht einen String in einem anderen und gibt die Anfangsposition zurück.
@author Limeox
*/

global func FindString(string szString, string szFind)
{
  for (var i; i < GetLength(szString); i++)
  {
    if (GetChar(szString,i) == GetChar(szFind))
    {
      var f = true;
      for (var j = 0; j < GetLength(szFind); j++)  
        if (GetChar(szString, i + j) != GetChar(szFind, j))
          f = false;
        if (f)
          return i;
    }
  }  
  return -1;
}

/** SplitString
Teilt einen String in 2 Teile.
@author Limeox
*/

global func SplitString(string szString, string & part1, string & part2, int index)
{
  part1 = "";
  part2 = "";
  for (var i; i < GetLength(szString); i++)
  {
    if (i < index)
      part1 = Format("%s%c", part1, GetChar(szString, i));
    else if(i > index)
      part2 = Format("%s%c", part2, GetChar(szString, i));
  }
  return true;
}

global func SplitStringAT(string szString, string szChar)
{
	szChar = Format("%c", GetChar(szChar));
	
	var ret = [];
	
	for(var i = 0; FindString(szString, szChar) != -1; i++)
	{
		SplitString(szString, ret[GetLength(ret)], szString, FindString(szString, szChar));
		if(i > 100) break;
	}
	ret[GetLength(ret)] = szString;
	return ret;
}

global func JoinString(array aArray, string szDelimeter)
{
	if(!szDelimeter) szDelimeter = "";
	var szString = "";
	for(var i in aArray)
	{
		var type = "%v";
		if(GetType(i) == C4V_String) type = "%s";
		else if(GetType(i) == C4V_C4ID) type = "%i";
		else if(GetType(i) == C4V_Int) type = "%d";
		if(szString != "") szString = Format(Format("%%s%%s%s", type), szString, szDelimeter, i);
		else szString = Format(Format("%%s%s", type), szString, i);
	}
	return szString;
}