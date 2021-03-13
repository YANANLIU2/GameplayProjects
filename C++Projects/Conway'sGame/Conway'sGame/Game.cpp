#include "stdafx.h"
#include "Game.h"
#include "MyLog.h"
#include "Cell.h"
#include "MyInput.h"
#include <Windows.h>
#include <string>

void Game::Draw(HDC& hdc)
{
	TextOut(hdc, 0, 0, L"Click or drag to make one or multiple cells alive or dead", 58);

	TextOut(hdc, 0, 20, L"Press S to forward one simulation", 34);

	TextOut(hdc, 0, 40, L"Press Space to simulate continuously or pause the simulation", 61);

	TextOut(hdc, 0, 60, L"Press P to hide/show grids", 27);

	TextOut(hdc, 0, 80, L"Press A/D to accelerate/decelerate the simulation", 46);

	TextOut(hdc, 0, 100, L"Press Esc to reset the simulation", 34);

	if (is_drawing_grids_)
	{
		DrawBoard(hdc);
	}

	DrawPieces(hdc);
}

void Game::Update()
{
	// If click or drag => toggle 
	if (MyInput::get_instance().get_is_click() || MyInput::get_instance().get_is_drag())
	{
		MyVector2<float> pos = MyInput::get_instance().get_mouse_pos();

		int index = tiled_map_.get_index_from_pixel_pos(pos.x_, pos.y_);

		// Log the index to the console 
		std::string s = std::to_string(index);

		char const* pchar = s.c_str();  

		MyLog::get_instance().LogToConsole(pchar);

		// Toggle the tile
		tiled_map_[index]->set_is_alive_toggle();
	}

	MyInput::get_instance().Update();
}

void Game::SimulationForward()
{
	tiled_map_.Update();
}

void Game::Reset()
{
	// Reset input
	MyInput::get_instance().Reset();

	// Reset the tiled map
	tiled_map_.Reset();
}

void Game::AccelerateSimulation()
{
	simulation_time_ -= kChangeInterval;

	MyLog::get_instance().LogToConsole("Accelerate the simulation speed");

	if (simulation_time_ < kMinSimulationTime)
	{
		simulation_time_ = kMinSimulationTime;

		MyLog::get_instance().LogToConsole("The simulation speed has reached maximum");
	}
}

void Game::DecelerateSimulation()
{
	simulation_time_ += kChangeInterval;

	MyLog::get_instance().LogToConsole("Decelerate the simulation speed");

	if (simulation_time_ > kMaxSimulationTime)
	{
		simulation_time_ = kMaxSimulationTime;

		MyLog::get_instance().LogToConsole("The simulation speed has reached minimum");
	}
}

void Game::DrawBoard(HDC& hdc)
{
	// Draw horizontal lines
	for (int iHorz = 0; iHorz < kMapHeight; ++iHorz)
	{
		MoveToEx(hdc, 0, (iHorz + 1) * kTileWidth, nullptr);

		LineTo(hdc, WINDOW_WIDTH, (iHorz + 1) * kTileWidth);
	}

	// Draw vertical lines
	for (int iVert = 0; iVert < kMapWidth; ++iVert)
	{
		MoveToEx(hdc, (iVert + 1) * kTileHeight, 0, nullptr);

		LineTo(hdc, (iVert + 1) * kTileHeight, WINDOW_HEIGHT);
	}
}

void Game::DrawPieces(HDC& hdc)
{
	tiled_map_.Draw(hdc);
}
