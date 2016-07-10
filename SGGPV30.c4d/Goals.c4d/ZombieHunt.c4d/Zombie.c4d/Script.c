// Zombie Clonk
// Author: Jeason

#strict

#include CLNK

local gate;
local gatepos;

protected func Hurt()
{
  Sound("UHurt*");
  return(1);
}

protected func Death()
{
  Sound("UDie*");
  return(1);
}

func IsBulletTarget()    { return(1); }

func Check()
{
  if(FindObject(STGT,-300,-300,600,600,OCF_InFree(),"Worm"))
  {
   gate = FindObject(STGT,-300,-300,600,600,OCF_InFree(),"Worm");
  }
  
  if(gate)
  {
   if(!LocalN("pFrom",gate))
   {
    if((GetX() - GetX(gate)) < 0)
    {
     SetComDir(COMD_Right());
    }
    
    if((GetX() - GetX(gate)) > 0)
    {
     SetComDir(COMD_Left());
    }
   }
  }

  if(FindContents(NVDN))
  {
   FindContents(NVDN)->Activate(this());
  }

  if(FindContents(MEDI))
  {
   FindContents(MEDI)->Activate(this());
  }
  
  if(FindContents(HEGR))
  {
   FindContents(HEGR)->Activate(Contained());
  }

  if(FindObject(HEGR,-50,-50,100,100))
  {
   if((GetX() - GetX(FindObject(HEGR,-50,-50,100,100,OCF_InFree(),"Scharf"))) < 0)
   {
    SetComDir(COMD_Left());
    return(1);
   }
   
   if((GetX() - GetX(FindObject(HEGR,-50,-50,100,100,OCF_InFree(),"Scharf"))) > 0)
   {
    SetComDir(COMD_Right());
    return(1);
   }
  }
  
  return(1);
}