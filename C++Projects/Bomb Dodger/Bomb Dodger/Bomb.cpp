#include "stdafx.h"
#include "Bomb.h"

vector<AnimationPair> Bomb::animation_vec_(6);
const int Bomb::kDamage = 1;
const double Bomb::kAnimationTime = 0.031;

Bomb::Bomb(ObjBase* player, EDirection spawnDirection)
	:ObjBase()
{
	switch (spawnDirection)
	{
	case EDirection::kDown:
		x_ = player->get_x() + player->get_x_size()/2 - x_size_ / 2;
		y_ = player->get_y() + player->get_y_size();
		break;
	case EDirection::kLeft:
		x_ = player->get_x() - player->get_x_size() / 2 - x_size_;
		y_ = player->get_y() - y_size_ / 2;
		break;
	case EDirection::kRight:
		x_ = player->get_x() + player->get_x_size();
		y_ = player->get_y() - y_size_ / 2;
		break;
	case EDirection::kUp:
		x_ = player->get_x() + player->get_x_size() / 2 - x_size_ / 2;
		y_ = player->get_y() - y_size_;
		break;
	default:
		x_ = player->get_x() + player->get_x_size() / 2 - x_size_ / 2;
		y_ = player->get_y() - y_size_;
		break;
	}
	
	x_size_ = kXSize;
	y_size_ = kYSize;
	direction_ = spawnDirection;
	max_speed_ = 1;
	acc_rate_ = 0.5;
	timer_.set_time(kAnimationTime);
}

void Bomb::Update()
{
	ObjBase::Update();
	UpdateAnimationIndex(animation_vec_.size(), false);
	Move();
	rect_.set_rect(x_ + x_size_, y_ + y_size_, x_, y_);
}

HBITMAP Bomb::GethBmp()
{
	return animation_vec_[animation_index_].first;
}

BITMAP Bomb::GetBitmap()
{
	return animation_vec_[animation_index_].second;
}

