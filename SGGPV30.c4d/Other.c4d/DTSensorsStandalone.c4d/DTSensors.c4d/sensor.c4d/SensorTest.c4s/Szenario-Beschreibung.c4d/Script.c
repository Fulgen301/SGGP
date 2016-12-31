#strict

protected func Activate(iByPlayer)
{
  MessageWindow(GetDesc(), iByPlayer);
  return(1);
}

func InitializePlayer(iPlr)
{
  ScheduleCall (0,"Activate",35,0,iPlr); 
}