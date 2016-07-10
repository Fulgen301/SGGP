#strict

#appendto HZCK

private func Control2Contents (string command, par1, par2, par3, par4)
{
  if(GetAction() S= "Push")
    return(0);
  if(ObjectCall(Contents(), command, this(), par1, par2, par3, par4))
    return(1);
  return(0);
}