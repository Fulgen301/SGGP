#strict

public func Initialize()
{
  SetAction("Open");
  return(1);
}

public func Check()
{
  if(GetAction() eq "Close")
  {
   if(GetDir() == 1)
   {
    SetSolidMask(31,21,31,21);
   }
   
   if(GetDir() == 0)
   {
    SetSolidMask(0,21,31,21);
   }
  }
  return(1);
}

public func Dir1()
{
  SetDir(1);
  return(1);
}

public func Dir0()
{
  SetDir(0);
  return(1);
}

public func Close()
{
  SetSolidMask(0,0,31,21);
  return(1);
}

public func Open()
{
  SetSolidMask(0,0,0,0);
  return(1);
}

public func Teltak()
{
	return(1);
}