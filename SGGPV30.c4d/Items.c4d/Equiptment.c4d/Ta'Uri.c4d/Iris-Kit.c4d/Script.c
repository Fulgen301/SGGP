/*--- Iris-Kit ---*/

#strict

func Activate(pClonk)
{ 
  if(!FindObject2(Find_Func("IsStargate"),Find_Distance(200),Sort_Distance()))
  {
   Message("<c ff0000>Kein Gate in der nähe!</c>",this());
   return(1);
  }
  if(FindObject2(Find_Func("IsStargate"),Find_Distance(200),Sort_Distance())->HasIris())
  {
   if(LocalN("update",FindObject2(Find_Func("IsStargate"),Find_Distance(200),Sort_Distance())->HasIris()) == 1)
   {
    Message("<c ff0000>Das Gate hat bereits eine Iris!</c>",this());
    return(1);
   }
   else
   {
    FindObject2(Find_ID(SGIR),Sort_Distance())->Update();
    Message("<c 00ff00>Die Iris im Gate wurde zu einem Iris-Shild aufgewertet!</c>",this());
    DoneIt();
    return(1);
   }
   return(1);
  }
  else
  {
   FindObject2(Find_Func("IsStargate"),Find_Distance(200),Sort_Distance())->InstallIris();
   FindObject2(Find_ID(SGIR),Sort_Distance())->Update();
   Message("<c 00ff00>Ein Iris-Schild wurde im Gate eingebaut!</c>",this());
   DoneIt();
   return(1);
  }
  return(1);
}

func DoneIt()
{
  Sound("Connect");
  RemoveObject();
  return(1);
}

func Hit()
{
  Sound("RockHit*");
  return(1);
}
