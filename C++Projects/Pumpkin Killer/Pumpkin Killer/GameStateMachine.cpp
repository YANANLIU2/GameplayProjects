#include "stdafx.h"
#include "resource.h"
#include "GameStateMachine.h"
#include "InfoState.h"
#include "InGameState.h"
#include "Player.h"
#include "Tile.h"
#include "Bomb.h"
#include "Enemy.h"
#include "Coin.h"

GameStateMachine::~GameStateMachine()
{
	// Destroy all states
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
	// Go to the next state based on the type of the current state 
	GameState::EStateType currentStateType = current_state_->get_state_type();

	GameState::EStateType nextStateType = GameState::EStateType::kNone;

	switch (currentStateType)
	{
	// Intro => InGame
	case GameState::EStateType::kIntro:

		nextStateType = GameState::EStateType::kInGame;

		break;

	// In game => Lose or Win
	case GameState::EStateType::kInGame:

		nextStateType = get_is_win() ? GameState::EStateType::kWin : GameState::EStateType::kLose;

		break;

	// Win => Intro (also Reset())
	case GameState::EStateType::kWin:

		nextStateType = GameState::EStateType::kIntro;

		Reset();

		break;

	// Lose => Intro (also Reset())
	case GameState::EStateType::kLose:

		nextStateType = GameState::EStateType::kIntro;

		Reset();

		break;

	default:
		break;
	}

	if (nextStateType != GameState::EStateType::kNone)
	{
		current_state_ = get_state_by_type(nextStateType);
	}
}

bool GameStateMachine::get_is_win()
{
	return current_state_->get_is_win();
}

bool GameStateMachine::Init(HWND hWindow, HINSTANCE hInstance)
{
	h_instance_ = hInstance;

	// Constants used for creating game states
	constexpr wchar_t * introTxt = L"Instructions:\nWASD: to move\nArrow KEY: to fire\nSpace Key: to begin\nLose: if you get touched\nWin: kill all enemies";
	
	constexpr wchar_t* loseTxt = L"Lose.\nPress Ese To Exit.\nPress Space to Restart.";
	
	constexpr wchar_t* winTxt = L"Win.\nPress Ese To Exit.\nPress Space to Restart.";
	
	const MyRect introTxtRect = MyRect (GAME_WIDTH / 2 + 200, GAME_HEIGHT / 2 + 50, GAME_WIDTH / 2 - 100, GAME_HEIGHT / 2 - 100);
	
	const MyRect winTxtRect = MyRect(GAME_WIDTH / 2 + 120, GAME_HEIGHT / 2 + 50, GAME_WIDTH / 2 - 120, GAME_HEIGHT / 2 - 50);
	
	const MyRect loseTxtRect = MyRect(GAME_WIDTH / 2 + 85, GAME_HEIGHT / 2 + 50, GAME_WIDTH / 2 - 85, GAME_HEIGHT / 2 - 50);
	
	const int introTextLength = 114;
	
	const int loseTxtLength = 49;
	
	const int winTxtLength = 48;

	// Create game states
	auto inGameState = new InGameState(hWindow, input_.get());

	auto introState = new InfoState(hWindow, input_.get(), GameState::EStateType::kIntro, introTxt, introTxtRect, introTextLength);

	auto winState = new InfoState(hWindow, input_.get(), GameState::EStateType::kWin, winTxt, winTxtRect, winTxtLength);

	auto loseState = new InfoState(hWindow, input_.get(), GameState::EStateType::kLose, loseTxt, loseTxtRect, loseTxtLength);

	current_state_ = introState;
	
	game_states_ = vector<GameState*> { introState, inGameState, winState, loseState };

	// Load bitmap 
	ObjBase::LoadImages(hInstance, Tile::animation_vec_, IDB_BITMAP14, IDB_BITMAP14);

	ObjBase::LoadImages(hInstance, Player::animation_vec_, IDB_BITMAP25, IDB_BITMAP44);

	ObjBase::LoadImages(hInstance, Enemy::animation_vec_, IDB_BITMAP15, IDB_BITMAP24);

	ObjBase::LoadImages(hInstance, Bomb::animation_vec_, IDB_BITMAP8, IDB_BITMAP13);

	ObjBase::LoadImages(hInstance, Coin::animation_vec_, IDB_BITMAP45, IDB_BITMAP49);

	return true;
}

void GameStateMachine::Draw()
{
	current_state_->Draw();
}

void GameStateMachine::Reset()
{
	for (GameState* state : game_states_)
	{
		state->Reset();
	}
}

void GameStateMachine::Update()
{
	// When the player presses the quit key => quit the game
	if (input_->get_input_state(Input::EInputValue::kQuit) == Input::EInputState::kPress)
	{
		is_playing_ = false;

		return;
	}
	
	// Update current game state
	if (!current_state_->Update())
	{
		NextState();
	}

	// Update the input
	input_->Update();
}

GameState* GameStateMachine::get_state_by_type(GameState::EStateType type)
{
	// Loop the game states array to find the target game state 
	for (GameState* state : game_states_)
	{
		if (state->get_state_type() == type)
		{
			return state;
		}
	}
	return nullptr;
}
