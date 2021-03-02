#pragma once
#include "GameState.h"

class InfoState :
    public GameState
{
	wchar_t* txt_;
	MyRect txt_rect_;
	size_t txt_size_;
	static constexpr const int kTxtBufferSize = 120;

public:
	// Constructor 
	InfoState(HWND hWindow, Input* input, EStateType type, wchar_t* txt = L"", MyRect textRect = MyRect(), size_t txtSize = 0);

	// Destructor 
	virtual ~InfoState() = default;

	// Update 
	bool Update() override final;

	// Render
	virtual void Draw();

	// Reset for restarting the game 
	void Reset() override final;
};

