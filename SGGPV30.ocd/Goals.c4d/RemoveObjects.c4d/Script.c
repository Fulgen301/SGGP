/*-- Objekte entfernen --*/

#strict
#include GOAL
local Type;
  
func IsFulfilled()
{
	if(!ObjectCount(Type)) return(1);
}

func Activate(iPlayer)
{
	MessageWindow(Format("Noch %d Objekte vom Typ %s ({{%i}}) zu entfernen",ObjectCount(Type),GetName(0,Type),Type),iPlayer);
}

func AddType(id IdType)
{
	Type = IdType;
}