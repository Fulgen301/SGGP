/*-- Scripte aus http://wiki.nosebud.de/wiki/Kategorie:Scripte --*/

#strict 2
/* Objekt zum Overlay machen */

global func Object2Overlay(object target, object obj)
{
// Sicherheit/Lokaler Aufruf
if (!target) return 0;
if (!obj) if (!(obj = this)) return 0;

// Neues Overlay mit Parametern des Objektes erzeugen
var overlay_mode = GFXOV_MODE_Base;
var overlay_action = 0;
var overlay_id = GetUnusedOverlayID(GFX_Overlay, target);
if (!ActIdle(obj))
{
overlay_mode = GFXOV_MODE_Action;
overlay_action = GetAction(obj);
}
if (!SetGraphics(0, target, GetID(obj), overlay_id, overlay_mode, overlay_action, GetObjectBlitMode(obj),0)) return 0;
if (GetClrModulation(obj)) SetClrModulation(GetClrModulation(obj), target, overlay_id);
SetObjDrawTransform(1000,0,(GetX(obj)-GetX(target))*1000, 0,1000,(GetY(obj)-GetY(target))*1000, target, overlay_id);
// Altes Objekt kann weg
RemoveObject(obj);
// Erzeugtes Overlay zurückgeben
return overlay_id;
}

global func GetClanTag(int playerIndex)
{
var name = GetPlayerName(playerIndex);
if (!name) return "";
// Das erste Zeichen sollte '[' sein.
var leftBracket = GetChar(name, 0);
if (leftBracket != 91) return "";
var position = 1;
var tag = "";
// Nach dem ']'-Zeichen suchen, die Zeichen zwischen diesen Klammern merken.
var length = GetLength(name);
while (position < length)
{
var char = GetChar(name, position);
if (char != 93) tag = Format("%s%c", tag, char);
else return tag;
position++;
}
// Kein vollständiger Clantag gefunden.
return "";
}

/* League64 by Isilkor */

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
