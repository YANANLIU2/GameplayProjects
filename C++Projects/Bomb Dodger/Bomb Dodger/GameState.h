#pragma once
#include "Input.h"
class ObjBase;
class GameState
{
public:
	enum class EStateType
	{
		kIntro,
		kInGame,
		kWin,
		kLose,
		kNone
	};

protected:
	HWND h_window_;
	bool is_finish_;
	bool is_win_;

public:
	// Constructor & Destructor 
	GameState(HWND hWindow): h_window_(hWindow), is_finish_(false), is_win_(false){}
	virtual ~GameState() = default;

	// Getters & Setters
	bool get_is_win() const { return is_win_; }
	void set_is_win(bool win) { is_win_ = win; }
	virtual EStateType get_state_type() { return EStateType::kNone; }

	// Update
	virtual bool Update() { return false; };
	virtual void Draw(){};
	
	// Collision
	virtual void Collision() {};
	bool IsCollidedWith(ObjBase* ObjOne, ObjBase* ObjTwo);

	// Input
	virtual void GetInput(Input::InputValue input) {};
};
	


