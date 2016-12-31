#strict 2

static TU7I_Speed;
static const TU7I_NoCallback = -1;

func Initialize()
{
	SetAction("Connect");  
	
	SetVertex(0, 0, GetX());
	SetVertex(0, 1, GetY());
	
	SetVertex(1, 0, GetX());
	SetVertex(1, 1, GetY());
	
	SetPosition(0, 0, this);
	
	Local(0) = 2;
	Local(1) = 2;
	
	SetClrModulation(RGBa(255, 255, 255, 64));
}

func Complement(object line)
{
	if(line)
	{
		SetAction("Idle");
		SetObjectOrder(this, line, true);
		return AddEffect("ComplementLine", line, 1, 1, this);
	}
}

func LineBreak(bool noMsg)
{
	if(!noMsg)
	{
		var source = GetActionTarget(0);
		var target = GetActionTarget(1);

		if(source && GetID(source) == TK7I) 
		{
			Message("$TxtLinebroke$", source);
		}
		else
		{
			Message("$TxtLinebroke$", target);
		}
	}
}

func KitID()
{
	return TK7I;
}

func CanSendObject(object sender, object obj)
{
	var lineEnd = GetLineEnd(sender);
	return lineEnd && lineEnd->~AcceptsObject(obj, 0, this);
}

func CanRetrieveObject(object receiver, id type, bool allowProduction, object excludeOrigin, object sender)
{
	if(ObjectOrigin(receiver) == excludeOrigin)
	{
		return false;
	}
	var lineEnd = sender || GetLineEnd(receiver);
	return lineEnd && lineEnd->~HasObject(type, allowProduction, this, excludeOrigin);
}

func SendObject(object sender, object obj, arriveCallback, bool noReturn, object realTarget)
{
	var lineEnd = GetLineEnd(sender);
	if(obj != lineEnd && (noReturn || (realTarget || lineEnd)->~AcceptsObject(obj, 0, this)))
	{
		var box = CreateObject(TC7I, 0, 0, GetOwner(obj));
		SetObjectOrder(this, box, true);
		if(!obj->Enter(box))
		{
			return false;
		}
		AddEffect("SendObject", box, 1, 1, this, 0, sender, noReturn, arriveCallback);
		return true;
	}
	return false;
}

func RetrieveObject(object receiver, id type, arriveCallback, object excludeOrigin, failCallback, object realTarget)
{
	var lineEnd = GetLineEnd(receiver);
	return lineEnd && CanRetrieveObject(receiver, type, true, excludeOrigin, lineEnd) && lineEnd->~RetrieveObject(this, type, arriveCallback, excludeOrigin, failCallback, realTarget);
}

func GetRetrievableObjects(object receiver)
{
	var lineEnd = GetLineEnd(receiver);
	return lineEnd && lineEnd->~GetRetrievableObjects(this, ...);
}

func GetLineDistancePoint(int distance, int startVertex, int dir, int& x, int& y, int& r)
{
	if(!dir)
	{
		return;
	}
	var max = GetVertexNum() - 1, vertexDistance, vXC, vYC, vXN, vYN;
	var rOff = 3 + (dir < 0);
	for(var vertex = startVertex; Inside(vertex + dir, 0, max); vertex += dir)
	{
		vXC = GetVertex(vertex, VTX_X);
		vYC = GetVertex(vertex, VTX_Y);
		vXN = GetVertex(vertex + dir, VTX_X);
		vYN = GetVertex(vertex + dir, VTX_Y);
		var dist = Distance(vXC, vYC, vXN, vYN);
		if(dist > distance)
		{
			var angle = Angle(vXC, vYC, vXN, vYN);
			x = vXC + ((vXN - vXC) * distance + dist / 2) / dist - Cos(angle, rOff) * dir;
			y = vYC + ((vYN - vYC) * distance + dist / 2) / dist - Sin(angle, rOff) * dir;
			r = angle - 90;
			return false;
		}
		else
		{
			distance -= dist;
		}
	}
	x = vXN;
	y = vYN;
	return true;
}

func FxSendObjectStart(object target, int effectNumber, int temp, object sender, bool noReturn, arriveCallback)
{
	if(!temp)
	{
		EffectVar(0, target, effectNumber) = (GetActionTarget(1) == sender);
		EffectVar(1, target, effectNumber) = noReturn;
		
		EffectCall(target, effectNumber, "Timer");
		EffectVar(2, target, effectNumber) = AddEffect("SendObjectHelper", this, 1, 0, this, 0, target);
		EffectVar(3, target, effectNumber) = arriveCallback;
	}
}

func FxSendObjectHelperStart(object target, int effectNumber, int temp, object box)
{
	if(!temp)
	{
		EffectVar(0, target, effectNumber) = box;
	}
}

func FxSendObjectHelperStop(object target, int effectNumber, int reason, bool temp)
{
	if(!temp)
	{
		var box = EffectVar(0, target, effectNumber);
		if(box)
		{
			RemoveObject(box, true);
		}
	}
}

func FxSendObjectTimer(object target, int effectNumber, int effectTime)
{
	var startTarget = EffectVar(0, target, effectNumber);
	var dir = -(startTarget * 2 - 1);
	var startVertex = 0;
	if(startTarget)
	{
		startVertex = GetVertexNum() - 1;
	}
	var x, y, r, end;
	r = target->GetR();
	end = GetLineDistancePoint(effectTime * (TU7I_Speed || 20), startVertex, dir, x, y, r);
	
	target->SetPosition(x, y);
	target->SetR(r);
	target->SetRDir(0);

	if(end)
	{
		var lineEnd = GetActionTarget(!startTarget);
		var noReturn = EffectVar(1, target, effectNumber);
		var arriveCallback = EffectVar(3, target, effectNumber);
		var cnt = target->ContentsCount();
		for(var i = cnt - 1; i >= 0; --i)
		{
			var obj = target->Contents(i);
			var ret;
			if(!(ret = lineEnd->~ReceiveObject(obj, noReturn, arriveCallback, this)) && !noReturn)
			{
				SendObject(lineEnd, obj, 0, true);
			}
			else
			{
				if(arriveCallback && ret != TU7I_NoCallback)
				{
					lineEnd->CallA(arriveCallback, [obj, this, lineEnd], true);
				}
			}
		}
		return FX_Execute_Kill;
	}
}

func FxSendObjectStop(object target, int effectNumber, int reason, bool temp)
{
	if(!temp)
	{
		RemoveObject(target, true);
		RemoveEffect(0, this, EffectVar(2, target, effectNumber));
	}
}

func FxComplementLineStart(object target, int effectNumber, int temp)
{
	if(!temp)
	{
		return EffectCall(target, effectNumber, "Timer");
	}
}

func FxComplementLineTimer(object target, int effectNumber)
{
	var i;
	var angle, prevAngle, midAngle;
	var cnt = target->GetVertexNum();
	for(i = 0; i < cnt; ++i)
	{
		var x = target->GetVertex(i, VTX_X);
		var y = target->GetVertex(i, VTX_Y);
		
		if(i < cnt - 1)
		{
			var nX = target->GetVertex(i + 1, VTX_X);
			var nY = target->GetVertex(i + 1, VTX_Y);
			angle = Angle(x, y, nX, nY);
		}
		
		if(i == 0)
		{
			midAngle = angle;
		}
		else if(i == cnt - 1)
		{
			midAngle = prevAngle;
		}
		else
		{
			midAngle = (angle + prevAngle) / 2;
			if(Abs(angle - prevAngle) > 180)
			{
				midAngle += 180;
			}
		}
			
		if(GetVertexNum() <= i)
		{
			AddVertex(x, y);
		}
		else
		{
			SetVertex(i, VTX_X, x - Cos(midAngle, 7));
			SetVertex(i, VTX_Y, y - Sin(midAngle, 7));
		}
		prevAngle = angle;
	}
	for(var j = GetVertexNum() - 1; j >= i; --j)
	{
		RemoveVertex(j);
	}
}

func FxComplementLineStop(object target, int effectNumber, int reason, bool temp)
{
	if(!temp)
	{
		RemoveObject();
	}
}

func ObjectOrigin(object other)
{
	return GetLineEnd(other)->~ObjectOrigin();
}

func HasObjectOrigin(object origin)
{
	return GetLineEnd()->~ObjectOrigin() == origin || GetLineEnd(0, true)->~ObjectOrigin() == origin;
}

func IsTube()
{
	return true;
}

func FactoryLoad(object other)
{
	return GetLineEnd(other)->~FactoryLoad();
}
