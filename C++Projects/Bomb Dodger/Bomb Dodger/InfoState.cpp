#include "stdafx.h"
#include <assert.h>     /* assert */
#include "InfoState.h"
#include "Input.h"
#include "GameSettings.h"

InfoState::InfoState(HWND hWindow, Input* input, EStateType type, wchar_t* txt, MyRect textRect, size_t txtSize)
	: GameState(hWindow, input, type)
	, txt_(txt)
	, txt_rect_(textRect)
	, txt_size_(txtSize) 
{
	assert(txt_size_ <= kTxtBufferSize);
}

bool InfoState::Update()
{
	// Skip the current state when skip key is pressed
	if (input_->IsValueKeyPressed(Input::EInputValue::kSkip))
	{
		is_finish_ = true;
	}

	return is_finish_ == true ? false : true;
}

void InfoState::Draw()
{
	// Double Buffered
	HDC hdcScreen = GetDC(h_window_);
	HDC hdcMemory = CreateCompatibleDC(hdcScreen);
	HBITMAP hBlankBitmap = CreateCompatibleBitmap(hdcScreen, GAME_WIDTH, GAME_HEIGHT);

	// "Clear Screen"
	SelectObject(hdcMemory, hBlankBitmap);
	HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	HPEN hNullPen = CreatePen(PS_NULL, 1, RGB(255, 255, 255));
	SelectObject(hdcMemory, hNullPen);
	SelectObject(hdcMemory, hWhiteBrush);
	Rectangle(hdcMemory, 0, 0, GAME_WIDTH, GAME_HEIGHT);

	//Introduction
	WCHAR Text[kTxtBufferSize];
	wsprintf(Text, txt_);
	RECT win_Rectangle{ (LONG)txt_rect_.left, (LONG)txt_rect_.top, (LONG)txt_rect_.right, (LONG)txt_rect_.bottom };
	DrawText(hdcMemory, Text, (int)txt_size_, &win_Rectangle, DT_BOTTOM);

	// Present the Memory to the Screen
	BitBlt(hdcScreen, 0, 0, GAME_WIDTH, GAME_HEIGHT, hdcMemory, 0, 0, SRCCOPY);

	DeleteObject(hWhiteBrush);
	DeleteObject(hdcScreen);
	DeleteObject(hNullPen);
	DeleteObject(hBlankBitmap);
	DeleteDC(hdcMemory);
}

void InfoState::Reset()
{
	is_finish_ = false;
}