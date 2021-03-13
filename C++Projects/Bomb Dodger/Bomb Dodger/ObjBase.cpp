#include "stdafx.h"
#include "ObjBase.h"
#include "Bomb.h"

void ObjBase::DrawTransparent(HDC & hdcScreen, HDC & hdcMemory, int transparent)
{
	HDC theDc = CreateCompatibleDC(hdcScreen);

 	SelectObject(theDc, this->GethBmp());

	TransparentBlt(hdcMemory, (int)x_, (int)y_, (int)x_size_, (int)y_size_, theDc, 0, 0, GetBitmap().bmWidth, GetBitmap().bmHeight, transparent);

	DeleteDC(theDc);
}

void ObjBase::DrawAll(HDC & hdcScreen, HDC & hdcMemory)
{
	HDC theDc = CreateCompatibleDC(hdcScreen);

	SelectObject(theDc, this->GethBmp());

	StretchBlt(hdcMemory, (int)x_, (int)y_, (int)x_size_, (int)y_size_, theDc, 0, 0, GetBitmap().bmWidth, GetBitmap().bmHeight, SRCCOPY);

	DeleteDC(theDc);
}

void ObjBase::LoadImages(HINSTANCE hInstance, vector<AnimationPair>& animationVec, int startIDB, int endIDB)
{
	for (int i = startIDB, j = 0; i <= endIDB; i++, j++)
	{
		animationVec[j].first = LoadBitmap(hInstance, MAKEINTRESOURCE(i));

		GetObject(animationVec[j].first, sizeof(animationVec[j].second), &animationVec[j].second);
	}
}






