/* Stabwaffen-Kristall */

#strict 2

protected func Activate(pCaller)
{
  if(FindObject2(Find_Container(pCaller),Find_ID(STBW),Find_Not(Find_Func("HasCell"))))
  {
   ShiftContents(Contained(),0,STBW);
   Enter(FindObject2(Find_Container(pCaller),Find_ID(STBW),Find_Not(Find_Func("HasCell"))));
  }
  return 1;
}

func Damage()
{
  if(GetDamage() > 10)
  {
   Explode(30);
  }
  return(1);
}

/* Eigenschaften */

public func IsGoauldWeapon() {return true;}
public func IsAlchemContainer() {return(true);}
public func AlchemProcessTime() {return(150);}
public func IsBulletTarget() { return(true);}
local Name = "$Name$";
local Collectible = 1;
