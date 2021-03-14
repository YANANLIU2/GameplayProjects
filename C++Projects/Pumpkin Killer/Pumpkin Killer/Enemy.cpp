#include <stdlib.h>     /* srand, rand */
#include "stdafx.h"
#include "Enemy.h"
#include "FrameTimer.h"
#include "Player.h"

vector<AnimationPair> Enemy::animation_vec_(10);

Enemy::Enemy(Player* player, float x, float y) : Actor(), health_points_(3), player_(player)
{
	// Size
	x_size_ = 58;

	y_size_ = 76;

	// Movement
	max_speed_ = 0.5;

	acceleration_ = 1;

	acceleration_ = 1;

	// Position
	x_ = x;

	y_ = y;

	// Rect: because the right side of the enemy sprites has more space, the right offset value is larger
	hitbox_offset_ = MyRect(-15,-5,5,5);

	UpdateRect();

	// Timer
	animation_timer_.set_time(0.011);
}

void Enemy::Update()
{
	max_speed_ *= kMaxSpeedAccelerationOverTime;

	ObjBase::Update();

	// Animation
	UpdateAnimationIndex(animation_vec_.size(), true);

	// Movement
	WalkToPlayer();

	// Update position
	Move();

	// Check whether the position valid or not
	IsOutOfScreen(false);

	// Update rects
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
	health_points_ -= dmg;
	if (health_points_ <= 0)
	{
		is_alive_ = false;
	}
}

void Enemy::WalkToPlayer()
{
	MyRect playerHitbox = player_->get_hitbox();

	EDirection horizontalDir = EDirection::kNull, verticalDir = EDirection::kNull;

	// Player is at the enemy's right side
	if (hitbox_.right < playerHitbox.left)
	{
		horizontalDir = EDirection::kRight;
	}
	// Player is at the enemy's left side
	else if (hitbox_.left > playerHitbox.right)
	{
		horizontalDir = EDirection::kLeft;
	}

	// Player is at the enemy's bottom side
	if (hitbox_.top > playerHitbox.bottom)
	{
		verticalDir = EDirection::kUp;
	}
	// Player is at the enemy's up side
	else
	{
		verticalDir = EDirection::kDown;
	}

	// If the enemy can go either vertically or horizontally to chase the player then pick a random one
	if (verticalDir != EDirection::kNull && horizontalDir != EDirection::kNull)
	{
		bool isHorizontalFirst = rand() % 2;

		direction_ =  isHorizontalFirst? horizontalDir : verticalDir;
	}
	// If not, pick the one the enemy can go
	else
	{
		direction_ = verticalDir == EDirection::kNull ? horizontalDir : verticalDir;
	}
}
