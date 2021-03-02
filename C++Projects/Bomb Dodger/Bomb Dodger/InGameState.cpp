#include <cmath> 
#include <math.h> 
#include "stdafx.h"
#include "MyMath.h"
#include "GameSettings.h"
#include "FrameTimer.h"
#include "InGameState.h"
#include "Player.h"
#include "Bomb.h"
#include "Tile.h"
#include "Enemy.h"
#include "Coin.h"

#define A_TILE tiled_map_[y*kTileColumns + x]

InGameState::InGameState(HWND hWindow, Input* input)
	: GameState(hWindow, input, EStateType::kInGame)
	, score_(0)
	, player_(std::make_unique<Player>())
	, bomb_timer_(0.1)
	, one_coin_score_(10)
	, one_kill_score_(20)
{
	// Initialize the tiled map with tiles
	tiled_map_ = new Tile*[kTotalTiles];
	for (size_t y = 0; y < kTileRows; ++y)
	{
		for (size_t x = 0; x < kTileColumns; ++x)
		{
			size_t index = y* kTileColumns + x;
			A_TILE = new Tile(index, kTileColumns, kTileRows, x, y);
		}
	}

	// Set the player's input
	player_.get()->set_input(input);

	// Reset all the variables
	Reset();
}

InGameState::~InGameState()
{
	// Destroy all the tiles in the tiled map
	for (int y = 0; y < kTileRows; ++y)
	{
		for (int x = 0; x < kTileColumns; ++x)
		{
			delete A_TILE;
			A_TILE = nullptr;
		}
	}

	delete[] tiled_map_;
	tiled_map_ = nullptr;

	// Destroy all other game objects 
	DestroyAllGameObjects();
}

bool InGameState::Update()
{
	// Update game objects 
	player_->Update();
	UpdatePlayerAttack();
	
	for each (auto & coin in coin_vec_)
	{
		coin->Update();
	}

	for each (auto& enemy in enemy_vec_)
	{
		enemy->Update();
	}

	bomb_vec_.erase(
		std::remove_if(
			bomb_vec_.begin(),
			bomb_vec_.end(),
			[](Bomb* p) 
			{ 
				p->Update();

				if (p->IsOutOfScreen())
				{
					delete p;
					p = nullptr;
					return true;
				}
				else
				{
					return false;
				}
			}
		),
		bomb_vec_.end()
	);

	// Calculate collision
	Collision();

	// If player is dead => next state (Lose)
	if (player_->get_is_alive() == false)
	{
		is_win_ = false;
		return false;
	}

	// If all enemies are dead => next state (Win)
	if (enemy_vec_.size() == 0)
	{
		is_win_ = true;
		return false;
	}
	return true;
}


void InGameState::Draw()
{
	// Double Bufferedddd
	HDC hdcScreen = GetDC(h_window_);
	HDC hdcMemory = CreateCompatibleDC(hdcScreen);
	HBITMAP hBlankBitmap = CreateCompatibleBitmap(hdcScreen, GAME_WIDTH, GAME_HEIGHT);

	// "Clear Screen"
	SelectObject(hdcMemory, hBlankBitmap);
	HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	HPEN hNullPen = CreatePen(PS_NULL, 1, RGB(255, 255, 255));
	SelectObject(hdcMemory, hNullPen);
	SelectObject(hdcMemory, hWhiteBrush);
	Rectangle(hdcMemory, 0, 0, GAME_WIDTH, GAME_HEIGHT);

	// Tiled map
	HDC TileDc = CreateCompatibleDC(hdcScreen);
	for (int y = 0; y < kTileRows; ++y)
	{
		for (int x = 0; x < kTileColumns; ++x)
		{
			SelectObject(TileDc, A_TILE->GethBmp());
			StretchBlt(hdcMemory, (int)A_TILE->get_x(), (int)A_TILE->get_y(), (int)A_TILE->get_x_size(), (int)A_TILE->get_y_size(),
				TileDc, 0, 0, A_TILE->GetBitmap().bmWidth, A_TILE->GetBitmap().bmHeight, SRCCOPY);
		}
	}

	// Draw game objects
	for each (auto & enemy in enemy_vec_)
	{
		enemy->DrawTransparent(hdcScreen, hdcMemory, Default_Transparent_Color);
	}

	for each (auto & bomb in bomb_vec_)
	{
		bomb->DrawTransparent(hdcScreen, hdcMemory, Default_Transparent_Color);
	}

	for each (auto & coin in coin_vec_)
	{
		coin->DrawTransparent(hdcScreen, hdcMemory, Default_Transparent_Color);
	}

	player_->DrawTransparent(hdcScreen, hdcMemory, Default_Transparent_Color);

	// Draw score
	WCHAR score_text[20];
	wsprintf(score_text, L"Score: %d   ", int(score_));
	RECT score_Rectangle{ 10 , 10, 82, 30 };
	DrawText(hdcMemory, score_text, 20, &score_Rectangle, DT_BOTTOM);

	// Present the Memory to the Screen
	BitBlt(hdcScreen, 0, 0, GAME_WIDTH, GAME_HEIGHT, hdcMemory, 0, 0, SRCCOPY);

	// IMPORTANT:  TERRIBLY INCREDIBLY IMPORTANT
	// Destroy objects in the *opposite* order in which they were made
	DeleteObject(hWhiteBrush);
	DeleteObject(hdcScreen);
	DeleteObject(hNullPen);
	DeleteObject(TileDc);
	DeleteObject(hBlankBitmap);
	DeleteDC(hdcMemory);
}

void InGameState::Reset()
{
	bomb_timer_.set_elapsed_time(0);
	DestroyAllGameObjects();

	// Enemy
	enemy_vec_.push_back(new Enemy(player_.get()));
	enemy_vec_.push_back(new Enemy(player_.get(), 100, 0));
	enemy_vec_.push_back(new Enemy(player_.get(), 500, 0));

	is_win_ = false;
	player_.get()->Reset();
	score_ = 0;
}

void InGameState::Collision()
{
	auto enemyVecIterator = std::begin(enemy_vec_);
	while (enemyVecIterator != std::end(enemy_vec_)) {

		// If any enemy collide with the player => the player lose
		if (player_->IsCollidedWith(*enemyVecIterator))
		{
			player_->set_is_alive(false);
			return; // Return cause the player dies
		}

		// If any bomb collide with the enemy => enemy - hp, delete bomb
		bomb_vec_.erase(
			std::remove_if(
				bomb_vec_.begin(),
				bomb_vec_.end(),
				[this, enemyVecIterator](Bomb* bomb) -> bool {
					if (bomb->IsCollidedWith(*enemyVecIterator))
					{
						// enemy gets hit: generate a coin
						(*enemyVecIterator)->GetHit(Bomb::kDamage);
						coin_vec_.push_back(new Coin((*enemyVecIterator)->get_x(), (*enemyVecIterator)->get_y()));
						delete bomb;
						return true;
					}
					return false;
				}),bomb_vec_.end());

		// If enemy dies => erase
		if (!(*enemyVecIterator)->get_is_alive())
		{
			delete (*enemyVecIterator);
			enemyVecIterator = enemy_vec_.erase(enemyVecIterator);
			score_ += one_kill_score_;
		}
		else
		{
			++enemyVecIterator;
		}
	}

	// If player collides with any coin => destroy the coin and add score
	coin_vec_.erase(
		std::remove_if(
			coin_vec_.begin(),
			coin_vec_.end(),
			[this](Coin* coin) -> bool {
				if (coin->IsCollidedWith(player_.get()))
				{
					score_ += one_coin_score_;
					delete coin;
					return true;
				}
				return false;
			}
		),coin_vec_.end());
}

void InGameState::UpdatePlayerAttack()
{
	if (!bomb_timer_.UpdateTimer())
	{
		return;
	}

	float x = player_->get_x() + player_->get_x_size() * 0.5f;
	float y = player_->get_y() + player_->get_y_size() * 0.5f;

	if (input_->IsValueKeyPressed(Input::EInputValue::kAttackDown))
	{
		FireABomb(x, y, EDirection::kDown);
	}
	else if (input_->IsValueKeyPressed(Input::EInputValue::kAttackLeft))
	{
		FireABomb(x, y, EDirection::kLeft);
	}
	else if (input_->IsValueKeyPressed(Input::EInputValue::kAttackRight))
	{
		FireABomb(x, y, EDirection::kRight);
	}
	else if (input_->IsValueKeyPressed(Input::EInputValue::kAttackUp))
	{
		FireABomb(x, y, EDirection::kUp);
	}
}

void InGameState::FireABomb(float x, float y, EDirection dir)
{
	bomb_timer_.RestartTimer();
	bomb_vec_.push_back(new Bomb(x, y, dir));
}

void InGameState::DestroyAllGameObjects()
{
	// Destroy all enemies
	for (auto & enemy : enemy_vec_)
	{
		delete enemy;
	}

	enemy_vec_.clear();

	// Destory all bombs
	for (auto & bomb : bomb_vec_)
	{
		delete bomb;
	}

	bomb_vec_.clear();

	// Destory all coins
	for (auto & coin : coin_vec_)
	{
		delete coin;
	}

	coin_vec_.clear();

	// Doesn't need to destroy the player because the smart pointer will handle it
}

