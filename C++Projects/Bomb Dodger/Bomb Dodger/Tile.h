#pragma once
#include "ObjBase.h"
#include "GameSettings.h"

// The script is for defining a basic tile in a tiled-map
class Tile :
	public ObjBase
{
public:
	// The render image of a map
	static vector<AnimationPair> animation_vec_;

	// Constructor
	Tile(size_t index, size_t columnNum, size_t rowNum, size_t colth, size_t rowth) :ObjBase()
	{
		x_size_ = GAME_WIDTH / (int)columnNum;
		y_size_ = GAME_HEIGHT / (int)rowNum;
		x_ = float(colth * x_size_);
		y_ = float(rowth * y_size_);
	}

	// Destructor
	~Tile() = default;

	// Get tile image's h-bitmap
	HBITMAP GethBmp() override { return animation_vec_[0].first; }
	
	// Get tile image's bitmap
	BITMAP GetBitmap() override { return animation_vec_[0].second; }
};
