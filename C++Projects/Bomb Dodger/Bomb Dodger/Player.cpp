#include "stdafx.h"
#include "Player.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "GameStateMachine.h"
vector<AnimationPair> Player::animation_vec_(4);


Player::Player():ObjBase(), last_direction_(EDirection::kStop)
{
	// Transform
	x_size_ = kXSize;
	y_size_ = kYSize;
	y_ = float(GAME_HEIGHT - y_size_);
	UpdateRect();

	// Animation
	timer_.set_time(kAnimationTime);
}

Player::~Player()
{
	for (auto command : commands_vec)
	{
		delete command;
	}
	commands_vec.clear();
}

void Player::Update()
{
	ObjBase::Update();

	if(direction_ != EDirection::kStop)
	{
		UpdateAnimationIndex(animation_vec_.size(), kAnimationTime);
	}
	this->Move();
	IsOutOfScreen(false);
	UpdateRect();
}

void Player::HandleInput(Command * pCommand)
{
	if (this->get_is_alive())
	{
		switch (pCommand->GetType())
		{
		case Command::ECommandType::kMove:
		{
			MoveCommand* pMove = static_cast<MoveCommand*>(pCommand);
			switch (pMove->GetDirection())
			{
			case Input::InputValue::kMoveLeft:
				direction_ = EDirection::kLeft;
				break;

			case Input::InputValue::kMoveRight:
				direction_ = EDirection::kRight;
				break;

			case Input::InputValue::kMoveUp:
				direction_ = EDirection::kUp;
				break;

			case Input::InputValue::kMoveDown:
				direction_ = EDirection::kDown;
				break;

			case Input::InputValue::kStopMove:
				direction_ = EDirection::kStop;
				break;

			default:
				break;
			}

			// Clear former commands if differnet directions
			if (last_direction_ != direction_)
			{

			}
			last_direction_ = direction_;
		}

		default:
			break;
		}
	}
}

HBITMAP Player::GethBmp()
{
	return animation_vec_[animation_index_].first;
}

BITMAP Player::GetBitmap()
{
	return animation_vec_[animation_index_].second;
}

