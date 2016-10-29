#strict

Launch:
  SetAction(Par(0));
  SetLocal(0,Par(1));
  if(Local(0)) SetXDir(Par(2));
  if(Local(0)) SetYDir(Par(3));
  return(1);

ContactBottom:
  if(Not(InLiquid())) Sound("Wasser");
  if(Local(0)) return(RemoveObject());
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  ObjectCall(CreateObject(WS3V,0,-2),"Launch",GetAction(),1,Sum(-20,Random(40)),Sum(-20,Random(30)));
  RemoveObject();
  return(1);
  
