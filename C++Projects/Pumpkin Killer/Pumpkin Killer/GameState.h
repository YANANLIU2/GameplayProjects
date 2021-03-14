#pragma once
#include "stdafx.h"
#include "MyMath.h"

// The script is for providing basic functions for every game state
class Input;
class ObjBase;
class GameState
{
public:
	// Type of the game state, used for identifying which game state it is
	enum class EStateType
	{
		kIntro,
		kInGame,
		kWin,
		kLose,
		kNone
	};

protected:
	// A window handler
	HWND h_window_;

	// Is the state finished  
	bool is_finish_;

	// Whether the player wins or not
	bool is_win_;

	// The input reference so the game state can get player input to create bombs the player fires 
	Input* input_;

	// The game state type of the state
	EStateType state_type_;

	// Calculate collision
	virtual void Collision() {};

public:
	// Constructor 
	GameState(HWND hWindow, Input* input, EStateType type): h_window_(hWindow), is_finish_(false), is_win_(false), input_(input), state_type_(type){}

	// Destructor 
	virtual ~GameState() = default;

	// Get the value of whether the player wins or not
	bool get_is_win() const { return is_win_; }

	// Get the value of whether the player wins or not
	void set_is_win(bool win) { is_win_ = win; }

	// Get the game state's type
	virtual EStateType get_state_type() { return state_type_; }

	// Update
	virtual bool Update() { return false; }

	// Render
	virtual void Draw() {}

	// Reset for restarting a game
	virtual void Reset() {}
};
	


