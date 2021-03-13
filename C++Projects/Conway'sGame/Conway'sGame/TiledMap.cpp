#include "stdafx.h"
#include "TiledMap.h"
#include "Cell.h"

// Eight neighbors
const MyVector2<int> TiledMap::kNeighborsArray[] = { {0, -1}, {0, 1}, {1, 0},{-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

TiledMap::TiledMap() :tiles_(nullptr), tiles_states_()
{
	tiles_ = new Cell * [kMapWidth * kMapHeight];

	for (int y = 0; y < kMapHeight; y++)
	{
		for (int x = 0; x < kMapWidth; x++)
		{
			int index = y * kMapWidth + x;

			tiles_[index] = new Cell();
		}
	}
}

TiledMap::~TiledMap()
{
	// Delete all tiles
	for (int y = 0; y < kMapHeight; y++)
	{
		for (int x = 0; x < kMapWidth; x++)
		{
			int index = y * kMapWidth + x;

			delete tiles_[index];

			tiles_[index] = nullptr;
		}
	}

	delete[] tiles_;
}

int TiledMap::get_index_from_pixel_pos(float x, float y)
{
	int height = (int)y / kTileHeight;
	int width = (int)x / kTileWidth;
	return height * kMapWidth + width;
}

void TiledMap::Reset()
{
	for (int y = 0; y < kMapHeight; y++)
	{
		for (int x = 0; x < kMapWidth; x++)
		{
			tiles_[y * kMapWidth + x]->set_is_alive(false);
		}
	}
}

void TiledMap::Update()
{
	// Record the states 
	for (int y = 0; y < kMapHeight; y++)
	{
		for (int x = 0; x < kMapWidth; x++)
		{
			tiles_states_[y * kMapWidth + x] = tiles_[y * kMapWidth + x]->get_is_alive();
			if (tiles_states_[y * kMapWidth + x])
			{
				int xx = 0;
			}
		}
	}

	// Update every tile
	for (int y = 0; y < kMapHeight; y++)
	{
		for (int x = 0; x < kMapWidth; x++)
		{
			tiles_[y * kMapWidth + x]->Update(GetAliveNeighbors(x, y));
		}
	}
}

void TiledMap::Draw(HDC& hdc)
{
	for (int y = 0; y < kMapHeight; y++)
	{
		for (int x = 0; x < kMapWidth; x++)
		{
			int index = y * kMapWidth + x;

			if (tiles_[index]->get_is_alive())
			{
				Ellipse(hdc, x * kTileWidth, y * kTileHeight, (x + 1) * kTileWidth, (y + 1) * kTileHeight);
			}
		}
	}
}

int TiledMap::GetAliveNeighbors(int x, int y)
{
	int result = 0;

	for each (MyVector2<int> pos in kNeighborsArray)
	{
		MyVector2<int> neighbor = { x + pos.x_, y + pos.y_ };

		if (0 <= neighbor.x_ && neighbor.x_ < kMapWidth && 0 <= neighbor.y_ && neighbor.y_ < kMapHeight)
		{
			int index = neighbor.y_ * kMapWidth + neighbor.x_;

			if (tiles_states_[index])
			{
				result++;
			}
		}
	}

	return result;
}
