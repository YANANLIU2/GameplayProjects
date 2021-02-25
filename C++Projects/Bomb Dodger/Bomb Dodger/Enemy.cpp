#include <stdlib.h>     /* srand, rand */

#include "stdafx.h"
#include "Enemy.h"
#include "FrameTimer.h"
#include "Player.h"
vector<AnimationPair> Enemy::animation_vec_(10);

Enemy::Enemy(std::shared_ptr<Player> player, float x, float y) : ObjBase(), hp_(kMaxHp), player_(player)
{
	x_size_ = kXSize;
	y_size_ = kYSize;
	max_speed_ = 0.5;
	acc_rate_ = 0.25;
	x_ = x;
	y_ = y;
	UpdateRect();
	timer_.set_time(kAnimationTime);
}

void Enemy::Update()
{
	ObjBase::Update();
	UpdateAnimationIndex(animation_vec_.size(), kAnimationTime);
	WalkToPlayer();
	Move();
	IsOutOfScreen(false);
	UpdateRect();
}

HBITMAP Enemy::GethBmp()
{
	return animation_vec_[animation_index_].first;
}

BITMAP Enemy::GetBitmap()
{
	return animation_vec_[animation_index_].second;
}

void Enemy::GetHit(int dmg)
{
	hp_ -= dmg;
	if (hp_ <= 0)
	{
		is_alive_ = false;
	}
}

void Enemy::WalkToPlayer()
{
	bool isHorizontalFirst = rand() % 2;

	if (!isHorizontalFirst)
	{
		// Player is at the enemy's right side
		if (rect_.right < player_->get_rect().left)
		{
			direction_ = EDirection::kRight;
		}
		// left side
		else if (rect_.left > player_->get_rect().right)
		{
			direction_ = EDirection::kLeft;
		}
		// bottom side
		else if (rect_.top > player_->get_rect().bottom)
		{
			direction_ = EDirection::kUp;
		}
		else
		{
			direction_ = EDirection::kDown;
		}
	}
	else
	{
		if (rect_.top > player_->get_rect().bottom)
		{
			direction_ = EDirection::kUp;
		}
		else if (rect_.bottom < player_->get_rect().top)
		{
			direction_ = EDirection::kDown;
		}
		else if (rect_.right < player_->get_rect().left) //right
		{
			direction_ = EDirection::kRight;
		}
		else
		{
			direction_ = EDirection::kLeft;
		}
	}
}
