/*-- Hyperspace --*/

#strict 2

global func HyperdriveWindow(int iX, int iY, int iSize, int iXTo, int iYTo, object pObj)
{
	if (!pObj)
		pObj = this;
	var pWindow;
	pWindow = pObj->CreateObject(HYFE, iX, iY);
	pWindow->SetSize(iSize);
	pWindow->SetPos(iXTo, iYTo, iX + GetX(pObj), iY + GetY(pObj));
	pWindow->SetObjectDir(pObj);
}