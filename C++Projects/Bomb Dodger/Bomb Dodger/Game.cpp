#include "stdafx.h"
#include "Game.h"
#include "Bitmaps.h"
#include <cmath> 
#include <math.h>  
#include "FrameTimer.h"
#define pCorner player->GetCorner()
#define bCorner bomb->GetCorner()


Game::Game()
	: m_isPlaying(true)
{
	m_BombVec.resize(kBombCount);
}


Game::~Game()
{
	delete m_player;
	m_player = nullptr;

	for (int i = 0; i < kBombCount; ++i)
	{
		delete m_BombVec[i];
		m_BombVec[i] = nullptr;
	}
}

Game & Game::Get()
{
	static Game instance;
	return instance;
}

bool Game::Init(HWND hWindow, HINSTANCE hInstance)
{
	m_player = new Player(hInstance);
	
	for (int i = 0; i < kBombCount; i++)
	{
		m_BombVec[i] = new Bomb(i, hInstance);
	}

	m_score = 0;
	m_hWindow = hWindow;
	Reset();

	return true;
}


void Game::Update()
{
	for (int i = 0; i < kBombCount; ++i)
	{
		m_BombVec[i]->Update();
	}
	m_player->Update();

	this->Collision();
}

void Game::Draw()
{
	m_score += 0.001;
	// Double Buffered
	HDC hdcScreen = GetDC(m_hWindow);
	HDC hdcMemory = CreateCompatibleDC(hdcScreen);
	HBITMAP hBlankBitmap = CreateCompatibleBitmap(hdcScreen, GAME_WIDTH, GAME_HEIGHT);

	// "Clear Screen"
	SelectObject(hdcMemory, hBlankBitmap);
	HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	HPEN hNullPen = CreatePen(PS_NULL, 1, RGB(255, 255, 255));
	SelectObject(hdcMemory, hNullPen);
	SelectObject(hdcMemory, hWhiteBrush);
	Rectangle(hdcMemory, 0, 0, GAME_WIDTH, GAME_HEIGHT);

	//text score: m_score

	WCHAR score_text[20];
	wsprintf(score_text, L"Score: %d", int(m_score));
	RECT score_Rectangle{ 10 , 10, 70, 30 };
	DrawText(hdcMemory, score_text, 20, &score_Rectangle, DT_BOTTOM);

	HDC BombDc = CreateCompatibleDC(hdcScreen);

	//Bomb
	SelectObject(BombDc, m_BombVec[0]->GethBmp());

	for (int i = 0; i < kBombCount; ++i)
	{
		StretchBlt(hdcMemory, (int)m_BombVec[i]->Getx(), (int)m_BombVec[i]->Gety(), m_BombVec[i]->Getxsize(), m_BombVec[i]->Getysize(),
			BombDc, 0, 0, m_BombVec[i]->GetBitmap().bmWidth, m_BombVec[i]->GetBitmap().bmHeight, SRCCOPY);
	}


	// Player
	HDC playerDc = CreateCompatibleDC(hdcScreen);

	SelectObject(playerDc, m_player->GethBmp());

	StretchBlt(hdcMemory, (int)m_player->Getx(), (int)m_player->Gety(), m_player->Getxsize(), m_player->Getysize(),
		playerDc, 0, 0, m_player->GetBitmap().bmWidth, m_player->GetBitmap().bmHeight, SRCCOPY);

	//win and lose text
	if (m_score >= 50.0 || m_isPlaying == false)
	{
		WCHAR endTxt[40];
		if (m_score >= 50.0 && m_isPlaying == true)
		{
			wsprintf(endTxt, L"Win!\nMade by YananLiu");
			m_isPlaying = false;
		}

		else
			wsprintf(endTxt, L"Lose!\nMade by YananLiu");

		RECT win_Rectangle{ GAME_WIDTH / 2 , GAME_HEIGHT / 2, GAME_WIDTH / 2 + 130, GAME_HEIGHT / 2 + 50 };
		DrawText(hdcMemory, endTxt, 40, &win_Rectangle, DT_BOTTOM);
	}

	
	if (m_score >= 51)
	{
		int x = 5;
	}
	if (m_score >= 52)
	{
		int x = 5;
	}
	
	// Present the Memory to the Screen
	BitBlt(hdcScreen, 0, 0, GAME_WIDTH, GAME_HEIGHT, hdcMemory, 0, 0, SRCCOPY);

	// IMPORTANT:  TERRIBLY INCREDIBLY IMPORTANT
	// Destroy objects in the *opposite* order in which they were made

	DeleteObject(hWhiteBrush);
	DeleteObject(hdcScreen);
	DeleteObject(hNullPen);

	DeleteDC(playerDc);
	DeleteDC(BombDc);
	DeleteObject(hBlankBitmap);
	DeleteDC(hdcMemory);
}

void Game::Cleanup()
{
	m_player->CleanUp();

	for (int i = 0; i < kBombCount; ++i)
		m_BombVec[i]->CleanUp();
}

void Game::Reset()
{
	m_player->Reset();

	for (int i = 0; i < kBombCount; ++i)
	{
		m_BombVec[i]->Reset();
	}
}

void Game::GoRight(bool right)
{
	if (right)
		m_player->MoveRight();
	else
		m_player->MoveLeft();
}

void Game::Collision()
{
	for (int i = 0; i < kBombCount; i++)
	{
		if (CollideWithPlayer(m_BombVec[i], m_player))
			m_isPlaying = false;
	}
}

bool Game::CollideWithPlayer(ObjBase * bomb, ObjBase * player)
{
	bool IsRight = (pCorner.Max_x < bCorner.Min_x);
	bool IsLeft = (pCorner.Min_x > bCorner.Max_x);
	bool IsAbove = (pCorner.Min_y > bCorner.Max_y);
	bool IsBelow = (pCorner.Max_y < bCorner.Min_y);

	bool IsNotOverlapping = (IsRight || IsLeft || IsAbove || IsBelow);

	return !IsNotOverlapping;
}

void Game::StopMoving()
{
	m_player->StopMoving();
}

void Game::BombChange()
{
	for (int i = 0; i < kBombCount; i++)
	{
		m_BombVec[i]->ChangeState();
	}
}
