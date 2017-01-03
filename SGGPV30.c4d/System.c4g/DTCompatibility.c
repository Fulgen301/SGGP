/*-- Avoid errors from non-existing Engine-Functions --*/

#strict 2

static hostFeatures;
static hostTime;

global func SetGameComment() { return _inherited(...); }
global func IsHost() { return _inherited(...); }
global func RequestHostFeature(string feature) { if(!HaveHostFeature(feature) || feature == "HostTime") return _inherited(feature, ...); }

global func AnnounceHostFeature(string feature)
{
	hostFeatures || (hostFeatures = []);
	hostFeatures[GetLength(hostFeatures)] = feature;
}

global func HaveHostFeature(string feature)
{
	hostFeatures || (hostFeatures = []);
	return GetIndexOf(feature, hostFeatures) != -1;
}

global func ReRequestHostFeatures()
{
	if(IsNetwork())
	{
		var features = hostFeatures;
		hostFeatures = [];

		if(features)
		{
			for(var feature in features)
			{
				RequestHostFeature(feature);
			}
		}
	}
}

global func AnnounceHostTime(int time)
{
	hostTime = time;
}

global func GetSystemTime(int what)
{
	if(HaveHostFeature("HostTime"))
	{
		if(what == 10) // is leap year
		{
			var year = GetSystemTime(0);
			return !!((!(year % 4) && year % 100) || !(year % 400));
		}
		if(what == 9) return hostTime; // timestamp
		if(what == 8) // day of year
		{
			return (hostTime - (GetSystemTime(0) - 1970) * 31556926)/(3600*24) + 1;
		}
		if(what == 7) return 0;
		if(what == 6) return hostTime % 60;
		if(what == 5) return (hostTime/60) % 60;
		if(what == 4) return (hostTime/3600) % 24;
		if(what == 3)
		{
			var dayofyear = GetSystemTime(8);
			var leapyear = GetSystemTime(10);
			if(dayofyear < 32) return dayofyear;
			else if(dayofyear < 60 + leapyear) return dayofyear - 31;
			else if(dayofyear < 91 + leapyear) return dayofyear - 59;
			else if(dayofyear < 121 + leapyear) return dayofyear - (90 + leapyear);
			else if(dayofyear < 152 + leapyear) return dayofyear - (120 + leapyear);
			else if(dayofyear < 182 + leapyear) return dayofyear - (151 + leapyear);
			else if(dayofyear < 213 + leapyear) return dayofyear - (181 + leapyear);
			else if(dayofyear < 244 + leapyear) return dayofyear - (212 + leapyear);
			else if(dayofyear < 274 + leapyear) return dayofyear - (243 + leapyear);
			else if(dayofyear < 305 + leapyear) return dayofyear - (273 + leapyear);
			else if(dayofyear < 335 + leapyear) return dayofyear - (204 + leapyear);
			else return dayofyear - (334 + leapyear);
		}
		if(what == 2)
		{
			return ((hostTime/86400) + 4) % 7;
		}
		if(what == 1)
		{
			var dayofyear = GetSystemTime(8);
			var leapyear = GetSystemTime(10);
			if(dayofyear < 32) return 1;
			else if(dayofyear < 60 + leapyear) return 2;
			else if(dayofyear < 91 + leapyear) return 3;
			else if(dayofyear < 121 + leapyear) return 4;
			else if(dayofyear < 152 + leapyear) return 5;
			else if(dayofyear < 182 + leapyear) return 6;
			else if(dayofyear < 213 + leapyear) return 7;
			else if(dayofyear < 244 + leapyear) return 8;
			else if(dayofyear < 274 + leapyear) return 9;
			else if(dayofyear < 305 + leapyear) return 10;
			else if(dayofyear < 335 + leapyear) return 11;
			else return 12;
		}
		if(what == 0) return 1970 + ((hostTime + 31556926 * 2)/(31556926)) - 2;
	}
	else return _inherited(what, ...);
}
