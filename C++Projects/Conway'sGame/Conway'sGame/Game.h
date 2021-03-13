#pragma once
#include "TiledMap.h"

class Game
{
private:
	// The quickest one simulation can be 
	const UINT kMinSimulationTime = 100;

	// The slowest one simulation can be 
	const UINT kMaxSimulationTime = 1500;

	// Each change wil + - the interval value from the current simulation time
	const UINT kChangeInterval = 100;

	// Whether the simulation is continuing or paused
	bool is_simulating_;

	// Whether we draw the grids or not
	bool is_drawing_grids_;

	// The time one simulation will cost
	UINT simulation_time_;

	// The map holds all tiles
	TiledMap tiled_map_;

	// Draws the lines indicating where each spot is
	void DrawBoard(HDC& hdc);

	// Draws the Xs and Os
	void DrawPieces(HDC& hdc);

public:
	// Constructor
	Game()
		: is_simulating_(false)
		, simulation_time_(500)
		, is_drawing_grids_(false)
	{
	}

	// Destructor
	~Game() = default;

	// Update input
	void Update();

	// Simulation one step forward
	void SimulationForward();

	// Draw all tiles
	void Draw(HDC& hdc);
	
	// Reset the game
	void Reset();

	// Getters & Setters
	
	inline bool get_is_simulating() const { return is_simulating_; }
	
	inline UINT get_simulation_time() const { return simulation_time_; }

	inline bool get_is_drawing_grids() { return is_drawing_grids_; }

	inline void set_is_simulating(bool value) { is_simulating_ = value; }

	inline void set_is_drawing_grids(bool value) { is_drawing_grids_ = value; }

	// Change simulation speed
	void AccelerateSimulation();
							   
	void DecelerateSimulation();
};

