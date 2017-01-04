/*-- Template Functions --*/

#strict 2

static v;
static TMPL_Funcs;
static const TMPL_FuncArguments = 0;
static const TMPL_FuncContents = 1;
static const TMPL_FuncName = 2;
static const TMPL_FuncCommands = 3;

global func InitializeTemplateFunctions()
{
	if(GetType(v) != C4V_Array) v = [];
	if(GetType(TMPL_Funcs) != C4V_Array) TMPL_Funcs = [];
}

global func DefineFunction(string name, arguments, commands)
{
	InitializeTemplateFunctions();

	var anonymousFunction = Function(arguments, commands);

	var function = [anonymousFunction[0], anonymousFunction[1], name, commands];

	SetFunction(name, function);
}

global func SetFunction(string name, array function)
{
	var index = FindTemplateFunction(name);
	if(index != -1)
	{
		TMPL_Funcs[index] = function;
	}
	else
	{
		TMPL_Funcs[GetLength(TMPL_Funcs)] = function;
	}
}

global func RemoveFunction(string name)
{
	var index = FindTemplateFunction(name);
	if(index != -1)
	{
		var i;
		for(i = index; i < GetLength(TMPL_Funcs) - 1; ++i)
		{
			TMPL_Funcs[i] = TMPL_Funcs[i + 1];
		}
		TMPL_Funcs[GetLength(TMPL_Funcs) - 1] = 0;
	}
}

global func Function(arguments, commands)
{
	if(!commands)
	{
		commands = arguments;
		arguments = [];
	}

	if(GetType(arguments) == C4V_String) arguments = [arguments];
	else if(arguments == 0) arguments = [];

	if(GetType(commands) == C4V_String) commands = [commands];

	var funcContents = [];
	for(var command in commands)
	{
		var isArg = false;
		var argument = "";
		var funcContent = [];
		var contentPart = "";
		var escapeCount = 0;
		for(var i = 0; i < GetLength(command); ++i)
		{
			var c = GetChar(command, i);
			if(isArg)
			{
				if(c == 37) // %
				{
					if(argument == "")
					{
						contentPart = Format("%s%%", contentPart);
					}
					else
					{
						var index = GetIndexOf2(argument, arguments);
						if(index == -1)
						{
							FatalError(Format("Function: Unknown argument-name %s", argument));
							return;
						}
						else
						{
							funcContent[GetLength(funcContent)] = [index, escapeCount];
							argument = "";
							escapeCount = 0;
						}
					}
					isArg = false;
				}
				else if(argument == "" && c == 47) // /
				{
					++escapeCount;
				}
				else
				{
					if(contentPart != "")
					{
						funcContent[GetLength(funcContent)] = contentPart;
						contentPart = "";
					}

					argument = Format("%s%c", argument, c);
				}
			}
			else
			{
				if(c == 37) // %
				{
					isArg = true;
				}
				else if(c == 39) // '
				{
					contentPart = Format("%s\"", contentPart);
				}
				else
				{
					contentPart = Format("%s%c", contentPart, c);
				}
			}
		}
		if(isArg) FatalError(Format("Function: argument-reference \"%s\" not closed.", argument));
		else if(contentPart) funcContent[GetLength(funcContent)] = contentPart;
		funcContents[GetLength(funcContents)] = funcContent;
	}

	return [arguments, funcContents];
}

global func FindTemplateFunction(string name)
{
	var i = 0;
	for(var function in TMPL_Funcs)
	{
		if(GetType(function) == C4V_Array && function[TMPL_FuncName] == name) return i;
		++i;
	}
	return -1;
}

global func F(string name, array args)
{
	return f(Func(name), args);
}

global func f(array function, array args)
{
	var ret;
	for(var content in function[TMPL_FuncContents])
	{
		var command = "";
		for(var contentPart in content)
		{
			if(GetType(contentPart) == C4V_Array)
			{
				var part = StringReplace("'", Serialize(args[contentPart[0]]), "\\\"");
				for(var i = 0; i < contentPart[1]; ++i)
				{
					part = EscapeString(part);
				}
				command = Format("%s%s", command, part);
			}
			else command = Format("%s%s", command, contentPart);
		}
		ret = eval(command);
	}
	return ret;
}

global func DebugF(string function, array args)
{
	return DebugFunc(Func(function), args);
}

global func DebugFunc(array function, array args)
{
	var ret;
	for(var content in function[TMPL_FuncContents])
	{
		var command = "";
		for(var contentPart in content)
		{
			if(GetType(contentPart) == C4V_Array)
			{
				var part = StringReplace("'", Serialize(args[contentPart[0]]), "\\\"");
				for(var i = 0; i < contentPart[1]; ++i)
				{
					part = EscapeString(part);
				}
				command = Format("%s%s", command, part);
			}
			else command = Format("%s%s", command, contentPart);
		}
		Log(command);
	}
	return ret;
}

global func Func(string name)
{
	var index = FindTemplateFunction(name);
	if(index == -1)
	{
		FatalError(Format("Func: Unknown function %s.", name));
		return;
	}
	return TMPL_Funcs[index];
}

global func SaveFunction(int plr, string name, array function)
{
	return SetPlrExtraDataArray(plr, Format("TemplateFunction_%s", name), function);
}

global func LoadFunction(int plr, string name, string loadAs)
{
	var function = GetPlrExtraDataArray(plr, Format("TemplateFunction_%s", name));
	if(function == 0)
	{
		FatalError(Format("LoadFunction: Unknown function: \"%s\"", name));
		return;
	}
	if(loadAs != 0)
	{
		SetFunction(loadAs, function);
	}
	return function;
}

global func DeleteFunction(int plr, string name)
{
	return SetPlrExtraDataString(plr, Format("TemplateFunction_%s", name), "");
}

global func CallCustom(callback, args)
{
	if(GetType(callback) == C4V_Array && GetLength(callback) >= 2 && GetType(callback[0]) == C4V_Array && GetType(callback[1]) == C4V_Array)
	{
		return f(callback, args);
	}
	else
	{
		return _inherited(callback, args, ...);
	}
}
