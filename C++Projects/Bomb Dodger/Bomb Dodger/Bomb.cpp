#include "stdafx.h"
#include "Bomb.h"

vector<AnimationPair> Bomb::animation_vec_(6);
const int Bomb::kDamage = 1;
const double Bomb::kAnimationTime = 0.031;

Bomb::Bomb(float x, float y, EDirection dir) :Actor()
{
	// Position
	x_ = x;
	y_ = y;

	// Size
	x_size_ = 13;
	y_size_ = 16;

	// Hitbox
	hitbox_offset_ = MyRect(-2, -2, 2, 2);

	// Movement
	max_speed_ = 2;
	acceleration_ = 2;
	acceleration_ = 2;
	direction_ = dir;

	// Timer
	animation_timer_.set_time(kAnimationTime);
}

void Bomb::Update()
{
	ObjBase::Update();
	UpdateAnimationIndex(animation_vec_.size(), false);
	Move();
	UpdateRect();
}

HBITMAP Bomb::GethBmp()
{
	return animation_vec_[animation_index_].first;
}

BITMAP Bomb::GetBitmap()
{
	return animation_vec_[animation_index_].second;
}

