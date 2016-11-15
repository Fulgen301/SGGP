

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
local ActMap = {
Tabel = {
Prototype = Action,
Name = "Tabel",
Delay = 3,
Length = 14,
X = 0,
Y = 0,
Wdt = 18,
Hgt = 11,
NextAction = "Tabel",
},
RedCurved1 = {
Prototype = Action,
Name = "RedCurved1",
Delay = 500,
Directions = 2,
Length = 1,
X = 0,
Y = 14,
Wdt = 11,
Hgt = 11,
NextAction = "RedCurved1",
},
RedCurved2 = {
Prototype = Action,
Name = "RedCurved2",
Delay = 500,
Directions = 2,
Length = 1,
X = 11,
Y = 14,
Wdt = 11,
Hgt = 11,
NextAction = "RedCurved2",
},
RedLongHor = {
Prototype = Action,
Name = "RedLongHor",
Delay = 500,
Length = 1,
X = 0,
Y = 11,
Wdt = 21,
Hgt = 3,
NextAction = "RedLongHor",
},
RedLongVert = {
Prototype = Action,
Name = "RedLongVert",
Delay = 500,
Length = 1,
X = 35,
Y = 11,
Wdt = 3,
Hgt = 21,
NextAction = "RedLongVert",
},
RedSmallHor = {
Prototype = Action,
Name = "RedSmallHor",
Delay = 500,
Length = 1,
X = 0,
Y = 38,
Wdt = 5,
Hgt = 1,
NextAction = "RedSmallHor",
},
RedSmallVert = {
Prototype = Action,
Name = "RedSmallVert",
Delay = 500,
Length = 1,
X = 5,
Y = 36,
Wdt = 1,
Hgt = 5,
NextAction = "RedSmallVert",
},
RedX = {
Prototype = Action,
Name = "RedX",
Delay = 500,
Length = 1,
X = 0,
Y = 41,
Wdt = 9,
Hgt = 10,
NextAction = "RedX",
},
RedTHor = {
Prototype = Action,
Name = "RedTHor",
Delay = 500,
Directions = 2,
Length = 1,
X = 22,
Y = 11,
Wdt = 13,
Hgt = 14,
NextAction = "RedTHor",
},
RedTVertRight = {
Prototype = Action,
Name = "RedTVertRight",
Delay = 500,
Length = 1,
X = 38,
Y = 11,
Wdt = 9,
Hgt = 13,
NextAction = "RedTVertRight",
},
RedTVertLeft = {
Prototype = Action,
Name = "RedTVertLeft",
Delay = 500,
Length = 1,
X = 43,
Y = 24,
Wdt = 9,
Hgt = 13,
NextAction = "RedTVertLeft",
},
RedPult1 = {
Prototype = Action,
Name = "RedPult1",
Delay = 500,
Length = 1,
X = 13,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "RedPult1",
},
RedPult2 = {
Prototype = Action,
Name = "RedPult2",
Delay = 500,
Length = 1,
X = 19,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "RedPult2",
},
RedPult3 = {
Prototype = Action,
Name = "RedPult3",
Delay = 500,
Length = 1,
X = 25,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "RedPult3",
},
RedPult4 = {
Prototype = Action,
Name = "RedPult4",
Delay = 500,
Length = 1,
X = 31,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "RedPult4",
},
RedPult5 = {
Prototype = Action,
Name = "RedPult5",
Delay = 500,
Length = 1,
X = 37,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "RedPult5",
},
RedPult6 = {
Prototype = Action,
Name = "RedPult6",
Delay = 500,
Length = 1,
X = 43,
Y = 37,
Wdt = 6,
Hgt = 14,
NextAction = "RedPult6",
},
RedPult7 = {
Prototype = Action,
Name = "RedPult7",
Delay = 500,
Length = 1,
X = 49,
Y = 43,
Wdt = 7,
Hgt = 8,
NextAction = "RedPult7",
},
RedPult8 = {
Prototype = Action,
Name = "RedPult8",
Delay = 500,
Length = 1,
X = 56,
Y = 43,
Wdt = 10,
Hgt = 8,
NextAction = "RedPult8",
},
RedPult9 = {
Prototype = Action,
Name = "RedPult9",
Delay = 500,
Length = 1,
X = 66,
Y = 43,
Wdt = 7,
Hgt = 8,
NextAction = "RedPult9",
},
RedEndHor = {
Prototype = Action,
Name = "RedEndHor",
Delay = 500,
Directions = 2,
Length = 1,
X = 47,
Y = 11,
Wdt = 6,
Hgt = 3,
NextAction = "RedEndHor",
},
RedEndVertDown = {
Prototype = Action,
Name = "RedEndVertDown",
Delay = 500,
Length = 1,
X = 53,
Y = 11,
Wdt = 3,
Hgt = 6,
NextAction = "RedEndVertDown",
},
RedEndVertUp = {
Prototype = Action,
Name = "RedEndVertUp",
Delay = 500,
Length = 1,
X = 56,
Y = 11,
Wdt = 3,
Hgt = 6,
NextAction = "RedEndVertUp",
},
RedCurved3 = {
Prototype = Action,
Name = "RedCurved3",
Delay = 500,
Directions = 2,
Length = 1,
X = 52,
Y = 17,
Wdt = 11,
Hgt = 11,
NextAction = "RedCurved3",
},
RedCurved4 = {
Prototype = Action,
Name = "RedCurved4",
Delay = 500,
Directions = 2,
Length = 1,
X = 63,
Y = 17,
Wdt = 11,
Hgt = 11,
NextAction = "RedCurved4",
},
RedTreeHorUp = {
Prototype = Action,
Name = "RedTreeHorUp",
Delay = 500,
Length = 1,
X = 59,
Y = 11,
Wdt = 17,
Hgt = 6,
NextAction = "TreeHorUp",
},
RedTreeHorDown = {
Prototype = Action,
Name = "RedTreeHorDown",
Delay = 500,
Length = 1,
X = 76,
Y = 11,
Wdt = 17,
Hgt = 6,
NextAction = "RedTreeHorDown",
},
RedTreeVertLeft = {
Prototype = Action,
Name = "RedTreeVertLeft",
Delay = 500,
Length = 1,
X = 74,
Y = 17,
Wdt = 6,
Hgt = 17,
NextAction = "RedTreeVertLeft",
},
RedTreeVertRight = {
Prototype = Action,
Name = "RedTreeVertRight",
Delay = 500,
Length = 1,
X = 80,
Y = 17,
Wdt = 6,
Hgt = 17,
NextAction = "RedTreeVertRight",
},
GreyCurved1 = {
Prototype = Action,
Name = "GreyCurved1",
Delay = 500,
Directions = 2,
Length = 1,
X = 93,
Y = 14,
Wdt = 11,
Hgt = 11,
NextAction = "GreyCurved1",
},
GreyCurved2 = {
Prototype = Action,
Name = "GreyCurved2",
Delay = 500,
Directions = 2,
Length = 1,
X = 104,
Y = 14,
Wdt = 11,
Hgt = 11,
NextAction = "GreyCurved2",
},
GreyLongHor = {
Prototype = Action,
Name = "GreyLongHor",
Delay = 500,
Length = 1,
X = 93,
Y = 11,
Wdt = 21,
Hgt = 3,
NextAction = "GreyLongHor",
},
GreyLongVert = {
Prototype = Action,
Name = "GreyLongVert",
Delay = 500,
Length = 1,
X = 128,
Y = 11,
Wdt = 3,
Hgt = 21,
NextAction = "GreyLongVert",
},
GreySmallHor = {
Prototype = Action,
Name = "GreySmallHor",
Delay = 500,
Length = 1,
X = 93,
Y = 38,
Wdt = 5,
Hgt = 1,
NextAction = "GreySmallHor",
},
GreySmallVert = {
Prototype = Action,
Name = "GreySmallVert",
Delay = 500,
Length = 1,
X = 98,
Y = 36,
Wdt = 1,
Hgt = 5,
NextAction = "GreySmallVert",
},
GreyX = {
Prototype = Action,
Name = "GreyX",
Delay = 500,
Length = 1,
X = 93,
Y = 41,
Wdt = 9,
Hgt = 10,
NextAction = "GreyX",
},
GreyTHor = {
Prototype = Action,
Name = "GreyTHor",
Delay = 500,
Directions = 2,
Length = 1,
X = 115,
Y = 11,
Wdt = 13,
Hgt = 14,
NextAction = "GreyTHor",
},
GreyTVertRight = {
Prototype = Action,
Name = "GreyTVertRight",
Delay = 500,
Length = 1,
X = 131,
Y = 11,
Wdt = 9,
Hgt = 13,
NextAction = "GreyTVertRight",
},
GreyTVertLeft = {
Prototype = Action,
Name = "GreyTVertLeft",
Delay = 500,
Length = 1,
X = 136,
Y = 24,
Wdt = 9,
Hgt = 13,
NextAction = "GreyTVertLeft",
},
GreyPult1 = {
Prototype = Action,
Name = "GreyPult1",
Delay = 500,
Length = 1,
X = 106,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "GreyPult1",
},
GreyPult2 = {
Prototype = Action,
Name = "GreyPult2",
Delay = 500,
Length = 1,
X = 102,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "GreyPult2",
},
GreyPult3 = {
Prototype = Action,
Name = "GreyPult3",
Delay = 500,
Length = 1,
X = 118,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "GreyPult3",
},
GreyPult4 = {
Prototype = Action,
Name = "GreyPult4",
Delay = 500,
Length = 1,
X = 124,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "GreyPult4",
},
GreyPult5 = {
Prototype = Action,
Name = "GreyPult5",
Delay = 500,
Length = 1,
X = 130,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "GreyPult5",
},
GreyPult6 = {
Prototype = Action,
Name = "GreyPult6",
Delay = 500,
Length = 1,
X = 136,
Y = 37,
Wdt = 6,
Hgt = 14,
NextAction = "GreyPult6",
},
GreyPult7 = {
Prototype = Action,
Name = "GreyPult7",
Delay = 500,
Length = 1,
X = 142,
Y = 43,
Wdt = 7,
Hgt = 8,
NextAction = "GreyPult7",
},
GreyPult8 = {
Prototype = Action,
Name = "GreyPult8",
Delay = 500,
Length = 1,
X = 149,
Y = 43,
Wdt = 10,
Hgt = 8,
NextAction = "GreyPult8",
},
GreyPult9 = {
Prototype = Action,
Name = "GreyPult9",
Delay = 500,
Length = 1,
X = 159,
Y = 43,
Wdt = 7,
Hgt = 8,
NextAction = "GreyPult9",
},
GreyEndHor = {
Prototype = Action,
Name = "GreyEndHor",
Delay = 500,
Directions = 2,
Length = 1,
X = 140,
Y = 11,
Wdt = 6,
Hgt = 3,
NextAction = "GreyEndHor",
},
GreyEndVertDown = {
Prototype = Action,
Name = "GreyEndVertDown",
Delay = 500,
Length = 1,
X = 146,
Y = 11,
Wdt = 3,
Hgt = 6,
NextAction = "GreyEndVertDown",
},
GreyEndVertUp = {
Prototype = Action,
Name = "GreyEndVertUp",
Delay = 500,
Length = 1,
X = 149,
Y = 11,
Wdt = 3,
Hgt = 6,
NextAction = "GreyEndVertUp",
},
GreyCurved3 = {
Prototype = Action,
Name = "GreyCurved3",
Delay = 500,
Directions = 2,
Length = 1,
X = 145,
Y = 17,
Wdt = 11,
Hgt = 11,
NextAction = "GreyCurved3",
},
GreyCurved4 = {
Prototype = Action,
Name = "GreyCurved4",
Delay = 500,
Directions = 2,
Length = 1,
X = 156,
Y = 17,
Wdt = 11,
Hgt = 11,
NextAction = "GreyCurved4",
},
GreyTreeHorUp = {
Prototype = Action,
Name = "GreyTreeHorUp",
Delay = 500,
Length = 1,
X = 152,
Y = 11,
Wdt = 17,
Hgt = 6,
NextAction = "TreeHorUp",
},
GreyTreeHorDown = {
Prototype = Action,
Name = "GreyTreeHorDown",
Delay = 500,
Length = 1,
X = 169,
Y = 11,
Wdt = 17,
Hgt = 6,
NextAction = "GreyTreeHorDown",
},
GreyTreeVertLeft = {
Prototype = Action,
Name = "GreyTreeVertLeft",
Delay = 500,
Length = 1,
X = 167,
Y = 17,
Wdt = 6,
Hgt = 17,
NextAction = "GreyTreeVertLeft",
},
GreyTreeVertRight = {
Prototype = Action,
Name = "GreyTreeVertRight",
Delay = 500,
Length = 1,
X = 173,
Y = 17,
Wdt = 6,
Hgt = 17,
NextAction = "RedTreeVertRight",
},
BlueCurved1 = {
Prototype = Action,
Name = "BlueCurved1",
Delay = 500,
Directions = 2,
Length = 1,
X = 186,
Y = 14,
Wdt = 11,
Hgt = 11,
NextAction = "BlueCurved1",
},
BlueCurved2 = {
Prototype = Action,
Name = "BlueCurved2",
Delay = 500,
Directions = 2,
Length = 1,
X = 197,
Y = 14,
Wdt = 11,
Hgt = 11,
NextAction = "BlueCurved2",
},
BlueLongHor = {
Prototype = Action,
Name = "BlueLongHor",
Delay = 500,
Length = 1,
X = 186,
Y = 11,
Wdt = 21,
Hgt = 3,
NextAction = "BlueLongHor",
},
BlueLongVert = {
Prototype = Action,
Name = "BlueLongVert",
Delay = 500,
Length = 1,
X = 221,
Y = 11,
Wdt = 3,
Hgt = 21,
NextAction = "BlueLongVert",
},
BlueSmallHor = {
Prototype = Action,
Name = "BlueSmallHor",
Delay = 500,
Length = 1,
X = 186,
Y = 38,
Wdt = 5,
Hgt = 1,
NextAction = "BlueSmallHor",
},
BlueSmallVert = {
Prototype = Action,
Name = "BlueSmallVert",
Delay = 500,
Length = 1,
X = 191,
Y = 36,
Wdt = 1,
Hgt = 5,
NextAction = "BlueSmallVert",
},
BlueX = {
Prototype = Action,
Name = "BlueX",
Delay = 500,
Length = 1,
X = 186,
Y = 41,
Wdt = 9,
Hgt = 10,
NextAction = "BlueX",
},
BlueTHor = {
Prototype = Action,
Name = "BlueTHor",
Delay = 500,
Directions = 2,
Length = 1,
X = 208,
Y = 11,
Wdt = 13,
Hgt = 14,
NextAction = "BlueTHor",
},
BlueTVertRight = {
Prototype = Action,
Name = "BlueTVertRight",
Delay = 500,
Length = 1,
X = 224,
Y = 11,
Wdt = 9,
Hgt = 13,
NextAction = "BlueTVertRight",
},
BlueTVertLeft = {
Prototype = Action,
Name = "BlueTVertLeft",
Delay = 500,
Length = 1,
X = 229,
Y = 24,
Wdt = 9,
Hgt = 13,
NextAction = "BlueTVertLeft",
},
BluePult1 = {
Prototype = Action,
Name = "BluePult1",
Delay = 500,
Length = 1,
X = 199,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "BluePult1",
},
BluePult2 = {
Prototype = Action,
Name = "BluePult2",
Delay = 500,
Length = 1,
X = 205,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "BluePult2",
},
BluePult3 = {
Prototype = Action,
Name = "BluePult3",
Delay = 500,
Length = 1,
X = 211,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "BluePult3",
},
BluePult4 = {
Prototype = Action,
Name = "BluePult4",
Delay = 500,
Length = 1,
X = 217,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "BluePult4",
},
BluePult5 = {
Prototype = Action,
Name = "BluePult5",
Delay = 500,
Length = 1,
X = 223,
Y = 36,
Wdt = 6,
Hgt = 15,
NextAction = "BluePult5",
},
BluePult6 = {
Prototype = Action,
Name = "BluePult6",
Delay = 500,
Length = 1,
X = 229,
Y = 37,
Wdt = 6,
Hgt = 14,
NextAction = "BluePult6",
},
BluePult7 = {
Prototype = Action,
Name = "BluePult7",
Delay = 500,
Length = 1,
X = 235,
Y = 43,
Wdt = 7,
Hgt = 8,
NextAction = "BluePult7",
},
BluePult8 = {
Prototype = Action,
Name = "BluePult8",
Delay = 500,
Length = 1,
X = 242,
Y = 43,
Wdt = 10,
Hgt = 8,
NextAction = "BluePult8",
},
BluePult9 = {
Prototype = Action,
Name = "BluePult9",
Delay = 500,
Length = 1,
X = 252,
Y = 43,
Wdt = 7,
Hgt = 8,
NextAction = "BluePult9",
},
BlueEndHor = {
Prototype = Action,
Name = "BlueEndHor",
Delay = 500,
Directions = 2,
Length = 1,
X = 233,
Y = 11,
Wdt = 6,
Hgt = 3,
NextAction = "BlueEndHor",
},
BlueEndVertDown = {
Prototype = Action,
Name = "BlueEndVertDown",
Delay = 500,
Length = 1,
X = 239,
Y = 11,
Wdt = 3,
Hgt = 6,
NextAction = "BlueEndVertDown",
},
BlueEndVertUp = {
Prototype = Action,
Name = "BlueEndVertUp",
Delay = 500,
Length = 1,
X = 242,
Y = 11,
Wdt = 3,
Hgt = 6,
NextAction = "BlueEndVertUp",
},
BlueCurved3 = {
Prototype = Action,
Name = "BlueCurved3",
Delay = 500,
Directions = 2,
Length = 1,
X = 238,
Y = 17,
Wdt = 11,
Hgt = 11,
NextAction = "BlueCurved3",
},
BlueCurved4 = {
Prototype = Action,
Name = "BlueCurved4",
Delay = 500,
Directions = 2,
Length = 1,
X = 249,
Y = 17,
Wdt = 11,
Hgt = 11,
NextAction = "BlueCurved4",
},
BlueTreeHorUp = {
Prototype = Action,
Name = "BlueTreeHorUp",
Delay = 500,
Length = 1,
X = 245,
Y = 11,
Wdt = 17,
Hgt = 6,
NextAction = "BlueTreeHorUp",
},
BlueTreeHorDown = {
Prototype = Action,
Name = "BlueTreeHorDown",
Delay = 500,
Length = 1,
X = 262,
Y = 11,
Wdt = 17,
Hgt = 6,
NextAction = "BlueTreeHorDown",
},
BlueTreeVertLeft = {
Prototype = Action,
Name = "BlueTreeVertLeft",
Delay = 500,
Length = 1,
X = 260,
Y = 17,
Wdt = 6,
Hgt = 17,
NextAction = "BlueTreeVertLeft",
},
BlueTreeVertRight = {
Prototype = Action,
Name = "BlueTreeVertRight",
Delay = 500,
Length = 1,
X = 266,
Y = 17,
Wdt = 6,
Hgt = 17,
NextAction = "BlueTreeVertRight",
},
Rohr = {
Prototype = Action,
Name = "Rohr",
Delay = 500,
Directions = 2,
Length = 1,
X = 279,
Y = 0,
Wdt = 34,
Hgt = 9,
NextAction = "Rohr",
},
RohrVert1 = {
Prototype = Action,
Name = "RohrVert1",
Delay = 500,
Length = 1,
X = 279,
Y = 18,
Wdt = 8,
Hgt = 17,
NextAction = "RohrVert1",
},
RohrVert2 = {
Prototype = Action,
Name = "RohrVert2",
Delay = 500,
Length = 1,
X = 289,
Y = 18,
Wdt = 8,
Hgt = 17,
NextAction = "RohrVert2",
},
RohrVert3 = {
Prototype = Action,
Name = "RohrVert3",
Delay = 500,
Length = 1,
X = 314,
Y = 0,
Wdt = 8,
Hgt = 34,
NextAction = "RohrVert3",
},
Rad1 = {
Prototype = Action,
Name = "Rad1",
Delay = 500,
Directions = 2,
Length = 1,
X = 252,
Y = 0,
Wdt = 5,
Hgt = 5,
NextAction = "Rad3",
},
Rad2 = {
Prototype = Action,
Name = "Rad2",
Delay = 500,
Directions = 2,
Length = 1,
X = 257,
Y = 0,
Wdt = 5,
Hgt = 2,
NextAction = "Rad2",
},
Rad3 = {
Prototype = Action,
Name = "Rad3",
Delay = 500,
Directions = 2,
Length = 1,
X = 257,
Y = 4,
Wdt = 2,
Hgt = 5,
NextAction = "Rad3",
},
Rad4 = {
Prototype = Action,
Name = "Rad4",
Delay = 500,
Length = 1,
X = 259,
Y = 4,
Wdt = 2,
Hgt = 5,
NextAction = "Rad4",
},
Loch = {
Prototype = Action,
Name = "Loch",
Delay = 20,
Length = 1,
X = 262,
Y = 0,
Wdt = 2,
Hgt = 2,
NextAction = "Loch",
EndCall = "Leck",
},  };
local Name = "Rohre";
