#strict
local unlook,x,y;

Initialize:
  SetAction("_NIX");
  SetSolidMask (0,1,7,67,0,0,this()); 
  return(1);
  
Peng:
  if(unlook==1)return(1);
  unlook=1;
  x=Par(0)-GetX();
  y=Par(1)-GetY();
  CreateObject(LOCH,x+4,y,-1);
  return(1);
  
Timer:
  if(Global(111)==1)unlook=0;
  return(1);
