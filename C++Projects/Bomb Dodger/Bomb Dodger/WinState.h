#pragma once
#include "GameState.h"

class WinState :
	public GameState
{
public:
	static EStateType type_;
	EStateType get_state_type() override final { return type_; }

	// Constructor & Destructor 
	WinState(HWND hWindow) :GameState(hWindow) {}
	~WinState() = default;

	void Draw() override;
	bool Update() override;
};
