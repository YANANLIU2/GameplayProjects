#include "stdafx.h"
#include "ObjBase.h"
#include "MoveCommand.h"
#include "Bomb.h"
#include "GameSettings.h"

void ObjBase::StopMoving()
{
	x_acceleration_ = 0;
	y_acceleration_ = 0;
	x_speed_ = 0;
	y_speed_ = 0;
}

void ObjBase::UpdateRect()
{
	rect_.set_rect(x_ + x_size_, y_ + y_size_, x_, y_);
}

bool ObjBase::IsOutOfScreen(bool isAllowed)
{
	if (x_ < 0)
	{
		if (!isAllowed)
		{
			x_ = 0;
		}
		return true;
	}
	else if (x_ + x_size_ > GAME_WIDTH)
	{
		if (!isAllowed)
		{
			x_ = float(GAME_WIDTH - x_size_);
		}
		return true;
	}

	if (y_ < 0)
	{
		if (!isAllowed)
		{
			y_ = 0;

		}
		return true;
	}
	else if (y_ + y_size_ > GAME_HEIGHT)
	{
		if (!isAllowed)
		{
			y_ = float(GAME_HEIGHT - y_size_);
		}
		return true;
	}
	return false;
}



void ObjBase::Move()
{
	if (direction_ == EDirection::kDown || direction_ == EDirection::kUp)
	{
		y_acceleration_ += acc_rate_;
		y_speed_ += y_acceleration_;
	}
	else if (direction_ == EDirection::kLeft || direction_ == EDirection::kRight)
	{
		x_acceleration_ += acc_rate_;
		x_speed_ += x_acceleration_;
	}

	//speed limitation
	if (x_speed_ > max_speed_)
	{
		x_speed_ = max_speed_;
	}
	else if (y_speed_ > max_speed_)
	{
		y_speed_ = max_speed_;
	}	

	switch (direction_)
	{
	case EDirection::kDown:
		y_ += y_speed_;
		break;

	case EDirection::kLeft:
		x_ -= x_speed_;
		break;

	case EDirection::kRight:
		x_ += x_speed_;
		break;

	case EDirection::kUp:
		y_ -= y_speed_;
		break;

	case EDirection::kStop:
		this->StopMoving();
		break;

	default:
		break;
	}
}

void ObjBase::DrawTransparent(HDC & hdcScreen, HDC & hdcMemory, int transparent)
{
	//draw the obj
	HDC theDc = CreateCompatibleDC(hdcScreen);

	SelectObject(theDc, this->GethBmp());

	TransparentBlt(hdcMemory, (int)x_, (int)y_, x_size_, y_size_, theDc, 0, 0,
		GetBitmap().bmWidth, GetBitmap().bmHeight, transparent);

	DeleteDC(theDc);
}

void ObjBase::DrawAll(HDC & hdcScreen, HDC & hdcMemory)
{
	//draw the obj
	HDC theDc = CreateCompatibleDC(hdcScreen);

	SelectObject(theDc, this->GethBmp());

	StretchBlt(hdcMemory, (int)x_, (int)y_, x_size_, y_size_,
		theDc, 0, 0, GetBitmap().bmWidth, GetBitmap().bmHeight, SRCCOPY);

	DeleteDC(theDc);
}

void ObjBase::UpdateAnimationIndex(size_t animationSize, bool isLoop)
{
	// Update animation
	if (timer_.IsTimerOver())
	{
		animation_index_++;
		if (animation_index_ >= animationSize )
		{
			animation_index_ = isLoop ? 0 : animationSize - 1;
		}
	}
}



