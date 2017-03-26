#strict 2
#appendto CTW0

func IsRemoteControllable() { return true; }

func RemoteControlMap()
{
	var ret = _inherited(...);
	ret[GetLength(ret)] = [RC7I_Control_T, "Shoot", "$CTW0_DirectShoot$"];
	return ret;
}

func GetNextAmmo()
{
	if(cannon)
	{
		for(var i = 0, content; content = Contents(i); ++i)
		{
			if(GetID(content) != GUNP && cannon->~CannonAmmo(content))
			{
				return content;
			}
		}
	}
}

func Shoot(object caller)
{
	if(cannon)
	{
		if(cannon->~IsDirectShoot())
		{
			return ContainedDig(caller);
		}
		else
		{
			var ammo = GetNextAmmo();
			return ammo && cannon->~Shoot(GetID(ammo), ammo, caller);
		}
	}
}
