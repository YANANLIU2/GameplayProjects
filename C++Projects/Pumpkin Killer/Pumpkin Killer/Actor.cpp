#include "stdafx.h"
#include "Actor.h"
#include "GameSettings.h"

void Actor::StopMoving()
{
	acceleration_ = 0;

	acceleration_ = 0;

	x_speed_ = 0;

	y_speed_ = 0;
}

void Actor::UpdateRect()
{
	// Update the render rect
	rect_.set_rect(x_ + x_size_, y_ + y_size_, x_, y_);

	// Update the collision rect
	hitbox_ = rect_ + hitbox_offset_;
}

bool Actor::IsOutOfScreen(bool isAllowed)
{
	bool result = false;

	// Is the object too left
	if (x_ < 0)
	{
		x_ = isAllowed ? x_ : 0;

		result = true;
	}
	// Is the object too right
	else if (x_ + x_size_ > GAME_WIDTH)
	{
		x_ = isAllowed ? x_ : float(GAME_WIDTH - x_size_);

		result = true;
	}

	// Is the object too up
	if (y_ < 0)
	{
		y_ = isAllowed ? y_ : 0;

		result = true;
	}
	// Is the object too down
	else if (y_ + y_size_ > GAME_HEIGHT)
	{
		y_ = isAllowed ? y_ : float(GAME_HEIGHT - y_size_);

		result = true;
	}
	return result;
}

void Actor::Move()
{
	// Is the object moving horizontally or vertically? 
	if (direction_ == EDirection::kDown || direction_ == EDirection::kUp)
	{
		// Accelerate the speed
		y_speed_ += acceleration_;

		// Limit the object's speed
		if (y_speed_ > max_speed_)
		{
			y_speed_ = max_speed_;
		}

		// Update position
		y_ = direction_ == EDirection::kDown ? y_ + y_speed_ : y_ - y_speed_;
	}
	else if (direction_ == EDirection::kLeft || direction_ == EDirection::kRight)
	{
		// Accelerate the speed
		x_speed_ += acceleration_;

		// Limit the object's speed
		if (x_speed_ > max_speed_)
		{
			x_speed_ = max_speed_;
		}

		// Update position
		x_ = direction_ == EDirection::kLeft ? x_ - x_speed_ : x_ + x_speed_;
	}
}

bool Actor::IsCollidedWith(Actor* another)
{
	MyRect rhs = another->get_hitbox();

	bool isRight = (hitbox_.right < rhs.left);

	bool isLeft = (hitbox_.left > rhs.right);

	bool isAbove = (hitbox_.top > rhs.bottom);

	bool isBelow = (hitbox_.bottom < rhs.top);

	bool isNotOverlapping = (isRight || isLeft || isAbove || isBelow);

	return !isNotOverlapping;
}


void Actor::UpdateAnimationIndex(size_t animationSize, bool isLoop)
{
	// Update animation index when a loop of the animation timer is over.
	if (animation_timer_.UpdateLoopTimer())
	{
		animation_index_++;

		// Loop the animations when the index is the end index.
		if (animation_index_ >= animationSize)
		{
			animation_index_ = isLoop ? 0 : animationSize - 1;
		}
	}
}