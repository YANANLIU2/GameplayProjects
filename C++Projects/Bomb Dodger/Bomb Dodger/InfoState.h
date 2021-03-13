#pragma once
#include "GameState.h"

class InfoState :
    public GameState
{
	// The txt will be displaying in the state
	wchar_t* txt_;

	// The display rect of the txt
	MyRect txt_rect_;

	// The length of the txt
	size_t txt_size_;

	// The buffer size: if the length of the txt exceeds the buffer size => error
	static constexpr const size_t kTxtBufferSize = 120;

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

