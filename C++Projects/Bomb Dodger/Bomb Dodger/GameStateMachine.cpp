#include "stdafx.h"
#include "resource.h"

#include "GameStateMachine.h"
#include "IntroState.h"
#include "InGameState.h"
#include "WinState.h"
#include "LoseState.h"
#include "Player.h"
#include "Tile.h"
#include "Bomb.h"
#include "Enemy.h"

GameStateMachine::~GameStateMachine()
{
	for (auto state : game_states_)
	{
		if (state != nullptr)
		{
			delete state;
		}
	}
	game_states_.clear();
}

void GameStateMachine::NextState()
{
	GameState::EStateType currentStateType = current_state_->get_state_type();
	GameState::EStateType nextStateType = GameState::EStateType::kNone;

	switch (currentStateType)
	{
	case GameState::EStateType::kIntro:
		nextStateType = GameState::EStateType::kInGame;
		break;
	case GameState::EStateType::kInGame:
		nextStateType = get_is_win() ? GameState::EStateType::kWin : GameState::EStateType::kLose;
		break;
	case GameState::EStateType::kWin:
		nextStateType = GameState::EStateType::kNone;
		break;
	case GameState::EStateType::kLose:
		nextStateType = GameState::EStateType::kNone;
		break;
	default:
		break;
	}

	if (nextStateType != GameState::EStateType::kNone)
	{
		current_state_ = GetStateByType(nextStateType);
	}
}

bool GameStateMachine::get_is_win()
{
	return current_state_->get_is_win();
}

bool GameStateMachine::Init(HWND hWindow, HINSTANCE hInstance)
{
	h_instance_ = hInstance;

	auto inGameState = new InGameState(hWindow);
	auto introState = new IntroState(hWindow);
	auto winState = new WinState(hWindow);
	auto loseState = new LoseState(hWindow);

	current_state_ = introState;
	game_states_ = vector<GameState*> { introState, inGameState, winState, loseState };

	// Load bitmap: Tile
	LoadaImage(Tile::animation_.first, Tile::animation_.second, IDB_BITMAP14);

	// Load bitmap: Player
	for (int i = IDB_BITMAP1, j = 0; i <= IDB_BITMAP4; i++, j++)
	{
		LoadaImage(Player::animation_vec_[j].first, Player::animation_vec_[j].second, i);
	}

	// Load bitmap: bomb
	for (int i = IDB_BITMAP8, j = 0; i <= IDB_BITMAP13; i++, j++)
	{
		LoadaImage(Bomb::animation_vec_[j].first, Bomb::animation_vec_[j].second, i);
	}

	// Load bitmap: zombie
	for (int i = IDB_BITMAP15, j = 0; i <= IDB_BITMAP24; i++, j++)
	{
		LoadaImage(Enemy::animation_vec_[j].first, Enemy::animation_vec_[j].second, i);
	}

	return true;
}

void GameStateMachine::Draw()
{
	current_state_->Draw();
}

void GameStateMachine::Update()
{
	// If the game ends => exit update 
	if (is_playing_ == false)
	{
		return;
	}

	// Update current game state
	if (!current_state_->Update())
	{
		NextState();
	}
}

void GameStateMachine::GetInput(Input::InputValue input)
{
	if (input == Input::InputValue::kQuit)
	{
		is_playing_ = false;
		return;
	}
	current_state_->GetInput(input);
}

void GameStateMachine::LoadaImage(HBITMAP& hBmp, BITMAP& Bitmap, int IDB)
{
	hBmp = LoadBitmap(h_instance_, MAKEINTRESOURCE(IDB));
	GetObject(hBmp, sizeof(Bitmap), &Bitmap);
}

GameState* GameStateMachine::GetStateByType(GameState::EStateType type)
{
	for (GameState* state : game_states_)
	{
		if (state->get_state_type() == type)
		{
			return state;
		}
	}
	return nullptr;
}
