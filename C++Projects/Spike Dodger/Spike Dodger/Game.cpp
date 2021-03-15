#include "stdafx.h"
#include <cmath> 
#include <math.h>  
#include "Game.h"
#include "GameSettings.h"
#include "ObjBase.h"
#include "Player.h"
#include "Spike.h"

Game::~Game()
{
	delete player_;

	player_ = nullptr;

	for (int i = 0; i < spike_num_; ++i)
	{
		auto spike = spike_array_[i];

		delete spike;

		spike = nullptr;
	}
}

bool Game::Init(HWND hWindow, HINSTANCE hInstance)
{
	player_ = new Player();
	
	for (int i = 0; i < spike_num_; i++)
	{
		spike_array_.Add(new Spike());
	}

	h_player_bmp_ = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

	GetObject(h_player_bmp_, sizeof(player_bmp_), &player_bmp_);

	h_spike_bmp_ = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));

	GetObject(h_spike_bmp_, sizeof(spike_bmp_), &spike_bmp_);

	h_background_bmp_ = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3));

	GetObject(h_background_bmp_, sizeof(background_bmp_), &background_bmp_);

	h_window_ = hWindow;
	
	Reset();

	return true;
}

void Game::Update()
{
	// Update spikes
	for (int i = 0; i < spike_num_; ++i)
	{
		spike_array_[i]->Update();
	}

	// Update the player
	player_->Update();
}

void Game::Draw()
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

	// Draw background
	HDC backgroundDc = CreateCompatibleDC(hdcScreen);

	SelectObject(backgroundDc, h_background_bmp_);

	StretchBlt(hdcMemory, 0, 0, GAME_WIDTH, GAME_HEIGHT, backgroundDc, 0, 0, background_bmp_.bmWidth, background_bmp_.bmHeight, SRCCOPY);

	// Draw spikes
	HDC spikeDc = CreateCompatibleDC(hdcScreen);
	
	SelectObject(spikeDc, h_spike_bmp_);

	for (int i = 0; i < spike_num_; ++i)
	{
		spike_array_[i]->Draw(spikeDc, hdcMemory, h_spike_bmp_, spike_bmp_);
	}

	// Draw the player 
	HDC playerDc = CreateCompatibleDC(hdcScreen);

	SelectObject(playerDc, h_player_bmp_);

	player_->Draw(playerDc, hdcMemory, h_player_bmp_, player_bmp_);

	// Present the Memory to the Screen
	BitBlt(hdcScreen, 0, 0, GAME_WIDTH, GAME_HEIGHT, hdcMemory, 0, 0, SRCCOPY);

	// IMPORTANT:  TERRIBLY INCREDIBLY IMPORTANT
	// Destroy objects in the *opposite* order in which they were made
	DeleteObject(hWhiteBrush);

	DeleteObject(hdcScreen);

	DeleteObject(hNullPen);

	DeleteDC(playerDc);

	DeleteDC(spikeDc);

	DeleteDC(backgroundDc);

	DeleteObject(hBlankBitmap);

	DeleteDC(hdcMemory);
}

void Game::Cleanup()
{
	DeleteObject(h_player_bmp_);

	DeleteObject(h_spike_bmp_);
}

void Game::Reset()
{
	player_->Reset();

	for (int i = 0; i < spike_num_; ++i)
	{
		spike_array_[i]->Reset();
	}
}

void Game::Movement(bool isRight)
{
	if (isRight)
	{
		player_->Move({ 1, 0 });
	}
	else
	{
		player_->Move({ -1, 0 });
	}
}

void Game::Collision()
{
	for (int i = 0; i < spike_num_; i++)
	{
		if (CollideWith(spike_array_[i], player_))
		{
			is_playing_ = false;
		}
	}
}

bool Game::CollideWith(ObjBase * objectOne, ObjBase * objectTwo)
{
	double distance = sqrt(pow(std::abs(objectOne->get_pos().x_ + objectOne->get_size().x_ /2 - objectTwo->get_pos().x_ - objectTwo->get_size().x_ /2) , 2) + pow(std::abs(objectOne->get_pos().y_ + objectOne->get_size().y_/2 - objectTwo->get_pos().y_ - objectTwo->get_size().y_ /2), 2));
	
	float minDis = objectOne->get_size().x_ /2 + objectTwo->get_size().x_ /2;
	
	return distance < minDis;
}

