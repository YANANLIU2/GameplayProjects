#pragma once
#include "GameState.h"

class LoseState :
	public GameState
{
public:
	static EStateType type_;
	EStateType get_state_type() override final { return type_; }

	// Constructor & Destructor 
	LoseState(HWND hWindow) :GameState(hWindow) {}
	~LoseState() = default;

	void Draw() override;
	bool Update() override;
};


