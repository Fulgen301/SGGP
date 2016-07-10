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