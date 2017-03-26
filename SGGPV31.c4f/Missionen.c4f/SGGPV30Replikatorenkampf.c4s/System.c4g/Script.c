#strict 2
#appendto NOAM

protected func Initialize()
{
	_inherited(...);
	return RemoveObject();
}