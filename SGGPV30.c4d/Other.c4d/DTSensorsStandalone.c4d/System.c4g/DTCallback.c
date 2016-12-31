/*-- Extensible callback system --*/
#strict 2

static const CallbackTarget_Bind = -1;
static const CallbackTarget_Global = -2;
static const CallbackTarget_Scenario = -3;

global func GlobalCallback(string name) { return [CallbackTarget_Global, name]; }
global func ScenarioCallback(string name) { return [CallbackTarget_Scenario, name]; }
global func ObjectCallback(string name, object target) { return [target || this || FatalError("ObjectCallback without target object"), name]; }
global func DefinitionCallback(string name, id target) { return [target || GetID() || FatalError("DefinitionCallback without target definition"), name]; }
global func Callback(string name, target) { return [target || this || GetID() || CallbackTarget_Global, name]; }
global func BindCallback(callback, array binding) { return [CallbackTarget_Bind, callback, binding]; }

static const BindCallback_Bind_Value = -1;
static const BindCallback_Bind_Context = -2;
static const BindCallback_Bind_ContextDef = -3;
static const BindCallback_Bind_CallbackResult = -4;
static const BindCallback_Bind_ArgumentArrayPart = -5;
static const BindCallback_Bind_Reference = -6;
global func Bind(value) { return [BindCallback_Bind_Value, value]; }
global func Bind_Context() { return [BindCallback_Bind_Context]; }
global func Bind_ContextDef() { return [BindCallback_Bind_ContextDef]; }
global func Bind_CallbackResult(callback) { return [BindCallback_Bind_CallbackResult, callback]; }
global func Bind_ArgumentArrayPart(int argument, part)
{
	if(GetType(part) != C4V_Array)
	{
		part = [part];
	}
	return [BindCallback_Bind_ArgumentArrayPart, argument, part];
}
global func Bind_Reference(array scopedVar) { return [BindCallback_Bind_Reference, scopedVar]; }

global func Call(callback)
{
	if(GetType(callback) == C4V_String)
	{
		return _inherited(callback, ...);
	}
	else
	{
		return CallA(callback, CreateFilledArray(...));
	}
}

global func CallA(callback, args, bool safe, array refs)
{
	if(GetType(callback) == C4V_String)
	{
		callback = [this, callback];
	}
	if(GetType(callback) != C4V_Array)
	{
		return _inherited(callback, args, ...);
	}
	else
	{
		refs = refs || [];
		var safeModifier = "";
		if(safe)
		{
			safeModifier = "~";
		}
		var target = callback[0], function = callback[1];
		var argsStr = "", pos = 0;
		for(var arg in args)
		{
			if(pos > 0)
			{
				argsStr = Format("%s, ", argsStr);
			}
			if(refs[pos])
			{
				argsStr = Format("%sScopedVar(%s)", argsStr, Serialize(arg));
			}
			else
			{
				argsStr = Format("%s%s", argsStr, Serialize(arg));
			}
			++pos;
		}
		if(target == CallbackTarget_Global)
		{
			return GlobalEval(Format("%s(%s)", function, argsStr));
		}
		else if(target == CallbackTarget_Scenario)
		{
			return GameCall(function, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
		}
		else if(target == CallbackTarget_Bind)
		{
			return CallA(callback[1], BindArgs(callback[2], args, safe, refs), safe, refs);
		}
		else
		{
			if(GetType(target) == C4V_C4Object || GetType(target) == C4V_C4ID)
			{
				return eval(Format("%s->%s%s(%s)", Serialize(target), safeModifier, function, argsStr));
			}
			else
			{
				return (this && this->~CallCustom(callback, args, ...)) || ROCK->~CallCustom(callback, args, ...);
			}
		}
	}
}

global func BindArgs_ArgumentArrayPart(array binding, array args, bool safe)
{
	var ret = args[binding[0]];
	for(var i = 1; i < GetLength(binding); ++i)
	{
		if(!safe || GetType(ret) == C4V_Array)
		{
			ret = ret[binding[i]];
		}
		else
		{
			return 0;
		}
	}
	return ret;
}

global func BindCustomArgs() { return _inherited(...); } // this allows "overloading" this function even if the "overloading" function is loaded before

global func BindArgs(array binding, array args, bool safe, array& refs)
{
	refs = [];
	var ret = CreateArray(GetLength(binding)), pos = 0;
	for(var bind in binding)
	{
		if(GetType(bind) == C4V_Int || GetType(bind) == C4V_Any && bind >= 0)
		{
			ret[pos] = args[bind];
		}
		else if(GetType(bind) == C4V_Array && GetLength(bind))
		{
			if(bind[0] == BindCallback_Bind_Value)
			{
				ret[pos] = bind[1];
			}
			else if(bind[0] == BindCallback_Bind_Context)
			{
				ret[pos] = this;
			}
			else if(bind[0] == BindCallback_Bind_ContextDef)
			{
				ret[pos] = GetID();
			}
			else if(bind[0] == BindCallback_Bind_CallbackResult)
			{
				ret[pos] = CallA(bind[1], args, safe);
			}
			else if(bind[0] == BindCallback_Bind_ArgumentArrayPart)
			{
				ret[pos] = BindArgs_ArgumentArrayPart(bind[2], args[bind[1]], safe);
			}
			else if(bind[0] == BindCallback_Bind_Reference)
			{
				refs[pos] = true;
				ret[pos] = bind[1];
			}
			else if(GetType(bind[0]) == C4V_Int && bind[0] < 0)
			{
				ret[pos] = BindCustomArgs(bind, args, safe);
			}
			else
			{
				ret[pos] = BindArgs(bind, args, safe);
			}
		}
		else
		{
			FatalError(Format("BindArgs: incorrect binding %v", bind));
		}
		++pos;
	}
	return ret;
}

global func GlobalEval(string code)
{
	var effect = AddEffect("IntGlobalEval", 0, 1);
	var ret = EffectCall(0, effect, "Eval", code);
	RemoveEffect(0, 0, effect);
	return ret;
}

global func FxIntGlobalEvalEval(object target, int effectNumber, string code)
{
	return eval(code);
}

global func foreach(array arr, callback)
{
	var i = 0;
	for(var val in arr)
	{
		CallA(callback, [val, i++]);
	}
}
