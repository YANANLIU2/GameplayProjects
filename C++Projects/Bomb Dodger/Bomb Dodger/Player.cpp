#include "stdafx.h"
#include "Player.h"
#include "GameStateMachine.h"
#include "Input.h"

vector<AnimationPair> Player::animation_vec_(20);

Player::Player()
	: Actor()
	, input_(nullptr)
{
	// Transform
	x_size_ = 61;

	y_size_ = 67;
	
	// Rect
	hitbox_offset_ = MyRect(-20,-20,20,20);
	
	// Animation timer
	animation_timer_.set_time(0.011);
	
	Reset();
}

void Player::Update()
{
	ObjBase::Update();

	// Movement
	UpdateMovement();

	// Update animations when the player is moving
	if (x_speed_ != 0 || y_speed_ != 0)
	{
		UpdateAnimationIndex(animation_vec_.size(), true);
	}
}

void Player::Reset()
{
	// Gameplay
	is_alive_ = true;

	// Animation Index 
	animation_index_ = 0;

	// Stop movement
	StopMoving();

	// Start position
	x_ = 0;

	y_ = float(GAME_HEIGHT - y_size_);

	UpdateRect();
}

void Player::UpdateMovement()
{
	// When the player pressed only the go-up key and not the go-down key => the player goes up
	if (input_->IsValueKeyPressed(Input::EInputValue::kIsMovingUp))
	{
		// When the player pressed both the go-up key and the go-down key => the player stays at the same position along y-axis
		y_speed_ = input_->IsValueKeyPressed(Input::EInputValue::kIsMovingDown) ? 0 : -kSpeed;
	}
	// When the player pressed only the go-down key and not the go-up key => the player goes down
	else if (input_->IsValueKeyPressed(Input::EInputValue::kIsMovingDown))
	{
		// When the player pressed both the go-up key and the go-down key => the player stays at the same position along y-axis
		y_speed_ = input_->IsValueKeyPressed(Input::EInputValue::kIsMovingUp) ? 0: +kSpeed;
	}

	// When the player pressed only the go-left key and not the go-right key => the player goes left
	if (input_->IsValueKeyPressed(Input::EInputValue::kIsMovingLeft))
	{
		// When the player pressed both the go-left key and the go-right key => the player stays at the same position along x-axis
		x_speed_ = input_->IsValueKeyPressed(Input::EInputValue::kIsMovingRight) ? 0: -kSpeed;
	}
	// When the player pressed only the go-right key and not the go-left key => the player goes left
	else if (input_->IsValueKeyPressed(Input::EInputValue::kIsMovingRight))
	{
		// When the player pressed both the go-left key and the go-right key => the player stays at the same position along x-axis
		x_speed_ = input_->IsValueKeyPressed(Input::EInputValue::kIsMovingLeft) ? 0: +kSpeed;
	}

	// When the player doesnt press neither the go-up key not the go-down key => the player stays at the same position along y-axis
	y_speed_ = (!input_->IsValueKeyPressed(Input::EInputValue::kIsMovingUp) && !input_->IsValueKeyPressed(Input::EInputValue::kIsMovingDown)) ? 0 : y_speed_;

	// When the player doesnt press neither the go-right key not the go-left key => the player stays at the same position along x-axis
	x_speed_ = (!input_->IsValueKeyPressed(Input::EInputValue::kIsMovingLeft) && !input_->IsValueKeyPressed(Input::EInputValue::kIsMovingRight)) ? 0 : x_speed_;

	// When the players moves diagonally: multiply both x_speed_ and y_speed_ with kRootOne to prevent moving too fast
	if (x_speed_ != 0 && y_speed_ != 0)
	{
		x_speed_ *= kRootOne;

		y_speed_ *= kRootOne;
	}

	// Update position
	y_ += y_speed_;

	x_ += x_speed_;

	// Limit position
	IsOutOfScreen(false);

	// Rect
	UpdateRect();
}

HBITMAP Player::GethBmp()
{
	return animation_vec_[animation_index_].first;
}

BITMAP Player::GetBitmap()
{
	return animation_vec_[animation_index_].second;
}



