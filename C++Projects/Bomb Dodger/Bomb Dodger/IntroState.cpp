#include "stdafx.h"
#include "IntroState.h"
#include "GameSettings.h"

GameState::EStateType IntroState::type_ = GameState::EStateType::kIntro;

void IntroState::Draw()
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
	WCHAR Text[109];
	wsprintf(Text, L"Instructions:\nWASD: to move\nArrow KEY: to fire\nLose: if you get bitten\nWin: kill all zombies\nSpace: to begin");
	RECT win_Rectangle{ GAME_WIDTH / 2 -100, GAME_HEIGHT / 2-100, GAME_WIDTH / 2 + 200, GAME_HEIGHT / 2 + 50 };
	DrawText(hdcMemory, Text, 109, &win_Rectangle, DT_BOTTOM);

	// Present the Memory to the Screen
	BitBlt(hdcScreen, 0, 0, GAME_WIDTH, GAME_HEIGHT, hdcMemory, 0, 0, SRCCOPY);

	//delete
	DeleteObject(hWhiteBrush);
	DeleteObject(hdcScreen);
	DeleteObject(hNullPen);
	DeleteObject(hBlankBitmap);
	DeleteDC(hdcMemory);
}

bool IntroState::Update()
{
	if (is_finish_ == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void IntroState::GetInput(Input::InputValue input)
{
	if (input == Input::InputValue::kSkip)
	{
		is_finish_ = true;
	}
}

