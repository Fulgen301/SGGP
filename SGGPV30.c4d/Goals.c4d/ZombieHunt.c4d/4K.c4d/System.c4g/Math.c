#strict

//Interpoliert einen Wert.
global func Interpolate4K(y1,y2,x1,x2,x3)
{
  return(y1 + ((y2 - y1)/(x2 - x1)) * (x3 - x1));
}

//*faul* Alte Funktion.
global func Interpolate(y1,y2,x1,x2,x3)
{
  return(Interpolate4K(y1,y2,x1,x2,x3));
}


//Interpoliert 2 Farben.
global func InterpolateRGBa(RGBa_1,RGBa_2,x1,x2,x3)
{
  var r = Interpolate(GetRGBaValue(RGBa_1,1),GetRGBaValue (RGBa_2,1),x1,x2,x3);
  var g = Interpolate(GetRGBaValue(RGBa_1,2),GetRGBaValue (RGBa_2,2),x1,x2,x3);
  var b = Interpolate(GetRGBaValue(RGBa_1,3),GetRGBaValue (RGBa_2,3),x1,x2,x3);
  var a = Interpolate(GetRGBaValue(RGBa_1,0),GetRGBaValue (RGBa_2,0),x1,x2,x3);

  return(RGBa(r,g,b,a));
}

//Interpoliert 3 Farben.
global func InterpolateRGBa2(RGBa_1,RGBa_2,RGBa_3,x1,x2,x3)
{
  if(x3 <= x2/2)
    return(InterpolateRGBa(RGBa_1,RGBa_2,x1,Average4K(x1,x2),x3));
  else
    return(InterpolateRGBa(RGBa_2,RGBa_3,Average4K(x1,x2),x2,x3));
}

//Gibt den Duchschnittswert zur�ck.
global func Average4K(int A, int B)
{
  return((B-A)/2+A);
}

//Normalisiert die angegeben Werte.
global func Normalize4K(int &a,int &b)
{
  if(!a || !b) return();
  if(a > b)
  {
    a = a/b;
    b = 1;
  }
  else
  {
    b = b/a;
    a = 1;
  }
}

//Operatoren mit Nachkommastellen.
global func Mul4K(int iVal1, int iVal2, int iPrec)
{
  return(( iVal1 * iVal2 ) / iPrec);
}

global func Div4K(int iVal1, int iVal2, int iPrec)
{
  return(( iVal1 / iVal2 ) / iPrec);
}

global func Add4K(int iVal1, int iVal2, int iPrec)
{
  return(( iVal1 + iVal2 ) / iPrec);
}

global func Sub4K(int iVal1, int iVal2, int iPrec)
{
  return(( iVal1 - iVal2 ) / iPrec);
}

global func Wrap4K(int iValue, int iMin, int iMax)
{
  if(iValue >= iMax)
    iMax++;
    
  if(iValue <= iMin)
    iMin--;//:/
    
  iValue %= iMax-iMin;
  return(iValue);
  
  /*
  if(iValue < iMin)
    return(iMax-(iMin-iValue)+1);
    
  if(iValue > iMax)
    return(iMin+(iValue-iMax)-1);
    
  return(iValue);*/
}