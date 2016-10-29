#strict
local pTarget,iSpeed,iMehr,iDamg;
func Initialize()
{
	SetAction("Fliegen");
	iSpeed=3;
}

func Timer()
{
	iMehr++;
	if(iMehr < 30) 
	{
		SetYDir(-100);
		return();
	}
	if(iMehr < 34)
	{
		if(iSpeed < 200) iSpeed+=2;
  		iMehr=30;
  	}
  	SetXDir(+Sin(GetR(),iSpeed));
  	SetYDir(-Cos(GetR(),iSpeed));
	if(!pTarget) pTarget = FindObject2(Find_Not(Find_ID(RELE)),Find_Or(Find_OCF(OCF_CrewMember),Find_Category(C4D_Vehicle),Find_ID(PUD_),Find_ID(TEL_)),Find_Distance(RepliView),Sort_Distance());
	SetR(Angle(GetX(),GetY(),GetX(pTarget),GetY(pTarget)));
	if(ObjectDistance(pTarget) < 10) 
	{
		Explode(30);
		Explode(20);
		Explode(10);
	}
}

func KilledByARW()
{
	CastReplis(20,1);
	RemoveObject();
}

func Hit()
{
	Explode(30);
	Explode(20);
	Explode(10);
}


func IsRepli()
{
	return(true);
}

func Damage(int iLevel)
{
	if(GetDamage() != 0) 
	{
		Hit();
	}
	return(1);
}

func IsBulletTarget()    { return(1); }