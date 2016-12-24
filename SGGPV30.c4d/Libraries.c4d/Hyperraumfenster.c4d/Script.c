#strict 2
local iSize, iX1, iY1, iX, iY, iTime, Act, Travel, iType;
//1 = Öffnen
//2 = Schließen
//1 = Aufnehmen
//2 = Ausgeben

public func Initialize()
{
	Act = 1;
	SetAction("On");
	iType = 1;
	iTime = 38 * 3;
	SetCon(1);
	Sound("Hyperdrive");
}

public func SetSize(int i)
{
	iSize = i;
}

public func SetPos(int x, int y, int x1, int y1)
{
	iX = x;
	iY = y;
	iX1 = x1;
	iY1 = y1;
}

public func SetObjectDir(object pObj)
{
	if (GetX() > GetX(pObj))
	{
		SetDir(DIR_Right);
	}
	else 
	{
		SetDir(DIR_Left);
	}
}

public func Timer()
{
	if (Travel)
	{
		if (Distance(GetX(), GetY(), iX, iY) < 120)
		{
			Travel = 0;
			Act = 1;
			iType = 2;
			iTime = 38 * 3;
			SetVisibility(VIS_All);
			SetDir(!GetDir());
			Sound("Hyperdrive");
			SetXDir();
			SetYDir();
		}
		else 
		{
			SetXDir(+Sin(Angle(GetX(), GetY(), iX, iY), 800));
			SetYDir(-Cos(Angle(GetX(), GetY(), iX, iY), 800));
		}
		return true;
	}
	else 
	{
		if (iType == 1)
		{
			SetPosition(iX1, iY1);
		}
	}
	if (GetCon() != iSize)
	{
		if (Act == 2)
		{
			if (GetCon() == 1)
			{
				if (iType == 1)
				{
					SetVisibility(VIS_None);
					Travel = 1;
				}
				else 
				{
					DoCon(-1);
				}
			}
			else 
			{
				DoCon(-1);
			}
		}
		else 
		{
			DoCon(1);
		}
		return true;
	}
	else 
	{
		iTime--;
		if (!iTime)
		{
			SetCon(iSize - 1);
			Act = 2;
		}
		if (iType == 1)
		{
			var pObj, iWdt;
			iWdt = 8 * GetCon();
			for (pObj in FindObjects(Find_Or(Find_Category(C4D_Vehicle), Find_Category(C4D_Object), Find_Category(C4D_Living)), Find_Not(Find_AnyContainer()), Find_InRect(-iWdt / 4, -iWdt / 2, iWdt / 2, iWdt))) 
			{
				AddEffect("Hyperdrive", pObj, 200, 0, this(), 0, GetXDir(pObj), GetYDir(pObj), iTime);
				EffectVar(1, pObj, GetEffect("Hyperdrive", pObj)) = iTime;
				EffectVar(2, pObj, GetEffect("Hyperdrive", pObj)) = GetYDir(pObj);
				EffectVar(3, pObj, GetEffect("Hyperdrive", pObj)) = GetXDir(pObj);
				pObj->Enter(this());
			}
		}
		else 
		{
			iWdt = 8 * GetCon();
			var pObj;
			for (pObj in FindObjects(Find_Container(this()))) 
			{
				if (EffectVar(1, pObj, GetEffect("Hyperdrive", pObj)) == iTime)
				{
					Exit(pObj, 0, iWdt / 2);
					pObj->SetXDir(EffectVar(2, pObj, GetEffect("Hyperdrive", pObj)) * 5);
					pObj->SetXDir(EffectVar(3, pObj, GetEffect("Hyperdrive", pObj)));
					RemoveEffect("Hyperdrive", pObj);
				}
			}
		}
	}
}