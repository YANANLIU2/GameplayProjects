#pragma once
#include "GameSettings.h"
#include "MyVector2.h"
#include <stdlib.h>

class Cell;
class TiledMap
{
	// An Array of tiles
	Cell** tiles_;

	// An array of bool used for recording of the current frame's tiles' states
	bool tiles_states_[kTotalTiles];

	// Eight neighbors around a tile
	static const int kNeighborNum = 8;

	static const MyVector2<int> kNeighborsArray[kNeighborNum];

public:
	// Constructor
	TiledMap();

	// Destructor
	~TiledMap();

	// Getters & Setters
	inline const bool get_is_index_valid(int index) const{ return 0 <= index && index < kTotalTiles; }

	// Acess the cell at the index
	inline Cell* operator[](int index) { return get_is_index_valid(index) ? tiles_[index] : nullptr; }

	// Get the index of the tile the cursor is on 
	int get_index_from_pixel_pos(float x, float y);

	// Reset all tiles in the map
	void Reset();

	// Update all tiles by the rules
	void Update();

	// Draw all alive tiles
	void Draw(HDC& hdc);

	// Get a tile's alive neighbors
	int GetAliveNeighbors(int x, int y);
};

