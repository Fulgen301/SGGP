#strict 2

global func AddTimer(callback, int timer, object target, int prio)
{
	target = target || this;
	return AddEffect("IntTimer", target, prio || 1, timer, target, 0, callback);
}

global func RemoveTimer(int id, object target)
{
	target = target || this;
	return RemoveEffect(0, target, id);
}

global func FxIntTimerStart(object target, int effectNumber, int temp, callback)
{
	if(!temp)
	{
		EffectVar(0, target, effectNumber) = callback;
	}
}

global func FxIntTimerTimer(object target, int effectNumber, int effectTime)
{
	return Call(EffectVar(0, target, effectNumber));
}
