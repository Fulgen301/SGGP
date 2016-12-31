#strict 2
#appendto LNKT


func Activate(clonk)
{
	[$TxtConnectline$]
	var line = FindObject2(Find_Action("Connect"), Find_Or(Find_ActionTarget(this), Find_ActionTarget2(this)));
	var lineName = 0;
	if(line)
	{
		lineName = GetName(line);
	}
	var fObjs = FindObjects(Find_OCF(OCF_LineConstruct), Find_AtPoint(), Find_Exclude(this));
	var objs = CreateArray(GetLength(fObjs));
	var i = 0;
	for(var obj in fObjs)
	{
		if(line && obj == GetActionTarget(0, line) || obj == GetActionTarget(1, line))
		{
			objs[i++] = [obj, "$TxtRemoveLine$", GetID()];
		}
		else
		{
			var lineType = obj->~LineConnectType() || DefaultLineType(obj);
			if(lineType)
			{
				var showName = GetName(obj);
				if(!lineName)
				{
					showName = Format("%s: %s", GetName(obj), GetName(0, lineType));
				}
				objs[i++] = [obj, showName];
			}
		}
	}
	SetLength(objs, i);
	if(GetLength(objs) <= 1)
	{
		ConnectToObject(0, fObjs[0]);
	}
	else
	{
		var caption = "$TxtConnectline$";
		if(line)
		{
			caption = Format("$TxtConnectLineType$", GetName(line));
		}
		(clonk && clonk->~CreateSelectionMenu("ConnectToObject", objs, GetID(), caption, this)) || ConnectToObject(0, objs[0]);
	}
	return true;
}

func ConnectToObject(id id, object obj)
{
	// Keins da? Auch gut.
	if(!obj) return(Message("$TxtNoNewLine$", this));
	// Leitung
	var pLine = FindObject(0, 0,0,0,0, 0, "Connect", this);
	
	// Aktuelle Leitung anschließen
	if(pLine)
	{
		// Zielobjekt == Quellobject?
		if(obj == GetActionTarget(0, pLine) || obj == GetActionTarget(1, pLine))
		{
			// Leitung wieder entfernen
			Message("$TxtLineRemoval$", this, GetName(pLine));
			RemoveObject(pLine);
			Sound("Connect");
			return(1);
		}
		else
		{
			// Line an pFrom anschließen
			if(!ConnectLine(pLine, obj)) return(1);
		}
	}
	// Neue Leitung
	else
	{
		// LineType abfragen
		var linetype = obj->~LineConnectType();
		// Nicht vorhanden -> Standard-LineType verwenden
		if(!linetype) linetype = DefaultLineType(obj);
		// Kein möglicher Leitungstyp? :(
		if(!linetype)
		{
			Sound("Error");
			return(Message("$TxtNoNewLine$", this));
		}
		
		// Line erzeugen
		pLine = CreateLine(linetype, GetOwner(), obj, this);
	}
}
