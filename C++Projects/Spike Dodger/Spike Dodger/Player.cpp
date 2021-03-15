#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	speed_ = { 30,0 };

	size_ = { 110,96 };

	Reset();
}

void Player::OutofBox()
{
	if (get_is_outside_left())
	{
		pos_.x_ = 0;
	}
	else if (get_is_outside_right())
	{
		pos_.x_ = GAME_WIDTH - size_.x_;
	}
}

void Player::Update()
{
	OutofBox();
}

void Player::Reset()
{
	pos_ = { 0, float(GAME_HEIGHT - size_.y_ - 120) };
}


