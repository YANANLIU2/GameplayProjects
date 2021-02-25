#pragma once

#include "ObjBase.h"
class Tile :
	public ObjBase
{
public:
	static AnimationPair animation_;

	Tile(size_t index, size_t columnNum, size_t rowNum, size_t colth, size_t rowth);
	~Tile() = default;
	HBITMAP GethBmp() override;
	BITMAP GetBitmap() override;
};

