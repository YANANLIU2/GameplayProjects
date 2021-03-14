#pragma once
#include "Actor.h"
#include "GameSettings.h"

// The script is for defining a user-controlled player
class Input;
class Player : public Actor
{
	// Unlike other actors, the player moves in a constant speed.
	const float kSpeed = 1;

	// Apply the value when the player moves diagonally to prevent the total speed increase. 
	const float kRootOne = 0.707f;

	// Input reference so the player can update based on player input 
	Input* input_;
public:
	// An array of animations for a player
	static vector<AnimationPair> animation_vec_;

	// Constructor 
	Player();

	// Destructor
	~Player() = default;

	// Set the input reference of a player
	void set_input(Input* input) { input_ = input; }

	// Update
	void Update() override final;
	
	// Reset a player to the state of game's beginning
	void Reset();

	// Update a player's movement based on player input
	void UpdateMovement();

	// Get the h-bitmap which should be displaying currently
	HBITMAP GethBmp() override final;

	// Get the h-bitmap which should be displaying currently
	BITMAP GetBitmap() override final;
};

