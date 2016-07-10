#strict

SetSize:
  DoCon(Sub(Div(Mul(Par(0),100),100),100));
  SetLocal(0,Par(0));
  SetVar(0,Mul(Div(Sub(100,Div(Mul(100,GetCon()),100)),2),-1));
  SetPosition(GetX(),Sum(GetY(),Var(0)));
  return(1);

Initialize:
  SetLocal(0,100);
  return(1);  