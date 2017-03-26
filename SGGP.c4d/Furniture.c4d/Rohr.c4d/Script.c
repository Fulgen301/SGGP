#strict
local unlook,x,y;

Initialize:
  SetAction("_NIX");
  SetSolidMask (1,1,7,68,0,0,this()); 
  return(1);
  
Peng:
  if(unlook==1)return(1);
  unlook=1;
  x=GetX()-Par(0);
  y=GetY()-Par(1);
  CreateObject(LOCH,x-10,y,-1);
  return(1);
  
Timer:
  if(Global(111)==1)unlook=0;
  return(1);
