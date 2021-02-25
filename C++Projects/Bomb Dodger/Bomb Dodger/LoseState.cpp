#include "stdafx.h"
#include "LoseState.h"
#include "GameSettings.h"

GameState::EStateType LoseState::type_ = GameState::EStateType::kLose;

void LoseState::Draw()
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
	WCHAR Text[45];
	wsprintf(Text, L"Lose.\nPress Ese To Exit.\nPress P to Restart.");
	RECT win_Rectangle{ GAME_WIDTH / 2-85 , GAME_HEIGHT / 2 - 50, GAME_WIDTH / 2 + 85, GAME_HEIGHT / 2 + 50 };
	DrawText(hdcMemory, Text, 45, &win_Rectangle, DT_BOTTOM);

	// Present the Memory to the Screen
	BitBlt(hdcScreen, 0, 0, GAME_WIDTH, GAME_HEIGHT, hdcMemory, 0, 0, SRCCOPY);

	//Wait for 3 seconds
	Sleep(3000);
	is_finish_ = true;

	DeleteObject(hWhiteBrush);
	DeleteObject(hdcScreen);
	DeleteObject(hNullPen);
	DeleteObject(hBlankBitmap);
	DeleteDC(hdcMemory);
}

bool LoseState::Update()
{
	if (is_finish_ == true)
		return false;
	else
		return true;
}
