/*--Ambiente--*/



local stNameOfTitel;
local RndDelay;
local Volume;

local pText;
protected func Initialize(){
 RndDelay = 20;
 Volume = 100;
 return(1);
}
public func IsGameDing(){  return(1); }

protected func SetNewTitel(string NewTitel, int NewDelay, int NewVolume) {  return(stNameOfTitel = NewTitel,RndDelay = NewDelay, Volume = NewVolume); }

protected func Timer(){
 if(!pText){
 pText = CreateObject(TBHD,0,0,-1);
 pText -> GetTarget(this());
  }
 Message("Abiente:%s",pText,stNameOfTitel);
 if(!Random(RndDelay))

 Sound(Format("%s",stNameOfTitel),0,this(),Volume,0,0);
 
  return(1);
  }
local Name = "Ambiente";
