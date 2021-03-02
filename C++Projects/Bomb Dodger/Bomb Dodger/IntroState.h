#pragma once
#include "GameState.h"
class IntroState :
	public GameState
{
public:
	static EStateType type_;
	EStateType get_state_type() override final { return type_; }

	IntroState(HWND hWindow) :GameState(hWindow) {}
	~IntroState() = default;
	void Draw() override;
	bool Update() override;
	void GetInput(Input::InputValue input) override final;
};