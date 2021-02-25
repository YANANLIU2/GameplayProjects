#include "stdafx.h"
#include "InGameState.h"
#include "GameSettings.h"
#include <cmath> 
#include <math.h>  
#include "FrameTimer.h"
#include "Player.h"
#include "Bomb.h"
#include "Tile.h"
#include "Enemy.h"
#include "MyMath.h"

#define A_TILE tiled_map_[y*kTileWidth + x]
GameState::EStateType InGameState::type_ = GameState::EStateType::kInGame;

InGameState::InGameState(HWND hWindow)
	: GameState(hWindow)
	, score_(0)
	, player_(std::make_shared<Player>())
	, player_input_(std::make_unique<Input>())
{
	player_input_->set_player(player_.get());

	// TiledMap
	tiled_map_ = new Tile*[kTotalTiles];
	for (size_t y = 0; y < kTileHeight; ++y)
	{
		for (size_t x = 0; x < kTileWidth; ++x)
		{
			size_t index = y* kTileWidth + x;
			A_TILE = new Tile(index, kTileWidth, kTileHeight, x, y);
		}
	}

	// Enemy
	/*enemy_vec_.push_back( new Enemy(player_));
	enemy_vec_.push_back( new Enemy(player_, 100, 0));
	enemy_vec_.push_back( new Enemy(player_, 500, 0));*/
}

InGameState::~InGameState()
{
	// Tile
	for (int y = 0; y < kTileHeight; ++y)
	{
		for (int x = 0; x < kTileWidth; ++x)
		{
			delete A_TILE;
			A_TILE = nullptr;
		}
	}

	delete[] tiled_map_;
	tiled_map_ = nullptr;

	// Enemy
	for (auto enemy : enemy_vec_)
	{
		delete enemy;
	}
	enemy_vec_.clear();

	// Bombs
	for (auto bomb : bomb_vec_)
	{
		delete bomb;
	}
	bomb_vec_.clear();
}

bool InGameState::Update()
{
	// Update game objects 
	player_->Update();

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
	/*if (enemy_vec_.size() == 0)
	{
		is_win_ = true;
		return false;
	}*/
	return true;
}


void InGameState::Draw()
{
	// Double Buffered
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
	for (int y = 0; y < kTileHeight; ++y)
	{
		for (int x = 0; x < kTileWidth; ++x)
		{
			SelectObject(TileDc, A_TILE->GethBmp());
			StretchBlt(hdcMemory, (int)A_TILE->get_x(), (int)A_TILE->get_y(), A_TILE->get_x_size(), A_TILE->get_y_size(),
				TileDc, 0, 0, A_TILE->GetBitmap().bmWidth, A_TILE->GetBitmap().bmHeight, SRCCOPY);
		}
	}

	// Draw game objects
	player_->DrawTransparent(hdcScreen, hdcMemory, Default_Transparent_Color);

	for each (auto & enemy in enemy_vec_)
	{
		enemy->DrawTransparent(hdcScreen, hdcMemory, Default_Transparent_Color);
	}

	for each (auto & bomb in bomb_vec_)
	{
		bomb->DrawTransparent(hdcScreen, hdcMemory, Default_Transparent_Color);
	}

	// Draw score
	WCHAR score_text[20];
	wsprintf(score_text, L"Score: %d", int(score_));
	RECT score_Rectangle{ 10 , 10, 70, 30 };
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


void InGameState::GetInput(Input::InputValue input)
{
	if (input == Input::InputValue::kAttackDown)
	{
		bomb_vec_.push_back(new Bomb(player_.get() ,EDirection::kDown));
	}
	else if (input == Input::InputValue::kAttackUp)
	{
		bomb_vec_.push_back(new Bomb(player_.get(), EDirection::kUp));
	}
	else if (input == Input::InputValue::kAttackRight)
	{
		bomb_vec_.push_back(new Bomb(player_.get(), EDirection::kRight));
	}
	else if (input == Input::InputValue::kAttackLeft)
	{
		bomb_vec_.push_back(new Bomb(player_.get(), EDirection::kLeft));
	}
	
	player_input_->HandleRawInput(input);
}


void InGameState::Collision()
{
	auto enemyVecIterator = std::begin(enemy_vec_);
	while (enemyVecIterator != std::end(enemy_vec_)) {

		// If any enemy collide with the player => the player lose
		if (IsCollidedWith(player_.get(), *enemyVecIterator))
		{
			player_->set_is_alive(false);
			return; // return cause the player dies
		}

		// If any bomb collide with the enemy => enemy - hp, delete bomb
		bomb_vec_.erase(
			std::remove_if(
				bomb_vec_.begin(),
				bomb_vec_.end(),
				[this, enemyVecIterator](Bomb* bomb) -> bool {
					if (IsCollidedWith(bomb, *enemyVecIterator))
					{
						// enemy gets hit
						(*enemyVecIterator)->GetHit(Bomb::kDamage);
						score_ += 10;
						return true;
					}
					return false;
				}
			),
			bomb_vec_.end()
		);


		// If enemy dies => erase
		if (!(*enemyVecIterator)->get_is_alive())
		{
			enemyVecIterator = enemy_vec_.erase(enemyVecIterator);
		}
		else
		{
			++enemyVecIterator;
		}
	}
}

