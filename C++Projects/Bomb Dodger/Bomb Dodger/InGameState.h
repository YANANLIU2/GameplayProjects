#pragma once
#include "GameState.h"
#include "Input.h"
#include <vector>
#include <memory>

class Tile;
class Enemy;
class Player;
class Bomb;
class InGameState : public GameState
{
	// Constants
	const size_t kTileHeight = 16;
	const size_t kTileWidth = 12;
	const size_t kTotalTiles = 12 * 16;
	const int kBombDamage = 1;
	
	// Scoreboard
	float score_;

	// Player
	std::shared_ptr<Player> player_;
	std::unique_ptr<Input> player_input_;

	// TiledMap
	Tile** tiled_map_;
	std::vector<Enemy*> enemy_vec_;
	std::vector<Bomb*> bomb_vec_;


public:
	static EStateType type_;

	InGameState(HWND hWindow);
	~InGameState();
	
	// Getters & Setters
	float get_score() { return score_; }
	EStateType get_state_type() override final { return type_; }

	// Main Loop
	bool Update() override;

	virtual void Draw();

	// Gameplay
	void GetInput(Input::InputValue input) override final;
	void Collision() override;
};

