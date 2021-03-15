#include "stdafx.h"
#include "ObjBase.h"

void ObjBase::Move(MyVector2<float> dir)
{
	pos_ += dir * speed_;
}

void ObjBase::Update()
{
	pos_ += speed_;

	OutofBox();
}

void ObjBase::Draw(HDC& hdc, HDC& hdcMemory, HBITMAP hBmp, BITMAP bmp)
{
	TransparentBlt(hdcMemory, (int)pos_.x_, (int)pos_.y_, (int)size_.x_, (int)size_.y_,hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, 0x00ffffff);
}
