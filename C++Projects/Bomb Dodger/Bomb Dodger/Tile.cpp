#include "stdafx.h"
#include "Tile.h"
#include "GameSettings.h"

AnimationPair Tile::animation_;

Tile::Tile(size_t index, size_t columnNum, size_t rowNum, size_t colth, size_t rowth)
	:ObjBase()
{
	x_size_ = GAME_WIDTH/ (int)columnNum;
	y_size_ = GAME_HEIGHT/ (int)rowNum;
	x_ = float(colth * x_size_);
	y_ = float(rowth * y_size_);
}

HBITMAP Tile::GethBmp()
{
	return animation_.first;
}

BITMAP Tile::GetBitmap()
{
	return animation_.second;
}

