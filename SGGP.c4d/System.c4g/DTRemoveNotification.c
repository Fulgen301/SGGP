#strict 2

global func AddRemoveNotification(callback, object target, object callbackTarget, int prio)
{
	if(!target || !callback)
	{
		return;
	}
	callbackTarget = callbackTarget || this;
	return AddEffect("IntRemoveNotifier", target, prio || 1, 0, callbackTarget, 0, callback);
}

global func RemoveRemoveNotification(int id, object target)
{
	if(!target)
	{
		return;
	}
	return RemoveEffect(0, target, id);
}

global func FxIntRemoveNotifierStart(object target, int effectNumber, int temp, callback)
{
	if(!temp)
	{
		EffectVar(0, target, effectNumber) = callback;
	}
}

global func FxIntRemoveNotifierStop(object target, int effectNumber, int reason, bool temp)
{
	if(!temp)
	{
		if(reason == FX_Call_RemoveClear)
		{
			Call(EffectVar(0, target, effectNumber), target);
		}
		else if(reason == FX_Call_RemoveDeath)
		{
			return FX_Stop_Deny;
		}
	}
}
