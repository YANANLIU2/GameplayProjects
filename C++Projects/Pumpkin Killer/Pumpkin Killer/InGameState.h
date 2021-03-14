#pragma once
#include <vector>
#include <memory>
#include "Input.h"
#include "FrameTimer.h"
#include "GameState.h"

// The class defines the game state when the player is playing the game
class Tile;
class Enemy;
class Player;
class Bomb;
class Coin;
enum class EDirection;
class InGameState : public GameState
{
#pragma region Constants
	// The num of rows of tiles 
	const size_t kTileRows = 16;

	// The num of columns of tiles 
	const size_t kTileColumns = 12;

	// The num of total tiles
	const size_t kTotalTiles = 12 * 16;

	// The damage one bomb hit can cause
	const int kBombDamage = 1;

#pragma endregion Constants

	// The total score the player has earned so far 
	float score_;

	// The score the player will earn after collecting one coin
	float one_coin_score_;

	// The score the player will earn after killing one enemy
	float one_kill_score_;

	// A tiled map which has all the tiles
	Tile** tiled_map_;

	// A smart pointer of the player, the state owns the ownership
	std::unique_ptr<Player> player_;

	// A vector of all active enemies
	std::vector<Enemy*> enemy_vec_;
	
	// A vector of all active bombs
	std::vector<Bomb*> bomb_vec_;

	// A vector of all active coins
	std::vector<Coin*> coin_vec_;

	// A cooldown timer for firing a bomb
	FrameTimer bomb_timer_;

	// Destroy all ObjBase objects
	void DestroyAllGameObjects();

	// Update player attack based on the player input => generate bombs when all prerequisites are met
	void UpdatePlayerAttack();

	// Generate a bomb
	void FireABomb(float x, float y, EDirection dir);

	// Calculate collision
	void Collision() override;

public:
	// Constructor
	InGameState(HWND hWindow, Input* input);

	// Destructor
	~InGameState();
	
	// Update 
	bool Update() override final;
	
	// Render
	virtual void Draw();
	
	// Reset for restarting the game 
	void Reset() override final;
};

