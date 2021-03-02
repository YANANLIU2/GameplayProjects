#include "stdafx.h"
#include "Coin.h"

vector<AnimationPair> Coin::animation_vec_(6);

Coin::Coin(float x, float y) : Actor()
{
	// Size
	x_size_ = 16;

	y_size_ = 16;

	// Position
	x_ = x;

	y_ = y;

	// Rect
	hitbox_offset_ = MyRect(0, 0, 0, 0);

	UpdateRect();

	// Timer
	animation_timer_.set_time(0.011);
}

void Coin::Update()
{
	ObjBase::Update();

	// Animation
	UpdateAnimationIndex(animation_vec_.size(), true);

	// Check whether the position valid or not
	IsOutOfScreen(false);

	// Update rects
	UpdateRect();
}

HBITMAP Coin::GethBmp()
{
	return animation_vec_[animation_index_].first;
}

BITMAP Coin::GetBitmap()
{
	return animation_vec_[animation_index_].second;
}
