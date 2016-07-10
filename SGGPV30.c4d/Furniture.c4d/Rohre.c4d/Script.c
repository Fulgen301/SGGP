#strict

SetLeck:
//Par(0)=Farbe der Flüssigkeit
//0...blau; 1...dunkelblau; 2...rot; 3...dunkelrot; 4...grün
//5...dunkelgrün; 6...gelb; 7...orange; 8...weiß; 9...braun
//Par(1)=Tropfenhäufigkeit
  SetLocal(0,Par(0));
  SetLocal(1,Par(1));
  SetAction("Loch");
  return(1);

Leck:
  if(Not(Random(Local(1)))) ObjectCall(CreateObject(WS3V,-5,-5),"Launch",ActionPaint());
  return(1);
ActionPaint:
  if(Equal(Local(0),0)) return("Blue1");
  if(Equal(Local(0),1)) return("Blue2");
  if(Equal(Local(0),2)) return("Red1");
  if(Equal(Local(0),3)) return("Red2");
  if(Equal(Local(0),4)) return("Green1");
  if(Equal(Local(0),5)) return("Green2");
  if(Equal(Local(0),6)) return("Yellow1");
  if(Equal(Local(0),7)) return("Yellow2");
  if(Equal(Local(0),8)) return("White");
  if(Equal(Local(0),9)) return("Brown");
  return("Blue1");
